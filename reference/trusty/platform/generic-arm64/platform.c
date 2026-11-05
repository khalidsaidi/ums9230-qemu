/*
 * Copyright (c) 2015 Google Inc. All rights reserved
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

#include <debug.h>
#include <dev/timer/arm_generic.h>
#include <err.h>
#include <inttypes.h>
#include <kernel/vm.h>
#include <lib/device_tree/libfdt_helpers.h>
#include <lib/dtb_service/dtb_service.h>
#include <lk/init.h>
#include <platform/gic.h>
#include <string.h>
#include <sys/types.h>
#if ARM64_BOOT_PROTOCOL_X0_DTB
#include <vsock/vsock.h>
#if MMIO_GUARD_ENABLED
#include <lib/libhypervisor/libhypervisor.h>
#endif
#endif

#include "debug.h"

#if ARM64_BOOT_PROTOCOL_X0_MEMSIZE || ARCH_ARM
#include "smc.h"
#endif

#ifdef GIC_VERSION
#include <dev/interrupt/arm_gic.h>

#define ARM_GENERIC_TIMER_INT_CNTV 27
#define ARM_GENERIC_TIMER_INT_CNTPS 29
#define ARM_GENERIC_TIMER_INT_CNTP 30

#define ARM_GENERIC_TIMER_INT_SELECTED(timer) ARM_GENERIC_TIMER_INT_##timer
#define XARM_GENERIC_TIMER_INT_SELECTED(timer) \
    ARM_GENERIC_TIMER_INT_SELECTED(timer)
#define ARM_GENERIC_TIMER_INT \
    XARM_GENERIC_TIMER_INT_SELECTED(TIMER_ARM_GENERIC_SELECTED)

#if GIC_VERSION <= 2
#define GICC_SIZE (0x1000)
#define GICD_SIZE (0x1000)
#define GICR_SIZE (0)
#else
#define GICC_SIZE (0x10000)
#define GICD_SIZE (0x10000)
#if GIC_VERSION < 4
#define GICR_SIZE (0x20000 * SMP_MAX_CPUS)
#else
#define GICR_SIZE (0x40000 * SMP_MAX_CPUS)
#endif
#endif
#elif HAFNIUM
#include <hf/types.h>
#define ARM_GENERIC_TIMER_INT HF_VIRTUAL_TIMER_INTID
#else
#error "Unknown interrupt library"
#endif

extern ulong lk_boot_args[4];

#if ARM64_BOOT_PROTOCOL_X0_DTB
static void generic_arm64_reserve_device_tree(paddr_t ram_base,
                                              size_t ram_size) {
    struct list_node list;
    list_initialize(&list);

    paddr_t fdt_paddr = lk_boot_args[0];
    if (fdt_paddr < ram_base || fdt_paddr - ram_base >= ram_size) {
        /* fdt address is outside ram_arena, no need to reserve it */
        return;
    }
    const void* fdt = paddr_to_kvaddr(fdt_paddr);
    if (fdt_check_header(fdt)) {
        return;
    }
    size_t fdt_size = fdt_totalsize(fdt);
    /* if fdt_paddr is not page aligned add offset in first page to size */
    fdt_size += fdt_paddr & (PAGE_SIZE - 1);
    uint fdt_page_count = DIV_ROUND_UP(fdt_size, PAGE_SIZE);
    uint fdt_reserved_page_count =
            pmm_alloc_range(fdt_paddr, fdt_page_count, &list);
    if (fdt_page_count != fdt_reserved_page_count) {
        panic("failed to reserve memory for device tree");
    }
}
#endif

/* initial memory mappings. parsed by start.S */
struct mmu_initial_mapping mmu_initial_mappings[] = {
        /* Mark next entry as dynamic as it might be updated
           by platform_reset code to specify actual size and
           location of RAM to use */
        {.phys = MEMBASE + KERNEL_LOAD_OFFSET,
         .virt = KERNEL_BASE + KERNEL_LOAD_OFFSET,
         .size = MEMSIZE,
         .flags = MMU_INITIAL_MAPPING_FLAG_DYNAMIC,
         .name = "ram"},

        /* null entry to terminate the list */
        {0, 0, 0, 0, 0}};

static pmm_arena_t ram_arena = {.name = "ram",
                                .base = MEMBASE + KERNEL_LOAD_OFFSET,
                                .size = MEMSIZE,
                                .flags = PMM_ARENA_FLAG_KMAP};

void platform_init_mmu_mappings(void) {
    /* go through mmu_initial_mapping to find dynamic entry
     * matching ram_arena (by name) and adjust it.
     */
    struct mmu_initial_mapping* m = mmu_initial_mappings;
    for (uint i = 0; i < countof(mmu_initial_mappings); i++, m++) {
        if (!(m->flags & MMU_INITIAL_MAPPING_FLAG_DYNAMIC))
            continue;

        if (strcmp(m->name, ram_arena.name) == 0) {
            /* update ram_arena */
            ram_arena.base = m->phys;
            ram_arena.size = m->size;
            ram_arena.flags = PMM_ARENA_FLAG_KMAP;

            break;
        }
    }
    pmm_add_arena(&ram_arena);
#if ARM64_BOOT_PROTOCOL_X0_DTB
    generic_arm64_reserve_device_tree(ram_arena.base, ram_arena.size);
#endif
}

#if ARM64_BOOT_PROTOCOL_X0_MEMSIZE || ARCH_ARM

static paddr_t generic_arm64_get_reg_base(int reg) {
#if ARCH_ARM64
    return generic_arm64_smc(SMC_FC64_GET_REG_BASE, reg, 0, 0);
#else
    return generic_arm64_smc(SMC_FC_GET_REG_BASE, reg, 0, 0);
#endif
}

#endif

#if ARM64_BOOT_PROTOCOL_X0_DTB
int static pci_init_fdt(const void* fdt) {
    int fdt_pci_offset =
            fdt_node_offset_by_compatible(fdt, 0, "pci-host-cam-generic");
    if (fdt_pci_offset < 0) {
        dprintf(CRITICAL, "failed to find pci device tree node\n");
        return ERR_NOT_FOUND;
    }

    paddr_t pci_paddr;
    size_t pci_size;
    int ret = fdt_helper_get_reg(fdt, fdt_pci_offset, 0, &pci_paddr, &pci_size);
    if (ret) {
        dprintf(CRITICAL, "failed to find get reg, err %d\n", ret);
        return ERR_NOT_VALID;
    }

    return pci_init_mmio(pci_paddr, pci_size, 1 << 11);
}
#endif /* ARM64_BOOT_PROTOCOL_X0_DTB */

static void platform_after_vm_init(uint level) {
#ifdef GIC_VERSION
#if ARM64_BOOT_PROTOCOL_X0_MEMSIZE || ARCH_ARM
    paddr_t gicc = generic_arm64_get_reg_base(SMC_GET_GIC_BASE_GICC);
    paddr_t gicd = generic_arm64_get_reg_base(SMC_GET_GIC_BASE_GICD);
    paddr_t gicr = generic_arm64_get_reg_base(SMC_GET_GIC_BASE_GICR);
#elif ARM64_BOOT_PROTOCOL_X0_DTB
    int ret;
    void* fdt_temp;
    size_t fdt_size;
    paddr_t fdt_paddr = lk_boot_args[0];
    ret = vmm_alloc_physical(vmm_get_kernel_aspace(), "device_tree_probe",
                             PAGE_SIZE, &fdt_temp, 0, fdt_paddr, 0,
                             ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                     ARCH_MMU_FLAG_CACHED |
                                     ARCH_MMU_FLAG_PERM_RO);
    if (ret) {
        dprintf(CRITICAL,
                "failed to map device tree page at 0x%" PRIxPADDR ": %d\n",
                fdt_paddr, ret);
        return;
    }
    const void* fdt = fdt_temp;

    if (fdt_check_header(fdt)) {
        dprintf(CRITICAL, "invalid device tree at 0x%" PRIxPADDR ": %d\n",
                fdt_paddr, ret);
        return;
    }

    fdt_size = fdt_totalsize(fdt);
    if (fdt_size > PAGE_SIZE) {
        fdt_size = page_align(fdt_size);
        dprintf(INFO, "remapping device tree with size 0x%zx\n", fdt_size);
        vmm_free_region(vmm_get_kernel_aspace(), (vaddr_t)fdt);
        ret = vmm_alloc_physical(vmm_get_kernel_aspace(), "device_tree_full",
                                 fdt_size, &fdt_temp, 0, fdt_paddr, 0,
                                 ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                         ARCH_MMU_FLAG_CACHED |
                                         ARCH_MMU_FLAG_PERM_RO);
        fdt = fdt_temp;
        if (ret) {
            dprintf(CRITICAL,
                    "failed to map device tree at 0x%" PRIxPADDR
                    " sz 0x%zx: %d\n",
                    fdt_paddr, fdt_size, ret);
            return;
        }
    }

    generic_arm64_setup_uart(fdt);

    int fdt_gic_offset = fdt_node_offset_by_compatible(fdt, 0, "arm,gic-v3");
    paddr_t gicc = 0; /* gic-v3 does not need a memory mapped gicc */
    paddr_t gicd, gicr;
    size_t gicd_size, gicr_size;
    if (fdt_helper_get_reg(fdt, fdt_gic_offset, 0, &gicd, &gicd_size)) {
        dprintf(CRITICAL, "failed get gicd regs, offset %d\n", fdt_gic_offset);
        return;
    }
    if (fdt_helper_get_reg(fdt, fdt_gic_offset, 1, &gicr, &gicr_size)) {
        dprintf(CRITICAL, "failed get gicr regs, offset %d\n", fdt_gic_offset);
        return;
    }
    if (gicd_size != GICD_SIZE) {
        dprintf(CRITICAL, "unexpected gicd_size %zd != %d\n", gicd_size,
                GICD_SIZE);
        return;
    }
    if (gicr_size < GICR_SIZE) {
        dprintf(CRITICAL, "unexpected gicr_size %zd < %d\n", gicr_size,
                GICR_SIZE);
        return;
    }

#if MMIO_GUARD_ENABLED
    /*
     * MMIO Guard map GIC addresses. Ignore not supported which implies that
     * guard is not used.
     */
    ret = hypervisor_mmio_map_region(gicc, GICC_SIZE);
    if (ret != NO_ERROR && ret != ERR_NOT_SUPPORTED) {
        dprintf(CRITICAL, "failed to mmio guard map gicc. error=%d\n", ret);
    }
    ret = hypervisor_mmio_map_region(gicd, GICD_SIZE);
    if (ret != NO_ERROR && ret != ERR_NOT_SUPPORTED) {
        dprintf(CRITICAL, "failed to mmio guard map gicd. error=%d\n", ret);
    }
    ret = hypervisor_mmio_map_region(gicr, GICR_SIZE);
    if (ret != NO_ERROR && ret != ERR_NOT_SUPPORTED) {
        dprintf(CRITICAL, "failed to mmio guard map gicr. error=%d\n", ret);
    }
#endif
#else
#error "Unknown ARM64_BOOT_PROTOCOL"
#endif
    dprintf(SPEW,
            "gicc 0x%" PRIxPADDR ", gicd 0x%" PRIxPADDR ", gicr 0x%" PRIxPADDR
            "\n",
            gicc, gicd, gicr);

    /* initialize the interrupt controller */
    struct arm_gic_init_info init_info = {
            .gicc_paddr = gicc,
            .gicc_size = GICC_SIZE,
            .gicd_paddr = gicd,
            .gicd_size = GICD_SIZE,
            .gicr_paddr = gicr,
            .gicr_size = GICR_SIZE,
    };
    arm_gic_init_map(&init_info);
#endif /* GIC_VERSION */

    /* initialize the timer block */
    arm_generic_timer_init(ARM_GENERIC_TIMER_INT, 0);

#if ARM64_BOOT_PROTOCOL_X0_DTB
    if (dtb_set(fdt, fdt_size) != NO_ERROR) {
        dprintf(CRITICAL, "failed to set device tree\n");
    }
    pci_init_fdt(fdt); /* ignore pci init errors */
#endif
}

LK_INIT_HOOK(platform_after_vm, platform_after_vm_init, LK_INIT_LEVEL_VM + 1);
