/*
 * Copyright (c) 2020 Google, Inc.
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

/*
 * This module registers smc handlers that are called by tests running in the
 * client os. This api is currently only available if lib/sm is enabled.
 */
#if WITH_LIB_SM

#define LOCAL_TRACE 0

#include <arch/arch_ops.h>
#include <arch/ops.h>
#include <err.h>
#include <inttypes.h>
#include <kernel/thread.h>
#include <kernel/timer.h>
#include <kernel/vm.h>
#include <lib/sm.h>
#include <lib/sm/sm_err.h>
#include <lib/sm/smcall.h>
#include <lib/smc/smc.h>
#include <limits.h>
#include <lk/init.h>
#include <stdatomic.h>
#include <string.h>
#include <trace.h>

#include "stdcalltest.h"

static ext_mem_obj_id_t args_get_id(struct smc32_args* args) {
    return (((uint64_t)args->params[1] << 32) | args->params[0]);
}

static size_t args_get_sz(struct smc32_args* args) {
    return (size_t)args->params[2];
}

/**
 * stdcalltest_sharedmem_rw - Test shared memory buffer.
 * @id:     Shared memory id.
 * @size:   Size.
 *
 * Check that buffer contains the 64 bit integer sqequnce [0, 1, 2, ...,
 * @size / 8 - 1] and modify sequence to [@size, @size - 1, size - 2, ...,
 * @size - (@size / 8 - 1)].
 *
 * Return: 0 on success. SM_ERR_INVALID_PARAMETERS is buffer does not contain
 * expected input pattern. SM_ERR_INTERNAL_FAILURE if @id could not be mapped.
 */
static long stdcalltest_sharedmem_rw(ext_mem_client_id_t client_id,
                                     ext_mem_obj_id_t mem_obj_id,
                                     size_t size) {
    struct vmm_aspace* aspace = vmm_get_kernel_aspace();
    status_t ret;
    long status;
    void* va;
    uint64_t* va64;

    if (!IS_PAGE_ALIGNED(size)) {
        return SM_ERR_INVALID_PARAMETERS;
    }

    ret = ext_mem_map_obj_id(aspace, "stdcalltest", client_id, mem_obj_id, 0, 0,
                             size, &va, PAGE_SIZE_SHIFT, 0,
                             ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret != NO_ERROR) {
        status = SM_ERR_INTERNAL_FAILURE;
        goto err_map;
    }
    va64 = va;

    for (size_t i = 0; i < size / sizeof(*va64); i++) {
        if (va64[i] != i) {
            TRACEF("input mismatch at %zd, got 0x%" PRIx64
                   " instead of 0x%zx\n",
                   i, va64[i], i);
            status = SM_ERR_INVALID_PARAMETERS;
            goto err_input_mismatch;
        }
        va64[i] = size - i;
    }
    status = 0;

err_input_mismatch:
    ret = vmm_free_region(aspace, (vaddr_t)va);
    if (ret) {
        status = SM_ERR_INTERNAL_FAILURE;
    }
err_map:
    return status;
}

#if ARCH_ARM64
long clobber_sve_asm(uint32_t byte_clobber);
long load_sve_asm(uint8_t* arr, uint64_t len);

#define SVE_VEC_LEN_BITS 128
#define SVE_NB_BYTE_VEC_LEN SVE_VEC_LEN_BITS / 8
#define SVE_SVE_REGS_COUNT 32

#define SMC_FC_TRNG_VERSION SMC_FASTCALL_NR(SMC_ENTITY_STD, 0x50)

static uint8_t sve_regs[SMP_MAX_CPUS][SVE_SVE_REGS_COUNT * SVE_NB_BYTE_VEC_LEN]
        __attribute__((aligned(16)));

enum clobber_restore_error {
    SVE_NO_ERROR = 0,
    SVE_GENERIC_ERROR = 1,
    SVE_REGISTER_NOT_RESTORED = 2,
    SVE_ERROR_LONG_TYPE = LONG_MAX
};

long stdcalltest_clobber_sve(struct smc32_args* args) {
    enum clobber_restore_error ret = SVE_NO_ERROR;
    if (!arch_sve_supported()) {
        /* test is OK, if there is no SVE there is nothing to assert but this is
         * not an ERROR */
        return ret;
    }

    uint64_t v_cpacr_el1 = arch_enable_sve();
    uint cpuid = arch_curr_cpu_num();
    long call_nb = args->params[1];

    /* First Call on cpu needs to Clobber ASM registers */
    if (call_nb == 1) {
        ret = clobber_sve_asm(args->params[0]);
        if (ret != SVE_NO_ERROR) {
            panic("Failed to Clobber ARM SVE registers: %lx\n", ret);
            ret = SVE_GENERIC_ERROR;
            goto end_stdcalltest_clobber_sve;
        }
    }

    /* Make sure registers are as expected */
    const uint8_t EXPECTED = (uint8_t)args->params[0];
    ret = load_sve_asm(sve_regs[cpuid], SVE_NB_BYTE_VEC_LEN);
    if (ret != SVE_NO_ERROR) {
        panic("Failed to Load ARM SVE registers: %lx\n", ret);
        ret = SVE_GENERIC_ERROR;
        goto end_stdcalltest_clobber_sve;
    }

    for (size_t idx = 0; idx < countof(sve_regs[cpuid]); ++idx) {
        uint8_t val = sve_regs[cpuid][idx];

        if (val != EXPECTED) {
            ret = SVE_REGISTER_NOT_RESTORED;
            goto end_stdcalltest_clobber_sve;
        }
    }

end_stdcalltest_clobber_sve:
    ARM64_WRITE_SYSREG(cpacr_el1, v_cpacr_el1);
    return ret;
}

static long stdcalltest_compute_fpacr(uint64_t* old_cpacr,
                                      uint64_t* new_cpacr) {
    uint64_t cpacr = ARM64_READ_SYSREG(cpacr_el1);

    DEBUG_ASSERT(old_cpacr);
    DEBUG_ASSERT(new_cpacr);

    if ((cpacr >> 20) & 1) {
        return SM_ERR_NOT_ALLOWED;
    }

    *old_cpacr = cpacr;
    *new_cpacr = cpacr | (3 << 20);
    return 0;
}

static uint32_t stdcalltest_random_u32(void) {
    /* Initialize the RNG seed to the golden ratio */
    static atomic_int hash = 0x9e3779b1U;
    int oldh, newh;

    /* Update the RNG with MurmurHash3 */
    do {
        newh = oldh = atomic_load(&hash);
        newh ^= newh >> 16;
        __builtin_mul_overflow(newh, 0x85ebca6bU, &newh);
        newh ^= newh >> 13;
        __builtin_mul_overflow(newh, 0xc2b2ae35U, &newh);
        newh ^= newh >> 16;
    } while (!atomic_compare_exchange_weak(&hash, &oldh, newh));

    return (uint32_t)oldh;
}

static struct fpstate stdcalltest_random_fpstate;

static long stdcalltest_clobber_fpsimd_clobber(struct smc32_args* args) {
    long ret;
    uint64_t old_cpacr, new_cpacr;
    bool loaded;

    /*
     * Check if the FPU at EL1 is already on;
     * it shouldn't be, so return an error if it is.
     * Otherwise, save the old value and restore it
     * after we're done.
     */
    ret = stdcalltest_compute_fpacr(&old_cpacr, &new_cpacr);
    if (ret) {
        return ret;
    }

    for (size_t i = 0; i < countof(stdcalltest_random_fpstate.regs); i++) {
        stdcalltest_random_fpstate.regs[i] =
                ((uint64_t)stdcalltest_random_u32() << 32) |
                stdcalltest_random_u32();
    }
    /*
     * TODO: set FPCR&FPSR to random values, but they need to be masked
     * because many of their bits are MBZ
     */
    stdcalltest_random_fpstate.fpcr = 0;
    stdcalltest_random_fpstate.fpsr = 0;

    ARM64_WRITE_SYSREG(cpacr_el1, new_cpacr);
    loaded = arm64_fpu_load_fpstate(&stdcalltest_random_fpstate, true);
    ARM64_WRITE_SYSREG(cpacr_el1, old_cpacr);
    return loaded ? 0 : SM_ERR_INTERNAL_FAILURE;
}

static long stdcalltest_clobber_fpsimd_check(struct smc32_args* args) {
    long ret;
    uint64_t old_cpacr, new_cpacr;
    struct fpstate new_fpstate;
    bool loaded;

    ret = stdcalltest_compute_fpacr(&old_cpacr, &new_cpacr);
    if (ret) {
        return ret;
    }

    ARM64_WRITE_SYSREG(cpacr_el1, new_cpacr);
    loaded = arm64_fpu_load_fpstate(&stdcalltest_random_fpstate, false);
    arm64_fpu_save_fpstate(&new_fpstate);
    ARM64_WRITE_SYSREG(cpacr_el1, old_cpacr);

    if (loaded) {
        /*
         * Check whether the current fpstate is still the one set
         * earlier by the clobber. If not, it means another thread
         * ran and overwrote our registers, and we do not want to
         * leak them here.
         */
        ret = SM_ERR_BUSY;
        goto err;
    }

    for (size_t i = 0; i < countof(new_fpstate.regs); i++) {
        if (new_fpstate.regs[i] != stdcalltest_random_fpstate.regs[i]) {
            TRACEF("regs[%zu] mismatch: %" PRIx64 " != %" PRIx64 "\n", i,
                   new_fpstate.regs[i], stdcalltest_random_fpstate.regs[i]);
            ret = SM_ERR_INTERNAL_FAILURE;
            goto err;
        }
    }
    if (new_fpstate.fpcr != stdcalltest_random_fpstate.fpcr) {
        TRACEF("FPCR mismatch: %" PRIx32 " != %" PRIx32 "\n", new_fpstate.fpcr,
               stdcalltest_random_fpstate.fpcr);
        ret = SM_ERR_INTERNAL_FAILURE;
        goto err;
    }
    if (new_fpstate.fpsr != stdcalltest_random_fpstate.fpsr) {
        TRACEF("FPSR mismatch: %" PRIx32 " != %" PRIx32 "\n", new_fpstate.fpsr,
               stdcalltest_random_fpstate.fpsr);
        ret = SM_ERR_INTERNAL_FAILURE;
        goto err;
    }

    /* Return 0 on success */
    ret = 0;

err:
    return ret;
}
#endif

/* 1ms x5000=5s should be long enough for the test to finish */
#define FPSIMD_TIMER_PERIOD_NS (1000000)
#define FPSIMD_TIMER_TICKS (5000)

static struct timer fpsimd_timers[SMP_MAX_CPUS];
static uint fpsimd_timer_ticks[SMP_MAX_CPUS];

static enum handler_return fpsimd_timer_cb(struct timer* timer,
                                           lk_time_ns_t now,
                                           void* arg) {
    uint cpu = arch_curr_cpu_num();

    fpsimd_timer_ticks[cpu]--;
    if (!fpsimd_timer_ticks[cpu]) {
        LTRACEF("Disabling FP test timer on cpu %u\n", cpu);
        timer_cancel(&fpsimd_timers[cpu]);
    }

    return INT_NO_RESCHEDULE;
}

static long stdcalltest_clobber_fpsimd_timer(struct smc32_args* args) {
    uint cpu = arch_curr_cpu_num();
    bool start_timer = !fpsimd_timer_ticks[cpu];

    DEBUG_ASSERT(arch_ints_disabled());

    LTRACEF("Enabling FP test timer on cpu %u\n", cpu);
    fpsimd_timer_ticks[cpu] = FPSIMD_TIMER_TICKS;
    if (start_timer) {
        timer_set_periodic_ns(&fpsimd_timers[cpu], FPSIMD_TIMER_PERIOD_NS,
                              fpsimd_timer_cb, NULL);
    }

    return 1;
}

static long stdcalltest_stdcall(struct smc32_args* args) {
    switch (args->smc_nr) {
    case SMC_SC_TEST_VERSION:
        return TRUSTY_STDCALLTEST_API_VERSION;
    case SMC_SC_TEST_SHARED_MEM_RW:
        return stdcalltest_sharedmem_rw(args->client_id, args_get_id(args),
                                        args_get_sz(args));
#if ARCH_ARM64
    case SMC_SC_TEST_CLOBBER_SVE: {
        return stdcalltest_clobber_sve(args);
    }
#endif
    default:
        return SM_ERR_UNDEFINED_SMC;
    }
}

static long stdcalltest_fastcall(struct smc32_args* args) {
    switch (args->smc_nr) {
#if ARCH_ARM64
    case SMC_FC_TEST_CLOBBER_FPSIMD_CLOBBER:
        return stdcalltest_clobber_fpsimd_clobber(args);
    case SMC_FC_TEST_CLOBBER_FPSIMD_CHECK:
        return stdcalltest_clobber_fpsimd_check(args);
#else
        /* This test is a no-op on other architectures, e.g., arm32 */
    case SMC_FC_TEST_CLOBBER_FPSIMD_CLOBBER:
    case SMC_FC_TEST_CLOBBER_FPSIMD_CHECK:
        return 0;
#endif
    default:
        return SM_ERR_UNDEFINED_SMC;
    }
}

static long stdcalltest_nopcall(struct smc32_args* args) {
    switch (args->params[0]) {
    case SMC_NC_TEST_CLOBBER_FPSIMD_TIMER:
        return stdcalltest_clobber_fpsimd_timer(args);
    default:
        return SM_ERR_UNDEFINED_SMC;
    }
}

static struct smc32_entity stdcalltest_sm_entity = {
        .stdcall_handler = stdcalltest_stdcall,
        .fastcall_handler = stdcalltest_fastcall,
        .nopcall_handler = stdcalltest_nopcall,
};

static void stdcalltest_init(uint level) {
    int err;

    for (size_t i = 0; i < SMP_MAX_CPUS; i++) {
        timer_initialize(&fpsimd_timers[i]);
    }

    err = sm_register_entity(SMC_ENTITY_TEST, &stdcalltest_sm_entity);
    if (err) {
        printf("trusty error register entity: %d\n", err);
    }
}
LK_INIT_HOOK(stdcalltest, stdcalltest_init, LK_INIT_LEVEL_APPS);

#endif
