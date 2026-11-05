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
#![feature(cfg_version)]
// C string literals were stabilized in Rust 1.77
#![cfg_attr(not(version("1.77")), feature(c_str_literals))]

use acpi::{AcpiHandler, AcpiTables, PhysicalMapping};

use rust_support::{
    init::lk_init_level,
    mmu::{ARCH_MMU_FLAG_CACHED, ARCH_MMU_FLAG_PERM_NO_EXECUTE, ARCH_MMU_FLAG_PERM_RO, PAGE_SIZE},
    vmm::{vmm_alloc_physical, vmm_free_region, vmm_get_kernel_aspace},
    LK_INIT_HOOK,
};

use core::ffi::{c_uint, c_void};
use core::ptr::NonNull;

const PAGE_MASK: usize = PAGE_SIZE as usize - 1;

#[derive(Clone)]
struct LkAcpiHandler;

impl AcpiHandler for LkAcpiHandler {
    // SAFETY: map_physical_region get passed a valid physical address range
    // if the assumptions below are met. It returns a read-only mapping to
    // that region and the caller must not create any mutable references
    // from the returned pointe.
    unsafe fn map_physical_region<T>(
        &self,
        physical_address: usize,
        size: usize,
    ) -> PhysicalMapping<Self, T> {
        let page_paddr = physical_address & !PAGE_MASK;
        let offset = physical_address - page_paddr;
        let aligned_size = (size + offset + PAGE_MASK) & !PAGE_MASK;
        let mut ptr: *mut c_void = core::ptr::null_mut();
        let ret = vmm_alloc_physical(
            vmm_get_kernel_aspace(),
            c"rust-acpi".as_ptr() as _,
            aligned_size,
            &mut ptr,
            0,
            page_paddr,
            0,
            ARCH_MMU_FLAG_CACHED | ARCH_MMU_FLAG_PERM_RO | ARCH_MMU_FLAG_PERM_NO_EXECUTE,
        );

        // If vmm_alloc_physical failed, panic.
        // Ideally we should return an error to the caller in that case, but
        // the api defined by the acpi crate does not allow that.
        if ret != 0 {
            panic!("vmm_alloc_physical failed, but map_physical_region is not allowed to return an error")
        }

        let nonnullptr = NonNull::new(ptr.wrapping_add(offset) as _).unwrap();

        PhysicalMapping::new(physical_address, nonnullptr, size, aligned_size - offset, Self)
    }
    fn unmap_physical_region<T>(region: &PhysicalMapping<Self, T>) {
        let ptr = region.virtual_start().as_ptr() as _;
        // SAFETY:: ptr came from vmm_alloc_physical
        unsafe { vmm_free_region(vmm_get_kernel_aspace(), ptr) };
    }
}

/// Search the ACPI tables for the physical address which is the base of the MMIO
/// region and pass it to `pci_init_mmio` to initialize the virtio-vsock bridge.
///
/// # Safety
///
/// A caller must ensure that this function is called exactly once during kernel
/// initialization on a system which has a BIOS (as opposed to UEFI systems).
unsafe extern "C" fn platform_acpi_init_func(_level: c_uint) {
    // SAFETY: search_for_rsdp_bios searches for a RSDP on BIOS systems.
    // It is not safe to call on a UEFI system. crosvm currently emulates
    // a BIOS system.
    let acpi_tables = match unsafe { AcpiTables::search_for_rsdp_bios(LkAcpiHandler) } {
        Ok(acpi_tables) => acpi_tables,
        Err(error) => {
            log::error!("search_for_rsdp_bios failed: {error:?}");
            return;
        }
    };
    let mcfg_table = match acpi_tables.find_table::<acpi::mcfg::Mcfg>() {
        Ok(mcfg_table) => mcfg_table,
        Err(error) => {
            log::error!("filed to find mcfg_table: {error:?}");
            return;
        }
    };
    let mcfg_entries = mcfg_table.entries();
    let entry = mcfg_entries[0];

    let entry_size = (1 + entry.bus_number_end as usize - entry.bus_number_start as usize) << 20;

    // SAFETY: the first argument must be a valid physical address pointing to the base of the MMIO region.
    // The second argument must be the size of the MMIO region and be valid under the PCI express version
    // implemented by the system. `pci_init_mmio` must not have been called previously.
    unsafe { vsock::pci_init_mmio(entry.base_address as usize, entry_size, 1usize << 15) };
}

LK_INIT_HOOK!(platform_acpi_init, platform_acpi_init_func, lk_init_level::LK_INIT_LEVEL_THREADING);
