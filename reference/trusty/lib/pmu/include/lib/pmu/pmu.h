/*
 * Copyright (C) 2023 The Android Open Source Project
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

#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "pmu_arch.h"

#ifndef ARM64_READ_SYSREG
#define DSB __asm__ volatile("dsb sy" ::: "memory")
#define ISB __asm__ volatile("isb" ::: "memory")

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define ARM64_READ_SYSREG(reg)                                  \
    ({                                                          \
        uint64_t _val;                                          \
        __asm__ volatile("mrs %0," TOSTRING(reg) : "=r"(_val)); \
        _val;                                                   \
    })

#define ARM64_WRITE_SYSREG_RAW(reg, val) \
    ({ __asm__ volatile("msr " TOSTRING(reg) ", %0" ::"r"(val)); })

#define ARM64_WRITE_SYSREG(reg, val)      \
    ({                                    \
        ARM64_WRITE_SYSREG_RAW(reg, val); \
        ISB;                              \
    })
#endif

static uint64_t set_bit(uint64_t reg, uint64_t bit_number) {
    return reg | bit_number;
}

static uint64_t clear_bit(uint64_t reg, uint64_t bit_number) {
    return reg & (~bit_number);
}

/**
 * get_pmu_feat - Returns ID_DFR0_EL1.PerfMon Bits
 *
 * Return: ID_DFR0_EL1.PerfMon Bits
 */
static uint64_t get_pmu_feat(void) {
    uint64_t id_dfr0_el1 = ARM64_READ_SYSREG(ID_DFR0_EL1);
    id_dfr0_el1 = id_dfr0_el1 >> 24; /* Shift PerfMon field down to bit 0 */
    id_dfr0_el1 &= 0x7;              /* Mask to leave just the PerfMon bits */
    return id_dfr0_el1;
}

/**
 * get_pmn - Returns the number of programmable counters
 *
 * Return: The number of available programmable counters
 */
static uint64_t get_pmn(void) {
    uint64_t pmcr_el0 = ARM64_READ_SYSREG(PMCR_EL0);
    pmcr_el0 = pmcr_el0 >> 11; /* Shift N field down to bit 0 */
    pmcr_el0 &= 0x1F;          /* Mask to leave just the 5 N bits */
    return pmcr_el0;
}

/**
 * pmn_config - Sets the event for a programmable counter to record
 * @counter: r0 = Which counter to program  (e.g. 0 for PMN0, 1 for PMN1)
 * @event:   r1 = The event code (from appropriate TRM or ARM Architecture
 * Reference Manual)
 */
static void pmn_config(uint64_t counter, uint64_t event) {
    ARM64_WRITE_SYSREG(PMSELR_EL0, counter);
    ARM64_WRITE_SYSREG(PMXEVTYPER_EL0, event);
}

/**
 * set_pmu_filters - Set Event Counter Filters
 *
 * @counter:     the index of the programmable counter slot to which the filter
 * applies
 * @filter_flags: filters to be applied to the programmable counter slot
 */
static void set_pmu_filters(uint64_t counter, uint64_t filter_flags) {
    ARM64_WRITE_SYSREG(PMSELR_EL0, counter);
    ARM64_WRITE_SYSREG(PMCCFILTR_EL0, filter_flags);
}

/**
 * ccnt_divider - Enables/disables the divider (1/64) on CCNT
 * @divider: r0 = If 0 disable divider, else enable dvider
 */
static void ccnt_divider(bool divider) {
    if (divider) {
        uint64_t reg = ARM64_READ_SYSREG(PMSELR_EL0);
        reg = clear_bit(reg, PMCR_EL0_D_BIT);
        ARM64_WRITE_SYSREG(PMSELR_EL0, reg);
    } else {
        uint64_t reg = ARM64_READ_SYSREG(PMSELR_EL0);
        reg = set_bit(reg, PMCR_EL0_D_BIT);
        ARM64_WRITE_SYSREG(PMSELR_EL0, reg);
    }
}

/**
 * enable_pmu - Global PMU enable
 * On ARM11 this enables the PMU, and the counters start immediately
 * On Cortex this enables the PMU, there are individual enables for the counters
 */
static void enable_pmu(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCR_EL0);
    reg = set_bit(reg, PMCR_EL0_E_BIT);
    ARM64_WRITE_SYSREG(PMCR_EL0, reg);
}

/**
 * disable_pmu - Global PMU disable
 * On Cortex, this overrides the enable state of the individual counters
 */
static void disable_pmu(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCR_EL0);
    reg = clear_bit(reg, PMCR_EL0_E_BIT);
    ARM64_WRITE_SYSREG(PMCR_EL0, reg);
}

/**
 * enable_ccnt - Enable the CCNT
 */
static void enable_ccnt(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCNTENSET_EL0);
    reg = set_bit(reg, PMCNTENSET_EL0_C_BIT);
    ARM64_WRITE_SYSREG(PMCNTENSET_EL0, reg);
}

/**
 * disable_ccnt - Disable the CCNT
 */
static void disable_ccnt(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCNTENSET_EL0);
    reg = clear_bit(reg, PMCNTENSET_EL0_C_BIT);
    ARM64_WRITE_SYSREG(PMCNTENSET_EL0, reg);
}

/**
 * enable_pmn - Enable PMN{n}
 * @counter: The counter to enable (e.g. 0 for PMN0, 1 for PMN1)
 */
static void enable_pmn(uint64_t counter) {
    uint64_t reg = ARM64_READ_SYSREG(PMCNTENSET_EL0);
    reg = set_bit(reg, (uint64_t)1 << counter);
    ARM64_WRITE_SYSREG(PMCNTENSET_EL0, reg);
}

/**
 * disable_pmn - Disable PMN{n}
 * @counter: The counter to disable (e.g. 0 for PMN0, 1 for PMN1)
 */
static void disable_pmn(uint64_t counter) {
    uint64_t reg = ARM64_READ_SYSREG(PMCNTENSET_EL0);
    reg = clear_bit(reg, (uint64_t)1 << counter);
    ARM64_WRITE_SYSREG(PMCNTENSET_EL0, reg);
}

/**
 * read_ccnt - Returns the value of CCNT
 *
 * Return: the value to PMCCNTR_EL0
 */
static uint64_t read_ccnt(void) {
    return ARM64_READ_SYSREG(PMCCNTR_EL0);
}

/**
 * read_pmn - Returns the value of PMN{n}
 * @counter: The counter to read (e.g. 0 for PMN0, 1 for PMN1)
 *
 * Return: the value to PMXEVCNTR_EL0 after selecting event
 */
static uint64_t read_pmn(uint64_t counter) {
    counter &= 0x1F;
    ARM64_WRITE_SYSREG(PMSELR_EL0, counter);
    return ARM64_READ_SYSREG(PMXEVCNTR_EL0);
}

/**
 * read_flags - Returns the value of the overflow flags
 *
 * Return: the value of PmovSCLR_EL0
 */
static uint64_t read_flags(void) {
    return ARM64_READ_SYSREG(PmovSCLR_EL0);
}

/**
 * write_flags - Writes the overflow flags
 * @flags: value of the flags to write to PmovSSET_EL0
 */
static void write_flags(uint64_t flags) {
    ARM64_WRITE_SYSREG(PmovSCLR_EL0, flags);
}

/**
 * reset_pmn - Resets the programmable counters
 */
static void reset_pmn(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCR_EL0);
    reg = set_bit(reg, PMCR_EL0_P_BIT);
    ARM64_WRITE_SYSREG(PMCR_EL0, reg);
}

/**
 * reset_ccnt - Resets the CCNT
 */
static void reset_ccnt(void) {
    uint64_t reg = ARM64_READ_SYSREG(PMCR_EL0);
    reg = set_bit(reg, PMCR_EL0_C_BIT);
    ARM64_WRITE_SYSREG(PMCR_EL0, reg);
}
/**
 * get_event_code_string - Get the code name for a given PMU event
 *
 * @event:  current states of the pmu counters
 *
 * Return:  The Code of the event as a String
 */
static const char* get_event_code_string(int event) {
    switch (event) {
    case PMU_EV_SW_INCR:
        return "SW_INCR";
    case PMU_EV_L1I_CACHE_REFILL:
        return "L1I_CACHE_REFILL";
    case PMU_EV_L1I_TLB_REFILL:
        return "L1I_TLB_REFILL";
    case PMU_EV_L1D_CACHE_REFILL:
        return "L1D_CACHE_REFILL";
    case PMU_EV_L1D_CACHE:
        return "L1D_CACHE";
    case PMU_EV_L1D_TLB_REFILL:
        return "L1D_TLB_REFILL";
    case PMU_EV_LD_RETIRED:
        return "LD_RETIRED";
    case PMU_EV_ST_RETIRED:
        return "ST_RETIRED";
    case PMU_EV_INST_RETIRED:
        return "INST_RETIRED";
    case PMU_EV_EXC_TAKEN:
        return "EXC_TAKEN";
    case PMU_EV_EXC_RETURN:
        return "EXC_RETURN";
    case PMU_EV_CID_WRITE_RETIRED:
        return "CID_WRITE_RETIRED";
    case PMU_EV_PC_WRITE_RETIRED:
        return "PC_WRITE_RETIRED";
    case PMU_EV_BR_IMMED_RETIRED:
        return "BR_IMMED_RETIRED";
    case PMU_EV_UNALIGNED_LDST_RETIRED:
        return "UNALIGNED_LDST_RETIRED";
    case PMU_EV_BR_MIS_PRED:
        return "BR_MIS_PRED";
    case PMU_EV_CPU_CYCLES:
        return "CPU_CYCLES";
    case PMU_EV_BR_PRED:
        return "BR_PRED";
    case PMU_EV_MEM_ACCESS:
        return "MEM_ACCESS";
    case PMU_EV_L1I_CACHE:
        return "L1I_CACHE";
    case PMU_EV_L1D_CACHE_WB:
        return "L1D_CACHE_WB";
    case PMU_EV_L2D_CACHE:
        return "L2D_CACHE";
    case PMU_EV_L2D_CACHE_REFILL:
        return "L2D_CACHE_REFILL";
    case PMU_EV_L2D_CACHE_WB:
        return "L2D_CACHE_WB";
    case PMU_EV_BUS_ACCESS:
        return "BUS_ACCESS";
    case PMU_EV_MEMORY_ERROR:
        return "MEMORY_ERROR";
    case PMU_EV_BUS_CYCLES:
        return "BUS_CYCLES";
    case PMU_EV_CHAIN:
        return "CHAIN";
    case PMU_EV_BUS_ACCESS_LD:
        return "BUS_ACCESS_LD";
    case PMU_EV_BUS_ACCESS_ST:
        return "BUS_ACCESS_ST";
    case PMU_EV_BR_INDIRECT_SPEC:
        return "BR_INDIRECT_SPEC";
    case PMU_EV_EXC_IRQ:
        return "EXC_IRQ";
    case PMU_EV_EXC_FIQ:
        return "EXC_FIQ";
    case -1:
        return "CCNT";
    default:
        return "UNKNOWN_EVENT";
    }
}

#define RECORD_SEL1 (U(0) | PMCCFILTR_EL0_U_BIT | PMCCFILTR_EL0_NSK_BIT)
#define RECORD_EL3 \
    (U(0) | PMCCFILTR_EL0_U_BIT | PMCCFILTR_EL0_P_BIT | PMCCFILTR_EL0_M_BIT)
#define RECORD_ALL (U(0) | PMCCFILTR_EL0_NSH_BIT)

/**
 * struct trusty_pmu_state - Holds the current state of pmu slots and counters.
 * @evts:             array of pmu counter events codes with which respective
 * slot have to be programmed
 * @vals:             array of pmu counter current values
 * @evt_cnt:         number of events/values
 */
struct trusty_pmu_state {
    uint64_t* evts;
    uint64_t* vals;
    uint64_t evt_cnt;
};

/**
 * pmu_start - Setup events slots and Start recording
 *
 * @state:      current states of the pmu counters
 */
static void pmu_start(struct trusty_pmu_state* state) {
    if (state == NULL || state->evts == NULL) {
        return;
    }

    uint64_t nb_counters = get_pmn();

    if (nb_counters < state->evt_cnt) {
        fprintf(stderr,
                "ERROR: There are only %" PRIu64
                " Programmable Counters, yet you are trying to record %" PRIu64
                " events.\n",
                nb_counters, state->evt_cnt);

        return;
    }

    enable_pmu();                  // Enable the PMU
    reset_ccnt();                  // Reset the CCNT (cycle counter)
    reset_pmn();                   // Reset the configurable counters
    write_flags((1 << 31) | 0xf);  // Reset overflow flags

    for (size_t i = 0; i < state->evt_cnt; i++) {
        pmn_config(i, state->evts[i] | RECORD_ALL);
        set_pmu_filters(i, 0U | RECORD_ALL);
    }
    ccnt_divider(0);  // Enable divide by 64
    enable_ccnt();    // Enable CCNT

    for (size_t i = 0; i < state->evt_cnt; i++)
        enable_pmn(i);
}

/**
 * pmu_stop - Stop recording
 *
 * @state:      current states of the pmu counters
 */
static void pmu_stop(struct trusty_pmu_state* state) {
    if (state == NULL || state->evts == NULL) {
        return;
    }
    disable_ccnt();

    for (size_t i = 0; i < state->evt_cnt; i++)
        disable_pmn(i);

    for (size_t i = 0; i < state->evt_cnt; i++) {
        state->vals[i + 1] = read_pmn(i);
    }
    state->vals[0] = read_ccnt();  // Read CCNT
}

/**
 * init_pmu_state - Allocate memory for values and bind events to be programmed
 *
 * @evt_arr:        array of events on whiches to program into the slots
 * @evt_arr_sz:     countof/nb_elements of evt_arr
 * @pmu_state:      current states of the pmu counters
 */
static inline void init_pmu_state(uint64_t* evt_arr,
                                  size_t evt_arr_sz,
                                  struct trusty_pmu_state* pmu_state) {
    pmu_state->vals = calloc(evt_arr_sz + 1, sizeof(uint64_t));
    pmu_state->evts = evt_arr;
    pmu_state->evt_cnt = evt_arr_sz;
}

/**
 * clean_pmu - Frees memory of value array and reset size
 *
 * @pmu_state:      current states of the pmu counters
 */
static inline void clean_pmu(struct trusty_pmu_state* pmu_state) {
    free(pmu_state->vals);
    pmu_state->vals = NULL;
    pmu_state->evt_cnt = 0;
}

/**
 * reset_pmu_cnts - Resets all pmu counters to 0
 *
 * @pmu_state:      current states of the pmu counters
 */
static inline void reset_pmu_cnts(struct trusty_pmu_state* pmu_state) {
    memset(pmu_state->vals, 0, sizeof(uint64_t) * pmu_state->evt_cnt);
}
