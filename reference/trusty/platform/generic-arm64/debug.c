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

#include <kernel/thread.h>
#include <kernel/vm.h>
#include <lib/device_tree/libfdt_helpers.h>
#include <lk/reg.h>
#include <lk/types.h>
#include <platform/debug.h>
#if MMIO_GUARD_ENABLED
#include <err.h>
#include <lib/libhypervisor/libhypervisor.h>
#endif

#include "debug.h"

#if GENERIC_ARM64_DEBUG_SMC_DEBUG_PUTC
#include "smc.h"
#endif

#if GENERIC_ARM64_DEBUG_FFA
#include <lib/arm_ffa/arm_ffa.h>
#endif

#if GENERIC_ARM64_DEBUG_UART
enum uart_type {
    UART_NONE,
    UART_PL011,
    UART_8250,
};

static uint8_t* uart_base;
static enum uart_type uart_type;

static void map_uart(paddr_t reg_paddr, enum uart_type new_uart_type) {
    int ret;
    void* page_vaddr;

    ASSERT(!uart_base);

    paddr_t reg_pbase = round_down(reg_paddr, PAGE_SIZE);
    ret = vmm_alloc_physical(
            vmm_get_kernel_aspace(), "uart", PAGE_SIZE, &page_vaddr, 0,
            reg_pbase, 0,
            ARCH_MMU_FLAG_PERM_NO_EXECUTE | ARCH_MMU_FLAG_UNCACHED_DEVICE);
    if (ret) {
        return;
    }

#if MMIO_GUARD_ENABLED
    /*
     * MMIO Guard map UART registers. Ignore not supported which implies that
     * guard is not used.
     *
     * TODO: Figure out why we sometimes get ERR_INVALID_ARGS when MMIO Guard is
     * not supported. It happens on qemu-generic-arm64-gicv3-test-debug builds.
     */
    ret = hypervisor_mmio_map_region(reg_pbase, PAGE_SIZE);
    if (ret != NO_ERROR && ret != ERR_NOT_SUPPORTED &&
        ret != ERR_INVALID_ARGS) {
        dprintf(CRITICAL, "failed to mmio guard map uart. error=%d\n", ret);
        return;
    }
#endif

    uart_type = new_uart_type;
    uart_base = (uint8_t*)page_vaddr + (reg_paddr - reg_pbase);
}

void generic_arm64_setup_uart(const void* fdt) {
    enum uart_type uart_type;
    int fdt_chosen_offset = fdt_path_offset(fdt, "/chosen");
    int fdt_stdout_path_len;
    const char* fdt_stdout_path = fdt_getprop(
            fdt, fdt_chosen_offset, "stdout-path", &fdt_stdout_path_len);
    if (!fdt_stdout_path) {
        return;
    }
    int fdt_stdout_offset = fdt_path_offset_namelen(fdt, fdt_stdout_path,
                                                    fdt_stdout_path_len - 1);

    if (!fdt_node_check_compatible(fdt, fdt_stdout_offset, "arm,pl011")) {
        uart_type = UART_PL011;
    } else if (!fdt_node_check_compatible(fdt, fdt_stdout_offset, "ns8250") ||
               !fdt_node_check_compatible(fdt, fdt_stdout_offset, "ns16550a")) {
        uart_type = UART_8250;
    } else {
        return;
    }

    paddr_t uart_reg;
    if (fdt_helper_get_reg(fdt, fdt_stdout_offset, 0, &uart_reg, NULL)) {
        return;
    }

    map_uart(uart_reg, uart_type);
}
#endif

void platform_dputc(char c) {
#if GENERIC_ARM64_DEBUG_SMC_DEBUG_PUTC
    generic_arm64_smc(SMC_FC_DEBUG_PUTC, (unsigned long)c, 0, 0);
#elif GENERIC_ARM64_DEBUG_FFA
    arm_ffa_console_log(&c, 1);
#elif GENERIC_ARM64_DEBUG_UART
    if (!uart_base) {
        return;
    }
    if (uart_type == UART_8250) {
        while (!(readb(uart_base + 5) & (1U << 5))) {
        }
        writeb(c, uart_base + 0);
    } else if (uart_type == UART_PL011) {
        while ((*REG16(uart_base + 0x018) & (1U << 5))) {
        }
        *REG16(uart_base + 0x000) = c;
    }
#else
#error Unsupported GENERIC_ARM64_DEBUG mode
#endif
}

int platform_dgetc(char* c, bool wait) {
    int ret = -1;

    while (wait)
        thread_sleep(100);

    return ret;
}
