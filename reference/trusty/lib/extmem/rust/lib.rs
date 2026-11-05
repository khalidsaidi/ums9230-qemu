/*
 * Copyright (c) 2025 Google Inc. All rights reserved
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

use crate::sys::ext_mem_client_id_t;
use crate::sys::ext_mem_get_obj_size;
use crate::sys::ext_mem_get_vmm_obj;
use crate::sys::ext_mem_obj_id_t;
use crate::sys::ext_mem_obj_set_match_tag;

use rust_support::lk_obj_ref_init;
use rust_support::mmu::PAGE_SIZE;
use rust_support::obj_ref;
use rust_support::status_t;
use rust_support::vmm::vmm_alloc_obj;
use rust_support::vmm::vmm_free_region;
use rust_support::vmm::vmm_get_kernel_aspace;
use rust_support::vmm::vmm_obj;
use rust_support::vmm::vmm_obj_del_ref;
use rust_support::Error;

use core::ffi::c_void;
use core::ffi::CStr;
use core::mem::zeroed;
use core::mem::ManuallyDrop;
use core::ptr::null_mut;
use core::ptr::NonNull;

mod sys {
    #![allow(non_camel_case_types)]
    #![allow(unused)]
    use rust_support::obj_ref;
    use rust_support::vmm::vmm_obj;
    include!(env!("BINDGEN_INC_FILE"));
}
/// An external memory object with ownership of its mapped memory.
///
/// Creating an ExtMemObj maps the object into the kernel address space and
/// dropping (either implicitly or with unmap_obj) unmaps the memory.
#[derive(Debug)]
pub struct ExtMemObj {
    vaddr: NonNull<c_void>,
    map_size: usize,
}

// SAFETY: Once created the only modifications to the underlying vmm_obj allowed
// is unmapping it which requires exclusive access to the ExtMemObj. Ensuring
// accesses to the mapped memory are synchronized is delegated to the safety
// requirements on the get_vaddr method.
unsafe impl Sync for ExtMemObj {}

// SAFETY: ExtMemObj may be sent between threads since any thread is allowed to
// unmap it, not just the thread that mapped it in. See safety comment on Sync
// impl for justification about calling get_vaddr from different threads.
unsafe impl Send for ExtMemObj {}

impl ExtMemObj {
    /// Maps an external memory object specified by `mem_obj_id` and `client_id`
    /// into the kernel address space..
    ///
    /// `size` can be specified to map a subset of the memory object starting at
    /// `offset`. If `size` is `None` the entire object is mapped in. It must be
    /// always be a multiple of the page size.
    #[allow(clippy::too_many_arguments)]
    pub fn map_obj_kernel(
        name: &'static CStr,
        client_id: ext_mem_client_id_t,
        mem_obj_id: ext_mem_obj_id_t,
        tag: u64,
        offset: usize,
        size: Option<usize>,
        align_log2: u8,
        vmm_flags: u32,
        arch_mmu_flags: u32,
    ) -> Result<Self, Error> {
        if let Some(sz) = size {
            assert!(sz % PAGE_SIZE as usize == 0);
        }

        let mut objp: *mut vmm_obj = null_mut();
        // SAFETY: obj_ref is a C type with two pointers which can be zeroed.
        // The obj_ref is initialized by lk_obj_ref_init before being used in
        // ext_mem_get_vmm_obj and does not move out of this function so it's
        // pointers to itself do not get invalidated.
        let mut tmp_obj_ref: obj_ref = unsafe { zeroed() };
        let tmp_obj_ref_ptr: *mut obj_ref = &raw mut tmp_obj_ref;
        // SAFETY: This takes a pointer to an obj_ref that will not move for its
        // entire lifetime.
        unsafe {
            lk_obj_ref_init(tmp_obj_ref_ptr);
        }

        // SAFETY: This takes a vmm_obj and vmm_obj_ref pointers that are
        // initialized to valid values and the error code is checked before
        // using the resulting vmm_obj. The function is thread-safe so there can
        // be no data race.
        let rc = unsafe {
            ext_mem_get_vmm_obj(
                client_id,
                mem_obj_id,
                tag,
                0, /* size hint */
                &raw mut objp,
                tmp_obj_ref_ptr,
            )
        };
        if rc < 0 {
            Error::from_lk(rc)?;
        }

        // SAFETY: objp points to a valid vmm_obj since ext_mem_get_vmm_obj didn't return an error.
        unsafe {
            // match_tag must be set before mapping the object
            ext_mem_obj_set_match_tag(objp, tag);
        }

        let aspace = vmm_get_kernel_aspace();
        let name = name.as_ptr();
        let map_size = match size {
            Some(sz) => sz,
            None => {
                // SAFETY: This function requires a pointer to a vmm_obj within
                // a ext_mem_obj which is ensured by ext_mem_get_vmm_obj
                unsafe { ext_mem_get_obj_size(objp) }
            }
        };
        let mut vaddr: *mut c_void = null_mut();
        // SAFETY: name is static and will outlive the allocation and objp
        // points to a valid vmm_obj because it was initialized in
        // ext_mem_get_vmm_obj. The return code is checked before the resulting
        // vaddr is used.
        let rc = unsafe {
            vmm_alloc_obj(
                aspace,
                name,
                objp,
                offset,
                map_size,
                &raw mut vaddr,
                align_log2,
                vmm_flags,
                arch_mmu_flags,
            )
        };
        // SAFETY: vmm_alloc_obj took a reference to the vmm_obj so dropping the
        // temporary reference create in this function will not drop the
        // vmm_obj. Arguments are valid because they were initialized in
        // ext_mem_get_vmm_obj and lk_obj_ref_init
        unsafe { vmm_obj_del_ref(objp, tmp_obj_ref_ptr) }
        if rc < 0 {
            Error::from_lk(rc)?;
        }
        let vaddr = NonNull::new(vaddr).expect("vmm_alloc_obj returned a non-null pointer");
        Ok(Self { vaddr, map_size })
    }

    /// Get a pointer to the memory mapped into the kernel address space for the
    /// memory object.
    ///
    /// # Safety
    ///
    /// Since the mapping is shared memory it may also be accessed from outside
    /// Trusty (e.g. VMs) so the caller must ensure that accesses are
    /// synchronized. Furthermore since ExtMemObj implements Sync these pointers
    /// may be obtained from any thread in Trusty so the caller must also ensure
    /// that accesses from different threads are synchronized. Finally the caller
    /// must ensure that pointers are not accessed after the ExtMemObj is
    /// dropped since that unmaps the memory from the kernel address space.
    pub unsafe fn get_vaddr(&self) -> NonNull<c_void> {
        self.vaddr
    }

    /// Get the size mapped for the external memory object.
    pub fn get_size(&self) -> usize {
        self.map_size
    }

    /// Unmaps the external memory object and returns whether the operation was
    /// successful  or not.
    ///
    /// On failure this returns a tuple with an ExtMemObj for the same mapping
    /// and a non-zero status_t returned by vmm_free_region.
    pub fn unmap_obj(self) -> Result<(), (Self, Error)> {
        let aspace = vmm_get_kernel_aspace();
        // Skip dropping self to avoid calling vmm_free_region multiple times
        let extmem = ManuallyDrop::new(self);
        // SAFETY: This deletes the obj_ref created by vmm_alloc_obj unmapping
        // the external memory object from the kernel address space.
        let rc = unsafe { vmm_free_region(aspace, extmem.vaddr.as_ptr() as usize) };
        if rc != 0 {
            return Error::from_lk(rc).map_err(|e| (ManuallyDrop::into_inner(extmem), e));
        }
        Ok(())
    }
}

impl Drop for ExtMemObj {
    /// Unmaps the external memory object.
    ///
    /// On failure this leaks the mapping without giving the caller a chance to
    /// retry.
    fn drop(&mut self) {
        let aspace = vmm_get_kernel_aspace();
        // SAFETY: This deletes the obj_ref created by vmm_alloc_obj unmapping
        // the external memory object from the kernel address space.
        let _rc: status_t = unsafe { vmm_free_region(aspace, self.vaddr.as_ptr() as usize) };
    }
}
