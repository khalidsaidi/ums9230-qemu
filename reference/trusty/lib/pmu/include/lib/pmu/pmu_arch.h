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

#ifndef PMU_ARCH_H
#define PMU_ARCH_H

#define U(_x) (_x##U)

/*******************************************************************************
 * Definitions of register offsets and fields in the CNTBaseN Frame of the
 * system level implementation of the Generic Timer.
 ******************************************************************************/
/* Physical Count register. */
#define CNTPCT_LO U(0x0)
/* Counter Frequency register. */
#define CNTBASEN_CNTFRQ U(0x10)
/* Physical Timer CompareValue register. */
#define CNTP_CVAL_LO U(0x20)
/* Physical Timer Control register. */
#define CNTP_CTL U(0x2c)

/* PMCR_EL0 definitions */
#define PMCR_EL0_RESET_VAL U(0x0)
#define PMCR_EL0_N_SHIFT U(11)
#define PMCR_EL0_N_MASK U(0x1f)
#define PMCR_EL0_N_BITS (PMCR_EL0_N_MASK << PMCR_EL0_N_SHIFT)
#define PMCR_EL0_LC_BIT (U(1) << 6)
#define PMCR_EL0_DP_BIT (U(1) << 5)
#define PMCR_EL0_X_BIT (U(1) << 4)
#define PMCR_EL0_D_BIT (U(1) << 3)
#define PMCR_EL0_C_BIT (U(1) << 2)
#define PMCR_EL0_P_BIT (U(1) << 1)
#define PMCR_EL0_E_BIT (U(1) << 0)

/* PMCNTENSET_EL0 definitions */
#define PMCNTENSET_EL0_C_BIT (U(1) << 31)
#define PMCNTENSET_EL0_P_BIT(x) (U(1) << x)

/* PMEVTYPER<n>_EL0 definitions */
#define PMEVTYPER_EL0_P_BIT (U(1) << 31)
#define PMEVTYPER_EL0_NSK_BIT (U(1) << 29)
#define PMEVTYPER_EL0_NSH_BIT (U(1) << 27)
#define PMEVTYPER_EL0_M_BIT (U(1) << 26)
#define PMEVTYPER_EL0_MT_BIT (U(1) << 25)
#define PMEVTYPER_EL0_SH_BIT (U(1) << 24)
#define PMEVTYPER_EL0_EVTCOUNT_BITS U(0x000003FF)

/* PMCCFILTR_EL0 definitions */
#define PMCCFILTR_EL0_P_BIT (U(1) << 31)
#define PMCCFILTR_EL0_U_BIT (U(1) << 30)
#define PMCCFILTR_EL0_NSK_BIT (U(1) << 29)
#define PMCCFILTR_EL0_NSH_BIT (U(1) << 27)
#define PMCCFILTR_EL0_M_BIT (U(1) << 26)
#define PMCCFILTR_EL0_MT_BIT (U(1) << 25)
#define PMCCFILTR_EL0_SH_BIT (U(1) << 24)
#define PMCCFILTR_EL0_T_BIT (U(1) << 23)
#define PMCCFILTR_EL0_RLK_BIT (U(1) << 22)
#define PMCCFILTR_EL0_RLU_BIT (U(1) << 21)
#define PMCCFILTR_EL0_RLH_BIT (U(1) << 20)

/* PMU event counter ID definitions */
#define PMU_EV_SW_INCR U(0x00)
#define PMU_EV_L1I_CACHE_REFILL U(0x01)
#define PMU_EV_L1I_TLB_REFILL U(0x02)
#define PMU_EV_L1D_CACHE_REFILL U(0x03)
#define PMU_EV_L1D_CACHE U(0x04)
#define PMU_EV_L1D_TLB_REFILL U(0x05)
#define PMU_EV_LD_RETIRED U(0x06)
#define PMU_EV_ST_RETIRED U(0x07)
#define PMU_EV_INST_RETIRED U(0x08)
#define PMU_EV_EXC_TAKEN U(0x09)
#define PMU_EV_EXC_RETURN U(0x0A)
#define PMU_EV_CID_WRITE_RETIRED U(0x0B)
#define PMU_EV_PC_WRITE_RETIRED U(0x0C)
#define PMU_EV_BR_IMMED_RETIRED U(0x0D)
#define PMU_EV_BR_RETURN_RETIRED U(0x0E)
#define PMU_EV_UNALIGNED_LDST_RETIRED U(0x0F)
#define PMU_EV_BR_MIS_PRED U(0x10)
#define PMU_EV_CPU_CYCLES U(0x11)
#define PMU_EV_BR_PRED U(0x12)
#define PMU_EV_MEM_ACCESS U(0x13)
#define PMU_EV_L1I_CACHE U(0x14)
#define PMU_EV_L1D_CACHE_WB U(0x15)
#define PMU_EV_L2D_CACHE U(0x16)
#define PMU_EV_L2D_CACHE_REFILL U(0x17)
#define PMU_EV_L2D_CACHE_WB U(0x18)
#define PMU_EV_BUS_ACCESS U(0x19)
#define PMU_EV_MEMORY_ERROR U(0x1A)
#define PMU_EV_BUS_CYCLES U(0x1D)
#define PMU_EV_CHAIN U(0x1E)
#define PMU_EV_BUS_ACCESS_LD U(0x60)
#define PMU_EV_BUS_ACCESS_ST U(0x61)
#define PMU_EV_BR_INDIRECT_SPEC U(0x7A)
#define PMU_EV_EXC_IRQ U(0x86)
#define PMU_EV_EXC_FIQ U(0x87)

#endif /* PMU_ARCH_H */
