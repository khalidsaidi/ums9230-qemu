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

use core::ffi::{c_ulong, c_void};
use rust_support::{
    mmu::{ARCH_MMU_FLAG_CACHED, ARCH_MMU_FLAG_PERM_NO_EXECUTE, ARCH_MMU_FLAG_PERM_RO, PAGE_SIZE},
    status_t,
    vmm::{vmm_alloc_physical, vmm_free_region, vmm_get_kernel_aspace},
};
use thiserror::Error;
use zerocopy::{FromBytes, Immutable, KnownLayout};

const PAGE_MASK: usize = PAGE_SIZE as usize - 1;

extern "C" {
    static lk_boot_args: [c_ulong; 4];
}

#[derive(Error, Debug)]
pub enum MappingError {
    #[error("failed to convert address: {0}")]
    ConversionError(#[from] core::num::TryFromIntError),

    #[error("mapping error {0}")]
    MappingError(status_t),
}

struct Mapped<T: ?Sized + FromBytes> {
    size: usize,
    ptr: *mut c_void,
    aligned_ptr: *mut c_void,

    _phantom: core::marker::PhantomData<T>,
}

impl<T: ?Sized + FromBytes> Mapped<T> {
    /// Maps [`size`] bytes at at the [`paddr`] physical address into virtual memory.
    /// If the [`paddr`] is not page aligned, the function will also map the preceding space
    /// to a closest page aligned address. Similarly the function will align up the size of
    /// the mapped region to page alignment.
    ///
    /// # Safety
    /// - The caller must be sure that [`paddr`] is mappable of at least [`size`] bytes
    ///   and readable
    /// - The caller must be sure that [`paddr`] is properly aligned for T
    /// - The caller must be sure that [`paddr`]..[`paddr`] + [`size`] contains the correct data
    ///   for T
    unsafe fn map_nbytes(paddr: u64, size: usize) -> Result<Self, MappingError> {
        let paddr = usize::try_from(paddr).map_err(MappingError::ConversionError)?;

        // Page align address and size
        let aligned_paddr = paddr & !PAGE_MASK;
        let aligned_size = (size + PAGE_MASK) & !PAGE_MASK;
        let offset = paddr - aligned_paddr;

        assert!(offset < aligned_size);
        assert_ne!(size, 0);

        let mut aligned_ptr: *mut c_void = core::ptr::null_mut();

        // Map the physical address to virtual memory
        // SAFETY:Delegated to caller
        let ret = unsafe {
            // vmm_alloc_physical function accepts a constant reference for outputting a pointer to
            // mapped region. Pass mutable reference and silence the clippy warning.
            #[allow(clippy::unnecessary_mut_passed)]
            vmm_alloc_physical(
                vmm_get_kernel_aspace(),
                c"rust-setup_data".as_ptr() as _,
                aligned_size,
                &mut aligned_ptr,
                0,
                aligned_paddr,
                0,
                ARCH_MMU_FLAG_CACHED | ARCH_MMU_FLAG_PERM_RO | ARCH_MMU_FLAG_PERM_NO_EXECUTE,
            )
        };

        // Make sure that the region was mapped correctly
        if ret != 0 || aligned_ptr.is_null() {
            return Err(MappingError::MappingError(ret));
        }

        // Adjust the pointer to virtual memory back from aligned address to desired offset
        // SAFETY: The pointer is within mapped range
        let ptr = unsafe { aligned_ptr.add(paddr - aligned_paddr) };

        Ok(Self { size, ptr, aligned_ptr, _phantom: Default::default() })
    }
}

impl<T: FromBytes> Mapped<T> {
    /// Maps T at at the [`paddr`] physical address into virtual memory. If the [`paddr`] is not
    /// page aligned, the function will also map the preceding space to a closest page aligned
    /// address. Similarly the function will align up the size of [`T`]  to page alignment.
    ///
    /// # Safety
    ///
    /// - The caller must be sure that [`paddr`] is mappable of at least sizeof(T) bytes
    ///   and readable.
    /// - The caller must be sure that [`paddr`] is properly aligned for T
    /// - The caller must be sure that [`paddr`]..[`paddr`] + sizeof(T) contains the correct
    ///   data for T
    pub unsafe fn map(paddr: u64) -> Result<Self, MappingError> {
        // SAFETY:Delegated to caller
        Self::map_nbytes(paddr, core::mem::size_of::<T>())
    }
}

impl<T: FromBytes> AsRef<T> for Mapped<T> {
    fn as_ref(&self) -> &T {
        debug_assert!(self.size == core::mem::size_of::<T>());

        // SAFETY:[`Self`] created with [`Self::map`] is at least the T size and the alignment
        // for T is asserted during the construction of [`Self`]. The bit pattern property is
        // asserted by requiring T to be [`FromBytes`].
        unsafe { self.ptr.cast::<T>().as_ref().unwrap() }
    }
}

impl<T: FromBytes> Mapped<[T]> {
    /// Maps `[T; size]` as a slice at at the [`paddr`] physical address into virtual memory
    /// If the [`paddr`] is not page aligned, the function will also map the preceding space
    /// to a closest page aligned address. Similarly the function will align up the size of
    /// `[T; size]` to page alignment.
    ///
    /// # Safety
    /// - The caller must be sure that [`paddr`] is mappable of at least [`size`] * sizeof(T)
    ///   bytes and readable.
    /// - The caller must be sure that [`paddr`] is properly aligned for T
    /// - The caller must be sure that [`paddr`]..[`paddr`] + [`size`] * sizeof(T) contains
    ///   the correct data for [T; size]
    /// - The [`size`] must not be zero.
    pub unsafe fn map_slice(paddr: u64, size: usize) -> Result<Self, MappingError> {
        // SAFETY:Delegated to caller
        Self::map_nbytes(paddr, size * core::mem::size_of::<T>())
    }
}

impl<T: ?Sized + FromBytes> Drop for Mapped<T> {
    fn drop(&mut self) {
        // Unmap the no longer needed memory region from virtual memory
        // SAFETY:: ptr came from vmm_alloc_physical
        unsafe { vmm_free_region(vmm_get_kernel_aspace(), self.aligned_ptr as _) };
    }
}

impl<T: FromBytes> AsRef<[T]> for Mapped<[T]> {
    fn as_ref(&self) -> &[T] {
        let n = self.size / core::mem::size_of::<T>();

        assert_ne!(n, 0);

        // SAFETY: The pointer compes from a successful vmm_alloc_physical call, so it's not null
        // and valid. It is mapped as RO making it immutable. The caller of constructor is
        // required to be sure that the data under the pointer is correct for [T; n] and properly
        // aligned.
        unsafe { core::slice::from_raw_parts::<'_, T>(self.ptr.cast::<T>(), n) }
    }
}

const BOOT_PARAMS_BOOT_FLAG_OFFSET: usize = 0x1fe;
const BOOT_PARAMS_BOOT_FLAG_MAGIC: u16 = 0xaa55;

const BOOT_PARAMS_HEADER_OFFSET: usize = 0x202;
const BOOT_PARAMS_HEADER_MAGIC: u32 = 0x53726448;

const BOOT_PARAMS_SETUP_DATA_OFFSET: usize = 0x250;

/// Based on crosvm's SETUP_DTB (x86_64/src/lib.rs)
pub const SETUP_DTB: u32 = 2;

/// Based on crosvm's setup_data_hdr (x86_64/src/lib.rs) which is
/// based on https://www.kernel.org/doc/html/latest/arch/x86/boot.html
#[repr(C)]
#[derive(Debug, Clone, Copy, FromBytes, Immutable, KnownLayout)]
struct setup_data_hdr {
    next: u64,
    type_: u32,
    len: u32,
}

/// Error type returned by [`SetupDataIter`] functions
#[derive(Error, Debug)]
pub enum FindSetupDataError {
    #[error("failed to map a memory region: {0}")]
    MappingError(#[from] MappingError),
    #[error("invalid magic in boot params structure")]
    InvalidMagic,
    #[error("failed to convert a value: {0}")]
    ConversionError(#[from] core::num::TryFromIntError),
}

/// Unpacked type and data from [`setup_data_hdr`]
pub struct SetupData {
    type_: u32,
    data: Mapped<[u8]>,
}

/// Iterator over `setup_data` chain rooted in `boot_params` structure
pub struct SetupDataIter {
    next: u64,
}

impl SetupDataIter {
    /// Searches for boot_params using second boot argument and then creates a iterator over
    /// setup_data chain.
    pub fn find() -> Result<Self, FindSetupDataError> {
        // SAFETY: lk_boot_args are set in early init and not modified afterwards
        let boot_params_addr = unsafe { lk_boot_args[1] };

        // Map the boot_params structure
        // SAFETY: boot_params struct should be passed by boot loader in second register
        let mapped_boot_params = unsafe {
            Mapped::<[u8]>::map_slice(
                boot_params_addr,
                BOOT_PARAMS_SETUP_DATA_OFFSET + core::mem::size_of::<u64>(),
            )?
        };

        let boot_params: &[u8] = mapped_boot_params.as_ref();

        // Verify that constant value of boot_flag in boot_params matches
        let boot_flag = u16::from_le_bytes(
            boot_params[BOOT_PARAMS_BOOT_FLAG_OFFSET..][..2].try_into().unwrap(),
        );

        if boot_flag != BOOT_PARAMS_BOOT_FLAG_MAGIC {
            return Err(FindSetupDataError::InvalidMagic);
        }

        // Verify that constant value of header in boot_params matches
        let header =
            u32::from_le_bytes(boot_params[BOOT_PARAMS_HEADER_OFFSET..][..4].try_into().unwrap());

        if header != BOOT_PARAMS_HEADER_MAGIC {
            return Err(FindSetupDataError::InvalidMagic);
        }

        // Get the first setup_data_hdr node address in the chain
        let next = u64::from_le_bytes(
            boot_params[BOOT_PARAMS_SETUP_DATA_OFFSET..][..8].try_into().unwrap(),
        );

        Ok(Self { next })
    }

    fn find_next(&mut self) -> Result<Option<SetupData>, FindSetupDataError> {
        // Check if the end of chain has been reached
        if self.next == 0u64 {
            return Ok(None);
        }

        // Briefly map setup_data_hdr into memory and copy into variable.
        // SAFETY:Each setup_data/next address passed using boot_params struct from bootloader
        // is expected to be valid.
        let mapped_hdr = unsafe { Mapped::<setup_data_hdr>::map(self.next)? };
        let hdr: setup_data_hdr = *mapped_hdr.as_ref();
        drop(mapped_hdr);

        // Calculate data start address
        let payload = self.next + u64::try_from(core::mem::size_of::<setup_data_hdr>())?;

        // Set the next setup_data_hdr address in the chain
        self.next = hdr.next;

        // Map the data into virtual memory and return it
        // SAFETY: The setup_data pointee is expected to be a valid mappable address and
        // size.
        let data = unsafe { Mapped::<[u8]>::map_slice(payload, usize::try_from(hdr.len)?)? };

        Ok(Some(SetupData { type_: hdr.type_, data }))
    }
}

impl Iterator for SetupDataIter {
    type Item = Result<SetupData, FindSetupDataError>;

    fn next(&mut self) -> Option<Self::Item> {
        // Repack the Option and Result
        match self.find_next() {
            Ok(Some(next)) => Some(Ok(next)),
            Ok(None) => None,
            Err(err) => {
                // Prevent next iterations to avoid dead lock
                self.next = 0u64;

                Some(Err(err))
            }
        }
    }
}

/// Searches for boot_params structure and returns iterator that yields setup_datas with DTBs
pub fn find_dtbs(
) -> Result<impl Iterator<Item = Result<impl AsRef<[u8]>, FindSetupDataError>>, FindSetupDataError>
{
    Ok(SetupDataIter::find()?.filter_map(|setup| match setup {
        // Filter out setup_data_hdr that are not DTBs
        Ok(setup) if setup.type_ == SETUP_DTB => Some(Ok(setup.data)),
        Ok(_) => None,
        Err(err) => Some(Err(err)),
    }))
}
