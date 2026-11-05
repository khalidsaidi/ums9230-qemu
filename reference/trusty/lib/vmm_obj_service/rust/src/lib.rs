/*
 * Copyright (c) 2024 Google Inc. All rights reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#![no_std]

use core::ffi::CStr;
use core::marker::PhantomPinned;
use core::pin::Pin;
use rust_support::{
    ktipc::{ktipc_port_acl, ktipc_server, ktipc_server_new, ktipc_server_start},
    mmu::PAGE_SIZE,
    vmm::{
        vmm_get_kernel_aspace, vmm_get_obj, vmm_obj_service, vmm_obj_service_add,
        vmm_obj_service_create_ro, vmm_obj_service_destroy, vmm_obj_slice, vmm_obj_slice_init,
        vmm_obj_slice_release, VmmPageArray,
    },
    Error,
};
use trusty_std::boxed::Box;
use zerocopy::{Immutable, IntoBytes};

#[derive(Immutable, IntoBytes)]
#[repr(C)]
pub struct VmmObjServiceHeader {
    data_start: u32,
    size: u32,
}
const HDR_SIZE: usize = core::mem::size_of::<VmmObjServiceHeader>();

fn create_obj_service_ro(
    port: &'static CStr,
    acl: &'static ktipc_port_acl,
    slice: &vmm_obj_slice,
    size: usize,
) -> Result<*mut vmm_obj_service, Error> {
    let mut svc: *mut vmm_obj_service = core::ptr::null_mut();
    // SAFETY: port and acl are static and therefore valid for the lifetime of vmm_obj_service.
    let rc = unsafe { vmm_obj_service_create_ro(port.as_ptr(), acl, slice.obj, 0, size, &mut svc) };
    if rc < 0 {
        log::error!("Failed to create service {:X}", rc);
        Error::from_lk(rc)?;
    }
    Ok(svc)
}

struct VmmObj {
    page_array: VmmPageArray,
    slice: vmm_obj_slice,
    _marker: PhantomPinned,
}
impl VmmObj {
    fn new(page_array: VmmPageArray) -> Result<Pin<Box<Self>>, Error> {
        let aspace = vmm_get_kernel_aspace();
        let ptr = page_array.ptr();
        let size = page_array.size();
        let mut slice = Box::<Self>::new_uninit();
        // SAFETY: Initializes a vmm_obj_slice to a default state. Slice is allocated above.
        unsafe { vmm_obj_slice_init(&raw mut (*slice.as_mut_ptr()).slice) };
        // SAFETY: Move page_array since we're aliasing it's pointer and want to prevent anyone
        // else from accessing it. This also ensures that underlying memory remains allocated for
        // the lifetime of VmmObj.
        unsafe { (*slice.as_mut_ptr()).page_array = page_array };
        // SAFETY: The object has been initialized by the two operations above.
        let mut slice = unsafe { slice.assume_init() };
        // SAFETY: ptr allocated by the vmm service. slice has been default initialized above and
        // is populated by this call with the object backing aligned buffer.
        let rc = unsafe { vmm_get_obj(aspace, ptr as usize, size, &mut slice.as_mut().slice) };
        if rc < 0 {
            Error::from_lk(rc)?;
        }
        // obj_ref in vmm_obj_slice cannot be moved, to convert this into Pin.
        let slice = Box::<VmmObj>::into_pin(slice);
        Ok(slice)
    }
}

impl Drop for VmmObj {
    fn drop(&mut self) {
        // SAFETY: Deallocating resources on failure. vmm_obj_slice_release is safe to call on an
        // object in the default state.
        unsafe { vmm_obj_slice_release(&mut self.slice) };
    }
}

/// Shares a buffer with the TAs specified in acl. The buffer is copied to new pages and prefixed
/// with size of the passed in data as a usize. This size will differ from that provided by
/// vmm_obj_service_create_ro and vmm_obj_map_ro as those function operate in increments of
/// PAGE_SIZE.
///
/// # Arguments
///
/// * `buffer` - a buffer to share with TAs.
/// * `size` - size of buffer.
/// * `align_log2` - alignment to use for the start of the destination data.
/// * `port` - a tipc port name for TAs to request the mapped buffer.
/// * `acl` - a ktipc_port_acl specifying which trust zones may connect and which apps may connect.
///     If uuids is empty, any app may connect.
///
pub fn share_sized_buffer(
    buffer: *const u8,
    size: usize,
    align_log2: u8,
    port: &'static CStr,
    acl: &'static ktipc_port_acl,
) -> Result<(), Error> {
    let aligned_ptr: usize = buffer as usize & !(PAGE_SIZE as usize - 1);
    let offset = buffer as usize - aligned_ptr;
    let aligned_size = (size + offset).next_multiple_of(PAGE_SIZE as usize);

    let mut phys_page_array = VmmPageArray::new_physical(port, aligned_ptr, aligned_size, 0, 0)?;

    let align = 1usize << align_log2;
    let dst_data_start = HDR_SIZE.next_multiple_of(align);
    let dst_size = (size + dst_data_start).next_multiple_of(PAGE_SIZE as usize);

    let mut page_array = VmmPageArray::new(port, dst_size, 0, 0)?;
    let header = VmmObjServiceHeader { data_start: dst_data_start as u32, size: size as u32 };
    page_array.as_mut_slice()[..HDR_SIZE].copy_from_slice(header.as_bytes());
    page_array.as_mut_slice()[dst_data_start..size + dst_data_start]
        .copy_from_slice(&phys_page_array.as_mut_slice()[offset..offset + size]);

    let slice = VmmObj::new(page_array)?;

    let srv = ktipc_server_new(port);
    // srv becomes owned by a new thread in ktipc_server_start, so leak the box to ensure Rust
    // doesn't deallocate it.
    let srv: *mut ktipc_server = Box::<ktipc_server>::leak(srv);
    // SAFETY: srv has been intentionally leaked and ownership is transferred to a thread create by
    // ktipc_server_start.
    let rc = unsafe { ktipc_server_start(srv) };
    if rc < 0 {
        log::error!("Failed to create thread: {:X}", rc);
        Error::from_lk(rc)?;
    }

    let mut svc = create_obj_service_ro(port, acl, &slice.slice, dst_size)?;

    // SAFETY: vmm_obj_service_add add a new service (svc) to the ktipc server (srv). srv has
    // already been moved to its own thread and svc now becomes owned by srv.
    let rc = unsafe { vmm_obj_service_add(svc, srv) };
    if rc < 0 {
        log::error!("Failed to add service: {:X}", rc);
        // SAFETY: Deallocating resources on failure.
        unsafe { vmm_obj_service_destroy(&mut svc) };
        Error::from_lk(rc)?;
    }

    Ok(())
}
