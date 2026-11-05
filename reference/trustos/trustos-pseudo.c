// pseudo-C decompilation of trustos.elf
/* ===== start @ 0x94020000 size 612 ===== */
// write access to const memory has been detected, the output may be wrong!
void __fastcall start(unsigned __int64 a1)
{
  unsigned __int64 StatusReg; // x19
  __int64 i; // x9
  __int64 (__fastcall **j)(); // x22
  unsigned __int64 v4; // x23
  __int64 (__fastcall *v5)(); // x24
  __int64 (__fastcall *v6)(); // x9
  unsigned __int64 v7; // x26
  unsigned __int64 v8; // x25
  __int64 v9; // x27
  unsigned __int64 v11; // x23
  __int64 *v12; // x13
  unsigned __int64 v13; // x12
  unsigned __int64 v14; // x11
  __int64 v15; // x9
  unsigned __int64 v16; // x14
  __int64 *v17; // x10
  unsigned __int64 v18; // x9
  __int64 k; // x9

  _WriteStatusReg(SCTLR_EL1, _ReadStatusReg(SCTLR_EL1) & 0xFFFFFFFFFFFFEFF3LL | 0x1004);
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( (StatusReg & 0xFFF) != 0 )
  {
    while ( 1 )
      ;
  }
  for ( i = 0; i != 256; ++i )
    qword_9405D000[i] = 0;
  for ( j = &off_9405A000; ; j += 5 )
  {
    v5 = *j;
    v4 = (unsigned __int64)j[1];
    v7 = (unsigned __int64)j[2];
    v6 = j[3];
    if ( ((unsigned __int8)v6 & 8) != 0 )
    {
      v5 = start;
      if ( a1 != 0 )
        v7 = a1;
      *j = start;
      j[2] = (__int64 (__fastcall *)())v7;
    }
    if ( v7 == 0 )
    {
      for ( k = 0; k < 256; ++k )
        qword_9405D800[k] = 0;
      qword_9405D800[(unsigned __int64)&loc_94020258 >> 30] = ((unsigned __int64)&loc_94020258 & 0xFFFFFFFFC0000000LL)
                                                            + 1801;
      dword_9405A0C8 = 0;
      __asm { TLBI            VMALLE1IS }
      __isb(0xFu);
      __dsb(0xFu);
      _WriteStatusReg(MAIR_EL1, 0xFF0400u);
      _WriteStatusReg(TCR_EL1, 0x2B523351AuLL);
      __isb(0xFu);
      _WriteStatusReg(TTBR0_EL1, (unsigned __int64)qword_9405D800);
      _WriteStatusReg(TTBR1_EL1, (unsigned __int64)qword_9405D000);
      __isb(0xFu);
      _WriteStatusReg(SCTLR_EL1, _ReadStatusReg(SCTLR_EL1) | 1);
      __isb(0xFu);
      JUMPOUT(0xFFFFFFFFE0000264LL);
    }
    v8 = v7;
    if ( ((unsigned __int8)v6 & 2) != 0 )
    {
      v9 = 0x60000000000400LL;
      goto LABEL_22;
    }
    if ( ((unsigned __int8)v6 & 4) != 0 )
      break;
    do
    {
      v9 = 0x40000000000788LL;
      v7 = -536682496LL - v4;
      if ( v4 >= 0xFFFFFFFFE002E000LL )
      {
        v9 = 0x60000000000788LL;
        v7 = -536633344LL - v4;
        if ( v4 >= 0xFFFFFFFFE003A000LL )
        {
          v9 = 0x60000000000708LL;
          while ( v4 > 0xFFFFFFFFE03E0000LL )
            ;
          while ( v8 < -532807680LL - v4 )
            ;
          v7 = v8;
        }
      }
LABEL_22:
      _CF = v8 >= v7;
      v8 -= v7;
      while ( !_CF )
        ;
      while ( (((unsigned __int16)(v4 | (unsigned __int16)v5) | (unsigned __int16)v7) & 0xFFF) != 0 )
        ;
      v11 = v4 ^ 0xFFFFFFFFE0000000LL;
      while ( (v11 & 0xFFFFFFFFE0000000LL) != 0 )
        ;
      do
      {
        v12 = qword_9405D000;
        v13 = 21;
        v14 = v11 >> 21;
        while ( v13 > 0x1E
             || (v11 | (unsigned __int64)v5) >> v13 << v13 != (v11 | (unsigned __int64)v5)
             || v7 >> v13 == 0 )
        {
          v16 = v12[v14];
          if ( v16 == 0 )
          {
            qword_9405CA78 = -532803584;
            v17 = &qword_943FF020[508];
            do
            {
              *v17 = 0;
              v17[1] = 0;
              v17 += 2;
            }
            while ( (unsigned __int64)v17 < 0x94401000 );
            v16 = (unsigned __int64)&qword_943FF020[508] + 3;
            v12[v14] = (__int64)&qword_943FF020[508] + 3;
          }
          while ( (v16 & 3) != 3 )
            ;
          v12 = (__int64 *)(v16 & 0xFFFFFFFFFFFFFFFCLL);
          v18 = v11 & ~(-1LL << v13);
          v13 -= 9LL;
          v14 = v18 >> v13;
        }
        v15 = v9 | 3;
        if ( v13 != 12 )
          v15 = v9 | 1;
        v12[v14] = v15 | (unsigned __int64)v5;
        v11 += 1LL << v13;
        v5 = (__int64 (__fastcall *)())((char *)v5 + (1LL << v13));
        v7 -= 1LL << v13;
      }
      while ( v7 != 0 );
      v4 = v11 ^ 0xFFFFFFFFE0000000LL;
    }
    while ( v8 != 0 );
  }
  v9 = 0x60000000000404LL;
  goto LABEL_22;
}

/* ===== secondary_cpu_entry @ 0x94020264 size 128 ===== */
void __noreturn secondary_cpu_entry()
{
  __int64 v0; // x19
  __int64 v5; // x9
  __int64 i; // x10
  signed __int64 v7; // x19

  _WriteStatusReg(TCR_EL1, 0x2B52335A7uLL);
  __isb(0xFu);
  __asm { TLBI            VMALLE1 }
  __isb(0xFu);
  if ( v0 == 0 )
  {
    v5 = -536600576;
    for ( i = 140408; i != 0; i -= 8 )
    {
      *(_QWORD *)v5 = 0;
      v5 += 8;
    }
    bootstrap();
  }
  if ( (unsigned __int8)v0 < 4uLL )
  {
    v7 = (unsigned __int8)v0 | ((v0 & 0xFFFFFFFFFFFFFF00LL) >> 6);
    if ( v7 < 4 )
      secondary_cpu_start(v7);
  }
  while ( 1 )
    __wfe();
}

/* ===== uart_putc @ 0x94022000 size 88 ===== */
__int64 __fastcall uart_putc(__int64 result)
{
  result = (unsigned __int8)result;
  if ( (unsigned __int8)result == 10 )
  {
    while ( (MEMORY[0xFFFFFFFFFF10000C] & 0x7F00) != 0 )
      ;
    MEMORY[0xFFFFFFFFFF100000] = 13;
  }
  while ( (MEMORY[0xFFFFFFFFFF10000C] & 0x7F00) != 0 )
    ;
  MEMORY[0xFFFFFFFFFF100000] = (unsigned __int8)result;
  return result;
}

/* ===== uart_getc @ 0x94022058 size 156 ===== */
__int64 __fastcall uart_getc(_BYTE *a1, char a2)
{
  unsigned int v3; // w1

  if ( a2 != 0 )
  {
    while ( (MEMORY[0xFFFFFFFFFF10000C] & 0x10) != 0 )
      thread_yield();
    v3 = 0;
    *a1 = MEMORY[0xFFFFFFFFFF100000];
    return v3;
  }
  if ( (MEMORY[0xFFFFFFFFFF10000C] & 0x10) != 0 )
    return (unsigned int)-1;
  *a1 = MEMORY[0xFFFFFFFFFF100000];
  return 0;
}

/* ===== gic_init @ 0x940220F4 size 332 ===== */
__int64 gic_init()
{
  __int64 v0; // x24
  __int64 v1; // x23
  int v2; // w2
  int v3; // w2
  __int64 v5; // [xsp+48h] [xbp+48h] BYREF

  v0 = smc_call(-50331647, 1, 0, 0);
  v1 = smc_call(-50331647, 0, 0, 0);
  if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
    log_printf("gicc 0x%lx, gicd 0x%lx\n", v0, v1);
  v5 = -65536;
  v2 = vmm_map(-536460256, "gic", 4096, &v5, 0, v0, 1, 2);
  if ( v2 != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("%s: failed %d\n", "generic_arm64_map_regs", v2);
  v5 = -61440;
  v3 = vmm_map(-536460256, "gic", 4096, &v5, 0, v1, 1, 2);
  if ( v3 != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("%s: failed %d\n", "generic_arm64_map_regs", v3);
  gic_dist_enable();
  return arm_generic_timer_init(29, 0);
}

/* ===== platform_early_init @ 0x94022240 size 196 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 platform_early_init()
{
  __int64 v0; // x20
  __int64 (__fastcall *v1)(); // x2

  v0 = -536633344;
  if ( (MEMORY[0xFFFFFFFFE003A018] & 8) != 0 && (unsigned int)strcmp(MEMORY[0xFFFFFFFFE003A020], -536682352) == 0 )
    goto LABEL_8;
  if ( (MEMORY[0xFFFFFFFFE003A040] & 8) != 0 && (unsigned int)strcmp(MEMORY[0xFFFFFFFFE003A048], -536682352) == 0 )
  {
    v0 = -536633304;
LABEL_8:
    v1 = *(__int64 (__fastcall **)())v0;
    qword_9405A0A0 = *(_QWORD *)(v0 + 16);
    off_9405A098 = v1;
    dword_9405A090 = 1;
    return pmm_add_arena(qword_9405A078);
  }
  if ( (MEMORY[0xFFFFFFFFE003A068] & 8) != 0 )
  {
    v0 = -536633264;
    if ( (unsigned int)strcmp(MEMORY[0xFFFFFFFFE003A070], -536682352) == 0 )
      goto LABEL_8;
  }
  return pmm_add_arena(qword_9405A078);
}

/* ===== smc_call @ 0x94022304 size 8 ===== */
void smc_call()
{
  __asm { SMC             #0 }
}

/* ===== get_stack_frame @ 0x9402230C size 72 ===== */
_QWORD *__fastcall get_stack_frame(_QWORD *result)
{
  __int64 v1; // [xsp+0h] [xbp-68h] BYREF

  *result = &v1;
  return result;
}

/* ===== el3_to_el1_entry @ 0x94022354 size 68 ===== */
void __fastcall __noreturn el3_to_el1_entry(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9)
{
  _WriteStatusReg(SCR_EL3, _ReadStatusReg(SCR_EL3) | 0x400);
  _WriteStatusReg(HCR_EL2, 0x80000000);
  _WriteStatusReg(CPTR_EL2, 0x33FFu);
  _WriteStatusReg(CPACR_EL1, 0x300000u);
  _WriteStatusReg(SP_EL1, (unsigned __int64)&a9);
  _WriteStatusReg(ELR_EL3, (unsigned __int64)nullsub_1);
  _WriteStatusReg(SPSR_EL3, 0x3C5u);
  __isb(0xFu);
  __asm { ERET }
}

/* ===== nullsub_1 @ 0x94022398 size 4 ===== */
void nullsub_1()
{
  ;
}

/* ===== spin_trylock @ 0x9402239C size 24 ===== */
unsigned __int64 __fastcall spin_trylock(unsigned __int64 *a1)
{
  unsigned __int64 result; // x0

  result = __ldaxr(a1);
  if ( result == 0 )
    return __stxr(1u, a1);
  return result;
}

/* ===== spin_lock @ 0x940223B4 size 32 ===== */
unsigned __int64 *__fastcall spin_lock(unsigned __int64 *result)
{
  unsigned __int64 v1; // x2

  __sevl();
  do
  {
    do
    {
      __wfe();
      v1 = __ldaxr(result);
    }
    while ( v1 != 0 );
  }
  while ( __stxr(1u, result) != 0 );
  return result;
}

/* ===== spin_unlock @ 0x940223D4 size 8 ===== */
unsigned __int64 *__fastcall spin_unlock(unsigned __int64 *result)
{
  atomic_store(0, result);
  return result;
}

/* ===== dcache_clean_range @ 0x940223FC size 32 ===== */
__int64 __fastcall dcache_clean_range(__int64 result, __int64 a2)
{
  unsigned __int64 v2; // x3

  v2 = result & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { DC              CIVAC, X3 }
    v2 += 32LL;
  }
  while ( v2 < result + a2 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_invalidate_range @ 0x9402241C size 32 ===== */
__int64 __fastcall dcache_invalidate_range(__int64 result, __int64 a2)
{
  unsigned __int64 v2; // x3

  v2 = result & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { DC              IVAC, X3 }
    v2 += 32LL;
  }
  while ( v2 < result + a2 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_clean_invalidate_range @ 0x9402243C size 60 ===== */
__int64 __fastcall dcache_clean_invalidate_range(__int64 result, __int64 a2)
{
  unsigned __int64 v2; // x3
  unsigned __int64 v7; // x3

  v2 = result & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { DC              CVAU, X3 }
    v2 += 32LL;
  }
  while ( v2 < result + a2 );
  __dsb(0xFu);
  v7 = result & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { IC              IVAU, X3 }
    v7 += 32LL;
  }
  while ( v7 < result + a2 );
  __dsb(0xFu);
  return result;
}

/* ===== arch_early_init @ 0x94022478 size 56 ===== */
__int64 __fastcall arch_early_init(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8)
{
  unsigned __int64 v8; // x0
  __int64 vars0; // [xsp+0h] [xbp+0h]

  _WriteStatusReg(VBAR_EL1, 0xFFFFFFFFE0001000LL);
  __isb(0xFu);
  v8 = _ReadStatusReg(CurrentEL) >> 2;
  if ( (unsigned int)v8 > 1 )
    el3_to_el1_entry(v8, a2, a3, a4, a5, a6, a7, a8, vars0);
  __asm { MSR             DAIFClr, #1 }
  return platform_early_init();
}

/* ===== platform_init_secondary @ 0x940224B0 size 72 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 *platform_init_secondary()
{
  unsigned __int64 v0; // x3
  __int64 *result; // x0

  nullsub_2();
  dword_94062000 = 3;
  smp_init(0);
  spin_unlock((unsigned __int64 *)&qword_9405A0D0);
  result = &qword_9405A0D0;
  v0 = (unsigned __int64)&qword_9405A0D0 & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { DC              CVAC, X3 }
    v0 += 32LL;
  }
  while ( v0 < (unsigned __int64)qword_9405A0D8 );
  __dsb(0xFu);
  return result;
}

/* ===== wfi @ 0x940224F8 size 8 ===== */
void wfi()
{
  __wfi();
}

/* ===== secondary_cpu_start @ 0x94022500 size 188 ===== */
__int64 __fastcall secondary_cpu_start(
        __int64 result,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8)
{
  unsigned __int64 StatusReg; // x1
  __int64 v9; // x3
  __int64 v10; // x2
  unsigned __int64 v11; // x1
  unsigned __int64 v12; // x0
  __int64 v18; // x0
  unsigned int v19; // w1
  __int64 v20; // [xsp+0h] [xbp+0h]

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  v9 = StatusReg & 0x1000000;
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v10 = (StatusReg >> 8) & 0xF;
  v11 = (unsigned __int8)StatusReg | (unsigned __int64)(4 * v10);
  if ( v11 == result )
  {
    _WriteStatusReg(VBAR_EL1, 0xFFFFFFFFE0001000LL);
    __isb(0xFu);
    v12 = _ReadStatusReg(CurrentEL) >> 2;
    if ( (unsigned int)v12 > 1 )
      el3_to_el1_entry(v12, v11, v10, v9, a5, a6, a7, a8, v20);
    __asm { MSR             DAIFClr, #1 }
    spin_lock((unsigned __int64 *)&qword_9405A0D0);
    spin_unlock((unsigned __int64 *)&qword_9405A0D0);
    v18 = call_init_hooks(2, 1, 458751);
    nullsub_2(v18);
    do
      v19 = __ldxr((unsigned int *)&dword_94062000);
    while ( __stxr(v19 - 1, (unsigned int *)&dword_94062000) != 0 );
    __sev();
    return secondary_cpu_main(&dword_94062000);
  }
  return result;
}

/* ===== dump_iframe @ 0x940225BC size 296 ===== */
__int64 __fastcall dump_iframe(_QWORD *a1)
{
  printf("iframe %p:\n", a1);
  printf("x0  0x%16llx x1  0x%16llx x2  0x%16llx x3  0x%16llx\n", *a1, a1[1], a1[2], a1[3]);
  printf("x4  0x%16llx x5  0x%16llx x6  0x%16llx x7  0x%16llx\n", a1[4], a1[5], a1[6], a1[7]);
  printf("x8  0x%16llx x9  0x%16llx x10 0x%16llx x11 0x%16llx\n", a1[8], a1[9], a1[10], a1[11]);
  printf("x12 0x%16llx x13 0x%16llx x14 0x%16llx x15 0x%16llx\n", a1[12], a1[13], a1[14], a1[15]);
  printf("x16 0x%16llx x17 0x%16llx x18 0x%16llx x19 0x%16llx\n", a1[16], a1[17], a1[18], a1[19]);
  printf("x20 0x%16llx x21 0x%16llx x22 0x%16llx x23 0x%16llx\n", a1[20], a1[21], a1[22], a1[23]);
  printf("x24 0x%16llx x25 0x%16llx x26 0x%16llx x27 0x%16llx\n", a1[24], a1[25], a1[26], a1[27]);
  printf("x28 0x%16llx x29 0x%16llx lr  0x%16llx sp  0x%16llx\n", a1[28], a1[29], a1[30], a1[31]);
  printf("elr 0x%16llx\n", a1[32]);
  return printf((const char *)invalid_exception_stub, a1[33]);
}

/* ===== sync_exception_handler @ 0x940226E4 size 332 ===== */
long double __fastcall sync_exception_handler(_QWORD *a1)
{
  unsigned int StatusReg; // w20
  unsigned int v3; // w19
  __int64 v4; // x0
  __int64 v5; // x6
  __int64 v6; // x0
  __int64 v7; // x1
  _QWORD *v8; // x2
  long double result; // q0
  unsigned __int64 v16; // x0
  unsigned __int64 v17; // x0
  unsigned __int64 v18; // x1
  __int64 v19; // x0
  int v20; // w1
  unsigned __int64 v21; // x2
  unsigned __int64 v22; // x4

  StatusReg = _ReadStatusReg(ESR_EL1);
  v3 = StatusReg >> 26;
  if ( ((StatusReg >> 26) & 0xFFFFFFFB) == 0x11 )
  {
    __asm { MSR             DAIFClr, #1 }
    syscall_dispatch();
    __asm { MSR             DAIFSet, #1 }
    return result;
  }
  if ( v3 == 7 )
    goto LABEL_16;
  v4 = -536682496;
  v5 = a1[32];
  if ( MEMORY[0xFFFFFFFFE002E000] == v5 )
    goto LABEL_10;
  v6 = -536682480;
  v7 = 0;
  while ( 1 )
  {
    v8 = (_QWORD *)v6;
    if ( v7 == 2 )
      break;
    ++v7;
    v6 += 16;
    if ( *v8 == v5 )
      goto LABEL_11;
  }
  printf("sync_exception\n");
  dump_iframe(a1);
  printf(
    "ESR 0x%x: ec 0x%x, il 0x%x, iss 0x%x\n",
    StatusReg,
    v3,
    (StatusReg & 0x2000000) != 0,
    StatusReg & 0xFFFFFF);
  if ( v3 == 21 )
  {
    printf("syscall\n");
    return result;
  }
  if ( (a1[33] & 0xFLL) != 0 )
  {
    halt(0, 9);
LABEL_16:
    v16 = _ReadStatusReg(CPACR_EL1);
    if ( ((v16 >> 20) & 3) != 3 )
    {
      _WriteStatusReg(CPACR_EL1, (unsigned int)v16 | 0x300000);
      __isb(0xFu);
      v17 = _ReadStatusReg(TPIDR_EL1);
      v18 = _ReadStatusReg(MPIDR_EL1);
      if ( (v18 & 0x1000000) != 0 )
        v18 >>= 8;
      v19 = v17 + 88;
      v20 = (unsigned __int8)v18 | (4 * ((v18 >> 8) & 0xF));
      if ( v19 != qword_94062008[v20] || v20 != *(_DWORD *)(v19 + 520) )
      {
        *(_DWORD *)(v19 + 520) = v20;
        v21 = *(unsigned int *)(v19 + 512);
        v22 = *(unsigned int *)(v19 + 516);
        qword_94062008[v20] = v19;
        result = *(long double *)v19;
        _WriteStatusReg(FPCR, v21);
        _WriteStatusReg(FPSR, v22);
      }
    }
    return result;
  }
  v4 = halt(3, 9);
LABEL_10:
  v8 = (_QWORD *)v4;
LABEL_11:
  a1[32] = v8[1];
  return result;
}

/* ===== invalid_exception_handler @ 0x94022830 size 72 ===== */
__int64 __fastcall invalid_exception_handler(_QWORD *a1, int a2)
{
  __int64 v3; // x0

  printf("invalid exception, which 0x%x\n", a2);
  dump_iframe(a1);
  if ( (a1[33] & 0xFLL) == 0 )
    halt(3, 9);
  v3 = halt(0, 9);
  return save_fpu_state(v3);
}

/* ===== save_fpu_state @ 0x94022878 size 88 ===== */
__int64 __fastcall save_fpu_state(
        __int64 a1,
        long double a2,
        long double a3,
        long double a4,
        long double a5,
        long double a6,
        long double a7,
        long double a8,
        long double a9)
{
  __int128 v9; // q8
  __int128 v10; // q9
  __int128 v11; // q10
  __int128 v12; // q11
  __int128 v13; // q12
  __int128 v14; // q13
  __int128 v15; // q14
  __int128 v16; // q15
  __int128 v17; // q16
  __int128 v18; // q17
  __int128 v19; // q18
  __int128 v20; // q19
  __int128 v21; // q20
  __int128 v22; // q21
  __int128 v23; // q22
  __int128 v24; // q23
  __int128 v25; // q24
  __int128 v26; // q25
  __int128 v27; // q26
  __int128 v28; // q27
  __int128 v29; // q28
  __int128 v30; // q29
  __int128 v31; // q30
  __int128 v32; // q31
  __int64 result; // x0
  int StatusReg; // w2
  int v35; // w1

  result = a1 + 88;
  *(long double *)result = a2;
  *(long double *)(result + 16) = a3;
  *(long double *)(result + 32) = a4;
  *(long double *)(result + 48) = a5;
  *(long double *)(result + 64) = a6;
  *(long double *)(result + 80) = a7;
  *(long double *)(result + 96) = a8;
  *(long double *)(result + 112) = a9;
  *(_OWORD *)(result + 128) = v9;
  *(_OWORD *)(result + 144) = v10;
  *(_OWORD *)(result + 160) = v11;
  *(_OWORD *)(result + 176) = v12;
  *(_OWORD *)(result + 192) = v13;
  *(_OWORD *)(result + 208) = v14;
  *(_OWORD *)(result + 224) = v15;
  *(_OWORD *)(result + 240) = v16;
  *(_OWORD *)(result + 256) = v17;
  *(_OWORD *)(result + 272) = v18;
  *(_OWORD *)(result + 288) = v19;
  *(_OWORD *)(result + 304) = v20;
  *(_OWORD *)(result + 320) = v21;
  *(_OWORD *)(result + 336) = v22;
  *(_OWORD *)(result + 352) = v23;
  *(_OWORD *)(result + 368) = v24;
  *(_OWORD *)(result + 384) = v25;
  *(_OWORD *)(result + 400) = v26;
  *(_OWORD *)(result + 416) = v27;
  *(_OWORD *)(result + 432) = v28;
  *(_OWORD *)(result + 448) = v29;
  *(_OWORD *)(result + 464) = v30;
  *(_OWORD *)(result + 480) = v31;
  *(_OWORD *)(result + 496) = v32;
  StatusReg = _ReadStatusReg(FPCR);
  v35 = _ReadStatusReg(FPSR);
  *(_DWORD *)(result + 512) = StatusReg;
  *(_DWORD *)(result + 516) = v35;
  return result;
}

/* ===== thread_trampoline @ 0x94022998 size 48 ===== */
__int64 thread_trampoline()
{
  unsigned __int64 StatusReg; // x19
  __int64 v6; // x0
  __int64 v7; // x0

  StatusReg = _ReadStatusReg(TPIDR_EL1);
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  __asm { MSR             DAIFClr, #2 }
  v6 = (*(__int64 (__fastcall **)(_QWORD))(StatusReg + 632))(*(_QWORD *)(StatusReg + 640));
  v7 = thread_exit(v6);
  return thread_setup_stack(v7);
}

/* ===== thread_setup_stack @ 0x940229C8 size 88 ===== */
__int64 (*__fastcall thread_setup_stack(_QWORD *a1))()
{
  unsigned __int64 v2; // x19

  v2 = (a1[77] + a1[78]) & 0xFFFFFFFFFFFFFFF0LL;
  memset(v2 - 104, 0, 104);
  *(_QWORD *)(v2 - 104) = thread_trampoline;
  a1[10] = v2 - 104;
  return thread_trampoline;
}

/* ===== arch_context_switch @ 0x94022A20 size 76 ===== */
_QWORD *__fastcall arch_context_switch(
        __int64 a1,
        long double a2,
        long double a3,
        long double a4,
        long double a5,
        long double a6,
        long double a7,
        long double a8,
        long double a9)
{
  unsigned __int64 StatusReg; // x19

  StatusReg = _ReadStatusReg(CPACR_EL1);
  if ( ((StatusReg >> 20) & 3) != 0 )
  {
    save_fpu_state(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    _WriteStatusReg(CPACR_EL1, StatusReg & 0xFFCFFFFF);
    __isb(0xFu);
  }
  __dsb(0xFu);
  return get_stack_frame((_QWORD *)(a1 + 80));
}

/* ===== nullsub_2 @ 0x94022A6C size 4 ===== */
void nullsub_2()
{
  ;
}

/* ===== arch_mmu_unmap_range @ 0x94022A70 size 504 ===== */
__int64 __fastcall arch_mmu_unmap_range(
        __int64 result,
        unsigned __int64 a2,
        unsigned __int64 a3,
        unsigned int a4,
        unsigned int a5,
        __int64 a6,
        unsigned int a7)
{
  unsigned __int64 v8; // x20
  unsigned __int64 v9; // x22
  __int64 v13; // x24
  __int64 v14; // x10
  __int64 v15; // x25
  unsigned __int64 v16; // x23
  unsigned __int64 v17; // x19
  __int64 v22; // t1
  __int64 v23; // x0
  __int64 v24; // [xsp+60h] [xbp+60h]
  __int64 v25; // [xsp+68h] [xbp+68h]
  __int64 v26; // [xsp+78h] [xbp+78h]
  __int64 v27; // [xsp+80h] [xbp+80h]
  __int64 *v28; // [xsp+88h] [xbp+88h]
  unsigned int v29; // [xsp+98h] [xbp+98h]
  int v30; // [xsp+9Ch] [xbp+9Ch]

  v8 = a3;
  v9 = result;
  v13 = a7;
  if ( a3 != 0 )
  {
    v14 = 1LL << a4;
    v30 = 1 << (a5 - 3);
    v15 = (1LL << a4) - 1;
    v29 = 1 << a5;
    do
    {
      v16 = a2 >> a4;
      v17 = v14 - (a2 & v15);
      if ( v17 > v8 )
        v17 = v8;
      result = *(_QWORD *)(a6 + 8 * v16);
      if ( a4 <= a5 || (*(_QWORD *)(a6 + 8 * v16) & 3LL) != 3 )
      {
        if ( result != 0 )
        {
          *(_QWORD *)(a6 + 8 * v16) = 0;
          if ( (_DWORD)v13 == -1 )
          {
            result = v9 >> 12;
            __asm { TLBI            VAAE1IS, X0 }
          }
          else
          {
            result = (v13 << 48) | (v9 >> 12);
            __asm { TLBI            VAE1IS, X0 }
          }
          __isb(0xFu);
        }
        goto LABEL_11;
      }
      v26 = a6;
      v27 = v14;
      v24 = result & 0xFFFFFFFFF000LL;
      v28 = (__int64 *)pmm_virt_to_phys();
      arch_mmu_unmap_range(v9, a2 & v15, v17, 3 - a5 + a4, a5, v28, (unsigned int)v13);
      v14 = v27;
      a6 = v26;
      if ( v17 != v27 && v30 > 0 )
      {
        result = *v28;
        if ( *v28 != 0 )
          goto LABEL_11;
        result = (__int64)v28;
        while ( (__int64 *)result != &v28[v30 - 1] )
        {
          v22 = *(_QWORD *)(result + 8);
          result += 8;
          if ( v22 != 0 )
            goto LABEL_11;
        }
      }
      *(_QWORD *)(v26 + 8 * v16) = 0;
      __dmb(0xAu);
      if ( v29 <= 0xFFF )
      {
        result = heap_free(v28);
        v14 = v27;
        a6 = v26;
      }
      else
      {
        if ( pmm_query_page(v24) == 0 )
        {
          v23 = panic(v25, "bad page table paddr 0x%lx\n", v24);
          return arch_mmu_query(v23);
        }
        result = pmm_free_page_list_init();
        v14 = v27;
        a6 = v26;
      }
LABEL_11:
      v8 -= v17;
      v9 += v17;
      a2 += v17;
    }
    while ( v8 != 0 );
  }
  return result;
}

/* ===== arch_mmu_query @ 0x94022C68 size 424 ===== */
__int64 __fastcall arch_mmu_query(unsigned __int64 a1, _QWORD *a2, int *a3)
{
  __int64 v3; // x30
  __int64 v4; // x20
  unsigned __int64 v7; // x1
  unsigned __int64 v8; // x19
  __int64 v9; // x1
  int v10; // w2
  __int64 v11; // x0
  __int64 v12; // x0
  __int64 v13; // x2
  int v15; // w0
  __int64 v16; // x0

  v4 = v3;
  if ( a1 <= 0xFFFFFFFFDFFFFFFFLL )
  {
    printf("%s:%d: vaddr 0x%lx < base 0x%lx\n", "arch_mmu_query", 104, a1, -536870912);
    return 4294967288LL;
  }
  v7 = (a1 + 0x20000000) >> 21;
  v8 = a1 + 0x20000000 - (v7 << 21);
  v9 = *(_QWORD *)(8 * v7 - 536621056);
  v10 = v9 & 3;
  v11 = v9 & 0xFFFFFFFFF000LL;
  if ( (v9 & 3) != 0 )
  {
    if ( v10 == 1 )
      goto LABEL_11;
    if ( v10 != 3 )
    {
LABEL_7:
      panic(v4, "%s unimplemented\n", "arch_mmu_query");
      return 4294967294LL;
    }
    v12 = pmm_virt_to_phys(v11);
    v13 = (unsigned int)(v8 >> 12);
    v9 = *(_QWORD *)(v12 + 8 * v13);
    if ( (v9 & 3) != 0 )
    {
      if ( (v9 & 3) != 3 )
        goto LABEL_7;
      v8 -= v13 << 12;
      v11 = v9 & 0xFFFFFFFFF000LL;
LABEL_11:
      if ( a2 != nullptr )
        *a2 = v11 + v8;
      if ( a3 != nullptr )
      {
        v15 = v9 & 0x20;
        *a3 = v15;
        switch ( v9 & 0x1C )
        {
          case 4LL:
            *a3 = v15 | 2;
            break;
          case 8LL:
            break;
          case 0LL:
            *a3 = v15 | 1;
            break;
          default:
            goto LABEL_7;
        }
        v16 = (unsigned __int8)v9 & 0xC0;
        switch ( v16 )
        {
          case 128LL:
            *a3 |= 8u;
            break;
          case 192LL:
            *a3 |= 0xCu;
            break;
          case 64LL:
            *a3 |= 4u;
            break;
          default:
            break;
        }
        if ( (v9 & 0x60000000000000LL) == 0x60000000000000LL )
        {
          *a3 |= 0x10u;
          return 0;
        }
      }
      return 0;
    }
  }
  return 4294967294LL;
}

/* ===== arm64_mmu_map_pt @ 0x94022E10 size 772 ===== */
__int64 __fastcall arm64_mmu_map_pt(
        __int64 a1,
        unsigned __int64 a2,
        __int64 a3,
        unsigned __int64 a4,
        __int64 a5,
        unsigned int a6,
        unsigned int a7,
        __int64 a8,
        unsigned int a9)
{
  __int64 v10; // x22
  unsigned __int64 v11; // x28
  __int64 v12; // x27
  unsigned __int64 v13; // x24
  __int64 v14; // x25
  __int64 v15; // x23
  unsigned __int64 v17; // x20
  unsigned __int64 v18; // x5
  __int64 v19; // x4
  __int64 v20; // x0
  __int64 v22; // x0
  __int64 v23; // x7
  unsigned int v24; // w27
  unsigned __int64 v25; // x0
  int v26; // w0
  unsigned __int64 v27; // x5
  int v28; // w0
  unsigned __int64 v29; // [xsp+70h] [xbp+60h]
  unsigned __int64 v30; // [xsp+70h] [xbp+60h]
  unsigned __int64 v31; // [xsp+78h] [xbp+68h]
  __int64 v32; // [xsp+78h] [xbp+68h]
  unsigned __int64 v33; // [xsp+78h] [xbp+68h]
  unsigned int v34; // [xsp+84h] [xbp+74h]
  __int64 v35; // [xsp+90h] [xbp+80h]
  __int64 v36; // [xsp+98h] [xbp+88h]
  unsigned int v40; // [xsp+B8h] [xbp+A8h]
  unsigned int v41; // [xsp+BCh] [xbp+ACh]
  __int64 v44; // [xsp+D8h] [xbp+C8h] BYREF

  if ( ((a3 | a4 | a2) & ((1LL << a7) - 1)) != 0 )
  {
    printf("%s:%d: not page aligned\n", "arm64_mmu_map_pt", 363);
    return 4294967288LL;
  }
  if ( a4 == 0 )
    return 0;
  v40 = 1 << a7;
  v36 = (unsigned int)(1 << a7);
  v10 = 1LL << a6;
  v34 = (unsigned int)(1 << a7) >> 12;
  v11 = a4;
  v12 = a1;
  v13 = a2;
  v14 = a3;
  v41 = a6 + 3 - a7;
  v15 = (1LL << a6) - 1;
  while ( 1 )
  {
    v17 = v10 - (v13 & v15);
    v18 = v13 >> a6;
    if ( v17 > v11 )
      v17 = v11;
    if ( ((v14 | v13) & v15) == 0 && v17 == v10 && a6 <= 0x1E )
      break;
    v22 = *(_QWORD *)(a8 + 8 * v18);
    if ( (v22 & 3) == 1 )
      goto LABEL_21;
    if ( (v22 & 3) == 0 )
      goto LABEL_24;
    if ( (v22 & 3) != 3 )
    {
      panic(v35, "%s unimplemented\n", (const char *)&loc_9404E478);
LABEL_24:
      if ( v40 > 0xFFF )
      {
        v33 = v18;
        v28 = pmm_alloc_pages(v34, a7, &v44, 0);
        v27 = v33;
        if ( v34 != v28 )
        {
LABEL_29:
          v24 = a6;
LABEL_31:
          printf("%s:%d: failed to allocate page table\n", (const char *)&loc_9404E478, 237);
          goto LABEL_22;
        }
      }
      else
      {
        v29 = v18;
        v25 = heap_alloc_aligned(v36, v40);
        v31 = v25;
        if ( v25 == 0 )
          goto LABEL_29;
        v26 = arch_mmu_query(v25, &v44, nullptr);
        v27 = v29;
        if ( v26 != 0 )
        {
          v24 = a6;
          heap_free(v31);
          goto LABEL_31;
        }
      }
      v30 = v27;
      v32 = pmm_virt_to_phys(v44);
      memset(v32, 0, v36);
      __dmb(0xAu);
      v23 = v32;
      *(_QWORD *)(a8 + 8 * v30) = v44 | 3;
      goto LABEL_19;
    }
    v44 = v22 & 0xFFFFFFFFF000LL;
    v23 = pmm_virt_to_phys(v22 & 0xFFFFFFFFF000LL);
LABEL_19:
    if ( v23 == 0 || (unsigned int)arm64_mmu_map_pt(v12, v13 & v15, v14, v17, a5, v41, a7) != 0 )
    {
LABEL_21:
      v24 = a6;
      goto LABEL_22;
    }
LABEL_13:
    v11 -= v17;
    v12 += v17;
    v13 += v17;
    v14 += v17;
    if ( v11 == 0 )
      return 0;
  }
  v19 = *(_QWORD *)(a8 + 8 * v18);
  if ( v19 == 0 )
  {
    v20 = v14 | a5 | 3;
    if ( a7 < a6 )
      v20 = v14 | a5 | 1;
    *(_QWORD *)(a8 + 8 * v18) = v20;
    goto LABEL_13;
  }
  v24 = a6;
  printf("%s:%d: page table entry already in use, index 0x%lx, 0x%llx\n", "arm64_mmu_map_pt", 391, v13 >> a6, v19);
LABEL_22:
  arch_mmu_unmap_range(a1, a2, a4 - v11, v24, a7, a8, a9);
  __dsb(0xFu);
  return 0xFFFFFFFFLL;
}

/* ===== arm64_mmu_map @ 0x94023114 size 204 ===== */
__int64 __fastcall arm64_mmu_map(
        __int64 a1,
        __int64 a2,
        unsigned __int64 a3,
        __int64 a4,
        __int64 a5,
        char a6,
        unsigned int a7,
        unsigned int a8,
        __int64 a9,
        unsigned int a10)
{
  unsigned __int64 v10; // x8
  __int64 result; // x0

  v10 = 1LL << a6;
  if ( a1 - a5 > (1LL << a6) - a3 || v10 < a3 )
  {
    printf(
      "%s:%d: vaddr 0x%lx, size 0x%lx out of range vaddr 0x%lx, size 0x%lx\n",
      "arm64_mmu_map",
      433,
      a1,
      a3,
      a5,
      v10);
    return 4294967288LL;
  }
  else if ( a9 != 0 )
  {
    result = arm64_mmu_map_pt(a1, a1 - a5, a2, a3, a4, a7, a8, a9, a10);
    __dsb(0xFu);
  }
  else
  {
    printf("%s:%d: page table is NULL\n", "arm64_mmu_map", 438);
    return 4294967288LL;
  }
  return result;
}

/* ===== arm64_mmu_unmap @ 0x940231E0 size 176 ===== */
__int64 __fastcall arm64_mmu_unmap(
        __int64 a1,
        unsigned __int64 a2,
        __int64 a3,
        char a4,
        unsigned int a5,
        unsigned int a6,
        __int64 a7,
        unsigned int a8)
{
  unsigned __int64 v8; // x8

  v8 = 1LL << a4;
  if ( a1 - a3 > (1LL << a4) - a2 || v8 < a2 )
  {
    printf(
      "%s:%d: vaddr 0x%lx, size 0x%lx out of range vaddr 0x%lx, size 0x%lx\n",
      (const char *)&loc_9404E4B8,
      460,
      a1,
      a2,
      a3,
      v8);
    return 4294967288LL;
  }
  else if ( a7 != 0 )
  {
    arch_mmu_unmap_range(a1, a1 - a3, a2, a5, a6, a7, a8);
    __dsb(0xFu);
    return 0;
  }
  else
  {
    printf("%s:%d: page table is NULL\n", (const char *)&loc_9404E4B8, 465);
    return 4294967288LL;
  }
}

/* ===== arm64_mmu_map_page @ 0x94023290 size 212 ===== */
__int64 __fastcall arm64_mmu_map_page(__int64 a1, __int64 a2, unsigned int a3, char a4)
{
  unsigned __int64 v4; // x2
  __int64 v5; // x4
  int v6; // w5
  bool v7; // zf
  int v8; // w3
  __int64 v9; // x3

  v4 = (unsigned __int64)a3 << 12;
  if ( (a4 & 3) == 1 )
  {
    v5 = 1024;
    goto LABEL_5;
  }
  if ( (a4 & 3) != 0 )
  {
    if ( (a4 & 3) != 2 )
    {
      v9 = -8;
      return arm64_mmu_map(a1, a2, v4, v9, -536870912, 29, 0x15u, 0xCu, -536621056, 0xFFFFFFFF);
    }
    v5 = 1028;
LABEL_5:
    v6 = a4 & 0xC;
    if ( v6 != 8 )
      goto LABEL_6;
    goto LABEL_17;
  }
  v6 = a4 & 0xC;
  v5 = 1800;
  if ( v6 != 8 )
  {
LABEL_6:
    if ( v6 == 12 )
    {
      v5 |= 0xC0uLL;
    }
    else if ( v6 == 4 )
    {
      v5 |= 0x40uLL;
    }
    goto LABEL_9;
  }
LABEL_17:
  v5 |= 0x80uLL;
LABEL_9:
  v7 = (a4 & 0x12) == 0;
  v8 = a4 & 0x20;
  if ( !v7 )
    v5 |= 0x60000000000000uLL;
  v7 = v8 == 0;
  v9 = v5 | 0x20;
  if ( v7 )
    v9 = v5;
  return arm64_mmu_map(a1, a2, v4, v9, -536870912, 29, 0x15u, 0xCu, -536621056, 0xFFFFFFFF);
}

/* ===== arm64_mmu_unmap_page @ 0x94023364 size 36 ===== */
__int64 __fastcall arm64_mmu_unmap_page(__int64 a1, unsigned int a2)
{
  return arm64_mmu_unmap(a1, (unsigned __int64)a2 << 12, -536870912, 29, 0x15u, 0xCu, -536621056, 0xFFFFFFFF);
}

/* ===== call_init_hooks @ 0x94023388 size 532 ===== */
__int64 __fastcall call_init_hooks(int a1, unsigned int a2, unsigned int a3)
{
  __int64 v3; // x30
  __int64 result; // x0
  unsigned int *v8; // x19
  __int64 v9; // x1
  int v10; // w3
  unsigned int *v11; // x2
  unsigned int v12; // w4
  __int64 v13; // x0
  __int64 v14; // x0
  __int64 v15; // x0

  if ( a2 != 0 )
  {
    result = a2 - 1;
    v8 = nullptr;
    v9 = -536636368;
    while ( 2 )
    {
      v10 = 0;
      v11 = nullptr;
      do
      {
        if ( (unsigned int *)v9 == v8 )
          v10 = 1;
        if ( (a1 & *(_DWORD *)(v9 + 4)) != 0 )
        {
          v12 = *(_DWORD *)v9;
          if ( *(_DWORD *)v9 <= a3 && (unsigned int)result <= v12 && (v11 == nullptr || v12 < *v11) )
          {
            if ( a2 > v12 || (unsigned int)result >= v12 )
            {
              if ( (_DWORD)result == v12 && (unsigned int *)v9 != v8 && v10 != 0 )
              {
                v8 = (unsigned int *)v9;
                goto LABEL_17;
              }
            }
            else
            {
              v11 = (unsigned int *)v9;
            }
          }
        }
        v9 += 24;
      }
      while ( v9 != -536635432 );
      if ( v11 != nullptr )
      {
        result = *v11;
        v8 = v11;
LABEL_17:
        (*((void (__fastcall **)(__int64))v8 + 1))(result);
        v9 = -536636368;
        result = *v8;
        continue;
      }
      break;
    }
  }
  else
  {
    panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/top/init.c", 51, "start_level > 0");
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("top of bootstrap2()\n");
    call_init_hooks(1, 458752, 0x7FFFF);
    platform_init_secondary();
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("initializing platform\n");
    v13 = call_init_hooks(1, 0x80000, 589823);
    nullsub_6(v13);
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("initializing target\n");
    v14 = call_init_hooks(1, 589824, 655359);
    nullsub_8(v14);
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("calling apps_init()\n");
    v15 = call_init_hooks(1, 655360, 720895);
    apps_init(v15);
    call_init_hooks(1, 720896, 0xFFFFFFFFLL);
    return 0;
  }
  return result;
}

/* ===== secondary_bootstrap @ 0x9402359C size 36 ===== */
__int64 secondary_bootstrap()
{
  call_init_hooks(2, 0x70000u, 0xFFFFFFFF);
  return 0;
}

/* ===== bootstrap @ 0x940235C0 size 444 ===== */
void __fastcall __noreturn bootstrap(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 *v4; // x21
  __int64 v5; // x0
  __int64 v6; // x1
  __int64 v7; // x2
  __int64 v8; // x3
  __int64 v9; // x4
  __int64 v10; // x5
  __int64 v11; // x6
  __int64 v12; // x7
  __int64 v13; // x0
  __int64 v14; // x0
  __int64 v15; // x0
  __int64 v16; // x0
  __int64 v17; // x0
  __int64 v18; // x19
  __int64 v19; // x0

  v4 = &qword_9405BFF0[2];
  MEMORY[0xFFFFFFFFE005A038] = a4;
  MEMORY[0xFFFFFFFFE005A020] = a1;
  MEMORY[0xFFFFFFFFE005A028] = a2;
  MEMORY[0xFFFFFFFFE005A030] = a3;
  thread_init_bootstrap();
  v5 = call_init_hooks(1, 1u, 0xFFFFu);
  arch_early_init(v5, v6, v7, v8, v9, v10, v11, v12);
  v13 = call_init_hooks(1, 0x10000u, 0x1FFFFu);
  nullsub_5(v13);
  v14 = call_init_hooks(1, 0x20000u, 0x2FFFFu);
  nullsub_7(v14);
  if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
  {
    log_printf("\nwelcome to lk/MP\n\n");
    if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
    {
      log_printf(
        "boot args 0x%lx 0x%lx 0x%lx 0x%lx\n",
        MEMORY[0xFFFFFFFFE005A020],
        MEMORY[0xFFFFFFFFE005A028],
        MEMORY[0xFFFFFFFFE005A030],
        MEMORY[0xFFFFFFFFE005A038]);
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("calling constructors\n");
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          log_printf("initializing heap\n");
      }
    }
  }
  while ( 1 )
  {
    v15 = call_init_hooks(1, 0x30000u, 0x3FFFFu);
    heap_init(v15);
    v16 = call_init_hooks(1, 0x40000u, 0x5FFFFu);
    kernel_init(v16);
    call_init_hooks(1, 0x60000u, 0x6FFFFu);
    v4 = (__int64 *)v4[464];
    if ( *v4 > 1 )
      log_printf("creating bootstrap completion thread\n");
    v17 = thread_create_simple("bootstrap2", &loc_940234AC, 0, 16, 4096);
    *(_DWORD *)(v17 + 60) = 0;
    v18 = v17;
    thread_cancel();
    v19 = thread_resume_full(v18);
    thread_become_idle(v19);
  }
}

/* ===== secondary_cpu_main @ 0x9402377C size 172 ===== */
__int64 secondary_cpu_main()
{
  unsigned __int64 StatusReg; // x0
  __int64 v1; // x1
  __int64 result; // x0
  __int64 v3; // x0

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v1 = (unsigned __int8)StatusReg | (4 * ((unsigned int)(StatusReg >> 8) & 0xF));
  if ( (_DWORD)v1 == 0 )
  {
    thread_init_idle((unsigned __int8)StatusReg, v1, &dword_94062000);
    thread_resume_full(MEMORY[0x894062020]);
    v3 = MEMORY[0xFFFFFFFFE003CB98];
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      v3 = log_printf("entering scheduler on cpu %d\n", 0);
    thread_enter_idle(v3);
  }
  result = MEMORY[0xFFFFFFFFE003CB98];
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    return log_printf(
             "Invalid secondary cpu num %d, SMP_MAX_CPUS %d, secondary_bootstrap_thread_count %d\n",
             v1,
             4,
             0);
  return result;
}

/* ===== smp_init @ 0x94023828 size 292 ===== */
// write access to const memory has been detected, the output may be wrong!
int *__fastcall smp_init(unsigned int a1)
{
  unsigned int v1; // w23
  __int64 v2; // x21
  unsigned int v3; // w19
  __int64 v4; // x20
  __int64 v5; // x1
  unsigned int v6; // w22
  __int64 v7; // x0
  __int64 v8; // x21

  v1 = a1;
  if ( a1 <= 3 )
  {
    if ( a1 == 0 )
      goto LABEL_11;
    v2 = MEMORY[0xFFFFFFFFE003CB98];
  }
  else
  {
    v2 = MEMORY[0xFFFFFFFFE003CB98];
    if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    {
      log_printf("Invalid secondary_cpu_count %d, SMP_MAX_CPUS %d\n", a1, 4);
      v2 = MEMORY[0xFFFFFFFFE003CB98];
    }
    v1 = 3;
  }
  v3 = 1;
  v4 = 0;
  v5 = 1;
  v6 = 1;
  if ( v2 > 1 )
LABEL_6:
    log_printf("creating bootstrap completion thread for cpu %d\n", v5);
  while ( 1 )
  {
    v7 = thread_create_simple(&loc_9404E700, secondary_bootstrap, 0, 16, 4096);
    *(_DWORD *)(v7 + 60) = v3;
    v8 = v7;
    ++v3;
    thread_cancel();
    qword_94062028[v4++] = v8;
    if ( v1 <= v6 )
      break;
    v5 = v3;
    v6 = v3;
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      goto LABEL_6;
  }
LABEL_11:
  dword_94062040 = v1;
  return &dword_94062000;
}

/* ===== thread_entry_wrapper @ 0x9402394C size 32 ===== */
__int64 __fastcall thread_entry_wrapper(__int64 a1)
{
  (*(void (__fastcall **)(__int64, _QWORD))(a1 + 16))(a1, 0);
  return 0;
}

/* ===== apps_init @ 0x9402396C size 236 ===== */
__int64 apps_init()
{
  return -536621840;
}

/* ===== gic_dist_init @ 0x94023A58 size 40 ===== */
__int64 gic_dist_init()
{
  MEMORY[0xFFFFFFFFFFFF0000] = 11;
  MEMORY[0xFFFFFFFFFFFF1080] = -1;
  MEMORY[0xFFFFFFFFFFFF0004] = 255;
  return -65532;
}

/* ===== gic_set_irq_target @ 0x94023A80 size 332 ===== */
__int64 __fastcall gic_set_irq_target(char a1, unsigned __int8 a2, int a3, unsigned __int8 a4)
{
  int v4; // w22
  int v6; // w23
  unsigned __int8 v7; // w20
  unsigned int v8; // w19
  int v9; // w20
  __int64 v10; // x1
  int v11; // w11
  unsigned __int64 v12; // x7
  int v13; // w10
  int v14; // w0
  unsigned int v15; // w5
  unsigned int v16; // w14
  char v17; // w4
  int v18; // w8
  int v19; // w4
  char v20; // w4
  unsigned int v21; // w5
  __int64 v22; // x4
  int v24; // w4

  v4 = a2;
  v6 = a4;
  v7 = MEMORY[0xFFFFFFFFFFFF1004];
  spin_lock((unsigned __int64 *)&qword_94065E08);
  v8 = 0;
  v9 = v7 >> 5;
  v10 = 0;
  v11 = (unsigned __int8)(1 << a1);
  do
  {
    v12 = qword_94065E18[v10];
    if ( v12 != 0 )
    {
      v13 = 1 * v10;
      do
      {
        while ( 1 )
        {
          while ( 1 )
          {
            v14 = __clz(__rbit64(v12));
            v15 = v14 + v13;
            v16 = (unsigned int)(v14 + v13) >> 2;
            v17 = 8 * ((v14 + v13) & 3);
            v18 = v11 << v17;
            v19 = (-v4 << v17) & (v11 << v17);
            v12 &= ~(1LL << v14);
            if ( v14 + v13 == a3 )
              v8 = 1;
            if ( v9 == 0 )
              break;
            v24 = *((_DWORD *)qword_9405A178 + v16) & ~v18 | v19;
            *((_DWORD *)qword_9405A178 + v16) = v24;
            *(_DWORD *)(4LL * ((v16 + 1536) & 0x3FFFFFFF) - 0x10000) = v24;
            if ( v6 != 0 )
              break;
            if ( v12 == 0 )
              goto LABEL_9;
          }
          v20 = v15 & 0x1F;
          v21 = v15 >> 5;
          v22 = 1LL << v20;
          if ( v4 == 0 )
            break;
          *(_DWORD *)(4LL * ((v21 + 1088) & 0xFFFFFFF) - 0x10000) = v22;
          if ( v12 == 0 )
            goto LABEL_9;
        }
        *(_DWORD *)(4LL * ((v21 + 1120) & 0xFFFFFFF) - 0x10000) = v22;
      }
      while ( v12 != 0 );
    }
LABEL_9:
    ++v10;
  }
  while ( v10 != 16 );
  spin_unlock((unsigned __int64 *)&qword_94065E08);
  return v8;
}

/* ===== gic_init_cpu @ 0x94023BCC size 104 ===== */
__int64 gic_init_cpu()
{
  __int64 v0; // x30
  unsigned __int64 StatusReg; // x1
  __int64 v3; // x0

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) <= 7 )
    return gic_set_irq_target((unsigned __int8)StatusReg | (unsigned __int8)(4 * (BYTE1(StatusReg) & 0xF)), 0, -1, 0);
  v3 = panic(v0, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/dev/interrupt/arm_gic/arm_gic.c", 573, "cpu < 8");
  return register_int_handler(v3);
}

/* ===== register_int_handler @ 0x94023C34 size 360 ===== */
unsigned __int64 *__fastcall register_int_handler(unsigned int a1, __int64 a2, __int64 a3)
{
  __int64 v3; // x30
  unsigned __int64 StatusReg; // x20
  char v6; // w21
  __int64 v12; // x1
  __int64 v13; // x2
  __int64 *v14; // x19
  unsigned __int64 *result; // x0
  __int64 *v18; // x19
  __int64 v20; // x0
  __int64 v21; // [xsp+40h] [xbp+40h]
  __int64 v22; // [xsp+48h] [xbp+48h]

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( a1 > 0x3FB )
  {
    v20 = panic(v3, "register_int_handler: vector out of range %d\n", a1);
    return (unsigned __int64 *)gic_dist_enable(v20);
  }
  v6 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    v21 = a3;
    v22 = a2;
    if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
    {
LABEL_6:
      v6 |= 2u;
      __asm { MSR             DAIFSet, #1 }
      spin_lock((unsigned __int64 *)&qword_94065E08);
      v12 = v22;
      v13 = v21;
      goto LABEL_7;
    }
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    v6 = 1;
    v21 = a3;
    v22 = a2;
    if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
      goto LABEL_6;
  }
  spin_lock((unsigned __int64 *)&qword_94065E08);
  v12 = v22;
  v13 = v21;
LABEL_7:
  if ( a1 > 0x1F )
  {
    v18 = &qword_94062048[2 * a1 - 64];
    *v18 = v12;
    v18[1] = v13;
    result = spin_unlock((unsigned __int64 *)&qword_94065E08);
    if ( (v6 & 2) == 0 )
      goto LABEL_9;
  }
  else
  {
    v14 = &qword_94065E98[8 * a1 + 2 * ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF)))];
    *v14 = v12;
    v14[1] = v13;
    result = spin_unlock((unsigned __int64 *)&qword_94065E08);
    if ( (v6 & 2) == 0 )
      goto LABEL_9;
  }
  __asm { MSR             DAIFClr, #1 }
LABEL_9:
  if ( (v6 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== gic_dist_enable @ 0x94023D9C size 236 ===== */
__int64 gic_dist_enable()
{
  int v0; // w2
  int v1; // w0
  int v2; // w0
  int i; // w1
  int v4; // w2
  int v5; // w0
  int v6; // w1
  unsigned int v7; // w2
  int v8; // w0

  v0 = 0;
  do
  {
    v1 = v0 >> 5;
    v0 += 32;
    v2 = 4 * (v1 + 1120);
    *(_DWORD *)(v2 - 0x10000LL) = -1;
    *(_DWORD *)(v2 + 256 - 0x10000LL) = -1;
  }
  while ( v0 != 1024 );
  if ( MEMORY[0xFFFFFFFFFFFF1004] >> 5 != 0 )
  {
    for ( i = 32; i != 1020; i += 4 )
    {
      v4 = i >> 2;
      v5 = (i >> 2) + 1536;
      *(_DWORD *)(4 * v5 - 0x10000LL) = *((_DWORD *)qword_9405A178 + v4);
    }
  }
  v6 = 32;
  MEMORY[0xFFFFFFFFFFFF1000] = 3;
  do
  {
    v7 = v6 >> 5;
    v8 = (v6 >> 5) + 1056;
    v6 += 32;
    *(_DWORD *)(4LL * (v8 & 0x3FFFFFFF) - 0x10000) = *((_DWORD *)qword_9405A0D8 + v7);
  }
  while ( v6 != 1024 );
  MEMORY[0xFFFFFFFFFFFF0000] = 11;
  MEMORY[0xFFFFFFFFFFFF1080] = -1;
  MEMORY[0xFFFFFFFFFFFF0004] = 255;
  return -65532;
}

/* ===== gic_resume_cpu @ 0x94023E88 size 300 ===== */
__int64 gic_resume_cpu()
{
  __int64 v0; // x30
  __int64 v1; // x21
  char v2; // w19
  unsigned __int8 v9; // w22
  unsigned __int64 StatusReg; // x1
  __int64 v14; // x0

  v1 = v0;
  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
  }
  spin_lock((unsigned __int64 *)&qword_94065E08);
  if ( (MEMORY[0xFFFFFFFFFFFF1000] & 1) != 0 )
  {
    v9 = 0;
    MEMORY[0xFFFFFFFFFFFF0000] = 11;
    MEMORY[0xFFFFFFFFFFFF1080] = -1;
    MEMORY[0xFFFFFFFFFFFF0004] = 255;
  }
  else
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("%s: distibutor is off, calling arm_gic_init instead\n", "arm_gic_resume_cpu");
    v9 = 1;
    gic_dist_enable();
  }
  spin_unlock((unsigned __int64 *)&qword_94065E08);
  if ( (v2 & 2) != 0 )
    __asm { MSR             DAIFClr, #1 }
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) <= 7 )
    return gic_set_irq_target((unsigned __int8)StatusReg | (unsigned __int8)(4 * (BYTE1(StatusReg) & 0xF)), 1u, -1, v9);
  v14 = panic(
          v1,
          "ASSERT FAILED at (%s:%d): %s\n",
          "external/lk/dev/interrupt/arm_gic/arm_gic.c",
          573,
          "cpu < 8");
  return gic_enable_irq(v14);
}

/* ===== gic_enable_irq @ 0x94023FB4 size 76 ===== */
__int64 __fastcall gic_enable_irq(unsigned int a1)
{
  __int64 v1; // x2
  _DWORD *v2; // x1

  if ( a1 > 0x3FB )
    return 4294967288LL;
  v1 = 1LL << (a1 & 0x1F);
  v2 = (_DWORD *)(4LL * ((a1 >> 5) + 1088) - 0x10000);
  *v2 = v1;
  return 0;
}

/* ===== platform_irq @ 0x94024000 size 484 ===== */
__int64 platform_irq()
{
  char v0; // w21
  unsigned int v1; // w19
  unsigned __int64 StatusReg; // x0
  int v3; // w20
  __int64 *v4; // x0
  char v5; // w23
  char v7; // w21
  int v8; // w2
  int *v9; // x1
  unsigned int v10; // w3
  unsigned int v11; // w22
  __int64 *v14; // x20
  __int64 result; // x0

  v0 = MEMORY[0xFFFFFFFFFFFF0028];
  v1 = MEMORY[0xFFFFFFFFFFFF0028] & 0x3FF;
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( v1 > 0x3FB )
    return sm_handle_irq();
  v3 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  v4 = v1 <= 0x1F
     ? &qword_94065E98[8 * (v1 & 0x3FF) + 2 * (unsigned __int8)(StatusReg | (4 * (BYTE1(StatusReg) & 0xF)))]
     : &qword_94062048[2 * v1 - 64];
  if ( *v4 == 0 )
    return sm_handle_irq();
  v5 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v5 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    v5 |= 2u;
    __asm { MSR             DAIFSet, #1 }
  }
  v7 = 8 * (v0 & 3);
  spin_lock((unsigned __int64 *)&qword_94065E08);
  v8 = ~(255 << v7);
  v9 = (int *)(4LL * (((unsigned __int16)(v1 >> 2) + 1280) & 0xFFF) - 0x10000);
  v10 = *v9;
  *v9 &= v8;
  __dsb(0xFu);
  v11 = MEMORY[0xFFFFFFFFFFFF0020] & 0x3FF;
  *v9 = ((unsigned __int8)(v10 >> v7) << v7) | *v9 & v8;
  spin_unlock((unsigned __int64 *)&qword_94065E08);
  if ( (v5 & 2) != 0 )
    __asm { MSR             DAIFClr, #1 }
  if ( (v5 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  if ( v11 <= 0x3FB
    && (v1 <= 0x1F
      ? (v14 = &qword_94065E98[8 * (v1 & 0x3FF) + 2 * (unsigned __int8)v3])
      : (v14 = &qword_94062048[2 * v1 - 64]),
        *v14 != 0) )
  {
    result = ((__int64 (__fastcall *)(__int64))*v14)(v14[1]);
    MEMORY[0xFFFFFFFFFFFF0024] = v11;
  }
  else
  {
    printf("%s:%d: unexpected irq %d != %d may get lost\n", "platform_irq", 450, v11, v1);
    MEMORY[0xFFFFFFFFFFFF0024] = v11;
    return 0;
  }
  return result;
}

/* ===== platform_fiq @ 0x940241E4 size 4 ===== */
// attributes: thunk
__int64 platform_fiq()
{
  return sm_handle_fiq();
}

/* ===== platform_get_irq @ 0x940241E8 size 308 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall platform_get_irq(__int64 a1)
{
  char v2; // w20
  unsigned int v9; // w5
  unsigned int v10; // w4
  unsigned int v11; // w0
  unsigned __int64 StatusReg; // x2
  __int64 *v13; // x1
  __int64 *v14; // x2
  __int64 v15; // x19

  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
  }
  spin_lock((unsigned __int64 *)&qword_94065E08);
  v9 = *(_DWORD *)(a1 + 8) != 0;
  byte_94065E10 = 1;
  if ( v9 != 0 )
    v10 = 32;
  else
    v10 = 1020;
  v11 = *(_DWORD *)(a1 + 4);
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( (v11 <= 0x1F) > v9 )
    v11 = 32;
  if ( v10 <= v11 )
  {
LABEL_22:
    v15 = -10;
    spin_unlock((unsigned __int64 *)&qword_94065E08);
    if ( (v2 & 2) == 0 )
      goto LABEL_19;
    goto LABEL_23;
  }
  v13 = &qword_94065E98[8 * v11 + 2 * ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF)))];
  while ( 1 )
  {
    v14 = v13;
    if ( v11 > 0x1F )
      v14 = &qword_94062048[2 * v11 - 64];
    v13 += 8;
    if ( *v14 != 0 )
      break;
    if ( ++v11 == v10 )
      goto LABEL_22;
  }
  v15 = (int)v11;
  spin_unlock((unsigned __int64 *)&qword_94065E08);
  if ( (v2 & 2) != 0 )
LABEL_23:
    __asm { MSR             DAIFClr, #1 }
LABEL_19:
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v15;
}

/* ===== smc_intc_request_fiq @ 0x9402431C size 484 ===== */
__int64 __fastcall smc_intc_request_fiq(__int64 a1)
{
  unsigned int v1; // w22
  BOOL v2; // w23
  char v3; // w20
  signed int v10; // w0
  __int64 v11; // x6
  int v12; // w2
  __int64 v13; // x2
  int v14; // w1
  int v15; // w4
  int v16; // w1
  __int64 v17; // x0
  __int64 v21; // x4

  v1 = *(_DWORD *)(a1 + 4);
  v2 = *(_DWORD *)(a1 + 8) != 0;
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("%s: fiq %d, enable %d\n", "smc_intc_request_fiq", v1, v2);
  v3 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v3 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    v3 |= 2u;
    __asm { MSR             DAIFSet, #1 }
  }
  spin_lock((unsigned __int64 *)&qword_94065E08);
  v10 = v1 >> 5;
  v11 = 1LL << (v1 & 0x1F);
  if ( v1 <= 0x3FB )
  {
    v12 = *((_DWORD *)qword_9405A0D8 + v10) & ~(_DWORD)v11;
    *((_DWORD *)qword_9405A0D8 + v10) = v12;
    *(_DWORD *)(4LL * ((v1 >> 5) + 1056) - 0x10000) = v12;
  }
  v13 = 4 * ((v1 >> 2) + 1536);
  v14 = 255 << (8 * (v1 & 3));
  v15 = ~v14;
  v16 = ~v14 & *((_DWORD *)qword_9405A178 + (v1 >> 2)) | (-1 << (8 * (v1 & 3))) & v14;
  *(_DWORD *)(v13 - 0x10000) = v16;
  *((_DWORD *)qword_9405A178 + (v1 >> 2)) = v16;
  *(_DWORD *)((unsigned int)(v13 - 1024) - 0x10000LL) &= v15;
  if ( v2 )
  {
    v17 = qword_94065E18[v1 >> 6];
    *(_DWORD *)(4LL * ((v1 >> 5) + 1088) - 0x10000) = v11;
    qword_94065E18[v1 >> 6] = v17 | (1LL << v1);
  }
  else
  {
    v21 = qword_94065E18[v1 >> 6];
    *(_DWORD *)(4LL * ((v1 >> 5) + 1120) - 0x10000) = v11;
    qword_94065E18[v1 >> 6] = v21 & ~(1LL << v1);
  }
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("%s: fiq %d, enable %d done\n", "smc_intc_request_fiq", v1, v2);
  spin_unlock((unsigned __int64 *)&qword_94065E08);
  if ( (v3 & 2) != 0 )
    __asm { MSR             DAIFClr, #1 }
  if ( (v3 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return 0;
}

/* ===== sm_intc_fiq_enter @ 0x94024500 size 316 ===== */
__int64 sm_intc_fiq_enter()
{
  __int64 v0; // x30
  unsigned __int64 StatusReg; // x1
  unsigned int v2; // w19
  unsigned int v3; // w20
  char v4; // w0
  int v5; // w2
  unsigned int v6; // w21

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v2 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  v3 = MEMORY[0xFFFFFFFFFFFF000C] & 0x3FF;
  if ( v2 > 7 )
  {
    panic(v0, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/dev/interrupt/arm_gic/arm_gic.c", 584, "cpu < 8");
  }
  else if ( v3 <= 0x3FB )
  {
    v4 = gic_set_irq_target((unsigned __int8)StatusReg | (unsigned __int8)(4 * (BYTE1(StatusReg) & 0xF)), 0, v3, 0);
    MEMORY[0xFFFFFFFFFFFF0010] = v3;
    v5 = *((_DWORD *)qword_9405A158 + v2);
    if ( v5 != 1023 )
    {
      v6 = -6;
      if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
        log_printf("more than one fiq active: cpu %d, old %d, new %d\n", v2, v5, v3);
      return v6;
    }
    if ( v4 == 0 )
    {
      v6 = -3;
      if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
        log_printf("got disabled fiq: cpu %d, new %d\n", v2, v3);
      return v6;
    }
    *((_DWORD *)qword_9405A158 + v2) = v3;
    return 0;
  }
  return (unsigned int)-4;
}

/* ===== sm_intc_fiq_exit @ 0x9402463C size 212 ===== */
__int64 sm_intc_fiq_exit()
{
  __int64 v0; // x30
  unsigned __int64 StatusReg; // x1
  unsigned int v2; // w19
  int v3; // w2
  __int64 result; // x0

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v2 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  if ( v2 > 7 )
  {
    panic(v0, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/dev/interrupt/arm_gic/arm_gic.c", 615, "cpu < 8");
    _WriteStatusReg(CNTPS_TVAL_EL1, 0);
    __isb(0xFu);
    return 0;
  }
  else
  {
    v3 = *((_DWORD *)qword_9405A158 + v2);
    if ( v3 == 1023 )
    {
      result = MEMORY[0xFFFFFFFFE003CB98];
      if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
        return log_printf("%s: no fiq active, cpu %d\n", "sm_intc_fiq_exit", v2);
    }
    else
    {
      gic_set_irq_target(StatusReg | (4 * (BYTE1(StatusReg) & 0xF)), 1u, v3, 0);
      result = 1023;
      *((_DWORD *)qword_9405A158 + v2) = 1023;
    }
  }
  return result;
}

/* ===== test_time_conversion_ticks @ 0x94024710 size 268 ===== */
unsigned __int64 __fastcall test_time_conversion_ticks(unsigned int a1, unsigned int a2, unsigned int a3)
{
  unsigned __int64 v3; // x3
  unsigned __int64 v4; // x3
  unsigned __int64 result; // x0
  unsigned __int64 v6; // x4
  unsigned int v7; // w4
  __int64 v8; // x3

  v3 = a1 * (unsigned __int64)a2 / 0x3E8;
  if ( a1 * (unsigned __int64)a3 > 0xFFFFFFFF )
    v4 = v3
       + ((unsigned __int64)((((unsigned __int64)a1 << 29) * (unsigned __int128)0x20C49BA5E353F7CFuLL) >> 64) >> 4) * a3;
  else
    v4 = v3
       + ((unsigned __int64)((((unsigned __int64)(a1 * a3) << 29) * (unsigned __int128)0x20C49BA5E353F7CFuLL) >> 64) >> 4);
  result = (a1 + 999) / a1;
  v6 = (unsigned int)v4 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A054]
     + HIDWORD(v4) * MEMORY[0xFFFFFFFFE005A058]
     + (((unsigned int)v4 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A050]) << 32)
     + ((HIDWORD(v4) * MEMORY[0xFFFFFFFFE005A054]) << 32)
     + (((unsigned int)v4 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A058]) >> 32);
  v7 = HIDWORD(v6) + ((unsigned int)v6 >> 31);
  if ( a2 != (unsigned __int64)v7 )
  {
    v8 = (int)abs32(v7 - a2);
    if ( result < (int)v8 )
      return printf("%s:%d: FAIL, off by %llu\n", "test_time_conversion_check_result", 288, v8);
  }
  return result;
}

/* ===== timer_irq_init @ 0x9402481C size 52 ===== */
__int64 timer_irq_init()
{
  register_int_handler(0, (__int64)arm_generic_timer_irq, 0);
  return gic_enable_irq(0);
}

/* ===== test_time_conversion_ns @ 0x94024850 size 184 ===== */
__int64 __fastcall test_time_conversion_ns(__int64 result, __int64 a2)
{
  unsigned __int64 v2; // x2
  __int64 v3; // x3
  unsigned __int64 v4; // x5
  unsigned __int64 v5; // x7
  unsigned __int64 v6; // x8
  unsigned __int64 v7; // x1
  __int64 v8; // x3
  unsigned __int64 v9; // x2
  unsigned __int64 v10; // x2
  unsigned __int64 v11; // x6
  __int64 v12; // x3
  unsigned __int64 v13; // x3

  v2 = (unsigned int)result * a2;
  v3 = 15625 * a2;
  v4 = HIDWORD(v2) * MEMORY[0xFFFFFFFFE005A040];
  v5 = (unsigned int)v2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A044];
  v6 = (unsigned int)v2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A040] + HIDWORD(v2) * MEMORY[0xFFFFFFFFE005A044];
  v7 = HIDWORD(v2) * MEMORY[0xFFFFFFFFE005A048];
  v8 = v3 << 6;
  v9 = (unsigned int)v7
     + (unsigned __int64)(unsigned int)v5
     + (((unsigned int)v2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A048]) >> 32);
  v10 = ((v9 & 0x80000000) != 0LL) + v6 + (v4 << 32) + HIDWORD(v5) + HIDWORD(v7) + HIDWORD(v9);
  v11 = ((int)result + 999999) / (unsigned int)result;
  if ( v8 != v10 )
  {
    v12 = v10 - v8;
    result = v12 ^ (v12 >> 63);
    v13 = abs64(v12);
    if ( v11 < v13 )
      return printf("%s:%d: FAIL, off by %llu\n", "test_time_conversion_check_result", 288, v13);
  }
  return result;
}

/* ===== test_time_conversion_us @ 0x94024908 size 148 ===== */
__int64 __fastcall test_time_conversion_us(unsigned int a1, unsigned int a2)
{
  unsigned __int64 v2; // x3
  unsigned __int64 v3; // x2
  unsigned __int64 v4; // x0
  unsigned __int64 v5; // x1
  __int64 result; // x0
  unsigned __int64 v7; // x1
  unsigned __int64 v8; // x3
  __int64 v9; // x3
  __int64 v10; // x3

  v2 = (a2 * (unsigned __int64)a1 + 500) >> 3;
  v3 = a2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A064];
  v4 = ((a2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A068]) >> 32) + (unsigned int)v3;
  v5 = HIDWORD(v3) + a2 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A060] + HIDWORD(v4);
  result = (v4 & 0x80000000) != 0LL;
  v7 = result + v5;
  v8 = (unsigned __int64)((v2 * (unsigned __int128)0x20C49BA5E353F7CFuLL) >> 64) >> 4;
  if ( v8 != v7 )
  {
    v9 = v7 - v8;
    result = v9 ^ (v9 >> 63);
    v10 = abs64(v9);
    if ( v10 > 1 )
      return printf("%s:%d: FAIL, off by %llu\n", "test_time_conversion_check_result", 288, v10);
  }
  return result;
}

/* ===== arch_counter_get @ 0x9402499C size 8 ===== */
unsigned __int64 arch_counter_get()
{
  return _ReadStatusReg(CNTPCT_EL0);
}

/* ===== arm_generic_timer_set @ 0x940249A4 size 208 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall arm_generic_timer_set(void *a1, __int64 a2, unsigned int a3)
{
  __int64 v3; // x30
  unsigned __int64 v4; // x3
  unsigned __int64 v5; // x19
  unsigned __int64 v6; // x19
  __int64 v8; // x0

  v4 = a3 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A064];
  v5 = ((a3 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A068]) >> 32) + (unsigned int)v4;
  v6 = ((v5 & 0x80000000) != 0LL) + HIDWORD(v4) + a3 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A060] + HIDWORD(v5);
  if ( a2 != 0 )
  {
    v8 = panic(
           v3,
           "ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/dev/timer/arm_generic/arm_generic_timer.c",
           244,
           "arg == NULL");
    return arm_generic_timer_cancel(v8);
  }
  else
  {
    off_94066698 = a1;
    if ( v6 > 0x7FFFFFFF )
      _WriteStatusReg(CNTPS_CVAL_EL1, arch_counter_get() + v6);
    else
      _WriteStatusReg(CNTPS_TVAL_EL1, v6);
    __isb(0xFu);
    _WriteStatusReg(CNTPS_CTL_EL1, 1u);
    __isb(0xFu);
    return 0;
  }
}

/* ===== arm_generic_timer_cancel @ 0x94024A74 size 16 ===== */
__int64 arm_generic_timer_cancel()
{
  _WriteStatusReg(CNTPS_CTL_EL1, 0);
  __isb(0xFu);
  return 0;
}

/* ===== arch_time_now @ 0x94024A84 size 108 ===== */
unsigned __int64 arch_time_now()
{
  unsigned __int64 v0; // x0
  unsigned __int64 v1; // x4
  unsigned __int64 v2; // x2
  unsigned __int64 v3; // x1

  v0 = arch_counter_get();
  v1 = (unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A044];
  v2 = HIDWORD(v0) * MEMORY[0xFFFFFFFFE005A048];
  v3 = (unsigned int)v2
     + (unsigned __int64)(unsigned int)v1
     + (((unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A048]) >> 32);
  return ((v3 & 0x80000000) != 0LL)
       + (unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A040]
       + HIDWORD(v0) * MEMORY[0xFFFFFFFFE005A044]
       + ((HIDWORD(v0) * MEMORY[0xFFFFFFFFE005A040]) << 32)
       + HIDWORD(v1)
       + HIDWORD(v2)
       + HIDWORD(v3);
}

/* ===== arch_time_now_ms @ 0x94024AF0 size 88 ===== */
__int64 arch_time_now_ms()
{
  unsigned __int64 v0; // x0
  unsigned __int64 v1; // x0

  v0 = arch_counter_get();
  v1 = (unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A054]
     + HIDWORD(v0) * MEMORY[0xFFFFFFFFE005A058]
     + (((unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A050]) << 32)
     + ((HIDWORD(v0) * MEMORY[0xFFFFFFFFE005A054]) << 32)
     + (((unsigned int)v0 * (unsigned __int64)MEMORY[0xFFFFFFFFE005A058]) >> 32);
  return HIDWORD(v1) + ((unsigned int)v1 >> 31);
}

/* ===== arm_generic_timer_irq @ 0x94024B48 size 84 ===== */
__int64 arm_generic_timer_irq()
{
  _WriteStatusReg(CNTPS_CTL_EL1, 0);
  __isb(0xFu);
  return 0;
}

/* ===== arm_generic_timer_init @ 0x94024B9C size 608 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 *__fastcall arm_generic_timer_init(unsigned int a1, unsigned int a2)
{
  unsigned int StatusReg; // w19
  unsigned __int64 v4; // x6

  StatusReg = a2;
  if ( a2 == 0 )
  {
    StatusReg = _ReadStatusReg(CNTFRQ_EL0);
    if ( StatusReg == 0 )
      return (__int64 *)printf(
                          "%s:%d: Failed to initialize timer, frequency is 0\n",
                          "arm_generic_timer_init",
                          368);
  }
  v4 = ((((unsigned __int64)StatusReg << 29) & 0x1FFFFFFFFFFFFFFFLL) * (unsigned __int128)0x20C49BA5E353F7CFuLL) >> 64;
  MEMORY[0xFFFFFFFFE005A060] = v4 >> 36;
  MEMORY[0xFFFFFFFFE005A068] = (unsigned __int64)(((((((unsigned __int64)StatusReg << 32) - 1000 * (v4 >> 4)) << 29)
                                                  & 0x1FFFFFFFFFFFFFFFLL)
                                                 * (unsigned __int128)0x20C49BA5E353F7CFuLL) >> 64) >> 4;
  MEMORY[0xFFFFFFFFE005A064] = v4 >> 4;
  MEMORY[0xFFFFFFFFE005A050] = (0x3E800000000uLL / StatusReg) >> 32;
  MEMORY[0xFFFFFFFFE005A054] = 0x3E800000000uLL / StatusReg;
  MEMORY[0xFFFFFFFFE005A040] = (0xF424000000000uLL / StatusReg) >> 32;
  MEMORY[0xFFFFFFFFE005A044] = 0xF424000000000uLL / StatusReg;
  MEMORY[0xFFFFFFFFE005A058] = ((0x3E800000000uLL % StatusReg) << 32) / StatusReg;
  MEMORY[0xFFFFFFFFE005A048] = ((0xF424000000000uLL % StatusReg) << 32) / StatusReg;
  test_time_conversion_us(StatusReg, 0);
  test_time_conversion_us(StatusReg, 1u);
  test_time_conversion_us(StatusReg, 0x7FFFFFFFu);
  test_time_conversion_us(StatusReg, 0x80000000);
  test_time_conversion_us(StatusReg, 0xFFFFFFFF);
  test_time_conversion_ticks(StatusReg, 0, 0);
  test_time_conversion_ticks(StatusReg, 0x7FFFFFFFu, 0);
  test_time_conversion_ticks(StatusReg, 0x80000000, 0);
  test_time_conversion_ticks(StatusReg, 0xFFFFFFFF, 0);
  test_time_conversion_ticks(StatusReg, 0, 1u);
  test_time_conversion_ticks(StatusReg, 0, 7u);
  test_time_conversion_ticks(StatusReg, 0, 0x46u);
  test_time_conversion_ticks(StatusReg, 0, 0x2BCu);
  test_time_conversion_ns(StatusReg, 0);
  test_time_conversion_ns(StatusReg, 1);
  test_time_conversion_ns(StatusReg, 86400);
  test_time_conversion_ns(StatusReg, 31536000);
  test_time_conversion_ns(StatusReg, 315532800);
  test_time_conversion_ns(StatusReg, 3153772800LL);
  register_int_handler(a1, (__int64)arm_generic_timer_irq, 0);
  gic_enable_irq(a1);
  dword_940666A0 = a1;
  return &qword_94065E98[45];
}

/* ===== event_init @ 0x94024DFC size 52 ===== */
__int64 __fastcall event_init(__int64 result, char a2, int a3)
{
  *(_DWORD *)result = 1702260340;
  *(_BYTE *)(result + 4) = a2;
  *(_DWORD *)(result + 8) = a3;
  *(_DWORD *)(result + 16) = 2002872692;
  *(_QWORD *)(result + 24) = result + 24;
  *(_QWORD *)(result + 32) = result + 24;
  *(_DWORD *)(result + 40) = 0;
  return result;
}

/* ===== event_destroy @ 0x94024E30 size 204 ===== */
unsigned __int64 *__fastcall event_destroy(__int64 a1)
{
  __int64 v1; // x30
  unsigned __int64 *result; // x0
  __int64 v10; // x0

  if ( *(_DWORD *)a1 == 1702260340 )
  {
    if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
    {
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      *(_DWORD *)a1 = 0;
      *(_BYTE *)(a1 + 4) = 0;
      *(_DWORD *)(a1 + 8) = 0;
      wait_queue_destroy(a1 + 16, 1);
      return spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    }
    else
    {
      __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      *(_DWORD *)a1 = 0;
      *(_BYTE *)(a1 + 4) = 0;
      *(_DWORD *)(a1 + 8) = 0;
      wait_queue_destroy(a1 + 16, 1);
      result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
    }
  }
  else
  {
    v10 = panic(
            v1,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            "external/lk/kernel/event.c",
            72,
            "e->magic == EVENT_MAGIC");
    return (unsigned __int64 *)event_wait_timeout(v10);
  }
  return result;
}

/* ===== event_wait_timeout @ 0x94024EFC size 224 ===== */
__int64 __fastcall event_wait_timeout(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  int v4; // w22
  __int64 v5; // x1
  unsigned int v6; // w21
  __int64 v14; // x0

  if ( *(_DWORD *)a1 != 1702260340 )
  {
    v14 = panic(
            v2,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            "external/lk/kernel/event.c",
            103,
            "e->magic == EVENT_MAGIC");
    return event_signal(v14);
  }
  v4 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v5 = a2;
    if ( *(_BYTE *)(a1 + 4) != 0 )
      goto LABEL_4;
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    v4 = 1;
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v5 = a2;
    if ( *(_BYTE *)(a1 + 4) != 0 )
    {
LABEL_4:
      v6 = 0;
      if ( (*(_DWORD *)(a1 + 8) & 1) != 0 )
        *(_BYTE *)(a1 + 4) = 0;
      goto LABEL_6;
    }
  }
  v6 = wait_queue_block(a1 + 16, v5);
LABEL_6:
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( v4 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v6;
}

/* ===== event_signal @ 0x94024FDC size 288 ===== */
__int64 __fastcall event_signal(__int64 a1, unsigned __int8 a2)
{
  __int64 *v2; // x20
  int v3; // w22
  __int64 v4; // x30
  unsigned int v6; // w21

  v6 = a2;
  if ( *(_DWORD *)a1 == 1702260340 )
  {
    if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
    {
      v2 = &qword_9405BFF0[2];
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      if ( *(_BYTE *)(a1 + 4) != 0 )
      {
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        return 0;
      }
      v3 = 0;
      if ( (*(_DWORD *)(a1 + 8) & 1) != 0 )
        goto LABEL_5;
    }
    else
    {
      __asm { MSR             DAIFSet, #2 }
      v2 = &qword_9405BFF0[2];
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      if ( *(_BYTE *)(a1 + 4) != 0 )
      {
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        goto LABEL_7;
      }
      v3 = 1;
      if ( (*(_DWORD *)(a1 + 8) & 1) != 0 )
      {
LABEL_5:
        if ( (int)wait_queue_wake_one(a1 + 16, v6, 0) > 0 )
          goto LABEL_6;
        goto LABEL_13;
      }
    }
    *(_BYTE *)(a1 + 4) = 1;
    wait_queue_wake_all(a1 + 16, v6, 0);
    goto LABEL_6;
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/event.c", 142, "e->magic == EVENT_MAGIC");
LABEL_13:
  *(_BYTE *)(a1 + 4) = 1;
LABEL_6:
  spin_unlock((unsigned __int64 *)v2[465]);
  if ( v3 != 0 )
LABEL_7:
    __asm { MSR             DAIFClr, #2 }
  return 0;
}

/* ===== event_unsignal @ 0x940250FC size 80 ===== */
__int64 __fastcall event_unsignal(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x0

  if ( *(_DWORD *)a1 == 1702260340 )
  {
    *(_BYTE *)(a1 + 4) = 0;
    return 0;
  }
  else
  {
    v3 = panic(
           v1,
           "DEBUG ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/kernel/event.c",
           183,
           "e->magic == EVENT_MAGIC");
    return kernel_init(v3);
  }
}

/* ===== kernel_init @ 0x9402514C size 120 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 *kernel_init()
{
  __int64 v0; // x0
  __int64 v1; // x0

  v0 = MEMORY[0xFFFFFFFFE003CB98];
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    v0 = log_printf("initializing mp\n");
  nullsub_3(v0);
  v1 = MEMORY[0xFFFFFFFFE003CB98];
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    v1 = log_printf("initializing threads\n");
  thread_init_queues(v1);
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("initializing timers\n");
  qword_94067508 = (__int64)&qword_94067500;
  qword_94067500 = (__int64)&qword_94067500;
  MEMORY[0xFFFFFFFFE005A210] = 0;
  qword_94067528 = (__int64)&qword_94067520;
  qword_94067520 = (__int64)&qword_94067520;
  qword_94067548 = (__int64)&qword_94067540;
  qword_94067540 = (__int64)&qword_94067540;
  qword_94067568 = (__int64)&qword_94067560;
  qword_94067560 = (__int64)&qword_94067560;
  return &qword_94067500;
}

/* ===== mutex_init @ 0x940251C4 size 52 ===== */
__int64 __fastcall mutex_init(__int64 result)
{
  *(_DWORD *)result = 1836414072;
  *(_QWORD *)(result + 8) = 0;
  *(_DWORD *)(result + 16) = 0;
  *(_DWORD *)(result + 24) = 2002872692;
  *(_QWORD *)(result + 32) = result + 32;
  *(_QWORD *)(result + 40) = result + 32;
  *(_DWORD *)(result + 48) = 0;
  return result;
}

/* ===== mutex_acquire_timeout @ 0x940251F8 size 276 ===== */
__int64 __fastcall mutex_acquire_timeout(__int64 a1, __int64 a2)
{
  __int64 *v2; // x20
  int v3; // w22
  __int64 v4; // x30
  unsigned int v6; // w21
  __int64 v7; // x1
  int v8; // w0

  if ( *(_DWORD *)a1 != 1836414072 )
  {
    panic(
      v4,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/mutex.c",
      82,
      "m->magic == MUTEX_MAGIC");
  }
  else if ( *(_QWORD *)(a1 + 8) != _ReadStatusReg(TPIDR_EL1) )
  {
    v3 = 0;
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    {
      __asm { MSR             DAIFSet, #2 }
      v3 = 1;
    }
    v2 = &qword_9405BFF0[2];
    v6 = 0;
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v7 = a2;
    v8 = *(_DWORD *)(a1 + 16) + 1;
    *(_DWORD *)(a1 + 16) = v8;
    if ( v8 <= 1 )
      goto LABEL_6;
LABEL_12:
    v6 = wait_queue_block(a1 + 24, v7);
    if ( (v6 & 0x80000000) == 0 )
    {
LABEL_6:
      *(_QWORD *)(a1 + 8) = _ReadStatusReg(TPIDR_EL1);
      goto LABEL_7;
    }
    if ( v6 == -13 )
      --*(_DWORD *)(a1 + 16);
LABEL_7:
    spin_unlock((unsigned __int64 *)v2[465]);
    if ( v3 != 0 )
      __asm { MSR             DAIFClr, #2 }
    return v6;
  }
  panic(
    v4,
    "mutex_acquire_timeout: thread %p (%s) tried to acquire mutex %p it already owns.\n",
    _ReadStatusReg(TPIDR_EL1),
    _ReadStatusReg(TPIDR_EL1) + 696,
    a1);
  goto LABEL_12;
}

/* ===== mutex_release @ 0x9402530C size 312 ===== */
__int64 __fastcall mutex_release(__int64 a1)
{
  __int64 v1; // x20
  __int64 v2; // x30
  unsigned __int64 StatusReg; // x1
  char *v5; // x5
  int v11; // w0
  int v14; // w0
  const void *v15; // x2
  const char *v16; // x3
  const char *v17; // x6

  if ( *(_DWORD *)a1 != 1836414072 )
  {
    panic(
      v2,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/mutex.c",
      124,
      "m->magic == MUTEX_MAGIC");
    goto LABEL_11;
  }
  StatusReg = _ReadStatusReg(TPIDR_EL1);
  v5 = *(char **)(a1 + 8);
  if ( v5 != (char *)StatusReg )
  {
LABEL_11:
    v15 = (const void *)_ReadStatusReg(TPIDR_EL1);
    v16 = (const char *)(_ReadStatusReg(TPIDR_EL1) + 696);
    if ( v5 != nullptr )
      v17 = v5 + 696;
    else
      v17 = "none";
    panic(
      v2,
      "mutex_release: thread %p (%s) tried to release mutex %p it doesn't own. owned by %p (%s)\n",
      v15,
      v16,
      (const void *)a1,
      v5,
      v17);
    goto LABEL_14;
  }
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v1 = -536578848;
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    *(_QWORD *)(a1 + 8) = 0;
    v11 = *(_DWORD *)(a1 + 16) - 1;
    *(_DWORD *)(a1 + 16) = v11;
    if ( v11 <= 0 )
    {
LABEL_5:
      spin_unlock((unsigned __int64 *)v1);
      __asm { MSR             DAIFClr, #2 }
      return 0;
    }
LABEL_14:
    wait_queue_wake_one(a1 + 24, 1, 0);
    goto LABEL_5;
  }
  spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  *(_QWORD *)(a1 + 8) = 0;
  v14 = *(_DWORD *)(a1 + 16) - 1;
  *(_DWORD *)(a1 + 16) = v14;
  if ( v14 > 0 )
    wait_queue_wake_one(a1 + 24, 1, 0);
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  return 0;
}

/* ===== thread_get_current_cpu @ 0x94025444 size 212 ===== */
int *__fastcall thread_get_current_cpu(int a1)
{
  return &dword_940666C0[182 * a1];
}

/* ===== thread_insert_ready_queue @ 0x94025518 size 336 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall thread_insert_ready_queue(__int64 a1)
{
  __int64 v1; // x30
  __int64 v2; // x3
  int v3; // w1
  __int64 v4; // x4
  int v5; // w5
  __int64 *v6; // x2
  __int64 v8; // x0

  v2 = v1;
  if ( *(_DWORD *)a1 != 1953002084 )
  {
    panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 101, "t->magic == THREAD_MAGIC");
    goto LABEL_10;
  }
  v3 = *(_DWORD *)(a1 + 44);
  if ( v3 != 1 )
  {
LABEL_10:
    panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 102, "t->state == THREAD_READY");
LABEL_11:
    panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 104, "arch_ints_disabled()");
    goto LABEL_12;
  }
  v4 = a1 + 24;
  if ( *(_QWORD *)(a1 + 24) == 0 )
    goto LABEL_5;
  do
  {
    a1 = panic(
           v2,
           "ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/kernel/thread.c",
           103,
           "!list_in_list(&t->queue_node)");
LABEL_5:
    ;
  }
  while ( *(_QWORD *)(v4 + 8) != 0 );
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    goto LABEL_11;
  if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
  {
    v5 = *(_DWORD *)(a1 + 40);
    v6 = &qword_940672E0[2 * v5];
    *(_QWORD *)(v4 + 8) = v6[1];
    *(_QWORD *)(a1 + 24) = v6;
    *(_QWORD *)v6[1] = v4;
    v6[1] = v4;
    dword_940666B8 = v3 << v5;
    return 0;
  }
LABEL_12:
  v8 = panic(
         v2,
         "ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/thread.c",
         105,
         "spin_lock_held(&thread_lock)");
  return thread_insert_ready_queue_tail(v8);
}

/* ===== thread_insert_ready_queue_tail @ 0x94025668 size 340 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall thread_insert_ready_queue_tail(__int64 a1)
{
  __int64 v1; // x30
  __int64 v2; // x3
  int v3; // w1
  __int64 v4; // x4
  int v5; // w5
  __int64 *v6; // x7
  __int64 result; // x0
  __int64 v8; // x0

  v2 = v1;
  if ( *(_DWORD *)a1 != 1953002084 )
  {
    panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 115, "t->magic == THREAD_MAGIC");
    goto LABEL_10;
  }
  v3 = *(_DWORD *)(a1 + 44);
  if ( v3 != 1 )
  {
LABEL_10:
    panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 116, "t->state == THREAD_READY");
LABEL_11:
    panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 118, "arch_ints_disabled()");
    goto LABEL_12;
  }
  v4 = a1 + 24;
  if ( *(_QWORD *)(a1 + 24) == 0 )
    goto LABEL_5;
  do
  {
    a1 = panic(
           v2,
           "ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/kernel/thread.c",
           117,
           "!list_in_list(&t->queue_node)");
LABEL_5:
    ;
  }
  while ( *(_QWORD *)(v4 + 8) != 0 );
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    goto LABEL_11;
  if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
  {
    v5 = *(_DWORD *)(a1 + 40);
    v6 = &qword_940672E0[2 * v5];
    *(_QWORD *)(a1 + 24) = *v6;
    *(_QWORD *)(v4 + 8) = v6;
    result = *v6;
    dword_940666B8 = v3 << v5;
    *(_QWORD *)(result + 8) = v4;
    *v6 = v4;
    return result;
  }
LABEL_12:
  v8 = panic(
         v2,
         "ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/thread.c",
         119,
         "spin_lock_held(&thread_lock)");
  return thread_resched_check(v8);
}

/* ===== thread_resched_check @ 0x940257BC size 340 ===== */
int *thread_resched_check()
{
  __int64 v0; // x30
  __int64 v1; // x19
  int *result; // x0
  int v3; // w2
  int v4; // w3
  int v5; // w4
  __int64 v6; // x0

  v1 = v0;
  result = thread_get_current_cpu(-1);
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 516, "arch_ints_disabled()");
  }
  else if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
  {
    if ( (MEMORY[0xFFFFFFFFE005A220] & 1) != 0 )
    {
      v3 = 0;
      v4 = 0;
    }
    else
    {
      v3 = 0x7FFFFFFF;
      v4 = -1;
    }
    if ( (MEMORY[0xFFFFFFFFE005A220] & 2) != 0 && v3 > 0 )
    {
      v3 = 0;
      v4 = 1;
    }
    if ( (MEMORY[0xFFFFFFFFE005A220] & 4) != 0 && v3 > 0 )
    {
      v3 = 0;
      v4 = 2;
    }
    if ( (MEMORY[0xFFFFFFFFE005A220] & 8) != 0 && v3 > 0 )
    {
      v3 = 0;
      v4 = 3;
    }
    v5 = result[10];
    if ( v5 > v3 )
    {
      dword_940666A8[v4] = v5;
      return (int *)nullsub_4(1LL << v4, 0);
    }
    return result;
  }
  v6 = panic(
         v1,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/thread.c",
         517,
         "spin_lock_held(&thread_lock)");
  return (int *)thread_reschedule(v6);
}

/* ===== thread_reschedule @ 0x94025910 size 864 ===== */
__int64 thread_reschedule()
{
  __int64 v0; // x30
  __int64 v1; // x20
  int *StatusReg; // x21
  unsigned __int64 v3; // x0
  unsigned __int64 v4; // x19
  unsigned int v5; // w22
  __int64 v6; // x19
  int *v7; // x0
  int *v8; // x19
  bool v9; // zf
  __int64 result; // x0
  int v11; // w2
  __int64 v12; // x1
  int v13; // w0
  int v14; // w0
  unsigned __int64 v15; // x1
  int v16; // w3
  __int64 v17; // x1
  long double v18; // q0
  long double v19; // q1
  long double v20; // q2
  long double v21; // q3
  long double v22; // q4
  long double v23; // q5
  long double v24; // q6
  long double v25; // q7
  unsigned __int64 v26; // x0
  unsigned __int64 v27; // x0
  int v28; // w2

  v1 = v0;
  StatusReg = (int *)_ReadStatusReg(TPIDR_EL1);
  v3 = _ReadStatusReg(MPIDR_EL1);
  if ( (v3 & 0x1000000) != 0 )
    v3 >>= 8;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    panic(v0, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 561, "arch_ints_disabled()");
  }
  else if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
  {
    if ( StatusReg[11] == 2 )
    {
LABEL_32:
      panic(
        v0,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        563,
        "current_thread->state != THREAD_RUNNING");
      return panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 571, "newthread");
    }
    v4 = _ReadStatusReg(MPIDR_EL1);
    if ( (v4 & 0x1000000) != 0 )
      v4 >>= 8;
    v5 = (unsigned __int8)v3 | (4 * ((v3 >> 8) & 0xF));
    v6 = 80 * ((unsigned __int8)v4 | (4 * ((v4 >> 8) & 0xF))) - 536502064;
    ++*(_QWORD *)(v6 + 16);
    v7 = thread_get_current_cpu(v5);
    v8 = v7;
    if ( v7 != nullptr )
    {
      v9 = v7 == StatusReg;
      result = 2;
      v8[11] = 2;
      if ( v9 )
        return result;
      if ( v8[12] <= 0 )
        v8[12] = 5;
      StatusReg[14] = -1;
      v8[14] = v5;
      v11 = v8[13];
      v12 = 1LL << v5;
      if ( (v11 & 0x10) != 0 )
      {
        v13 = 1LL << v5;
        MEMORY[0xFFFFFFFFE005A224] |= v12;
        if ( (v11 & 8) == 0 )
          goto LABEL_25;
      }
      else
      {
        v13 = 1LL << v5;
        MEMORY[0xFFFFFFFFE005A224] &= ~(_DWORD)v12;
        if ( (v11 & 8) == 0 )
          goto LABEL_25;
      }
      if ( v8[10] > 16 )
      {
        v14 = v13 | MEMORY[0xFFFFFFFFE005A228];
        goto LABEL_16;
      }
LABEL_25:
      v14 = MEMORY[0xFFFFFFFFE005A228] & ~v13;
LABEL_16:
      MEMORY[0xFFFFFFFFE005A228] = v14;
      v15 = _ReadStatusReg(MPIDR_EL1);
      if ( (v15 & 0x1000000) != 0 )
        v15 >>= 8;
      v16 = StatusReg[13];
      v17 = 80 * ((unsigned __int8)v15 | (4 * ((v15 >> 8) & 0xF))) - 536502064;
      ++*(_QWORD *)(v17 + 24);
      if ( (v16 & 0x10) != 0 )
      {
        v26 = arch_time_now();
        v11 = v8[13];
        *(_QWORD *)(80LL * v5 - 536502064) = *(_QWORD *)(80LL * v5 - 536502064)
                                           - *(_QWORD *)(80LL * v5 - 536502056)
                                           + v26;
        if ( (v11 & 0x10) == 0 )
        {
LABEL_20:
          if ( (v11 & 0x18) == 0 )
            goto LABEL_21;
          goto LABEL_28;
        }
      }
      else if ( (v11 & 0x10) == 0 )
      {
        goto LABEL_20;
      }
      v27 = arch_time_now();
      v28 = v8[13];
      *(_QWORD *)(80LL * v5 - 536502056) = v27;
      if ( (v28 & 0x18) == 0 )
      {
LABEL_21:
        if ( (StatusReg[13] & 0x18) != 0 )
          timer_set_periodic(&qword_94067220[6 * v5], 10, -536846872, 0);
LABEL_23:
        dword_940666A8[v5] = v8[10];
        _WriteStatusReg(TPIDR_EL1, (unsigned __int64)v8);
        __isb(0xFu);
        v18 = arch_mmu_switch_aspace(StatusReg, v8);
        return (__int64)arch_context_switch((__int64)StatusReg, v18, v19, v20, v21, v22, v23, v24, v25);
      }
LABEL_28:
      thread_resched_check();
      if ( (StatusReg[13] & 0x18) == 0 )
        timer_cancel(&qword_94067220[6 * v5]);
      goto LABEL_23;
    }
    return panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 571, "newthread");
  }
  panic(v0, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 562, "spin_lock_held(&thread_lock)");
  goto LABEL_32;
}

/* ===== thread_preempt_check @ 0x94025C70 size 120 ===== */
__int64 __fastcall thread_preempt_check(__int64 a1, __int64 a2)
{
  unsigned __int64 StatusReg; // x2
  int v3; // w3
  __int64 v4; // x0

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  v3 = *(_DWORD *)(a2 + 60);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( v3 == -1 || v3 == *(_DWORD *)(a1 + 60) || ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) == v3 )
  {
    v4 = 0;
  }
  else
  {
    v4 = 0;
    if ( *(_DWORD *)(a2 + 40) >= dword_940666A8[v3] )
      v4 = 1LL << v3;
  }
  return nullsub_4(v4, 0);
}

/* ===== thread_timeout_callback @ 0x94025CE8 size 416 ===== */
bool __fastcall thread_timeout_callback(__int64 a1, __int64 a2, _DWORD *a3)
{
  __int64 v3; // x30
  unsigned __int64 StatusReg; // x19
  int v12; // w0

  if ( *a3 == 1953002084 )
  {
    if ( a3[11] == 4 )
    {
      if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
      {
        spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        a3[11] = 1;
        thread_insert_ready_queue((__int64)a3);
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      }
      else
      {
        __asm { MSR             DAIFSet, #2 }
        spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        a3[11] = 1;
        thread_insert_ready_queue((__int64)a3);
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        __asm { MSR             DAIFClr, #2 }
      }
      return true;
    }
  }
  else
  {
    panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 807, "t->magic == THREAD_MAGIC");
  }
  panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 808, "t->state == THREAD_SLEEPING");
  StatusReg = _ReadStatusReg(TPIDR_EL1);
  if ( (*(_DWORD *)(StatusReg + 52) & 0x10) != 0 )
    return false;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    thread_resched_check();
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    thread_resched_check();
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    __asm { MSR             DAIFClr, #2 }
  }
  if ( (*(_DWORD *)(StatusReg + 52) & 0x18) != 0 )
    return false;
  v12 = *(_DWORD *)(StatusReg + 48) - 1;
  *(_DWORD *)(StatusReg + 48) = v12;
  return v12 <= 0;
}

/* ===== thread_resume @ 0x94025E88 size 264 ===== */
__int64 __fastcall thread_resume(_DWORD *a1)
{
  __int64 v1; // x30
  int v3; // w21
  __int64 result; // x0
  unsigned __int64 StatusReg; // x1

  if ( a1 == nullptr )
    return 4294967288LL;
  if ( *a1 != 1953002084 )
  {
    panic(v1, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 236, "t->magic == THREAD_MAGIC");
    return 4294967288LL;
  }
  v3 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    if ( a1 != (_DWORD *)_ReadStatusReg(TPIDR_EL1) )
      goto LABEL_5;
LABEL_9:
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    if ( (StatusReg & 0x1000000) != 0 )
      StatusReg >>= 8;
    timer_cancel(&qword_94067220[6 * ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF)))]);
    goto LABEL_5;
  }
  __asm { MSR             DAIFSet, #2 }
  v3 = 1;
  spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( a1 == (_DWORD *)_ReadStatusReg(TPIDR_EL1) )
    goto LABEL_9;
LABEL_5:
  a1[13] |= 8u;
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  result = 0;
  if ( v3 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== thread_yield @ 0x94025F90 size 288 ===== */
unsigned __int64 *thread_yield()
{
  __int64 v0; // x30
  _DWORD *StatusReg; // x19
  int v2; // w21
  unsigned __int64 v3; // x0
  int v4; // w3
  __int64 v5; // x1
  unsigned __int64 *result; // x0
  __int64 v13; // x0

  StatusReg = (_DWORD *)_ReadStatusReg(TPIDR_EL1);
  if ( *StatusReg != 1953002084 )
  {
    panic(
      v0,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      673,
      "current_thread->magic == THREAD_MAGIC");
  }
  else if ( StatusReg[11] == 2 )
  {
    v2 = 0;
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    {
      __asm { MSR             DAIFSet, #2 }
      v2 = 1;
    }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v3 = _ReadStatusReg(MPIDR_EL1);
    v4 = StatusReg[13];
    if ( (v3 & 0x1000000) != 0 )
      v3 >>= 8;
    v5 = (unsigned __int8)v3 | (4 * ((v3 >> 8) & 0xF));
    ++*(_QWORD *)(80 * v5 - 536502024);
    StatusReg[12] = 0;
    StatusReg[11] = 1;
    if ( (v4 & 0x10) == 0 )
      thread_insert_ready_queue_tail((__int64)StatusReg);
    thread_reschedule();
    result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    if ( v2 != 0 )
      __asm { MSR             DAIFClr, #2 }
    return result;
  }
  v13 = panic(
          v0,
          "ASSERT FAILED at (%s:%d): %s\n",
          "external/lk/kernel/thread.c",
          674,
          "current_thread->state == THREAD_RUNNING");
  return (unsigned __int64 *)thread_resume_full(v13);
}

/* ===== thread_resume_full @ 0x940260B0 size 776 ===== */
unsigned __int64 *__fastcall thread_resume_full(_DWORD *a1)
{
  __int64 v1; // x22
  __int64 v2; // x30
  unsigned __int64 v4; // x23
  int v5; // w21
  BOOL v6; // w22
  unsigned __int64 v7; // x3
  unsigned __int64 v8; // x0
  int v9; // w1
  __int64 v10; // x0
  unsigned __int64 *result; // x0
  __int64 v18; // x30
  _DWORD *StatusReg; // x19
  unsigned __int64 v20; // x0
  __int64 v21; // x1
  int v22; // w21
  int v23; // w0

  if ( *a1 != 1953002084 )
  {
    panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 314, "t->magic == THREAD_MAGIC");
LABEL_21:
    panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 315, "t->state != THREAD_DEATH");
    StatusReg = (_DWORD *)_ReadStatusReg(TPIDR_EL1);
    if ( *StatusReg == 1953002084 )
    {
      if ( StatusReg[11] == 2 )
      {
        if ( (StatusReg[13] & 0x10) == 0 )
        {
          v20 = _ReadStatusReg(MPIDR_EL1);
          if ( (v20 & 0x1000000) != 0 )
            v20 >>= 8;
          v21 = (unsigned __int8)v20 | (4 * ((v20 >> 8) & 0xF));
          ++*(_QWORD *)(80 * v21 - 536502032);
        }
        if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
        {
          __asm { MSR             DAIFSet, #2 }
          v22 = 1;
          spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
          StatusReg[11] = 1;
          if ( (StatusReg[13] & 0x10) != 0 )
          {
            thread_reschedule();
            result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
            goto LABEL_32;
          }
LABEL_29:
          if ( (int)StatusReg[12] <= 0 )
            thread_insert_ready_queue_tail((__int64)StatusReg);
          else
            thread_insert_ready_queue((__int64)StatusReg);
          thread_reschedule();
          result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
          if ( v22 == 0 )
            return result;
LABEL_32:
          __asm { MSR             DAIFClr, #2 }
          return result;
        }
        v22 = 0;
        v1 = -536578848;
        spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        v23 = StatusReg[13];
        StatusReg[11] = 1;
        if ( (v23 & 0x10) == 0 )
          goto LABEL_29;
LABEL_39:
        thread_reschedule();
        return spin_unlock((unsigned __int64 *)v1);
      }
    }
    else
    {
      panic(
        v18,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        712,
        "current_thread->magic == THREAD_MAGIC");
    }
    panic(
      v18,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      713,
      "current_thread->state == THREAD_RUNNING");
    goto LABEL_39;
  }
  if ( a1[11] == 5 )
    goto LABEL_21;
  v4 = _ReadStatusReg(DAIF);
  v5 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v5 = 1;
    v6 = false;
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    if ( a1[11] != 0 )
      goto LABEL_5;
LABEL_18:
    a1[11] = 1;
    v6 = ((v4 ^ 0x80) & 0x80) != 0;
    thread_insert_ready_queue((__int64)a1);
    goto LABEL_5;
  }
  v6 = false;
  spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( a1[11] == 0 )
    goto LABEL_18;
LABEL_5:
  v7 = _ReadStatusReg(TPIDR_EL1);
  v8 = _ReadStatusReg(MPIDR_EL1);
  v9 = a1[15];
  if ( (v8 & 0x1000000) != 0 )
    v8 >>= 8;
  if ( v9 == -1 || v9 == *(_DWORD *)(v7 + 60) || ((unsigned __int8)v8 | (4 * ((v8 >> 8) & 0xF))) == v9 )
  {
    v10 = 0;
  }
  else
  {
    v10 = 0;
    if ( a1[10] >= dword_940666A8[v9] )
      v10 = 1LL << v9;
  }
  nullsub_4(v10, 0);
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( v5 != 0 )
    __asm { MSR             DAIFClr, #2 }
  if ( v6 )
    thread_yield();
  return nullptr;
}

/* ===== thread_sleep @ 0x940263B8 size 352 ===== */
unsigned __int64 *__fastcall thread_sleep(unsigned int a1)
{
  __int64 v1; // x30
  _DWORD *StatusReg; // x19
  unsigned __int64 *result; // x0
  __int64 v11; // x0
  _BYTE v12[48]; // [xsp+30h] [xbp+30h] BYREF

  StatusReg = (_DWORD *)_ReadStatusReg(TPIDR_EL1);
  if ( *StatusReg != 1953002084 )
  {
    panic(
      v1,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      838,
      "current_thread->magic == THREAD_MAGIC");
  }
  else if ( StatusReg[11] == 2 )
  {
    if ( (StatusReg[13] & 0x10) != 0 )
    {
LABEL_9:
      v11 = panic(
              v1,
              "ASSERT FAILED at (%s:%d): %s\n",
              "external/lk/kernel/thread.c",
              840,
              "!thread_is_idle(current_thread)");
      return (unsigned __int64 *)thread_init_queues(v11);
    }
    timer_init(v12);
    if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
    {
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      timer_set_oneshot(v12, a1, thread_timeout_callback, StatusReg);
      StatusReg[11] = 4;
      thread_reschedule();
      return spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    }
    else
    {
      __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      timer_set_oneshot(v12, a1, thread_timeout_callback, StatusReg);
      StatusReg[11] = 4;
      thread_reschedule();
      result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
    }
    return result;
  }
  panic(
    v1,
    "ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/thread.c",
    839,
    "current_thread->state == THREAD_RUNNING");
  goto LABEL_9;
}

/* ===== thread_init_queues @ 0x94026518 size 60 ===== */
__int64 thread_init_queues()
{
  timer_init(qword_94067220);
  timer_init(qword_94067250);
  timer_init(qword_94067280);
  return timer_init(qword_940672B0);
}

/* ===== thread_set_name @ 0x94026554 size 20 ===== */
__int64 __fastcall thread_set_name(__int64 a1)
{
  return strlcpy(_ReadStatusReg(TPIDR_EL1) + 696, a1, 32);
}

/* ===== thread_become_idle @ 0x94026568 size 264 ===== */
void __noreturn thread_become_idle()
{
  __int64 v0; // x30
  _DWORD *StatusReg; // x19
  unsigned __int64 v2; // x0
  unsigned __int64 v3; // x1
  unsigned __int64 v4; // x0
  __int64 v10; // x0
  _BYTE v11[16]; // [xsp+20h] [xbp+20h] BYREF

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    StatusReg = (_DWORD *)_ReadStatusReg(TPIDR_EL1);
    v2 = _ReadStatusReg(MPIDR_EL1);
    if ( (v2 & 0x1000000) != 0 )
      v2 >>= 8;
    snprintf(v11, 16, "idle %d", (unsigned __int8)v2 | (4 * ((v2 >> 8) & 0xF)));
    thread_set_name((__int64)v11);
    StatusReg[10] = 0;
    StatusReg[13] |= 0x10u;
    v3 = _ReadStatusReg(MPIDR_EL1);
    if ( (v3 & 0x1000000) != 0 )
      v3 >>= 8;
    StatusReg[15] = (unsigned __int8)v3 | (4 * ((v3 >> 8) & 0xF));
    smp_clear_cpu_mask(1);
    v4 = _ReadStatusReg(MPIDR_EL1);
    if ( (v4 & 0x1000000) != 0 )
      v4 >>= 8;
    MEMORY[0xFFFFFFFFE005A224] |= 1LL << ((unsigned __int8)v4 | (unsigned __int8)(4 * (BYTE1(v4) & 0xF)));
    __asm { MSR             DAIFClr, #2 }
    thread_yield();
    while ( 1 )
    {
      wfi();
      wfi();
    }
  }
  v10 = panic(
          v0,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "external/lk/kernel/thread.c",
          942,
          "arch_ints_disabled()");
  thread_enter_idle(v10);
}

/* ===== thread_enter_idle @ 0x94026670 size 108 ===== */
void __noreturn thread_enter_idle()
{
  unsigned __int64 StatusReg; // x0
  int v1; // w19

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v1 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  *(_DWORD *)(_ReadStatusReg(TPIDR_EL1) + 40) = 0;
  smp_clear_cpu_mask(1);
  MEMORY[0xFFFFFFFFE005A224] |= 1LL << v1;
  __asm { MSR             DAIFClr, #2 }
  thread_yield();
  while ( 1 )
  {
    wfi();
    wfi();
  }
}

/* ===== wait_queue_init @ 0x940266DC size 32 ===== */
__int64 __fastcall wait_queue_init(__int64 result)
{
  *(_QWORD *)(result + 8) = result + 8;
  *(_DWORD *)result = 2002872692;
  *(_QWORD *)(result + 16) = result + 8;
  *(_DWORD *)(result + 24) = 0;
  return result;
}

/* ===== thread_create @ 0x940266FC size 444 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall thread_create(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        unsigned int a5,
        __int64 a6,
        __int64 a7)
{
  __int64 v8; // x19
  int v11; // w21
  __int64 v12; // x0
  __int64 v20; // x0
  __int64 v21; // [xsp+48h] [xbp+48h]
  __int64 v22; // [xsp+48h] [xbp+48h]
  unsigned int v23; // [xsp+50h] [xbp+50h]
  unsigned int v24; // [xsp+50h] [xbp+50h]
  __int64 v25; // [xsp+58h] [xbp+58h]
  __int64 v26; // [xsp+58h] [xbp+58h]

  v8 = a1;
  v11 = 0;
  if ( a1 == 0 )
  {
    v22 = a6;
    v24 = a5;
    v11 = 4;
    v26 = a4;
    v20 = malloc(728);
    a4 = v26;
    v8 = v20;
    a5 = v24;
    a6 = v22;
    if ( v20 == 0 )
      return 0;
  }
  v21 = a6;
  v23 = a5;
  v25 = a4;
  memset(v8, 0, 728);
  *(_DWORD *)v8 = 1953002084;
  *(_DWORD *)(v8 + 60) = -1;
  strlcpy(v8 + 696, a2, 32);
  *(_QWORD *)(v8 + 632) = a3;
  *(_QWORD *)(v8 + 640) = v25;
  *(_QWORD *)(v8 + 40) = v23;
  *(_QWORD *)(v8 + 64) = 0;
  *(_DWORD *)(v8 + 72) = 0;
  *(_DWORD *)(v8 + 56) = -1;
  *(_DWORD *)(v8 + 648) = 0;
  wait_queue_init(v8 + 656);
  if ( v21 == 0 )
  {
    v12 = malloc(a7);
    *(_QWORD *)(v8 + 616) = v12;
    if ( v12 == 0 )
    {
      if ( (v11 & 4) != 0 )
        free(v8);
      return 0;
    }
    v11 |= 2u;
  }
  *(_QWORD *)(v8 + 624) = a7;
  *(_DWORD *)(v8 + 52) = v11;
  *(_QWORD *)(v8 + 688) = *(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688);
  thread_setup_stack((_QWORD *)v8);
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    *(_QWORD *)(v8 + 16) = 0;
    *(_QWORD *)(v8 + 8) = &qword_940674E8;
    MEMORY[0] = v8 + 8;
    off_940674F0 = (_UNKNOWN *)(v8 + 8);
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    *(_QWORD *)(v8 + 16) = 0;
    *(_QWORD *)(v8 + 8) = &qword_940674E8;
    MEMORY[0] = v8 + 8;
    off_940674F0 = (_UNKNOWN *)(v8 + 8);
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    __asm { MSR             DAIFClr, #2 }
  }
  return v8;
}

/* ===== thread_create_simple @ 0x940268B8 size 48 ===== */
__int64 __fastcall thread_create_simple(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, __int64 a5)
{
  return thread_create(0, a1, a2, a3, a4, 0, a5);
}

/* ===== thread_init_bootstrap @ 0x940268E8 size 300 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 *thread_init_bootstrap()
{
  __int64 v0; // x30
  unsigned __int64 StatusReg; // x1
  __int64 *v2; // x0
  __int64 v4; // x0
  __int64 v5; // x1
  __int64 v6; // x2

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  if ( ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) != 0 )
  {
    v4 = panic(
           v0,
           "DEBUG ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/kernel/thread.c",
           861,
           "arch_curr_cpu_num() == 0");
    return (__int64 *)thread_init_idle(v4, v5, v6);
  }
  else
  {
    v2 = qword_940672E0;
    do
    {
      v2[1] = (__int64)v2;
      *v2 = (__int64)v2;
      v2 += 2;
    }
    while ( v2 != &qword_940674E0 );
    qword_940674E8 = (__int64)&qword_940674E8;
    off_940674F0 = &qword_940674E8;
    memset(dword_940666C0, 0, 728);
    dword_940666C0[0] = 1953002084;
    dword_940666FC = -1;
    strlcpy(&qword_94066700[79], "bootstrap", 32);
    dword_940666F8 = 0;
    dword_940666E8 = 31;
    dword_940666EC = 2;
    dword_940666FC = 0;
    dword_940666F4 = 1;
    wait_queue_init((__int64)&qword_94066700[74]);
    qword_940666D0 = 0;
    qword_940666C8 = (__int64)&qword_940674E8;
    MEMORY[0] = &qword_940666C8;
    off_940674F0 = &qword_940666C8;
    dword_940666A8[0] = 0;
    _WriteStatusReg(TPIDR_EL1, (unsigned __int64)dword_940666C0);
    __isb(0xFu);
    return &qword_94065E98[45];
  }
}

/* ===== thread_init_idle @ 0x94026A14 size 404 ===== */
// write access to const memory has been detected, the output may be wrong!
unsigned __int64 *thread_init_idle()
{
  __int64 v0; // x30
  unsigned __int64 StatusReg; // x0
  __int64 v2; // x20
  int *v3; // x23
  int v4; // w24
  int *v5; // x1
  unsigned __int64 *result; // x0
  __int64 v13; // x0
  __int64 v14; // x1
  _BYTE v15[16]; // [xsp+60h] [xbp+60h] BYREF

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    if ( (StatusReg & 0x1000000) != 0 )
      StatusReg >>= 8;
    v2 = (unsigned __int8)StatusReg | (4 * ((unsigned int)(StatusReg >> 8) & 0xF));
    v3 = &dword_940666C0[182 * v2];
    snprintf(v15, 16, "idle %d", (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF)));
    memset(v3, 0, 728);
    *v3 = 1953002084;
    v3[15] = -1;
    strlcpy(v3 + 174, v15, 32);
    v3[15] = v2;
    v3[10] = 31;
    v3[13] = 17;
    v3[11] = 2;
    v3[14] = v2;
    wait_queue_init((__int64)&dword_940666C0[182 * v2 + 164]);
    v4 = 0;
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    {
      __asm { MSR             DAIFSet, #2 }
      v4 = 1;
    }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v5 = &dword_940666C0[182 * v2];
    *((_QWORD *)v5 + 1) = &qword_940674E8;
    *((_QWORD *)v5 + 2) = 0;
    MEMORY[0] = v5 + 2;
    off_940674F0 = v5 + 2;
    dword_940666A8[(unsigned int)v2] = v5[10];
    _WriteStatusReg(TPIDR_EL1, (unsigned __int64)v3);
    __isb(0xFu);
    result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    if ( v4 != 0 )
      __asm { MSR             DAIFClr, #2 }
  }
  else
  {
    v13 = panic(
            v0,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            "external/lk/kernel/thread.c",
            969,
            "arch_ints_disabled()");
    return (unsigned __int64 *)wait_queue_block(v13, v14);
  }
  return result;
}

/* ===== wait_queue_block @ 0x94026BA8 size 372 ===== */
__int64 __fastcall wait_queue_block(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  unsigned __int64 StatusReg; // x19
  int v4; // w2
  __int64 v5; // x4
  _BYTE v8[48]; // [xsp+30h] [xbp+30h] BYREF

  StatusReg = _ReadStatusReg(TPIDR_EL1);
  if ( *(_DWORD *)a1 != 2002872692 )
  {
    panic(
      v2,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      1166,
      "wait->magic == WAIT_QUEUE_MAGIC");
  }
  else if ( *(_DWORD *)(StatusReg + 44) == 2 )
  {
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    {
LABEL_13:
      panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1168, "arch_ints_disabled()");
    }
    else if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
    {
      if ( (_DWORD)a2 == 0 )
        return 4294967283LL;
      *(_QWORD *)(StatusReg + 24) = *(_QWORD *)(a1 + 8);
      v4 = *(_DWORD *)(a1 + 24);
      v5 = *(_QWORD *)(a1 + 8);
      *(_QWORD *)(StatusReg + 32) = a1 + 8;
      *(_QWORD *)(v5 + 8) = StatusReg + 24;
      *(_DWORD *)(a1 + 24) = v4 + 1;
      *(_QWORD *)(a1 + 8) = StatusReg + 24;
      *(_DWORD *)(StatusReg + 44) = 3;
      *(_QWORD *)(StatusReg + 64) = a1;
      *(_DWORD *)(StatusReg + 72) = 0;
      if ( (_DWORD)a2 == -1 )
      {
        thread_reschedule();
      }
      else
      {
        timer_init(v8);
        timer_set_oneshot(v8, a2, &loc_94027950, StatusReg);
        thread_reschedule();
        timer_cancel(v8);
      }
      return *(unsigned int *)(StatusReg + 72);
    }
    panic(
      v2,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      1169,
      "spin_lock_held(&thread_lock)");
    return 4294967283LL;
  }
  panic(
    v2,
    "ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/thread.c",
    1167,
    "current_thread->state == THREAD_RUNNING");
  goto LABEL_13;
}

/* ===== thread_join @ 0x94026D1C size 612 ===== */
__int64 __fastcall thread_join(__int64 a1, _DWORD *a2, unsigned int a3)
{
  int v3; // w23
  __int64 *v4; // x24
  __int64 v5; // x30
  __int64 v7; // x21
  unsigned int v9; // w20
  unsigned int v10; // w2
  _QWORD *v16; // x1
  int v18; // w1
  __int64 v19; // x0
  unsigned int v23; // [xsp+48h] [xbp+48h]

  v7 = v5;
  if ( *(_DWORD *)a1 != 1953002084 )
    goto LABEL_15;
  v23 = a3;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    goto LABEL_11;
  v4 = &qword_9405BFF0[2];
  v9 = -536578848;
  spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( (*(_DWORD *)(a1 + 52) & 1) != 0 )
  {
    v9 = -34;
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    return v9;
  }
  v3 = 0;
  v10 = v23;
  if ( *(_DWORD *)(a1 + 44) == 5 )
    goto LABEL_13;
  while ( 1 )
  {
    v9 = wait_queue_block(a1 + 656, v10);
    if ( (v9 & 0x80000000) != 0 )
      goto LABEL_29;
    if ( *(_DWORD *)a1 == 1953002084 )
      break;
LABEL_14:
    panic(v7, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 371, "t->magic == THREAD_MAGIC");
LABEL_15:
    panic(v5, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 350, "t->magic == THREAD_MAGIC");
LABEL_16:
    if ( *(_QWORD *)(a1 + 32) == 0 )
    {
      if ( a2 != nullptr )
        *a2 = *(_DWORD *)(a1 + 648);
      v16 = *(_QWORD **)(a1 + 16);
      *v16 = *(_QWORD *)(a1 + 8);
      *(_QWORD *)(*(_QWORD *)(a1 + 8) + 8LL) = v16;
      *(_QWORD *)(a1 + 16) = 0;
      *(_QWORD *)(a1 + 8) = 0;
      *(_DWORD *)a1 = 0;
      spin_unlock((unsigned __int64 *)v4[465]);
      if ( v3 != 0 )
        __asm { MSR             DAIFClr, #2 }
      v18 = *(_DWORD *)(a1 + 52);
      if ( (v18 & 2) != 0 )
      {
        v19 = *(_QWORD *)(a1 + 616);
        if ( v19 != 0 )
        {
          free(v19);
          v18 = *(_DWORD *)(a1 + 52);
        }
      }
      v9 = 0;
      if ( (v18 & 4) != 0 )
        free(a1);
      return v9;
    }
    while ( 1 )
    {
      panic(
        v7,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        374,
        "!list_in_list(&t->queue_node)");
LABEL_11:
      __asm { MSR             DAIFSet, #2 }
      v4 = &qword_9405BFF0[2];
      v9 = -536578848;
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      if ( (*(_DWORD *)(a1 + 52) & 1) != 0 )
      {
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        __asm { MSR             DAIFClr, #2 }
        return (unsigned int)-34;
      }
      v3 = 1;
      v10 = v23;
      if ( *(_DWORD *)(a1 + 44) != 5 )
        break;
LABEL_13:
      if ( *(_DWORD *)a1 != 1953002084 )
        goto LABEL_14;
LABEL_8:
      if ( *(_QWORD *)(a1 + 64) != 0 )
        goto LABEL_28;
      if ( *(_QWORD *)(a1 + 24) == 0 )
        goto LABEL_16;
    }
  }
  if ( *(_DWORD *)(a1 + 44) == 5 )
    goto LABEL_8;
  panic(v7, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 372, "t->state == THREAD_DEATH");
LABEL_28:
  panic(
    v7,
    "ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/thread.c",
    373,
    "t->blocking_wait_queue == NULL");
LABEL_29:
  spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  if ( v3 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v9;
}

/* ===== wait_queue_wake_one @ 0x94026F80 size 424 ===== */
__int64 __fastcall wait_queue_wake_one(__int64 a1, char a2, int a3)
{
  __int64 v3; // x30
  __int64 StatusReg; // x21
  __int64 v5; // x3
  _QWORD *v6; // x4
  __int64 v7; // x19
  int v8; // w4
  __int64 v10; // x0
  __int64 v11; // x1
  __int64 v12; // x2

  StatusReg = _ReadStatusReg(TPIDR_EL1);
  if ( *(_DWORD *)a1 != 2002872692 )
  {
    panic(
      v3,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      1219,
      "wait->magic == WAIT_QUEUE_MAGIC");
  }
  else if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE00474E0] == 0 )
    {
LABEL_14:
      panic(
        v3,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        1221,
        "spin_lock_held(&thread_lock)");
LABEL_15:
      v10 = panic(
              v3,
              "ASSERT FAILED at (%s:%d): %s\n",
              "external/lk/kernel/thread.c",
              1228,
              "t->state == THREAD_BLOCKED");
      return wait_queue_wake_all(v10, v11, v12);
    }
    v5 = *(_QWORD *)(a1 + 16);
    if ( v5 == a1 + 8 )
      return 0;
    v6 = *(_QWORD **)(v5 + 8);
    *v6 = *(_QWORD *)v5;
    *(_QWORD *)(*(_QWORD *)v5 + 8LL) = v6;
    *(_QWORD *)(v5 + 8) = 0;
    *(_QWORD *)v5 = 0;
    v7 = v5 - 24;
    if ( v5 == 24 )
      return 0;
    v8 = *(_DWORD *)(v5 + 20);
    --*(_DWORD *)(a1 + 24);
    if ( v8 != 3 )
      goto LABEL_15;
    *(_DWORD *)(v5 + 48) = a3;
    *(_DWORD *)(v5 + 20) = 1;
    *(_QWORD *)(v5 + 40) = 0;
    if ( a2 != 0 )
    {
      *(_DWORD *)(StatusReg + 44) = 1;
      thread_insert_ready_queue(StatusReg);
      thread_insert_ready_queue(v7);
      thread_preempt_check(StatusReg, v7);
      thread_reschedule();
    }
    else
    {
      thread_insert_ready_queue(v7);
      thread_preempt_check(StatusReg, v7);
    }
    return 1;
  }
  panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1220, "arch_ints_disabled()");
  goto LABEL_14;
}

/* ===== wait_queue_wake_all @ 0x94027128 size 724 ===== */
__int64 __fastcall wait_queue_wake_all(__int64 a1, unsigned __int8 a2, int a3)
{
  __int64 v3; // x30
  __int64 StatusReg; // x22
  int v7; // w1
  __int64 v8; // x28
  __int64 v9; // x0
  _QWORD *v10; // x2
  __int64 v11; // x19
  int v12; // w0
  unsigned int v13; // w25
  unsigned int v14; // w26
  __int64 v15; // x2
  __int64 v16; // x0
  _QWORD *v17; // x1
  int v18; // w1
  unsigned __int64 v19; // x0
  int v20; // w1
  __int64 v22; // x0
  __int64 v23; // [xsp+60h] [xbp+60h]
  int v24; // [xsp+6Ch] [xbp+6Ch]

  v24 = a2;
  StatusReg = _ReadStatusReg(TPIDR_EL1);
  if ( *(_DWORD *)a1 != 2002872692 )
  {
    panic(
      v3,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      1278,
      "wait->magic == WAIT_QUEUE_MAGIC");
  }
  else if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE00474E0] == 0 )
    {
LABEL_31:
      panic(
        v23,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        1280,
        "spin_lock_held(&thread_lock)");
      goto LABEL_32;
    }
    v7 = *(_DWORD *)(a1 + 24);
    if ( v24 != 0 && v7 > 0 )
    {
      *(_DWORD *)(StatusReg + 44) = 1;
      v8 = a1 + 8;
      thread_insert_ready_queue(StatusReg);
      v9 = *(_QWORD *)(a1 + 16);
      v7 = *(_DWORD *)(a1 + 24);
      if ( a1 + 8 == v9 )
      {
LABEL_25:
        if ( v7 == 0 )
          return 0;
        goto LABEL_32;
      }
    }
    else
    {
      v8 = a1 + 8;
      v9 = *(_QWORD *)(a1 + 16);
      if ( a1 + 8 == v9 )
        goto LABEL_25;
    }
    v10 = *(_QWORD **)(v9 + 8);
    *v10 = *(_QWORD *)v9;
    *(_QWORD *)(*(_QWORD *)v9 + 8LL) = v10;
    *(_QWORD *)(v9 + 8) = 0;
    *(_QWORD *)v9 = 0;
    v11 = v9 - 24;
    if ( v9 == 24 )
      goto LABEL_25;
    v12 = *(_DWORD *)(v9 + 20);
    *(_DWORD *)(a1 + 24) = v7 - 1;
    v13 = 0;
    v14 = 0;
    if ( v12 != 3 )
    {
LABEL_27:
      panic(
        v23,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        1296,
        "t->state == THREAD_BLOCKED");
      goto LABEL_28;
    }
    while ( 1 )
    {
      *(_DWORD *)(v11 + 44) = 1;
      *(_DWORD *)(v11 + 72) = a3;
      *(_QWORD *)(v11 + 64) = 0;
      thread_insert_ready_queue(v11);
      v19 = _ReadStatusReg(MPIDR_EL1);
      v20 = *(_DWORD *)(v11 + 60);
      if ( (v19 & 0x1000000) != 0 )
        v19 >>= 8;
      if ( v20 != -1 && v20 != *(_DWORD *)(StatusReg + 60) && ((unsigned __int8)v19 | (4 * ((v19 >> 8) & 0xF))) != v20 )
        break;
      v16 = *(_QWORD *)(v8 + 8);
      ++v14;
      if ( v8 == v16 )
        goto LABEL_20;
LABEL_14:
      v17 = *(_QWORD **)(v16 + 8);
      *v17 = *(_QWORD *)v16;
      *(_QWORD *)(*(_QWORD *)v16 + 8LL) = v17;
      *(_QWORD *)(v16 + 8) = 0;
      *(_QWORD *)v16 = 0;
      v11 = v16 - 24;
      if ( v16 == 24 )
        goto LABEL_20;
      v18 = *(_DWORD *)(v16 + 20);
      --*(_DWORD *)(a1 + 24);
      if ( v18 != 3 )
        goto LABEL_27;
    }
    LODWORD(v15) = 0;
    ++v14;
    v16 = *(_QWORD *)(v8 + 8);
    if ( *(_DWORD *)(v11 + 40) >= dword_940666A8[v20] )
      v15 = 1LL << v20;
    v13 |= v15;
    if ( v8 != v16 )
      goto LABEL_14;
LABEL_20:
    if ( *(_DWORD *)(a1 + 24) != 0 )
    {
LABEL_32:
      v22 = panic(v23, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1308, "wait->count == 0");
      return thread_cancel(v22);
    }
    nullsub_4(v13, 0);
    if ( v24 == 0 )
      return v14;
LABEL_28:
    thread_reschedule();
    return v14;
  }
  panic(v23, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1279, "arch_ints_disabled()");
  goto LABEL_31;
}

/* ===== thread_cancel @ 0x940273FC size 320 ===== */
__int64 __fastcall thread_cancel(_DWORD *a1)
{
  __int64 v1; // x20
  __int64 v2; // x30

  if ( *a1 == 1953002084 )
  {
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
    {
      __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      wait_queue_wake_all((__int64)(a1 + 164), 0, -34);
      if ( a1[11] != 5 )
      {
        a1[13] |= 1u;
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        __asm { MSR             DAIFClr, #2 }
        return 0;
      }
      a1[13] &= ~1u;
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
      return thread_join((__int64)a1, nullptr, 0);
    }
    v1 = -536578848;
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    wait_queue_wake_all((__int64)(a1 + 164), 0, -34);
    if ( a1[11] != 5 )
    {
      a1[13] |= 1u;
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      return 0;
    }
  }
  else
  {
    panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 402, "t->magic == THREAD_MAGIC");
  }
  a1[13] &= ~1u;
  spin_unlock((unsigned __int64 *)v1);
  return thread_join((__int64)a1, nullptr, 0);
}

/* ===== thread_exit @ 0x9402753C size 332 ===== */
__int64 __fastcall thread_exit(int a1)
{
  __int64 v1; // x30
  unsigned __int64 StatusReg; // x19
  int v4; // w1
  _QWORD *v5; // x2
  __int64 v6; // x30
  __int64 v12; // x0
  __int64 v13; // x1

  StatusReg = _ReadStatusReg(TPIDR_EL1);
  if ( *(_DWORD *)StatusReg != 1953002084 )
  {
    panic(
      v1,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      435,
      "current_thread->magic == THREAD_MAGIC");
  }
  else if ( *(_DWORD *)(StatusReg + 44) == 2 )
  {
    if ( (*(_DWORD *)(StatusReg + 52) & 0x10) == 0 )
    {
      if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
        __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      *(_DWORD *)(StatusReg + 648) = a1;
      v4 = *(_DWORD *)(StatusReg + 52);
      *(_DWORD *)(StatusReg + 44) = 5;
      if ( (v4 & 1) == 0 )
        goto LABEL_13;
      v5 = *(_QWORD **)(StatusReg + 16);
      *v5 = *(_QWORD *)(StatusReg + 8);
      *(_QWORD *)(*(_QWORD *)(StatusReg + 8) + 8LL) = v5;
      *(_QWORD *)(StatusReg + 16) = 0;
      *(_QWORD *)(StatusReg + 8) = 0;
      *(_DWORD *)StatusReg = 0;
      if ( (v4 & 2) != 0 && *(_QWORD *)(StatusReg + 616) != 0 )
      {
        ((void (*)(void))heap_free_to_quarantine)();
        v4 = *(_DWORD *)(StatusReg + 52);
      }
      if ( (v4 & 4) != 0 )
        heap_free_to_quarantine(StatusReg);
      while ( 1 )
      {
        thread_reschedule();
        panic(v6, "somehow fell through thread_exit()\n");
LABEL_13:
        wait_queue_wake_all(StatusReg + 656, 0, 0);
      }
    }
LABEL_16:
    v12 = panic(
            v1,
            "ASSERT FAILED at (%s:%d): %s\n",
            "external/lk/kernel/thread.c",
            437,
            "!thread_is_idle(current_thread)");
    return wait_queue_destroy(v12, v13);
  }
  panic(
    v1,
    "ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/thread.c",
    436,
    "current_thread->state == THREAD_RUNNING");
  goto LABEL_16;
}

/* ===== wait_queue_destroy @ 0x94027688 size 196 ===== */
__int64 __fastcall wait_queue_destroy(_DWORD *a1, unsigned __int8 a2)
{
  __int64 v2; // x30
  __int64 result; // x0
  __int64 v5; // x0

  if ( *a1 != 2002872692 )
  {
    panic(
      v2,
      "ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/thread.c",
      1329,
      "wait->magic == WAIT_QUEUE_MAGIC");
  }
  else if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
    {
      result = wait_queue_wake_all((__int64)a1, a2, -11);
      *a1 = 0;
      return result;
    }
LABEL_7:
    v5 = panic(
           v2,
           "ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/kernel/thread.c",
           1331,
           "spin_lock_held(&thread_lock)");
    return thread_wakeup(v5);
  }
  panic(v2, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1330, "arch_ints_disabled()");
  goto LABEL_7;
}

/* ===== thread_wakeup @ 0x9402774C size 652 ===== */
__int64 __fastcall thread_wakeup(__int64 a1, int a2)
{
  __int64 v2; // x30
  __int64 v4; // x0
  _DWORD *v5; // x2
  __int64 v6; // x3
  _QWORD *v7; // x4
  int v8; // w3
  unsigned __int64 StatusReg; // x3
  unsigned __int64 v10; // x0
  int v11; // w1
  __int64 v12; // x0
  _DWORD *v14; // x2
  __int64 v15; // x30
  int v16; // w20
  __int64 v17; // x0
  _DWORD *v18; // [xsp+28h] [xbp-8h]

  v4 = v2;
  if ( *(_DWORD *)a1 != 1953002084 )
    goto LABEL_20;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
LABEL_21:
    v4 = panic(v4, "ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/thread.c", 1353, "arch_ints_disabled()");
  }
  else if ( MEMORY[0xFFFFFFFFE00474E0] != 0 )
  {
    if ( *(_DWORD *)(a1 + 44) != 3 )
      return 4294967284LL;
    v5 = *(_DWORD **)(a1 + 64);
    if ( v5 == nullptr )
    {
      v4 = panic(
             v2,
             "ASSERT FAILED at (%s:%d): %s\n",
             "external/lk/kernel/thread.c",
             1361,
             "t->blocking_wait_queue != NULL");
LABEL_25:
      panic(
        v4,
        "ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/thread.c",
        1362,
        "t->blocking_wait_queue->magic == WAIT_QUEUE_MAGIC");
      if ( *v14 == 1953002084 )
      {
        v18 = v14;
        spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        v16 = thread_wakeup(v18);
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        return v16 >= 0;
      }
      else
      {
        v17 = panic(
                v15,
                "ASSERT FAILED at (%s:%d): %s\n",
                "external/lk/kernel/thread.c",
                1126,
                "thread->magic == THREAD_MAGIC");
        return timer_insert(v17);
      }
    }
    if ( *v5 != 2002872692 )
      goto LABEL_25;
    v6 = *(_QWORD *)(a1 + 24);
    v7 = *(_QWORD **)(a1 + 32);
    if ( v6 == 0 && v7 == nullptr )
    {
      v4 = panic(
             v2,
             "ASSERT FAILED at (%s:%d): %s\n",
             "external/lk/kernel/thread.c",
             1363,
             "list_in_list(&t->queue_node)");
LABEL_20:
      v4 = panic(
             v4,
             "ASSERT FAILED at (%s:%d): %s\n",
             "external/lk/kernel/thread.c",
             1352,
             "t->magic == THREAD_MAGIC");
      goto LABEL_21;
    }
    *v7 = v6;
    v8 = v5[6] - 1;
    *(_QWORD *)(*(_QWORD *)(a1 + 24) + 8LL) = v7;
    *(_QWORD *)(a1 + 32) = 0;
    *(_QWORD *)(a1 + 24) = 0;
    v5[6] = v8;
    *(_QWORD *)(a1 + 64) = 0;
    *(_DWORD *)(a1 + 44) = 1;
    *(_DWORD *)(a1 + 72) = a2;
    thread_insert_ready_queue(a1);
    StatusReg = _ReadStatusReg(TPIDR_EL1);
    v10 = _ReadStatusReg(MPIDR_EL1);
    v11 = *(_DWORD *)(a1 + 60);
    if ( (v10 & 0x1000000) != 0 )
      v10 >>= 8;
    if ( v11 == -1 || v11 == *(_DWORD *)(StatusReg + 60) || ((unsigned __int8)v10 | (4 * ((v10 >> 8) & 0xF))) == v11 )
    {
      v12 = 0;
    }
    else
    {
      v12 = 0;
      if ( *(_DWORD *)(a1 + 40) >= dword_940666A8[v11] )
        v12 = 1LL << v11;
    }
    nullsub_4(v12, 0);
    return 0;
  }
  panic(
    v4,
    "ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/thread.c",
    1354,
    "spin_lock_held(&thread_lock)");
  return 4294967284LL;
}

/* ===== timer_insert @ 0x940279D8 size 228 ===== */
__int64 __fastcall timer_insert(unsigned int a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 *v3; // x5
  __int64 v4; // x4
  __int64 v5; // x2
  int v6; // w6
  __int64 result; // x0
  __int64 v8; // x1
  __int64 v9; // x0

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    v3 = &qword_94067500[4 * a1];
    v4 = v3[1];
    v5 = v4 - 8;
    if ( (__int64 *)v4 != v3 )
    {
      v6 = *(_DWORD *)(a2 + 24);
      if ( *(_DWORD *)(v4 + 16) - v6 > 0 )
      {
LABEL_8:
        result = a2 + 8;
        *(_QWORD *)(a2 + 8) = *(_QWORD *)(v5 + 8);
        v8 = *(_QWORD *)(v5 + 8);
        *(_QWORD *)(result + 8) = v4;
        *(_QWORD *)(v8 + 8) = result;
        *(_QWORD *)(v5 + 8) = result;
        return result;
      }
      while ( 1 )
      {
        v4 = *(_QWORD *)(v5 + 16);
        v5 = v4 - 8;
        if ( (__int64 *)v4 == v3 )
          break;
        if ( *(_DWORD *)(v4 + 16) - v6 > 0 )
          goto LABEL_8;
      }
    }
    result = 32LL * a1;
    *(_QWORD *)(a2 + 8) = *(__int64 *)((char *)qword_94067500 + result);
    *(_QWORD *)(a2 + 16) = v3;
    *(_QWORD *)(*(__int64 *)((char *)qword_94067500 + result) + 8) = a2 + 8;
    *(__int64 *)((char *)qword_94067500 + result) = a2 + 8;
    return result;
  }
  v9 = panic(
         v2,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/timer.c",
         82,
         "arch_ints_disabled()");
  return timer_tick(v9);
}

/* ===== timer_tick @ 0x94027ABC size 876 ===== */
unsigned __int64 *__fastcall timer_tick(__int64 a1, unsigned int a2)
{
  __int64 *v2; // x19
  __int64 *v3; // x21
  unsigned int v4; // w22
  __int64 *v5; // x23
  unsigned int v6; // w24
  __int64 *v7; // x25
  __int64 *v8; // x26
  __int64 v9; // x28
  __int64 v10; // x30
  __int64 v11; // x20
  unsigned __int64 StatusReg; // x1
  __int64 v14; // x0
  unsigned __int64 v15; // x1
  unsigned __int64 *result; // x0
  int v17; // w2
  signed int v18; // w2
  __int64 *v19; // x0
  unsigned __int64 v20; // x4
  unsigned int (__fastcall *v21)(__int64, _QWORD, __int64); // x7
  __int64 v22; // x2
  __int64 v23; // x3
  int v24; // w0
  __int64 v25; // x20
  int v26; // w2
  unsigned int v27; // w1
  unsigned int v28; // w22
  __int64 v29; // x3
  __int64 v30; // x4
  int v31; // w0
  int v32; // w21
  unsigned __int64 v38; // x19
  unsigned int v39; // w19
  __int64 *v40; // x19
  __int64 *v41; // x0
  int v43; // [xsp+48h] [xbp-18h]
  __int64 v44; // [xsp+50h] [xbp-10h]
  __int64 v45; // [xsp+58h] [xbp-8h]
  unsigned __int64 *v46; // [xsp+C0h] [xbp+60h]
  int v47; // [xsp+C8h] [xbp+68h]

  v11 = v10;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/timer.c", 231, "arch_ints_disabled()");
    goto LABEL_12;
  }
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  v2 = &qword_9405BFF0[2];
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v14 = 80 * ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) - 536502064;
  ++*(_QWORD *)(v14 + 56);
  v15 = _ReadStatusReg(MPIDR_EL1);
  v5 = &qword_9405BFF0[2];
  if ( (v15 & 0x1000000) != 0 )
    v15 >>= 8;
  v4 = (unsigned __int8)v15 | (4 * ((v15 >> 8) & 0xF));
  v6 = 0;
  spin_lock((unsigned __int64 *)0xFFFFFFFFE005A210LL);
  v3 = &qword_94067500[4 * (unsigned __int8)v4];
  v7 = v3;
  while ( 1 )
  {
    v8 = (__int64 *)v7[1];
    if ( v8 == v3 )
      goto LABEL_10;
    if ( v8 == nullptr )
      goto LABEL_10;
    v9 = (__int64)(v8 - 1);
    if ( v8 == (__int64 *)8 )
      goto LABEL_10;
LABEL_12:
    v17 = *(_DWORD *)(v9 + 24);
    if ( ((a2 - v17) & 0x80000000) != 0 )
    {
      v18 = v17 - a2;
      if ( v18 > 0 )
      {
        arm_generic_timer_set(timer_tick, 0, v18);
LABEL_10:
        spin_unlock((unsigned __int64 *)v5[490]);
        return (unsigned __int64 *)v6;
      }
      panic(
        v11,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "external/lk/kernel/timer.c",
        288,
        (const char *)&loc_9404F130);
    }
    if ( *((_DWORD *)v8 - 2) != 1953066354 )
      break;
    v19 = (__int64 *)v8[1];
    *v19 = *v8;
    *(_QWORD *)(*v8 + 8) = v19;
    v8[1] = 0;
    *v8 = 0;
    v46 = (unsigned __int64 *)v5[490];
    spin_unlock(v46);
    v20 = _ReadStatusReg(MPIDR_EL1);
    if ( (v20 & 0x1000000) != 0 )
      v20 >>= 8;
    v21 = *(unsigned int (__fastcall **)(__int64, _QWORD, __int64))(v9 + 32);
    v22 = *(_QWORD *)(v9 + 40);
    v47 = *(_DWORD *)(v9 + 28);
    v23 = v2[469] + 80 * ((unsigned __int8)v20 | (4 * ((v20 >> 8) & 0xF)));
    ++*(_QWORD *)(v23 + 64);
    if ( v21(v9, a2, v22) == 1 )
      v6 = 1;
    spin_lock(v46);
    if ( v47 != 0 && *v8 == 0 && v8[1] == 0 )
    {
      v24 = *(_DWORD *)(v9 + 28);
      if ( v24 != 0 )
      {
        *(_DWORD *)(v9 + 24) = a2 + v24;
        timer_insert(v4, v9);
      }
    }
  }
  v25 = panic(
          v11,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "external/lk/kernel/timer.c",
          253,
          "timer && timer->magic == TIMER_MAGIC");
  v43 = v26;
  v28 = v27;
  v44 = v29;
  v45 = v30;
  v31 = arch_time_now_ms();
  *(_DWORD *)(v25 + 28) = v43;
  *(_QWORD *)(v25 + 32) = v44;
  *(_DWORD *)(v25 + 24) = v31 + v28;
  *(_QWORD *)(v25 + 40) = v45;
  v32 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v32 = 1;
  }
  spin_lock((unsigned __int64 *)0xFFFFFFFFE005A210LL);
  v38 = _ReadStatusReg(MPIDR_EL1);
  if ( (v38 & 0x1000000) != 0 )
    v38 >>= 8;
  v39 = (unsigned __int8)v38 | (4 * ((v38 >> 8) & 0xF));
  timer_insert(v39, v25);
  v40 = &qword_94067500[4 * (unsigned __int8)v39];
  v41 = (__int64 *)v40[1];
  if ( v41 != nullptr && v41 != v40 && (__int64 *)v25 == v41 - 1 )
    arm_generic_timer_set(timer_tick, 0, v28);
  result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE005A210LL);
  if ( v32 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== timer_init @ 0x94027E28 size 40 ===== */
__int64 __fastcall timer_init(__int64 result)
{
  *(_QWORD *)(result + 8) = 0;
  *(_QWORD *)(result + 16) = 0;
  *(_DWORD *)result = 1953066354;
  *(_DWORD *)(result + 24) = 0;
  *(_DWORD *)(result + 28) = 0;
  *(_QWORD *)(result + 32) = 0;
  *(_QWORD *)(result + 40) = 0;
  return result;
}

/* ===== timer_is_empty @ 0x94027E50 size 52 ===== */
bool __fastcall timer_is_empty(unsigned int a1)
{
  __int64 *v1; // x0
  __int64 *v2; // x1

  v1 = &qword_94067500[4 * a1];
  v2 = (__int64 *)v1[1];
  return v2 == nullptr || v2 == v1 || v2 == (__int64 *)8;
}

/* ===== timer_set_oneshot @ 0x94027E84 size 140 ===== */
__int64 __fastcall timer_set_oneshot(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x30
  __int64 v5; // x5
  __int64 v6; // x8
  __int64 v7; // x4
  __int64 v8; // x0
  __int64 v9; // x1
  __int64 v10; // x2
  __int64 v11; // x3

  v5 = a1;
  v6 = v4;
  v7 = a4;
  if ( *(_DWORD *)a1 == 1953066354 )
  {
    if ( *(_QWORD *)(a1 + 8) == 0 )
      goto LABEL_4;
    while ( 1 )
    {
      a1 = panic(v6, (const char *)&loc_9404F178, v5, a4, v7);
LABEL_4:
      if ( *(_QWORD *)(a1 + 16) == 0 )
        JUMPOUT(0x94027D28LL);
    }
  }
  v8 = panic(
         v4,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/timer.c",
         103,
         "timer->magic == TIMER_MAGIC");
  return timer_set_periodic(v8, v9, v10, v11);
}

/* ===== timer_set_periodic @ 0x94027F10 size 140 ===== */
__int64 __fastcall timer_set_periodic(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x30
  __int64 v5; // x5
  __int64 v6; // x8
  __int64 v7; // x4
  __int64 v8; // x0

  v5 = a1;
  v6 = v4;
  v7 = a4;
  if ( *(_DWORD *)a1 == 1953066354 )
  {
    if ( *(_QWORD *)(a1 + 8) == 0 )
      goto LABEL_4;
    while ( 1 )
    {
      a1 = panic(v6, (const char *)&loc_9404F178, v5, a4, v7);
LABEL_4:
      if ( *(_QWORD *)(a1 + 16) == 0 )
        JUMPOUT(0x94027D28LL);
    }
  }
  v8 = panic(
         v4,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         "external/lk/kernel/timer.c",
         103,
         "timer->magic == TIMER_MAGIC");
  return timer_cancel(v8);
}

/* ===== timer_cancel @ 0x94027F9C size 368 ===== */
unsigned __int64 *__fastcall timer_cancel(__int64 a1)
{
  __int64 *v1; // x20
  int v2; // w21
  __int64 v3; // x30
  unsigned __int64 StatusReg; // x0
  __int64 v6; // x8
  __int64 v7; // x2
  __int64 *v8; // x3
  __int64 v9; // x0
  __int64 v10; // x5
  BOOL v11; // w1
  _QWORD *v12; // x6
  signed int v13; // w2
  unsigned __int64 *result; // x0

  if ( *(_DWORD *)a1 != 1953066354 )
  {
    panic(
      v3,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/timer.c",
      181,
      "timer->magic == TIMER_MAGIC");
LABEL_22:
    arm_generic_timer_cancel();
    goto LABEL_16;
  }
  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  v1 = &qword_9405BFF0[2];
  spin_lock((unsigned __int64 *)0xFFFFFFFFE005A210LL);
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v6 = *(_QWORD *)(a1 + 8);
  v7 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  v8 = &qword_94067500[4 * v7];
  v9 = v8[1];
  v10 = v9 - 8;
  v11 = v9 != (_QWORD)v8 && v9 != 0;
  v12 = *(_QWORD **)(a1 + 16);
  if ( v9 == (_QWORD)v8 || v9 == 0 )
    v10 = 0;
  if ( v6 != 0 || v12 != nullptr )
  {
    *v12 = v6;
    *(_QWORD *)(*(_QWORD *)(a1 + 8) + 8LL) = v12;
    *(_QWORD *)(a1 + 16) = 0;
    *(_QWORD *)(a1 + 8) = 0;
    v9 = qword_94067500[4 * v7 + 1];
    v11 = v8 != (__int64 *)v9 && v9 != 0;
  }
  *(_DWORD *)(a1 + 28) = 0;
  *(_QWORD *)(a1 + 32) = 0;
  *(_QWORD *)(a1 + 40) = 0;
  if ( !v11 || v9 == 8 )
    goto LABEL_22;
  if ( v10 != v9 - 8 )
  {
    v13 = *(_DWORD *)(v9 + 16) - arch_time_now_ms();
    if ( v13 < 0 )
      v13 = 0;
    arm_generic_timer_set(timer_tick, 0, v13);
  }
LABEL_16:
  result = spin_unlock((unsigned __int64 *)v1[490]);
  if ( v2 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== semaphore_init @ 0x94028150 size 48 ===== */
__int64 __fastcall semaphore_init(__int64 result, int a2)
{
  *(_DWORD *)result = 1936026977;
  *(_DWORD *)(result + 4) = a2;
  *(_DWORD *)(result + 8) = 2002872692;
  *(_QWORD *)(result + 16) = result + 16;
  *(_QWORD *)(result + 24) = result + 16;
  *(_DWORD *)(result + 32) = 0;
  return result;
}

/* ===== semaphore_destroy @ 0x94028180 size 132 ===== */
unsigned __int64 *__fastcall semaphore_destroy(__int64 a1)
{
  unsigned __int64 *result; // x0

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    *(_DWORD *)(a1 + 4) = 0;
    wait_queue_destroy((_DWORD *)(a1 + 8), 1u);
    return spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    *(_DWORD *)(a1 + 4) = 0;
    wait_queue_destroy((_DWORD *)(a1 + 8), 1u);
    result = spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    __asm { MSR             DAIFClr, #2 }
  }
  return result;
}

/* ===== semaphore_post @ 0x94028204 size 244 ===== */
__int64 __fastcall semaphore_post(__int64 a1, char a2)
{
  int v9; // w0
  unsigned int v10; // w19
  int v13; // w0
  unsigned int v14; // w19

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v13 = *(_DWORD *)(a1 + 4) + 1;
    *(_DWORD *)(a1 + 4) = v13;
    if ( v13 <= 0 )
      v14 = wait_queue_wake_one(a1 + 8, a2, 0);
    else
      v14 = 0;
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    return v14;
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v9 = *(_DWORD *)(a1 + 4) + 1;
    *(_DWORD *)(a1 + 4) = v9;
    if ( v9 <= 0 )
    {
      v10 = wait_queue_wake_one(a1 + 8, a2, 0);
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
    }
    else
    {
      v10 = 0;
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
    }
    return v10;
  }
}

/* ===== semaphore_wait @ 0x940282F8 size 296 ===== */
__int64 __fastcall semaphore_wait(__int64 a1, __int64 a2)
{
  int v8; // w0
  unsigned int v9; // w21
  int v12; // w0
  unsigned int v13; // w21

  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v12 = *(_DWORD *)(a1 + 4) - 1;
    *(_DWORD *)(a1 + 4) = v12;
    if ( v12 < 0 )
    {
      v13 = wait_queue_block(a1 + 8, a2);
      if ( v13 == -13 )
        ++*(_DWORD *)(a1 + 4);
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    }
    else
    {
      v13 = 0;
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    }
    return v13;
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
    v8 = *(_DWORD *)(a1 + 4) - 1;
    *(_DWORD *)(a1 + 4) = v8;
    if ( v8 < 0 )
    {
      v9 = wait_queue_block(a1 + 8, a2);
      if ( v9 == -13 )
      {
        ++*(_DWORD *)(a1 + 4);
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        __asm { MSR             DAIFClr, #2 }
      }
      else
      {
        spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
        __asm { MSR             DAIFClr, #2 }
      }
    }
    else
    {
      v9 = 0;
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE00474E0LL);
      __asm { MSR             DAIFClr, #2 }
    }
    return v9;
  }
}

/* ===== nullsub_3 @ 0x94028420 size 4 ===== */
void nullsub_3()
{
  ;
}

/* ===== nullsub_4 @ 0x94028424 size 4 ===== */
void nullsub_4()
{
  ;
}

/* ===== smp_clear_cpu_mask @ 0x94028428 size 68 ===== */
__int64 smp_clear_cpu_mask()
{
  unsigned __int64 StatusReg; // x0
  __int64 result; // x0
  unsigned int v2; // w2

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  result = (unsigned int)(1 << (StatusReg | (4 * (BYTE1(StatusReg) & 0xF))));
  do
    v2 = __ldxr((unsigned int *)0xFFFFFFFFE005A220LL);
  while ( __stxr(v2 | result, (unsigned int *)0xFFFFFFFFE005A220LL) != 0 );
  return result;
}

/* ===== sm_register_entity @ 0x9402846C size 56 ===== */
__int64 sm_register_entity()
{
  __int64 result; // x0

  result = sm_register_entity_ex(51, &qword_9405A588);
  if ( (_DWORD)result != 0 )
    return printf("trusty error register entity: %d\n", result);
  return result;
}

/* ===== log_ring_write @ 0x940284A4 size 344 ===== */
unsigned __int64 *__fastcall log_ring_write(__int64 a1, __int64 a2, unsigned __int64 a3)
{
  int **v3; // x19
  char v5; // w20
  unsigned __int64 v12; // x10
  __int64 v13; // x7
  __int64 v14; // x9
  int *v15; // x6
  int v16; // w8
  __int64 i; // x4
  int v18; // w3
  char v19; // w5
  unsigned __int64 v20; // x2
  _DWORD *v21; // x6
  int v22; // w7
  __int64 v23; // x4
  int v24; // w3
  char v25; // w1
  unsigned __int64 *result; // x0

  v3 = (int **)(a1 - 32);
  v5 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v5 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    v5 |= 2u;
    __asm { MSR             DAIFSet, #1 }
  }
  spin_lock((unsigned __int64 *)&qword_94067580);
  v12 = a3 >> 7;
  if ( a3 >> 7 != 0 )
  {
    v13 = a2;
    v14 = 0;
    do
    {
      v15 = *v3;
      v16 = **v3;
      **v3 = v16 + 128;
      __dsb(0xEu);
      for ( i = 0; i != 128; ++i )
      {
        v18 = v16 + i;
        v19 = *(_BYTE *)(v13 + i);
        *((_BYTE *)v15 + (((unsigned int)v3[1] - 1) & v18) + 12) = v19;
      }
      __dsb(0xEu);
      ++v14;
      v13 += 128;
      v15[1] += 128;
    }
    while ( v14 != v12 );
    v12 <<= 7;
  }
  v20 = a3 - v12;
  if ( a3 != v12 )
  {
    v21 = *(_DWORD **)(a1 - 32);
    v22 = *v21;
    *v21 += v20;
    __dsb(0xEu);
    v23 = 0;
    do
    {
      v24 = v22 + v23;
      v25 = *(_BYTE *)(a2 + v12 + v23++);
      *((_BYTE *)v21 + (((unsigned int)v3[1] - 1) & v24) + 12) = v25;
    }
    while ( v23 != v20 );
    __dsb(0xEu);
    v21[1] += v23;
  }
  result = spin_unlock((unsigned __int64 *)&qword_94067580);
  if ( (v5 & 2) != 0 )
    __asm { MSR             DAIFClr, #1 }
  if ( (v5 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== logmem_create @ 0x940285FC size 372 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall logmem_create(unsigned __int64 a1, __int64 a2)
{
  __int64 v2; // x2
  unsigned __int64 v3; // x3
  __int64 *v5; // x2
  bool v6; // zf
  __int64 v9; // x22
  __int64 v10; // x23
  _DWORD *v11; // x3
  char v12; // w2
  __int64 v13; // x0
  _DWORD *v14; // [xsp+48h] [xbp+48h] BYREF

  v2 = -536632000;
  if ( &qword_9405A578 == (__int64 *)-536631944LL )
  {
LABEL_7:
    v9 = malloc(72);
    if ( v9 != 0 )
    {
      v10 = a1 & 0xFFFFF;
      *(_QWORD *)(v9 + 16) = a1;
      *(_QWORD *)(v9 + 24) = a2;
      if ( (unsigned int)vmm_map(
                           -536460256,
                           "logmem",
                           (a2 + 0xFFFFF + (a1 & 0xFFFFF)) & 0xFFFFFFFFFFF00000LL,
                           &v14,
                           12,
                           a1 & 0xFFFFFFFFFFF00000LL,
                           0,
                           48) == 0 )
      {
        v11 = (_DWORD *)((char *)v14 + v10);
        v12 = __clz(*(_QWORD *)(v9 + 24) - 12);
        *(_QWORD *)v9 = (char *)v14 + v10;
        v13 = (unsigned int)(1 << (31 - v12));
        *(_QWORD *)(v9 + 8) = v13;
        v11[2] = v13;
        v14 = v11;
        *v11 = 0;
        v11[1] = 0;
        *(_QWORD *)(v9 + 64) = -536631944;
        *(_QWORD *)(v9 + 56) = &qword_9405A578;
        MEMORY[0xFFFFFFFFE003A578] = v9 + 56;
        off_9405A580 = (_UNKNOWN *)(v9 + 56);
        *(_QWORD *)(v9 + 48) = -536836956;
        console_register(v9 + 32);
        MEMORY[0xFFFFFFFFE0057F30] = 1;
        return 0;
      }
      free(v9);
    }
    return -7;
  }
  else
  {
    while ( 1 )
    {
      v3 = *(_QWORD *)(v2 + 16);
      if ( v3 < a1 + a2 && a1 < v3 + *(_QWORD *)(v2 + 24) )
        return -2;
      v5 = *(__int64 **)(v2 + 64);
      v6 = &qword_9405A578 == v5;
      v2 = (__int64)(v5 - 7);
      if ( v6 )
        goto LABEL_7;
    }
  }
}

/* ===== logmem_destroy @ 0x94028770 size 172 ===== */
__int64 __fastcall logmem_destroy(__int64 a1)
{
  __int64 v1; // x1
  __int64 v2; // x19
  _QWORD *v3; // x2
  __int64 v4; // x1
  int v5; // w20
  __int64 result; // x0

  v1 = -536631944;
  v2 = -536632000;
  if ( &qword_9405A578 == (__int64 *)-536631944LL )
    return -2;
  while ( a1 != *(_QWORD *)(v1 - 40) )
  {
    v1 = *(_QWORD *)(v2 + 64);
    v2 = v1 - 56;
    if ( &qword_9405A578 == (__int64 *)v1 )
      return -2;
  }
  console_unregister(v2 + 32);
  v3 = *(_QWORD **)(v2 + 64);
  v4 = *(_QWORD *)v2;
  *v3 = *(_QWORD *)(v2 + 56);
  *(_QWORD *)(*(_QWORD *)(v2 + 56) + 8LL) = v3;
  *(_QWORD *)(v2 + 64) = 0;
  *(_QWORD *)(v2 + 56) = 0;
  v5 = vmm_free_region(-536460256, v4);
  free(v2);
  result = -7;
  if ( v5 == 0 )
    return 0;
  return result;
}

/* ===== logmem_ioctl @ 0x9402881C size 92 ===== */
__int64 __fastcall logmem_ioctl(int *a1)
{
  int v1; // w1
  __int64 result; // x0

  v1 = *a1;
  if ( *a1 == 855638017 )
    return logmem_create((unsigned int)a1[1] | ((unsigned __int64)(unsigned int)a1[2] << 32), (unsigned int)a1[3]);
  if ( v1 == 855638018 )
    return logmem_destroy((unsigned int)a1[1] | ((unsigned __int64)(unsigned int)a1[2] << 32));
  result = 0xFFFFFFFFLL;
  if ( v1 == 855638016 )
    return 1;
  return result;
}

/* ===== sm_register_entity2 @ 0x94028878 size 56 ===== */
__int64 sm_register_entity2()
{
  __int64 result; // x0

  result = sm_register_entity_ex(53, &qword_9405A598);
  if ( (_DWORD)result != 0 )
    return printf("trusty error register entity: %d\n", result);
  return result;
}

/* ===== sm_debug_ioctl @ 0x940288B0 size 152 ===== */
__int64 __fastcall sm_debug_ioctl(_DWORD *a1)
{
  unsigned int v2; // w1
  __int64 result; // x0

  switch ( *a1 )
  {
    case 0x35000000:
      MEMORY[0xFFFFFFFFE0059F48] = (unsigned int)a1[1];
      result = 0;
      break;
    case 0x35000001:
      result = MEMORY[0xFFFFFFFFE0059F48];
      break;
    case 0x35000002:
      v2 = a1[1];
      if ( v2 > 2 )
      {
        result = -2;
      }
      else
      {
        result = 0;
        MEMORY[0xFFFFFFFFE003CB98] = v2;
      }
      break;
    case 0x35000003:
      result = MEMORY[0xFFFFFFFFE003CB98];
      break;
    default:
      result = 0xFFFFFFFFLL;
      break;
  }
  return result;
}

/* ===== smc_entry @ 0x94028948 size 96 ===== */
__int64 __fastcall smc_entry(int a1, _DWORD *a2)
{
  _DWORD *v8; // x9
  _DWORD *v9; // [xsp+10h] [xbp-10h]

  v9 = a2;
  __asm { SMC             #0 }
  v8 = v9;
  *v9 = 1006632960;
  v8[1] = a1;
  v8 += 2;
  *v8 = 0;
  v8[1] = 0;
  return 1006632960;
}

/* ===== smc_entry_thunk @ 0x940289A8 size 8 ===== */
void smc_entry_thunk()
{
  JUMPOUT(0x94028950LL);
}

/* ===== smc_handle_call @ 0x940289B0 size 36 ===== */
__int64 __fastcall smc_handle_call(unsigned __int16 *a1)
{
  __int64 v1; // x1
  __int64 (*v3)(void); // x2

  v1 = *a1;
  if ( (unsigned int)v1 < MEMORY[0xFFFFFFFFE003AB08] && (v3 = *(__int64 (**)(void))(8 * v1 - 536631192)) != nullptr )
    return v3();
  else
    return smc_undefined_thunk();
}

/* ===== smc_undefined_thunk @ 0x940289D4 size 8 ===== */
// attributes: thunk
void smc_undefined_thunk(void)
{
  JUMPOUT(0xFFFFFFFFE0009608LL);
}

/* ===== halt @ 0x94028A08 size 588 ===== */
// write access to const memory has been detected, the output may be wrong!
unsigned __int64 *__fastcall halt(int a1, int a2)
{
  __int64 v9; // x0
  __int64 v10; // x30
  __int64 v11; // x22
  unsigned __int64 StatusReg; // x0
  int v13; // w19
  _DWORD *v14; // x0
  _DWORD *v15; // x0
  unsigned __int64 *result; // x0
  __int64 i; // x19
  _DWORD *v18; // x0
  unsigned __int64 *v19; // x1
  _BYTE v20[32]; // [xsp+60h] [xbp-20h] BYREF
  _QWORD v21[2]; // [xsp+B0h] [xbp+30h] BYREF

  v21[0] = 0;
  v21[1] = 0;
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("HALT: (reason = %d)\n", a2);
  __asm
  {
    MSR             DAIFSet, #2
    MSR             DAIFSet, #1
  }
  while ( a1 != 3 || *(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) == 0 )
    smc_entry(-11, v21);
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("HALT: terminate user thread %s\n", (const char *)(_ReadStatusReg(TPIDR_EL1) + 696));
  v9 = uctx_get_current();
  uctx_destroy(v9);
  uthread_exit(0);
  v11 = v10;
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v13 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
  event_init((__int64)&qword_94067600[6 * v13], 0, 1);
  snprintf(v20, 32, "irq-ns-switch-%d", v13);
  v14 = (_DWORD *)thread_create_simple((__int64)v20, (__int64)sm_irq_thread, (unsigned __int8)v13, 0x1Fu, 4096);
  qword_940675B0[v13] = (__int64)v14;
  if ( v14 != nullptr )
  {
    v14[15] = v13;
    thread_resume(v14);
    snprintf(v20, 32, "idle-ns-switch-%d", v13);
    v15 = (_DWORD *)thread_create_simple((__int64)v20, (__int64)sm_get_stdcall_ret, 0, 1u, 4096);
    qword_940675D8[v13] = (__int64)v15;
    if ( v15 != nullptr )
    {
      v15[15] = v13;
      thread_resume(v15);
      return nullptr;
    }
    panic(v11, "failed to create idle NS switcher thread for cpu %d!\n", v13);
  }
  panic(v11, "failed to create irq NS switcher thread for cpu %d!\n", v13);
  byte_940675A0 = 1;
  __dmb(0xAu);
  for ( i = 0; i != 4; ++i )
  {
    v18 = (_DWORD *)qword_940675B0[i];
    if ( v18 != nullptr )
      thread_resume_full(v18);
    v19 = (unsigned __int64 *)qword_940675D8[i];
    result = v19;
    if ( v19 != nullptr )
      result = thread_resume_full(v19);
  }
  return result;
}

/* ===== sm_init @ 0x94028C54 size 292 ===== */
// write access to const memory has been detected, the output may be wrong!
unsigned __int64 *sm_init()
{
  __int64 v0; // x30
  __int64 v1; // x20
  _DWORD *v2; // x0
  __int64 v4; // x21
  int v5; // w3
  __int64 v6; // x0
  __int64 v7; // [xsp+38h] [xbp+38h] BYREF

  v1 = v0;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  if ( MEMORY[0xFFFFFFFFE005A028] != 0 && MEMORY[0xFFFFFFFFE005A030] != 0 )
  {
    v4 = MEMORY[0xFFFFFFFFE005A028] & 0xFFF;
    v5 = vmm_map(
           -536460256,
           "sm",
           (MEMORY[0xFFFFFFFFE005A030] + 4095LL + v4) & 0xFFFFFFFFFFFFF000LL,
           &v7,
           12,
           MEMORY[0xFFFFFFFFE005A028] & 0xFFFFFFFFFFFFF000LL,
           0,
           48);
    if ( v5 != 0 )
    {
      qword_940675D0 = 0;
      printf("%s:%d: Error mapping boot parameter block: %d\n", "sm_init", 398, v5);
    }
    else
    {
      qword_940675D0 = v7 + v4;
      dword_940675A4 = 1;
    }
  }
  mutex_release((__int64)"xtum");
  v2 = (_DWORD *)thread_create_simple((__int64)"sm-stdcall", (__int64)sm_stdcall_thread, 0, 2u, 4096);
  qword_940675A8 = (__int64)v2;
  if ( v2 != nullptr )
  {
    thread_resume(v2);
    return thread_resume_full(nullptr);
  }
  else
  {
    v6 = panic(v1, "failed to create sm-stdcall thread!\n");
    return (unsigned __int64 *)sm_queue_stdcall(v6);
  }
}

/* ===== sm_queue_stdcall @ 0x94028D78 size 432 ===== */
__int64 __fastcall sm_queue_stdcall(int a1)
{
  __int64 result; // x0
  unsigned __int64 StatusReg; // x0
  int v10; // w25
  unsigned __int64 v11; // x3
  __int64 v12; // [xsp+50h] [xbp+50h] BYREF
  __int64 v13; // [xsp+58h] [xbp+58h]

  v12 = 0;
  v13 = 0;
  while ( 1 )
  {
    __asm { MSR             DAIFSet, #1 }
    smc_entry(a1, &v12);
    __asm { MSR             DAIFClr, #1 }
    result = 1006632963;
    if ( (_DWORD)v12 == 1006632963 )
      return result;
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    if ( (StatusReg & 0x1000000) != 0 )
      StatusReg >>= 8;
    v10 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
    spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    if ( MEMORY[0xFFFFFFFFE003A5B4] != 0 || MEMORY[0xFFFFFFFFE003A5F8] != 0 )
    {
      if ( (_DWORD)v12 == 1006632960 && MEMORY[0xFFFFFFFFE003A5FC] == -1 )
      {
        ++MEMORY[0xFFFFFFFFE003A608];
LABEL_18:
        MEMORY[0xFFFFFFFFE003A5FC] = v10;
        return (__int64)spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
      }
      a1 = -5;
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("%s: cpu %d, std call busy\n", "sm_queue_stdcall", v10);
    }
    else
    {
      if ( (_DWORD)v12 != 1006632960 )
      {
        MEMORY[0xFFFFFFFFE003A600] = v10;
        MEMORY[0xFFFFFFFFE003A5F0] = -7;
        MEMORY[0xFFFFFFFFE003A5E0] = v12;
        MEMORY[0xFFFFFFFFE003A5E8] = v13;
        MEMORY[0xFFFFFFFFE003A608] = 0;
        event_signal(-536631888, 0);
        goto LABEL_18;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
      {
        a1 = -4;
      }
      else
      {
        v11 = _ReadStatusReg(MPIDR_EL1);
        if ( (v11 & 0x1000000) != 0 )
          v11 >>= 8;
        a1 = -4;
        log_printf(
          "%s: cpu %d, unexpected restart, no std call active\n",
          "sm_queue_stdcall",
          (unsigned __int8)v11 | (4 * ((v11 >> 8) & 0xF)));
      }
    }
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
  }
}

/* ===== sm_stdcall_thread @ 0x94028F28 size 164 ===== */
void __noreturn sm_stdcall_thread()
{
  __int64 v0; // x24

  while ( 1 )
  {
    event_wait_timeout(-536631888, 0xFFFFFFFFLL);
    v0 = (*(__int64 (__fastcall **)(__int64))(8LL * (HIBYTE(MEMORY[0xFFFFFFFFE003A5E0]) & 0x3F) - 536631032))(-536631840);
    if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
    {
      spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
      MEMORY[0xFFFFFFFFE003A5F0] = v0;
      MEMORY[0xFFFFFFFFE003A5F8] = 1;
      event_unsignal(-536631888);
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    }
    else
    {
      __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
      MEMORY[0xFFFFFFFFE003A5F0] = v0;
      MEMORY[0xFFFFFFFFE003A5F8] = 1;
      event_unsignal(-536631888);
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
      __asm { MSR             DAIFClr, #2 }
    }
  }
}

/* ===== sm_get_api_version @ 0x94028FCC size 252 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 sm_get_api_version()
{
  char v0; // w21

  v0 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v0 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94067590);
    byte_94067588 = 1;
    printf("%s:%d: lock api version %d\n", "sm_get_api_version", 109, 0);
    spin_unlock((unsigned __int64 *)&qword_94067590);
  }
  else
  {
    v0 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94067590);
    byte_94067588 = 1;
    printf("%s:%d: lock api version %d\n", "sm_get_api_version", 109, 0);
    spin_unlock((unsigned __int64 *)&qword_94067590);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v0 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return 0;
}

/* ===== sm_get_stdcall_ret @ 0x940290C8 size 300 ===== */
void sm_get_stdcall_ret()
{
  unsigned __int64 StatusReg; // x0
  int v7; // w27
  unsigned __int64 v8; // x27
  int v9; // w28

  while ( 1 )
  {
    __asm { MSR             DAIFSet, #2 }
    thread_yield();
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    if ( (StatusReg & 0x1000000) != 0 )
      StatusReg >>= 8;
    v7 = -15;
    if ( MEMORY[0xFFFFFFFFE003A5FC] == ((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF))) )
    {
      v8 = _ReadStatusReg(MPIDR_EL1);
      if ( (v8 & 0x1000000) != 0 )
        v8 >>= 8;
      v9 = (unsigned __int8)v8 | (4 * ((v8 >> 8) & 0xF));
      spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
      if ( MEMORY[0xFFFFFFFFE003A5FC] == v9 )
      {
        MEMORY[0xFFFFFFFFE003A604] = MEMORY[0xFFFFFFFFE003A5FC];
        MEMORY[0xFFFFFFFFE003A5FC] = -1;
        if ( MEMORY[0xFFFFFFFFE003A5F8] != 0 )
        {
          MEMORY[0xFFFFFFFFE003A5F8] = 0;
          v7 = MEMORY[0xFFFFFFFFE003A5F0];
        }
        else if ( (unsigned int)sm_get_api_version() > 1 )
        {
          v7 = -13;
        }
        else if ( MEMORY[0xFFFFFFFFE003A608] != 0 )
        {
          v7 = -5;
        }
        else
        {
          v7 = -3;
        }
      }
      else
      {
        v7 = -7;
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf(
            "%s: stdcallcpu, a%d != curr-cpu %d, l%d, i%d\n",
            "sm_get_stdcall_ret",
            MEMORY[0xFFFFFFFFE003A5FC],
            v9,
            MEMORY[0xFFFFFFFFE003A604],
            MEMORY[0xFFFFFFFFE003A600]);
      }
      spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    }
    sm_queue_stdcall(v7);
    __asm { MSR             DAIFClr, #2 }
  }
}

/* ===== sm_irq_thread @ 0x940291F4 size 180 ===== */
void __fastcall __noreturn sm_irq_thread(int a1)
{
  __int64 *v6; // x23
  unsigned __int64 StatusReg; // x1
  int v8; // w21
  int v9; // w19

  __asm { MSR             DAIFSet, #2 }
  *((_BYTE *)&qword_94067598 + a1) = 1;
  _ReadStatusReg(MPIDR_EL1);
  v6 = &qword_94067600[6 * a1];
  while ( 1 )
  {
    event_wait_timeout((__int64)v6, 0xFFFFFFFFLL);
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    if ( (StatusReg & 0x1000000) != 0 )
      StatusReg >>= 8;
    v8 = -14;
    v9 = (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
    spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    if ( v9 == MEMORY[0xFFFFFFFFE003A5FC] )
    {
      MEMORY[0xFFFFFFFFE003A604] = v9;
      v8 = -3;
      MEMORY[0xFFFFFFFFE003A5FC] = -1;
    }
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    sm_queue_stdcall(v8);
  }
}

/* ===== sm_set_api_version @ 0x940292A8 size 160 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sm_set_api_version(__int64 a1)
{
  unsigned int v1; // w19

  v1 = *(_DWORD *)(a1 + 4);
  spin_lock((unsigned __int64 *)&qword_94067590);
  if ( v1 > 2 )
    v1 = 2;
  dword_940675F8 = v1;
  spin_unlock((unsigned __int64 *)&qword_94067590);
  return v1;
}

/* ===== sm_handle_irq @ 0x94029348 size 260 ===== */
__int64 sm_handle_irq()
{
  unsigned __int64 StatusReg; // x1
  __int64 v1; // x1
  unsigned __int64 v2; // x0
  int v3; // w22
  int v4; // w19

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  v1 = (int)((unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF)));
  if ( *((_BYTE *)&qword_94067598 + v1) != 0 )
  {
    event_signal((__int64)&qword_94067600[6 * v1], 0);
    return 1;
  }
  else
  {
    printf("%s:%d: warning: got ns irq before irq thread is ready\n", "sm_handle_irq", 421);
    v2 = _ReadStatusReg(MPIDR_EL1);
    if ( (v2 & 0x1000000) != 0 )
      v2 >>= 8;
    v3 = -14;
    v4 = (unsigned __int8)v2 | (4 * ((v2 >> 8) & 0xF));
    spin_lock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    if ( v4 == MEMORY[0xFFFFFFFFE003A5FC] )
    {
      MEMORY[0xFFFFFFFFE003A604] = v4;
      MEMORY[0xFFFFFFFFE003A5FC] = -1;
      v3 = -3;
    }
    spin_unlock((unsigned __int64 *)0xFFFFFFFFE003A5A8LL);
    sm_queue_stdcall(v3);
    return 1;
  }
}

/* ===== sm_handle_fiq @ 0x9402944C size 156 ===== */
__int64 sm_handle_fiq()
{
  int v0; // w20
  __int64 result; // x0
  _QWORD v2[2]; // [xsp+20h] [xbp+20h] BYREF

  v2[0] = 0;
  v2[1] = 0;
  if ( (unsigned int)sm_get_api_version() != 0 )
  {
    v0 = 1006632962;
    result = smc_entry(-12, v2);
  }
  else
  {
    v0 = 1006632960;
    result = smc_entry(-3, v2);
  }
  if ( LODWORD(v2[0]) != v0 )
  {
    printf("%s:%d: got bad restart smc %x, expected %x\n", "sm_handle_fiq", 441, LODWORD(v2[0]), v0);
    for ( result = LODWORD(v2[0]); LODWORD(v2[0]) != v0; result = LODWORD(v2[0]) )
      smc_entry(-6, v2);
  }
  return result;
}

/* ===== sm_put_boot_args @ 0x940294E8 size 124 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 sm_put_boot_args()
{
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  printf("%s:%d: WARNING: caller does not own a reference to boot parameters\n", "sm_put_boot_args", 489);
  return mutex_release((__int64)"xtum");
}

/* ===== sm_get_boot_args @ 0x94029564 size 88 ===== */
__int64 sm_get_boot_args()
{
  ((void (*)(void))loc_94028BE4)();
  return 0;
}

/* ===== sm_get_boot_args_null @ 0x940295BC size 8 ===== */
__int64 sm_get_boot_args_null()
{
  return 0;
}

/* ===== smc_entity_dispatch @ 0x940295C4 size 68 ===== */
__int64 __fastcall smc_entity_dispatch(unsigned __int16 *a1)
{
  __int64 (*v1)(void); // x1

  if ( *a1 <= 3u && (v1 = (__int64 (*)(void))qword_9405A848[*a1]) != nullptr )
    return v1();
  else
    return MEMORY[0xFFFFFFFFE0009608]();
}

/* ===== smc_undefined @ 0x94029608 size 184 ===== */
__int64 __fastcall smc_undefined(unsigned int *a1)
{
  unsigned __int64 v2; // x3
  const char *v3; // x4
  int *v4; // x20
  int v5; // w19
  int v6; // t1
  int v7; // w3

  printf("%s:%d: %s\n", "smc_undefined", 78, (const char *)&loc_9404F578);
  v2 = *a1;
  if ( (v2 & 0x80000000) != 0 )
    v3 = "Fastcall";
  else
    v3 = "Stdcall";
  v4 = (int *)(a1 + 1);
  v5 = 0;
  printf(
    "%s:%d: SMC: 0x%x (%s entity %d function 0x%x)\n",
    "smc_undefined",
    78,
    v2,
    v3,
    (v2 >> 24) & 0x3F,
    (unsigned __int16)v2);
  do
  {
    v6 = *v4++;
    v7 = v5++;
    printf("%s:%d: param%d: 0x%x\n", "smc_undefined", 78, v7, v6);
  }
  while ( v5 != 3 );
  return 0xFFFFFFFFLL;
}

/* ===== smc_restart_stdcall @ 0x940296C0 size 184 ===== */
__int64 __fastcall smc_restart_stdcall(unsigned int *a1)
{
  unsigned __int64 v2; // x3
  const char *v3; // x4
  int *v4; // x20
  int v5; // w19
  int v6; // t1
  int v7; // w3

  printf("%s:%d: %s\n", "smc_restart_stdcall", 85, "Unexpected stdcall restart!");
  v2 = *a1;
  if ( (v2 & 0x80000000) != 0 )
    v3 = "Fastcall";
  else
    v3 = "Stdcall";
  v4 = (int *)(a1 + 1);
  v5 = 0;
  printf(
    "%s:%d: SMC: 0x%x (%s entity %d function 0x%x)\n",
    "smc_restart_stdcall",
    85,
    v2,
    v3,
    (v2 >> 24) & 0x3F,
    (unsigned __int16)v2);
  do
  {
    v6 = *v4++;
    v7 = v5++;
    printf("%s:%d: param%d: 0x%x\n", "smc_restart_stdcall", 85, v7, v6);
  }
  while ( v5 != 3 );
  return -4;
}

/* ===== sm_intc_fiq_handler @ 0x94029778 size 24 ===== */
__int64 sm_intc_fiq_handler()
{
  sm_intc_fiq_exit();
  return 1;
}

/* ===== timer_is_pending @ 0x94029790 size 32 ===== */
__int64 __fastcall timer_is_pending(__int64 a1)
{
  if ( timer_is_empty(*(_DWORD *)(a1 + 4)) )
    return 0;
  else
    return -1;
}

/* ===== sm_get_version @ 0x940297B0 size 76 ===== */
unsigned __int64 __fastcall sm_get_version(__int64 a1)
{
  int v1; // w19
  unsigned __int64 result; // x0

  v1 = *(_DWORD *)(a1 + 4);
  result = strlen(-536621880);
  if ( v1 != -1 )
  {
    if ( result <= v1 )
      return -2;
    else
      return *(unsigned __int8 *)(v1 - 536621880LL);
  }
  return result;
}

/* ===== call_init_hooks_8 @ 0x940297FC size 36 ===== */
__int64 call_init_hooks_8()
{
  call_init_hooks(8, 1u, 0xFFFFFFFF);
  return 0;
}

/* ===== call_init_hooks_4 @ 0x94029820 size 36 ===== */
__int64 call_init_hooks_4()
{
  call_init_hooks(4, 1u, 0xFFFFFFFF);
  return 0;
}

/* ===== sm_handle_fiq_simple @ 0x94029844 size 24 ===== */
__int64 sm_handle_fiq_simple()
{
  return (int)sm_intc_fiq_enter();
}

/* ===== sm_register_entity_ex @ 0x9402985C size 228 ===== */
__int64 __fastcall sm_register_entity_ex(unsigned int a1, _QWORD *a2)
{
  unsigned int v4; // w21
  __int64 v6; // x0

  if ( a1 <= 0x3F )
  {
    if ( a1 - 5 <= 0x2A )
      return 4294967279LL;
    if ( a2 != nullptr )
    {
      if ( *a2 == 0 && a2[1] == 0 )
        return 4294967289LL;
      v4 = -14;
      mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
      if ( *(_QWORD *)(8LL * a1 - 536631736) == -536832504 && *(_QWORD *)(8LL * a1 - 536631032) == -536832504 )
      {
        if ( *a2 != 0 )
          *(_QWORD *)(8LL * a1 - 536631736) = *a2;
        v6 = a2[1];
        v4 = 0;
        if ( v6 != 0 )
          *(_QWORD *)(8LL * a1 - 536631032) = v6;
      }
      mutex_release((__int64)"xtum");
      return v4;
    }
  }
  return 4294967288LL;
}

/* ===== sm_decode_ns_memory_attr @ 0x94029940 size 284 ===== */
__int64 __fastcall sm_decode_ns_memory_attr(_QWORD *a1, __int64 *a2, int *a3)
{
  int v6; // w3
  __int64 v7; // x3
  int v8; // w1
  __int64 result; // x0

  if ( a1 == nullptr )
    return 4294967288LL;
  printf(
    "%s:%d: raw=0x%llx: pa=0x%llx: mair=0x%x, sharable=0x%x\n",
    "sm_decode_ns_memory_attr",
    89,
    *a1,
    *a1 & 0xFFFFFFFFF000LL,
    (unsigned __int8)BYTE6(*a1),
    (*a1 >> 8) & 3);
  if ( a2 != nullptr )
    *a2 = *a1 & 0xFFFFFFFFF000LL;
  if ( a3 == nullptr )
    return 0;
  v6 = (unsigned __int8)BYTE6(*a1);
  if ( v6 == 68 )
  {
    v8 = 1;
  }
  else
  {
    if ( v6 != 255 )
    {
      printf("%s:%d: Unsupported memory attr 0x%x\n", "sm_decode_ns_memory_attr", 112, v6);
      return 4294967272LL;
    }
    v7 = (*a1 >> 8) & 3LL;
    if ( v7 != 3 )
    {
      printf("%s:%d: Unsupported sharable attr 0x%x\n", "sm_decode_ns_memory_attr", 119, v7);
      return 4294967272LL;
    }
    v8 = 0;
  }
  if ( (*a1 & 0x40LL) != 0 )
    v8 |= 4u;
  result = 0;
  if ( (*a1 & 0x80LL) != 0 )
    v8 |= 8u;
  *a3 = v8 | 0x30;
  return result;
}

/* ===== sm_decode_ns_mem_args @ 0x94029A5C size 268 ===== */
__int64 __fastcall sm_decode_ns_mem_args(unsigned int *a1, __int64 *a2, _DWORD *a3, int *a4)
{
  __int64 v4; // x30
  __int64 result; // x0
  unsigned __int64 v8; // [xsp+48h] [xbp+28h] BYREF

  if ( a1 != nullptr )
  {
    v8 = a1[1] | ((unsigned __int64)a1[2] << 32);
    result = sm_decode_ns_memory_attr(&v8, a2, a4);
    if ( (_DWORD)result == 0 && a3 != nullptr )
      *a3 = a1[3];
  }
  else
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/sm/ns_mem.c", 144, "args");
    memcpy(-536485312, "VerifiedBoot-LOCK", 18);
    MEMORY[0xFFFFFFFFE005F240] = 64;
    if ( (unsigned int)sm_register_entity_ex(0x34u, &qword_9405AB20) != 0 )
      printf("trusty error register entity: %d\n", 52);
    result = sm_register_entity_ex(2u, qword_9405AB10);
    if ( (_DWORD)result != 0 )
      return printf("trusty error register entity: %d\n", 2);
  }
  return result;
}

/* ===== aes_cbc_encrypt_test @ 0x94029B68 size 564 ===== */
__int64 __fastcall aes_cbc_encrypt_test(__int64 a1, unsigned int a2)
{
  __int64 v4; // x0
  __int64 v5; // x20
  int v6; // w0
  unsigned int v7; // w19
  int v9; // w0
  unsigned int v10; // w1
  _QWORD v11[4]; // [xsp+40h] [xbp+40h] BYREF
  _BYTE v12[352]; // [xsp+60h] [xbp+60h] BYREF

  strcpy((char *)v11, " !\"#$%&'()*+,-./");
  BYTE1(v11[2]) = 0;
  WORD1(v11[2]) = 0;
  HIDWORD(v11[2]) = 0;
  v11[3] = 0;
  v4 = malloc(a2);
  v5 = v4;
  if ( v4 != 0 )
  {
    memset(v4, 0, a2);
    v6 = sprd_aes_init(0, 0, v12, v11, 0, 16, 0, 0);
    if ( v6 != 0 )
    {
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      {
        v7 = -65521;
        log_printf("lihj : aes_cbc encrypt test init FAILED [%d]\n", v6);
LABEL_5:
        free(v5);
        return v7;
      }
    }
    else
    {
      v9 = sprd_aes_process(v12, a1, v5, a2);
      if ( v9 != 0 )
      {
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        {
          v7 = -65521;
          log_printf("lihj : aes_cbc encrypt test process FAILED [%d]\n", v9);
          goto LABEL_5;
        }
      }
      else
      {
        v7 = sprd_aes_final(v12, 0, 0, 0, 0, 0);
        if ( v7 == 0 )
        {
          memcpy(a1, v5, a2);
          goto LABEL_5;
        }
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        {
          v10 = v7;
          v7 = -65521;
          log_printf("lihj : aes_cbc encrypt test final FAILED [%d]\n", v10);
          goto LABEL_5;
        }
      }
    }
    free(v5);
    return 4294901775LL;
  }
  else
  {
    v7 = -65526;
    if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
      goto LABEL_5;
    log_printf("Cann't malloc memory for pt !\n");
    free(0);
    return 4294901770LL;
  }
}

/* ===== save_uboot_key @ 0x94029D9C size 620 ===== */
__int64 __fastcall save_uboot_key(unsigned int a1, unsigned __int8 *a2, unsigned int a3)
{
  __int64 result; // x0
  __int64 v7; // x1
  unsigned __int8 *v8; // x19
  __int64 v9; // x19
  __int64 v10; // x19
  __int64 v11; // x19

  switch ( a1 )
  {
    case 2u:
      v7 = MEMORY[0xFFFFFFFFE003CB98];
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("hwkey hash from uboot is:\n");
        v7 = MEMORY[0xFFFFFFFFE003CB98];
      }
      v8 = a2;
      do
      {
        if ( v7 > 1 )
        {
          log_printf("%02x", *v8);
          v7 = MEMORY[0xFFFFFFFFE003CB98];
        }
        ++v8;
      }
      while ( v8 != a2 + 32 );
      goto LABEL_14;
    case 1u:
      v7 = MEMORY[0xFFFFFFFFE003CB98];
      if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
      {
        if ( a3 == 0 )
          goto LABEL_5;
      }
      else
      {
        log_printf("public key from uboot is:\n");
        v7 = MEMORY[0xFFFFFFFFE003CB98];
        if ( a3 == 0 )
          goto LABEL_14;
      }
      v9 = 0;
      do
      {
        if ( v7 > 1 )
        {
          log_printf("%02x", a2[v9]);
          v7 = MEMORY[0xFFFFFFFFE003CB98];
        }
        ++v9;
      }
      while ( a3 > (unsigned int)v9 );
      goto LABEL_14;
    case 4u:
      v7 = MEMORY[0xFFFFFFFFE003CB98];
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("device state from uboot is:\n");
        v7 = MEMORY[0xFFFFFFFFE003CB98];
        if ( a3 == 0 )
          goto LABEL_14;
      }
      else if ( a3 == 0 )
      {
        goto LABEL_5;
      }
      v10 = 0;
      do
      {
        if ( v7 > 1 )
        {
          log_printf("%02x", a2[v10]);
          v7 = MEMORY[0xFFFFFFFFE003CB98];
        }
        ++v10;
      }
      while ( a3 > (unsigned int)v10 );
      goto LABEL_14;
    default:
      break;
  }
  if ( a1 != 5 )
    goto LABEL_5;
  v7 = MEMORY[0xFFFFFFFFE003CB98];
  if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
  {
    if ( a3 == 0 )
      goto LABEL_5;
    goto LABEL_36;
  }
  log_printf("chip uid from uboot(id=%d) len=%d:\n", 5, a3);
  v7 = MEMORY[0xFFFFFFFFE003CB98];
  if ( a3 != 0 )
  {
LABEL_36:
    v11 = 0;
    do
    {
      if ( v7 > 1 )
      {
        log_printf("%02x ", a2[v11]);
        v7 = MEMORY[0xFFFFFFFFE003CB98];
      }
      ++v11;
    }
    while ( a3 > (unsigned int)v11 );
  }
LABEL_14:
  if ( v7 > 1 )
    log_printf("\n");
LABEL_5:
  memcpy(4100LL * a1 - 536501712, a2, a3);
  *(_DWORD *)(4100LL * a1 - 536497616) = a3;
  result = MEMORY[0xFFFFFFFFE003CB98];
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    return log_printf("key[%d] data has been saved!\n", a1);
  return result;
}

/* ===== process_sip_call @ 0x9402A008 size 1756 ===== */
__int64 __fastcall process_sip_call(_DWORD *a1)
{
  __int64 v2; // x19
  unsigned int v4; // w22
  unsigned int v5; // w21
  int v6; // w0
  int v7; // w21
  unsigned int v8; // w23
  unsigned int v9; // w22
  int v10; // w0
  unsigned int v11; // w23
  unsigned int v12; // w22
  int v13; // w0
  unsigned int v14; // w23
  unsigned int v15; // w22
  int v16; // w0
  __int64 v17; // x21
  unsigned int v18; // w0
  char v19; // w21
  __int64 v20; // x0
  __int64 v21; // x21
  unsigned int v22; // w0
  char v23; // w21
  __int64 v24; // x0
  __int64 v25; // [xsp+58h] [xbp+58h] BYREF
  unsigned __int8 *v26[8]; // [xsp+60h] [xbp+60h] BYREF

  if ( a1 != nullptr )
  {
    if ( *a1 == -2113863934 )
    {
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("have got sip smc all from uboot###\n");
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          log_printf(" args->params[0] is 0x%x. ###\n", a1[1]);
      }
      switch ( a1[1] )
      {
        case 1:
          return process_verify_img_smc(a1);
        case 3:
          return process_get_socid_smc(a1);
        case 8:
          return process_save_hubkey_smc(a1);
        case 9:
          return (int)sprd_fw_null(a1);
        case 0xA:
          return process_get_lcs_smc(a1);
        case 0xB:
          return process_set_rma_smc(a1);
        case 0x20:
          return process_vboot_verify_smc(a1);
        case 0x21:
          return process_set_version_smc(a1);
        case 0x22:
          return process_rpmb_size_smc(a1);
        case 0x23:
          return process_rpmb_key_smc(a1);
        case 0x30:
          v2 = 0xFFFFFFFFLL;
          if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            log_printf("enter process_sip_call FUNCTYPE_SET_BINDING_DATA !\n");
          return v2;
        case 0x31:
          if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
          {
            v26[0] = nullptr;
            v8 = a1[2];
            v9 = a1[3];
          }
          else
          {
            log_printf("enter process_sip_call FUNCTYPE_CRYPTO_DATA !\n");
            v26[0] = nullptr;
            v8 = a1[2];
            v9 = a1[3];
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            {
              log_printf("from uboot smc...addr:0x%x len:0x%x\n", v8, v9);
              if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              {
                log_printf("from uboot smc...p[0]:0x%x p1:0x%x p2:0x%x\n", a1[1], a1[2], a1[3]);
                if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
                  log_printf("from uboot smc...addr:0x%x len:0x%x\n", v8, v9);
              }
            }
          }
          v10 = sprd_iomap("sprdsec", v8, (v9 & 0xFFFFF000) + 4096, 48, v26);
          v2 = v10;
          if ( v10 != 0 )
            goto LABEL_31;
          v2 = 0;
          aes_cbc_encrypt_test((__int64)v26[0], v9);
          v7 = sprd_iounmap(v26[0], v9);
          if ( v7 == 0 )
            return v2;
          goto LABEL_17;
        case 0x32:
          if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
          {
            v25 = 0;
            v11 = a1[2];
            v12 = a1[3];
          }
          else
          {
            log_printf("enter process_sip_call FUNCTYPE_CHECK_PWD !\n");
            v25 = 0;
            v11 = a1[2];
            v12 = a1[3];
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            {
              log_printf("from uboot smc...addr:0x%x len:0x%x\n", v11, v12);
              if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              {
                log_printf("from uboot smc...p[0]:0x%x p1:0x%x p2:0x%x\n", a1[1], a1[2], a1[3]);
                if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
                  log_printf("from uboot smc...addr:0x%x len:0x%x\n", v11, v12);
              }
            }
          }
          v13 = sprd_iomap("sprdsec", v11, (v12 & 0xFFFFF000) + 4096, 48, &v25);
          v2 = v13;
          if ( v13 != 0 )
          {
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("can not map phy addr, ret:%d\n", v13);
            return v2;
          }
          v21 = v25;
          memset(v26, 0, 64);
          v22 = strlen("ab#AB");
          memcpy(v26, "ab#AB", v22);
          aes_cbc_encrypt_test(v21, 0x40u);
          aes_cbc_encrypt_test((__int64)v26, 0x40u);
          if ( (unsigned int)memcmp(v21, v26, 64) != 0 )
          {
            v23 = 1;
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("password is incorrect.\n");
          }
          else
          {
            v23 = 0;
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("check password passed.\n");
          }
          v2 = 0;
          v24 = v25;
          *(_BYTE *)(v25 + 128) = v23;
          v7 = sprd_iounmap(v24, v12);
          if ( v7 != 0 )
            goto LABEL_17;
          return v2;
        case 0x33:
          if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
          {
            v25 = 0;
            v14 = a1[2];
            v15 = a1[3];
          }
          else
          {
            log_printf("enter process_sip_call FUNCTYPE_CHECK_LOCK_STATUS !\n");
            v25 = 0;
            v14 = a1[2];
            v15 = a1[3];
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            {
              log_printf("from uboot smc...addr:0x%x len:0x%x\n", v14, v15);
              if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              {
                log_printf("from uboot smc...p[0]:0x%x p1:0x%x p2:0x%x\n", a1[1], a1[2], a1[3]);
                if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
                  log_printf("from uboot smc...addr:0x%x len:0x%x\n", v14, v15);
              }
            }
          }
          v16 = sprd_iomap("sprdsec", v14, (v15 & 0xFFFFF000) + 4096, 48, &v25);
          v2 = v16;
          if ( v16 != 0 )
            goto LABEL_31;
          v17 = v25;
          memset(v26, 0, 64);
          v18 = strlen("VerifiedBoot-UNLOCK");
          memcpy(v26, "VerifiedBoot-UNLOCK", v18);
          aes_cbc_encrypt_test((__int64)v26, 0x40u);
          if ( (unsigned int)memcmp(v17, v26, 64) != 0 )
          {
            v19 = 0;
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("unlock status isn't matched, return lock.\n");
          }
          else
          {
            v19 = 1;
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("unlock status is matched, return unlock.\n");
          }
          v2 = 0;
          v20 = v25;
          *(_BYTE *)(v25 + 64) = v19;
          v7 = sprd_iounmap(v20, v15);
          if ( v7 != 0 )
            goto LABEL_17;
          return v2;
        case 0x34:
          return process_vboot_verify_sn_smc(a1);
        case 0x35:
          return process_config_os_version_smc(a1);
        case 0x40:
          v26[0] = nullptr;
          v4 = a1[2];
          v5 = a1[3];
          if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            log_printf("from uboot smc(set chip uid)...addr:0x%x len:0x%x\n", v4, v5);
          v6 = sprd_iomap("sprdsec", v4, (v5 & 0xFFFFF000) + 4096, 48, v26);
          v2 = v6;
          if ( v6 != 0 )
          {
LABEL_31:
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("can not map phy addr 1 , ret:%d\n", v2);
          }
          else
          {
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
              log_printf("get cpu id: 0x%x 0x%x\n", *(_DWORD *)v26[0], *((_DWORD *)v26[0] + 1));
            v2 = 0;
            save_uboot_key(5u, v26[0], v5);
            v7 = sprd_iounmap(v26[0], v5);
            if ( v7 != 0 )
            {
LABEL_17:
              if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
                log_printf("can not unmap virt addr, ret:%d\n", v7);
              v2 = v7;
            }
          }
          break;
        default:
          return 0xFFFFFFFFLL;
      }
    }
    else
    {
      return 0xFFFFFFFFLL;
    }
  }
  else
  {
    v2 = -1;
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("args is null###\n");
  }
  return v2;
}

/* ===== process_uboot_key_smc @ 0x9402A6E4 size 264 ===== */
__int64 __fastcall process_uboot_key_smc(unsigned int a1, unsigned int a2, unsigned int a3)
{
  int v6; // w19
  __int64 result; // x0
  unsigned __int8 *v8; // [xsp+48h] [xbp+48h] BYREF

  v8 = nullptr;
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("from uboot smc...addr:0x%x len:0x%x\n", a1, a2);
  v6 = vmm_map(-536460256, "sprdsec", 4096, &v8, 12, a1, 0, 48);
  if ( v6 != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("can not map phy addr, ret:%d\n", v6);
    return v6;
  }
  save_uboot_key(a3, v8, a2);
  v6 = vmm_free_region(-536460256, v8);
  result = 0;
  if ( v6 != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("can not unmap virt addr, ret:%d\n", v6);
    return v6;
  }
  return result;
}

/* ===== process_uboot_key @ 0x9402A7EC size 164 ===== */
__int64 __fastcall process_uboot_key(_DWORD *a1)
{
  __int64 v1; // x19

  if ( a1 == nullptr )
  {
    v1 = -1;
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("args is null###\n", 0);
    return v1;
  }
  if ( *a1 == 872415262 )
    return process_uboot_key_smc(a1[2], a1[3], 1u);
  if ( *a1 != 872415263 )
    return 0xFFFFFFFFLL;
  return process_uboot_key_smc(a1[2], a1[3], 2u);
}

/* ===== install_stdin_handler @ 0x9402A890 size 76 ===== */
__int64 install_stdin_handler()
{
  __int64 result; // x0

  result = trusty_install_handler(0, qword_9405AB30);
  if ( (_DWORD)result != 0 && MEMORY[0xFFFFFFFFE003CB98] > 1 )
    return log_printf("can not install std in handler: %d\n", result);
  return result;
}

/* ===== sys_get_uboot_data @ 0x9402A8DC size 920 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sys_get_uboot_data(__int64 a1, int a2, unsigned int a3)
{
  unsigned int v3; // w19
  __int64 result; // x0
  __int64 v6; // x0
  __int64 i; // x19
  int v8; // w0
  int v9; // w0
  _QWORD v10[33]; // [xsp+48h] [xbp+48h] BYREF

  if ( a3 != 0 )
  {
    switch ( a2 )
    {
      case 1:
        if ( MEMORY[0xFFFFFFFFE005C234] != 0 )
        {
          copy_to_user(a3, -536497612, MEMORY[0xFFFFFFFFE005C234]);
          return (unsigned int)MEMORY[0xFFFFFFFFE005C234];
        }
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          log_printf("there is no public key yet, give you fake data\n");
        memset(v10, 255, 264);
        copy_to_user(a3, v10, 264);
        return 264;
      case 2:
        if ( MEMORY[0xFFFFFFFFE005D238] == 0 )
          return 0xFFFFFFFFLL;
        copy_to_user(a3, -536493512, MEMORY[0xFFFFFFFFE005D238]);
        return (unsigned int)MEMORY[0xFFFFFFFFE005D238];
      case 3:
        if ( MEMORY[0xFFFFFFFFE005E23C] != 0 )
          goto LABEL_14;
        v10[0] = 0;
        v8 = vmm_map(-536460256, "sprdrng", 4096, v10, 12, 2516578304LL, 0, 16);
        if ( v8 != 0 )
        {
          if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            log_printf("can not map sec addr, ret:%d\n", v8);
          return 0xFFFFFFFFLL;
        }
        memcpy(-536489412, v10[0], 4096);
        MEMORY[0xFFFFFFFFE005E23C] = 4096;
        v9 = vmm_free_region(-536460256, v10[0]);
        if ( v9 != 0 )
        {
          if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            log_printf("can not unmap virt addr, ret:%d\n", v9);
          return 0xFFFFFFFFLL;
        }
LABEL_14:
        dword_940676C0 = 1;
        v6 = MEMORY[0xFFFFFFFFE003CB98];
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
        {
          log_printf("RNG  from kernel is:\n");
          v6 = MEMORY[0xFFFFFFFFE003CB98];
        }
        for ( i = -536489412; i != -536489380; ++i )
        {
          if ( v6 > 1 )
          {
            log_printf("%02x", *(unsigned __int8 *)i);
            v6 = MEMORY[0xFFFFFFFFE003CB98];
          }
        }
        if ( v6 > 1 )
          log_printf("\n");
        copy_to_user(a3, -536489412, 32);
        result = 32;
        break;
      case 5:
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          log_printf("SEC_CHIP_UID(%d) len: %d\n", 5, MEMORY[0xFFFFFFFFE0060244]);
        if ( MEMORY[0xFFFFFFFFE0060244] == 0 )
          return 0xFFFFFFFFLL;
        copy_to_user(a3, -536481212, MEMORY[0xFFFFFFFFE0060244]);
        v3 = MEMORY[0xFFFFFFFFE0060244];
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          log_printf("got chip id(len=%d)\n", MEMORY[0xFFFFFFFFE0060244]);
        return v3;
      case 6:
        if ( MEMORY[0xFFFFFFFFE0061248] == 0 )
          return 0xFFFFFFFFLL;
        copy_to_user(a3, -536477112, MEMORY[0xFFFFFFFFE0061248]);
        return (unsigned int)MEMORY[0xFFFFFFFFE0061248];
      default:
        return (unsigned int)-24;
    }
  }
  else
  {
    return (unsigned int)-8;
  }
  return result;
}

/* ===== ta_manager_init @ 0x9402AC74 size 340 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 ta_manager_init()
{
  printf("initializing ta_manager enter\n");
  qword_94067758 = (__int64)&qword_94067758;
  dword_940677A0 = 0;
  qword_94067760 = (__int64)&qword_94067758;
  event_init((__int64)qword_94067728, 0, 1);
  event_init((__int64)qword_940676F8, 0, 1);
  event_init((__int64)qword_940676C8, 0, 1);
  event_init((__int64)qword_940678B8, 0, 1);
  qword_940677D0 = (__int64)&qword_940677D0;
  qword_94067868 = (__int64)&qword_94067868;
  qword_940677D8 = (__int64)&qword_940677D0;
  qword_94067870 = (__int64)&qword_94067868;
  mutex_init((__int64)qword_94067768);
  mutex_init((__int64)qword_940677E0);
  mutex_init((__int64)qword_94067878);
  qword_940677B8 = thread_create_simple((__int64)"ta_manager", (__int64)ta_manager_thread_fun, 0, 0x10u, 4096);
  qword_940677C8 = thread_create_simple((__int64)"ta_manager_unload", (__int64)ta_manager_unload_thread_fun, 0, 0x10u, 4096);
  printf("initializing ta_manager thread_resume\n");
  return 0;
}

/* ===== ta_manager_unload_thread_fun @ 0x9402ADC8 size 752 ===== */
// write access to const memory has been detected, the output may be wrong!
void __noreturn ta_manager_unload_thread_fun()
{
  __int64 v0; // x1
  __int64 v1; // x27
  __int64 v2; // x19
  int v3; // w21
  unsigned int v4; // w21
  __int64 v5; // x0
  __int64 v6; // x1
  _QWORD *v7; // x2
  __int64 v8; // [xsp+70h] [xbp+70h]
  __int64 v9; // [xsp+88h] [xbp+88h] BYREF

  v8 = 0;
  printf("%s:%d: ta_manager_unload_thread_fun enter\n", "ta_manager_unload_thread_fun", 600);
LABEL_2:
  event_wait_timeout((__int64)qword_940676F8, 0xFFFFFFFFLL);
  event_unsignal((__int64)qword_940676F8);
  while ( 1 )
  {
LABEL_3:
    mutex_acquire_timeout((__int64)qword_94067878, 0xFFFFFFFFLL);
    if ( &qword_94067868 == nullptr )
    {
LABEL_15:
      mutex_release((__int64)qword_94067878);
      goto LABEL_2;
    }
    while ( 1 )
    {
      v0 = MEMORY[8];
      *MEMORY[8] = MEMORY[0];
      *(_QWORD *)(MEMORY[0] + 8LL) = v0;
      MEMORY[8] = 0;
      MEMORY[0] = 0;
      mutex_release((__int64)qword_94067878);
      printf("%s:%d: look up %s\n", "ta_manager_unload_thread_fun", 614, 16);
      mutex_acquire_timeout((__int64)qword_94067768, 0xFFFFFFFFLL);
      v1 = 0;
      if ( &qword_94067758 != nullptr )
      {
        while ( 1 )
        {
          if ( (unsigned int)strncmp(v1 + 40, 16, 64) == 0 )
            goto LABEL_9;
          if ( *(__int64 **)(v1 + 8) == &qword_94067758 )
            break;
          v1 = *(_QWORD *)(v1 + 8);
        }
        mutex_release((__int64)qword_94067768);
        free(0);
      }
      else
      {
        v1 = v8;
LABEL_9:
        mutex_release((__int64)qword_94067768);
        free(0);
        if ( v1 == 0 )
        {
          v8 = 0;
          printf("%s:%d: static TA\n", "ta_manager_unload_thread_fun", 626);
          goto LABEL_3;
        }
      }
      v2 = ((__int64 (__fastcall *)(_QWORD))loc_9402EB7C)(*(_QWORD *)(v1 + 16));
      v3 = ((__int64 (*)(void))loc_9402EBD8)();
      if ( v3 > (int)uctx_get_handle_count(v2) )
        break;
      v4 = 0;
      v5 = *(_QWORD *)(*(_QWORD *)(v1 + 16) + 80LL);
      byte_940677C0 = 1;
      dword_94067860 = *(_DWORD *)(v5 + 104);
      while ( 1 )
      {
        v6 = v4++;
        if ( (unsigned int)uctx_handle_put(v2, v6, &v9) == 0 )
          break;
        if ( v4 == 10 )
          goto LABEL_14;
      }
      handle_decref(v9);
LABEL_14:
      v8 = 0;
      printf("%s:%d: unload_thread wait for %d\n", "ta_manager_unload_thread_fun", 649, 0);
      event_wait_timeout((__int64)qword_940676C8, 0xFFFFFFFFLL);
      byte_940677C0 = 0;
      event_unsignal((__int64)qword_940676C8);
      uctx_destroy(v2);
      mutex_acquire_timeout((__int64)qword_94067768, 0xFFFFFFFFLL);
      v7 = *(_QWORD **)(v1 + 8);
      *v7 = *(_QWORD *)v1;
      *(_QWORD *)(*(_QWORD *)v1 + 8LL) = v7;
      *(_QWORD *)(v1 + 8) = 0;
      *(_QWORD *)v1 = 0;
      dword_940677A0 = -1;
      mutex_release((__int64)qword_94067768);
      free(*(_QWORD *)(v1 + 24));
      free(*(_QWORD *)(*(_QWORD *)(v1 + 16) + 88LL));
      free(*(_QWORD *)(*(_QWORD *)(v1 + 16) + 96LL));
      printf(
        "%s:%d: will free trusty_app path %s\n",
        "ta_manager_unload_thread_fun",
        663,
        (const char *)(v1 + 40));
      free(v1);
      mutex_acquire_timeout((__int64)qword_94067878, 0xFFFFFFFFLL);
      if ( &qword_94067868 == nullptr )
        goto LABEL_15;
    }
    v8 = v1;
    printf("%s:%d: list_length %d\n", "ta_manager_unload_thread_fun", 635, v3);
  }
}

/* ===== ta_manager_send_response @ 0x9402B0B8 size 148 ===== */
__int64 __fastcall ta_manager_send_response(__int64 a1, int a2, __int64 a3, unsigned int a4)
{
  __int64 v4; // x19
  __int64 result; // x0
  int v6; // [xsp+28h] [xbp+28h] BYREF
  _QWORD v7[4]; // [xsp+30h] [xbp+30h] BYREF
  int v8; // [xsp+50h] [xbp+50h] BYREF
  _QWORD *v9; // [xsp+58h] [xbp+58h]
  int v10; // [xsp+60h] [xbp+60h]
  __int64 v11; // [xsp+68h] [xbp+68h]

  v6 = a2 | 1;
  v7[2] = a3;
  v7[0] = &v6;
  v8 = 2;
  v7[1] = 4;
  v7[3] = a4;
  v9 = v7;
  v10 = 0;
  v11 = 0;
  v4 = (int)sys_msg_send(a1, &v8);
  result = 0;
  if ( v4 < 0 )
  {
    printf("%s:%d: failed (%ld) to send_msg\n", "ta_manager_send_response", 150, v4);
    return v4;
  }
  return result;
}

/* ===== ta_manager_thread_fun @ 0x9402B14C size 2892 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 ta_manager_thread_fun()
{
  unsigned int v0; // w24
  _QWORD *v1; // x25
  __int64 *v2; // x26
  unsigned int v3; // w27
  __int64 v4; // x28
  __int64 v5; // x30
  int *v6; // x21
  __int64 v7; // x19
  _QWORD *v8; // x21
  __int64 v9; // x0
  int v11; // w3
  int v12; // w4
  const char *v13; // x0
  const char *v14; // x1
  __int64 v15; // x2
  int v16; // w3
  int v17; // w1
  int v18; // w3
  __int64 v19; // x3
  char v20; // w3
  unsigned int v21; // w5
  int v22; // w4
  int v23; // w3
  int *v24; // x6
  unsigned int v25; // w3
  __int64 v26; // x0
  __int64 v27; // x2
  int v28; // w0
  int v29; // w3
  int v30; // w1
  int v31; // w1
  unsigned int v32; // w3
  __int64 v33; // x0
  unsigned int v34; // w0
  __int64 *i; // x3
  _QWORD *v36; // x1
  _QWORD *v37; // x2
  __int64 v38; // x0
  int v39; // w2
  __int64 v40; // x3
  _QWORD *v41; // x3
  _QWORD *v42; // x2
  __int64 v43; // x0
  unsigned int v44; // w3
  __int64 v45; // [xsp+70h] [xbp+70h]
  __int64 v46; // [xsp+80h] [xbp+80h]
  __int64 v47; // [xsp+80h] [xbp+80h]
  __int64 *v48; // [xsp+88h] [xbp+88h]
  __int64 v49; // [xsp+88h] [xbp+88h]
  _DWORD *v50; // [xsp+90h] [xbp+90h]
  int *v51; // [xsp+98h] [xbp+98h]
  __int64 v52; // [xsp+98h] [xbp+98h]
  _QWORD *v53; // [xsp+98h] [xbp+98h]
  __int64 v54; // [xsp+A0h] [xbp+A0h]
  int v55; // [xsp+A0h] [xbp+A0h]
  int v56; // [xsp+A0h] [xbp+A0h]
  __int64 v57; // [xsp+A0h] [xbp+A0h]
  __int64 v58; // [xsp+A0h] [xbp+A0h]
  int v59; // [xsp+A0h] [xbp+A0h]
  int v60; // [xsp+A0h] [xbp+A0h]
  __int64 v61; // [xsp+A8h] [xbp+A8h]
  unsigned int v62; // [xsp+B8h] [xbp+B8h] BYREF
  unsigned int v63; // [xsp+BCh] [xbp+BCh]
  __int64 v64; // [xsp+C0h] [xbp+C0h] BYREF
  __int64 v65; // [xsp+C8h] [xbp+C8h] BYREF
  unsigned int v66; // [xsp+D0h] [xbp+D0h]
  int v67; // [xsp+D4h] [xbp+D4h]
  _QWORD v68[2]; // [xsp+E0h] [xbp+E0h] BYREF
  int v69; // [xsp+F0h] [xbp+F0h] BYREF
  _QWORD *v70; // [xsp+F8h] [xbp+F8h]
  int v71; // [xsp+100h] [xbp+100h]
  __int64 v72; // [xsp+108h] [xbp+108h]

  v6 = (int *)"ta_manager_thread_fun";
  v7 = v5;
  printf("%s:%d: ta_manager_thread_fun enter\n", "ta_manager_thread_fun", 541);
  qword_9405ABA0 = calloc(1, 8LL * MEMORY[0xFFFFFFFFE006124C]);
  panic(v7, "allocate app local storage failed\n");
LABEL_79:
  v54 = -5;
  printf("%s:%d: ta_manager_wait_load calloc(%d) failed!\n", "ta_manager_wait_load", 222, 68);
  v16 = -5;
LABEL_22:
  printf("%s:%d: ta_manager_handle_request failed %d!\n", "ta_manager_handle_msg", 458, v16);
  v17 = *v6;
  v65 = v54;
  v18 = ta_manager_send_response(v64, v17, (__int64)&v65, 8u);
  v12 = v18;
  if ( v18 < 0 )
  {
    v55 = v18;
    printf("%s:%d: ta_manager_send_error_response failed %d!\n", "ta_manager_handle_msg", 461, v18);
    v12 = v55;
  }
LABEL_24:
  v56 = v12;
  free(v6);
  ipc_msg_free(v64, v63);
  v19 = v56;
  if ( v56 == 0 )
  {
LABEL_25:
    v20 = v67;
    goto LABEL_26;
  }
LABEL_31:
  printf("%s:%d: failed (%ld) to handle event on %d\n", "ta_manager_handle_channel", 523, v19, v66);
  uctx_handle_close(*(_QWORD *)(v7 + 1960), v3);
  v20 = v67;
LABEL_26:
  if ( (v20 & 4) != 0 )
  {
LABEL_9:
    printf("%s:%d: closed by peer\n", "ta_manager_handle_channel", 530);
    uctx_handle_close(*(_QWORD *)(v7 + 1960), v3);
  }
  while ( 1 )
  {
    v8 = (_QWORD *)(v7 + 1960);
    v9 = uctx_wait_any(*(_QWORD *)(v7 + 1960), qword_9405AB48, 0xFFFFFFFFLL);
    if ( v9 < 0 )
      break;
    if ( v9 == 0 )
    {
      v3 = v66;
      if ( v66 == v0 )
      {
        if ( (v67 & 0x1E) != 0 )
        {
          printf("%s:%d: error event (0x%x) for port (%d)\n", "ta_manager_handle_port", 490, v67, v0);
        }
        else if ( (v67 & 1) != 0 )
        {
          v11 = sys_accept_port(*v8, v0, &v69);
          if ( v11 < 0 )
            printf("%s:%d: failed (%d) to accept on port %d\n", "ta_manager_handle_port", 499, v11, v66);
        }
      }
      else if ( (v67 & 3) != 0 )
      {
        printf("%s:%d: error event (0x%x) for chan (%d)\n", "ta_manager_handle_channel", 513, v67, v66);
      }
      else
      {
        if ( (v67 & 8) != 0 )
        {
          if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, _QWORD, __int64 *))loc_9402E4E4)(*v8, v66, &v64) != 0 )
          {
            printf("%s:%d: uctx_handle_get failed %d!\n", "ta_manager_handle_msg", 424, v3);
            v19 = -2;
            goto LABEL_31;
          }
          if ( (unsigned int)ipc_msg_get_next(v64, &v62) == -4 )
            goto LABEL_25;
          v6 = (int *)calloc(v62, 1);
          if ( v6 == nullptr )
          {
            printf("%s:%d: ta_manager_handle_msg: no message!\n", "ta_manager_handle_msg", 436);
            ipc_msg_free(v64, v63);
            v19 = -5;
            goto LABEL_31;
          }
          v68[1] = v62;
          v69 = 1;
          v68[0] = v6;
          v70 = v68;
          v71 = 0;
          v72 = 0;
          v12 = sys_msg_write(v64, v63, 0, &v69);
          if ( (v12 & 0x80000000) == 0 )
          {
            switch ( *v6 )
            {
              case 2:
                v50 = (_DWORD *)calloc(8, 1);
                if ( v50 != nullptr )
                  goto LABEL_52;
                v13 = "%s:%d: ta_manager_initilze calloc(%d) failed!\n";
                v14 = "ta_manager_initilze";
                v15 = 168;
                goto LABEL_21;
              case 4:
                v50 = (_DWORD *)calloc(8, 1);
                if ( v50 != nullptr )
                {
LABEL_52:
                  v31 = *v6;
                  v32 = 8;
                  goto LABEL_53;
                }
                v13 = "%s:%d: ta_manager_terminate calloc(%d) failed!\n";
                v14 = "ta_manager_terminate";
                v15 = 182;
LABEL_21:
                v54 = -5;
                printf(v13, v14, v15, 8);
                v16 = -5;
                goto LABEL_22;
              case 6:
                v33 = calloc(1, 68);
                v50 = (_DWORD *)v33;
                if ( v33 == 0 )
                  goto LABEL_79;
                v45 = v33 + 4;
                do
                {
LABEL_43:
                  while ( 1 )
                  {
                    event_wait_timeout((__int64)qword_94067728, 0xFFFFFFFFLL);
                    mutex_acquire_timeout(v4, 0xFFFFFFFFLL);
                    v57 = v1[1];
                    if ( (_QWORD *)v57 != v1 )
                      break;
                    mutex_release(v4);
                    event_unsignal((__int64)qword_94067728);
                  }
                  mutex_release(v4);
                  event_unsignal((__int64)qword_94067728);
                }
                while ( v57 == 0 );
                v52 = v57 + 16;
                printf("%s:%d: ta_manager_wait_load %s\n", "ta_manager_wait_load", 235, (const char *)(v57 + 16));
                v34 = strlen(v57 + 16);
                *v50 = v34;
                memcpy(v45, v57 + 16, v34);
                v46 = (unsigned int)*v50;
                mutex_acquire_timeout(v61, 0xFFFFFFFFLL);
                for ( i = (__int64 *)v2[1]; i != v2; i = (__int64 *)v48[1] )
                {
                  v48 = i;
                  if ( (unsigned int)strncmp(i + 5, v52, v46) == 0 )
                  {
                    mutex_release(v61);
                    printf("%s:%d: %s is existing\n", "ta_manager_wait_load", 242, v52);
                    tipc_handle_save_ctx(v52, *(_QWORD *)(v57 + 80), *(unsigned int *)(v57 + 88));
                    mutex_acquire_timeout(v4, 0xFFFFFFFFLL);
                    v36 = (_QWORD *)v1[1];
                    if ( v36 == v1 )
                    {
                      mutex_release(v4);
                    }
                    else
                    {
                      v37 = (_QWORD *)v36[1];
                      v58 = v1[1];
                      *v37 = *v36;
                      *(_QWORD *)(*v36 + 8LL) = v37;
                      v36[1] = 0;
                      *v36 = 0;
                      mutex_release(v4);
                      free(v58);
                    }
                    goto LABEL_43;
                  }
                }
                mutex_release(v61);
                v12 = ta_manager_send_response(v64, *v6, (__int64)v50, 0x44u);
                if ( v12 < 0 )
                  goto LABEL_57;
                goto LABEL_54;
              case 14:
                if ( v62 == 4 )
                {
                  v54 = -8;
                  printf("%s:%d: ta_manager_write_ta: invalid parameters!\n", "ta_manager_write_ta", 272);
                  v16 = -8;
                  goto LABEL_22;
                }
                v21 = v6[1];
                v22 = v6[3];
                if ( v21 == 0 || v22 == 0 )
                {
                  v54 = -8;
                  printf(
                    "%s:%d: write_ta: total_size %d, payload_len = %d\n",
                    "ta_manager_write_ta",
                    281,
                    v21,
                    v22);
                  v16 = -8;
                  goto LABEL_22;
                }
                v23 = v6[2];
                if ( v21 < v23 + v22 )
                {
                  v54 = -8;
                  printf(
                    "%s:%d: write_ta: pos %d, payload_len = %d, total_size = %d\n",
                    "ta_manager_write_ta",
                    288,
                    v23,
                    v22,
                    v21);
                  v16 = -8;
                  goto LABEL_22;
                }
                v50 = (_DWORD *)calloc(1, 4);
                v24 = v6 + 1;
                if ( v50 == nullptr )
                {
                  v54 = -5;
                  printf("%s:%d: write_ta:wresq calloc(%d) failed!\n", "ta_manager_write_ta", 294, 4);
                  v16 = -5;
                  goto LABEL_22;
                }
                v25 = v6[2];
                if ( v25 != 0 )
                {
                  v26 = MEMORY[0x18];
                }
                else
                {
                  printf("%s:%d: ta_manager_write_ta: new ta!\n", "ta_manager_write_ta", 299);
                  v43 = calloc(1, 112);
                  off_940677B0 = (_UNKNOWN *)v43;
                  if ( v43 == 0 )
                  {
                    v54 = -5;
                    printf("%s:%d: write_ta: ta calloc(%d) failed!\n", "ta_manager_write_ta", 303, 112);
                    free(v50);
                    v16 = -5;
                    goto LABEL_22;
                  }
                  v44 = v6[1];
                  *(_QWORD *)(v43 + 8) = v43;
                  *(_QWORD *)v43 = v43;
                  *(_BYTE *)(v43 + 104) = 0;
                  *(_DWORD *)(v43 + 32) = v44;
                  *(_QWORD *)(v43 + 24) = memalign(4096, v44);
                  v26 = MEMORY[0x18];
                  if ( MEMORY[0x18] == 0 )
                  {
                    v54 = -5;
                    printf(
                      "%s:%d: write_ta: image malloc(%d) failed!\n",
                      "ta_manager_write_ta",
                      313,
                      MEMORY[0x20]);
                    free(0);
                    free(v50);
                    v16 = -5;
                    off_940677B0 = nullptr;
                    goto LABEL_22;
                  }
                  v24 = v6 + 1;
                  v25 = v6[2];
                }
                v51 = v24;
                memcpy(v26 + v25, v6 + 4, (unsigned int)v24[2]);
                v27 = 0;
                v28 = v51[2];
                v29 = MEMORY[0x20];
                MEMORY[0x24] += v28;
                v30 = MEMORY[0x24];
                *v50 = v28;
                if ( v30 == v29 )
                {
                  *(_QWORD *)(v27 + 16) = trusty_tapp_bootloader(MEMORY[0x18]);
                  if ( MEMORY[0x10] != 0 )
                    trusty_tapp_init();
                  event_wait_timeout((__int64)qword_940678B8, 0xFFFFFFFFLL);
                  mutex_acquire_timeout(v4, 0xFFFFFFFFLL);
                  v47 = v1[1];
                  if ( (_QWORD *)v47 == v1 )
                  {
                    mutex_release(v4);
                    printf(
                      "%s:%d: ta_manager_write_ta, load %s accomplished!\n",
                      "ta_manager_write_ta",
                      352,
                      (const char *)qword_94067820);
                    event_unsignal((__int64)qword_940678B8);
                  }
                  else
                  {
                    mutex_release(v4);
                    printf(
                      "%s:%d: ta_manager_write_ta, load %s accomplished!\n",
                      "ta_manager_write_ta",
                      352,
                      (const char *)qword_94067820);
                    event_unsignal((__int64)qword_940678B8);
                    if ( v47 != 0 )
                    {
                      v38 = strlen(v47 + 16);
                      if ( (unsigned int)strncmp(qword_94067820, v47 + 16, v38) == 0 )
                      {
                        tipc_handle_save_ctx(v47 + 16, *(_QWORD *)(v47 + 80), *(unsigned int *)(v47 + 88));
                        mutex_acquire_timeout(v4, 0xFFFFFFFFLL);
                        v41 = (_QWORD *)v1[1];
                        if ( v41 == v1 )
                        {
                          mutex_release(v4);
                        }
                        else
                        {
                          v42 = (_QWORD *)v41[1];
                          v49 = v1[1];
                          *v42 = *v41;
                          *(_QWORD *)(*v41 + 8LL) = v42;
                          v41[1] = 0;
                          *v41 = 0;
                          v53 = v41 + 2;
                          mutex_release(v4);
                          memcpy(40, v53, 64);
                          free(v49);
                        }
                      }
                    }
                  }
                  MEMORY[0x68] = 1;
                  mutex_acquire_timeout(v61, 0xFFFFFFFFLL);
                  v39 = *((_DWORD *)v2 + 18) + 1;
                  MEMORY[0] = *v2;
                  MEMORY[8] = v2;
                  v40 = *v2;
                  *v2 = 0;
                  *(_QWORD *)(v40 + 8) = 0;
                  *((_DWORD *)v2 + 18) = v39;
                  mutex_release(v61);
                  off_940677B0 = nullptr;
                }
                v31 = *v6;
                v32 = 4;
LABEL_53:
                v12 = ta_manager_send_response(v64, v31, (__int64)v50, v32);
                if ( (v12 & 0x80000000) == 0 )
                {
LABEL_54:
                  v59 = v12;
                  free(v50);
                  v12 = v59;
                  goto LABEL_24;
                }
LABEL_57:
                v60 = v12;
                printf("%s:%d: ta_manager_send_response failed %d!\n", "ta_manager_handle_msg", 467, v12);
                v12 = v60;
                if ( v50 != nullptr )
                  goto LABEL_54;
                break;
              default:
                v12 = ta_manager_send_response(v64, *v6, 0, 0);
                if ( (v12 & 0x80000000) == 0 )
                  goto LABEL_24;
                v50 = nullptr;
                goto LABEL_57;
            }
          }
          goto LABEL_24;
        }
        if ( (v67 & 4) != 0 )
          goto LABEL_9;
      }
    }
  }
  printf("%s:%d: uctx_wait_any failed %ld\n", "ta_manager_thread_fun", 571, v9);
  printf("%s:%d: ta_manager_thread_fun exit\n", "ta_manager_thread_fun", 584);
  free(0);
  uctx_destroy(*(_QWORD *)(v7 + 1960));
  return 0;
}

/* ===== ta_manager_noop @ 0x9402BC98 size 108 ===== */
void __spoils<> ta_manager_noop()
{
  ;
}

/* ===== tam_port_publish @ 0x9402BD04 size 164 ===== */
const char *__fastcall tam_port_publish(const char *result, unsigned int a2)
{
  const char *v2; // x20

  if ( a2 <= 0x3F && &qword_940677D0 != nullptr )
  {
    v2 = result;
    printf("%s:%d:  %s\n", "tam_port_publish", 695, result);
    memset(qword_94067820, 0, 64);
    memcpy(qword_94067820, v2, a2);
    return (const char *)event_signal((__int64)qword_940678B8, 0);
  }
  return result;
}

/* ===== tam_load_request @ 0x9402BDA8 size 244 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall tam_load_request(const char *a1, __int64 a2, int a3)
{
  __int64 v6; // x19
  __int64 v7; // x0

  printf("%s:%d:  %s\n", "tam_load_request", 707, a1);
  v6 = calloc(1, 96);
  if ( v6 == 0 )
    return printf("%s:%d:  calloc failed!\n", "tam_load_request", 711);
  v7 = strlen(a1);
  memcpy(v6 + 16, a1, v7);
  *(_QWORD *)(v6 + 80) = a2;
  *(_DWORD *)(v6 + 88) = a3;
  *(_QWORD *)(v6 + 8) = v6;
  *(_QWORD *)v6 = v6;
  mutex_acquire_timeout((__int64)qword_940677E0, 0xFFFFFFFFLL);
  *(_QWORD *)v6 = 0;
  *(_QWORD *)(v6 + 8) = &qword_940677D0;
  MEMORY[8] = v6;
  qword_940677D0 = v6;
  mutex_release((__int64)qword_940677E0);
  return event_signal((__int64)qword_94067728, 0);
}

/* ===== tam_unload_request @ 0x9402BE9C size 236 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall tam_unload_request(const char *a1, __int64 a2)
{
  _QWORD *v4; // x19
  __int64 v5; // x0

  printf("%s:%d:  %s\n", "tam_unload_request", 728, a1);
  v4 = (_QWORD *)calloc(1, 96);
  if ( v4 == nullptr )
    return printf("%s:%d:  calloc failed!\n", "tam_unload_request", 732);
  v5 = strlen(a1);
  memcpy(v4 + 2, a1, v5);
  v4[10] = a2;
  v4[1] = v4;
  *v4 = v4;
  mutex_acquire_timeout((__int64)qword_94067878, 0xFFFFFFFFLL);
  *v4 = 0;
  v4[1] = &qword_94067868;
  MEMORY[8] = v4;
  qword_94067868 = (__int64)v4;
  mutex_release((__int64)qword_94067878);
  return event_signal((__int64)qword_940676F8, 1u);
}

/* ===== trusty_app_init @ 0x9402BF88 size 36 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 trusty_app_init()
{
  printf("initializing trusty (%s)\n", (const char *)0xFFFFFFFFE003CCC8LL);
  qword_940678F8 = MEMORY[0xFFFFFFFFE03DF028];
  qword_94067910 = -536457216;
  dword_94067908 = MEMORY[0xFFFFFFFFE03DF028] + 536457216;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  byte_94067904 = 1;
  mutex_release((__int64)"xtum");
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("trusty_app: start %p size 0x%08x end %p\n", nullptr, 0, nullptr);
  return 0;
}

/* ===== trusty_app_load_segments @ 0x9402BFAC size 1136 ===== */
__int64 __fastcall trusty_app_load_segments(__int64 a1)
{
  __int64 v1; // x20
  unsigned int v3; // w1
  unsigned __int64 v4; // x22
  unsigned __int64 v5; // x21
  unsigned __int64 v6; // x24
  unsigned __int64 v7; // x23
  unsigned int v8; // w19
  __int64 v9; // x7
  _DWORD *v10; // x26
  unsigned int v11; // w0
  unsigned int v12; // w0
  __int64 v13; // x28
  __int64 v14; // x0
  int v15; // w3
  __int64 v16; // x28
  int v17; // w5
  int v18; // w3
  int v19; // w4
  unsigned __int64 v20; // x28
  __int64 v21; // x0
  unsigned int v22; // w0
  unsigned __int64 v23; // x1
  unsigned int v24; // w1
  __int64 v25; // x3
  unsigned __int64 v26; // x0
  unsigned int v27; // w2
  unsigned __int64 v28; // x1
  __int64 v29; // x2
  unsigned __int64 v30; // x1
  unsigned __int64 v31; // x0
  __int64 v32; // x19
  unsigned int v33; // w19
  __int64 v35; // x0
  __int64 v36; // x19
  __int64 v37; // x0
  __int64 v38; // x1
  __int64 v39; // x0
  __int64 v40; // [xsp+68h] [xbp+68h]
  __int64 v41; // [xsp+88h] [xbp+88h]
  __int64 v42; // [xsp+98h] [xbp+98h] BYREF
  __int64 v43; // [xsp+A0h] [xbp+A0h] BYREF
  __int64 v44; // [xsp+A8h] [xbp+A8h] BYREF

  v1 = *(_QWORD *)(a1 + 72);
  v3 = *(unsigned __int16 *)(v1 + 44);
  v4 = 0;
  v5 = -1;
  v6 = 0;
  v7 = 0;
  if ( *(_WORD *)(v1 + 44) != 0 )
  {
    v8 = 0;
    v9 = 0x7FFF;
    while ( 1 )
    {
      v10 = (_DWORD *)(v1 + *(unsigned int *)(v1 + 28) + 32LL * v8);
      if ( *v10 != 1 )
        goto LABEL_3;
      v11 = v10[2];
      if ( v11 <= (unsigned int)v9 || *(_QWORD *)a1 <= (unsigned __int64)v11 )
        goto LABEL_3;
      if ( (v11 & 0xFFF) != 0 || ((v12 = v10[1]) & 0xFFF) != 0 )
      {
        panic(
          v40,
          "ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/trusty/trusty_app.c",
          331,
          "!(prg_hdr->p_vaddr & PAGE_MASK) && !(prg_hdr->p_offset & PAGE_MASK)");
        goto LABEL_39;
      }
      v41 = v9;
      v13 = (unsigned int)v10[5];
      v14 = pmm_phys_to_virt(v1 + v12);
      v15 = v10[6];
      v16 = v13 + 4095;
      v42 = v14;
      v17 = v15 & 1;
      v18 = v15 & 2 | 0x100 | ((v15 & 4) != 0);
      if ( v17 != 0 )
        v19 = 4;
      else
        v19 = 0;
      v20 = v16 & 0xFFFFFFFFFFFFF000LL;
      v21 = *(_QWORD *)(a1 + 80);
      v44 = (unsigned int)v10[2];
      v22 = uthread_map(v21, &v44, &v42, v20, v18 | v19 | 0x20u, 4096);
      v9 = v41;
      if ( v22 != 0 )
      {
        v33 = v22;
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("cannot map the segment\n");
        return v33;
      }
      v23 = (unsigned int)(0x1000000 - *(_DWORD *)(a1 + 48));
      if ( v23 < v20 + v44 )
      {
        v33 = -25;
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("failed to load trusty_app: (overlaps user stack 0x%lx)\n", v23);
        return v33;
      }
      v24 = v10[2];
      v25 = v24;
      v26 = v24 + v10[4];
      if ( v5 > v24 )
        v5 = v24;
      if ( v4 < v24 )
        v4 = v24;
      if ( v7 < v26 && (v10[6] & 1) != 0 )
        v7 = v24 + v10[4];
      v27 = v10[5];
      if ( v6 < v26 )
        v6 = v24 + v10[4];
      v28 = v27 + v24;
      if ( v28 > *(_QWORD *)(a1 + 8) )
      {
        v39 = (unsigned int)v10[1];
        *(_QWORD *)(a1 + 8) = v28;
        *(_QWORD *)(a1 + 24) = v20 + v25;
        memset(v1 + v27 + v39, 0, v20 - v27);
        v3 = *(unsigned __int16 *)(v1 + 44);
        v9 = v41;
LABEL_3:
        if ( v3 <= ++v8 )
          break;
      }
      else
      {
        v3 = *(unsigned __int16 *)(v1 + 44);
        if ( v3 <= ++v8 )
          break;
      }
    }
  }
  v29 = *(_QWORD *)(a1 + 8);
  v30 = *(unsigned int *)(a1 + 52);
  v31 = *(_QWORD *)(a1 + 24) - v29;
  *(_QWORD *)(a1 + 16) = v29;
  if ( v31 >= v30 )
  {
LABEL_26:
    v32 = 0x4EC4EC4EC4EC4EC5LL * (a1 >> 3);
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    {
      log_printf("trusty_app %d: code: start 0x%08lx end 0x%08lx\n", v32, v5, v7);
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("trusty_app %d: data: start 0x%08lx end 0x%08lx\n", v32, v4, v6);
        if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
        {
          log_printf("trusty_app %d: bss:                end 0x%08lx\n", v32, *(_QWORD *)a1);
          if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
          {
            log_printf(
              "trusty_app %d: brk:  start 0x%08lx end 0x%08lx\n",
              v32,
              *(_QWORD *)(a1 + 8),
              *(_QWORD *)(a1 + 24));
            if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
            {
              v33 = 0;
              log_printf(
                "trusty_app %d: entry 0x%08lx\n",
                -991146299 * (a1 >> 3),
                *(_QWORD *)(*(_QWORD *)(a1 + 80) + 8LL));
              return v33;
            }
          }
        }
      }
    }
    return 0;
  }
  v35 = memalign(4096, v30);
  v1 = v35;
  if ( v35 != 0 )
  {
    memset(v35, 0, *(unsigned int *)(a1 + 52));
    v36 = *(_QWORD *)(a1 + 80);
    v43 = *(_QWORD *)(a1 + 24);
    v44 = pmm_phys_to_virt(v1);
    if ( (unsigned int)uthread_map(v36, &v43, &v44, *(unsigned int *)(a1 + 52), 291, 4096) == 0 )
    {
      v37 = *(_QWORD *)(a1 + 24);
      if ( v37 == v43 )
      {
        v38 = *(unsigned int *)(a1 + 52);
        *(_QWORD *)(a1 + 96) = v1;
        *(_QWORD *)(a1 + 24) = v38 + v37;
        goto LABEL_26;
      }
    }
LABEL_39:
    if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      log_printf("cannot map brk\n");
    free(v1);
  }
  v33 = -5;
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
    return v33;
  log_printf("failed to load trusty_app: trusty_app heap creation error\n");
  return 4294967291LL;
}

/* ===== load_app_config_options @ 0x9402C41C size 916 ===== */
__int64 __fastcall load_app_config_options(__int64 a1, __int64 a2, unsigned int a3, _DWORD *a4)
{
  __int64 v4; // x30
  __int64 v7; // x22
  __int64 v8; // x20
  __int64 *v9; // x21
  __int64 result; // x0
  unsigned int v11; // w4
  __int64 v12; // x0
  unsigned int v13; // w3
  int v14; // w2
  unsigned int v15; // w3
  unsigned int v16; // w2
  __int64 *v17; // x21
  unsigned int v18; // w2

  v7 = v4;
  if ( *a4 <= 0xFu )
  {
    panic(
      v4,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      171,
      "shdr->sh_size >= sizeof(uuid_t)");
LABEL_25:
    panic(
      v7,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      219,
      "(trusty_app->props.config_entry_cnt - i) > 1");
LABEL_26:
    panic(
      v7,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      212,
      "(trusty_app->props.config_entry_cnt - i) > 1");
LABEL_27:
    panic(
      v7,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      226,
      "(trusty_app->props.config_entry_cnt - i) > 3");
LABEL_28:
    panic(
      v7,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      215,
      "trusty_app->props.min_stack_size > 0");
    return 0;
  }
  else
  {
    v8 = a1 + a3;
    *(_DWORD *)(a2 + 52) = 0x4000;
    v9 = &qword_9405BFF0[2];
    *(_DWORD *)(a2 + 48) = 4096;
    memcpy(a2 + 32, v8, 16);
    result = MEMORY[0xFFFFFFFFE003CB98];
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      result = log_printf(
                 "trusty_app %d uuid: 0x%x 0x%x 0x%x 0x%x%x 0x%x%x%x%x%x%x\n",
                 -991146299 * (unsigned int)(a2 >> 3),
                 *(_DWORD *)(a2 + 32),
                 *(unsigned __int16 *)(a2 + 36),
                 *(unsigned __int16 *)(a2 + 38),
                 *(unsigned __int8 *)(a2 + 40),
                 *(unsigned __int8 *)(a2 + 41),
                 *(unsigned __int8 *)(a2 + 42),
                 *(unsigned __int8 *)(a2 + 43),
                 *(unsigned __int8 *)(a2 + 44),
                 *(unsigned __int8 *)(a2 + 45),
                 *(unsigned __int8 *)(a2 + 46),
                 *(unsigned __int8 *)(a2 + 47));
    v11 = (unsigned int)(*a4 - 16) >> 2;
    *(_DWORD *)(a2 + 60) = v11;
    if ( v11 != 0 )
    {
      v12 = v8 + 16;
      v13 = 0;
      *(_QWORD *)(a2 + 64) = v8 + 16;
      while ( 1 )
      {
        v14 = *(_DWORD *)(v12 + 4LL * v13);
        if ( v14 != 2 )
          break;
        if ( v11 - v13 <= 1 )
          goto LABEL_25;
        v15 = v13 + 1;
        v18 = (*(_DWORD *)(v12 + 4LL * v15) + 4095) & 0xFFFFF000;
        *(_DWORD *)(a2 + 52) = v18;
        if ( v18 == 0 )
        {
          v12 = panic(
                  v7,
                  "ASSERT FAILED at (%s:%d): %s\n",
                  "lk/trusty/lib/trusty/trusty_app.c",
                  222,
                  "trusty_app->props.min_heap_size > 0");
LABEL_22:
          if ( v11 - v13 <= 3 )
            goto LABEL_27;
          v15 = v13 + 3;
          ++*(_DWORD *)(a2 + 56);
        }
LABEL_14:
        v13 = v15 + 1;
        if ( v11 <= v13 )
        {
          v17 = (__int64 *)v9[464];
          result = *v17;
          if ( *v17 > 1 )
          {
            log_printf("trusty_app %p: stack_sz=0x%x\n", (const void *)a2, *(_DWORD *)(a2 + 48));
            result = *v17;
            if ( *v17 > 1 )
              return log_printf("trusty_app %p: heap_sz=0x%x\n", (const void *)a2, *(_DWORD *)(a2 + 52));
          }
          return result;
        }
      }
      if ( v14 != 3 )
      {
        if ( v14 != 1 )
        {
          v9 = (__int64 *)v9[464];
          if ( (*v9 & 0x8000000000000000LL) == 0 )
            log_printf("%s: unknown config key: %d\n", "load_app_config_options", v14);
          v12 = panic(v7, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/trusty_app.c", 234, "0");
        }
        if ( v11 - v13 <= 1 )
          goto LABEL_26;
        v15 = v13 + 1;
        v16 = (*(_DWORD *)(v12 + 4LL * v15) + 4095) & 0xFFFFF000;
        *(_DWORD *)(a2 + 48) = v16;
        if ( v16 == 0 )
          goto LABEL_28;
        goto LABEL_14;
      }
      goto LABEL_22;
    }
  }
  return result;
}

/* ===== trusty_register_notifier @ 0x9402C7B0 size 120 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall trusty_register_notifier(_QWORD *a1)
{
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  a1[1] = &qword_9405ABE8;
  *a1 = -536630296;
  qword_9405ABE8 = (__int64)a1;
  MEMORY[0xFFFFFFFFE003ABF0] = a1;
  mutex_release((__int64)"xtum");
  return 0;
}

/* ===== trusty_alloc_als_slot @ 0x9402C828 size 96 ===== */
__int64 trusty_alloc_als_slot()
{
  unsigned int v0; // w19

  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  v0 = ++MEMORY[0xFFFFFFFFE006124C];
  mutex_release((__int64)"xtum");
  return v0;
}

/* ===== trusty_app_map_segment @ 0x9402C888 size 176 ===== */
__int64 __fastcall trusty_app_map_segment(__int64 a1, int a2, __int64 a3, int a4)
{
  unsigned int v4; // w8
  __int64 v5; // x7
  unsigned int v6; // w4
  unsigned int v7; // w5
  unsigned int v8; // w9
  unsigned int v9; // w6
  int v10; // w4
  unsigned int v11; // w3
  __int64 v12; // x0
  __int64 v14; // [xsp+18h] [xbp+18h] BYREF

  v4 = *(_DWORD *)(a1 + 60);
  if ( v4 == 0 )
    return 4294967294LL;
  v5 = *(_QWORD *)(a1 + 64);
  v6 = 0;
  while ( 1 )
  {
    v7 = v6 + 1;
    if ( *(_DWORD *)(v5 + 4LL * v6) == 3 )
    {
      v8 = v6 + 1;
      v7 = v6 + 3;
      v9 = *(_DWORD *)(v5 + 4LL * (v6 + 2));
      v10 = *(_DWORD *)(v5 + 4LL * (v6 + 3));
      if ( *(_DWORD *)(v5 + 4LL * v8) == a2 )
        break;
    }
    v6 = v7 + 1;
    if ( v7 + 1 >= v4 )
      return 4294967294LL;
  }
  v11 = (a4 + 4095) & 0xFFFFF000;
  if ( ((v10 + 4095) & 0xFFFFF000) < v11 )
    return 4294967288LL;
  v12 = *(_QWORD *)(a1 + 80);
  v14 = v9;
  return uthread_map(v12, a3, &v14, v11 & 0xFFFFF000, 163, 4096);
}

/* ===== trusty_tapp_bootloader @ 0x9402CF10 size 792 ===== */
__int64 __fastcall trusty_tapp_bootloader(__int64 a1, unsigned int a2)
{
  __int64 v5; // x0
  _QWORD *v6; // x21
  __int64 v7; // x2
  __int64 v8; // x24
  unsigned int *v9; // x28
  unsigned int v10; // w23
  unsigned int *v11; // x22
  unsigned int *v12; // x26
  unsigned int v13; // w27
  __int64 v14; // x20
  bool v15; // zf
  unsigned int *v16; // x0
  unsigned int v17; // w0
  unsigned int v18; // w2
  __int64 v19; // x0
  unsigned int *v20; // [xsp+70h] [xbp+70h]
  unsigned int *v21; // [xsp+80h] [xbp+80h]
  __int64 vars0; // [xsp+88h] [xbp+88h]

  if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
  {
    if ( a2 == 0 || a1 == 0 )
      return 0;
  }
  else
  {
    log_printf("trusty_tapp_bootloader: start %p size 0x%08x end %p\n", (const void *)a1, a2, (const void *)(a1 + a2));
    if ( a2 == 0 || a1 == 0 )
    {
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      {
        log_printf("trusty_tapp_bootloader:start %p size 0x%08x invalid parameters\n", (const void *)a1, a2);
        return 0;
      }
      return 0;
    }
  }
  v5 = calloc(1, 104);
  v6 = (_QWORD *)v5;
  if ( v5 == 0 )
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    {
      log_printf("trusty_tapp_bootloader: calloc failed!\n");
      return 0;
    }
    return 0;
  }
  memset(v5, 0, 104);
  if ( (unsigned int)strncmp(a1, &qword_94050A58, 4) != 0 )
  {
    if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      log_printf("trusty_tapp_bootloader: ELF header not found\n");
    free(v6);
    return 0;
  }
  v7 = *(unsigned int *)(a1 + 32) + a1;
  v8 = a1 + *(unsigned int *)(v7 + 40LL * *(unsigned __int16 *)(a1 + 50) + 16);
  if ( *(_WORD *)(a1 + 48) == 0 )
    goto LABEL_35;
  v9 = (unsigned int *)(*(unsigned int *)(a1 + 32) + a1);
  v10 = 0;
  v21 = nullptr;
  v11 = (unsigned int *)(v7 + 40LL * ((unsigned int)*(unsigned __int16 *)(a1 + 48) - 1) + 40);
  v20 = nullptr;
  v12 = nullptr;
  do
  {
    v13 = v9[1];
    if ( v13 != 0 )
    {
      v14 = v8 + *v9;
      if ( (unsigned int)strcmp(v14, ".bss") != 0 )
      {
        if ( (unsigned int)strcmp(v14, ".bss-pad") != 0 )
        {
          v15 = (unsigned int)strcmp(v14, ".trusty_app.manifest") == 0;
          v16 = v21;
          if ( v15 )
            v16 = v9;
          v21 = v16;
        }
        else
        {
          v20 = v9;
        }
      }
      else
      {
        v12 = v9;
        *v6 = v9[5] + v9[3];
      }
      if ( v13 != 8 && v10 < v9[5] + v9[4] )
        v10 = v9[5] + v9[4];
    }
    v9 += 10;
  }
  while ( v9 != v11 );
  if ( v20 != nullptr && v12 != nullptr && v21 != nullptr )
  {
    v17 = v12[4];
    v18 = v12[5];
    if ( v18 + v17 <= v10 )
    {
      memset(a1 + v17, 0, v18);
      load_app_config_options(a1, (__int64)v6, v21[4], v21 + 5);
      v6[9] = a1;
      return (__int64)v6;
    }
  }
  else
  {
LABEL_35:
    panic(
      vars0,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_app.c",
      748,
      "bss_shdr && bss_pad_shdr && manifest_shdr");
  }
  v19 = panic(
          vars0,
          "ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/trusty/trusty_app.c",
          751,
          "(bss_shdr->sh_offset + bss_shdr->sh_size) <= trusty_app_max_extent");
  return trusty_tapp_init(v19);
}

/* ===== trusty_tapp_init @ 0x9402D228 size 504 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall trusty_tapp_init(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x23
  __int64 v4; // x0
  __int64 v5; // x0
  __int64 v6; // x19
  __int64 (__fastcall *v7)(__int64); // x1
  int v8; // w2
  int v10; // w0
  unsigned int v11; // w2
  __int64 v12; // x20
  unsigned int v13; // w19
  int v14; // w22
  unsigned int v15; // w1
  __int64 v16; // x21
  __int64 v17; // x0
  _BYTE v18[32]; // [xsp+70h] [xbp+40h] BYREF

  v3 = v1;
  if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    log_printf("trusty_tapp_init:\n");
  snprintf(
    v18,
    32,
    "trusty_tapp_%d_%08x-%04x-%04x",
    0,
    *(_DWORD *)(a1 + 32),
    *(unsigned __int16 *)(a1 + 36),
    *(unsigned __int16 *)(a1 + 38));
  v4 = uthread_create(v18, *(unsigned int *)(*(_QWORD *)(a1 + 72) + 24LL), 16, 0x1000000, *(unsigned int *)(a1 + 48), a1);
  if ( v4 == 0 )
    goto LABEL_15;
  *(_QWORD *)(a1 + 80) = v4;
  if ( (unsigned int)trusty_app_load_segments(a1) != 0 )
  {
LABEL_14:
    panic(v3, "failed to load address map\n");
LABEL_15:
    panic(v3, "allocate user thread failed\n");
    goto LABEL_16;
  }
  v5 = calloc(1, 8LL * MEMORY[0xFFFFFFFFE006124C]);
  *(_QWORD *)(a1 + 88) = v5;
  if ( v5 == 0 )
  {
LABEL_13:
    panic(v3, "allocate app local storage failed\n");
    goto LABEL_14;
  }
  v6 = -536630296;
  if ( &qword_9405ABE8 != (__int64 *)-536630296LL )
  {
    while ( 1 )
    {
      v7 = *(__int64 (__fastcall **)(__int64))(v6 + 16);
      if ( v7 != nullptr )
      {
        v8 = v7(a1);
        if ( v8 != 0 )
          break;
      }
      v6 = *(_QWORD *)(v6 + 8);
      if ( (__int64 *)v6 == &qword_9405ABE8 )
        goto LABEL_10;
    }
    panic(v3, "failed (%d) to invoke startup notifier\n", v8);
    goto LABEL_13;
  }
LABEL_10:
  if ( (unsigned int)uthread_start(*(_QWORD *)(a1 + 80)) == 0 )
  {
    dword_940678E8 = 1;
    return 1;
  }
LABEL_16:
  v10 = panic(v3, "Cannot start Trusty app!\n");
  v12 = v11;
  v13 = v11;
  v14 = v10;
  v16 = v15;
  if ( (unsigned __int8)uthread_is_mapped(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688), v15, v11) == 0 )
    return 4294967288LL;
  v17 = 2;
  if ( v14 == 2 )
    v17 = 1;
  if ( v17 <= MEMORY[0xFFFFFFFFE003CB98] )
    console_write_raw(v16, v12);
  return v13;
}

/* ===== trusty_install_handler @ 0x9402D420 size 116 ===== */
__int64 __fastcall trusty_install_handler(unsigned int a1, __int64 a2)
{
  unsigned int v4; // w20

  if ( a1 > 9 )
    return 4294967288LL;
  v4 = -14;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  if ( qword_9405AC48[a1] == 0 )
  {
    qword_9405AC48[a1] = a2;
    v4 = 0;
  }
  mutex_release((__int64)"xtum");
  return v4;
}

/* ===== trusty_call_handler @ 0x9402D494 size 64 ===== */
__int64 __fastcall trusty_call_handler(unsigned int a1)
{
  __int64 v1; // x3
  __int64 v2; // x4
  int (*v3)(void); // x4

  v1 = -24;
  if ( a1 <= 9 )
  {
    v2 = qword_9405AC48[a1];
    if ( v2 != 0 )
    {
      v3 = *(int (**)(void))(v2 + 8);
      if ( v3 != nullptr )
        return v3();
    }
  }
  return v1;
}

/* ===== trusty_get_brk @ 0x9402D4D4 size 56 ===== */
__int64 __fastcall trusty_get_brk(__int64 result)
{
  _QWORD *v1; // x1

  result = (unsigned int)result;
  v1 = *(_QWORD **)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 144LL);
  if ( (unsigned __int64)(unsigned int)result < v1[1] || (unsigned __int64)(unsigned int)result > v1[3] )
    return v1[2];
  v1[2] = (unsigned int)result;
  return result;
}

/* ===== trusty_exit @ 0x9402D50C size 116 ===== */
__int64 trusty_exit()
{
  const char *StatusReg; // x1
  __int64 v1; // x0
  __int64 v2; // x1
  __int64 v3; // x3
  int (__fastcall **v4)(__int64, __int64); // x4
  int (__fastcall *v5)(__int64, __int64); // x4

  StatusReg = (const char *)_ReadStatusReg(TPIDR_EL1);
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("exit called, thread %p, name %s\n", StatusReg, StatusReg + 696);
  v1 = uthread_exit(0);
  v3 = -24;
  if ( (unsigned int)v1 <= 9 )
  {
    v4 = (int (__fastcall **)(__int64, __int64))qword_9405AC48[(unsigned int)v1];
    if ( v4 != nullptr )
    {
      v5 = *v4;
      if ( v5 != nullptr )
        return v5(v1, v2);
    }
  }
  return v3;
}

/* ===== trusty_call_handler2 @ 0x9402D580 size 64 ===== */
__int64 __fastcall trusty_call_handler2(unsigned int a1)
{
  __int64 v1; // x3
  __int64 v2; // x4
  int (*v3)(void); // x4

  v1 = -24;
  if ( a1 <= 9 )
  {
    v2 = qword_9405AC48[a1];
    if ( v2 != 0 )
    {
      v3 = *(int (**)(void))(v2 + 16);
      if ( v3 != nullptr )
        return v3();
    }
  }
  return v1;
}

/* ===== trusty_sleep_ns @ 0x9402D5C0 size 64 ===== */
__int64 __fastcall trusty_sleep_ns(__int64 a1, __int64 a2, unsigned int a3, __int64 a4)
{
  thread_sleep(((a4 << 32) + (unsigned __int64)a3 + 999999) / 0xF4240);
  return 0;
}

/* ===== trusty_get_time_ms @ 0x9402D600 size 92 ===== */
__int64 __fastcall trusty_get_time_ms(__int64 a1, __int64 a2, unsigned int a3)
{
  unsigned __int64 v3; // x0
  __int64 v6; // [xsp+28h] [xbp+28h] BYREF

  if ( MEMORY[0xFFFFFFFFE0047918] != nullptr )
    v3 = MEMORY[0xFFFFFFFFE0047918]();
  else
    v3 = arch_time_now();
  v6 = 1000 * v3;
  return (int)copy_to_user(a3, &v6, 8);
}

/* ===== trusty_mmap @ 0x9402D65C size 84 ===== */
__int64 __fastcall trusty_mmap(int a1, int a2, int a3, int a4)
{
  bool v4; // zf
  __int64 v5; // x2
  __int64 result; // x0
  __int64 v7; // [xsp+18h] [xbp+18h] BYREF

  v4 = a3 == 1;
  v5 = *(_QWORD *)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 144LL);
  if ( !v4 || a1 != 0 )
    return -8;
  result = (int)trusty_app_map_segment(v5, a4, (__int64)&v7, a2);
  if ( (_DWORD)result == 0 )
    return v7;
  return result;
}

/* ===== trusty_munmap @ 0x9402D6B0 size 48 ===== */
__int64 __fastcall trusty_munmap(unsigned int a1, unsigned int a2)
{
  return (int)uthread_unmap(
                *(_QWORD *)(*(_QWORD *)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 144LL) + 80LL),
                a1,
                a2);
}

/* ===== trusty_stub_ret24_1 @ 0x9402D6E0 size 8 ===== */
__int64 trusty_stub_ret24_1()
{
  return -24;
}

/* ===== trusty_stub_ret24_2 @ 0x9402D6E8 size 8 ===== */
__int64 trusty_stub_ret24_2()
{
  return -24;
}

/* ===== handle_wait_any @ 0x9402D6F0 size 364 ===== */
__int64 __fastcall handle_wait_any(__int64 a1, _QWORD *a2, _DWORD *a3, unsigned __int8 a4)
{
  __int64 v4; // x30
  int v8; // w21
  __int64 v9; // x19
  __int64 v10; // x19
  __int64 v11; // x22
  __int64 v12; // x26
  int v13; // w0
  __int64 v14; // x19
  bool v15; // zf
  unsigned int v17; // w24
  __int64 v18; // x19
  __int64 i; // x19
  __int64 v20; // x19

  v8 = a4;
  if ( *(_QWORD *)(a1 + 72) == 0 )
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 272, "hlist->wait_event");
    return 4294967294LL;
  }
  v9 = *(_QWORD *)(a1 + 8);
  if ( a1 == v9 )
    return 4294967294LL;
  v10 = v9 - 80;
  v11 = 0;
  while ( 1 )
  {
    if ( v8 != 0 )
    {
      v12 = *(_QWORD *)(a1 + 72);
      mutex_acquire_timeout(v10 + 24, 0xFFFFFFFFLL);
      if ( *(_QWORD *)(v10 + 16) != 0 )
      {
        v17 = -6;
        mutex_release(v10 + 24);
        goto LABEL_13;
      }
      *(_QWORD *)(v10 + 16) = v12;
      v11 = v10;
      mutex_release(v10 + 24);
    }
    v13 = (**(__int64 (__fastcall ***)(__int64))(v10 + 8))(v10);
    if ( v13 != 0 )
      break;
    v14 = *(_QWORD *)(v10 + 88);
    v15 = a1 == v14;
    v10 = v14 - 80;
    if ( v15 )
      return 0;
  }
  *a3 = v13;
  v17 = 1;
  *a2 = v10;
  if ( v8 == 0 )
    return 1;
LABEL_13:
  if ( v11 != 0 )
  {
    v18 = *(_QWORD *)(a1 + 8);
    v15 = a1 == v18;
    for ( i = v18 - 80; !v15; i = v20 - 80 )
    {
      mutex_acquire_timeout(i + 24, 0xFFFFFFFFLL);
      *(_QWORD *)(i + 16) = 0;
      mutex_release(i + 24);
      if ( v11 == i )
        break;
      v20 = *(_QWORD *)(i + 88);
      v15 = a1 == v20;
    }
  }
  return v17;
}

/* ===== handle_init @ 0x9402D85C size 212 ===== */
__int64 __fastcall handle_init(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  unsigned int v4; // w0
  __int64 result; // x0
  __int64 v6; // x0

  if ( a1 == 0 )
  {
    panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 45, "handle");
  }
  else if ( a2 != 0 )
  {
    if ( *(_QWORD *)(a2 + 24) == 0 )
    {
LABEL_9:
      v6 = panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 47, "ops->destroy");
      return handle_incref(v6);
    }
    do
      __ldxr((unsigned int *)a1);
    while ( __stxr(0, (unsigned int *)a1) != 0 );
    do
      v4 = __ldxr((unsigned int *)a1);
    while ( __stxr(v4 + 1, (unsigned int *)a1) != 0 );
    *(_QWORD *)(a1 + 8) = a2;
    *(_QWORD *)(a1 + 16) = 0;
    result = mutex_init(a1 + 24);
    *(_QWORD *)(a1 + 96) = 0;
    *(_QWORD *)(a1 + 88) = 0;
    *(_QWORD *)(a1 + 80) = 0;
    return result;
  }
  panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 46, "ops");
  goto LABEL_9;
}

/* ===== handle_incref @ 0x9402D930 size 176 ===== */
__int64 __fastcall handle_incref(__int64 result)
{
  __int64 v1; // x30
  unsigned int v2; // w1
  __int64 v3; // x30
  unsigned int v4; // w2
  __int64 v5; // x0

  if ( result != 0 )
  {
    do
      v2 = __ldxr((unsigned int *)result);
    while ( __stxr(v2 + 1, (unsigned int *)result) != 0 );
  }
  else
  {
    result = panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 67, "handle");
    if ( result != 0 )
    {
      do
        v4 = __ldxr((unsigned int *)result);
      while ( __stxr(v4 - 1, (unsigned int *)result) != 0 );
      if ( v4 == 1 )
        return (*(__int64 (__fastcall **)(__int64, _QWORD))(*(_QWORD *)(result + 8) + 24LL))(
                 result,
                 *(_QWORD *)(*(_QWORD *)(result + 8) + 24LL));
    }
    else
    {
      v5 = panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 73, "handle");
      return handle_close(v5);
    }
  }
  return result;
}

/* ===== handle_close @ 0x9402D9E0 size 252 ===== */
void __fastcall handle_close(__int64 a1, _QWORD *a2)
{
  __int64 v2; // x30
  __int64 v5; // x0
  __int64 v6; // x2
  _QWORD *v7; // x1
  __int64 v8; // x0

  v5 = v2;
  if ( a1 != 0 )
  {
    if ( a2 == nullptr )
    {
LABEL_10:
      panic(v5, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 204, "handle");
      goto LABEL_11;
    }
    v6 = a2[10];
    v7 = (_QWORD *)a2[11];
    if ( v6 != 0 || v7 != nullptr )
    {
      *v7 = v6;
      v8 = *(_QWORD *)(a1 + 72);
      *(_QWORD *)(a2[10] + 8LL) = v7;
      a2[11] = 0;
      a2[10] = 0;
      if ( v8 == 0
        || (mutex_acquire_timeout((__int64)(a2 + 3), 0xFFFFFFFFLL),
            a2[2] = 0,
            mutex_release((__int64)(a2 + 3)),
            *(_QWORD *)(a1 + 8) != a1) )
      {
LABEL_12:
        JUMPOUT(0x9402D978LL);
      }
LABEL_11:
      event_signal(*(_QWORD *)(a1 + 72), 1u);
      goto LABEL_12;
    }
    v5 = panic(
           v2,
           "DEBUG ASSERT FAILED at (%s:%d): %s\n",
           "lk/trusty/lib/trusty/handle.c",
           205,
           "list_in_list(&handle->hlist_node)");
  }
  v5 = panic(v5, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 203, "hlist");
  goto LABEL_10;
}

/* ===== handle_decref @ 0x9402DADC size 344 ===== */
__int64 __fastcall handle_decref(__int64 a1)
{
  __int64 v1; // x30
  void (*v2)(void); // x1
  __int64 v3; // x0
  unsigned int *v4; // x1
  unsigned int v5; // w2
  __int64 v6; // x19
  unsigned int v7; // w23
  unsigned int *v8; // x24
  unsigned int v9; // w20
  unsigned int v10; // w20
  void (__fastcall *v11)(__int64, _QWORD); // x2
  _BYTE v13[48]; // [xsp+40h] [xbp-30h] BYREF

  if ( a1 != 0 )
  {
    v2 = *(void (**)(void))(*(_QWORD *)(a1 + 8) + 16LL);
    if ( v2 != nullptr )
      v2();
    JUMPOUT(0x9402D978LL);
  }
  v3 = panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 79, "handle");
  if ( v3 == 0 || v4 == nullptr )
    return 4294967288LL;
  v6 = v3;
  v7 = v5;
  v8 = v4;
  event_init((__int64)v13, 0, 1);
  mutex_acquire_timeout(v6 + 24, 0xFFFFFFFFLL);
  if ( *(_QWORD *)(v6 + 16) != 0 )
  {
    v9 = -6;
    mutex_release(v6 + 24);
  }
  else
  {
    *(_QWORD *)(v6 + 16) = v13;
    mutex_release(v6 + 24);
    while ( 1 )
    {
      v10 = (**(__int64 (__fastcall ***)(__int64))(v6 + 8))(v6);
      if ( v10 != 0 )
        break;
      v9 = event_wait_timeout((__int64)v13, v7);
      if ( (v9 & 0x80000000) != 0 )
        goto LABEL_14;
    }
    v11 = *(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)(v6 + 8) + 8LL);
    if ( v11 != nullptr )
      v11(v6, v10);
    *v8 = v10;
    v9 = 0;
LABEL_14:
    mutex_acquire_timeout(v6 + 24, 0xFFFFFFFFLL);
    *(_QWORD *)(v6 + 16) = 0;
    mutex_release(v6 + 24);
  }
  event_destroy((__int64)v13);
  return v9;
}

/* ===== handle_cancel_wait @ 0x9402DC34 size 104 ===== */
__int64 __fastcall handle_cancel_wait(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x20
  __int64 v4; // x0
  __int64 v6; // x0

  if ( a1 != 0 )
  {
    v3 = a1 + 24;
    mutex_acquire_timeout(a1 + 24, 0xFFFFFFFFLL);
    v4 = *(_QWORD *)(a1 + 16);
    if ( v4 != 0 )
      event_signal(v4, 1u);
    return mutex_release(v3);
  }
  else
  {
    v6 = panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 159, "handle");
    return hlist_init(v6);
  }
}

/* ===== hlist_init @ 0x9402DC9C size 112 ===== */
_QWORD *__fastcall hlist_init(_QWORD *result)
{
  __int64 v1; // x30
  __int64 v2; // x0

  if ( result != nullptr )
  {
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    result[5] = 0;
    *result = result;
    result[8] = 0;
    result[9] = 0;
    result[1] = result;
    *((_DWORD *)result + 4) = 1836414072;
    *((_DWORD *)result + 10) = 2002872692;
    result[6] = result + 6;
    result[7] = result + 6;
  }
  else
  {
    v2 = panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 174, "hlist");
    return (_QWORD *)hlist_add_handle(v2);
  }
  return result;
}

/* ===== hlist_add_handle @ 0x9402DD0C size 300 ===== */
__int64 __fastcall hlist_add_handle(_QWORD *a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 v5; // x22
  __int64 v7; // x0

  if ( a1 == nullptr )
  {
    panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 181, "hlist");
  }
  else if ( a2 != 0 )
  {
    if ( *(_QWORD *)(a2 + 80) == 0 )
      goto LABEL_5;
    do
    {
      panic(
        v2,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/handle.c",
        183,
        "!list_in_list(&handle->hlist_node)");
LABEL_5:
      ;
    }
    while ( *(_QWORD *)(a2 + 88) != 0 );
    handle_incref(a2);
    mutex_acquire_timeout((__int64)(a1 + 2), 0xFFFFFFFFLL);
    v5 = a1[9];
    *(_QWORD *)(a2 + 80) = *a1;
    *(_QWORD *)(a2 + 88) = a1;
    *(_QWORD *)(*a1 + 8LL) = a2 + 80;
    *a1 = a2 + 80;
    if ( v5 != 0 )
    {
      mutex_acquire_timeout(a2 + 24, 0xFFFFFFFFLL);
      if ( *(_QWORD *)(a2 + 16) == 0 )
        *(_QWORD *)(a2 + 16) = v5;
      mutex_release(a2 + 24);
      if ( (**(unsigned int (__fastcall ***)(__int64))(a2 + 8))(a2) != 0 )
        handle_cancel_wait(a2);
    }
    return mutex_release((__int64)(a1 + 2));
  }
  v7 = panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 182, "handle");
  return hlist_remove_handle(v7);
}

/* ===== hlist_remove_handle @ 0x9402DE38 size 856 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall hlist_remove_handle(__int64 a1, _QWORD *a2)
{
  __int64 v2; // x30
  __int64 v5; // x21
  __int64 result; // x0
  __int64 *v7; // x1
  unsigned int *v8; // x2
  _QWORD *v9; // x21
  __int64 v10; // x30
  __int64 v11; // x20
  __int64 *v12; // x23
  unsigned int *v13; // x24
  unsigned int v14; // w3
  unsigned int v15; // w19
  int v16; // w0
  unsigned int v17; // w20
  _QWORD *v18; // x19
  bool v19; // zf
  _QWORD *v20; // x19
  __int64 v21; // x19
  void (__fastcall *v22)(__int64, _QWORD); // x2
  _QWORD *v23; // x0
  _QWORD *v24; // x19
  _QWORD *v25; // x19
  __int64 v26; // x30
  __int64 v27; // x19
  int v28; // w2
  int v29; // w2
  __int64 v30; // x0
  _BYTE v31[48]; // [xsp+70h] [xbp-30h] BYREF

  if ( a1 != 0 )
  {
    if ( a2 != nullptr )
    {
      v5 = a1 + 16;
      mutex_acquire_timeout(a1 + 16, 0xFFFFFFFFLL);
      handle_close(a1, a2);
      return mutex_release(v5);
    }
  }
  else
  {
    panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 224, "hlist");
  }
  v9 = (_QWORD *)panic(
                   v2,
                   "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                   "lk/trusty/lib/trusty/handle.c",
                   225,
                   "handle");
  v11 = v10;
  v12 = v7;
  v13 = v8;
  v15 = v14;
  if ( v9 == nullptr )
  {
    panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 312, "hlist");
  }
  else if ( v7 != nullptr )
  {
    if ( v8 == nullptr )
    {
LABEL_28:
      panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 314, "event_ptr");
      goto LABEL_29;
    }
    event_init((__int64)v31, 0, 1);
    *v13 = 0;
    *v12 = 0;
    mutex_acquire_timeout((__int64)(v9 + 2), 0xFFFFFFFFLL);
    if ( v9[9] == 0 )
    {
      v9[9] = v31;
      v16 = handle_wait_any((__int64)v9, v12, v13, 1u);
      v17 = v16;
      if ( v16 >= 0 )
      {
        if ( v16 != 0 )
        {
LABEL_11:
          if ( v17 != 1 )
            goto LABEL_12;
        }
        else
        {
          do
          {
            mutex_release((__int64)(v9 + 2));
            v17 = event_wait_timeout((__int64)v31, v15);
            mutex_acquire_timeout((__int64)(v9 + 2), 0xFFFFFFFFLL);
            if ( (v17 & 0x80000000) != 0 )
            {
              v18 = (_QWORD *)v9[1];
              v19 = v9 == v18;
              v20 = v18 - 10;
              if ( v19 )
                goto LABEL_12;
              goto LABEL_22;
            }
            v17 = handle_wait_any((__int64)v9, v12, v13, 0);
          }
          while ( v17 == 0 );
          v24 = (_QWORD *)v9[1];
          v19 = v9 == v24;
          v20 = v24 - 10;
          if ( v19 )
            goto LABEL_11;
          do
          {
LABEL_22:
            mutex_acquire_timeout((__int64)(v20 + 3), 0xFFFFFFFFLL);
            v20[2] = 0;
            mutex_release((__int64)(v20 + 3));
            v25 = (_QWORD *)v20[11];
            v19 = v9 == v25;
            v20 = v25 - 10;
          }
          while ( !v19 );
          if ( v17 != 1 )
            goto LABEL_12;
        }
        v21 = *v12;
        v22 = *(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)(*v12 + 8) + 8LL);
        if ( v22 != nullptr )
          v22(*v12, *v13);
        v17 = 0;
        handle_incref(v21);
        v23 = (_QWORD *)v9[1];
        *v23 = *v9;
        *(_QWORD *)(*v9 + 8LL) = v23;
        v9[1] = 0;
        v9[1] = *(_QWORD *)(v21 + 88);
        *v9 = v21 + 80;
        **(_QWORD **)(v21 + 88) = v9;
        *(_QWORD *)(v21 + 88) = v9;
      }
LABEL_12:
      v9[9] = 0;
      mutex_release((__int64)(v9 + 2));
      event_destroy((__int64)v31);
      return v17;
    }
LABEL_29:
    panic(
      v11,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/handle.c",
      323,
      "hlist->wait_event == NULL");
    v27 = v26;
    v28 = trusty_alloc_als_slot();
    if ( v28 < 0 )
    {
      panic(v27, "failed (%d) to alloc als slot\n", v28);
      goto LABEL_33;
    }
    dword_94067920 = v28;
    result = trusty_register_notifier(qword_9405AC98);
    v29 = result;
    if ( (result & 0x80000000) != 0 )
    {
LABEL_33:
      v30 = panic(v27, "failed (%d) to register uctx notifier\n", v29);
      return uctx_get_current(v30);
    }
    return result;
  }
  panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/handle.c", 313, "handle_ptr");
  goto LABEL_28;
}

/* ===== uctx_get_current @ 0x9402E190 size 232 ===== */
__int64 uctx_get_current()
{
  __int64 v0; // x30
  __int64 v1; // x0
  __int64 v2; // x30
  __int64 *v3; // x1
  __int64 *v4; // x20
  __int64 v5; // x21
  __int64 v6; // x0
  __int64 v7; // x19

  _ReadStatusReg(TPIDR_EL1);
  v1 = panic(
         v0,
         "ASSERT FAILED at (%s:%d): %s\n",
         "lk/trusty/lib/tam/../trusty/include/lib/trusty/trusty_app.h",
         102,
         "slot < als_slot_cnt");
  v4 = v3;
  v5 = v1;
  if ( v3 == nullptr )
  {
    panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 164, "ctx");
    return 4294967291LL;
  }
  v6 = calloc(1, 616);
  v7 = v6;
  if ( v6 == 0 )
    return 4294967291LL;
  *(_QWORD *)(v6 + 520) = v5;
  hlist_init((_QWORD *)(v6 + 528));
  *v4 = v7;
  return 0;
}

/* ===== uctx_get_current_slot @ 0x9402E278 size 136 ===== */
__int64 uctx_get_current_slot()
{
  __int64 v0; // x30
  __int64 v1; // x20
  __int64 result; // x0
  __int64 v3; // x0

  v1 = v0;
  result = ((__int64 (*)(void))loc_9402E1F8)();
  if ( (_DWORD)result == 0 )
  {
    v3 = panic(
           v1,
           "ASSERT FAILED at (%s:%d): %s\n",
           "lk/trusty/lib/tam/../trusty/include/lib/trusty/trusty_app.h",
           109,
           "slot < als_slot_cnt");
    return uctx_destroy(v3);
  }
  return result;
}

/* ===== uctx_destroy @ 0x9402E300 size 696 ===== */
__int64 __fastcall uctx_destroy(__int64 a1)
{
  __int64 v1; // x30
  __int64 *v3; // x19
  __int64 *v4; // x20
  _QWORD *v6; // x0
  __int64 v7; // x1
  _DWORD *v8; // x2
  __int64 v9; // x30
  int v10; // w3
  int v11; // w19
  unsigned int *v12; // x4
  unsigned int v13; // w2
  _QWORD *v14; // x0
  unsigned int v15; // w1
  _QWORD *v16; // x2
  __int64 v17; // x30
  _QWORD *v18; // x1
  __int64 v19; // x19
  _QWORD *v20; // [xsp+28h] [xbp-38h]
  _DWORD *v21; // [xsp+58h] [xbp-8h]

  v3 = (__int64 *)(a1 + 8);
  v4 = (__int64 *)(a1 + 520);
  if ( a1 != 0 )
  {
    do
    {
      if ( *v3 != 0 )
      {
        printf("%s:%d: destroying a non-empty uctx!!!\n", "uctx_destroy", 191);
        hlist_remove_handle(a1 + 528, (_QWORD *)*v3);
        handle_decref(*v3);
        *v3 = 0;
      }
      ++v3;
    }
    while ( v3 != v4 );
    return free(a1);
  }
  v6 = (_QWORD *)panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 187, "ctx");
  if ( v6 == nullptr )
  {
    panic(v9, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 218, "ctx");
  }
  else if ( v7 != 0 )
  {
    if ( v8 == nullptr )
    {
LABEL_17:
      panic(v9, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 220, "id");
      goto LABEL_18;
    }
    if ( *v6 == -1 )
      return 4294967255LL;
    v10 = __clz(__rbit64(~*v6)) + 1;
    v11 = v10 - 1;
    if ( v6[v10] == 0 )
    {
      v21 = v8;
      v12 = (unsigned int *)((char *)v6 + (((__int64)v11 >> 3) & 0x1FFFFFFFFFFFFFFCLL));
      do
        v13 = __ldxr(v12);
      while ( __stxr(v13 | (1 << v11), v12) != 0 );
      v6[v10] = v7;
      hlist_add_handle(v6 + 66, v7);
      *v21 = v11;
      return 0;
    }
LABEL_18:
    v14 = (_QWORD *)panic(
                      v9,
                      "ASSERT FAILED at (%s:%d): %s\n",
                      "lk/trusty/lib/trusty/uctx.c",
                      226,
                      "ctx->handles[new_id] == NULL");
    if ( v14 == nullptr )
    {
      panic(v17, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 242, "ctx");
    }
    else if ( v16 != nullptr )
    {
      if ( v15 > 0x3F )
        return 4294967254LL;
      if ( ((*v14 >> v15) & 1) != 0 )
      {
        v18 = &v14[v15];
        v19 = v18[1];
        if ( v19 != 0 )
        {
          v20 = v16;
          handle_incref(v18[1]);
          *v20 = v19;
          return 0;
        }
        panic(
          v17,
          "ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/trusty/uctx.c",
          134,
          "ctx->handles[handle_id]");
      }
      return 4294967294LL;
    }
    panic(v17, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 243, "handle_ptr");
    return 4294967254LL;
  }
  panic(v9, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 219, "handle");
  goto LABEL_17;
}

/* ===== uctx_handle_put @ 0x9402E5B8 size 260 ===== */
__int64 __fastcall uctx_handle_put(_QWORD *a1, unsigned int a2, _QWORD *a3)
{
  __int64 v3; // x30
  unsigned __int64 v4; // x3
  _QWORD *v5; // x5
  _QWORD *v6; // x19
  int v7; // w1
  unsigned int *v8; // x3
  unsigned int v9; // w2
  __int64 result; // x0

  if ( a1 == nullptr )
  {
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 262, "ctx");
  }
  else if ( a3 != nullptr )
  {
    if ( a2 > 0x3F )
      return 4294967254LL;
    if ( ((*a1 >> a2) & 1) == 0 )
      return 4294967294LL;
    v4 = a2;
    v5 = &a1[a2];
    v6 = (_QWORD *)v5[1];
    if ( v6 == nullptr )
    {
      panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 134, "ctx->handles[handle_id]");
      return 4294967294LL;
    }
    v7 = ~(1 << a2);
    v8 = (unsigned int *)a1 + (v4 >> 5);
    do
      v9 = __ldxr(v8);
    while ( __stxr(v9 & v7, v8) != 0 );
    v5[1] = 0;
    hlist_remove_handle((__int64)(a1 + 66), v6);
    result = 0;
    *a3 = v6;
    return result;
  }
  panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 263, "handle_ptr");
  return 4294967254LL;
}

/* ===== uctx_handle_dup @ 0x9402E6BC size 600 ===== */
__int64 __fastcall uctx_handle_dup(unsigned int a1, unsigned int a2, __int64 a3)
{
  __int64 v3; // x23
  __int64 v4; // x30
  __int64 v5; // x20
  __int64 v7; // x22
  __int64 v8; // x21
  __int64 v9; // x0
  __int64 result; // x0
  int v11; // w19
  int v12; // w0
  unsigned int v13; // w0
  __int64 v14; // x30
  unsigned int v15; // w1
  unsigned int v16; // w19
  unsigned int v17; // w22
  __int64 v18; // x23
  __int64 v19; // x20
  int v20; // w19
  _QWORD *v21; // x1
  int v22; // w0
  int v23; // w1
  __int64 v24; // x2
  int v25; // w0
  _QWORD *v26; // x0
  unsigned int v27; // [xsp+18h] [xbp-78h]
  __int64 v28[10]; // [xsp+28h] [xbp-68h] BYREF
  __int64 v29; // [xsp+78h] [xbp-18h] BYREF
  unsigned int v30; // [xsp+80h] [xbp-10h] BYREF
  _DWORD v31[3]; // [xsp+84h] [xbp-Ch] BYREF
  __int64 v32; // [xsp+90h] [xbp+0h] BYREF
  __int64 v33; // [xsp+C8h] [xbp+38h] BYREF
  int v34; // [xsp+D0h] [xbp+40h] BYREF
  _BYTE v35[4]; // [xsp+D4h] [xbp+44h] BYREF
  int v36; // [xsp+D8h] [xbp+48h]

  v5 = a1;
  v7 = a2;
  v8 = v4;
  v9 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v9, (unsigned int)v5, &v33);
  if ( (_DWORD)result != 0 )
    return (int)result;
  if ( v33 == 0 )
  {
    v13 = panic(v8, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 305, "handle");
    v28[1] = (__int64)&v32;
    v28[2] = v14;
    v28[3] = a3;
    v28[4] = v5;
    v28[5] = v8;
    v28[6] = v7;
    v16 = v15;
    v28[7] = v3;
    v17 = v13;
    v18 = v14;
    v19 = uctx_get_current();
    v20 = ((__int64 (__fastcall *)(__int64, __int64 *, _DWORD *, _QWORD))loc_9402DED0)(v19 + 528, &v29, v31, v16);
    if ( (v20 & 0x80000000) == 0 )
    {
      if ( v29 == 0 )
      {
        panic(v18, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 357, "handle");
LABEL_21:
        panic(v18, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 144, "ctx");
LABEL_22:
        v27 = panic(
                v18,
                "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                "lk/trusty/lib/trusty/uctx.c",
                366,
                "tmp_event.handle < IPC_MAX_HANDLES");
        v26 = (_QWORD *)uctx_get_current();
        LODWORD(result) = uctx_handle_put(v26, v27, v28);
        if ( (_DWORD)result != 0 )
          return (int)result;
        handle_decref(v28[0]);
        return 0;
      }
      v21 = (_QWORD *)(v19 + 8);
      v22 = 0;
      if ( v19 == 0 )
        goto LABEL_21;
      do
      {
        if ( v29 == *v21 )
        {
          v23 = v22;
          goto LABEL_15;
        }
        ++v22;
        ++v21;
      }
      while ( v22 != 64 );
      v23 = -1;
LABEL_15:
      v24 = *(_QWORD *)(v29 + 96);
      v30 = v23;
      v31[1] = v24;
      ((void (__fastcall *)(__int64))loc_9402D978)(v29);
      if ( v30 > 0x3F )
        goto LABEL_22;
      v25 = copy_to_user(v17, &v30, 12);
      if ( v25 != 0 )
        return v25;
    }
    return v20;
  }
  v11 = ((__int64 (__fastcall *)(__int64, _BYTE *, _QWORD))loc_9402DB34)(v33, v35, (unsigned int)a3);
  if ( (v11 & 0x80000000) == 0 )
  {
    v34 = v5;
    v36 = *(_QWORD *)(v33 + 96);
    v12 = copy_to_user((unsigned int)v7, &v34, 12);
    if ( v12 != 0 )
      v11 = v12;
  }
  ((void (__fastcall *)(__int64))loc_9402D978)(v33);
  return v11;
}

/* ===== uctx_handle_set_cookie @ 0x9402E914 size 88 ===== */
__int64 __fastcall uctx_handle_set_cookie(unsigned int a1, unsigned int a2)
{
  __int64 v3; // x19
  __int64 v4; // x0
  __int64 result; // x0
  __int64 v6; // x0
  __int64 v7; // [xsp+28h] [xbp+28h] BYREF

  v3 = a2;
  v4 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v4, a1, &v7);
  if ( (_DWORD)result != 0 )
    return (int)result;
  v6 = v7;
  *(_QWORD *)(v7 + 96) = v3;
  ((void (__fastcall *)(__int64))loc_9402D978)(v6);
  return 0;
}

/* ===== uctx_get_current_slot2 @ 0x9402E96C size 252 ===== */
__int64 uctx_get_current_slot2()
{
  __int64 v0; // x30
  __int64 v1; // x21
  __int64 v2; // x0
  __int64 v3; // x1

  v1 = v0;
  if ( (unsigned int)((__int64 (*)(void))loc_9402E1F8)() != 0 )
    panic(
      v1,
      "ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/tam/../trusty/include/lib/trusty/trusty_app.h",
      102,
      "slot < als_slot_cnt");
  v2 = panic(
         v1,
         "ASSERT FAILED at (%s:%d): %s\n",
         "lk/trusty/lib/tam/../trusty/include/lib/trusty/trusty_app.h",
         109,
         "slot < als_slot_cnt");
  return uctx_handle_close(v2, v3);
}

/* ===== uctx_handle_close @ 0x9402EA68 size 52 ===== */
__int64 __fastcall uctx_handle_close(_QWORD *a1, unsigned int a2)
{
  __int64 result; // x0
  __int64 v3; // [xsp+18h] [xbp+18h] BYREF

  LODWORD(result) = uctx_handle_put(a1, a2, &v3);
  if ( (_DWORD)result != 0 )
    return (int)result;
  handle_decref(v3);
  return 0;
}

/* ===== uctx_wait_any @ 0x9402EA9C size 356 ===== */
__int64 __fastcall uctx_wait_any(__int64 a1, int *a2, __int64 a3)
{
  __int64 v3; // x30
  __int64 v6; // x22
  int v7; // w21
  _QWORD *v8; // x2
  int v9; // w1
  __int64 v11; // x30
  __int64 v12; // x0
  __int64 *v13; // x1
  unsigned int v14; // w2
  __int64 *v15; // x0
  __int64 v16; // t1
  __int64 v17; // [xsp+48h] [xbp+38h] BYREF

  v6 = v3;
  v7 = ((__int64 (__fastcall *)(__int64, __int64 *, int *, __int64))loc_9402DED0)(a1 + 528, &v17, a2 + 1, a3);
  if ( v7 < 0 )
    return v7;
  if ( v17 == 0 )
  {
    panic(v6, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 453, "handle");
    goto LABEL_11;
  }
  v8 = (_QWORD *)(a1 + 8);
  v9 = 0;
  if ( a1 != 0 )
  {
    while ( v17 != *v8 )
    {
      ++v9;
      ++v8;
      if ( v9 == 64 )
      {
        v9 = -1;
        break;
      }
    }
    a2[2] = *(_QWORD *)(v17 + 96);
    *a2 = v9;
    ((void (*)(void))loc_9402D978)();
    return v7;
  }
LABEL_11:
  panic(v6, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/uctx.c", 144, "ctx");
  v12 = panic(
          v11,
          "ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/tam/../trusty/include/lib/trusty/trusty_app.h",
          102,
          "slot < als_slot_cnt");
  v13 = (__int64 *)(v12 + 8);
  v14 = 0;
  v15 = (__int64 *)(v12 + 520);
  do
  {
    v16 = *v13++;
    if ( v16 != 0 )
      ++v14;
  }
  while ( v13 != v15 );
  return v14;
}

/* ===== uctx_get_handle_count @ 0x9402EC00 size 8 ===== */
__int64 __fastcall uctx_get_handle_count(__int64 a1)
{
  return *(unsigned int *)(a1 + 608);
}

/* ===== uctx_add_handle_count @ 0x9402EC08 size 16 ===== */
__int64 __fastcall uctx_add_handle_count(__int64 result, int a2)
{
  *(_DWORD *)(result + 608) += a2;
  return result;
}

/* ===== ipc_chan_ref_create @ 0x9402EC18 size 112 ===== */
__int64 __fastcall ipc_chan_ref_create(int a1, __int64 a2, __int64 *a3)
{
  __int64 result; // x0

  result = calloc(1, 232);
  if ( result != 0 )
  {
    *(_QWORD *)(result + 8) = a3;
    *(_QWORD *)result = a3;
    *(_QWORD *)(result + 184) = 0;
    *(_QWORD *)(result + 192) = 0;
    *a3 = result;
    a3[1] = result;
    *(_QWORD *)(result + 16) = 0;
    *(_QWORD *)(result + 24) = 0;
    *(_QWORD *)(result + 64) = 0;
    *(_QWORD *)(result + 72) = 0;
    *(_QWORD *)(result + 40) = a2;
    *(_DWORD *)(result + 48) = 0;
    *(_DWORD *)(result + 52) = a1;
  }
  return result;
}

/* ===== ipc_chan_connect @ 0x9402EC88 size 812 ===== */
__int64 __fastcall ipc_chan_connect(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  int v3; // w21
  __int64 v5; // x20
  __int64 v6; // x22
  __int64 v7; // x21
  __int64 v8; // x1
  __int64 v9; // x0
  __int64 v11; // x2
  __int64 v12; // x1
  __int64 v13; // x1
  __int64 v14; // x0
  __int64 v15; // x1
  __int64 *v16; // x0
  __int64 v17; // x1
  __int64 v18; // x1
  __int64 *v19; // x0
  __int64 v20; // x1
  __int64 v21; // x0
  __int64 v22; // x0
  __int64 v23; // x0
  __int64 v24; // x0
  __int64 v25; // [xsp+40h] [xbp+40h] BYREF
  __int64 *v26; // [xsp+48h] [xbp+48h]

  v3 = *(_DWORD *)(a1 + 72);
  v25 = 0;
  v26 = nullptr;
  if ( v3 != 1 )
    return 4294967293LL;
  if ( *(_QWORD *)(a2 + 40) == 0 )
    return 4294967253LL;
  v5 = a2;
  v6 = v2;
  if ( (unsigned __int8)is_tipc_uuid() != 0 )
    goto LABEL_10;
  if ( (*(_DWORD *)(a1 + 76) & 1) == 0 )
    return 4294967253LL;
  while ( 1 )
  {
    v7 = ipc_chan_ref_create(1, *(_QWORD *)(a1 + 64), &v25);
    if ( v7 == 0 )
      return 4294967291LL;
    if ( (unsigned int)ipc_msg_queue_create(*(unsigned int *)(a1 + 80), *(_QWORD *)(a1 + 88), v5 + 216) != 0 )
      goto LABEL_28;
    if ( (unsigned int)ipc_msg_queue_create(*(unsigned int *)(a1 + 80), *(_QWORD *)(a1 + 88), v7 + 216) != 0 )
    {
      ipc_msg_queue_destroy(*(_QWORD *)(v5 + 216));
      *(_QWORD *)(v5 + 216) = 0;
LABEL_28:
      v18 = v25;
      v19 = v26;
      if ( v25 == 0 )
        goto LABEL_45;
      goto LABEL_29;
    }
    v8 = *(_QWORD *)(v5 + 16);
    *(_DWORD *)(v7 + 48) = 1;
    *(_DWORD *)(v5 + 48) = 2;
    v9 = v5 + 16;
    if ( v8 == 0 && *(_QWORD *)(v5 + 24) == 0 )
    {
      v11 = v7 + 16;
      *(_QWORD *)(v5 + 16) = *(_QWORD *)v7;
      *(_QWORD *)(v5 + 24) = v7;
      v12 = *(_QWORD *)(v7 + 16);
      *(_QWORD *)(*(_QWORD *)v7 + 8LL) = v9;
      *(_QWORD *)v7 = v9;
      *(_QWORD *)(v5 + 32) = v7;
      if ( v12 == 0 && *(_QWORD *)(v7 + 24) == 0 )
      {
        v13 = v7 + 184;
        *(_QWORD *)(v7 + 16) = *(_QWORD *)v5;
        *(_QWORD *)(v7 + 24) = v5;
        *(_QWORD *)(*(_QWORD *)v5 + 8LL) = v11;
        *(_QWORD *)v5 = v11;
        *(_QWORD *)(v7 + 32) = v5;
        if ( *(_QWORD *)(v7 + 184) == 0 && *(_QWORD *)(v7 + 192) == 0 )
          break;
      }
    }
    panic(
      v6,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/include/reflist.h",
      62,
      "!list_in_list(&ref->ref_node)");
LABEL_10:
    if ( (*(_DWORD *)(a1 + 76) & 2) == 0 )
      return 4294967253LL;
  }
  v14 = *(_QWORD *)v7;
  *(_QWORD *)(v7 + 184) = *(_QWORD *)v7;
  *(_QWORD *)(v7 + 192) = v7;
  *(_QWORD *)(v14 + 8) = v13;
  *(_QWORD *)v7 = v13;
  v5 = v7 + 200;
  *(_QWORD *)(v7 + 200) = *(_QWORD *)(a1 + 200);
  *(_QWORD *)(v7 + 208) = a1 + 200;
  *(_QWORD *)(*(_QWORD *)(a1 + 200) + 8LL) = v7 + 200;
  *(_QWORD *)(a1 + 200) = v7 + 200;
  handle_incref(a1 + 96);
  handle_cancel_wait(a1 + 96);
  v15 = v25;
  v16 = v26;
  if ( v25 == 0 )
    goto LABEL_24;
  while ( 1 )
  {
    *v16 = v15;
    v17 = v25;
    v25 = 0;
    *(_QWORD *)(v17 + 8) = v16;
    v26 = nullptr;
    if ( v7 != *(_QWORD *)(v7 + 8) )
      return 0;
    if ( *(_QWORD *)(v7 + 32) != 0 )
    {
      while ( 1 )
      {
        v19 = (__int64 *)panic(
                           v6,
                           "ASSERT FAILED at (%s:%d): %s\n",
                           "lk/trusty/lib/trusty/ipc.c",
                           390,
                           (const char *)&loc_94051058);
LABEL_45:
        if ( v19 == nullptr )
          break;
LABEL_29:
        *v19 = v18;
        v20 = v25;
        v25 = 0;
        *(_QWORD *)(v20 + 8) = v19;
        v26 = nullptr;
        if ( v7 != *(_QWORD *)(v7 + 8) )
          return 4294967291LL;
        if ( *(_QWORD *)(v7 + 32) == 0 )
        {
          if ( *(_QWORD *)(v7 + 200) != 0 || *(_QWORD *)(v7 + 208) != 0 )
            goto LABEL_23;
          v21 = *(_QWORD *)(v7 + 224);
          if ( v21 != 0 )
            free(v21);
          v22 = *(_QWORD *)(v7 + 216);
          if ( v22 != 0 )
          {
            ipc_msg_queue_destroy(v22);
            *(_QWORD *)(v7 + 216) = 0;
          }
          free(v7);
          return 4294967291LL;
        }
      }
LABEL_25:
      panic(
        v6,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/include/reflist.h",
        71,
        "list_in_list(&ref->ref_node)");
      return 4294967291LL;
    }
    if ( *(_QWORD *)(v7 + 200) == 0 && *(_QWORD *)(v5 + 8) == 0 )
      break;
LABEL_23:
    v16 = (__int64 *)panic(
                       v6,
                       "ASSERT FAILED at (%s:%d): %s\n",
                       "lk/trusty/lib/trusty/ipc.c",
                       393,
                       "!list_in_list(&chan->node)");
LABEL_24:
    if ( v16 == nullptr )
      goto LABEL_25;
  }
  v23 = *(_QWORD *)(v7 + 224);
  if ( v23 != 0 )
    free(v23);
  v24 = *(_QWORD *)(v7 + 216);
  if ( v24 != 0 )
  {
    ipc_msg_queue_destroy(v24);
    *(_QWORD *)(v7 + 216) = 0;
  }
  free(v7);
  return 0;
}

/* ===== ipc_chan_close @ 0x9402EFB4 size 800 ===== */
__int64 __fastcall ipc_chan_close(__int64 a1)
{
  __int64 v1; // x20
  __int64 v2; // x21
  __int64 v3; // x30
  __int64 v5; // x22
  __int64 v6; // kr18_8
  __int64 result; // x0
  __int64 v8; // x1
  __int64 v9; // x2
  _QWORD *v10; // x0
  __int64 v11; // x3
  __int64 v12; // x2
  _QWORD *v13; // x0
  __int64 v14; // x0
  __int64 v15; // x0
  __int64 v16; // x1
  _QWORD *v17; // x0
  __int64 v18; // x1
  __int64 v19; // x2
  _QWORD *v20; // x0
  __int64 v21; // x3
  _QWORD *v22; // x0
  __int64 v23; // x0
  __int64 v24; // x0
  __int64 v25; // x0
  __int64 v26; // x0

  v5 = v3;
  v6 = (unsigned int)(*(_DWORD *)(a1 + 48) - 1);
  result = (__int64)&loc_9402EFF4 + 4 * jpt_9402EFF0[(unsigned int)v6];
  switch ( (int)v6 )
  {
    case 0:
      goto LABEL_14;
    case 1:
    case 2:
      goto LABEL_25;
    case 3:
      goto LABEL_15;
    case 4:
      v8 = a1 + 200;
      v9 = *(_QWORD *)(a1 + 200);
      v10 = *(_QWORD **)(a1 + 208);
      if ( v9 != 0 )
        goto LABEL_4;
      break;
    default:
      result = v6;
      goto LABEL_15;
  }
  while ( 1 )
  {
    if ( v10 != nullptr )
    {
LABEL_4:
      *v10 = v9;
      v11 = a1 + 184;
      v12 = *(_QWORD *)(a1 + 184);
      *(_QWORD *)(*(_QWORD *)(a1 + 200) + 8LL) = v10;
      *(_QWORD *)(v8 + 8) = 0;
      *(_QWORD *)(a1 + 200) = 0;
      v13 = *(_QWORD **)(a1 + 192);
      if ( v12 != 0 )
        goto LABEL_5;
    }
    else
    {
LABEL_44:
      v13 = (_QWORD *)panic(
                        v5,
                        "ASSERT FAILED at (%s:%d): %s\n",
                        "lk/trusty/lib/trusty/ipc.c",
                        461,
                        "list_in_list(&chan->node)");
    }
    if ( v13 == nullptr )
    {
LABEL_33:
      while ( 1 )
      {
        panic(
          v5,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/include/reflist.h",
          71,
          "list_in_list(&ref->ref_node)");
LABEL_34:
        if ( *(_QWORD *)(v1 + 32) != 0 )
          goto LABEL_42;
        if ( *(_QWORD *)(v1 + 200) != 0 || *(_QWORD *)(v18 + 8) != 0 )
          goto LABEL_24;
        v23 = *(_QWORD *)(v1 + 224);
        if ( v23 != 0 )
          free(v23);
        v24 = *(_QWORD *)(v1 + 216);
        if ( v24 != 0 )
        {
          ipc_msg_queue_destroy(v24);
          *(_QWORD *)(v1 + 216) = 0;
        }
        free(v1);
        v1 = *(_QWORD *)(a1 + 32);
LABEL_29:
        *(_DWORD *)(v2 + 48) = 4;
        v2 = v1;
LABEL_17:
        v16 = *(_QWORD *)(a1 + 16);
        v17 = *(_QWORD **)(a1 + 24);
        if ( v16 != 0 || v17 != nullptr )
        {
          *v17 = v16;
          *(_QWORD *)(*(_QWORD *)(a1 + 16) + 8LL) = v17;
          *(_QWORD *)(a1 + 24) = 0;
          *(_QWORD *)(a1 + 16) = 0;
          result = *(_QWORD *)(v2 + 8);
          if ( v2 != result )
          {
            *(_QWORD *)(a1 + 32) = 0;
            return result;
          }
          if ( *(_QWORD *)(v2 + 32) != 0 )
            goto LABEL_42;
          if ( *(_QWORD *)(v2 + 200) != 0 || *(_QWORD *)(v2 + 208) != 0 )
            goto LABEL_24;
          v25 = *(_QWORD *)(v2 + 224);
          if ( v25 != 0 )
            free(v25);
          v26 = *(_QWORD *)(v2 + 216);
          if ( v26 != 0 )
          {
            ipc_msg_queue_destroy(v26);
            *(_QWORD *)(v2 + 216) = 0;
          }
          result = free(v2);
          *(_QWORD *)(a1 + 32) = 0;
          return result;
        }
      }
    }
LABEL_5:
    *v13 = v12;
    *(_QWORD *)(*(_QWORD *)(a1 + 184) + 8LL) = v13;
    *(_QWORD *)(v11 + 8) = 0;
    *(_QWORD *)(a1 + 184) = 0;
    if ( a1 != *(_QWORD *)(a1 + 8) )
      goto LABEL_14;
    if ( *(_QWORD *)(a1 + 32) == 0 )
      break;
LABEL_42:
    v10 = (_QWORD *)panic(
                      v5,
                      "ASSERT FAILED at (%s:%d): %s\n",
                      "lk/trusty/lib/trusty/ipc.c",
                      390,
                      (const char *)&loc_94051058);
  }
  if ( *(_QWORD *)(a1 + 200) == 0 && *(_QWORD *)(v8 + 8) == 0 )
  {
    v14 = *(_QWORD *)(a1 + 224);
    if ( v14 != 0 )
      free(v14);
    v15 = *(_QWORD *)(a1 + 216);
    if ( v15 != 0 )
    {
      ipc_msg_queue_destroy(v15);
      *(_QWORD *)(a1 + 216) = 0;
    }
    free(a1);
LABEL_14:
    result = 4;
    *(_DWORD *)(a1 + 48) = 4;
    goto LABEL_15;
  }
LABEL_24:
  panic(v5, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 393, "!list_in_list(&chan->node)");
LABEL_25:
  *(_DWORD *)(a1 + 48) = 4;
  result = handle_cancel_wait(a1 + 80);
LABEL_15:
  v1 = *(_QWORD *)(a1 + 32);
  v2 = v1;
  if ( v1 != 0 )
  {
    switch ( *(_DWORD *)(v1 + 48) )
    {
      case 1:
        *(_DWORD *)(v1 + 48) = 4;
        goto LABEL_17;
      case 2:
      case 3:
        *(_DWORD *)(v1 + 48) = 4;
        handle_cancel_wait(v1 + 80);
        v2 = *(_QWORD *)(a1 + 32);
        goto LABEL_17;
      case 5:
        v18 = v1 + 200;
        v19 = *(_QWORD *)(v1 + 200);
        v20 = *(_QWORD **)(v1 + 208);
        if ( v19 == 0 && v20 == nullptr )
          goto LABEL_44;
        *v20 = v19;
        v21 = *(_QWORD *)(v1 + 184);
        *(_QWORD *)(*(_QWORD *)(v1 + 200) + 8LL) = v20;
        *(_QWORD *)(v1 + 208) = 0;
        *(_QWORD *)(v1 + 200) = 0;
        v22 = *(_QWORD **)(v1 + 192);
        if ( v21 == 0 && v22 == nullptr )
          goto LABEL_33;
        *v22 = v21;
        *(_QWORD *)(*(_QWORD *)(v1 + 184) + 8LL) = v22;
        *(_QWORD *)(v1 + 192) = 0;
        *(_QWORD *)(v1 + 184) = 0;
        if ( v1 != *(_QWORD *)(v1 + 8) )
          goto LABEL_29;
        goto LABEL_34;
      default:
        goto LABEL_17;
    }
  }
  return result;
}

/* ===== ipc_is_channel @ 0x9402F2D4 size 24 ===== */
bool __fastcall ipc_is_channel(__int64 a1)
{
  return *(_QWORD *)(a1 + 8) == (_QWORD)qword_9405ACC8;
}

/* ===== ipc_chan_release @ 0x9402F2EC size 1008 ===== */
__int64 __fastcall ipc_chan_release(__int64 a1)
{
  _QWORD *v1; // x20
  __int64 *v2; // x21
  __int64 v3; // x30
  __int64 v5; // x22
  __int64 v6; // x1
  _QWORD *v7; // x0
  _QWORD *v8; // x0
  __int64 v9; // x0
  __int64 v10; // x0
  __int64 v11; // x0
  __int64 v12; // x30
  __int64 v13; // x20
  __int64 v14; // x19
  __int64 result; // x0
  __int64 v16; // x0
  __int64 v17; // x30
  __int64 v18; // x19
  __int64 v19; // x21
  unsigned int v20; // w1
  __int64 v21; // x20
  __int64 v22; // x0
  __int64 v23; // x30
  __int64 v24; // x20
  __int64 v25; // x19
  __int64 v26; // x4
  __int64 v27; // x5
  __int64 v28; // x6
  __int64 v29; // x7
  int v30; // w0
  __int64 v31; // x1
  bool v32; // zf
  __int64 v33; // x0
  unsigned int v34; // w19
  __int64 v35; // x2
  char v36; // w0
  __int64 v37; // x0
  __int64 v38; // [xsp+8h] [xbp-78h]
  __int64 v39; // [xsp+10h] [xbp-70h]
  __int64 v40; // [xsp+18h] [xbp-68h]
  _QWORD v41[6]; // [xsp+30h] [xbp-50h] BYREF
  _QWORD v42[4]; // [xsp+60h] [xbp-20h] BYREF
  __int64 vars0; // [xsp+80h] [xbp+0h] BYREF

  v5 = v3;
  if ( a1 == 0 )
    goto LABEL_11;
  if ( !ipc_is_channel(a1) )
    goto LABEL_12;
  v2 = &qword_9405BFF0[2];
  v1 = (_QWORD *)(a1 - 80);
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  v6 = *(_QWORD *)(a1 - 16);
  v7 = *(_QWORD **)(a1 - 8);
  if ( v6 == 0 )
    goto LABEL_9;
  while ( 1 )
  {
    *v7 = v6;
    *(_QWORD *)(*(_QWORD *)(a1 - 16) + 8LL) = v7;
    *(_QWORD *)(a1 - 8) = 0;
    v8 = *(_QWORD **)(a1 - 72);
    *(_QWORD *)(a1 - 16) = 0;
    if ( v1 != v8 )
      return mutex_release(v2[495]);
    if ( *(_QWORD *)(a1 - 48) != 0 )
    {
      v11 = panic(
              v5,
              "ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/ipc.c",
              390,
              (const char *)&loc_94051058);
      v42[0] = &vars0;
      v42[1] = v12;
      v42[2] = a1;
      v42[3] = v1;
      v13 = v11;
      v14 = v12;
      if ( v11 != 0 )
      {
        if ( ipc_is_channel(v11) )
        {
          mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
          ipc_chan_close(v13 - 80);
          return mutex_release(-536630024);
        }
      }
      else
      {
        panic(v12, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 492, "chandle");
      }
      v16 = panic(
              v14,
              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/ipc.c",
              493,
              "ipc_is_channel(chandle)");
      v41[0] = v42;
      v41[1] = v17;
      v41[2] = v14;
      v41[3] = v13;
      v41[4] = v2;
      v18 = v16;
      v19 = v17;
      v21 = v20;
      if ( v16 != 0 )
      {
        if ( ipc_is_channel(v16) )
        {
          result = 17;
          if ( (v21 & 0x11) != 0 )
          {
            mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
            if ( (v21 & 0x10) != 0 )
              *(_DWORD *)(v18 - 24) &= ~2u;
            if ( (v21 & 1) != 0 )
              *(_DWORD *)(v18 - 24) &= ~4u;
            return mutex_release(-536630024);
          }
          return result;
        }
      }
      else
      {
        panic(v17, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 563, "chandle");
      }
      v22 = panic(
              v19,
              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/ipc.c",
              564,
              "ipc_is_channel(chandle)");
      v38 = v23;
      v39 = v18;
      v40 = v21;
      v24 = v22;
      v25 = v23;
      if ( v22 != 0 )
      {
        if ( ipc_is_channel(v22) )
        {
          mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
          v30 = *(_DWORD *)(v24 - 32);
          if ( v30 != 0 )
          {
            v31 = *(unsigned int *)(v24 - 24);
            v32 = v30 == 4;
            v33 = *(_QWORD *)(v24 + 136);
            if ( v32 )
              v34 = 4;
            else
              v34 = 0;
            v35 = v34 | 1;
            if ( (v31 & 4) != 0 )
              v34 |= 1u;
            if ( v33 != 0 )
            {
              v36 = ((__int64 (__fastcall *)(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, _QWORD *, __int64, __int64, __int64, __int64))ipc_msg_queue_is_empty)(
                      v33,
                      v31,
                      v35,
                      v31 & 4,
                      v26,
                      v27,
                      v28,
                      v29,
                      v41,
                      v38,
                      v39,
                      v40,
                      v19);
              LODWORD(v31) = *(_DWORD *)(v24 - 24);
              if ( v36 == 0 )
                v34 |= 8u;
            }
            if ( (v31 & 2) != 0 )
              v34 |= 0x10u;
            mutex_release(-536630024);
            return v34;
          }
          else
          {
            mutex_release(-536630024);
            return 2;
          }
        }
      }
      else
      {
        panic(v23, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 520, "chandle");
      }
      v37 = panic(
              v25,
              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/ipc.c",
              521,
              "ipc_is_channel(chandle)");
      return ipc_is_port(v37);
    }
    if ( v1[25] == 0 )
    {
LABEL_13:
      if ( v1[26] == 0 )
        break;
    }
    v7 = (_QWORD *)panic(
                     v5,
                     "ASSERT FAILED at (%s:%d): %s\n",
                     "lk/trusty/lib/trusty/ipc.c",
                     393,
                     "!list_in_list(&chan->node)");
LABEL_9:
    if ( v7 == nullptr )
    {
      panic(
        v5,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/include/reflist.h",
        71,
        "list_in_list(&ref->ref_node)");
LABEL_11:
      panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 506, "chandle");
LABEL_12:
      panic(
        v5,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/ipc.c",
        507,
        "ipc_is_channel(chandle)");
      goto LABEL_13;
    }
  }
  v9 = v1[28];
  if ( v9 != 0 )
    free(v9);
  v10 = v1[27];
  if ( v10 != 0 )
  {
    ipc_msg_queue_destroy(v10);
    v1[27] = 0;
  }
  free(v1);
  return mutex_release(v2[495]);
}

/* ===== ipc_is_port @ 0x9402F6DC size 24 ===== */
bool __fastcall ipc_is_port(__int64 a1)
{
  return *(_QWORD *)(a1 + 8) == (_QWORD)qword_9405AD30;
}

/* ===== ipc_port_destroy @ 0x9402F6F4 size 768 ===== */
__int64 __fastcall ipc_port_destroy(__int64 a1)
{
  _QWORD *v1; // x22
  __int64 *v2; // x23
  __int64 v3; // x30
  _QWORD *v4; // x19
  __int64 v5; // x20
  __int64 v6; // x0
  __int64 v7; // x1
  _QWORD *v8; // x19
  __int64 v10; // x0
  __int64 v11; // x30
  __int64 v12; // x21
  __int64 v13; // x24
  __int64 v14; // x0
  __int64 *v15; // x1
  _QWORD *v16; // x2
  _QWORD *v17; // x1
  _QWORD *v18; // x0
  __int64 v19; // x3
  _QWORD *v20; // x2
  __int64 v21; // x0
  __int64 v22; // x0

  v4 = (_QWORD *)a1;
  v5 = v3;
  if ( a1 == 0 )
  {
    panic(v3, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 217, "phandle");
  }
  else if ( ipc_is_port(a1) )
  {
    v6 = (__int64)(v4 - 12);
    if ( (_QWORD *)v4[14] != v4 + 13 )
      goto LABEL_10;
    v7 = v4[15];
    v8 = v4 + 15;
    if ( v7 == 0 )
      goto LABEL_6;
    do
    {
      v6 = panic(
             v5,
             "DEBUG ASSERT FAILED at (%s:%d): %s\n",
             "lk/trusty/lib/trusty/ipc.c",
             226,
             "!list_in_list(&port->node)");
LABEL_6:
      ;
    }
    while ( v8[1] != 0 );
    return free(v6);
  }
  panic(v5, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 218, (const char *)invalid_handle_stub);
LABEL_10:
  v10 = panic(
          v5,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/trusty/ipc.c",
          225,
          "list_is_empty(&port->pending_list)");
  v12 = v10;
  v13 = v11;
  if ( v10 != 0 )
  {
    if ( ipc_is_port(v10) )
    {
      v2 = &qword_9405BFF0[2];
      v1 = (_QWORD *)(v12 - 96);
      mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
      v14 = *(_QWORD *)(v12 + 120);
      *(_DWORD *)(v12 - 24) = 2;
      v15 = *(__int64 **)(v12 + 128);
      if ( v14 == 0 )
        goto LABEL_25;
LABEL_13:
      *v15 = v14;
      *(_QWORD *)(v1[27] + 8LL) = v15;
      v1[28] = 0;
      v1[27] = 0;
      ((void (__fastcall *)(__int64))loc_9402D978)(v12);
LABEL_14:
      v4 = (_QWORD *)(v1[26] - 200LL);
      v5 = *(_QWORD *)(v1[26] + 8LL) - 200LL;
      if ( v1 == v4 )
        return mutex_release(v2[495]);
      while ( 1 )
      {
        ipc_chan_close((__int64)v4);
        v16 = (_QWORD *)v4[26];
        v17 = v4 + 25;
        v18 = v4 + 23;
        *v16 = v4[25];
        v19 = v4[23];
        *(_QWORD *)(v4[25] + 8LL) = v16;
        v4[26] = 0;
        v4[25] = 0;
        v20 = (_QWORD *)v4[24];
        if ( v19 == 0 )
          goto LABEL_22;
        while ( 1 )
        {
          *v20 = v19;
          *(_QWORD *)(*v18 + 8LL) = v20;
          v18[1] = 0;
          *v18 = 0;
          if ( v4 != (_QWORD *)v4[1] )
            break;
          if ( v4[4] != 0 )
            goto LABEL_24;
          if ( *v17 == 0 )
          {
LABEL_29:
            if ( v17[1] == 0 )
            {
              v21 = v4[28];
              if ( v21 != 0 )
                free(v21);
              v22 = v4[27];
              if ( v22 != 0 )
              {
                ipc_msg_queue_destroy(v22);
                v4[27] = 0;
              }
              free(v4);
              break;
            }
          }
          v18 = (_QWORD *)panic(
                            v13,
                            "ASSERT FAILED at (%s:%d): %s\n",
                            "lk/trusty/lib/trusty/ipc.c",
                            393,
                            "!list_in_list(&chan->node)");
LABEL_22:
          if ( v20 == nullptr )
          {
            panic(
              v13,
              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/include/reflist.h",
              71,
              "list_in_list(&ref->ref_node)");
LABEL_24:
            v14 = panic(
                    v13,
                    "ASSERT FAILED at (%s:%d): %s\n",
                    "lk/trusty/lib/trusty/ipc.c",
                    390,
                    (const char *)&loc_94051058);
LABEL_25:
            if ( v15 != nullptr )
              goto LABEL_13;
            goto LABEL_14;
          }
        }
        v4 = (_QWORD *)v5;
        ((void (__fastcall *)(__int64))loc_9402D978)(v12);
        v5 = *(_QWORD *)(v5 + 208) - 200LL;
        if ( v1 == v4 )
          return mutex_release(v2[495]);
      }
    }
  }
  else
  {
    panic(v11, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 170, "phandle");
  }
  panic(v13, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 171, (const char *)invalid_handle_stub);
  goto LABEL_29;
}

/* ===== ipc_port_has_pending @ 0x9402F9F4 size 216 ===== */
__int64 __fastcall ipc_port_has_pending(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x20
  BOOL v5; // w21
  __int64 v6; // x0

  v3 = v1;
  if ( a1 == 0 )
  {
    panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 365, "phandle");
  }
  else if ( ipc_is_port(a1) )
  {
    mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
    if ( *(_DWORD *)(a1 - 24) == 1 )
    {
      v5 = *(_QWORD *)(a1 + 112) != a1 + 104;
      mutex_release(-536630024);
      return v5;
    }
    else
    {
      mutex_release(-536630024);
      return 2;
    }
  }
  v6 = panic(
         v3,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         "lk/trusty/lib/trusty/ipc.c",
         366,
         (const char *)invalid_handle_stub);
  return ipc_port_create(v6);
}

/* ===== ipc_port_create @ 0x9402FACC size 288 ===== */
__int64 __fastcall ipc_port_create(__int64 a1, __int64 a2, int a3, __int64 a4, int a5, _QWORD *a6)
{
  __int64 v12; // x0
  __int64 v13; // x20
  unsigned int v14; // w0
  unsigned int v15; // w19

  if ( a1 == 0 || (unsigned int)(a3 - 1) > 0x1F || (unsigned __int64)(a4 - 1) > 0xFFF )
    return 4294967288LL;
  v12 = calloc(1, 232);
  v13 = v12;
  if ( v12 == 0 )
    return 4294967291LL;
  v14 = strlcpy(v12, a2, 64);
  if ( v14 != 0 )
  {
    v15 = -25;
    if ( v14 <= 0x3F )
    {
      *(_QWORD *)(v13 + 64) = a1;
      *(_DWORD *)(v13 + 80) = a3;
      *(_QWORD *)(v13 + 88) = a4;
      *(_DWORD *)(v13 + 76) = a5;
      *(_DWORD *)(v13 + 72) = 0;
      *(_QWORD *)(v13 + 208) = v13 + 200;
      *(_QWORD *)(v13 + 200) = v13 + 200;
      handle_init(v13 + 96, (__int64)qword_9405AD30);
      *a6 = v13 + 96;
      return 0;
    }
  }
  else
  {
    v15 = -8;
  }
  free(v13);
  return v15;
}

/* ===== ipc_port_publish @ 0x9402FBEC size 916 ===== */
__int64 __fastcall ipc_port_publish(__int64 a1)
{
  __int64 *v1; // x21
  __int64 v2; // x23
  __int64 (__fastcall **v3)(); // x25
  __int64 v4; // x30
  __int64 v6; // x20
  __int64 v7; // x22
  __int64 *v8; // x22
  bool v9; // zf
  unsigned int v10; // w24
  __int64 (__fastcall *v12)(); // x2
  __int64 v13; // x19
  __int64 v14; // x22
  __int64 v15; // x24
  __int64 v16; // x1
  __int64 v17; // x0
  _QWORD *v18; // x24
  _QWORD *v19; // x1
  __int64 v20; // x2
  _QWORD *v21; // x1
  __int64 v22; // x1
  _QWORD *v23; // x0
  __int64 v24; // x1
  __int64 v25; // x0
  __int64 v26; // x0
  __int64 v27; // x0
  __int64 v28; // [xsp+50h] [xbp+50h] BYREF
  _QWORD *v29; // [xsp+58h] [xbp+58h]

  v6 = v4;
  if ( a1 == 0 )
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 240, "phandle");
  }
  else if ( ipc_is_port(a1) )
  {
    v1 = &qword_9405BFF0[2];
    v2 = a1 - 96;
    mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
    if ( *(_QWORD *)(a1 + 120) == 0 )
      goto LABEL_5;
    do
    {
      panic(
        v6,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/ipc.c",
        246,
        "!list_in_list(&port->node)");
LABEL_5:
      ;
    }
    while ( *(_QWORD *)(a1 + 128) != 0 );
    v3 = &off_9405A000;
    v7 = -536630304;
    if ( &qword_9405ACB8 == (__int64 *)-536630088LL )
      goto LABEL_14;
    while ( (unsigned int)strcmp(a1 - 96, v7) != 0 )
    {
      v8 = *(__int64 **)(v7 + 224);
      v9 = &qword_9405ACB8 == v8;
      v7 = (__int64)(v8 - 27);
      if ( v9 )
        goto LABEL_14;
    }
    v10 = -14;
    if ( v7 == 0 )
    {
LABEL_14:
      v12 = v3[407];
      *(_DWORD *)(a1 - 24) = 1;
      *(_QWORD *)(v2 + 216) = v12;
      *(_QWORD *)(v2 + 224) = v3 + 407;
      *((_QWORD *)v12 + 1) = v2 + 216;
      v3[407] = (__int64 (__fastcall *)())(v2 + 216);
      handle_incref(v2 + 96);
      v28 = 0;
      v29 = nullptr;
      v13 = -536630240;
      v14 = MEMORY[0xFFFFFFFFE003ACF0] - 200LL;
      if ( &off_9405ACE8 == (_UNKNOWN **)-536630040LL )
      {
LABEL_18:
        v10 = 0;
        goto LABEL_11;
      }
      while ( 1 )
      {
        v15 = *(_QWORD *)(v13 + 224);
        if ( (unsigned int)strcmp(v15, v2) != 0 )
          goto LABEL_16;
        free(v15);
        *(_QWORD *)(v13 + 224) = 0;
        if ( v28 != 0 )
          break;
LABEL_21:
        if ( v29 != nullptr )
          break;
        v16 = *(_QWORD *)v13;
        v29 = (_QWORD *)v13;
        v17 = v13 + 184;
        v28 = v16;
        *(_QWORD *)(*(_QWORD *)v13 + 8LL) = &v28;
        *(_QWORD *)v13 = &v28;
        v18 = (_QWORD *)(v13 + 200);
        v19 = *(_QWORD **)(v13 + 208);
        *v19 = *(_QWORD *)(v13 + 200);
        v20 = *(_QWORD *)(v13 + 184);
        *(_QWORD *)(*(_QWORD *)(v13 + 200) + 8LL) = v19;
        *(_QWORD *)(v13 + 208) = 0;
        *(_QWORD *)(v13 + 200) = 0;
        v21 = *(_QWORD **)(v13 + 192);
        if ( v20 == 0 && v21 == nullptr )
        {
          while ( 1 )
          {
            v23 = (_QWORD *)panic(
                              v6,
                              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                              "lk/trusty/include/reflist.h",
                              71,
                              "list_in_list(&ref->ref_node)");
LABEL_39:
            if ( v23 != nullptr )
              goto LABEL_27;
          }
        }
        *v21 = v20;
        *(_QWORD *)(*(_QWORD *)v17 + 8LL) = v21;
        *(_QWORD *)(v13 + 192) = 0;
        *(_QWORD *)v17 = 0;
        if ( v13 == *(_QWORD *)(v13 + 8) )
        {
          while ( 1 )
          {
            if ( *(_QWORD *)(v13 + 32) != 0 )
              goto LABEL_41;
            if ( *v18 == 0 && *(_QWORD *)(v13 + 208) == 0 )
              break;
LABEL_30:
            panic(
              v6,
              "ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/ipc.c",
              393,
              "!list_in_list(&chan->node)");
          }
          v25 = *(_QWORD *)(v13 + 216);
          if ( v25 != 0 )
          {
            ipc_msg_queue_destroy(v25);
            *(_QWORD *)(v13 + 216) = 0;
          }
          free(v13);
        }
        if ( (unsigned int)ipc_chan_connect(v2, v13) != 0 )
          ipc_chan_close(v13);
        v22 = v28;
        v23 = v29;
        if ( v28 == 0 )
          goto LABEL_39;
LABEL_27:
        *v23 = v22;
        v24 = v28;
        v28 = 0;
        *(_QWORD *)(v24 + 8) = v23;
        v29 = nullptr;
        if ( v13 == *(_QWORD *)(v13 + 8) )
        {
          if ( *(_QWORD *)(v13 + 32) == 0 )
          {
            if ( *v18 == 0 )
            {
LABEL_42:
              if ( *(_QWORD *)(v13 + 208) == 0 )
              {
                v26 = *(_QWORD *)(v13 + 224);
                if ( v26 != 0 )
                  free(v26);
                v27 = *(_QWORD *)(v13 + 216);
                if ( v27 != 0 )
                {
                  ipc_msg_queue_destroy(v27);
                  *(_QWORD *)(v13 + 216) = 0;
                }
                free(v13);
                goto LABEL_16;
              }
            }
            goto LABEL_30;
          }
LABEL_41:
          panic(
            v6,
            "ASSERT FAILED at (%s:%d): %s\n",
            "lk/trusty/lib/trusty/ipc.c",
            390,
            (const char *)&loc_94051058);
          goto LABEL_42;
        }
LABEL_16:
        v9 = &off_9405ACE8 == (_UNKNOWN **)(v14 + 200);
        v13 = v14;
        v14 = *(_QWORD *)(v14 + 208) - 200LL;
        if ( v9 )
          goto LABEL_18;
      }
      panic(
        v6,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/include/reflist.h",
        62,
        "!list_in_list(&ref->ref_node)");
      goto LABEL_21;
    }
LABEL_11:
    mutex_release(v1[495]);
    return v10;
  }
  panic(
    v6,
    "DEBUG ASSERT FAILED at (%s:%d): %s\n",
    "lk/trusty/lib/trusty/ipc.c",
    241,
    (const char *)invalid_handle_stub);
  goto LABEL_14;
}

/* ===== sys_port_connect @ 0x9402FF80 size 308 ===== */
__int64 __fastcall sys_port_connect(unsigned int a1, int a2, __int64 a3, int a4)
{
  __int64 v8; // x24
  _QWORD *v9; // x26
  __int64 result; // x0
  int v11; // w19
  unsigned int v12; // w0
  unsigned int v13; // [xsp+54h] [xbp+54h] BYREF
  __int64 v14; // [xsp+58h] [xbp+58h] BYREF
  char v15[64]; // [xsp+60h] [xbp+60h] BYREF

  v8 = *(_QWORD *)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 144LL);
  v9 = (_QWORD *)uctx_get_current();
  v14 = 0;
  LODWORD(result) = copy_from_user_string(v15, a1, 64);
  if ( (result & 0x80000000) != 0 )
    return (int)result;
  if ( (unsigned int)result > 0x3F )
    return -8;
  v11 = ipc_port_create(v8 + 32, (__int64)v15, a2, a3, a4, &v14);
  if ( v11 == 0 )
  {
    v11 = ((__int64 (__fastcall *)(_QWORD *, __int64, unsigned int *))loc_9402E3B0)(v9, v14, &v13);
    if ( v11 == 0 )
    {
      uctx_add_handle_count((__int64)v9, 1);
      v11 = ipc_port_publish(v14);
      if ( v11 == 0 )
      {
        v12 = strlen(v15);
        tam_port_publish(v15, v12);
        return v13;
      }
      uctx_handle_put(v9, v13, &v14);
    }
    ((void (__fastcall *)(__int64))loc_9402D978)(v14);
  }
  return v11;
}

/* ===== ipc_chan_open @ 0x940300B4 size 704 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall ipc_chan_open(__int64 a1, __int64 a2, unsigned __int64 a3, char a4, _QWORD *a5)
{
  __int64 v5; // x30
  __int64 v7; // x24
  unsigned __int64 v11; // x0
  __int64 v12; // x22
  __int64 v13; // x19
  __int64 *v14; // x19
  bool v15; // zf
  unsigned int v16; // w19
  __int64 v17; // x0
  _QWORD *v18; // x0
  __int64 v19; // x1
  __int64 v21; // x0
  __int64 v22; // x4
  __int64 v23; // x2
  __int64 v24; // x0
  __int64 v25; // x1
  __int64 v26; // x0
  __int64 v27; // x0
  __int64 v29; // [xsp+60h] [xbp+60h] BYREF
  _QWORD *v30; // [xsp+68h] [xbp+68h]

  v29 = 0;
  v30 = nullptr;
  v7 = v5;
  if ( a1 == 0 )
    return 4294967288LL;
  v11 = strnlen(a2, a3);
  if ( v11 >= a3 || v11 == 0 )
    return 4294967288LL;
  v12 = ipc_chan_ref_create(0, a1, &v29);
  if ( v12 != 0 )
  {
    mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
    v13 = -536630304;
    if ( &qword_9405ACB8 == (__int64 *)-536630088LL )
      goto LABEL_13;
    while ( (unsigned int)strcmp(a2, v13) != 0 )
    {
      v14 = *(__int64 **)(v13 + 224);
      v15 = &qword_9405ACB8 == v14;
      v13 = (__int64)(v14 - 27);
      if ( v15 )
        goto LABEL_13;
    }
    if ( v13 == 0 )
      goto LABEL_13;
    v16 = ipc_chan_connect(v13, v12);
    if ( v16 == 0 )
      goto LABEL_11;
    while ( 1 )
    {
LABEL_15:
      v18 = v30;
      if ( v29 == 0 && v30 == nullptr )
      {
        panic(
          v7,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/include/reflist.h",
          71,
          "list_in_list(&ref->ref_node)");
        return 4294967288LL;
      }
      *v30 = v29;
      v19 = v29;
      v29 = 0;
      *(_QWORD *)(v19 + 8) = v18;
      v30 = nullptr;
      if ( v12 != *(_QWORD *)(v12 + 8) )
        goto LABEL_17;
      if ( *(_QWORD *)(v12 + 32) != 0 )
        break;
      if ( *(_QWORD *)(v12 + 200) == 0 && *(_QWORD *)(v12 + 208) == 0 )
      {
        v26 = *(_QWORD *)(v12 + 224);
        if ( v26 != 0 )
          free(v26);
        v27 = *(_QWORD *)(v12 + 216);
        if ( v27 != 0 )
        {
          ipc_msg_queue_destroy(v27);
          *(_QWORD *)(v12 + 216) = 0;
        }
        free(v12);
LABEL_17:
        mutex_release(-536630024);
        return v16;
      }
      panic(
        v7,
        "ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/ipc.c",
        393,
        "!list_in_list(&chan->node)");
      while ( 1 )
      {
        v16 = -5;
        v21 = strdup(a2);
        *(_QWORD *)(v12 + 224) = v21;
        if ( v21 == 0 )
          break;
        *(_DWORD *)(v12 + 48) = 5;
        v22 = *(_QWORD *)(v12 + 184);
        v23 = v12 + 184;
        *(_QWORD *)(v12 + 200) = -536630040;
        *(_QWORD *)(v12 + 208) = &off_9405ACE8;
        MEMORY[0xFFFFFFFFE003ACF0] = v12 + 200;
        off_9405ACE8 = (_UNKNOWN *)(v12 + 200);
        if ( v22 == 0 && *(_QWORD *)(v12 + 192) == 0 )
        {
          v24 = *(_QWORD *)v12;
          *(_QWORD *)(v12 + 184) = *(_QWORD *)v12;
          *(_QWORD *)(v12 + 192) = v12;
          *(_QWORD *)(v24 + 8) = v23;
          *(_QWORD *)v12 = v23;
LABEL_11:
          handle_init(v12 + 80, (__int64)qword_9405ACC8);
          v17 = v12 + 64;
          if ( *(_QWORD *)(v12 + 64) == 0 && *(_QWORD *)(v12 + 72) == 0 )
          {
            v25 = *(_QWORD *)v12;
            v16 = 0;
            *(_QWORD *)(v12 + 64) = *(_QWORD *)v12;
            *(_QWORD *)(v12 + 72) = v12;
            *(_QWORD *)(v25 + 8) = v17;
            *(_QWORD *)v12 = v17;
            *a5 = v12 + 80;
            goto LABEL_15;
          }
        }
        panic(
          v7,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/include/reflist.h",
          62,
          "!list_in_list(&ref->ref_node)");
LABEL_13:
        if ( (a4 & 1) == 0 )
        {
          v16 = -2;
          goto LABEL_15;
        }
      }
    }
    panic(v7, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 390, (const char *)&loc_94051058);
  }
  return 4294967291LL;
}

/* ===== sys_connect @ 0x94030374 size 400 ===== */
__int64 __fastcall sys_connect(unsigned int a1, int a2)
{
  __int64 v4; // x22
  __int64 v5; // x23
  __int64 result; // x0
  int v7; // w19
  unsigned int v8; // [xsp+44h] [xbp+44h] BYREF
  __int64 v9; // [xsp+48h] [xbp+48h] BYREF
  char v10[64]; // [xsp+50h] [xbp+50h] BYREF

  v4 = *(_QWORD *)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 144LL);
  v5 = uctx_get_current();
  if ( (a2 & 0xFFFFFFFC) == 0 )
  {
    LODWORD(result) = copy_from_user_string(v10, a1, 64);
    if ( (result & 0x80000000) != 0 )
      return (int)result;
    if ( (unsigned int)result <= 0x3F )
    {
      LODWORD(result) = ipc_chan_open(v4 + 32, (__int64)v10, 0x40u, a2, &v9);
      if ( (_DWORD)result != 0 )
        return (int)result;
      if ( (a2 & 2) != 0 )
        goto LABEL_10;
      v7 = ((__int64 (__fastcall *)(__int64, unsigned int *, __int64))loc_9402DB34)(v9, &v8, 0xFFFFFFFFLL);
      if ( v7 != -13 )
      {
        if ( (v7 & 0x80000000) == 0 )
          goto LABEL_8;
LABEL_14:
        handle_decref(v9);
        return v7;
      }
      printf("%s:%d: Timedout connecting to %s\n", "sys_connect", 792, v10);
      v7 = ((__int64 (__fastcall *)(__int64, unsigned int *, __int64))loc_9402DB34)(v9, &v8, 0xFFFFFFFFLL);
      if ( v7 < 0 )
        goto LABEL_14;
LABEL_8:
      if ( (v8 & 0xC) == 4 )
      {
        handle_decref(v9);
        return -15;
      }
      else
      {
        if ( (v8 & 1) != 0 )
        {
LABEL_10:
          v7 = ((__int64 (__fastcall *)(__int64, __int64, unsigned int *))loc_9402E3B0)(v5, v9, &v8);
          if ( v7 == 0 )
            return v8;
          goto LABEL_14;
        }
        printf("%s:%d: Unexpected channel state: event = 0x%x\n", "sys_connect", 811, v8);
        handle_decref(v9);
        return -3;
      }
    }
  }
  return -8;
}

/* ===== ipc_chan_accept @ 0x94030504 size 920 ===== */
__int64 __fastcall ipc_chan_accept(__int64 a1, _QWORD *a2, _QWORD *a3)
{
  __int64 v3; // x30
  __int64 v5; // x25
  __int64 v8; // x26
  unsigned int v9; // w21
  _QWORD *v11; // x19
  _QWORD *v12; // x0
  _QWORD *v13; // x20
  __int64 v14; // x2
  __int64 v15; // x2
  _QWORD *v16; // x0
  __int64 v17; // x1
  _QWORD *v18; // x0
  __int64 v19; // x1
  __int64 v20; // x0
  __int64 v21; // x0
  int v22; // w1
  _QWORD *v23; // x1
  __int64 v24; // x2
  __int64 v25; // x0
  __int64 v26; // x0
  __int64 v27; // [xsp+60h] [xbp+60h] BYREF
  _QWORD *v28; // [xsp+68h] [xbp+68h]

  v27 = 0;
  v5 = v3;
  v28 = nullptr;
  if ( a2 == nullptr )
    goto LABEL_12;
  if ( a3 == nullptr )
  {
LABEL_13:
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 840, "uuid_ptr");
    return 4294967288LL;
  }
  if ( a1 == 0 || !ipc_is_port(a1) )
    return 4294967288LL;
  v8 = a1 - 96;
  v9 = -15;
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( *(_DWORD *)(a1 - 24) != 1 )
    goto LABEL_6;
  v11 = *(_QWORD **)(a1 + 112);
  if ( v11 == (_QWORD *)(a1 + 104)
    || (v12 = (_QWORD *)v11[1],
        *v12 = *v11,
        *(_QWORD *)(*v11 + 8LL) = v12,
        v11[1] = 0,
        *v11 = 0,
        v13 = v11 - 25,
        v11 == (_QWORD *)200) )
  {
    v9 = -4;
    goto LABEL_6;
  }
  if ( (*((_DWORD *)v11 - 37) & 1) == 0 )
  {
    v18 = (_QWORD *)panic(
                      v5,
                      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                      "lk/trusty/lib/trusty/ipc.c",
                      870,
                      "server->flags & IPC_CHAN_FLAG_SERVER");
    goto LABEL_42;
  }
  if ( v27 != 0 || v28 != nullptr )
  {
LABEL_11:
    panic(
      v5,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/include/reflist.h",
      62,
      "!list_in_list(&ref->ref_node)");
LABEL_12:
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 839, "chandle_ptr");
    goto LABEL_13;
  }
  v14 = *(v11 - 25);
  v28 = v11 - 25;
  v27 = v14;
  v15 = *(v11 - 2);
  *(_QWORD *)(*(v11 - 25) + 8LL) = &v27;
  *(v11 - 25) = &v27;
  v16 = (_QWORD *)*(v11 - 1);
  if ( v15 == 0 && v16 == nullptr )
    goto LABEL_36;
  *v16 = v15;
  *(_QWORD *)(*(v11 - 2) + 8LL) = v16;
  *(v11 - 1) = 0;
  *(v11 - 2) = 0;
  if ( v13 != (_QWORD *)*(v11 - 24) )
    goto LABEL_19;
  while ( 1 )
  {
    if ( *(v11 - 21) != 0 )
      goto LABEL_44;
    if ( *v11 == 0 && v11[1] == 0 )
      break;
LABEL_26:
    panic(v5, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 393, "!list_in_list(&chan->node)");
  }
  v20 = v11[3];
  if ( v20 != 0 )
    free(v20);
  v21 = v11[2];
  if ( v21 != 0 )
  {
    ipc_msg_queue_destroy(v21);
    v11[2] = 0;
  }
  free(v11 - 25);
LABEL_19:
  ((void (__fastcall *)(__int64))loc_9402D978)(v8 + 96);
  v8 = *(v11 - 21);
  if ( v8 == 0 || *((_DWORD *)v11 - 38) != 1 )
  {
LABEL_21:
    v9 = -15;
    ipc_chan_close((__int64)(v11 - 25));
    goto LABEL_22;
  }
  while ( 1 )
  {
    if ( *(_DWORD *)(v8 + 48) != 2 )
      goto LABEL_21;
    v22 = *(_DWORD *)(v8 + 56);
    *((_DWORD *)v11 - 38) = 3;
    *(_DWORD *)(v8 + 56) = v22 | 4;
    *(_DWORD *)(v8 + 48) = 3;
    handle_init((__int64)(v11 - 15), (__int64)qword_9405ACC8);
    v23 = v11 - 17;
    if ( *(v11 - 17) != 0 || *(v11 - 16) != 0 )
      goto LABEL_11;
    v24 = *(v11 - 25);
    *(v11 - 17) = v24;
    v9 = 0;
    *(v11 - 16) = v13;
    *(_QWORD *)(v24 + 8) = v23;
    *(v11 - 25) = v23;
    *a2 = v11 - 15;
    *a3 = *(_QWORD *)(v8 + 40);
    handle_cancel_wait(v8 + 80);
LABEL_22:
    v17 = v27;
    v18 = v28;
    if ( v27 != 0 )
      break;
LABEL_42:
    if ( v18 != nullptr )
      break;
LABEL_36:
    panic(
      v5,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/include/reflist.h",
      71,
      "list_in_list(&ref->ref_node)");
  }
  *v18 = v17;
  v19 = v27;
  v27 = 0;
  *(_QWORD *)(v19 + 8) = v18;
  v28 = nullptr;
  if ( v13 != (_QWORD *)*(v11 - 24) )
    goto LABEL_6;
  if ( *(v11 - 21) != 0 )
  {
LABEL_44:
    panic(v5, "ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc.c", 390, (const char *)&loc_94051058);
    goto LABEL_45;
  }
  if ( *v11 != 0 )
    goto LABEL_26;
LABEL_45:
  if ( v11[1] != 0 )
    goto LABEL_26;
  v25 = v11[3];
  if ( v25 != 0 )
    free(v25);
  v26 = v11[2];
  if ( v26 != 0 )
  {
    ipc_msg_queue_destroy(v26);
    v11[2] = 0;
  }
  free(v11 - 25);
LABEL_6:
  mutex_release(-536630024);
  return v9;
}

/* ===== sys_accept @ 0x9403089C size 220 ===== */
__int64 __fastcall sys_accept(unsigned int a1, unsigned int a2)
{
  _QWORD *v4; // x20
  __int64 result; // x0
  int v6; // w19
  unsigned int v7; // [xsp+34h] [xbp+34h] BYREF
  __int64 v8; // [xsp+38h] [xbp+38h] BYREF
  __int64 v9; // [xsp+40h] [xbp+40h] BYREF
  __int64 v10; // [xsp+48h] [xbp+48h] BYREF

  v8 = 0;
  v4 = (_QWORD *)uctx_get_current();
  v9 = 0;
  LODWORD(result) = ((__int64 (__fastcall *)(_QWORD *, _QWORD, __int64 *))loc_9402E4E4)(v4, a1, &v8);
  if ( (_DWORD)result == 0 )
  {
    v6 = ipc_chan_accept(v8, &v9, &v10);
    if ( v6 == 0 )
    {
      v6 = ((__int64 (__fastcall *)(_QWORD *, __int64, unsigned int *))loc_9402E3B0)(v4, v9, &v7);
      if ( v6 == 0 )
      {
        v6 = copy_to_user(a2, v10, 16);
        if ( v6 == 0 )
        {
          ((void (__fastcall *)(__int64))loc_9402D978)(v8);
          return v7;
        }
        uctx_handle_put(v4, v7, &v9);
      }
      handle_decref(v9);
    }
    ((void (__fastcall *)(__int64))loc_9402D978)(v8);
    return v6;
  }
  return (int)result;
}

/* ===== ipc_chan_create_pair @ 0x94030978 size 160 ===== */
__int64 __fastcall ipc_chan_create_pair(__int64 a1, _QWORD *a2, __int64 a3, int a4, __int64 a5, int a6)
{
  int v7; // w19
  unsigned int v9; // [xsp+34h] [xbp+34h] BYREF
  __int64 v10; // [xsp+38h] [xbp+38h] BYREF

  v10 = 0;
  v7 = ipc_port_create(a1 + 32, a3, a4, a5, a6, &v10);
  if ( v7 == 0 )
  {
    v7 = ((__int64 (__fastcall *)(_QWORD *, __int64, unsigned int *))loc_9402E3B0)(a2, v10, &v9);
    if ( v7 == 0 )
    {
      v7 = ipc_port_publish(v10);
      if ( v7 == 0 )
        return v9;
      uctx_handle_put(a2, v9, &v10);
    }
    ((void (__fastcall *)(__int64))loc_9402D978)(v10);
  }
  return v7;
}

/* ===== sys_accept_port @ 0x94030A18 size 152 ===== */
__int64 __fastcall sys_accept_port(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 result; // x0
  int v5; // w19
  __int64 v6; // [xsp+28h] [xbp+28h] BYREF
  unsigned int v7; // [xsp+3Ch] [xbp+3Ch] BYREF
  __int64 v8; // [xsp+40h] [xbp+40h] BYREF
  __int64 v9; // [xsp+48h] [xbp+48h] BYREF

  v6 = a3;
  v8 = 0;
  v9 = 0;
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, __int64, __int64 *))loc_9402E4E4)(a1, a2, &v8);
  if ( (_DWORD)result == 0 )
  {
    v5 = ipc_chan_accept(v8, &v9, &v6);
    if ( v5 == 0 )
    {
      v5 = ((__int64 (__fastcall *)(__int64, __int64, unsigned int *))loc_9402E3B0)(a1, v9, &v7);
      if ( v5 == 0 )
      {
        ((void (__fastcall *)(__int64))loc_9402D978)(v8);
        return v7;
      }
      handle_decref(v9);
    }
    ((void (__fastcall *)(__int64))loc_9402D978)(v8);
    return v5;
  }
  return (int)result;
}

/* ===== ipc_msg_put @ 0x94030AB0 size 312 ===== */
__int64 __fastcall ipc_msg_put(__int64 a1, _DWORD *a2)
{
  __int64 v2; // x30
  _QWORD *v3; // x20
  _QWORD *v4; // x19
  int v6; // w2
  __int64 v7; // x1
  __int64 v8; // x4
  __int64 v9; // x0
  __int64 v10; // x0
  __int64 result; // x0
  _QWORD *v12; // x3
  __int64 v13; // x4

  v3 = *(_QWORD **)(*(_QWORD *)(a1 + 32) + 216LL);
  v4 = (_QWORD *)v3[1];
  if ( v3 == v4 || v4 == nullptr || v4 == (_QWORD *)48 )
  {
    *(_DWORD *)(a1 + 56) |= 1u;
    return 4294967287LL;
  }
  if ( *((_BYTE *)v4 - 47) != 0 )
  {
    panic(
      v2,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/ipc_msg.c",
      228,
      "item->state == MSG_ITEM_STATE_FREE");
    return 4294967272LL;
  }
  *(v4 - 1) = 0;
  v6 = *a2;
  v7 = v3[7];
  v8 = v3[8];
  v9 = *((unsigned __int8 *)v4 - 48);
  *((_DWORD *)v4 - 11) = 0;
  v10 = v8 + v9 * v7;
  if ( v6 != 1 )
  {
    if ( v6 != 0 )
      return 4294967288LL;
    if ( a2[4] == 0 )
    {
      result = iov_copy_from_user_handle(v10, v7, (unsigned int)a2[3], (unsigned int)a2[2]);
      goto LABEL_9;
    }
    return 4294967272LL;
  }
  if ( a2[6] != 0 )
    return 4294967272LL;
  result = iov_copy_from_user(v10, v7, *((_QWORD *)a2 + 2), (unsigned int)a2[2]);
LABEL_9:
  if ( (result & 0x8000000000000000LL) == 0 )
  {
    v12 = (_QWORD *)v4[1];
    v13 = *v4;
    *(v4 - 1) = result;
    *v12 = v13;
    *(_QWORD *)(*v4 + 8LL) = v12;
    *v4 = 0;
    *v4 = v3[2];
    v4[1] = v3 + 2;
    *(_QWORD *)(v3[2] + 8LL) = v4;
    v3[2] = v4;
    *((_BYTE *)v4 - 47) = 1;
  }
  return result;
}

/* ===== ipc_msg_get @ 0x94030BE8 size 188 ===== */
__int64 __fastcall ipc_msg_get(__int64 a1, unsigned int a2, unsigned int a3, __int64 a4)
{
  __int64 v4; // x7
  __int64 v5; // x1
  __int64 v6; // x7
  unsigned __int64 v7; // x6
  unsigned __int64 v9; // x3
  __int64 v10; // x2

  v4 = a2 + 1LL;
  v5 = a1 + ((unsigned __int64)a2 << 6);
  v6 = a1 + (v4 << 6);
  if ( *(_BYTE *)(v5 + 73) != 2 )
    return 4294967288LL;
  if ( *(_DWORD *)(v5 + 76) == 0 )
  {
    v7 = *(_QWORD *)(v5 + 112);
    if ( a3 <= v7 )
    {
      v9 = v7 - a3;
      v10 = *(_QWORD *)(a1 + 64) + a3 + *(unsigned __int8 *)(v6 + 8) * *(_QWORD *)(a1 + 56);
      if ( *(_DWORD *)a4 == 1 )
      {
        if ( *(_DWORD *)(a4 + 24) == 0 )
          return iov_copy_to_user(*(_QWORD *)(a4 + 16), *(unsigned int *)(a4 + 8), v10, v9);
        return 4294967272LL;
      }
      if ( *(_DWORD *)a4 == 0 )
      {
        if ( *(_DWORD *)(a4 + 16) == 0 )
          return iov_copy_to_user_handle(*(unsigned int *)(a4 + 12), *(unsigned int *)(a4 + 8), v10, v9);
        return 4294967272LL;
      }
    }
    return 4294967288LL;
  }
  return 4294967272LL;
}

/* ===== ipc_msg_queue_create @ 0x94030CA4 size 328 ===== */
__int64 __fastcall ipc_msg_queue_create(unsigned int a1, __int64 a2, __int64 *a3)
{
  __int64 v4; // x23
  __int64 v6; // x19
  __int64 v7; // x0
  _QWORD *v8; // x0
  _QWORD *v9; // x4
  int v10; // w1
  unsigned int v11; // w19
  __int64 v13; // x0

  v4 = a1;
  v6 = calloc(1, ((unsigned __int64)a1 << 6) + 72);
  if ( v6 != 0 )
  {
    v7 = malloc(v4 * a2);
    *(_QWORD *)(v6 + 64) = v7;
    if ( v7 != 0 )
    {
      *(_DWORD *)(v6 + 48) = v4;
      *(_QWORD *)(v6 + 56) = a2;
      *(_QWORD *)(v6 + 8) = v6;
      *(_QWORD *)v6 = v6;
      *(_QWORD *)(v6 + 24) = v6 + 16;
      *(_QWORD *)(v6 + 16) = v6 + 16;
      *(_QWORD *)(v6 + 40) = v6 + 32;
      *(_QWORD *)(v6 + 32) = v6 + 32;
      if ( (_DWORD)v4 != 0 )
      {
        v8 = (_QWORD *)(v6 + 120);
        v9 = (_QWORD *)v6;
        v10 = 0;
        do
        {
          *((_BYTE *)v8 - 48) = v10++;
          *v8 = v9;
          v8[1] = v6;
          v9[1] = v8;
          v9 = v8;
          v8 += 8;
        }
        while ( v10 != (_DWORD)v4 );
        *(_QWORD *)v6 = v6 + ((unsigned __int64)(unsigned int)(v10 - 1) << 6) + 120;
      }
      *a3 = v6;
      return 0;
    }
    else
    {
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("cannot allocate memory for message queue buf\n");
      v13 = v6;
      v11 = -5;
      free(v13);
    }
    return v11;
  }
  v11 = -5;
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
    return v11;
  log_printf("cannot allocate memory for message queue\n");
  return 4294967291LL;
}

/* ===== ipc_msg_queue_destroy @ 0x94030DEC size 40 ===== */
__int64 __fastcall ipc_msg_queue_destroy(__int64 a1)
{
  free(*(_QWORD *)(a1 + 64));
  return free(a1);
}

/* ===== ipc_msg_queue_is_empty @ 0x94030E14 size 20 ===== */
bool __fastcall ipc_msg_queue_is_empty(__int64 a1)
{
  return *(_QWORD *)(a1 + 24) == a1 + 16;
}

/* ===== sys_msg_put @ 0x94030E28 size 296 ===== */
__int64 __fastcall sys_msg_put(unsigned int a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 v4; // x22
  __int64 result; // x0
  __int64 v6; // x0
  __int64 v7; // x19
  int v8; // w0
  __int64 v9; // x19
  int v10; // w0
  __int64 v11; // x1
  __int64 v12; // x19
  __int64 v13; // x0
  __int64 v14; // x1
  __int64 v15; // [xsp+30h] [xbp+30h] BYREF
  int v16; // [xsp+38h] [xbp+38h] BYREF
  __int64 v17; // [xsp+40h] [xbp+40h] BYREF

  v16 = 0;
  v4 = v2;
  LODWORD(result) = copy_from_user(&v17, a2, 16);
  if ( (_DWORD)result != 0 )
    return (int)result;
  v6 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v6, a1, &v15);
  if ( (_DWORD)result != 0 )
    return (int)result;
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  v7 = v15;
  if ( v15 == 0 || !ipc_is_channel(v15) )
  {
    v12 = -8;
LABEL_9:
    mutex_release(-536630024);
    ((void (__fastcall *)(__int64))loc_9402D978)(v15);
    return v12;
  }
  v8 = *(_DWORD *)(v7 - 32);
  if ( v8 != 3 )
  {
    v12 = -3;
    if ( v8 == 4 )
      v12 = -15;
    goto LABEL_9;
  }
  if ( *(_QWORD *)(v7 - 48) != 0 )
  {
    v9 = v15;
    v10 = ipc_msg_put(v15 - 80, &v16);
    if ( v10 < 0 )
    {
      v12 = v10;
    }
    else
    {
      v11 = *(_QWORD *)(v9 - 48);
      v12 = v10;
      handle_cancel_wait(v11 + 80);
    }
    goto LABEL_9;
  }
  v13 = panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc_msg.c", 206, "chan->peer");
  return sys_msg_send(v13, v14);
}

/* ===== sys_msg_send @ 0x94030F50 size 240 ===== */
__int64 __fastcall sys_msg_send(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 v4; // x20
  int v5; // w1
  unsigned int v6; // w20
  int v8; // [xsp+38h] [xbp+38h] BYREF
  __int64 v9; // [xsp+40h] [xbp+40h] BYREF

  if ( a2 == 0 )
    return 4294967288LL;
  v4 = v2;
  v8 = 1;
  memcpy(&v9, a2, 32);
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( a1 != 0 && ipc_is_channel(a1) )
  {
    v5 = *(_DWORD *)(a1 - 32);
    if ( v5 != 3 )
    {
      if ( v5 == 4 )
        v6 = -15;
      else
        v6 = -3;
      goto LABEL_8;
    }
    if ( *(_QWORD *)(a1 - 48) != 0 )
    {
      v6 = ipc_msg_put(a1 - 80, &v8);
      if ( (v6 & 0x80000000) == 0 )
        handle_cancel_wait(*(_QWORD *)(a1 - 48) + 80LL);
      goto LABEL_8;
    }
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc_msg.c", 206, "chan->peer");
    return 4294967288LL;
  }
  v6 = -8;
LABEL_8:
  mutex_release(-536630024);
  return v6;
}

/* ===== sys_msg_get @ 0x94031040 size 380 ===== */
__int64 __fastcall sys_msg_get(unsigned int a1, unsigned int a2)
{
  __int64 v2; // x30
  __int64 v4; // x20
  __int64 v6; // x0
  __int64 result; // x0
  __int64 v8; // x19
  __int64 v9; // x0
  __int64 v10; // x3
  int v11; // w0
  _QWORD *v12; // x1
  _QWORD *v13; // x2
  _QWORD *v14; // x5
  __int64 v15; // x19
  __int64 v16; // x0
  __int64 v17; // x1
  __int64 v18; // [xsp+30h] [xbp+30h] BYREF
  _DWORD v19[2]; // [xsp+38h] [xbp+38h] BYREF

  v4 = v2;
  v6 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v6, a1, &v18);
  if ( (_DWORD)result != 0 )
    return (int)result;
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( v18 == 0 || !ipc_is_channel(v18) )
  {
    v15 = -8;
    goto LABEL_13;
  }
  v8 = v18 - 80;
  v9 = *(_QWORD *)(v18 + 136);
  v10 = *(_QWORD *)(v9 + 24);
  if ( v10 == v9 + 16 || v10 == 0 || v10 == 48 )
  {
    v15 = -4;
    goto LABEL_13;
  }
  v19[0] = *(_QWORD *)(v10 - 8);
  v19[1] = *(unsigned __int8 *)(v10 - 48);
  v11 = copy_to_user(a2, v19, 8);
  if ( v11 != 0 )
  {
    v15 = v11;
    goto LABEL_13;
  }
  v12 = *(_QWORD **)(v8 + 216);
  v13 = (_QWORD *)v12[3];
  if ( v13 != v12 + 2 && v13 != nullptr && v13 != (_QWORD *)48 )
  {
    v14 = (_QWORD *)v13[1];
    v15 = 0;
    *v14 = *v13;
    *(_QWORD *)(*v13 + 8LL) = v14;
    *v13 = 0;
    *v13 = v12[4];
    v13[1] = v12 + 4;
    *(_QWORD *)(v12[4] + 8LL) = v13;
    v12[4] = v13;
    *((_BYTE *)v13 - 47) = 2;
LABEL_13:
    mutex_release(-536630024);
    ((void (__fastcall *)(__int64))loc_9402D978)(v18);
    return v15;
  }
  v16 = panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc_msg.c", 349, "item");
  return ipc_msg_get_next(v16, v17);
}

/* ===== ipc_msg_get_next @ 0x940311BC size 268 ===== */
__int64 __fastcall ipc_msg_get_next(__int64 a1, _DWORD *a2)
{
  _QWORD *v4; // x2
  _QWORD *v5; // x0
  unsigned int v6; // w19
  _QWORD *v7; // x4

  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( a1 != 0 && ipc_is_channel(a1) )
  {
    v4 = *(_QWORD **)(a1 + 136);
    v5 = (_QWORD *)v4[3];
    if ( v5 == v4 + 2 || v5 == nullptr )
    {
      mutex_release(-536630024);
      return 4294967292LL;
    }
    else
    {
      v6 = -4;
      if ( v5 != (_QWORD *)48 )
      {
        *a2 = *(v5 - 1);
        v6 = 0;
        v7 = (_QWORD *)v5[1];
        a2[1] = *((unsigned __int8 *)v5 - 48);
        *v7 = *v5;
        *(_QWORD *)(*v5 + 8LL) = v7;
        *v5 = 0;
        *v5 = v4[4];
        v5[1] = v4 + 4;
        *(_QWORD *)(v4[4] + 8LL) = v5;
        v4[4] = v5;
        *((_BYTE *)v5 - 47) = 2;
      }
      mutex_release(-536630024);
      return v6;
    }
  }
  else
  {
    mutex_release(-536630024);
    return 4294967288LL;
  }
}

/* ===== ipc_msg_free @ 0x940312C8 size 352 ===== */
__int64 __fastcall ipc_msg_free(__int64 a1, unsigned int a2)
{
  __int64 v2; // x30
  __int64 v3; // x22
  __int64 v5; // x19
  __int64 v6; // x1
  __int64 v7; // x2
  __int64 v8; // x19
  __int64 v9; // x3
  _QWORD *v10; // x4
  __int64 v11; // x1
  int v12; // w0
  unsigned int v13; // w19

  v3 = v2;
  v5 = a2;
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( a1 == 0 || !ipc_is_channel(a1) )
    goto LABEL_10;
  if ( a1 == 80 )
  {
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc_msg.c", 358, "chan");
    goto LABEL_13;
  }
  v6 = *(_QWORD *)(a1 + 136);
  if ( v6 == 0 )
  {
LABEL_13:
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/ipc_msg.c", 359, "chan->msg_queue");
    goto LABEL_14;
  }
  if ( (unsigned int)v5 >= *(_DWORD *)(v6 + 48)
    || (v7 = v5 << 6, v8 = v6 + (v5 << 6), v9 = v6 + v7, *(_BYTE *)(v6 + v7 + 73) != 2) )
  {
LABEL_10:
    v13 = -8;
    goto LABEL_11;
  }
  v10 = *(_QWORD **)(v8 + 128);
  *v10 = *(_QWORD *)(v8 + 120);
  *(_QWORD *)(*(_QWORD *)(v8 + 120) + 8LL) = v10;
  *(_QWORD *)(v8 + 128) = 0;
  *(_QWORD *)(v8 + 128) = *(_QWORD *)(v6 + 8);
  *(_QWORD *)(v8 + 120) = v6;
  **(_QWORD **)(v6 + 8) = v9 + 120;
  *(_QWORD *)(v6 + 8) = v9 + 120;
  *(_BYTE *)(v9 + 73) = 0;
  v11 = *(_QWORD *)(a1 - 48);
  if ( v11 == 0 )
  {
LABEL_14:
    v13 = 0;
    goto LABEL_11;
  }
  v12 = *(_DWORD *)(v11 + 56);
  v13 = 0;
  if ( (v12 & 1) != 0 )
  {
    *(_DWORD *)(v11 + 56) = v12 & 0xFFFFFFFC | 2;
    handle_cancel_wait(v11 + 80);
    mutex_release(-536630024);
    return 0;
  }
LABEL_11:
  mutex_release(-536630024);
  return v13;
}

/* ===== sys_msg_free @ 0x94031428 size 96 ===== */
__int64 __fastcall sys_msg_free(unsigned int a1, unsigned int a2)
{
  __int64 v4; // x0
  __int64 result; // x0
  int v6; // w19
  __int64 v7; // [xsp+28h] [xbp+28h] BYREF

  v4 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v4, a1, &v7);
  if ( (_DWORD)result != 0 )
    return (int)result;
  v6 = ipc_msg_free(v7, a2);
  ((void (__fastcall *)(__int64))loc_9402D978)(v7);
  return v6;
}

/* ===== sys_msg_read @ 0x94031488 size 220 ===== */
__int64 __fastcall sys_msg_read(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  __int64 result; // x0
  __int64 v8; // x0
  __int64 v9; // x0
  __int64 v10; // x19
  __int64 v11; // [xsp+30h] [xbp+30h] BYREF
  int v12; // [xsp+38h] [xbp+38h] BYREF
  __int64 v13; // [xsp+40h] [xbp+40h] BYREF

  v12 = 0;
  LODWORD(result) = copy_from_user(&v13, a4, 16);
  if ( (_DWORD)result != 0 )
    return (int)result;
  v8 = uctx_get_current();
  LODWORD(result) = ((__int64 (__fastcall *)(__int64, _QWORD, __int64 *))loc_9402E4E4)(v8, a1, &v11);
  if ( (_DWORD)result != 0 )
    return (int)result;
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( v11 != 0 && ipc_is_channel(v11) && *(_DWORD *)((v9 = *(_QWORD *)(v11 + 136)) + 48) > a2 )
    v10 = (int)ipc_msg_get(v9, a2, a3, (__int64)&v12);
  else
    v10 = -8;
  mutex_release(-536630024);
  ((void (__fastcall *)(__int64))loc_9402D978)(v11);
  return v10;
}

/* ===== sys_msg_write @ 0x94031564 size 184 ===== */
__int64 __fastcall sys_msg_write(__int64 a1, unsigned int a2, unsigned int a3, __int64 a4)
{
  __int64 v7; // x0
  unsigned int v8; // w19
  int v10; // [xsp+48h] [xbp+48h] BYREF
  __int64 v11; // [xsp+50h] [xbp+50h] BYREF

  if ( a4 == 0 )
    return 4294967288LL;
  v10 = 1;
  memcpy(&v11, a4, 32);
  mutex_acquire_timeout(-536630024, 0xFFFFFFFFLL);
  if ( a1 != 0 && ipc_is_channel(a1) && *(_DWORD *)((v7 = *(_QWORD *)(a1 + 136)) + 48) > a2 )
    v8 = ipc_msg_get(v7, a2, a3, (__int64)&v10);
  else
    v8 = -8;
  mutex_release(-536630024);
  return v8;
}

/* ===== iov_copy_to_user @ 0x9403161C size 236 ===== */
__int64 __fastcall iov_copy_to_user(_QWORD *a1, int a2, __int64 a3, unsigned __int64 a4)
{
  _QWORD *v4; // x20
  __int64 v5; // x22
  unsigned __int64 v6; // x21
  __int64 v7; // x23
  _QWORD *v8; // x24
  __int64 v9; // x1
  unsigned __int64 v10; // x19

  v4 = a1;
  v5 = a3;
  v6 = a4;
  if ( a2 == 0 || a4 == 0 )
    return 0;
  if ( a1 == nullptr || a3 == 0 )
    return -8;
  v7 = 0;
  v8 = &a1[2 * (unsigned int)(a2 - 1) + 2];
  while ( 1 )
  {
    v10 = v4[1];
    if ( v10 >= v6 )
      break;
    v9 = v5;
    if ( v10 == 0 )
      goto LABEL_19;
    v7 += v10;
    v5 += v10;
    if ( *v4 == 0 )
      return -8;
    memcpy(*v4, v9, v4[1]);
    v6 -= v10;
    if ( v6 != 0 )
    {
LABEL_19:
      v4 += 2;
      if ( v4 != v8 )
        continue;
    }
    return v7;
  }
  if ( *v4 == 0 )
    return -8;
  memcpy(*v4, v5, v6);
  return v7 + v6;
}

/* ===== iov_copy_from_user @ 0x94031708 size 236 ===== */
__int64 __fastcall iov_copy_from_user(__int64 a1, unsigned __int64 a2, _QWORD *a3, int a4)
{
  __int64 v4; // x22
  unsigned __int64 v5; // x21
  _QWORD *v6; // x20
  __int64 v7; // x23
  _QWORD *v8; // x24
  __int64 v9; // x0
  unsigned __int64 v10; // x19

  v4 = a1;
  v5 = a2;
  v6 = a3;
  if ( a4 == 0 || a2 == 0 )
    return 0;
  if ( a1 == 0 || a3 == nullptr )
    return -8;
  v7 = 0;
  v8 = &a3[2 * (unsigned int)(a4 - 1) + 2];
  while ( 1 )
  {
    v10 = v6[1];
    if ( v5 <= v10 )
      break;
    v9 = v4;
    if ( v10 == 0 )
      goto LABEL_19;
    v7 += v10;
    v4 += v10;
    if ( *v6 == 0 )
      return -8;
    memcpy(v9, *v6, v6[1]);
    v5 -= v10;
    if ( v5 != 0 )
    {
LABEL_19:
      v6 += 2;
      if ( v6 != v8 )
        continue;
    }
    return v7;
  }
  if ( *v6 == 0 )
    return -8;
  memcpy(v4, *v6, v5);
  return v7 + v5;
}

/* ===== iov_copy_to_user_handle @ 0x940317F4 size 240 ===== */
__int64 __fastcall iov_copy_to_user_handle(unsigned int a1, int a2, __int64 a3, unsigned __int64 a4)
{
  __int64 v5; // x22
  unsigned __int64 v6; // x20
  int v8; // w23
  __int64 v9; // x24
  __int64 v10; // x1
  __int64 result; // x0
  __int64 v12; // x1
  unsigned __int64 v13; // x19
  unsigned int v14; // [xsp+58h] [xbp+58h] BYREF
  unsigned int v15; // [xsp+5Ch] [xbp+5Ch]

  v5 = a3;
  v6 = a4;
  if ( a2 == 0 || a4 == 0 )
    return 0;
  if ( a3 == 0 )
    return -8;
  v8 = 0;
  v9 = 0;
  while ( 1 )
  {
    v10 = a1;
    ++v8;
    a1 += 8;
    LODWORD(result) = copy_from_user(&v14, v10, 8);
    v12 = v5;
    if ( (_DWORD)result != 0 )
      break;
    v13 = v15;
    if ( v6 <= v15 )
      v13 = v6;
    v9 += v13;
    v5 += v13;
    LODWORD(result) = copy_to_user(v14, v12, v13);
    v6 -= v13;
    if ( (_DWORD)result != 0 )
      break;
    if ( v6 == 0 || v8 == a2 )
      return v9;
  }
  return (int)result;
}

/* ===== iov_copy_from_user_handle @ 0x940318E4 size 272 ===== */
__int64 __fastcall iov_copy_from_user_handle(__int64 a1, unsigned __int64 a2, unsigned int a3, int a4)
{
  __int64 v5; // x22
  unsigned __int64 v6; // x20
  int v8; // w23
  __int64 v9; // x24
  __int64 v10; // x1
  int v11; // w1
  __int64 v12; // x0
  unsigned __int64 v13; // x19
  __int64 result; // x0
  unsigned int v15; // [xsp+58h] [xbp+58h] BYREF
  unsigned int v16; // [xsp+5Ch] [xbp+5Ch]

  v5 = a1;
  v6 = a2;
  if ( a4 == 0 || a2 == 0 )
    return 0;
  if ( a1 == 0 )
    return -8;
  v8 = 0;
  v9 = 0;
  while ( 1 )
  {
    v10 = a3;
    ++v8;
    a3 += 8;
    v11 = copy_from_user(&v15, v10, 8);
    v12 = v5;
    if ( v11 != 0 )
      return v11;
    v13 = v16;
    if ( v6 <= v16 )
      v13 = v6;
    v9 += v13;
    v5 += v13;
    LODWORD(result) = copy_from_user(v12, v15, v13);
    v6 -= v13;
    if ( (_DWORD)result != 0 )
      break;
    if ( v6 == 0 || v8 == a4 )
      return v9;
  }
  return (int)result;
}

/* ===== vqueue_init @ 0x940319F4 size 716 ===== */
__int64 __fastcall vqueue_init(
        __int64 a1,
        int a2,
        __int64 a3,
        unsigned int a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8)
{
  __int64 v8; // x30
  __int64 v17; // x2
  unsigned int v18; // w26
  __int64 v19; // x3
  __int64 v20; // x4
  __int64 v22; // x0
  __int64 v23; // x30
  __int64 v24; // x19
  unsigned __int64 *v25; // x20
  __int64 v26; // x1
  __int64 v32; // x1
  __int64 v34; // x19
  unsigned __int64 *v35; // x20
  __int64 v39; // [xsp+48h] [xbp-8h]
  __int64 v40; // [xsp+A8h] [xbp+58h] BYREF

  v40 = 0;
  if ( a1 != 0 )
  {
    v17 = 8 * a4 + 6 + (((_DWORD)a5 - 1 + 2 * (a4 + 3 + 8 * a4)) & -(int)a5);
    *(_QWORD *)(a1 + 48) = v17;
    v18 = vmm_map(-536460256, "vqueue", (v17 + 4095) & 0x1FFFFF000LL, &v40, 12, a3, 0, 48);
    if ( v18 != 0 )
    {
      free(a1);
      return v18;
    }
    else
    {
      v19 = v40;
      *(_DWORD *)(a1 + 8) = a4;
      v20 = v19 + 16LL * a4;
      *(_QWORD *)(a1 + 16) = v19;
      *(_QWORD *)(a1 + 24) = v20;
      *(_DWORD *)a1 = a2;
      *(_QWORD *)(a1 + 136) = a6;
      *(_QWORD *)(a1 + 32) = -a5 & (v20 + 2LL * a4 + 5 + a5);
      *(_QWORD *)(a1 + 120) = a7;
      *(_QWORD *)(a1 + 40) = v19;
      *(_QWORD *)(a1 + 128) = a8;
      event_init(a1 + 72, 0, 0);
      return 0;
    }
  }
  else
  {
    v22 = panic(v8, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 51, "vq");
    v24 = v22;
    if ( v22 != 0 )
    {
      v25 = (unsigned __int64 *)(v22 + 56);
      if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
      {
        spin_lock(v25);
        *(_QWORD *)(v24 + 48) = 0;
        v26 = *(_QWORD *)(v24 + 40);
        *(_QWORD *)(v24 + 40) = 0;
        v39 = v26;
        spin_unlock(v25);
      }
      else
      {
        __asm { MSR             DAIFSet, #2 }
        spin_lock(v25);
        *(_QWORD *)(v24 + 48) = 0;
        v32 = *(_QWORD *)(v24 + 40);
        *(_QWORD *)(v24 + 40) = 0;
        v39 = v32;
        spin_unlock(v25);
        __asm { MSR             DAIFClr, #2 }
      }
      return vmm_free_region(-536460256, v39);
    }
    else
    {
      v34 = panic(v23, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 84, "vq");
      v35 = (unsigned __int64 *)(v34 + 56);
      if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
      {
        spin_lock(v35);
        if ( *(_QWORD *)(v34 + 40) != 0 )
          **(_WORD **)(v34 + 32) |= 1u;
        spin_unlock(v35);
      }
      else
      {
        __asm { MSR             DAIFSet, #2 }
        spin_lock(v35);
        if ( *(_QWORD *)(v34 + 40) != 0 )
        {
          **(_WORD **)(v34 + 32) |= 1u;
          spin_unlock(v35);
          __asm { MSR             DAIFClr, #2 }
        }
        else
        {
          spin_unlock(v35);
          __asm { MSR             DAIFClr, #2 }
        }
      }
      return event_signal(v34 + 72, 1u);
    }
  }
}

/* ===== vqueue_get_buf @ 0x94031CC0 size 576 ===== */
__int64 __fastcall vqueue_get_buf(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 v4; // x23
  unsigned __int64 *v6; // x22
  int v7; // w19
  int v13; // w3
  int v14; // w4
  unsigned int v15; // w1
  unsigned int v16; // w4
  unsigned int v17; // w3
  __int64 v18; // x8
  __int64 v19; // x3
  __int64 v20; // x5
  __int16 v21; // w7
  __int64 v22; // x0
  unsigned int v23; // w1
  __int64 v24; // x10
  __int64 v25; // x2
  __int64 v26; // x11
  unsigned int v27; // w20

  v4 = v2;
  v6 = (unsigned __int64 *)(a1 + 56);
  v7 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v7 = 1;
  }
  spin_lock(v6);
  if ( a1 != 0 )
  {
    if ( a2 != 0 )
    {
      if ( *(_QWORD *)(a1 + 40) == 0 )
      {
LABEL_28:
        v27 = -15;
        goto LABEL_17;
      }
      v13 = *(unsigned __int16 *)(a1 + 64);
      v14 = *(unsigned __int16 *)(*(_QWORD *)(a1 + 24) + 2LL);
      if ( *(unsigned __int16 *)(a1 + 8) >= (unsigned int)(unsigned __int16)(v14 - v13) )
      {
        if ( v14 != v13 )
          goto LABEL_8;
        goto LABEL_23;
      }
    }
    else
    {
      panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 118, "iovbuf");
    }
    panic(v4, "vq %p: new avail idx out of range (old %u new %u)\n", (const void *)a1, v13, v14);
    goto LABEL_27;
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 117, "vq");
LABEL_23:
  event_unsignal(a1 + 72);
  **(_WORD **)(a1 + 32) &= ~1u;
  __dmb(0xBu);
  if ( *(unsigned __int16 *)(a1 + 64) == *(unsigned __int16 *)(*(_QWORD *)(a1 + 24) + 2LL) )
  {
    v27 = -9;
    goto LABEL_17;
  }
  **(_WORD **)(a1 + 32) |= 1u;
  event_signal(a1 + 72, 0);
LABEL_8:
  __dmb(9u);
  v15 = *(unsigned __int16 *)(a1 + 64);
  v16 = *(_DWORD *)(a1 + 8);
  v17 = *(unsigned __int16 *)(*(_QWORD *)(a1 + 24) + 2LL * (v15 % v16) + 4);
  *(_WORD *)(a1 + 64) = v15 + 1;
  if ( v16 <= v17 )
  {
LABEL_27:
    panic(v4, "vq %p: head out of range %u (max %u)\n", (const void *)a1, v17, v16);
    goto LABEL_28;
  }
  v18 = *(_QWORD *)(a1 + 16);
  *(_WORD *)a2 = v17;
  *(_DWORD *)(a2 + 12) = 0;
  *(_QWORD *)(a2 + 16) = 0;
  *(_DWORD *)(a2 + 44) = 0;
  *(_QWORD *)(a2 + 48) = 0;
  while ( 1 )
  {
    v19 = 16LL * (unsigned __int16)v17;
    v20 = v18 + v19;
    v21 = *(_WORD *)(v18 + v19 + 12);
    if ( (v21 & 2) != 0 )
      v22 = a2 + 40;
    else
      v22 = a2 + 8;
    v23 = *(_DWORD *)(v22 + 4);
    if ( v23 >= *(_DWORD *)v22 )
    {
      v27 = -25;
      goto LABEL_17;
    }
    v24 = *(_QWORD *)(v22 + 16);
    v25 = *(unsigned int *)(v20 + 8);
    v26 = *(_QWORD *)(v18 + v19);
    v17 = *(unsigned __int16 *)(v20 + 14);
    *(_QWORD *)(*(_QWORD *)(v22 + 24) + 16LL * *(unsigned int *)(v22 + 4) + 8) = v25;
    *(_QWORD *)(v24 + 8LL * v23) = v26;
    *(_DWORD *)(v22 + 4) = v23 + 1;
    *(_QWORD *)(v22 + 8) += v25;
    if ( (v21 & 1) == 0 )
      break;
    if ( v16 <= v17 )
    {
      v27 = -7;
      goto LABEL_17;
    }
  }
  v27 = 0;
LABEL_17:
  spin_unlock(v6);
  if ( v7 != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v27;
}

/* ===== vqueue_map_iovs @ 0x94031F00 size 404 ===== */
__int64 __fastcall vqueue_map_iovs(__int64 a1, unsigned int a2)
{
  __int64 v2; // x30
  __int64 v5; // x0
  __int64 v6; // x1
  __int64 v7; // x2
  unsigned int v8; // w3
  unsigned int v9; // w19
  __int64 v10; // x5
  _QWORD *v11; // x3
  unsigned int v12; // w24
  unsigned int v13; // w22
  __int64 v14; // x1
  __int64 v15; // x19
  int v16; // w0
  __int64 v18; // x0

  v5 = v2;
  if ( a1 == 0 )
  {
    v5 = panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 216, "vqiovs");
    goto LABEL_16;
  }
  v6 = *(_QWORD *)(a1 + 16);
  if ( v6 == 0 )
  {
LABEL_16:
    v5 = panic(v5, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 217, "vqiovs->phys");
    goto LABEL_17;
  }
  v7 = *(_QWORD *)(a1 + 24);
  if ( v7 == 0 )
  {
LABEL_17:
    v5 = panic(v5, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 218, "vqiovs->iovs");
    goto LABEL_18;
  }
  v8 = *(_DWORD *)(a1 + 4);
  if ( v8 > *(_DWORD *)a1 )
  {
LABEL_18:
    v18 = panic(
            v5,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            "lk/trusty/lib/trusty/vqueue.c",
            219,
            "vqiovs->used <= vqiovs->cnt");
    return vqueue_unmap_iovs(v18);
  }
  if ( v8 == 0 )
    return 0;
  v9 = 0;
  while ( 1 )
  {
    v10 = *(_QWORD *)(v6 + 8LL * v9);
    v11 = (_QWORD *)(v7 + 16LL * v9);
    *v11 = 0;
    v12 = vmm_map(-536460256, "vqueue", (v11[1] + 4095LL) & 0xFFFFFFFFFFFFF000LL, v11, 12, v10, 0, a2);
    if ( v12 != 0 )
      break;
    if ( *(_DWORD *)(a1 + 4) <= ++v9 )
      return 0;
    v7 = *(_QWORD *)(a1 + 24);
    v6 = *(_QWORD *)(a1 + 16);
  }
  v13 = v9 - 1;
  if ( v9 != 0 )
  {
    v14 = *(_QWORD *)(a1 + 24);
    do
    {
      v15 = 16LL * v13;
      vmm_free_region(-536460256, *(_QWORD *)(v14 + v15));
      v14 = *(_QWORD *)(a1 + 24);
      v16 = v13--;
      *(_QWORD *)(v14 + v15) = 0;
    }
    while ( v16 != 0 );
  }
  return v12;
}

/* ===== vqueue_unmap_iovs @ 0x94032094 size 332 ===== */
__int64 *__fastcall vqueue_unmap_iovs(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x23
  __int64 *result; // x0
  unsigned int v5; // w1
  __int64 v6; // x1
  __int64 v7; // x21
  unsigned int v8; // w19
  unsigned int v9; // w1
  __int64 v10; // x0

  v3 = v1;
  if ( a1 == 0 )
  {
    panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 244, "vqiovs");
  }
  else if ( *(_QWORD *)(a1 + 16) != 0 )
  {
    result = *(__int64 **)(a1 + 24);
    if ( result == nullptr )
    {
LABEL_14:
      panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 246, "vqiovs->iovs");
      goto LABEL_15;
    }
    v5 = *(_DWORD *)(a1 + 4);
    if ( v5 > *(_DWORD *)a1 )
    {
LABEL_15:
      v10 = panic(
              v1,
              "DEBUG ASSERT FAILED at (%s:%d): %s\n",
              "lk/trusty/lib/trusty/vqueue.c",
              247,
              "vqiovs->used <= vqiovs->cnt");
      return (__int64 *)vqueue_add_buf(v10);
    }
    if ( v5 != 0 )
    {
      v6 = *result;
      if ( *result != 0 )
      {
        v7 = 0;
        v8 = 0;
        while ( 1 )
        {
          ++v8;
          vmm_free_region(-536460256, v6);
          result = *(__int64 **)(a1 + 24);
          v9 = *(_DWORD *)(a1 + 4);
          result[v7] = 0;
          if ( v9 <= v8 )
            break;
          v7 = 2LL * v8;
          v6 = result[v7];
          if ( v6 == 0 )
            return (__int64 *)panic(
                                v3,
                                "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                                "lk/trusty/lib/trusty/vqueue.c",
                                251,
                                "vqiovs->iovs[i].base");
        }
      }
      else
      {
        return (__int64 *)panic(
                            v3,
                            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                            "lk/trusty/lib/trusty/vqueue.c",
                            251,
                            "vqiovs->iovs[i].base");
      }
    }
    return result;
  }
  panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 245, "vqiovs->phys");
  goto LABEL_14;
}

/* ===== vqueue_add_buf @ 0x940321E0 size 280 ===== */
__int64 __fastcall vqueue_add_buf(__int64 a1, unsigned __int16 *a2, int a3)
{
  __int64 v3; // x30
  __int64 v4; // x22
  unsigned __int64 *v6; // x21
  int v7; // w20
  unsigned int v13; // w3
  unsigned int v14; // w0
  __int64 v15; // x0
  __int64 v16; // x1
  unsigned int v17; // w19

  v4 = v3;
  v6 = (unsigned __int64 *)(a1 + 56);
  v7 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v7 = 1;
  }
  spin_lock(v6);
  if ( a1 == 0 )
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 262, "vq");
  }
  else if ( a2 != nullptr )
  {
    if ( *(_QWORD *)(a1 + 40) == 0 )
    {
LABEL_13:
      v17 = -15;
      goto LABEL_8;
    }
    v13 = *a2;
    v14 = *(_DWORD *)(a1 + 8);
    if ( v13 >= v14 )
    {
      v17 = -7;
    }
    else
    {
      v15 = *(_QWORD *)(a1 + 32) + 8LL * (*(unsigned __int16 *)(*(_QWORD *)(a1 + 32) + 2LL) % v14);
      *(_DWORD *)(v15 + 4) = v13;
      *(_DWORD *)(v15 + 8) = a3;
      __dmb(0xAu);
      v16 = *(_QWORD *)(a1 + 32);
      v17 = 0;
      ++*(_WORD *)(v16 + 2);
    }
LABEL_8:
    spin_unlock(v6);
    if ( v7 != 0 )
      __asm { MSR             DAIFClr, #2 }
    return v17;
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/vqueue.c", 263, "buf");
  goto LABEL_13;
}

/* ===== trusty_sm_init @ 0x940322F8 size 100 ===== */
__int64 trusty_sm_init()
{
  __int64 result; // x0

  if ( MEMORY[0xFFFFFFFFE003CB98] > 0 )
    log_printf("Initializing Trusted OS SMC handler\n");
  result = sm_register_entity_ex(0x32u, &qword_9405AD50);
  if ( (_DWORD)result != 0 )
    return printf("%s:%d: WARNING: Cannot register SMC entity! (%d)\n", "trusty_sm_init", 138, result);
  return result;
}

/* ===== smcall_decode_ns_mem @ 0x9403235C size 192 ===== */
__int64 __fastcall smcall_decode_ns_mem(unsigned int *a1, __int64 *a2, _DWORD *a3, int *a4)
{
  __int64 v4; // x30
  __int64 result; // x0

  if ( a2 == nullptr )
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/smcall.c", 45, "ppa");
  }
  else if ( a3 != nullptr )
  {
    if ( a4 == nullptr )
    {
LABEL_12:
      panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/smcall.c", 47, "pflags");
      return 4294967288LL;
    }
    result = sm_decode_ns_mem_args(a1, a2, a3, a4);
    if ( (_DWORD)result != 0 )
      return result;
    if ( (*a4 & 3u) > 1 )
      return 4294967288LL;
    if ( (*a4 & 0xC) != 0 )
      return 4294967288LL;
    else
      return 0;
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/smcall.c", 46, "psz");
  goto LABEL_12;
}

/* ===== smcall_handler @ 0x9403241C size 260 ===== */
__int64 __fastcall smcall_handler(unsigned int *a1)
{
  __int64 result; // x0
  unsigned int v2; // [xsp+10h] [xbp+10h] BYREF
  unsigned int v3; // [xsp+14h] [xbp+14h] BYREF
  __int64 v4; // [xsp+18h] [xbp+18h] BYREF

  switch ( *a1 )
  {
    case 0x32000014u:
      result = (int)smcall_decode_ns_mem(a1, &v4, &v2, (int *)&v3);
      if ( (_DWORD)result == 0 )
        result = virtio_init(v4, v2, v3);
      break;
    case 0x32000015u:
      result = (int)smcall_decode_ns_mem(a1, &v4, &v2, (int *)&v3);
      if ( (_DWORD)result == 0 )
        result = (int)virtio_setup(v4, v2, v3);
      break;
    case 0x32000016u:
      result = (int)smcall_decode_ns_mem(a1, &v4, &v2, (int *)&v3);
      if ( (_DWORD)result == 0 )
        result = (int)virtio_reset(v4, v2, v3);
      break;
    case 0x32000017u:
      result = (int)virtio_notify_stub1(a1[1]);
      break;
    case 0x32000018u:
      result = (int)virtio_notify_stub2(a1[1], a1[2]);
      break;
    default:
      result = -24;
      break;
  }
  return result;
}

/* ===== virtio_register_device @ 0x94032520 size 156 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall virtio_register_device(__int64 a1)
{
  _QWORD *v1; // x1
  unsigned int v2; // w7

  if ( a1 != 0
    && (v1 = *(_QWORD **)(a1 + 32)) != nullptr
    && *v1 != 0
    && v1[1] != 0
    && v1[2] != 0
    && v1[3] != 0
    && v1[4] != 0 )
  {
    dword_9405AD64 = 1;
    *(_QWORD *)(a1 + 16) = -536629896;
    v2 = 0;
    *(_QWORD *)(a1 + 24) = &off_9405AD78;
    *(_DWORD *)(a1 + 4) = 0;
    dword_9405AD60 = 1;
    MEMORY[0xFFFFFFFFE003AD80] = a1 + 16;
    off_9405AD78 = (_UNKNOWN *)(a1 + 16);
  }
  else
  {
    return (unsigned int)-8;
  }
  return v2;
}

/* ===== virtio_init @ 0x940325BC size 636 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall virtio_init(__int64 a1, int a2, int a3)
{
  __int64 v3; // x30
  __int64 v5; // x24
  __int64 *v6; // x25
  _DWORD *v7; // x23
  __int64 v8; // x19
  unsigned __int64 v9; // x20
  __int64 (__fastcall **v10)(__int64); // x1
  int v11; // w0
  _UNKNOWN **v12; // x19
  bool v13; // zf
  __int64 result; // x0
  __int64 v15; // x20
  _DWORD *v16; // [xsp+68h] [xbp+68h] BYREF

  v5 = v3;
  LODWORD(v6) = a2;
  LODWORD(v7) = a3;
  v8 = -536629912;
  v9 = 16;
  if ( &off_9405AD78 != (_UNKNOWN **)-536629896LL )
  {
    do
    {
      v10 = *(__int64 (__fastcall ***)(__int64))(v8 + 32);
      *(_DWORD *)(v8 + 8) = v9;
      v11 = (*v10)(v8);
      v12 = *(_UNKNOWN ***)(v8 + 24);
      v9 = (unsigned int)(v9 + v11);
      v13 = v12 == &off_9405AD78;
      v8 = (__int64)(v12 - 2);
    }
    while ( !v13 );
  }
  qword_9405AD68 = v9;
  dword_9405AD70 = 1;
  while ( 1 )
  {
    if ( v9 > (unsigned int)v6 )
      return -9;
    v16 = nullptr;
    if ( a1 == 0 || (a1 & 0xFFF) != 0 )
      return -8;
    v6 = &qword_9405BFF0[2];
    LODWORD(result) = vmm_map(
                        -536460256,
                        "virtio",
                        (v9 + 4095) & 0xFFFFFFFFFFFFF000LL,
                        &v16,
                        12,
                        a1,
                        0,
                        (unsigned int)v7);
    if ( (_DWORD)result != 0 )
      return (int)result;
    memset(v16, 0, 0);
    v7 = v16;
    v16[1] = 0;
    *v7 = 1;
    if ( &off_9405AD78 == (_UNKNOWN **)-536629896LL )
      break;
    v15 = MEMORY[0xFFFFFFFFE003AD70];
    a1 = 0;
    if ( MEMORY[0xFFFFFFFFE003AD70] == 0 )
    {
      if ( v15 + ((__int64 (__fastcall *)(__int64))*MEMORY[0xFFFFFFFFE003AD88])(-536629912) != 0 )
        panic(
          v5,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "lk/trusty/lib/trusty/trusty_virtio.c",
          215,
          "vd->descr_offset + vd->ops->descr_sz(vd) <= vb->descr_size");
      panic(
        v5,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/trusty_virtio.c",
        216,
        "vdev_idx < vb->vdev_cnt");
      return -9;
    }
    panic(
      v5,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "lk/trusty/lib/trusty/trusty_virtio.c",
      214,
      "vd->descr_offset <= vb->descr_size");
    v9 = -536629896;
  }
  vmm_free_region(-536460256, v7);
  return 0;
}

/* ===== virtio_setup @ 0x94032838 size 404 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall virtio_setup(__int64 a1, int a2, unsigned int a3)
{
  unsigned int v3; // w4
  unsigned int v4; // w20
  __int64 result; // x0
  __int64 v8; // x23
  __int64 v9; // x20
  _UNKNOWN **v10; // x20
  bool v11; // zf
  int v12; // [xsp+54h] [xbp+54h]
  __int64 v13; // [xsp+58h] [xbp+58h] BYREF

  v13 = 0;
  v12 = 1;
  do
    v3 = __ldxr((unsigned int *)&dword_9405AD70);
  while ( v3 == 1 && __stxr(2u, (unsigned int *)&dword_9405AD70) != 0 );
  if ( v3 != 1 )
    v12 = v3;
  if ( v12 != 1 )
    return 4294967265LL;
  v4 = -8;
  if ( a2 != 0 )
    goto LABEL_8;
  v8 = malloc(0);
  if ( v8 == 0 )
  {
    v4 = -5;
    goto LABEL_8;
  }
  if ( a1 == 0 || (a1 & 0xFFF) != 0 || (v4 = vmm_map(-536460256, "virtio", 0, &v13, 12, a1, 0, a3)) != 0 )
  {
    free(v8);
LABEL_8:
    result = v4;
    dword_9405AD70 = 1;
    return result;
  }
  memcpy(v8, v13, 0);
  v9 = -536629912;
  if ( &off_9405AD78 != (_UNKNOWN **)-536629896LL )
  {
    do
    {
      (*(void (__fastcall **)(__int64, __int64))(*(_QWORD *)(v9 + 32) + 16LL))(v9, v8 + *(unsigned int *)(v9 + 8));
      v10 = *(_UNKNOWN ***)(v9 + 24);
      v11 = v10 == &off_9405AD78;
      v9 = (__int64)(v10 - 2);
    }
    while ( !v11 );
  }
  vmm_free_region(-536460256, v13);
  free(v8);
  dword_9405AD70 = 3;
  return 0;
}

/* ===== virtio_reset @ 0x940329CC size 180 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 virtio_reset()
{
  unsigned int v0; // w2
  __int64 v1; // x19
  _UNKNOWN **v2; // x19
  bool v3; // zf
  __int64 result; // x0
  int v5; // [xsp+3Ch] [xbp+3Ch]

  v5 = 3;
  do
    v0 = __ldxr((unsigned int *)&dword_9405AD70);
  while ( v0 == 3 && __stxr(4u, (unsigned int *)&dword_9405AD70) != 0 );
  if ( v0 != 3 )
    v5 = v0;
  if ( v5 != 3 )
    return 4294967265LL;
  v1 = -536629912;
  if ( &off_9405AD78 != (_UNKNOWN **)-536629896LL )
  {
    do
    {
      (*(void (__fastcall **)(__int64))(*(_QWORD *)(v1 + 32) + 24LL))(v1);
      v2 = *(_UNKNOWN ***)(v1 + 24);
      v3 = v2 == &off_9405AD78;
      v1 = (__int64)(v2 - 2);
    }
    while ( !v3 );
  }
  result = 0;
  dword_9405AD70 = 1;
  return result;
}

/* ===== virtio_notify_stub1 @ 0x94032A80 size 124 ===== */
__int64 virtio_notify_stub1()
{
  return 4294967265LL;
}

/* ===== virtio_notify_stub2 @ 0x94032AFC size 124 ===== */
__int64 virtio_notify_stub2()
{
  return 4294967265LL;
}

/* ===== virtio_get_config @ 0x94032B78 size 8 ===== */
__int64 __fastcall virtio_get_config(__int64 a1)
{
  return *(_QWORD *)(a1 + 56);
}

/* ===== virtio_read_config @ 0x94032B80 size 60 ===== */
__int64 __fastcall virtio_read_config(__int64 a1, __int64 a2)
{
  memcpy(a2, *(_QWORD *)(a1 + 48), *(_QWORD *)(a1 + 56));
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(a1 + 4);
  return *(_QWORD *)(a1 + 56);
}

/* ===== virtio_kick_rx @ 0x94032BBC size 24 ===== */
__int64 virtio_kick_rx()
{
  ((void (*)(void))loc_94031C08)();
  return 0;
}

/* ===== virtio_kick_tx @ 0x94032BD4 size 24 ===== */
__int64 virtio_kick_tx()
{
  ((void (*)(void))loc_94031C08)();
  return 0;
}

/* ===== tipc_dev_notify @ 0x94032BEC size 132 ===== */
__int64 __fastcall tipc_dev_notify(__int64 a1, int a2)
{
  __int64 v2; // x30
  __int64 v3; // x0
  __int64 (__fastcall *v4)(__int64, _QWORD); // x2

  if ( a1 == 0 )
  {
    panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1071, "vd");
    return 4294967294LL;
  }
  if ( *(_DWORD *)(a1 + 64) == a2 )
  {
    v3 = a1 + 64;
    v4 = *(__int64 (__fastcall **)(__int64, _QWORD))(v3 + 120);
    if ( v4 != nullptr )
      return v4(v3, *(_QWORD *)(v3 + 136));
    return 0;
  }
  if ( a2 != *(_DWORD *)(a1 + 208) )
    return 4294967294LL;
  v3 = a1 + 208;
  v4 = *(__int64 (__fastcall **)(__int64, _QWORD))(v3 + 120);
  if ( v4 == nullptr )
    return 0;
  return v4(v3, *(_QWORD *)(v3 + 136));
}

/* ===== tipc_copy_to_buf @ 0x94032C70 size 372 ===== */
__int64 __fastcall tipc_copy_to_buf(__int64 a1, unsigned __int64 a2, _QWORD *a3)
{
  __int64 v3; // x30
  unsigned int v4; // w19
  __int64 v6; // x0
  __int64 v7; // x2
  __int64 v8; // x30
  __int64 v9; // x1
  __int64 v10; // x5
  __int64 v11; // x0
  unsigned int v12; // w1
  __int64 v13; // x0
  _QWORD v14[2]; // [xsp+10h] [xbp-30h] BYREF
  int v15; // [xsp+20h] [xbp-20h] BYREF
  _QWORD *v16; // [xsp+28h] [xbp-18h]
  int v17; // [xsp+30h] [xbp-10h]
  __int64 v18; // [xsp+38h] [xbp-8h]

  v4 = a2;
  if ( a1 == 0 )
  {
    panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1204, "dst");
  }
  else if ( a3 != nullptr )
  {
    if ( *a3 == 0 )
    {
LABEL_8:
      panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1206, "buf->data");
      goto LABEL_9;
    }
    if ( a3[1] >= a2 )
    {
      memcpy(a1, *a3, a2);
      return v4;
    }
LABEL_9:
    v6 = panic(
           v3,
           "DEBUG ASSERT FAILED at (%s:%d): %s\n",
           "lk/trusty/lib/trusty/tipc_dev.c",
           1207,
           "sz <= buf->len");
    v10 = v9;
    if ( v6 != 0 )
    {
      if ( v7 != 0 )
      {
        v14[0] = v6;
        v11 = *(_QWORD *)v7;
        v12 = *(_DWORD *)(v7 + 12);
        v15 = 1;
        v14[1] = v10;
        v16 = v14;
        v17 = 0;
        v18 = 0;
        return sys_msg_write(v11, v12, 0, (__int64)&v15);
      }
    }
    else
    {
      panic(v8, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 668, "buf");
    }
    v13 = panic(v8, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 669, "cb_ctx");
    return tipc_send_msg(v13);
  }
  panic(v3, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1205, "buf");
  goto LABEL_8;
}

/* ===== tipc_send_msg @ 0x94032DE4 size 428 ===== */
__int64 __fastcall tipc_send_msg(
        __int64 a1,
        int a2,
        int a3,
        __int64 (__fastcall *a4)(__int64, __int64, __int64),
        __int64 a5,
        unsigned __int16 a6)
{
  __int64 v6; // x30
  __int64 v12; // x21
  __int64 v13; // x22
  __int64 v14; // x19
  __int64 result; // x0
  int v16; // w2
  __int64 v17; // x1
  __int64 v18; // x0
  unsigned __int64 v19; // x2
  int v20; // w0
  int v21; // w19
  char v22; // [xsp+60h] [xbp+60h] BYREF
  char v23; // [xsp+68h] [xbp+68h] BYREF
  unsigned __int16 v24[20]; // [xsp+78h] [xbp+78h] BYREF
  _DWORD v25[4]; // [xsp+A0h] [xbp+A0h] BYREF
  char *v26; // [xsp+B0h] [xbp+B0h]
  __int64 *v27; // [xsp+B8h] [xbp+B8h]

  v12 = a1 + 64;
  if ( a1 == 0 )
  {
    panic(v6, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1100, "dev");
  }
  else if ( a4 != nullptr )
  {
    v13 = a1 + 136;
    v14 = a1 + 69632;
    memset(v24, 0, 72);
    v25[0] = 1;
    v26 = &v22;
    v27 = (__int64 *)&v23;
    while ( 1 )
    {
      result = vqueue_get_buf(v12, (__int64)v24);
      if ( (_DWORD)result == 0 )
        break;
      if ( (_DWORD)result != -9 )
        return result;
      event_wait_timeout(v13, 0xFFFFFFFFLL);
      if ( *(_BYTE *)(v14 + 584) != 0 )
        return 4294967281LL;
    }
    v16 = -9;
    if ( v25[1] != 0 && (unsigned __int64)v27[1] > 0xF )
    {
      v16 = vqueue_map_iovs((__int64)v25, 0x30u);
      if ( v16 == 0 )
      {
        v17 = a6;
        v18 = *v27;
        v19 = v27[1];
        *(_DWORD *)v18 = a2;
        *(_DWORD *)(v18 + 4) = a3;
        *(_DWORD *)(v18 + 8) = 0;
        *(_WORD *)(v18 + 12) = a6;
        *(_WORD *)(v18 + 14) = 0;
        if ( (unsigned __int64)a6 + 16 > v19 )
          v17 = (unsigned __int16)(v19 - 16);
        v20 = a4(v18 + 16, v17, a5);
        v21 = v20;
        if ( v20 >= 0 )
          v21 = v20 + 16;
        vqueue_unmap_iovs((__int64)v25);
        v16 = v21;
      }
    }
    return vqueue_add_buf(v12, v24, v16);
  }
  return 4294967288LL;
}

/* ===== tipc_dev_start @ 0x94032F90 size 548 ===== */
__int64 __fastcall tipc_dev_start(__int64 a1, __int64 a2)
{
  __int64 v2; // x30
  __int64 v4; // x0
  __int64 result; // x0
  unsigned int *v7; // x22
  __int64 v8; // x25
  __int64 v9; // x24
  unsigned int v10; // w23
  unsigned int v11; // w21
  _DWORD *v12; // x0
  _DWORD *v13; // x0
  __int64 v14; // [xsp+68h] [xbp+68h] BYREF
  _QWORD v15[2]; // [xsp+70h] [xbp+70h] BYREF
  _BYTE v16[32]; // [xsp+80h] [xbp+80h] BYREF

  v4 = v2;
  if ( a1 == 0 )
  {
    v4 = panic(v2, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1062, "vd");
  }
  else if ( a2 != 0 )
  {
    if ( *(_DWORD *)a1 != 0 )
      return 4294967265LL;
    result = 4294967288LL;
    if ( *(_DWORD *)a2 == 3 && *(_DWORD *)(a2 + 4) == 13 && *(_BYTE *)(a2 + 25) == 2 && *(_BYTE *)(a2 + 24) == 7 )
    {
      v7 = (unsigned int *)(a2 + 28);
      v8 = a1 + 64;
      v9 = 0;
      v10 = 0;
      do
      {
        v11 = vqueue_init(v8, v7[3], *v7 | ((unsigned __int64)v7[4] << 32), v7[2], v7[1], a1, qword_9405ADB0[v9], 0);
        if ( v11 != 0 )
        {
          if ( v10 != 0 )
            ((void (__fastcall *)(__int64))loc_94031B4C)(a1 + 64);
          return v11;
        }
        ++v10;
        v7 += 5;
        ++v9;
        v8 += 144;
      }
      while ( v10 < *(unsigned __int8 *)(a2 + 25) );
      snprintf(v16, 32, "tipc-dev%d-rx", *(_DWORD *)(a1 + 4));
      v12 = (_DWORD *)thread_create_simple((__int64)v16, (__int64)handle_rx_msg, a1, 0x10u, 4096);
      *(_QWORD *)(a1 + 70200) = v12;
      if ( v12 != nullptr )
        thread_resume_full(v12);
      snprintf(v16, 32, "tipc-dev%d-tx", *(_DWORD *)(a1 + 4));
      v13 = (_DWORD *)thread_create_simple((__int64)v16, (__int64)handle_tx_msg, a1, 0x10u, 4096);
      *(_QWORD *)(a1 + 70208) = v13;
      if ( v13 != nullptr )
        thread_resume_full(v13);
      v15[1] = 8;
      v14 = 1;
      v15[0] = &v14;
      result = tipc_send_msg(
                 a1,
                 53,
                 53,
                 (__int64 (__fastcall *)(__int64, __int64, __int64))tipc_copy_to_buf,
                 (__int64)v15,
                 8u);
      if ( (_DWORD)result == 0 )
        *(_DWORD *)a1 = 1;
    }
    return result;
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1063, "descr");
  return 4294967265LL;
}

/* ===== tipc_send_cmd @ 0x940331B4 size 96 ===== */
__int64 __fastcall tipc_send_cmd(__int64 a1, int a2, int a3, int a4, int a5, int a6)
{
  _QWORD v7[2]; // [xsp+10h] [xbp+10h] BYREF
  _DWORD v8[8]; // [xsp+20h] [xbp+20h] BYREF

  v8[4] = a2;
  v8[3] = a4;
  v8[0] = 4;
  v8[2] = a3;
  v8[5] = a5;
  v8[6] = a6;
  v8[1] = 20;
  v7[1] = 28;
  v7[0] = v8;
  return tipc_send_msg(a1, 53, 53, (__int64 (__fastcall *)(__int64, __int64, __int64))tipc_copy_to_buf, (__int64)v7, 0x1Cu);
}

/* ===== tipc_handle_alloc @ 0x94033214 size 260 ===== */
__int64 __fastcall tipc_handle_alloc(_QWORD *a1, int a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x4
  unsigned __int64 v5; // x4
  unsigned int v6; // w19
  unsigned int *v7; // x4
  unsigned int v8; // w6
  __int64 v9; // x4
  _QWORD *v10; // x5
  __int64 v13; // x6
  int v14; // w4
  unsigned __int64 v15; // x6
  int v16; // w19

  v4 = a1[8748];
  if ( v4 != -1 )
  {
    v5 = ~v4;
    v6 = __clz(__rbit64(v5));
    if ( v5 == 0 )
      v6 = -1;
    goto LABEL_4;
  }
  v13 = a1[8749];
  v14 = 1;
  if ( v13 == -1 )
  {
    v13 = a1[8750];
    v14 = 2;
    if ( v13 == -1 )
    {
      v13 = a1[8751];
      if ( v13 == -1 )
        return 0;
      v14 = 3;
    }
  }
  v15 = ~v13;
  v16 = __clz(__rbit64(v15));
  if ( v15 == 0 )
    v16 = -1;
  v6 = v16 + (v14 << 6);
  if ( v6 <= 0xFF )
  {
LABEL_4:
    v7 = (unsigned int *)a1 + (v6 >> 5) + 17496;
    do
      v8 = __ldxr(v7);
    while ( __stxr(v8 | (1 << v6), v7) != 0 );
    v9 = 34LL * (int)v6;
    v10 = &a1[v9];
    v10[45] = a3;
    *((_DWORD *)v10 + 88) = a2;
    if ( a4 != 0 )
      strcpy(&a1[v9 + 46], a4);
    return v6 + 1000;
  }
  return 0;
}

/* ===== handle_rx_msg @ 0x94033318 size 1532 ===== */
__int64 __fastcall handle_rx_msg(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x28
  int v4; // w0
  __int64 v5; // x21
  int v6; // w3
  unsigned __int64 v7; // x0
  int *v8; // x1
  int v9; // w5
  int v10; // w3
  unsigned __int64 v11; // x2
  int v12; // w0
  __int64 v14; // x4
  __int64 v15; // x2
  __int64 v16; // x0
  int v17; // w0
  __int64 v18; // x21
  __int64 v19; // x0
  __int64 v20; // x6
  _DWORD *v21; // x2
  unsigned __int64 v22; // x0
  __int64 v23; // x2
  unsigned __int64 v24; // x0
  __int64 v25; // x0
  int v26; // w0
  int v27; // w5
  __int64 v28; // x2
  __int64 v29; // x4
  int v30; // w21
  unsigned int *v31; // x1
  unsigned int v32; // w3
  __int64 v33; // x0
  unsigned int v34; // w21
  int v35; // w3
  int v36; // w1
  int v37; // [xsp+60h] [xbp+60h]
  __int64 v38; // [xsp+60h] [xbp+60h]
  int v39; // [xsp+68h] [xbp+68h]
  int v40; // [xsp+68h] [xbp+68h]
  __int64 v41; // [xsp+68h] [xbp+68h]
  __int64 v42; // [xsp+68h] [xbp+68h]
  int v43; // [xsp+70h] [xbp+70h]
  _QWORD *v44; // [xsp+70h] [xbp+70h]
  int v45; // [xsp+70h] [xbp+70h]
  char v46; // [xsp+88h] [xbp+88h] BYREF
  __int64 v47; // [xsp+90h] [xbp+90h] BYREF
  __int64 v48; // [xsp+98h] [xbp+98h] BYREF
  _QWORD v49[2]; // [xsp+A8h] [xbp+A8h] BYREF
  __int64 v50; // [xsp+B8h] [xbp+B8h] BYREF
  _DWORD v51[4]; // [xsp+C0h] [xbp+C0h] BYREF
  char *v52; // [xsp+D0h] [xbp+D0h]
  int **v53; // [xsp+D8h] [xbp+D8h]
  _QWORD v54[32]; // [xsp+100h] [xbp+100h] BYREF

  v3 = v1;
  memset(&v50, 0, 72);
  v51[0] = 1;
  v52 = &v46;
  v53 = (int **)&v48;
  do
  {
LABEL_2:
    if ( *(_BYTE *)(a1 + 70217) == 0 )
    {
      event_wait_timeout(a1 + 280, 0xFFFFFFFFLL);
      v4 = vqueue_get_buf(a1 + 208, (__int64)&v50);
      if ( v4 != -15 )
        continue;
    }
    return 0;
  }
  while ( v4 == -9 );
  LODWORD(v5) = v4;
  if ( v4 != 0 )
    goto LABEL_11;
  if ( v51[1] != 0 )
  {
    v6 = vqueue_map_iovs((__int64)v51, 0x38u);
    if ( v6 != 0 )
    {
      LODWORD(v5) = v6;
      printf("%s:%d: failed to map iovs %d\n", "handle_rx_msg", 574, v6);
      goto LABEL_11;
    }
    v7 = (unsigned __int64)v53[1];
    if ( v7 <= 0xF )
      goto LABEL_14;
    v8 = *v53;
    v5 = 4294967288LL;
    v9 = **v53;
    v10 = (*v53)[1];
    v11 = *((unsigned __int16 *)*v53 + 6);
    if ( v7 != v11 + 16 )
      goto LABEL_10;
    if ( v10 != 53 )
    {
      v49[0] = v8 + 4;
      v37 = v10;
      v54[0] = 1;
      v39 = v9;
      LODWORD(v5) = -2;
      v54[2] = 0;
      v54[3] = 0;
      v49[1] = v11;
      v54[1] = v49;
      mutex_acquire_timeout(a1 + 70144, 0xFFFFFFFFLL);
      v14 = a1 + 70144;
      if ( (unsigned int)(v37 - 1000) <= 0xFF
        && ((*(_QWORD *)(a1 + 8 * ((unsigned __int64)(unsigned int)(v37 - 1000) >> 6) + 69984) >> ((unsigned __int8)v37
                                                                                                 + 24))
          & 1) != 0 )
      {
        v15 = a1 + 272LL * (unsigned int)(v37 - 1000);
        if ( v39 == *(_DWORD *)(v15 + 352) )
        {
          v16 = *(_QWORD *)(v15 + 360);
          if ( v16 != 0 )
          {
            LODWORD(v5) = sys_msg_send(v16, (__int64)v54);
            v14 = a1 + 70144;
          }
        }
      }
      mutex_release(v14);
      goto LABEL_10;
    }
    if ( v8 == (int *)-16LL )
    {
      LODWORD(v24) = panic(
                       v3,
                       "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                       "lk/trusty/lib/trusty/tipc_dev.c",
                       474,
                       "ns_data");
      goto LABEL_51;
    }
    if ( v11 <= 7 || (v17 = v8[4], v18 = (unsigned int)v8[5], v11 != v18 + 8) )
    {
LABEL_49:
      LODWORD(v5) = -7;
      goto LABEL_10;
    }
    if ( v17 != 3 )
    {
      if ( v17 == 5 )
      {
        v43 = *v8;
        if ( v18 == 4 )
        {
          v5 = a1 + 70144;
          v40 = v8[6];
          mutex_acquire_timeout(a1 + 70144, 0xFFFFFFFFLL);
          if ( (unsigned int)(v40 - 1000) <= 0xFF
            && ((*(_QWORD *)(a1 + 8 * ((unsigned __int64)(unsigned int)(v40 - 1000) >> 6) + 69984) >> ((unsigned __int8)v40 + 24))
              & 1) != 0
            && (v19 = 272LL * (unsigned int)(v40 - 1000), v43 == *(_DWORD *)(a1 + v19 + 352)) )
          {
            v20 = a1 + 352;
            v23 = a1 + v19 + 352;
          }
          else
          {
            v20 = a1 + 352;
            v21 = (_DWORD *)(a1 + 352);
            v22 = 0;
            while ( ((*(_QWORD *)(a1 + 69984 + 8 * (v22 >> 6)) >> v22) & 1) == 0 || v43 != *v21 )
            {
              ++v22;
              v21 += 68;
              if ( v22 == 256 )
                goto LABEL_43;
            }
            v23 = a1 + 272LL * (unsigned int)v22 + 352;
          }
          if ( *(_QWORD *)(v23 + 8) != 0 )
          {
            v38 = v20;
            v41 = v23;
            v44 = *(_QWORD **)(v23 + 8);
            hlist_remove_handle(a1 + 70064, v44);
            v44[12] = 0;
            handle_decref((__int64)v44);
            v23 = v41;
            v20 = v38;
            if ( *(_BYTE *)(v41 + 16) != 0 )
            {
              tam_unload_request((const char *)(v41 + 16), a1);
              v20 = v38;
              v23 = v41;
            }
          }
          v24 = 0xF0F0F0F0F0F0F0F1LL * ((v23 - v20) >> 4);
          if ( (unsigned int)v24 > 0xFF )
          {
LABEL_43:
            v25 = v5;
            LODWORD(v5) = 0;
            mutex_release(v25);
            goto LABEL_10;
          }
LABEL_51:
          v31 = (unsigned int *)(a1 + (((__int64)(int)v24 >> 3) & 0x1FFFFFFFFFFFFFFCLL) + 69984);
          do
            v32 = __ldxr(v31);
          while ( __stxr(v32 & ~(1 << v24), v31) != 0 );
          v33 = a1 + 272LL * (unsigned int)v24;
          *(_QWORD *)(v33 + 360) = 0;
          *(_DWORD *)(v33 + 352) = 0;
          *(_BYTE *)(v33 + 368) = 0;
          goto LABEL_43;
        }
      }
      goto LABEL_49;
    }
    v45 = *v8;
    if ( v18 != 256 )
      goto LABEL_49;
    v47 = 0;
    strncpy(v54, v8 + 6, 256);
    v26 = ipc_chan_open(*(_QWORD *)(a1 + 40), (__int64)v54, 0x100u, 0, &v47);
    v27 = v45;
    if ( v26 == -2 )
    {
      tam_load_request((const char *)v54, a1, v45);
      v28 = v47;
      v29 = 0;
      v35 = -2;
      if ( v47 != 0 )
        goto LABEL_48;
    }
    else
    {
      if ( v26 != 0 )
      {
        v28 = v47;
        v29 = 0;
        v30 = 0;
        if ( v47 != 0 )
        {
LABEL_48:
          *(_QWORD *)(v28 + 96) = v29;
          LODWORD(v5) = 0;
          hlist_add_handle((_QWORD *)(a1 + 70064), v28);
          event_signal(a1 + 70016, 0);
          goto LABEL_10;
        }
      }
      else
      {
        v42 = a1 + 70144;
        mutex_acquire_timeout(a1 + 70144, 0xFFFFFFFFLL);
        v30 = tipc_handle_alloc((_QWORD *)a1, v45, v47, 0);
        if ( v30 != 0 )
        {
          mutex_release(v42);
          v28 = v47;
          v27 = v45;
          if ( v47 != 0 )
          {
            v34 = v30 - 1000;
            v29 = 0;
            if ( v34 <= 0xFF && ((*(_QWORD *)(a1 + 8 * ((unsigned __int64)v34 >> 6) + 69984) >> v34) & 1) != 0 )
              v29 = a1 + 272LL * v34 + 352;
            goto LABEL_48;
          }
        }
        else
        {
          handle_decref(v47);
          v47 = 0;
          mutex_release(v42);
          v28 = v47;
          v29 = 0;
          v27 = v45;
          if ( v47 != 0 )
            goto LABEL_48;
        }
      }
      v36 = v30;
      LODWORD(v5) = 0;
      v35 = tipc_send_cmd(a1, v36, v27, -41, 0, 0);
      if ( v35 == 0 )
        goto LABEL_10;
    }
    LODWORD(v5) = v35;
    printf("%s:%d: failed (%d) to send response\n", "handle_conn_req", 406);
    goto LABEL_10;
  }
  LODWORD(v5) = -8;
LABEL_11:
  while ( 1 )
  {
    v12 = vqueue_add_buf(a1 + 208, (unsigned __int16 *)&v50, v5);
    if ( v12 == -15 )
      return 0;
    if ( v12 == 0 )
      goto LABEL_2;
    panic(v3, "Unable (%d) to return buffer to vqueue\n", v12);
LABEL_14:
    LODWORD(v5) = -8;
LABEL_10:
    vqueue_unmap_iovs((__int64)v51);
  }
}

/* ===== tipc_dev_stop @ 0x94033914 size 540 ===== */
__int64 __fastcall tipc_dev_stop(__int64 a1)
{
  __int64 v1; // x30
  __int64 v3; // x26
  int v5; // w2
  __int64 v6; // x28
  __int64 v7; // x19
  unsigned __int64 v8; // x27
  _QWORD *v9; // x1
  __int64 v10; // x0
  unsigned __int64 v11; // x0
  unsigned int *v12; // x1
  unsigned int v13; // w2
  __int64 v14; // x0
  int v15; // w2
  __int64 v16; // x0
  __int64 v17; // [xsp+68h] [xbp+68h]

  v3 = v1;
  if ( a1 != 0 )
  {
    if ( *(_DWORD *)a1 == 0 )
      return 0;
    v17 = a1 + 208;
    *(_BYTE *)(a1 + 70217) = 1;
    ((void (*)(void))loc_94031C08)();
    v5 = thread_join(*(_QWORD *)(a1 + 70200), nullptr, 0x3E8u);
    if ( v5 != 0 )
      goto LABEL_17;
    *(_BYTE *)(a1 + 70216) = 1;
    *(_QWORD *)(a1 + 70200) = 0;
    *(_BYTE *)(a1 + 70217) = 0;
    v6 = a1 + 69984;
    mutex_acquire_timeout(a1 + 70144, 0xFFFFFFFFLL);
    v7 = a1 + 352;
    v8 = 0;
    do
    {
      while ( 1 )
      {
        if ( ((*(_QWORD *)(v6 + 8 * (v8 >> 6)) >> v8) & 1) != 0 )
        {
          v9 = *(_QWORD **)(v7 + 8);
          if ( v9 != nullptr )
          {
            hlist_remove_handle(a1 + 70064, v9);
            v10 = *(_QWORD *)(v7 + 8);
            *(_QWORD *)(v10 + 96) = 0;
            handle_decref(v10);
            v11 = 0xF0F0F0F0F0F0F0F1LL * ((v7 - (a1 + 352)) >> 4);
            if ( (unsigned int)v11 <= 0xFF )
              break;
          }
        }
        v7 += 272;
        ++v8;
        if ( v7 == v6 )
          goto LABEL_13;
      }
      v12 = (unsigned int *)(v6 + (((__int64)(int)v11 >> 3) & 0x1FFFFFFFFFFFFFFCLL));
      do
        v13 = __ldxr(v12);
      while ( __stxr(v13 & ~(1 << v11), v12) != 0 );
      v7 += 272;
      ++v8;
      v14 = a1 + 272LL * (unsigned int)v11;
      *(_QWORD *)(v14 + 360) = 0;
      *(_DWORD *)(v14 + 352) = 0;
      *(_BYTE *)(v14 + 368) = 0;
    }
    while ( v7 != v6 );
LABEL_13:
    mutex_release(a1 + 70144);
    event_signal(a1 + 70016, 0);
    ((void (__fastcall *)(__int64))loc_94031C08)(a1 + 64);
    v15 = thread_join(*(_QWORD *)(a1 + 70208), nullptr, 0x3E8u);
    if ( v15 == 0 )
    {
      *(_QWORD *)(a1 + 70208) = 0;
      *(_BYTE *)(a1 + 70216) = 0;
      ((void (__fastcall *)(__int64))loc_94031B4C)(v17);
      ((void (__fastcall *)(__int64))loc_94031B4C)(a1 + 64);
      *(_DWORD *)a1 = 0;
      return 0;
    }
  }
  else
  {
    panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 922, "vd");
  }
  panic(v3, "unable to shutdown tx thread: %d\n", v15);
LABEL_17:
  v16 = panic(v3, "unable to shutdown rx thread: %d\n", v5);
  return handle_tx_msg(v16);
}

/* ===== handle_tx_msg @ 0x94033B30 size 936 ===== */
__int64 __fastcall handle_tx_msg(__int64 a1)
{
  __int64 v1; // x25
  __int64 v2; // x19
  int v4; // w3
  __int64 v6; // x19
  __int64 v7; // x0
  int *v8; // x1
  int v9; // w24
  int v10; // w0
  unsigned int v11; // w0
  _QWORD *v12; // x24
  int *v13; // x3
  unsigned __int64 v14; // x22
  unsigned int *v15; // x0
  unsigned int v16; // w3
  __int64 v17; // x0
  __int64 v18; // x0
  __int64 v19; // x1
  __int64 v20; // x2
  __int64 v21; // [xsp+68h] [xbp+68h]
  __int64 v22; // [xsp+70h] [xbp+70h]
  int v23; // [xsp+88h] [xbp+88h]
  int v24; // [xsp+88h] [xbp+88h]
  int v25; // [xsp+94h] [xbp+94h] BYREF
  _DWORD *v26; // [xsp+98h] [xbp+98h] BYREF
  _DWORD v27[4]; // [xsp+A0h] [xbp+A0h] BYREF
  _DWORD *v28; // [xsp+B0h] [xbp+B0h] BYREF
  __int64 v29; // [xsp+B8h] [xbp+B8h] BYREF

  v1 = a1 + 69632;
  v2 = *(unsigned __int8 *)(a1 + 70216);
  if ( *(_BYTE *)(a1 + 70216) != 0 )
    return 0;
  v22 = a1 + 70016;
  while ( 1 )
  {
    event_wait_timeout(v22, 0xFFFFFFFFLL);
    v4 = ((__int64 (__fastcall *)(__int64, _DWORD **, int *, __int64))loc_9402DED0)(v1 + 432, &v26, &v25, 0xFFFFFFFFLL);
    if ( v4 != -2 )
      break;
LABEL_11:
    if ( *(_BYTE *)(v1 + 584) != 0 )
      return 0;
  }
  while ( (v4 & 0x80000000) == 0 )
  {
    if ( v26 == nullptr )
    {
      panic(v21, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 817, "chan");
LABEL_26:
      panic(
        v21,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        "lk/trusty/lib/trusty/tipc_dev.c",
        818,
        "ipc_is_channel(chan)");
LABEL_27:
      v7 = v2;
LABEL_28:
      mutex_release(v7);
      goto LABEL_10;
    }
    if ( !ipc_is_channel((__int64)v26) )
      goto LABEL_26;
    if ( (v25 & 1) != 0 )
    {
      v6 = (__int64)v26;
      mutex_acquire_timeout(v1 + 512, 0xFFFFFFFFLL);
      v2 = *(_QWORD *)(v6 + 96);
      v7 = v1 + 512;
      if ( v2 == 0 )
        goto LABEL_28;
      v23 = *(_DWORD *)v2;
      mutex_release(v7);
      tipc_send_cmd(a1, -252645135 * ((v2 - (a1 + 352)) >> 4) + 1000, v23, 0, 4096, 1);
    }
    else
    {
      if ( (v25 & 8) != 0 )
      {
        v2 = (__int64)v26;
        v29 = 0;
        v28 = v26;
        mutex_acquire_timeout(v1 + 512, 0xFFFFFFFFLL);
        v8 = *(int **)(v2 + 96);
        v7 = v1 + 512;
        if ( v8 != nullptr )
        {
          v9 = *v8;
          mutex_release(v7);
          while ( 1 )
          {
            v10 = ipc_msg_get_next(v2, &v29);
            if ( v10 == -4 )
              goto LABEL_10;
            if ( v10 != 0 )
            {
              panic(v21, "%s: failed (%d) to get message\n", "handle_tx_msg", v10);
              goto LABEL_33;
            }
            v11 = tipc_send_msg(
                    a1,
                    0,
                    v9,
                    (__int64 (__fastcall *)(__int64, __int64, __int64))&loc_94032D44,
                    (__int64)&v28,
                    v29);
            if ( v11 != 0 )
              printf("%s:%d: tipc_send_data failed (%d)\n", "handle_tx_msg", 724, v11);
            ipc_msg_free(v2, HIDWORD(v29));
          }
        }
        goto LABEL_28;
      }
      if ( (v25 & 4) != 0 )
      {
        v2 = v1 + 512;
        v12 = v26;
        mutex_acquire_timeout(v1 + 512, 0xFFFFFFFFLL);
        v13 = (int *)v12[12];
        if ( v13 != nullptr )
        {
          v24 = *v13;
          v14 = 0xF0F0F0F0F0F0F0F1LL * (((__int64)v13 - a1 - 352) >> 4);
          hlist_remove_handle(v1 + 432, v12);
          v12[12] = 0;
          handle_decref((__int64)v12);
          if ( (unsigned int)v14 <= 0xFF )
          {
            v15 = (unsigned int *)(a1 + (((__int64)(int)v14 >> 3) & 0x1FFFFFFFFFFFFFFCLL) + 69984);
            do
              v16 = __ldxr(v15);
            while ( __stxr(v16 & ~(1 << v14), v15) != 0 );
            v17 = a1 + 272LL * (unsigned int)v14;
            *(_QWORD *)(v17 + 360) = 0;
            *(_DWORD *)(v17 + 352) = 0;
            *(_BYTE *)(v17 + 368) = 0;
          }
          mutex_release(v1 + 512);
          v27[0] = 5;
          v27[1] = 4;
          v27[2] = v24;
          v28 = v27;
          v29 = 12;
          tipc_send_msg(
            a1,
            v14 + 1000,
            53,
            (__int64 (__fastcall *)(__int64, __int64, __int64))tipc_copy_to_buf,
            (__int64)&v28,
            0xCu);
          goto LABEL_10;
        }
        goto LABEL_27;
      }
    }
LABEL_10:
    ((void (__fastcall *)(_DWORD *))loc_9402D978)(v26);
    v4 = ((__int64 (__fastcall *)(__int64, _DWORD **, int *, __int64))loc_9402DED0)(v1 + 432, &v26, &v25, 0xFFFFFFFFLL);
    if ( v4 == -2 )
      goto LABEL_11;
  }
LABEL_33:
  v18 = panic(v21, "%s: couldn't wait for handle events (%d)\n", "handle_tx", v4);
  return tipc_handle_save_ctx(v18, v19, v20);
}

/* ===== tipc_handle_save_ctx @ 0x94033ED8 size 416 ===== */
__int64 __fastcall tipc_handle_save_ctx(__int64 a1, _QWORD *a2, int a3)
{
  __int64 v6; // x2
  _QWORD *v7; // x3
  _QWORD *v8; // x22
  int v9; // w19
  __int64 result; // x0
  unsigned int v11; // w19
  __int64 v12; // [xsp+58h] [xbp+58h] BYREF
  _BYTE v13[256]; // [xsp+60h] [xbp+60h] BYREF

  v12 = 0;
  memset(v13, 0, 256);
  strcpy(v13, a1);
  if ( (unsigned int)ipc_chan_open(a2[5], (__int64)v13, 0x100u, 0, &v12) != 0 )
  {
    v6 = v12;
    v7 = nullptr;
    v8 = a2 + 8704;
    v9 = 0;
    if ( v12 != 0 )
    {
LABEL_3:
      *(_QWORD *)(v6 + 96) = v7;
      hlist_add_handle(v8 + 54, v6);
      event_signal((__int64)(v8 + 48), 0);
      return 0;
    }
  }
  else
  {
    v8 = a2 + 8704;
    mutex_acquire_timeout((__int64)(a2 + 8768), 0xFFFFFFFFLL);
    v9 = tipc_handle_alloc(a2, a3, v12, a1);
    if ( v9 != 0 )
    {
      mutex_release((__int64)(a2 + 8768));
      v6 = v12;
      if ( v12 != 0 )
      {
        v7 = nullptr;
        if ( (unsigned int)(v9 - 1000) <= 0xFF
          && ((a2[((unsigned __int64)(unsigned int)(v9 - 1000) >> 6) + 8748] >> ((unsigned __int8)v9 + 24)) & 1) != 0 )
        {
          v7 = &a2[34 * (unsigned int)(v9 - 1000) + 44];
        }
        goto LABEL_3;
      }
    }
    else
    {
      handle_decref(v12);
      v12 = 0;
      mutex_release((__int64)(a2 + 8768));
      v6 = v12;
      v7 = nullptr;
      if ( v12 != 0 )
        goto LABEL_3;
    }
  }
  v11 = tipc_send_cmd((__int64)a2, v9, a3, -41, 0, 0);
  result = 0;
  if ( v11 != 0 )
  {
    printf("%s:%d: failed (%d) to send response\n", "tipc_handle_save_ctx", 350, v11);
    return v11;
  }
  return result;
}

/* ===== tipc_dev_create @ 0x94034078 size 336 ===== */
__int64 __fastcall tipc_dev_create(__int64 a1, __int64 a2, __int64 a3, _QWORD *a4)
{
  __int64 v4; // x30
  __int64 v9; // x0
  _QWORD *v10; // x19
  __int64 v11; // x20
  unsigned int v12; // w20

  if ( a3 == 0 )
  {
    panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1238, "uuid");
  }
  else if ( a1 != 0 )
  {
    if ( a2 == 0 )
    {
LABEL_13:
      panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1240, "size");
      return 4294967291LL;
    }
    v9 = calloc(1, 70224);
    v10 = (_QWORD *)v9;
    if ( v9 == 0 )
      return 4294967291LL;
    v11 = v9 + 69632;
    mutex_init(v9 + 70144);
    v10[5] = a3;
    v10[6] = a1;
    v10[4] = qword_9405AD88;
    v10[7] = a2;
    hlist_init((_QWORD *)(v11 + 432));
    event_init(v11 + 384, 0, 1);
    v12 = virtio_register_device((__int64)v10);
    if ( v12 != 0 )
    {
      free(v10);
      return v12;
    }
    else
    {
      if ( a4 != nullptr )
        *a4 = v10;
      return 0;
    }
  }
  panic(v4, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "lk/trusty/lib/trusty/tipc_dev.c", 1239, "descr");
  goto LABEL_13;
}

/* ===== tipc_init @ 0x940341C8 size 80 ===== */
__int64 tipc_init()
{
  __int64 result; // x0

  result = tipc_dev_create((__int64)qword_94051880, 108, -536668192, nullptr);
  if ( (_DWORD)result != 0 )
    return printf("%s:%d: WARNING: failed (%d) to register tipc device\n", "tipc_init", 51, result);
  return result;
}

/* ===== is_tipc_uuid @ 0x94034218 size 20 ===== */
bool __fastcall is_tipc_uuid(__int64 a1)
{
  return a1 == -536668192;
}

/* ===== nullsub_5 @ 0x9403422C size 4 ===== */
void nullsub_5()
{
  ;
}

/* ===== nullsub_6 @ 0x94034230 size 4 ===== */
void nullsub_6()
{
  ;
}

/* ===== clk_get_info @ 0x94034234 size 212 ===== */
__int64 __fastcall clk_get_info(int a1)
{
  __int64 v1; // x1
  int v2; // t1
  __int64 v3; // x3
  __int64 result; // x0
  int v5; // w1

  if ( MEMORY[0xFFFFFFFFE003ADE0] == 0 )
    return 0;
  if ( MEMORY[0xFFFFFFFFE003ADC0] != a1 )
  {
    v1 = -536629784;
    while ( 1 )
    {
      v3 = v1;
      if ( *(_QWORD *)(v1 + 32) == 0 )
        return 0;
      v2 = *(_DWORD *)v1;
      v1 += 40;
      if ( v2 == a1 )
        goto LABEL_8;
    }
  }
  v3 = -536629824;
LABEL_8:
  v5 = *(_DWORD *)(v3 + 4);
  if ( v5 > 3 )
    return 0;
  result = v3;
  switch ( v5 )
  {
    case 0:
      *(_QWORD *)(v3 + 8) = MEMORY[0xFFFFFFFFE0061260];
      result = v3;
      break;
    case 1:
      *(_QWORD *)(v3 + 8) = MEMORY[0xFFFFFFFFE0061258];
      result = v3;
      break;
    case 2:
      *(_QWORD *)(v3 + 8) = MEMORY[0xFFFFFFFFE0061250];
      result = v3;
      break;
    case 3:
      *(_QWORD *)(v3 + 8) = MEMORY[0xFFFFFFFFE0061268];
      result = v3;
      break;
    default:
      return result;
  }
  return result;
}

/* ===== clk_enable @ 0x94034308 size 160 ===== */
__int64 __fastcall clk_enable(int a1)
{
  __int64 v2; // x19
  int v3; // w0
  __int64 v4; // x1
  unsigned int v6; // [xsp+2Ch] [xbp+2Ch] BYREF

  v2 = clk_get_info(a1);
  if ( v2 != 0 )
  {
    sprd_spin_lock_irqsave(&qword_94067928, &v6, 3221225472LL);
    v3 = *(_DWORD *)(v2 + 24);
    if ( v3 == 0 )
    {
      *(_DWORD *)(*(_QWORD *)(v2 + 8) + *(int *)(v2 + 16) + 4096LL) = *(_DWORD *)(v2 + 20);
      v3 = *(_DWORD *)(v2 + 24);
    }
    v4 = v6;
    *(_DWORD *)(v2 + 24) = v3 + 1;
    sprd_spin_unlock_irqrestore(&qword_94067928, v4, 3221225472LL);
    return 0;
  }
  else
  {
    sprd_log(2, "clk_get_info type:%d failed\n", a1);
    return 1;
  }
}

/* ===== clk_disable @ 0x940343A8 size 212 ===== */
__int64 __fastcall clk_disable(int a1)
{
  __int64 v2; // x19
  int v3; // w0
  unsigned int v4; // w20
  unsigned int v6; // [xsp+3Ch] [xbp+3Ch] BYREF

  v2 = clk_get_info(a1);
  if ( v2 != 0 )
  {
    sprd_spin_lock_irqsave(&qword_94067928, &v6, 3221225472LL);
    v3 = *(_DWORD *)(v2 + 24);
    if ( v3 != 0 )
    {
      *(_DWORD *)(v2 + 24) = v3 - 1;
      v4 = 0;
      if ( v3 == 1 )
        *(_DWORD *)(*(_QWORD *)(v2 + 8) + *(int *)(v2 + 16) + 0x2000LL) = *(_DWORD *)(v2 + 20);
    }
    else
    {
      v4 = 1;
      sprd_log(4, "%s clk:%s enable_count=0!\n", "clk_enable_restore", *(const char **)(v2 + 32));
    }
    sprd_spin_unlock_irqrestore(&qword_94067928, v6, 3221225472LL);
    return v4;
  }
  else
  {
    sprd_log(2, "clk_get_info type:%d failed\n", a1);
    return 1;
  }
}

/* ===== sprd_glb_clk_init @ 0x9403447C size 216 ===== */
__int64 sprd_glb_clk_init()
{
  if ( (unsigned int)sprd_iomap("ap_apb", 1898971136, 0x10000, 2, -536472992) != 0
    || (unsigned int)sprd_iomap("ap_ahb", 551550976, 0x10000, 2, -536473000) != 0
    || (unsigned int)sprd_iomap("aon_apb", 1076756480, 0x10000, 2, -536473008) != 0
    || (unsigned int)sprd_iomap("sec_aon_apb", 839188480, 0x10000, 2, -536472984) != 0 )
  {
    return sprd_log(2, "%s: failed %d\n");
  }
  else
  {
    return sprd_log(2, "sprd glb clk is ok!\n");
  }
}

/* ===== sprd_crypto_init_entry @ 0x94034554 size 20 ===== */
__int64 sprd_crypto_init_entry()
{
  __int64 v0; // x0

  v0 = sprd_crypto_init();
  return install_crypto_handler(v0);
}

/* ===== sprd_crypto_ioctl @ 0x94034568 size 3504 ===== */
__int64 __fastcall sprd_crypto_ioctl(int a1, unsigned int a2)
{
  unsigned int v3; // w19
  __int64 v5; // x22
  __int64 v6; // x0
  __int64 v7; // x23
  __int64 v8; // x0
  __int64 v9; // x22
  __int64 v10; // x23
  __int64 v11; // x24
  __int64 v12; // x22
  __int64 v13; // x24
  __int64 v14; // x23
  int v15; // w19
  int v16; // w19
  __int64 v17; // x25
  __int64 v18; // x24
  __int64 v19; // x22
  __int64 v20; // x21
  __int64 v21; // x23
  __int64 v22; // x25
  __int64 v23; // x24
  __int64 v24; // x21
  __int64 v25; // x0
  __int64 v26; // x21
  int v27; // w19
  int v28; // w19
  __int64 v29; // x2
  __int64 v30; // x1
  __int64 v31; // x0
  _QWORD v32[2]; // [xsp+50h] [xbp+50h] BYREF
  __int64 v33; // [xsp+60h] [xbp+60h]
  __int64 v34; // [xsp+68h] [xbp+68h]
  _QWORD v35[3]; // [xsp+78h] [xbp+78h] BYREF
  __int64 v36; // [xsp+90h] [xbp+90h] BYREF
  __int64 v37; // [xsp+98h] [xbp+98h]
  __int64 v38; // [xsp+A0h] [xbp+A0h]
  __int64 v39; // [xsp+A8h] [xbp+A8h] BYREF
  __int64 v40; // [xsp+B0h] [xbp+B0h] BYREF
  __int64 v41; // [xsp+B8h] [xbp+B8h]
  __int64 v42; // [xsp+C0h] [xbp+C0h]
  __int64 v43; // [xsp+C8h] [xbp+C8h]
  unsigned int v44; // [xsp+D0h] [xbp+D0h]
  unsigned int v45; // [xsp+100h] [xbp+100h]
  unsigned int v46; // [xsp+150h] [xbp+150h]
  unsigned int v47; // [xsp+158h] [xbp+158h] BYREF
  unsigned int v48; // [xsp+15Ch] [xbp+15Ch]
  unsigned int v49; // [xsp+160h] [xbp+160h]
  unsigned int v50; // [xsp+164h] [xbp+164h] BYREF
  unsigned int v51; // [xsp+16Ch] [xbp+16Ch]
  unsigned int v52; // [xsp+170h] [xbp+170h] BYREF
  _DWORD v53[2]; // [xsp+174h] [xbp+174h] BYREF
  unsigned int v54; // [xsp+17Ch] [xbp+17Ch]
  unsigned int v55; // [xsp+180h] [xbp+180h]
  unsigned int v56; // [xsp+184h] [xbp+184h]
  unsigned int v57; // [xsp+188h] [xbp+188h]
  int v58; // [xsp+18Ch] [xbp+18Ch]
  __int64 v59; // [xsp+190h] [xbp+190h]
  unsigned int v60; // [xsp+198h] [xbp+198h]

  switch ( a1 )
  {
    case 2:
      copy_from_user(&v36, a2, 32);
      v9 = malloc(HIDWORD(v38));
      v10 = malloc(164);
      v11 = malloc(1024);
      if ( v9 != 0 && v10 != 0 )
      {
        copy_from_user(v9, (unsigned int)v38, HIDWORD(v38));
        copy_from_user(&v40, HIDWORD(v36), 84);
        v27 = sprd_ecc_verify_init(v45, &v40, HIDWORD(v37), &v47);
        v28 = sprd_ecc_sign(v45, &v47, v9, BYTE4(v38), v10) | v27;
        v3 = v28 | sprd_ecc_sign_result(v10, v11, &v39);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("SPRD_ENGINE_ECC_SIGN failed !errno (%X)\n", v3);
        }
        else
        {
          copy_to_user(HIDWORD(v39), v11, (unsigned int)v39);
          copy_to_user(a2, &v36, 32);
        }
      }
      else
      {
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("Cann't malloc when operate SPRD_ENGINE_ECC_SIGN !\n");
        v3 = -5;
        if ( v9 == 0 )
          goto LABEL_18;
      }
      free(v9);
LABEL_18:
      if ( v10 != 0 )
        free(v10);
      if ( v11 != 0 )
        free(v11);
      return v3;
    case 3:
      copy_from_user(&v36, a2, 32);
      v12 = malloc((unsigned int)v39);
      v13 = malloc(164);
      v14 = malloc(164);
      if ( v12 != 0 && v13 != 0 && v14 != 0 )
      {
        copy_from_user(v12, (unsigned int)v38, HIDWORD(v38));
        copy_from_user(v14, HIDWORD(v39), (unsigned int)v39);
        copy_from_user(&v40, (unsigned int)v36, 164);
        v15 = sprd_ecc_verify_prepare(v46, &v40, (unsigned int)(2 * v37), &v47);
        v16 = sprd_ecc_verify_prepare2(v46, v14, HIDWORD(v38), v13) | v15;
        v3 = v16 | sprd_ecc_verify(v46, &v47, v12, (unsigned __int8)v39, v13);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("SPRD_ENGINE_ECC_VERIFY failed !errno (%X)\n", v3);
        }
        else
        {
          copy_to_user(a2, &v36, 32);
        }
LABEL_27:
        free(v13);
        goto LABEL_28;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("Cann't malloc when operate SPRD_ENGINE_ECC_SIGN !\n");
      v3 = -5;
      if ( v13 != 0 )
        goto LABEL_27;
LABEL_28:
      if ( v14 != 0 )
        free(v14);
      if ( v12 != 0 )
        free(v12);
      return v3;
    case 32:
      copy_from_user(&v47, a2, 8);
      v24 = malloc(v47);
      if ( v24 != 0 )
      {
        v3 = 0;
        sprd_rsa_prime_gen(v47, v24);
        copy_to_user(v48, v24, v47);
        copy_to_user(a2, &v47, 8);
        free(v24);
      }
      else
      {
        v3 = -5;
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_GEN_PRIME !\n");
      }
      return v3;
    case 33:
      copy_from_user(&v47, a2, 68);
      v19 = malloc(v54);
      v20 = malloc((int)v55);
      v21 = malloc((int)v55);
      if ( v20 != 0 && v19 != 0 && v21 != 0 )
      {
        copy_from_user(v19, v53[1], v54);
        v3 = sprd_rsa_key_gen(v19, v54, v55, v21, v20);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("sprd_rsa_key_gen failed !errno (%X)\n", v3);
        }
        else
        {
          copy_to_user(v56, v21, (int)v55);
          copy_to_user(v57, v20, (int)v55);
          copy_to_user(a2, &v47, 68);
        }
LABEL_49:
        free(v19);
        goto LABEL_50;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_GEN !\n");
      v3 = -5;
      if ( v19 != 0 )
        goto LABEL_49;
LABEL_50:
      if ( v20 != 0 )
        free(v20);
      if ( v21 == 0 )
        return v3;
      v8 = v21;
      goto LABEL_11;
    case 34:
      copy_from_user(&v47, a2, 68);
      copy_from_user(v35, v48, 16);
      v38 = v35[1];
      v37 = malloc(HIDWORD(v35[1]));
      v36 = malloc((unsigned int)v38);
      v22 = malloc(v50);
      v23 = malloc(v50);
      if ( v23 != 0 && v22 != 0 && v37 != 0 && v36 != 0 )
      {
        copy_from_user(v37, HIDWORD(v35[0]), HIDWORD(v38));
        copy_from_user(v36, LODWORD(v35[0]), (unsigned int)v38);
        copy_from_user(v22, v49, v50);
        LODWORD(v40) = v58;
        switch ( v58 )
        {
          case 20:
            LODWORD(v41) = v59;
            break;
          case 21:
            v41 = v59;
            break;
          case 11:
            LODWORD(v41) = v59;
            LODWORD(v43) = v60;
            copy_from_user(v42, HIDWORD(v59), v60);
            break;
          default:
            break;
        }
        v32[0] = v40;
        v32[1] = v41;
        v33 = v42;
        v34 = v43;
        v3 = sprd_rsa_public_encrypt(&v36, v22, v50, v23, &v52, v32);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("sprd_rsa_public_encrypt failed !errno (%X)\n", v3);
        }
        else
        {
          copy_to_user(v51, v23, v52);
          copy_to_user(a2, &v47, 68);
        }
        goto LABEL_110;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_ENCRYPT !\n");
      goto LABEL_109;
    case 35:
      copy_from_user(&v47, a2, 68);
      copy_from_user(v35, v47, 24);
      v43 = *(_QWORD *)((char *)&v35[1] + 4);
      v44 = HIDWORD(v35[2]);
      v41 = malloc(LODWORD(v35[2]));
      v40 = malloc((unsigned int)v43);
      v42 = malloc(v44);
      v17 = malloc(v52);
      v18 = malloc(v52);
      if ( v18 == 0 || v17 == 0 || v41 == 0 || v42 == 0 || v40 == 0 )
      {
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_DECRYPT !\n");
        goto LABEL_95;
      }
      copy_from_user(v41, HIDWORD(v35[0]), HIDWORD(v43));
      copy_from_user(v40, LODWORD(v35[0]), (unsigned int)v43);
      copy_from_user(v42, LODWORD(v35[1]), v44);
      copy_from_user(v17, v51, v52);
      LODWORD(v36) = v58;
      switch ( v58 )
      {
        case 20:
          LODWORD(v37) = v59;
          break;
        case 21:
          v37 = v59;
          break;
        case 11:
          LODWORD(v37) = v59;
          LODWORD(v39) = v60;
          copy_from_user(v38, HIDWORD(v59), v60);
          break;
        default:
          break;
      }
      v32[0] = v36;
      v32[1] = v37;
      v33 = v38;
      v34 = v39;
      v3 = sprd_rsa_private_decrypt(&v40, v17, v52, v18, &v50, v32);
      if ( v3 == 0 )
      {
        v29 = v50;
        v30 = v18;
        v31 = v49;
        goto LABEL_145;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("sprd_rsa_private_decrypt failed !errno (%X)\n", v3);
      goto LABEL_96;
    case 36:
      copy_from_user(&v47, a2, 68);
      copy_from_user(v35, v47, 24);
      v43 = *(_QWORD *)((char *)&v35[1] + 4);
      v44 = HIDWORD(v35[2]);
      v41 = malloc(LODWORD(v35[2]));
      v40 = malloc((unsigned int)v43);
      v42 = malloc(v44);
      v17 = malloc(v50);
      v18 = malloc(4096);
      if ( v18 != 0 && v17 != 0 && v41 != 0 && v42 != 0 && v40 != 0 )
      {
        copy_from_user(v41, HIDWORD(v35[0]), HIDWORD(v43));
        copy_from_user(v40, LODWORD(v35[0]), (unsigned int)v43);
        copy_from_user(v42, LODWORD(v35[1]), v44);
        copy_from_user(v17, v49, v50);
        LODWORD(v36) = v58;
        switch ( v58 )
        {
          case 20:
            LODWORD(v37) = v59;
            break;
          case 21:
            v37 = v59;
            break;
          case 11:
            LODWORD(v37) = v59;
            LODWORD(v39) = v60;
            copy_from_user(v38, HIDWORD(v59), v60);
            break;
          default:
            break;
        }
        v32[0] = v36;
        v32[1] = v37;
        v33 = v38;
        v34 = v39;
        v3 = sprd_rsa_sign(&v40, v17, v50, v18, &v52, v32);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("sprd_rsa_sign failed !errno (%X)\n", v3);
        }
        else
        {
          v29 = v52;
          v30 = v18;
          v31 = v51;
LABEL_145:
          copy_to_user(v31, v30, v29);
          copy_to_user(a2, &v47, 68);
        }
LABEL_96:
        free(v17);
        goto LABEL_97;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_SIGN !\n");
LABEL_95:
      v3 = -5;
      if ( v17 != 0 )
        goto LABEL_96;
LABEL_97:
      if ( v18 != 0 )
        free(v18);
      if ( v41 != 0 )
        free(v41);
      if ( v40 != 0 )
        free(v40);
      v8 = v42;
      if ( v42 != 0 )
        goto LABEL_11;
      return v3;
    case 37:
      copy_from_user(&v47, a2, 68);
      copy_from_user(v35, v48, 16);
      v38 = v35[1];
      v37 = malloc(HIDWORD(v35[1]));
      v36 = malloc((unsigned int)v38);
      v22 = malloc(v50);
      v23 = malloc(v52);
      if ( v23 != 0 && v22 != 0 && v37 != 0 && v36 != 0 )
      {
        copy_from_user(v37, HIDWORD(v35[0]), HIDWORD(v38));
        copy_from_user(v36, LODWORD(v35[0]), (unsigned int)v38);
        copy_from_user(v23, v51, v52);
        copy_from_user(v22, v49, v50);
        LODWORD(v40) = v58;
        switch ( v58 )
        {
          case 20:
            LODWORD(v41) = v59;
            break;
          case 21:
            v41 = v59;
            break;
          case 11:
            LODWORD(v41) = v59;
            LODWORD(v43) = v60;
            copy_from_user(v42, HIDWORD(v59), v60);
            break;
          default:
            break;
        }
        v32[0] = v40;
        v32[1] = v41;
        v33 = v42;
        v34 = v43;
        v3 = sprd_rsa_verify(&v36, v22, v50, v23, v52, v32, v53);
        if ( v3 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("sprd_rsa_verify failed !errno (%X)\n", v3);
        }
        else
        {
          copy_to_user(a2, &v47, 68);
        }
LABEL_110:
        free(v22);
        goto LABEL_111;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("Cann't malloc when operate SPRD_ENGINE_RSA_VERIFY !\n");
LABEL_109:
      v3 = -5;
      if ( v22 != 0 )
        goto LABEL_110;
LABEL_111:
      if ( v23 != 0 )
        free(v23);
      if ( v37 != 0 )
        free(v37);
      v8 = v36;
      if ( v36 != 0 )
        goto LABEL_11;
      return v3;
    case 49:
      copy_from_user(&v47, a2, 8);
      v25 = malloc(v47);
      v26 = v25;
      if ( v25 != 0 )
      {
        v3 = sprd_rng_gen(v25, v47);
        copy_to_user(v48, v26, v47);
        copy_to_user(a2, &v47, 8);
LABEL_81:
        v8 = v26;
        goto LABEL_11;
      }
      v3 = -5;
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
        goto LABEL_81;
      log_printf("Cann't malloc when operate SPRD_ENGINE_RNG_GEN !\n");
      v8 = 0;
LABEL_11:
      free(v8);
      return v3;
    case 65:
      copy_from_user(&v47, a2, 16);
      v5 = malloc(v48);
      v6 = malloc(v47);
      v7 = v6;
      if ( v5 != 0 && v6 != 0 )
      {
        copy_from_user(v6, v49, v47);
        v3 = sprd_huk_derive(v7, v47, v5, v48);
        copy_to_user(v50, v5, v48);
        copy_to_user(a2, &v47, 16);
      }
      else
      {
        v3 = -5;
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("Cann't malloc when operate SPRD_ENGINE_HUK_DERIVE !\n");
      }
      free(v5);
      v8 = v7;
      goto LABEL_11;
    default:
      v3 = -24;
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
        log_printf("Don't support this cmd %d  \n", a1);
      return v3;
  }
}

/* ===== sys_crypto_ioctl @ 0x94035318 size 68 ===== */
__int64 __fastcall sys_crypto_ioctl(__int64 a1, int a2, unsigned int a3)
{
  if ( a3 != 0 )
    return sprd_crypto_ioctl(a2, a3);
  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("IOCTL params is wrong !\n");
  return 4294967288LL;
}

/* ===== install_crypto_handler @ 0x9403535C size 76 ===== */
__int64 install_crypto_handler()
{
  __int64 result; // x0

  result = trusty_install_handler(3u, (__int64)qword_9405B108);
  if ( (_DWORD)result != 0 && MEMORY[0xFFFFFFFFE003CB98] > 1 )
    return log_printf("can not install std in handler: %d\n", result);
  return result;
}

/* ===== sprd_queue_find_tail @ 0x940353A8 size 20 ===== */
__int64 __fastcall sprd_queue_find_tail(__int64 *a1)
{
  __int64 result; // x0

  for ( result = *a1; result != 0; result = *(_QWORD *)(result + 8) )
    ;
  return result;
}

/* ===== sprd_queue_add_item_top @ 0x940353BC size 192 ===== */
__int64 __fastcall sprd_queue_add_item_top(__int64 *a1, _QWORD *a2)
{
  int v3; // w0
  _QWORD *v4; // x0
  __int64 v5; // x0
  const void *v7; // x0
  int v9; // [xsp+28h] [xbp+28h]

  v3 = sprd_mutex_lock(a1[3]);
  if ( v3 != 0 )
  {
    v9 = v3;
    v7 = (const void *)get_current_thread();
    sprd_log(3, "%p: %s: %s: failed to get mutex err = %d\n", v7, "SPRD_CE", "sprd_queue_add_item_top", v9);
    return 0xFFFFFFFFLL;
  }
  else
  {
    v4 = (_QWORD *)*a1;
    a2[1] = *a1;
    *a2 = 0;
    if ( v4 != nullptr )
      *v4 = a2;
    v5 = a1[1];
    *a1 = (__int64)a2;
    if ( v5 == 0 )
      a1[1] = (__int64)a2;
    if ( a1[2] == 0 )
      a1[2] = (__int64)a2;
    sprd_queue_find_tail(a1);
    sprd_mutex_unlock(a1[3]);
    return 0;
  }
}

/* ===== sprd_queue_peek @ 0x9403547C size 8 ===== */
__int64 __fastcall sprd_queue_peek(__int64 a1)
{
  return *(_QWORD *)(a1 + 16);
}

/* ===== sprd_queue_pop @ 0x94035484 size 92 ===== */
__int64 __fastcall sprd_queue_pop(__int64 a1)
{
  _QWORD *v3; // x0

  if ( (unsigned int)sprd_mutex_lock(*(_QWORD *)(a1 + 24)) != 0 )
    return 0xFFFFFFFFLL;
  v3 = *(_QWORD **)(a1 + 16);
  if ( v3 != nullptr )
    *(_QWORD *)(a1 + 16) = *v3;
  sprd_mutex_unlock(*(_QWORD *)(a1 + 24));
  return 0;
}

/* ===== sprd_queue_delete_item_bottom @ 0x940354E0 size 180 ===== */
__int64 *__fastcall sprd_queue_delete_item_bottom(_QWORD *a1)
{
  __int64 *v2; // x20
  __int64 v3; // x0
  const void *v5; // x0

  if ( (unsigned int)sprd_mutex_lock(a1[3]) != 0 )
    return nullptr;
  v2 = (__int64 *)a1[1];
  if ( v2 == nullptr || v2 == (__int64 *)a1[2] )
  {
    v5 = (const void *)get_current_thread();
    v2 = nullptr;
    sprd_log(
      3,
      "%p: %s: %s: queue is empty or tail is equal to current\n",
      v5,
      "SPRD_CE",
      "sprd_queue_delete_item_bottom");
    sprd_mutex_unlock(a1[3]);
  }
  else
  {
    v3 = *v2;
    if ( *v2 != 0 )
    {
      *(_QWORD *)(v3 + 8) = 0;
      a1[1] = v3;
    }
    else
    {
      *a1 = 0;
      a1[1] = 0;
      a1[2] = 0;
    }
    sprd_mutex_unlock(a1[3]);
  }
  return v2;
}

/* ===== sprd_queue_init @ 0x94035594 size 56 ===== */
__int64 __fastcall sprd_queue_init(_QWORD *a1)
{
  __int64 v2; // x0

  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  v2 = sprd_mutex_create();
  a1[3] = v2;
  if ( v2 != 0 )
    return 0;
  else
    return 0xFFFFFFFFLL;
}

/* ===== sprd_ce_int_thread_pka @ 0x940355CC size 64 ===== */
void __noreturn sprd_ce_int_thread_pka()
{
  while ( 1 )
    sprd_semaphore_wait(0);
}

/* ===== sprd_ce_int_thread @ 0x9403560C size 64 ===== */
void __noreturn sprd_ce_int_thread()
{
  int v0; // [xsp+3Ch] [xbp+3Ch]

  v0 = 1;
  while ( 1 )
    sprd_semaphore_wait(0);
}

/* ===== ce_cmd_header_init @ 0x9403564C size 44 ===== */
_BYTE *__fastcall ce_cmd_header_init(_BYTE *result)
{
  result[3] = 119;
  result[2] = 48;
  result[1] = 16;
  *result = 8;
  return result;
}

/* ===== ce_write_cmd @ 0x94035678 size 60 ===== */
__int64 __fastcall ce_write_cmd(unsigned __int16 a1, unsigned int a2, __int64 a3)
{
  __int64 result; // x0
  __int64 v4; // x3

  result = a1 | 0x10000000 | ((unsigned __int8)(a2 & 0x1F) << 16);
  v4 = 0;
  for ( MEMORY[0x500] = result; a2 > (unsigned int)v4; MEMORY[0x500] = result )
    result = *(unsigned int *)(a3 + 4 * v4++);
  return result;
}

/* ===== ce_write_cmd_pka @ 0x940356B4 size 60 ===== */
__int64 __fastcall ce_write_cmd_pka(unsigned __int16 a1, unsigned int a2, __int64 a3)
{
  __int64 result; // x0
  __int64 v4; // x3

  result = a1 | 0x10000000 | ((unsigned __int8)(a2 & 0x1F) << 16);
  v4 = 0;
  for ( MEMORY[0x600] = result; a2 > (unsigned int)v4; MEMORY[0x600] = result )
    result = *(unsigned int *)(a3 + 4 * v4++);
  return result;
}

/* ===== ce_write_desc @ 0x940356F0 size 76 ===== */
__int64 __fastcall ce_write_desc(_DWORD *a1)
{
  __int64 result; // x0

  MEMORY[0x500] = ((*a1 & 0x7000000u) >> 4) | 0x20000000 | ((unsigned __int8)a1[5] << 8);
  MEMORY[0x500] = a1[1];
  MEMORY[0x500] = a1[2];
  MEMORY[0x500] = a1[3];
  result = (unsigned int)a1[4];
  MEMORY[0x500] = result;
  return result;
}

/* ===== ce_write_desc_pka @ 0x9403573C size 44 ===== */
__int64 __fastcall ce_write_desc_pka(_DWORD *a1, int a2)
{
  __int64 result; // x0

  MEMORY[0x600] = ((*a1 & 0x7000000u) >> 4) | 0x20000000;
  result = (unsigned int)a1[1];
  MEMORY[0x600] = a2;
  return result;
}

/* ===== ce_get_algo_type @ 0x94035768 size 132 ===== */
__int64 __fastcall ce_get_algo_type(_DWORD *a1)
{
  unsigned int v1; // w1
  __int64 result; // x0

  v1 = *a1 & 0xFFFF0000;
  if ( v1 == 84017152 )
    return 14;
  if ( v1 <= 0x5020000 )
  {
    if ( v1 != 0x2000000 )
    {
      if ( v1 != 83951616 )
      {
        result = 36;
        if ( v1 == 0 )
          return result;
        return 0;
      }
      return 14;
    }
    return 10;
  }
  if ( v1 == 84148224 )
    return 12;
  if ( v1 == 84213760 )
    return 10;
  result = 18;
  if ( v1 != 84082688 )
    return 0;
  return result;
}

/* ===== ce_cfg_ecc_sign @ 0x940357EC size 360 ===== */
__int64 __fastcall ce_cfg_ecc_sign(int *a1)
{
  unsigned __int64 v2; // x2
  __int64 v3; // x0
  __int64 v4; // x0
  unsigned __int64 v5; // x2
  __int64 v6; // x0
  int v7; // w0
  bool v8; // w3
  char v9; // w1
  __int64 v10; // x0
  __int16 v11; // w2
  unsigned __int64 v12; // x2
  __int64 v13; // x0
  unsigned __int64 v14; // x2
  __int64 v15; // x0
  unsigned int v17; // [xsp+38h] [xbp+38h] BYREF
  unsigned int v18; // [xsp+3Ch] [xbp+3Ch]
  int v19; // [xsp+40h] [xbp+40h]
  int v20; // [xsp+44h] [xbp+44h]
  int v21; // [xsp+48h] [xbp+48h] BYREF
  __int16 v22; // [xsp+4Ch] [xbp+4Ch]
  _BYTE v23[4]; // [xsp+50h] [xbp+50h] BYREF
  int v24; // [xsp+54h] [xbp+54h]
  int v25; // [xsp+58h] [xbp+58h]
  char v26; // [xsp+5Ch] [xbp+5Ch]

  memset(&v17, 0, 16);
  v2 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 37)) >> 32) & 0xF;
  v3 = *((_QWORD *)a1 + 37);
  HIBYTE(v17) = HIBYTE(v17) & 0xF0 | v2 & 0xF;
  v19 = virt_to_phys(v3);
  v4 = *((_QWORD *)a1 + 39);
  v17 = v17 & 0xFF000000 | a1[76] & 0xFFFFFF;
  v5 = ((unsigned __int64)virt_to_phys(v4) >> 32) & 0xF;
  v6 = *((_QWORD *)a1 + 39);
  HIBYTE(v18) = HIBYTE(v18) & 0xF0 | v5 & 0xF;
  v20 = virt_to_phys(v6);
  v18 = v18 & 0xFF000000 | a1[80] & 0xFFFFFF;
  ce_write_cmd(0x48u, 4u, (__int64)&v17);
  memset(&v21, 0, 24);
  v21 = *a1;
  ce_cmd_header_init(v23);
  v7 = a1[2];
  v8 = v7 != 0;
  v9 = v23[0] & 0xEF | (16 * (v7 & 1));
  v10 = *((_QWORD *)a1 + 19);
  v11 = v22 & 0xFE0F | (16 * (*a1 & 0x1F));
  v23[0] = v9 & 0xF9 | (4 * v8) | (2 * (a1[1] == 0));
  v22 = v11 | 1;
  v12 = ((unsigned __int64)virt_to_phys(v10) >> 32) & 0xF;
  v13 = *((_QWORD *)a1 + 19);
  v26 = v26 & 0xF0 | v12 & 0xF;
  v14 = ((unsigned __int64)virt_to_phys(v13) >> 32) & 0xF;
  v15 = *((_QWORD *)a1 + 19);
  v26 = v26 & 0xF | (16 * (v14 & 0xF));
  v24 = virt_to_phys(v15);
  v25 = virt_to_phys(*((_QWORD *)a1 + 19));
  return ce_write_desc(&v21);
}

/* ===== ce_cfg_ecc_verify @ 0x94035954 size 200 ===== */
__int64 __fastcall ce_cfg_ecc_verify(int *a1)
{
  __int64 v2; // x20
  __int64 v3; // x0
  int v4; // w0
  int v6; // [xsp+38h] [xbp+38h] BYREF
  char v7; // [xsp+3Ch] [xbp+3Ch]
  char v8; // [xsp+3Fh] [xbp+3Fh]
  char v9; // [xsp+40h] [xbp+40h] BYREF
  char v10; // [xsp+41h] [xbp+41h]
  char v11; // [xsp+42h] [xbp+42h]

  v2 = *((_QWORD *)a1 + 2) + 516LL;
  sprd_ecc_hw_config();
  memset(&v6, 0, 24);
  v6 = *a1;
  ce_cmd_header_init(&v9);
  v11 = v11 & 0xF | 0x80;
  v10 |= 1u;
  v7 |= 1u;
  v9 |= 0x16u;
  v8 = v8 & 0xF0 | 8;
  v3 = virt_to_phys(v2);
  v8 = v8 & 0xF | (16 * (BYTE4(v3) & 0xF));
  v4 = virt_to_phys(v2);
  return ce_write_desc_pka(&v6, v4);
}

/* ===== ce_cfg_rsa_encrypt @ 0x94035A1C size 556 ===== */
__int64 __fastcall ce_cfg_rsa_encrypt(int *a1)
{
  _DWORD *v2; // x22
  __int64 v3; // x0
  __int64 v4; // x22
  __int64 v5; // x0
  __int64 v6; // x22
  __int64 v7; // x0
  __int64 v8; // x22
  __int64 v9; // x22
  __int64 v10; // x0
  __int64 v11; // x22
  unsigned __int64 v12; // x1
  __int64 v13; // x0
  unsigned __int64 v14; // x1
  __int64 v15; // x0
  unsigned __int64 v16; // x2
  __int64 v17; // x0
  __int64 v18; // x0
  unsigned __int64 v19; // x2
  __int64 v20; // x0
  int v21; // w0
  int v23; // [xsp+3Ch] [xbp+3Ch] BYREF
  _DWORD v24[3]; // [xsp+40h] [xbp+40h] BYREF
  int v25; // [xsp+4Ch] [xbp+4Ch] BYREF
  int v26; // [xsp+50h] [xbp+50h] BYREF
  int v27; // [xsp+58h] [xbp+58h] BYREF
  char v28; // [xsp+5Ch] [xbp+5Ch]
  char v29; // [xsp+5Eh] [xbp+5Eh]
  char v30; // [xsp+5Fh] [xbp+5Fh]
  char v31; // [xsp+60h] [xbp+60h] BYREF
  char v32; // [xsp+61h] [xbp+61h]
  char v33; // [xsp+62h] [xbp+62h]

  v2 = *((_DWORD **)a1 + 5);
  v3 = virt_to_phys(*((_QWORD *)a1 + 2));
  *v2 = ce_desc_alg(0, 0, 1, v3 & 0x1FFFF);
  v4 = *((_QWORD *)a1 + 5);
  v5 = virt_to_phys(*((_QWORD *)a1 + 37));
  *(_DWORD *)(v4 + 4) = ce_desc_alg(0, 1, 1, v5 & 0x1FFFF);
  v6 = *((_QWORD *)a1 + 5);
  v7 = virt_to_phys(*((_QWORD *)a1 + 3));
  *(_DWORD *)(v6 + 8) = ce_desc_alg(0, 2, 1, v7 & 0x1FFFF);
  v8 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v8 + 12) = ce_desc_cipher2(0, 3, 1, 2);
  v9 = *((_QWORD *)a1 + 5);
  v10 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v9 + 16) = ce_desc_alg2(0, 3, 1, v10 & 0x1FFFF);
  v11 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v11 + 20) = ce_desc_nop();
  v23 = a1[8];
  ce_write_cmd_pka(0xD0u, 1u, (__int64)&v23);
  memset(v24, 0, 20);
  v12 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 37)) >> 17) & 0x7FFFF;
  v13 = *((_QWORD *)a1 + 39);
  v26 = v12;
  v14 = ((unsigned __int64)virt_to_phys(v13) >> 17) & 0x7FFFF;
  v15 = *((_QWORD *)a1 + 5);
  v25 = v14;
  v16 = ((unsigned __int64)virt_to_phys(v15) >> 32) & 0xF;
  v17 = *((_QWORD *)a1 + 5);
  HIBYTE(v24[0]) = HIBYTE(v24[0]) & 0xF0 | v16 & 0xF;
  v24[2] = virt_to_phys(v17);
  v24[0] = v24[0] & 0xFF000000 | 0x80;
  ce_write_cmd_pka(0x610u, 1u, (__int64)&v26);
  ce_write_cmd_pka(0x60Cu, 1u, (__int64)&v25);
  dcache_clean2(*((_QWORD *)a1 + 5), v24[0] & 0xFFFFFF);
  memset(&v27, 0, 24);
  v27 = *a1;
  ce_cmd_header_init(&v31);
  v18 = *((_QWORD *)a1 + 5);
  v31 |= 0x16u;
  v33 = v33 & 0x3F | 0x80;
  v32 |= 1u;
  v28 |= 3u;
  v29 = -1;
  v30 = v30 & 0xF0 | 3;
  v19 = ((unsigned __int64)virt_to_phys(v18) >> 32) & 0xF;
  v20 = *((_QWORD *)a1 + 5);
  v30 = v30 & 0xF | (16 * (v19 & 0xF));
  v21 = virt_to_phys(v20);
  return ce_write_desc_pka(&v27, v21);
}

/* ===== ce_cfg_rsa_decrypt @ 0x94035C48 size 436 ===== */
__int64 __fastcall ce_cfg_rsa_decrypt(int *a1)
{
  _DWORD *v2; // x22
  __int64 v3; // x22
  __int64 v4; // x22
  __int64 v5; // x0
  __int64 v6; // x22
  unsigned __int64 v7; // x1
  __int64 v8; // x0
  unsigned __int64 v9; // x2
  __int64 v10; // x0
  __int64 v11; // x0
  unsigned __int64 v12; // x2
  __int64 v13; // x0
  int v14; // w0
  int v16; // [xsp+3Ch] [xbp+3Ch] BYREF
  _DWORD v17[3]; // [xsp+40h] [xbp+40h] BYREF
  int v18; // [xsp+4Ch] [xbp+4Ch] BYREF
  int v19; // [xsp+50h] [xbp+50h] BYREF
  int v20; // [xsp+58h] [xbp+58h] BYREF
  char v21; // [xsp+5Ch] [xbp+5Ch]
  char v22; // [xsp+5Eh] [xbp+5Eh]
  char v23; // [xsp+5Fh] [xbp+5Fh]
  _BYTE v24[2]; // [xsp+60h] [xbp+60h] BYREF
  char v25; // [xsp+62h] [xbp+62h]

  v2 = *((_DWORD **)a1 + 4);
  *v2 = ce_desc_hash_init(0, 1);
  v3 = *((_QWORD *)a1 + 4);
  *(_DWORD *)(v3 + 4) = ce_desc_cipher(18, 0);
  v4 = *((_QWORD *)a1 + 4);
  v5 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v4 + 8) = ce_desc_alg2(0, 1, 1, v5 & 0x1FFFF);
  v6 = *((_QWORD *)a1 + 4);
  *(_DWORD *)(v6 + 12) = ce_desc_nop();
  v16 = a1[6];
  ce_write_cmd_pka(0xD0u, 1u, (__int64)&v16);
  memset(v17, 0, 20);
  v19 = 0;
  v7 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 39)) >> 17) & 0x7FFFF;
  v8 = *((_QWORD *)a1 + 4);
  v18 = v7;
  v9 = ((unsigned __int64)virt_to_phys(v8) >> 32) & 0xF;
  v10 = *((_QWORD *)a1 + 4);
  HIBYTE(v17[0]) = HIBYTE(v17[0]) & 0xF0 | v9 & 0xF;
  v17[2] = virt_to_phys(v10);
  v17[0] = v17[0] & 0xFF000000 | 0x30;
  ce_write_cmd_pka(0x610u, 1u, (__int64)&v19);
  ce_write_cmd_pka(0x60Cu, 1u, (__int64)&v18);
  dcache_clean2(*((_QWORD *)a1 + 4), v17[0] & 0xFFFFFF);
  memset(&v20, 0, 24);
  v20 = *a1;
  ce_cmd_header_init(v24);
  v11 = *((_QWORD *)a1 + 4);
  v24[0] |= 0x16u;
  v25 = v25 & 0x3F | 0x80;
  v21 |= 3u;
  v22 = -1;
  v23 = v23 & 0xF0 | 3;
  v12 = ((unsigned __int64)virt_to_phys(v11) >> 32) & 0xF;
  v13 = *((_QWORD *)a1 + 4);
  v23 = v23 & 0xF | (16 * (v12 & 0xF));
  v14 = virt_to_phys(v13);
  return ce_write_desc_pka(&v20, v14);
}

/* ===== ce_cfg_rsa_sign @ 0x94035DFC size 700 ===== */
__int64 __fastcall ce_cfg_rsa_sign(int *a1)
{
  _DWORD *v2; // x22
  __int64 v3; // x22
  __int64 v4; // x22
  __int64 v5; // x22
  int v6; // w0
  _DWORD *v7; // x1
  __int64 v8; // x22
  __int64 v9; // x22
  __int64 v10; // x22
  __int64 v11; // x22
  __int64 v12; // x0
  __int64 v13; // x22
  __int64 v14; // x0
  __int64 v15; // x22
  __int64 v16; // x0
  __int64 v17; // x22
  __int64 v18; // x0
  __int64 v19; // x22
  unsigned __int64 v20; // x1
  __int64 v21; // x0
  unsigned __int64 v22; // x2
  __int64 v23; // x0
  __int64 v24; // x0
  unsigned __int64 v25; // x2
  __int64 v26; // x0
  int v27; // w0
  unsigned int v29; // [xsp+3Ch] [xbp+3Ch] BYREF
  _DWORD v30[3]; // [xsp+40h] [xbp+40h] BYREF
  int v31; // [xsp+4Ch] [xbp+4Ch] BYREF
  int v32; // [xsp+50h] [xbp+50h] BYREF
  int v33; // [xsp+58h] [xbp+58h] BYREF
  char v34; // [xsp+5Ch] [xbp+5Ch]
  char v35; // [xsp+5Eh] [xbp+5Eh]
  char v36; // [xsp+5Fh] [xbp+5Fh]
  _BYTE v37[2]; // [xsp+60h] [xbp+60h] BYREF
  char v38; // [xsp+62h] [xbp+62h]

  v2 = *((_DWORD **)a1 + 5);
  *v2 = ce_desc_hash_init(0, 1);
  v3 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v3 + 4) = ce_desc_cipher(18, 0);
  v4 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v4 + 8) = ce_desc_hash_init(0, 9);
  v5 = *((_QWORD *)a1 + 5);
  v6 = ce_desc_cipher(18, 8);
  v7 = *((_DWORD **)a1 + 37);
  *(_DWORD *)(v5 + 12) = v6;
  v8 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v8 + 16) = ce_desc_hash_data(0, *v7 & 0x1FFFF);
  v9 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v9 + 20) = ce_desc_hash_final(0, 3, 5, 6);
  v10 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v10 + 24) = ce_desc_hash_final2(0, 4, 1, 9);
  v11 = *((_QWORD *)a1 + 5);
  v12 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v11 + 28) = ce_desc_alg2(0, 3, 1, v12 & 0x1FFFF);
  v13 = *((_QWORD *)a1 + 5);
  v14 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v13 + 32) = ce_desc_alg2(0, 4, 1, (v14 & 0x1FFFF) + ((unsigned int)a1[80] >> 2));
  v15 = *((_QWORD *)a1 + 5);
  v16 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v15 + 36) = ce_desc_alg2(0, 5, 1, (v16 & 0x1FFFF) + ((unsigned int)a1[80] >> 1));
  v17 = *((_QWORD *)a1 + 5);
  v18 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v17 + 40) = ce_desc_alg2(0, 6, 1, (v18 & 0x1FFFF) + ((unsigned int)(3 * a1[80]) >> 2));
  v19 = *((_QWORD *)a1 + 5);
  *(_DWORD *)(v19 + 44) = ce_desc_nop();
  v29 = (unsigned int)a1[8] >> 1;
  ce_write_cmd_pka(0xD0u, 1u, (__int64)&v29);
  memset(v30, 0, 20);
  v32 = 0;
  v20 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 39)) >> 17) & 0x7FFFF;
  v21 = *((_QWORD *)a1 + 5);
  v31 = v20;
  v22 = ((unsigned __int64)virt_to_phys(v21) >> 32) & 0xF;
  v23 = *((_QWORD *)a1 + 5);
  HIBYTE(v30[0]) = HIBYTE(v30[0]) & 0xF0 | v22 & 0xF;
  v30[2] = virt_to_phys(v23);
  v30[0] = v30[0] & 0xFF000000 | 0x30;
  ce_write_cmd_pka(0x610u, 1u, (__int64)&v32);
  ce_write_cmd_pka(0x60Cu, 1u, (__int64)&v31);
  dcache_clean2(*((_QWORD *)a1 + 5), v30[0] & 0xFFFFFF);
  memset(&v33, 0, 24);
  v33 = *a1;
  ce_cmd_header_init(v37);
  v24 = *((_QWORD *)a1 + 5);
  v37[0] |= 0x16u;
  v38 = v38 & 0x3F | 0x80;
  v34 |= 3u;
  v35 = -1;
  v36 = v36 & 0xF0 | 3;
  v25 = ((unsigned __int64)virt_to_phys(v24) >> 32) & 0xF;
  v26 = *((_QWORD *)a1 + 5);
  v36 = v36 & 0xF | (16 * (v25 & 0xF));
  v27 = virt_to_phys(v26);
  return ce_write_desc_pka(&v33, v27);
}

/* ===== ce_cfg_hash @ 0x940360B8 size 1208 ===== */
__int64 __fastcall ce_cfg_hash(int *a1)
{
  unsigned int v2; // w1
  int *v3; // x3
  unsigned int i; // w0
  __int64 v5; // x8
  __int64 v6; // x6
  __int64 v7; // x5
  int v8; // w4
  unsigned int v9; // w7
  unsigned int v10; // w1
  unsigned __int64 v11; // x2
  __int64 v12; // x0
  __int64 v13; // x0
  unsigned __int64 v14; // x2
  __int64 v15; // x0
  unsigned __int64 v16; // x2
  __int64 v17; // x0
  int v18; // w1
  __int64 v19; // x0
  unsigned __int64 v20; // x2
  __int64 v21; // x0
  unsigned __int64 v22; // x2
  __int64 v23; // x0
  int *v25; // x3
  unsigned int j; // w0
  __int64 v27; // x8
  __int64 v28; // x6
  __int64 v29; // x5
  int v30; // w4
  unsigned int v31; // w7
  __int16 v32; // w3
  unsigned int v33; // w4
  int v34; // w0
  int v35; // w3
  unsigned int v36; // w1
  __int16 v37; // [xsp+38h] [xbp+38h] BYREF
  __int16 v38; // [xsp+3Ah] [xbp+3Ah]
  char v39; // [xsp+40h] [xbp+40h] BYREF
  char v40; // [xsp+41h] [xbp+41h]
  int v41; // [xsp+44h] [xbp+44h]
  _DWORD v42[4]; // [xsp+48h] [xbp+48h] BYREF
  unsigned int v43; // [xsp+58h] [xbp+58h] BYREF
  unsigned int v44; // [xsp+5Ch] [xbp+5Ch]
  int v45; // [xsp+60h] [xbp+60h]
  int v46; // [xsp+64h] [xbp+64h]
  int v47; // [xsp+68h] [xbp+68h] BYREF
  char v48; // [xsp+6Ch] [xbp+6Ch]
  char v49; // [xsp+6Dh] [xbp+6Dh]
  char v50; // [xsp+70h] [xbp+70h] BYREF
  char v51; // [xsp+71h] [xbp+71h]
  int v52; // [xsp+74h] [xbp+74h]
  int v53; // [xsp+78h] [xbp+78h]
  char v54; // [xsp+7Ch] [xbp+7Ch]
  _DWORD v55[8]; // [xsp+80h] [xbp+80h] BYREF

  switch ( *a1 )
  {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
      goto LABEL_6;
    case 3:
      v2 = a1[24];
      if ( v2 != 0 )
      {
        v3 = a1 + 16;
        for ( i = 0; i < v2; i += 4 )
        {
          v5 = i + 3;
          v6 = i + 1;
          v7 = i + 2;
          v8 = LOBYTE(v3[i / 4]);
          v9 = i >> 2;
          v55[v9] = *((unsigned __int8 *)v3 + v5)
                  | (v8 << 24)
                  | (*((unsigned __int8 *)v3 + v6) << 16)
                  | (*((unsigned __int8 *)v3 + v7) << 8);
        }
        ce_write_cmd(0xA0u, v2 >> 2, (__int64)v55);
      }
LABEL_6:
      v10 = a1[15];
      if ( v10 == 0 )
        goto LABEL_7;
      v25 = a1 + 7;
      for ( j = 0; j < v10; j += 4 )
      {
        v27 = j + 3;
        v28 = j + 1;
        v29 = j + 2;
        v30 = LOBYTE(v25[j / 4]);
        v31 = j >> 2;
        v55[v31] = *((unsigned __int8 *)v25 + v27)
                 | (v30 << 24)
                 | (*((unsigned __int8 *)v25 + v28) << 16)
                 | (*((unsigned __int8 *)v25 + v29) << 8);
      }
      ce_write_cmd(0x80u, v10 >> 2, (__int64)v55);
      if ( a1[1] == 0 )
        goto LABEL_20;
      goto LABEL_8;
    case 7:
    case 8:
      memset(&v37, 0, 4);
      v32 = v38 & 0xC01F | (32 * (a1[15] & 0x1FF));
      v37 = v37 & 0xF801 | 0xC0;
      v38 = v32;
      ce_write_cmd(0x340u, 1u, (__int64)&v37);
      goto LABEL_7;
    default:
LABEL_7:
      if ( a1[1] == 0 )
      {
LABEL_20:
        memset(v42, 0, 16);
        switch ( *a1 )
        {
          case 1:
          case 2:
          case 3:
          case 5:
          case 7:
            v33 = _byteswap_ulong(a1[25]);
            v34 = *((unsigned __int8 *)a1 + 114);
            v35 = (*((unsigned __int8 *)a1 + 113) << 16)
                | (*((unsigned __int8 *)a1 + 112) << 24)
                | *((unsigned __int8 *)a1 + 115);
            v36 = _byteswap_ulong(a1[27]);
            v42[1] = _byteswap_ulong(a1[26]);
            v42[2] = v36;
            v42[3] = v35 | (v34 << 8);
            v42[0] = v33;
            ce_write_cmd(0x70u, 4u, (__int64)v42);
            break;
          default:
            ce_write_cmd(0x70u, 4u, (__int64)v42);
            break;
        }
      }
LABEL_8:
      memset(&v43, 0, 16);
      v11 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 37)) >> 32) & 0xF;
      v12 = *((_QWORD *)a1 + 37);
      HIBYTE(v43) = HIBYTE(v43) & 0xF0 | v11 & 0xF;
      v45 = virt_to_phys(v12);
      v13 = *((_QWORD *)a1 + 39);
      v43 = v43 & 0xFF000000 | a1[76] & 0xFFFFFF;
      v14 = ((unsigned __int64)virt_to_phys(v13) >> 32) & 0xF;
      v15 = *((_QWORD *)a1 + 39);
      HIBYTE(v44) = HIBYTE(v44) & 0xF0 | v14 & 0xF;
      v46 = virt_to_phys(v15);
      v44 = v44 & 0xFF000000 | a1[80] & 0xFFFFFF;
      ce_write_cmd(0x48u, 4u, (__int64)&v43);
      memset(&v39, 0, 8);
      v16 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 41)) >> 32) & 0xF;
      v17 = *((_QWORD *)a1 + 41);
      v40 = v40 & 0xF0 | v16 & 0xF;
      v41 = virt_to_phys(v17);
      v39 = a1[84];
      ce_write_cmd(0x68u, 2u, (__int64)&v39);
      memset(&v47, 0, 24);
      v47 = *a1;
      ce_cmd_header_init(&v50);
      if ( (unsigned int)(v47 - 7) > 1 )
        v51 &= ~1u;
      else
        v51 |= 2u;
      v18 = a1[15];
      v50 = v50 & 0x89
          | ((a1[5] & 1) << 6)
          | (32 * (a1[6] & 1))
          | (16 * (a1[2] & 1))
          | (4 * (a1[2] != 0))
          | (2 * (a1[1] == 0));
      if ( v18 == 24 )
      {
        v49 = v49 & 0x8F | 0x10;
      }
      else if ( v18 == 16 )
      {
        v49 &= 0x8Fu;
      }
      else
      {
        v49 = v49 & 0x8F | 0x20;
      }
      switch ( *a1 )
      {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          v49 = v49 & 0xF8 | *a1 & 7;
          break;
        case 7:
          v49 = v49 & 0xF8 | 1;
          break;
        case 8:
          v49 = v49 & 0xF8 | 4;
          break;
        default:
          break;
      }
      v19 = *((_QWORD *)a1 + 18);
      v48 = v48 & 0xEF | (16 * (a1[4] & 1)) | 1;
      v20 = ((unsigned __int64)virt_to_phys(v19) >> 32) & 0xF;
      v21 = *((_QWORD *)a1 + 18);
      v54 = v54 & 0xF0 | v20 & 0xF;
      v22 = ((unsigned __int64)virt_to_phys(v21) >> 32) & 0xF;
      v23 = *((_QWORD *)a1 + 18);
      v54 = v54 & 0xF | (16 * (v22 & 0xF));
      v52 = virt_to_phys(v23);
      v53 = virt_to_phys(*((_QWORD *)a1 + 18));
      return ce_write_desc(&v47);
  }
}

/* ===== ce_cfg_rng @ 0x94036570 size 416 ===== */
__int64 __fastcall ce_cfg_rng(int *a1)
{
  _DWORD *v2; // x22
  __int64 v3; // x22
  __int64 v4; // x0
  __int64 v5; // x22
  unsigned __int64 v6; // x1
  __int64 v7; // x0
  unsigned __int64 v8; // x2
  __int64 v9; // x0
  __int64 v10; // x0
  unsigned __int64 v11; // x2
  __int64 v12; // x0
  int v13; // w0
  int v15; // [xsp+3Ch] [xbp+3Ch] BYREF
  _DWORD v16[3]; // [xsp+40h] [xbp+40h] BYREF
  int v17; // [xsp+4Ch] [xbp+4Ch] BYREF
  int v18; // [xsp+50h] [xbp+50h] BYREF
  int v19; // [xsp+58h] [xbp+58h] BYREF
  char v20; // [xsp+5Ch] [xbp+5Ch]
  char v21; // [xsp+5Eh] [xbp+5Eh]
  char v22; // [xsp+5Fh] [xbp+5Fh]
  _BYTE v23[2]; // [xsp+60h] [xbp+60h] BYREF
  char v24; // [xsp+62h] [xbp+62h]

  v2 = *((_DWORD **)a1 + 2);
  *v2 = ce_desc_rng(0, 0);
  v3 = *((_QWORD *)a1 + 2);
  v4 = virt_to_phys(*((_QWORD *)a1 + 39));
  *(_DWORD *)(v3 + 4) = ce_desc_alg2(0, 0, 1, v4 & 0x1FFFF);
  v5 = *((_QWORD *)a1 + 2);
  *(_DWORD *)(v5 + 8) = ce_desc_nop();
  v15 = a1[80];
  ce_write_cmd_pka(0xD0u, 1u, (__int64)&v15);
  memset(v16, 0, 20);
  v18 = 0;
  v6 = ((unsigned __int64)virt_to_phys(*((_QWORD *)a1 + 39)) >> 17) & 0x7FFFF;
  v7 = *((_QWORD *)a1 + 2);
  v17 = v6;
  v8 = ((unsigned __int64)virt_to_phys(v7) >> 32) & 0xF;
  v9 = *((_QWORD *)a1 + 2);
  HIBYTE(v16[0]) = HIBYTE(v16[0]) & 0xF0 | v8 & 0xF;
  v16[2] = virt_to_phys(v9);
  v16[0] = v16[0] & 0xFF000000 | 0xC;
  ce_write_cmd_pka(0x610u, 1u, (__int64)&v18);
  ce_write_cmd_pka(0x60Cu, 1u, (__int64)&v17);
  dcache_clean2(*((_QWORD *)a1 + 2), v16[0] & 0xFFFFFF);
  memset(&v19, 0, 24);
  v19 = *a1;
  ce_cmd_header_init(v23);
  v10 = *((_QWORD *)a1 + 2);
  v23[0] |= 0x16u;
  v24 = v24 & 0x3F | 0x80;
  v20 |= 3u;
  v21 = -1;
  v22 = v22 & 0xF0 | 3;
  v11 = ((unsigned __int64)virt_to_phys(v10) >> 32) & 0xF;
  v12 = *((_QWORD *)a1 + 2);
  v22 = v22 & 0xF | (16 * (v11 & 0xF));
  v13 = virt_to_phys(v12);
  return ce_write_desc_pka(&v19, v13);
}

/* ===== sprd_crypto_process @ 0x94036710 size 272 ===== */
__int64 __fastcall sprd_crypto_process(int *a1)
{
  unsigned int v2; // w1

  v2 = *a1 & 0xFFFF0000;
  if ( v2 == 84017152 )
  {
    ce_cfg_rsa_sign(a1);
    a1[1] = 1;
    return 1;
  }
  else if ( v2 <= 0x5020000 )
  {
    switch ( v2 )
    {
      case 0x2000000u:
        ce_cfg_ecc_sign(a1);
        a1[1] = 1;
        return 1;
      case 0x5010000u:
        ce_cfg_rsa_encrypt(a1);
        a1[1] = 1;
        return 1;
      case 0u:
        ce_cfg_hash(a1);
        a1[1] = 1;
        return 1;
      default:
LABEL_7:
        a1[1] = 1;
        return 1;
    }
  }
  else if ( v2 == 84148224 )
  {
    ce_cfg_rng(a1);
    a1[1] = 1;
    return 1;
  }
  else
  {
    if ( v2 != 84213760 )
    {
      if ( v2 == 84082688 )
        ce_cfg_ecc_verify(a1);
      goto LABEL_7;
    }
    ce_cfg_rsa_decrypt(a1);
    a1[1] = 1;
    return 1;
  }
}

/* ===== ce_get_pka_status @ 0x94036820 size 24 ===== */
__int64 ce_get_pka_status()
{
  return (unsigned int)(109 - MEMORY[0x504]);
}

/* ===== ce_get_pka_result @ 0x94036838 size 16 ===== */
__int64 ce_get_pka_result()
{
  return MEMORY[0x514];
}

/* ===== ce_get_ce_status @ 0x94036848 size 24 ===== */
__int64 ce_get_ce_status()
{
  return (unsigned int)(109 - MEMORY[0x604]);
}

/* ===== ce_get_ce_result @ 0x94036860 size 16 ===== */
__int64 ce_get_ce_result()
{
  return MEMORY[0x614];
}

/* ===== sprd_ce_int_notify @ 0x94036870 size 232 ===== */
__int64 sprd_ce_int_notify()
{
  int v0; // w19
  int v1; // w21
  int v2; // w20
  const void *v3; // x0

  MEMORY[0x15C] = 1;
  while ( (MEMORY[0x15C] & 2) == 0 )
    ;
  v0 = MEMORY[0x20];
  MEMORY[0x24] = MEMORY[0x20];
  v1 = ce_get_pka_result();
  v2 = ce_get_ce_result();
  MEMORY[0x15C] = 16;
  if ( (v0 & 1) != 0 && v1 != 0 )
  {
    do
    {
      sprd_semaphore_post(0, 0);
      --v1;
    }
    while ( v1 != 0 );
  }
  if ( (v0 & 0x2000) != 0 && v2 != 0 )
  {
    do
    {
      sprd_semaphore_post(0, 0);
      --v2;
    }
    while ( v2 != 0 );
  }
  if ( (v0 & 0x5C10) != 0 )
  {
    while ( 1 )
    {
      v3 = (const void *)get_current_thread();
      sprd_log(3, "%p: %s: %s: int status = 0x%x\n", v3, "SPRD_CE", "sprd_ce_int_notify", v0);
    }
  }
  return 1;
}

/* ===== sprd_ce_set_pka_cb @ 0x94036958 size 12 ===== */
// write access to const memory has been detected, the output may be wrong!
void *__fastcall sprd_ce_set_pka_cb(void *result)
{
  off_94067960 = result;
  return result;
}

/* ===== sprd_ce_set_ce_cb @ 0x94036964 size 12 ===== */
// write access to const memory has been detected, the output may be wrong!
void *__fastcall sprd_ce_set_ce_cb(void *result)
{
  off_94067938 = result;
  return result;
}

/* ===== sprd_ce_prepare @ 0x94036970 size 84 ===== */
__int64 sprd_ce_prepare()
{
  if ( MEMORY[0x58] != 3 )
    MEMORY[0x58] = 3;
  clk_enable(22);
  ce_get_pka_result();
  ce_get_ce_result();
  MEMORY[0x24] = -1;
  MEMORY[0x1C] = 31761;
  return 0;
}

/* ===== sprd_ce_finish @ 0x940369C4 size 20 ===== */
__int64 sprd_ce_finish()
{
  MEMORY[0x1C] = 0;
  return clk_disable(22);
}

/* ===== sprd_ce_init @ 0x940369D8 size 456 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 sprd_ce_init()
{
  int v0; // w0
  int v1; // w0
  const void *v2; // x0
  const void *v4; // x0
  const void *v5; // x0
  const void *v6; // x0
  int v7; // [xsp+28h] [xbp+28h]
  int v8; // [xsp+28h] [xbp+28h]

  v0 = sprd_iomap("sprd_ce", 568328192, 0x100000, 2, &off_94067958);
  if ( v0 != 0 )
  {
    v8 = v0;
    v4 = (const void *)get_current_thread();
    sprd_log(3, "%p: %s: %s: sprd_pal_mem_map failed[0x%x]\n", v4, "SPRD_CE", "sprd_ce_init", v8);
  }
  v1 = sprd_iomap("sprd_clk", 558891008, 0x10000, 2, &off_94067970);
  if ( v1 != 0 )
  {
    v7 = v1;
    v2 = (const void *)get_current_thread();
    sprd_log(3, "%p: %s: %s: sprd_pal_mem_map ap clk phys failed[0x%x]\n", v2, "SPRD_CE", "sprd_ce_init", v7);
  }
  dword_94067968 = 85;
  qword_94067940 = sprd_semaphore_create(0);
  v6 = (const void *)get_current_thread();
  sprd_log(3, "%p: %s: %s: sem init FAILED!\n", v6, "SPRD_CE", "sprd_ce_irq_init");
  qword_94067950 = sprd_semaphore_create(0);
  v5 = (const void *)get_current_thread();
  sprd_log(3, "%p: %s: %s: sem pka init FAILED!\n", v5, "SPRD_CE", "sprd_ce_irq_init");
  qword_94067930 = sprd_thread_create("sprd_ce_int_thread", sprd_ce_int_thread, 0, 28, 4096);
  sprd_thread_resume(nullptr);
  qword_94067948 = sprd_thread_create("sprd_ce_int_thread_pka", sprd_ce_int_thread_pka, 0, 28, 4096);
  sprd_thread_resume(nullptr);
  irq_register(0, sprd_ce_int_notify, 0);
  return irq_enable(0);
}

/* ===== sprd_ce_run_pka_queue @ 0x94036BA0 size 136 ===== */
__int64 sprd_ce_run_pka_queue()
{
  unsigned int v0; // w21
  __int64 v1; // x0
  __int64 v2; // x19

  if ( (unsigned int)sprd_mutex_lock(0) == 0 )
  {
    while ( 1 )
    {
      v1 = sprd_queue_peek(-536472936);
      v2 = v1;
      if ( v1 == 0 )
        break;
      v0 = ce_get_algo_type(*(_DWORD **)(v1 + 16));
      if ( v0 > (unsigned int)ce_get_ce_status() )
        break;
      sprd_queue_pop(-536472936);
      sprd_crypto_process(*(int **)(v2 + 16));
    }
    sprd_mutex_unlock(0);
  }
  return 0;
}

/* ===== sprd_ce_flush_pka @ 0x94036C28 size 112 ===== */
__int64 __fastcall sprd_ce_flush_pka(int *a1)
{
  int i; // w20
  __int64 *v2; // x0
  __int64 *v3; // x19
  __int64 v4; // x1
  __int64 v5; // x0
  __int64 v6; // x0

  for ( i = *a1; i != 0; --i )
  {
    v2 = sprd_queue_delete_item_bottom((_QWORD *)0xFFFFFFFFE0061298LL);
    v3 = v2;
    v4 = 0;
    if ( v2 != nullptr )
    {
      v5 = v2[2];
      if ( v5 != 0 )
      {
        v6 = *(_QWORD *)(v5 + 344);
        if ( v6 != 0 )
          sprd_semaphore_post(v6, 0);
      }
      free(v3, v4);
    }
  }
  sprd_ce_run_pka_queue();
  return 0;
}

/* ===== sprd_ce_run_ce_queue @ 0x94036C98 size 136 ===== */
__int64 sprd_ce_run_ce_queue()
{
  unsigned int v0; // w21
  __int64 v1; // x0
  __int64 v2; // x19

  if ( (unsigned int)sprd_mutex_lock(0) == 0 )
  {
    while ( 1 )
    {
      v1 = sprd_queue_peek(-536472976);
      v2 = v1;
      if ( v1 == 0 )
        break;
      v0 = ce_get_algo_type(*(_DWORD **)(v1 + 16));
      if ( v0 > (unsigned int)ce_get_pka_status() )
        break;
      sprd_queue_pop(-536472976);
      sprd_crypto_process(*(int **)(v2 + 16));
    }
    sprd_mutex_unlock(0);
  }
  return 0;
}

/* ===== sprd_ce_flush_ce @ 0x94036D20 size 112 ===== */
__int64 __fastcall sprd_ce_flush_ce(int *a1)
{
  int i; // w20
  __int64 *v2; // x0
  __int64 *v3; // x19
  __int64 v4; // x1
  __int64 v5; // x0
  __int64 v6; // x0

  for ( i = *a1; i != 0; --i )
  {
    v2 = sprd_queue_delete_item_bottom((_QWORD *)0xFFFFFFFFE0061270LL);
    v3 = v2;
    v4 = 0;
    if ( v2 != nullptr )
    {
      v5 = v2[2];
      if ( v5 != 0 )
      {
        v6 = *(_QWORD *)(v5 + 344);
        if ( v6 != 0 )
          sprd_semaphore_post(v6, 0);
      }
      free(v3, v4);
    }
  }
  sprd_ce_run_ce_queue();
  return 0;
}

/* ===== sprd_crypto_work @ 0x94036D90 size 552 ===== */
__int64 __fastcall sprd_crypto_work(int *a1)
{
  unsigned int v2; // w0
  __int64 v3; // x2
  const char *v4; // x1
  unsigned int v5; // w20
  __int64 v6; // x0
  const void *v8; // x0
  __int64 v9; // x0
  _QWORD *v10; // x20
  int v11; // w0
  int v12; // w0
  const void *v13; // x0

  v2 = *a1 & 0xFFFF0000;
  if ( v2 != 84017152 )
  {
    if ( v2 > 0x5020000 )
    {
      if ( v2 != 84148224 )
      {
        if ( v2 == 84213760 || v2 == 84082688 )
          goto LABEL_18;
LABEL_14:
        v8 = (const void *)get_current_thread();
        v5 = -65535;
        sprd_log(3, "%p: %s: %s: bad algo!\n", v8, "SPRD_CE", "sprd_crypto_process");
        goto LABEL_15;
      }
      v5 = -65529;
      if ( a1[80] == 512 )
        goto LABEL_18;
    }
    else
    {
      if ( v2 != 0x2000000 )
      {
        if ( v2 == 83951616 )
        {
          if ( *((_QWORD *)a1 + 2) == 0 || *((_QWORD *)a1 + 3) == 0 || a1[8] == 0 )
          {
            v3 = get_current_thread();
            v4 = "%p: %s: %s: Bad RSA key!\n";
            goto LABEL_9;
          }
          goto LABEL_18;
        }
        if ( v2 == 0 )
          goto LABEL_18;
        goto LABEL_14;
      }
      if ( a1[76] != 0 || a1[2] != 0 )
        goto LABEL_18;
      v5 = 0;
    }
LABEL_15:
    v6 = *((_QWORD *)a1 + 43);
    if ( v6 == 0 )
      return v5;
LABEL_16:
    sprd_semaphore_post(v6, 0);
    return v5;
  }
  v12 = a1[8];
  if ( (v12 & 0xFFFFFEFF) != 128 && v12 != 32 && ((v12 - 256) & 0xFFFFFEFF) != 0 )
  {
    v3 = get_current_thread();
    v4 = "%p: %s: %s: Bad RSA key len!\n";
LABEL_9:
    v5 = -65529;
    sprd_log(3, v4, v3, "SPRD_CE", "sprd_crypto_process");
    v6 = *((_QWORD *)a1 + 43);
    if ( v6 == 0 )
      return v5;
    goto LABEL_16;
  }
LABEL_18:
  v9 = malloc(24);
  v10 = (_QWORD *)v9;
  if ( v9 != 0 )
  {
    memset(v9, 0, 24);
    v11 = *a1;
    v10[2] = a1;
    if ( (v11 & 0xFF000000) == 0x5000000 )
    {
      sprd_queue_add_item_top((__int64 *)0xFFFFFFFFE0061298LL, v10);
      sprd_ce_run_pka_queue();
    }
    else
    {
      sprd_queue_add_item_top((__int64 *)0xFFFFFFFFE0061270LL, v10);
      sprd_ce_run_ce_queue();
    }
    return 0;
  }
  else
  {
    v13 = (const void *)get_current_thread();
    sprd_log(3, "%p: %s: %s: out of memory !!\n", v13, "SPRD_CE", "sprd_crypto_process");
    return 4294901770LL;
  }
}

/* ===== align_up @ 0x94036FB8 size 20 ===== */
unsigned __int64 __fastcall align_up(__int64 a1, __int64 a2, unsigned int a3)
{
  return (a1 - 1 + a3) & ~(unsigned __int64)(a3 - 1);
}

/* ===== align_overhead @ 0x94036FCC size 32 ===== */
__int64 __fastcall align_overhead(int a1, int a2, int a3)
{
  return ((a2 + a1) & -a3) - ((a3 - 1 + a1) & (unsigned int)-a3);
}

/* ===== sprd_crypto_malloc_buf @ 0x94036FEC size 432 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_crypto_malloc_buf(__int64 a1, unsigned int a2, _QWORD *a3, int *a4)
{
  __int64 result; // x0
  const void *v9; // x0
  int v10; // w0

  if ( a3 != nullptr && a4 != nullptr )
  {
    result = a2 & 0x3F;
    if ( (a2 & 0x3F) != 0 )
    {
      *a3 = 0;
    }
    else
    {
      while ( (unsigned int)sprd_mutex_lock(0) != 0 )
        ;
      qword_94067998 = align_up(0, 0, a2);
      v10 = align_overhead(0, 0, a2);
      *a3 = 0;
      *(_QWORD *)&algn_940679A4[4] = a1;
      *a4 = v10;
      dword_940679A0 = v10;
      return sprd_mutex_unlock(0);
    }
  }
  else
  {
    v9 = (const void *)get_current_thread();
    return sprd_log(3, "%p: %s: %s: buf = NULL or len = NULL\n", v9, "SPRD_CE", "sprd_crypto_malloc_buf");
  }
  return result;
}

/* ===== sprd_crypto_free_buf @ 0x9403719C size 420 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_crypto_free_buf(__int64 result)
{
  __int64 v1; // x0
  const void *v2; // x0

  if ( result != 0 )
  {
    while ( (unsigned int)sprd_mutex_lock(0) != 0 )
      ;
    v1 = sprd_mutex_unlock(0);
    v2 = (const void *)get_current_thread(v1);
    return sprd_log(3, "%p: %s: %s: an addr is not in buf list !\n", v2, "SPRD_CE", "sprd_crypto_free_buf");
  }
  return result;
}

/* ===== sprd_crypto_unlock @ 0x94037340 size 56 ===== */
__int64 sprd_crypto_unlock()
{
  __int64 result; // x0

  result = sprd_mutex_lock(0);
  if ( (_DWORD)result == 0 )
    return sprd_mutex_unlock(0);
  return result;
}

/* ===== sprd_crypto_lock_init @ 0x94037378 size 160 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_crypto_lock_init(_DWORD *a1)
{
  int v2; // w1
  bool v3; // cf

  sprd_mutex_lock(0);
  sprd_ce_prepare();
  v2 = *a1 - 7;
  v3 = *a1 != 7;
  dword_94067AC8 = 1;
  if ( v2 == 1 || !v3 )
    sprd_sec_hw_init();
  sprd_mutex_unlock(0);
  return 0;
}

/* ===== sprd_crypto_lock_deinit @ 0x94037418 size 152 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_crypto_lock_deinit(int *a1)
{
  int v2; // w1

  sprd_mutex_lock(0);
  v2 = *a1;
  dword_94067AC8 = -1;
  if ( (unsigned int)(v2 - 7) <= 1 )
    sprd_sec_hw_deinit();
  sprd_crypto_unlock();
  sprd_mutex_unlock(0);
  return 0;
}

/* ===== log2_floor @ 0x940374B0 size 68 ===== */
__int64 __fastcall log2_floor(unsigned __int64 a1)
{
  unsigned int v1; // w2
  unsigned __int64 v2; // x0
  int i; // w1

  v1 = 0;
  if ( a1 != 1 )
  {
    v1 = 1;
    v2 = a1 >> 1;
    for ( i = 2; v2 != 1; i = (unsigned __int8)(i + 1) )
    {
      v1 = i;
      v2 >>= 1;
    }
  }
  return v1;
}

/* ===== crypto_buf_pool_init @ 0x940374F4 size 272 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 crypto_buf_pool_init()
{
  unsigned int v0; // w0

  v0 = log2_floor(0x40u);
  if ( (unsigned int)sprd_dma_alloc("crypto buffer", 0x80000, &qword_94067AE0, v0, 0, 0) == 0 )
    qword_94067980 = sprd_mutex_create();
  return 4294901760LL;
}

/* ===== sprd_crypto_init @ 0x94037604 size 252 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 sprd_crypto_init()
{
  __int64 v0; // x0
  __int64 v1; // x0
  __int64 v2; // x0
  __int64 result; // x0
  const void *v4; // x0
  const void *v5; // x0
  const void *v6; // x0

  crypto_buf_pool_init();
  sprd_ce_init();
  sprd_ce_set_pka_cb((void *)0xFFFFFFFFE0016D20LL);
  v0 = sprd_queue_init((_QWORD *)0xFFFFFFFFE0061270LL);
  qword_94067AD0 = sprd_mutex_create(v0);
  v5 = (const void *)get_current_thread(0);
  sprd_log(3, "%p: %s: %s: mutex init s_crypto_mutex FAILED!\n", v5, "SPRD_CE", "sprd_crypto_init");
  sprd_ce_set_ce_cb((void *)0xFFFFFFFFE0016C28LL);
  v1 = sprd_queue_init((_QWORD *)0xFFFFFFFFE0061298LL);
  v2 = sprd_mutex_create(v1);
  qword_94067AD8 = v2;
  if ( v2 == 0 )
  {
    v6 = (const void *)get_current_thread(0);
    v2 = sprd_log(3, "%p: %s: %s: mutex init s_crypto_mutex_pka FAILED!\n", v6, "SPRD_CE", "sprd_crypto_init");
  }
  result = sprd_mutex_create(v2);
  qword_94067978 = result;
  if ( result == 0 )
  {
    v4 = (const void *)get_current_thread(0);
    return sprd_log(3, "%p: %s: %s: mutex init s_crypto_count_mutex FAILED!\n", v4, "SPRD_CE", "sprd_crypto_init");
  }
  return result;
}

/* ===== ce_desc_nop @ 0x94037700 size 8 ===== */
__int64 ce_desc_nop()
{
  return 0xFFFFFFFFLL;
}

/* ===== ce_desc_alg @ 0x94037708 size 40 ===== */
__int64 __fastcall ce_desc_alg(char a1, char a2, char a3, int a4)
{
  return a4 & 0x1FFFF | 0xB0000000 | ((a2 & 0x1F) << 18) | ((a1 & 0xF) << 23) | ((a3 & 1) << 17);
}

/* ===== ce_desc_alg2 @ 0x94037730 size 40 ===== */
__int64 __fastcall ce_desc_alg2(char a1, char a2, char a3, int a4)
{
  return a4 & 0x1FFFF | 0xB8000000 | ((a2 & 0x1F) << 18) | ((a1 & 0xF) << 23) | ((a3 & 1) << 17);
}

/* ===== ce_desc_cipher @ 0x94037758 size 24 ===== */
__int64 __fastcall ce_desc_cipher(char a1, int a2)
{
  return a2 & 0x3FFFF | 0x28000000 | ((unsigned __int8)(a1 & 0x1F) << 18);
}

/* ===== ce_desc_hash_init @ 0x94037770 size 28 ===== */
__int64 __fastcall ce_desc_hash_init(char a1, char a2)
{
  return ((a2 & 0x1F) << 18) | 0xF0020805 | ((a1 & 0xF) << 23);
}

/* ===== ce_desc_hash_data @ 0x9403778C size 20 ===== */
__int64 __fastcall ce_desc_hash_data(char a1, int a2)
{
  return ((a2 & 0x1FFFF) << 6) | 0xF8000000 | ((a1 & 0xF) << 23);
}

/* ===== ce_desc_hash_final @ 0x940377A0 size 36 ===== */
__int64 __fastcall ce_desc_hash_final(char a1, char a2, char a3, char a4)
{
  return ((a4 & 0x1F) << 6) | 0xF8000001 | ((a3 & 0x1F) << 12) | ((a2 & 0x1F) << 18) | ((a1 & 0xF) << 23);
}

/* ===== ce_desc_hash_final2 @ 0x940377C4 size 44 ===== */
__int64 __fastcall ce_desc_hash_final2(char a1, char a2, char a3, char a4)
{
  return ((a4 & 0x1F) << 6) | 0xF8000002 | ((a3 & 0x1F) << 12) | ((a2 & 0x1F) << 18) | ((a1 & 0xF) << 23);
}

/* ===== ce_desc_cipher2 @ 0x940377F0 size 40 ===== */
__int64 __fastcall ce_desc_cipher2(char a1, char a2, char a3, char a4)
{
  return ((a4 & 0x1F) << 6)
       | 0x58000000
       | ((a3 & 0x1F) << 12)
       | ((a2 & 0x1F) << 18)
       | ((unsigned __int8)(a1 & 0xF) << 23);
}

/* ===== ce_desc_rng @ 0x94037818 size 20 ===== */
__int64 __fastcall ce_desc_rng(char a1, char a2)
{
  return ((a2 & 0x1F) << 18) | 0x8000000 | ((unsigned __int8)(a1 & 0xF) << 23);
}

/* ===== ce_clear_desc_flags @ 0x9403782C size 36 ===== */
__int64 __fastcall ce_clear_desc_flags(__int64 result, unsigned int a2)
{
  __int64 i; // x2

  for ( i = 0; a2 > (unsigned int)i; ++i )
    *(_DWORD *)(result + 4 * i) &= ~0x80000000;
  return result;
}

/* ===== sha256_csum_wd @ 0x94037850 size 240 ===== */
__int64 __fastcall sha256_csum_wd(__int64 a1, unsigned int a2, __int64 a3)
{
  __int64 v6; // x0
  __int64 v7; // x0
  __int64 result; // x0
  __int64 v9; // x2
  __int64 v10; // x2
  __int64 v11; // x2
  __int64 v12; // [xsp+38h] [xbp+38h]
  __int64 v13; // [xsp+38h] [xbp+38h]
  __int64 v14; // [xsp+38h] [xbp+38h]
  _BYTE v15[352]; // [xsp+40h] [xbp+40h] BYREF

  v6 = sprd_hash_init(33554436, v15);
  if ( (_DWORD)v6 != 0 )
  {
    v13 = (unsigned int)v6;
    v10 = get_current_thread(v6);
    return sprd_log(3, "%p: %s: %s: sprd_hash_init return [0x%x]\n", v10, "SPRD_CE", "sha256_csum_wd", v13);
  }
  else
  {
    v7 = sprd_hash_update(v15, a1, a2);
    if ( (_DWORD)v7 != 0 )
    {
      v12 = (unsigned int)v7;
      v9 = get_current_thread(v7);
      return sprd_log(3, "%p: %s: %s: sprd_hash_process return [0x%x]\n", v9, "SPRD_CE", "sha256_csum_wd", v12);
    }
    else
    {
      result = sprd_hash_final(v15, a3);
      if ( (_DWORD)result != 0 )
      {
        v14 = (unsigned int)result;
        v11 = get_current_thread(result);
        return sprd_log(3, "%p: %s: %s: sprd_hash_final return [0x%x]\n", v11, "SPRD_CE", "sha256_csum_wd", v14);
      }
    }
  }
  return result;
}

/* ===== RSA_PubDec @ 0x94037940 size 220 ===== */
__int64 __fastcall RSA_PubDec(__int64 a1, __int64 a2, int a3, __int64 a4, __int64 a5)
{
  __int64 v5; // x0
  __int64 result; // x0
  const void *v7; // x0
  const void *v8; // x0
  int v9; // [xsp+18h] [xbp+18h]
  _QWORD v10[4]; // [xsp+20h] [xbp+20h] BYREF
  int v11; // [xsp+44h] [xbp+44h] BYREF
  _QWORD v12[2]; // [xsp+48h] [xbp+48h] BYREF
  int v13; // [xsp+58h] [xbp+58h]
  int v14; // [xsp+5Ch] [xbp+5Ch]
  _QWORD v15[4]; // [xsp+60h] [xbp+60h]

  LODWORD(v15[0]) = 20;
  v12[0] = a2;
  qmemcpy(v10, v15, sizeof(v10));
  v12[1] = a1;
  v13 = a3 >> 3;
  v14 = 4;
  v5 = sprd_rsa_verify(v12, a5, 0, a4, (unsigned int)(a3 >> 3), v10, &v11);
  if ( (_DWORD)v5 != 0 )
  {
    v9 = v5;
    v7 = (const void *)get_current_thread(v5);
    sprd_log(3, "%p: %s: %s: sprd_rsa_verify fail(%08x)\n", v7, "SPRD_CE", "RSA_PubDec", v9);
    return 0xFFFFFFFFLL;
  }
  else
  {
    result = (unsigned int)v11;
    if ( v11 <= 0 )
    {
      v8 = (const void *)get_current_thread((unsigned int)v11);
      sprd_log(3, "%p: %s: %s: sprd_rsa_verify result(%08x)\n", v8, "SPRD_CE", "RSA_PubDec", v11);
      return 0xFFFFFFFFLL;
    }
  }
  return result;
}

/* ===== sprd_socid_get @ 0x94037A1C size 472 ===== */
__int64 __fastcall sprd_socid_get(__int64 a1)
{
  __int64 v2; // x0
  __int64 v3; // x2
  __int64 result; // x0
  __int64 v5; // x0
  __int64 v6; // x2
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 v9; // x2
  __int64 v10; // x2
  __int64 v11; // x5
  __int64 v12; // x2
  __int64 v13; // [xsp+48h] [xbp+48h]
  __int64 v14; // [xsp+48h] [xbp+48h]
  __int64 v15; // [xsp+48h] [xbp+48h]
  __int64 v16; // [xsp+48h] [xbp+48h]
  __int64 v17; // [xsp+48h] [xbp+48h]
  _BYTE v18[32]; // [xsp+58h] [xbp+58h] BYREF
  char v19[40]; // [xsp+78h] [xbp+78h] BYREF
  _BYTE v20[32]; // [xsp+A0h] [xbp+A0h] BYREF
  _QWORD v21[2]; // [xsp+C0h] [xbp+C0h] BYREF
  _BYTE v22[352]; // [xsp+D0h] [xbp+D0h] BYREF
  _BYTE v23[352]; // [xsp+230h] [xbp+230h] BYREF

  memset(v19, 0, 36);
  memset(v20, 0, sizeof(v20));
  v21[0] = 0;
  v21[1] = 0;
  efuse_read_ns_blocks(v18);
  ce_clear_desc_flags((__int64)v18, 8u);
  memcpy(v20, v18, 32);
  v19[0] = 1;
  strcpy(&v19[1], "I");
  v19[35] = 0x80;
  v2 = sprd_cmac_init(8, 0, 32, v22);
  if ( (_DWORD)v2 != 0 )
  {
    v13 = (unsigned int)v2;
    v3 = get_current_thread(v2);
    sprd_log(3, "%p: %s: %s: aes cmac init FAILED [%d]\n", v3, "SPRD_CE", "sprd_socid_get", v13);
    return 0xFFFFFFFFLL;
  }
  v5 = sprd_cmac_update(v22, v19, 36);
  if ( (_DWORD)v5 != 0 )
  {
    v14 = (unsigned int)v5;
    v6 = get_current_thread(v5);
    sprd_log(3, "%p: %s: %s: aes cmac update FAILED [%d]\n", v6, "SPRD_CE", "sprd_socid_get", v14);
    return 0xFFFFFFFFLL;
  }
  v7 = sprd_cmac_final(v22, v21);
  if ( (_DWORD)v7 != 0 )
  {
    v16 = (unsigned int)v7;
    v10 = get_current_thread(v7);
    sprd_log(3, "%p: %s: %s: aes cmac final FAILED [%d]\n", v10, "SPRD_CE", "sprd_socid_get", v16);
    return 0xFFFFFFFFLL;
  }
  v8 = sprd_hash_init(33554436, v23);
  if ( (_DWORD)v8 != 0 )
  {
    v15 = (unsigned int)v8;
    v9 = get_current_thread(v8);
    sprd_log(3, "%p: %s: %s: sha256 init FAILED [%d]\n", v9, "SPRD_CE", "sprd_socid_get", v15);
    return 0xFFFFFFFFLL;
  }
  result = sprd_hash_update(v23, v20, 48);
  v11 = (unsigned int)result;
  if ( (_DWORD)result != 0 || (v11 = (unsigned int)sprd_hash_final(v23, a1), result = 0, (_DWORD)v11 != 0) )
  {
    v17 = v11;
    v12 = get_current_thread(result);
    sprd_log(3, "%p: %s: %s: sha256 update FAILED [%d]\n", v12, "SPRD_CE", "sprd_socid_get", v17);
    return 0xFFFFFFFFLL;
  }
  return result;
}

/* ===== sprd_huk_derive @ 0x94037BF4 size 352 ===== */
__int64 __fastcall sprd_huk_derive(__int64 a1, unsigned int a2, __int64 a3, unsigned int a4)
{
  char v9[48]; // [xsp+40h] [xbp+40h] BYREF
  _BYTE v10[352]; // [xsp+70h] [xbp+70h] BYREF

  strcpy(v9, "@ABCDEFGHIJKLMNO");
  memset(&v9[17], 0, 31);
  if ( (unsigned int)sprd_aes_init(7, 0, v10, 0, 0, 16, v9, 16) != 0
    || (unsigned int)sprd_aes_process(v10, a1, &v9[16], a2) != 0
    || (unsigned int)sprd_aes_final(v10, 0, 0, 0, 0, 0) != 0 )
  {
    return 4294901775LL;
  }
  memcpy(a3, &v9[16], a4);
  return 0;
}

/* ===== sprd_aes_init @ 0x94037D54 size 524 ===== */
__int64 __fastcall sprd_aes_init(
        int a1,
        int a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        unsigned int a6,
        __int64 a7,
        unsigned int a8)
{
  __int64 v9; // x0
  __int64 v17; // x0
  __int64 v18; // x0
  unsigned int v19; // w1
  const void *v21; // x0
  __int64 v22; // x1
  __int64 v23; // x0
  __int64 v24; // x2
  __int64 v25; // x2
  __int64 v26; // x2

  v9 = (unsigned int)(a1 - 7);
  if ( (unsigned int)v9 > 1 && (a4 == 0 || (_DWORD)(v9 = a6 & 0xFFFFFFF7) != 16 && a6 != 32) )
  {
    v24 = get_current_thread(v9);
    sprd_log(3, "%p: %s: %s: Bad AES key1!\n", v24, "SPRD_CE", "sprd_aes_init");
    return (unsigned int)-65529;
  }
  if ( a1 == 3 && a5 == 0 )
  {
    v25 = get_current_thread(v9);
    sprd_log(3, "%p: %s: %s: Bad AES key2!\n", v25, "SPRD_CE", "sprd_aes_init");
    return (unsigned int)-65529;
  }
  if ( (a1 & 0xFFFFFFFB) != 0 && a1 != 8 && (a7 == 0 || a8 != 16) )
  {
    v26 = get_current_thread(v9);
    sprd_log(3, "%p: %s: %s: Bad AES iv!\n", v26, "SPRD_CE", "sprd_aes_init");
    return (unsigned int)-65529;
  }
  memset(a3, 0, 352);
  v17 = memalign(128, 64);
  *(_QWORD *)(a3 + 144) = v17;
  if ( v17 == 0 )
    return (unsigned int)-65526;
  dcache_clean(v17, 128);
  *(_DWORD *)a3 = a1;
  *(_DWORD *)(a3 + 16) = a2;
  if ( a4 != 0 )
    memcpy(a3 + 28, a4, a6);
  *(_DWORD *)(a3 + 60) = a6;
  if ( a5 != 0 )
  {
    memcpy(a3 + 64, a5, a6);
    *(_DWORD *)(a3 + 96) = a6;
  }
  if ( a7 != 0 )
  {
    memcpy(a3 + 100, a7, a8);
    *(_DWORD *)(a3 + 116) = a8;
  }
  v18 = sprd_crypto_lock_init((_DWORD *)a3);
  v19 = 0;
  if ( (_DWORD)v18 == 0 )
    return v19;
  v21 = (const void *)get_current_thread(v18);
  sprd_log(3, "%p: %s: %s: FAILED!\n", v21, "SPRD_CE", "sprd_aes_init");
  v23 = *(_QWORD *)(a3 + 144);
  if ( v23 != 0 )
  {
    free(v23, v22);
    *(_QWORD *)(a3 + 144) = 0;
  }
  return 4294901760LL;
}

/* ===== sprd_aes_process_internal @ 0x94037F60 size 568 ===== */
__int64 __fastcall sprd_aes_process_internal(__int64 a1, __int64 a2, int a3, __int64 a4)
{
  int v8; // w25
  __int64 v9; // x24
  __int64 v10; // x0
  const void *v11; // x19
  unsigned int v12; // w21
  __int64 v13; // x23
  __int64 v14; // x0
  const void *v15; // x0
  unsigned int v16; // w19
  int v17; // w0
  const void *v18; // x2
  __int64 v19; // x1
  unsigned int v20; // w28
  __int64 result; // x0
  const void *v22; // x0
  __int64 v23; // x1
  __int64 v24; // x0
  const void *v25; // x0
  unsigned int v26; // [xsp+64h] [xbp+64h] BYREF
  const void *v27; // [xsp+68h] [xbp+68h] BYREF

  v27 = nullptr;
  v8 = *(_DWORD *)(a1 + 8);
  v9 = sprd_semaphore_create(0);
  if ( v9 == 0 )
    return 4294901770LL;
  v10 = sprd_crypto_malloc_buf(a1, 0x40u, &v27, (int *)&v26);
  v11 = v27;
  if ( v27 != nullptr && (v10 = v26, v26 > 0x3F) )
  {
    v12 = (v26 - 1 + a3) / v26;
    if ( v12 == 0 )
    {
LABEL_13:
      sprd_semaphore_destroy(v9);
      result = (__int64)v27;
      if ( v27 != nullptr )
      {
        sprd_crypto_free_buf((__int64)v27);
        return 0;
      }
      return result;
    }
    v13 = a2;
    while ( 1 )
    {
      v15 = v11;
      if ( v12 == 1 )
      {
        v16 = a3 + a2 - v13;
        memcpy(v15, v13, v16);
        v17 = (unsigned __int8)v8;
      }
      else
      {
        v16 = v26;
        memcpy(v15, v13, v26);
        v17 = 0;
      }
      v18 = v27;
      v19 = v26;
      *(_DWORD *)(a1 + 8) = v17;
      *(_QWORD *)(a1 + 296) = v18;
      *(_QWORD *)(a1 + 312) = v18;
      *(_DWORD *)(a1 + 304) = v16;
      *(_DWORD *)(a1 + 320) = v16;
      *(_QWORD *)(a1 + 344) = v9;
      dcache_clean(v18, v19);
      v20 = sprd_crypto_work((int *)a1);
      if ( v20 != 0 )
        break;
      sprd_semaphore_wait(v9);
      if ( a4 != 0 )
      {
        dcache_invalidate(v27, v26);
        v14 = a4;
        a4 += v16;
        v13 += v16;
        memcpy(v14, v27, v16);
        if ( --v12 == 0 )
          goto LABEL_13;
      }
      else
      {
        --v12;
        v13 += v16;
        if ( v12 == 0 )
          goto LABEL_13;
      }
      v11 = v27;
    }
    v25 = (const void *)get_current_thread(v9);
    sprd_log(3, "%p: %s: %s: sprd_crypto_process return 0x%x\n", v25, "SPRD_CE", "sprd_aes_process_internal", v20);
  }
  else
  {
    v22 = (const void *)get_current_thread(v10);
    v20 = -65526;
    sprd_log(3, "%p: %s: %s: buf = %p, buf_len is %d!\n", v22, "SPRD_CE", "sprd_aes_process_internal", v27, v26);
  }
  if ( v27 != nullptr )
    sprd_crypto_free_buf((__int64)v27);
  sprd_semaphore_destroy(v9);
  v24 = *(_QWORD *)(a1 + 144);
  if ( v24 != 0 )
  {
    free(v24, v23);
    *(_QWORD *)(a1 + 144) = 0;
  }
  sprd_crypto_lock_deinit((int *)a1);
  return v20;
}

/* ===== sprd_aes_process @ 0x94038198 size 68 ===== */
__int64 __fastcall sprd_aes_process(__int64 a1, __int64 a2, __int64 a3, int a4)
{
  if ( a2 == 0 || a3 == 0 || a4 == 0 || (a4 & 0xF) != 0 )
    return 4294901767LL;
  *(_DWORD *)(a1 + 8) = 0;
  return sprd_aes_process_internal(a1, a2, a4, a3);
}

/* ===== sprd_aes_final @ 0x940381DC size 232 ===== */
__int64 __fastcall sprd_aes_final(__int64 a1, __int64 a2, unsigned int a3, __int64 a4, unsigned int *a5, unsigned int a6)
{
  unsigned int v9; // w22
  __int64 v10; // x0
  __int64 v12; // x0
  const void *v13; // x0

  if ( a2 != 0 && (a4 == 0 || a5 == nullptr || *a5 < a3) || (a3 & 0xF) != 0 || a6 > 2 )
    return 4294901767LL;
  if ( a2 == 0 || a3 == 0 )
    goto LABEL_9;
  *(_DWORD *)(a1 + 8) = 1;
  v12 = sprd_aes_process_internal(a1, a2, a3, a4);
  v9 = v12;
  if ( (_DWORD)v12 != 0 )
  {
    v13 = (const void *)get_current_thread(v12);
    sprd_log(3, "%p: %s: %s: sprd_aes_process_internal FAILED[0x%x]\n", v13, "SPRD_CE", "sprd_aes_final", v9);
    goto LABEL_10;
  }
  if ( a5 != nullptr )
    *a5 = a3;
  else
LABEL_9:
    v9 = 0;
LABEL_10:
  v10 = *(_QWORD *)(a1 + 144);
  if ( v10 != 0 )
  {
    free(v10, a2);
    *(_QWORD *)(a1 + 144) = 0;
  }
  sprd_crypto_lock_deinit((int *)a1);
  return v9;
}

/* ===== sprd_hash_init @ 0x940382C4 size 156 ===== */
__int64 __fastcall sprd_hash_init(int a1, __int64 a2)
{
  __int64 v4; // x0
  __int64 v5; // x0
  unsigned int v6; // w1
  const void *v8; // x0

  memset(a2, 0, 352);
  v4 = memalign(128, 64);
  *(_QWORD *)(a2 + 152) = v4;
  if ( v4 != 0 )
  {
    dcache_clean(v4, 128);
    *(_DWORD *)a2 = a1;
    v5 = sprd_crypto_lock_init((_DWORD *)a2);
    v6 = 0;
    if ( (_DWORD)v5 != 0 )
    {
      v8 = (const void *)get_current_thread(v5);
      sprd_log(3, "%p: %s: %s: FAILED!\n", v8, "SPRD_CE", "sprd_hash_init");
      return (unsigned int)-65536;
    }
  }
  else
  {
    return (unsigned int)-65526;
  }
  return v6;
}

/* ===== sprd_hash_process @ 0x94038360 size 940 ===== */
__int64 __fastcall sprd_hash_process(__int64 a1, __int64 a2, unsigned int a3, __int64 a4, unsigned int a5)
{
  __int64 v6; // x26
  int v10; // w23
  __int64 v11; // x21
  __int64 v12; // x0
  unsigned int v13; // w1
  const void *v14; // x0
  unsigned int v15; // w20
  __int64 v16; // x1
  __int64 v17; // x0
  __int64 v19; // x2
  int v20; // w22
  __int64 v21; // x24
  unsigned int v22; // w28
  unsigned int v23; // w22
  unsigned int v24; // w20
  __int64 v25; // x1
  char *v26; // x2
  __int64 v27; // x1
  __int64 v28; // x0
  __int64 v29; // x2
  int v30; // w3
  __int64 v31; // x1
  char *v32; // x0
  __int64 v33; // x1
  __int64 v34; // x24
  char *v35; // x0
  __int64 v36; // x0
  __int64 v37; // x2
  unsigned int v38; // [xsp+6Ch] [xbp+6Ch]
  unsigned int v39; // [xsp+74h] [xbp+74h] BYREF
  char *v40; // [xsp+78h] [xbp+78h] BYREF

  v6 = a3;
  v40 = nullptr;
  v10 = *(_DWORD *)(a1 + 8);
  v11 = sprd_semaphore_create(0);
  if ( v11 == 0 )
    return 4294901770LL;
  sprd_crypto_malloc_buf(a1, 0x80u, &v40, (int *)&v39);
  v12 = (__int64)v40;
  if ( v40 != nullptr )
  {
    v13 = v39;
    if ( v39 > 0x7F )
    {
      *(_QWORD *)(a1 + 344) = v11;
      v19 = *(unsigned int *)(a1 + 16);
      if ( (_BYTE)v10 != 0 )
      {
        memcpy(v12, a1 + 20, v19);
        *(_DWORD *)(a1 + 320) = a5;
        v30 = *(_DWORD *)(a1 + 16);
        v31 = v39;
        v32 = v40;
        *(_QWORD *)(a1 + 296) = v40;
        *(_DWORD *)(a1 + 304) = v30;
        *(_QWORD *)(a1 + 312) = v32;
        dcache_clean(v32, v31);
        v28 = sprd_crypto_work((int *)a1);
        v15 = v28;
        if ( (_DWORD)v28 != 0 )
        {
LABEL_27:
          v29 = get_current_thread(v28);
          sprd_log(3, "%p: %s: %s: sprd_crypt_process return 0x%x\n", v29, "SPRD_CE", "sprd_hash_process", v15);
          goto LABEL_5;
        }
        sprd_semaphore_wait(v11);
        sprd_semaphore_destroy(v11);
        if ( (unsigned __int8)v10 == 1 )
        {
          dcache_invalidate(v40, v39);
          memcpy(a4, v40, a5);
        }
LABEL_31:
        if ( v40 != nullptr )
        {
          sprd_crypto_free_buf((__int64)v40);
          return 0;
        }
        return 0;
      }
      v20 = v6 + v19;
      if ( (_DWORD)v6 + (_DWORD)v19 == 0 )
      {
LABEL_12:
        sprd_crypto_free_buf(v12);
LABEL_13:
        sprd_semaphore_destroy(v11);
        return 0;
      }
      if ( (unsigned int)(v20 - 1) <= 0x7E )
      {
        memcpy(a1 + (unsigned int)v19 + 20, a2, (unsigned int)v6);
        *(_DWORD *)(a1 + 16) = v20;
        v12 = (__int64)v40;
        if ( v40 == nullptr )
          goto LABEL_13;
        goto LABEL_12;
      }
      v21 = a2;
      if ( (_DWORD)v19 != 0 )
      {
        v20 -= 128;
        memcpy(v12, a1 + 20, v19);
        memcpy(&v40[*(unsigned int *)(a1 + 16)], a2, (unsigned int)(128 - *(_DWORD *)(a1 + 16)));
        v33 = v39;
        v34 = *(unsigned int *)(a1 + 16);
        v35 = v40;
        *(_QWORD *)(a1 + 296) = v40;
        *(_DWORD *)(a1 + 304) = 128;
        *(_QWORD *)(a1 + 312) = v35;
        v21 = a2 + 128 - v34;
        *(_DWORD *)(a1 + 16) = 0;
        *(_DWORD *)(a1 + 320) = a5;
        dcache_clean(v35, v33);
        v36 = sprd_crypto_work((int *)a1);
        v15 = v36;
        if ( (_DWORD)v36 != 0 )
        {
          v37 = get_current_thread(v36);
          sprd_log(3, "%p: %s: %s: sprd_crypto_process return 0x%x\n", v37, "SPRD_CE", "sprd_hash_process", v15);
          goto LABEL_5;
        }
        sprd_semaphore_wait(v11);
        if ( v20 == 0 )
        {
LABEL_36:
          sprd_semaphore_destroy(v11);
          goto LABEL_31;
        }
        v13 = v39;
      }
      v38 = v20 & 0x7F;
      v22 = v20 - v38;
      v23 = (v20 - v38) / v13;
      if ( v22 % v13 != 0 )
        ++v23;
      if ( v23 != 0 )
      {
        while ( 1 )
        {
          v24 = v13 > v22 ? v22 : v13;
          v25 = v21;
          v21 += v24;
          v22 -= v24;
          memcpy(v40, v25, v24);
          *(_DWORD *)(a1 + 304) = v24;
          v26 = v40;
          v27 = v39;
          *(_QWORD *)(a1 + 296) = v40;
          *(_DWORD *)(a1 + 8) = 0;
          *(_QWORD *)(a1 + 312) = v26;
          *(_DWORD *)(a1 + 320) = a5;
          dcache_clean(v26, v27);
          v15 = sprd_crypto_work((int *)a1);
          v28 = v11;
          if ( v15 != 0 )
            goto LABEL_27;
          sprd_semaphore_wait(v11);
          if ( --v23 == 0 )
            break;
          v13 = v39;
        }
      }
      if ( v38 != 0 )
      {
        memcpy(a1 + 20, a2 + v6 - v38, v38);
        *(_DWORD *)(a1 + 16) = v38;
      }
      goto LABEL_36;
    }
  }
  v14 = (const void *)get_current_thread(v40);
  v15 = -65526;
  sprd_log(3, "%p: %s: %s: buf = %p, buf_len is %d!\n", v14, "SPRD_CE", "sprd_hash_process", v40, v39);
LABEL_5:
  if ( v40 != nullptr )
    sprd_crypto_free_buf((__int64)v40);
  sprd_semaphore_destroy(v11);
  v17 = *(_QWORD *)(a1 + 152);
  if ( v17 != 0 )
  {
    free(v17, v16);
    *(_QWORD *)(a1 + 152) = 0;
  }
  sprd_crypto_lock_deinit((int *)a1);
  return v15;
}

/* ===== sprd_hash_update @ 0x9403870C size 16 ===== */
__int64 __fastcall sprd_hash_update(__int64 a1, __int64 a2, unsigned int a3)
{
  *(_DWORD *)(a1 + 8) = 0;
  return sprd_hash_process(a1, a2, a3, 0, 0);
}

/* ===== sprd_hash_final @ 0x9403871C size 336 ===== */
__int64 __fastcall sprd_hash_final(__int64 a1, __int64 a2)
{
  int v3; // w0
  unsigned int v4; // w4
  __int64 v5; // x0
  __int64 v6; // x1
  unsigned int v7; // w20
  const void *v8; // x0
  unsigned int v9; // w4
  __int64 v10; // x0

  v3 = *(_DWORD *)a1;
  *(_DWORD *)(a1 + 8) = 1;
  if ( v3 == 33554433 )
  {
    v9 = 16;
    goto LABEL_14;
  }
  if ( v3 == 33554434 )
  {
    v9 = 20;
    goto LABEL_14;
  }
  if ( v3 == 33554435 )
    goto LABEL_19;
  if ( v3 == 33554436 )
  {
    v9 = 32;
  }
  else if ( v3 == 33554437 )
  {
    v9 = 48;
  }
  else
  {
    if ( v3 != 33554438 )
    {
      if ( v3 != 33554439 )
      {
        if ( v3 == 33554440 )
          v4 = 32;
        else
          v4 = 0;
        v5 = sprd_hash_process(a1, 0, 0, a2, v4);
        v7 = v5;
        if ( (_DWORD)v5 == 0 )
          goto LABEL_15;
        goto LABEL_12;
      }
LABEL_19:
      v9 = 28;
      goto LABEL_14;
    }
    v9 = 64;
  }
LABEL_14:
  v5 = sprd_hash_process(a1, 0, 0, a2, v9);
  v7 = v5;
  if ( (_DWORD)v5 != 0 )
  {
LABEL_12:
    v8 = (const void *)get_current_thread(v5);
    sprd_log(3, "%p: %s: %s: sprd_crypto_hash_process FAILED!\n", v8, "SPRD_CE", "sprd_hash_final");
  }
LABEL_15:
  v10 = *(_QWORD *)(a1 + 152);
  if ( v10 != 0 )
  {
    free(v10, v6);
    *(_QWORD *)(a1 + 152) = 0;
  }
  sprd_crypto_lock_deinit((int *)a1);
  return v7;
}

/* ===== sprd_cmac_init @ 0x9403886C size 36 ===== */
__int64 __fastcall sprd_cmac_init(int a1, __int64 a2, unsigned int a3, __int64 a4)
{
  return sprd_aes_init(a1, 0, a4, a2, 0, a3, 0, 0);
}

/* ===== sprd_cmac_process_internal @ 0x94038890 size 660 ===== */
__int64 __fastcall sprd_cmac_process_internal(__int64 a1, __int64 a2, int a3, __int64 a4, unsigned int a5)
{
  int v10; // w24
  __int64 v11; // x21
  __int64 v12; // x0
  const void *v13; // x2
  __int64 v14; // x1
  int v15; // w28
  unsigned int v16; // w20
  __int64 v17; // x22
  unsigned int v18; // w24
  int v19; // w0
  const void *v20; // x2
  __int64 v21; // x1
  unsigned int v22; // w1
  __int64 v23; // x0
  const void *v25; // x0
  unsigned int v26; // w20
  const void *v27; // x0
  const void *v28; // x0
  int v29; // [xsp+6Ch] [xbp+6Ch]
  unsigned int v30; // [xsp+74h] [xbp+74h] BYREF
  const void *v31; // [xsp+78h] [xbp+78h] BYREF

  v31 = nullptr;
  v10 = *(_DWORD *)(a1 + 8);
  v11 = sprd_semaphore_create(0);
  if ( v11 == 0 )
    return 4294901770LL;
  v12 = sprd_crypto_malloc_buf(a1, 0x40u, &v31, (int *)&v30);
  v13 = v31;
  if ( v31 != nullptr )
  {
    v14 = v30;
    if ( v30 > 0x3F )
    {
      v15 = (unsigned __int8)v10;
      v16 = (v30 - 1 + a3) / v30;
      if ( v16 != 0 )
      {
        v17 = a2;
        v29 = (unsigned __int8)v10;
        while ( 1 )
        {
          if ( v16 == 1 )
          {
            v18 = a3 + a2 - v17;
            memcpy(v13, v17, v18);
            v19 = v29;
          }
          else
          {
            v18 = v30;
            memcpy(v13, v17, v30);
            v19 = 0;
          }
          v20 = v31;
          v17 += v18;
          v21 = v30;
          *(_DWORD *)(a1 + 8) = v19;
          *(_QWORD *)(a1 + 296) = v20;
          *(_QWORD *)(a1 + 312) = v20;
          *(_QWORD *)(a1 + 328) = v20;
          *(_DWORD *)(a1 + 304) = v18;
          *(_DWORD *)(a1 + 320) = 0;
          *(_DWORD *)(a1 + 336) = a5;
          *(_QWORD *)(a1 + 344) = v11;
          dcache_clean(v20, v21);
          v22 = sprd_crypto_work((int *)a1);
          v23 = v11;
          if ( v22 != 0 )
            break;
          sprd_semaphore_wait(v11);
          if ( --v16 == 0 )
            goto LABEL_11;
          v13 = v31;
        }
        v26 = v22;
        goto LABEL_25;
      }
      if ( (unsigned __int8)v10 == 1 )
      {
        v27 = v31;
        *(_QWORD *)(a1 + 296) = v31;
        *(_QWORD *)(a1 + 312) = v13;
        *(_QWORD *)(a1 + 328) = v13;
        *(_DWORD *)(a1 + 8) = 1;
        *(_DWORD *)(a1 + 304) = 0;
        *(_DWORD *)(a1 + 320) = 0;
        *(_DWORD *)(a1 + 336) = a5;
        *(_QWORD *)(a1 + 344) = v11;
        dcache_clean(v27, v14);
        v23 = sprd_crypto_work((int *)a1);
        v26 = v23;
        if ( (_DWORD)v23 != 0 )
        {
LABEL_25:
          v28 = (const void *)get_current_thread(v23);
          sprd_log(
            3,
            "%p: %s: %s: sprd_crypto_process return 0x%x\n",
            v28,
            "SPRD_CE",
            "sprd_cmac_process_internal",
            v26);
          goto LABEL_18;
        }
        sprd_semaphore_wait(v11);
LABEL_11:
        if ( a4 != 0 && v15 == 1 )
        {
          dcache_invalidate(v31, v30);
          memcpy(a4, v31, a5);
        }
      }
      sprd_semaphore_destroy(v11);
      if ( v31 != nullptr )
        sprd_crypto_free_buf((__int64)v31);
      return 0;
    }
  }
  v25 = (const void *)get_current_thread(v12);
  v26 = -65526;
  sprd_log(3, "%p: %s: %s: buf = %p, buf_len is %d!\n", v25, "SPRD_CE", "sprd_cmac_process_internal", v31, v30);
LABEL_18:
  if ( v31 != nullptr )
    sprd_crypto_free_buf((__int64)v31);
  sprd_semaphore_destroy(v11);
  sprd_aes_final(a1, 0, 0, 0, nullptr, 0);
  return v26;
}

/* ===== sprd_cmac_update @ 0x94038B24 size 400 ===== */
__int64 __fastcall sprd_cmac_update(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned int v3; // w4
  int v6; // w20
  int v7; // w22
  __int64 v8; // x0
  unsigned int v9; // w22
  int v10; // w0
  unsigned int v11; // w20
  unsigned int v12; // w22
  __int64 v13; // x21
  __int64 v14; // x2
  __int64 result; // x0
  unsigned int v16; // w19
  const void *v17; // x0
  const void *v18; // x0

  if ( (_DWORD)a3 == 0 )
    return 0;
  v3 = *(_DWORD *)(a1 + 120);
  *(_DWORD *)(a1 + 8) = 0;
  v6 = a3 + v3;
  v7 = a3;
  if ( (unsigned int)a3 + v3 <= 0x10 )
  {
    memcpy(a1 + v3 + 124, a2, a3);
    *(_DWORD *)(a1 + 120) += v7;
    return 0;
  }
  memcpy(a1 + v3 + 124, a2, 16 - v3);
  v8 = sprd_cmac_process_internal(a1, a1 + 124, 16, 0, 0);
  v9 = v8;
  if ( (_DWORD)v8 != 0 )
  {
    v18 = (const void *)get_current_thread(v8);
    sprd_log(3, "%p: %s: %s: sprd_cmac_process_internal FAILED[0x%x]\n", v18, "SPRD_CE", "sprd_cmac_update", v9);
    return v9;
  }
  v10 = *(_DWORD *)(a1 + 120);
  v11 = v6 - 16;
  *(_DWORD *)(a1 + 120) = 0;
  v12 = v11 & 0xF;
  v13 = a2 + (unsigned int)(16 - v10);
  if ( (v11 & 0xF) != 0 )
  {
    v14 = v11 & 0xF;
  }
  else
  {
    v14 = 16;
    v12 = 16;
  }
  memcpy(a1 + 124, v13 + v11 - v14, v12);
  *(_DWORD *)(a1 + 120) = v12;
  if ( v11 == v12 )
    return 0;
  v16 = sprd_cmac_process_internal(a1, v13, v11 - v12, 0, 0);
  result = 0;
  if ( v16 != 0 )
  {
    v17 = (const void *)get_current_thread(0);
    sprd_log(3, "%p: %s: %s: sprd_cmac_process_internal FAILED[0x%x]\n", v17, "SPRD_CE", "sprd_cmac_update", v16);
    return v16;
  }
  return result;
}

/* ===== sprd_cmac_final @ 0x94038CB4 size 156 ===== */
__int64 __fastcall sprd_cmac_final(__int64 a1, __int64 a2)
{
  int v3; // w2
  __int64 v4; // x0
  unsigned int v5; // w20
  const void *v7; // x0

  if ( a2 == 0 )
    return 4294901767LL;
  v3 = *(_DWORD *)(a1 + 120);
  *(_DWORD *)(a1 + 8) = 1;
  v4 = sprd_cmac_process_internal(a1, a1 + 124, v3, a2, 0x10u);
  v5 = v4;
  if ( (_DWORD)v4 != 0 )
  {
    v7 = (const void *)get_current_thread(v4);
    sprd_log(3, "%p: %s: %s: sprd_cmac_process_internal FAILED[0x%x]\n", v7, "SPRD_CE", "sprd_cmac_final", v5);
  }
  sprd_aes_final(a1, 0, 0, 0, nullptr, 0);
  return v5;
}

/* ===== sprd_ecc_work @ 0x94038D50 size 160 ===== */
__int64 __fastcall sprd_ecc_work(__int64 a1)
{
  __int64 v2; // x0
  __int64 v3; // x21
  unsigned int v4; // w20
  _QWORD v6[44]; // [xsp+30h] [xbp+30h] BYREF

  memset(v6, 0, 352);
  v2 = sprd_crypto_lock_init(v6);
  if ( (_DWORD)v2 != 0 )
    return 4294901760LL;
  v3 = sprd_semaphore_create(v2);
  if ( v3 == 0 )
    return 4294901770LL;
  v6[2] = a1;
  v6[43] = v3;
  LODWORD(v6[0]) = 84082688;
  v4 = sprd_crypto_work((int *)v6);
  if ( v4 == 0 )
    sprd_semaphore_wait(v3);
  sprd_semaphore_destroy(v3);
  sprd_crypto_lock_deinit((int *)v6);
  return v4;
}

/* ===== sprd_ecc_sign @ 0x94038DF0 size 232 ===== */
__int64 __fastcall sprd_ecc_sign(unsigned int a1, __int64 a2, __int64 a3, unsigned __int8 a4, __int64 a5)
{
  unsigned int v6; // w22
  _DWORD *v10; // x19
  _DWORD *v11; // x0
  unsigned int v12; // w22
  unsigned int v14; // [xsp+44h] [xbp+44h] BYREF
  _DWORD *v15; // [xsp+48h] [xbp+48h] BYREF

  v6 = a4;
  v15 = nullptr;
  v14 = 0;
  sprd_crypto_malloc_buf(0, 0x1000u, &v15, (int *)&v14);
  memset(v15, 0, v14);
  v10 = v15;
  v11 = v15;
  *v15 = 1;
  memcpy(v11 + 2, (char *)qword_9405B120 + 508 * a1, 508);
  memcpy(v10 + 641, a2, 84);
  memcpy(v10 + 662, a3, v6);
  *((_BYTE *)v10 + 2728) = v6;
  sprd_ecc_work((__int64)v10);
  v12 = v10[1];
  memcpy(a5, v10 + 683, 164);
  *(_DWORD *)(a5 + 160) = a1;
  sprd_crypto_free_buf((__int64)v15);
  return v12;
}

/* ===== sprd_ecc_verify @ 0x94038ED8 size 272 ===== */
__int64 __fastcall sprd_ecc_verify(unsigned int a1, __int64 a2, __int64 a3, unsigned __int8 a4, __int64 a5)
{
  unsigned int v5; // w21
  _DWORD *v9; // x19
  unsigned int v10; // w20
  unsigned int v13; // [xsp+54h] [xbp+54h] BYREF
  _DWORD *v14; // [xsp+58h] [xbp+58h] BYREF

  v5 = a4;
  v14 = nullptr;
  v13 = 0;
  sprd_crypto_malloc_buf(0, 0x1000u, &v14, (int *)&v13);
  memset(v14, 0, v13);
  v9 = v14;
  *v14 = 2;
  memcpy(v9 + 2, (char *)qword_9405B120 + 508 * a1, 508);
  memcpy(v9 + 641, a2, 164);
  memcpy(v9 + 682, a3, v5);
  *((_BYTE *)v9 + 2808) = v5;
  memcpy(v9 + 703, a5, 164);
  sprd_ecc_work((__int64)v9);
  v10 = v9[1];
  if ( v10 == 0 )
  {
    if ( (unsigned int)memcmp(v9 + 744, v9 + 703, (unsigned int)(4 * v9[126])) != 0 )
      v10 = 261;
    else
      v10 = 0;
  }
  sprd_crypto_free_buf((__int64)v14);
  return v10;
}

/* ===== sprd_ecc_verify_init @ 0x94038FE8 size 208 ===== */
__int64 __fastcall sprd_ecc_verify_init(unsigned int a1, __int64 a2, unsigned int a3, __int64 a4)
{
  __int64 result; // x0
  bool v6; // cc
  __int64 v7; // x0
  int v10; // w21
  _BYTE v12[488]; // [xsp+40h] [xbp+40h] BYREF
  int v13; // [xsp+228h] [xbp+228h]
  int v14; // [xsp+230h] [xbp+230h]

  if ( a2 == 0 || a4 == 0 )
    return 263;
  v6 = a1 > 0xA;
  result = 264;
  if ( !v6 )
  {
    v7 = a1;
    v10 = v7;
    memcpy(v12, (char *)qword_9405B120 + 508 * v7, 508);
    if ( a3 <= (unsigned int)(v13 + 7) >> 3 && a3 != 0 )
    {
      memset(a4, 0, (unsigned int)(4 * v14));
      reverse_bytes(a4, a2, a3);
      *(_DWORD *)(a4 + 80) = v10;
      return 0;
    }
    else
    {
      return 259;
    }
  }
  return result;
}

/* ===== sprd_ecc_verify_prepare @ 0x940390B8 size 240 ===== */
__int64 __fastcall sprd_ecc_verify_prepare(unsigned int a1, __int64 a2, unsigned int a3, __int64 a4)
{
  __int64 result; // x0
  unsigned int v9; // w21
  _BYTE v10[484]; // [xsp+40h] [xbp+40h] BYREF
  int v11; // [xsp+224h] [xbp+224h]
  int v12; // [xsp+22Ch] [xbp+22Ch]

  if ( a2 == 0 || a4 == 0 )
    return 263;
  memcpy(v10, (char *)qword_9405B120 + 508 * a1, 508);
  result = 259;
  if ( a3 != 0 && a3 <= 2 * ((unsigned int)(v11 + 7) >> 3) )
  {
    v9 = a3 >> 1;
    memset(a4, 0, (unsigned int)(4 * v12));
    memset(a4 + 80, 0, (unsigned int)(4 * v12));
    reverse_bytes(a4, a2, v9);
    reverse_bytes(a4 + 80, a2 + v9, v9);
    *(_DWORD *)(a4 + 160) = a1;
    return 0;
  }
  return result;
}

/* ===== sprd_ecc_verify_prepare2 @ 0x940391A8 size 240 ===== */
__int64 __fastcall sprd_ecc_verify_prepare2(unsigned int a1, __int64 a2, unsigned int a3, __int64 a4)
{
  __int64 result; // x0
  unsigned int v9; // w21
  _BYTE v10[488]; // [xsp+40h] [xbp+40h] BYREF
  int v11; // [xsp+228h] [xbp+228h]
  int v12; // [xsp+230h] [xbp+230h]

  if ( a2 == 0 || a4 == 0 )
    return 263;
  memcpy(v10, (char *)qword_9405B120 + 508 * a1, 508);
  result = 259;
  if ( a3 != 0 && a3 <= 2 * ((unsigned int)(v11 + 7) >> 3) )
  {
    v9 = a3 >> 1;
    memset(a4, 0, (unsigned int)(4 * v12));
    memset(a4 + 80, 0, (unsigned int)(4 * v12));
    reverse_bytes(a4, a2, v9);
    reverse_bytes(a4 + 80, a2 + v9, v9);
    *(_DWORD *)(a4 + 160) = a1;
    return 0;
  }
  return result;
}

/* ===== sprd_ecc_sign_result @ 0x94039298 size 224 ===== */
__int64 __fastcall sprd_ecc_sign_result(__int64 a1, __int64 a2, int *a3)
{
  unsigned int v6; // w22
  int v7; // w0
  _BYTE v9[488]; // [xsp+30h] [xbp+30h] BYREF
  int v10; // [xsp+218h] [xbp+218h]

  if ( a1 == 0 || a3 == nullptr || a2 == 0 )
    return 263;
  memcpy(v9, (char *)qword_9405B120 + 508 * *(unsigned int *)(a1 + 160), 508);
  v6 = (unsigned int)(v10 + 7) >> 3;
  v7 = 2 * v6;
  if ( *a3 >= 2 * v6 )
  {
    *a3 = v7;
    reverse_bytes(a2, a1, v6);
    reverse_bytes(a2 + v6, a1 + 80, v6);
    return 0;
  }
  else
  {
    *a3 = v7;
    return 262;
  }
}

/* ===== sprd_ecc_hw_config @ 0x94039378 size 4748 ===== */
__int64 __fastcall sprd_ecc_hw_config(__int64 a1)
{
  unsigned int v2; // w20
  int v3; // w22
  unsigned int v4; // w28
  unsigned int v5; // w22
  __int64 v6; // x0
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 v9; // x0
  __int64 v10; // x0
  __int64 v11; // x0
  __int64 v12; // x0
  __int64 v13; // x0
  __int64 v14; // x0
  __int64 v15; // x0
  __int64 result; // x0
  unsigned int v17; // w20
  int v18; // w22
  unsigned int v19; // w28
  unsigned int v20; // w22
  unsigned int v21; // w28
  int v22; // w3
  unsigned __int8 *v23; // x1
  unsigned int v24; // w0
  unsigned int v25; // w21
  unsigned int v26; // w20
  __int64 v27; // x0
  __int64 v28; // x0
  __int64 v29; // x0
  __int64 v30; // x0
  __int64 v31; // x0
  __int64 v32; // x0
  __int64 v33; // x0
  __int64 v34; // x0
  __int64 v35; // x0
  unsigned int v36; // w20
  unsigned int v37; // w21
  __int64 v38; // x0
  __int64 v39; // x0
  __int64 v40; // x0
  __int64 v41; // x0
  __int64 v42; // x0
  __int64 v43; // x0
  __int64 v44; // x0
  __int64 v45; // x0
  __int64 v46; // x0
  __int64 v47; // x0
  unsigned int v48; // w28
  int v49; // w3
  unsigned __int8 *v50; // x1
  unsigned int v51; // w0
  __int64 v52; // x0
  __int64 v53; // x0
  __int64 v54; // x0
  __int64 v55; // x0
  __int64 v56; // x0
  __int64 v57; // x0
  __int64 v58; // x0
  __int64 v59; // x0
  __int64 v60; // x0
  __int64 v61; // x0
  __int64 v62; // x0
  __int64 v63; // x0
  int v64; // [xsp+64h] [xbp+64h]
  int v65; // [xsp+68h] [xbp+68h]
  __int64 v66; // [xsp+68h] [xbp+68h]
  _BYTE v67[80]; // [xsp+70h] [xbp+70h] BYREF

  switch ( *(_DWORD *)a1 )
  {
    case 0:
      v25 = 4 * *(_DWORD *)(a1 + 504);
      v26 = 4 * *(_DWORD *)(a1 + 500);
      ce_cfg_dma_len(v25, 1);
      ce_cfg_dma_len(v26, 2);
      ce_cfg_dma_addr(a1 + 516, a1 + 516);
      *(_DWORD *)(a1 + 516) = ce_cfg_dma_src(0, 17, v25, 1);
      *(_DWORD *)(a1 + 520) = ce_cfg_dma_src(0, 18, v25, 1);
      *(_DWORD *)(a1 + 524) = ce_cfg_dma_src(0, 19, v25, 1);
      *(_DWORD *)(a1 + 528) = ce_cfg_dma_src(0, 20, v25, 1);
      *(_DWORD *)(a1 + 532) = ce_cfg_dma_src(0, 21, v25, 1);
      v27 = virt_to_phys(a1 + 8);
      *(_DWORD *)(a1 + 536) = ce_cfg_dma_dst(v27, 17, v26, 2);
      v28 = virt_to_phys(a1 + 88);
      *(_DWORD *)(a1 + 540) = ce_cfg_dma_dst(v28, 18, v26, 2);
      v29 = virt_to_phys(a1 + 168);
      *(_DWORD *)(a1 + 544) = ce_cfg_dma_dst(v29, 19, v26, 2);
      v30 = virt_to_phys(a1 + 248);
      *(_DWORD *)(a1 + 548) = ce_cfg_dma_dst(v30, 20, v26, 2);
      v31 = virt_to_phys(a1 + 328);
      *(_DWORD *)(a1 + 552) = ce_cfg_dma_dst(v31, 21, v26, 2);
      v32 = virt_to_phys(a1 + 408);
      *(_DWORD *)(a1 + 556) = ce_cfg_dma_dst(v32, 22, v25, 1);
      *(_DWORD *)(a1 + 560) = ce_cmd_field(1, 1, 2, 0, 0, 0, 0, 0);
      *(_DWORD *)(a1 + 564) = ce_cmd_field(15, 1, 1, 0, 2, 0, 22, 0);
      *(_DWORD *)(a1 + 568) = ce_cmd_field(13, 1, 2, 0, 1, 1, 1, 0);
      *(_DWORD *)(a1 + 572) = ce_cmd_field2(5, 0, 16, 0);
      *(_DWORD *)(a1 + 576) = ce_cmd_field(28, 1, 0, 0, 17, 0, 0, 0);
      *(_DWORD *)(a1 + 580) = ce_cmd_field(29, 1, 4, 0, 18, 0, 1, 2);
      *(_DWORD *)(a1 + 584) = ce_cmd_field(2, 1, 5, 0, 20, 0, 21, 0);
      *(_DWORD *)(a1 + 588) = ce_cmd_field2(5, 0, 17, 0);
      v33 = virt_to_phys(a1 + 2564);
      *(_DWORD *)(a1 + 592) = ce_cfg_dma_key(1, v33, v25, 1);
      v34 = virt_to_phys(a1 + 2648);
      *(_DWORD *)(a1 + 596) = ce_cfg_dma_key(4, v34, v26, 2);
      v35 = virt_to_phys(a1 + 2728);
      *(_DWORD *)(a1 + 600) = ce_cfg_dma_key(5, v35, v26, 2);
      *(_DWORD *)(a1 + 604) = -1;
      ce_nop(a1 + 516, 92);
      dcache_clean2(a1 + 8, 508);
      dcache_clean2(a1 + 516, 2048);
      dcache_invalidate(a1 + 2564, 84);
      dcache_invalidate(a1 + 2648, 164);
      result = 0;
      break;
    case 1:
      v2 = 4 * *(_DWORD *)(a1 + 504);
      v3 = *(_DWORD *)(a1 + 500);
      v4 = *(unsigned __int8 *)(a1 + 2728);
      v65 = *(_DWORD *)(a1 + 496);
      memset(v67, 0, v2);
      v5 = 4 * v3;
      if ( *(_DWORD *)(a1 + 496) < 8 * v4 )
      {
        v48 = (unsigned int)(v65 + 7) >> 3;
        reverse_bytes(v67, a1 + 2648, v48);
        v49 = -*(_DWORD *)(a1 + 496) & 7;
        if ( v49 != 0 )
        {
          if ( (unsigned int)(v65 + 7) >> 3 <= 1 )
          {
            v51 = 0;
          }
          else
          {
            v50 = v67;
            do
            {
              *v50 = (v50[1] << (8 - v49)) | ((int)*v50 >> v49);
              ++v50;
            }
            while ( v50 != &v67[v48 - 1] );
            v51 = v48 - 1;
          }
          v67[v51] = (int)(unsigned __int8)v67[v51] >> v49;
        }
        v4 = (unsigned __int8)((unsigned int)(v65 + 7) >> 3);
      }
      else
      {
        reverse_bytes(v67, a1 + 2648, v4);
      }
      memset(a1 + 2648, 0, 80);
      memcpy(a1 + 2648, v67, v4);
      ce_cfg_dma_len(v2, 1);
      ce_cfg_dma_len(v5, 2);
      ce_cfg_dma_addr(a1 + 516, a1 + 516);
      *(_DWORD *)(a1 + 516) = ce_cfg_dma_src(0, 17, v2, 1);
      *(_DWORD *)(a1 + 520) = ce_cfg_dma_src(0, 18, v2, 1);
      *(_DWORD *)(a1 + 524) = ce_cfg_dma_src(0, 19, v2, 1);
      *(_DWORD *)(a1 + 528) = ce_cfg_dma_src(0, 20, v2, 1);
      *(_DWORD *)(a1 + 532) = ce_cfg_dma_src(0, 21, v2, 1);
      v6 = virt_to_phys(a1 + 8);
      *(_DWORD *)(a1 + 536) = ce_cfg_dma_dst(v6, 17, v5, 2);
      v7 = virt_to_phys(a1 + 88);
      *(_DWORD *)(a1 + 540) = ce_cfg_dma_dst(v7, 18, v5, 2);
      v8 = virt_to_phys(a1 + 168);
      *(_DWORD *)(a1 + 544) = ce_cfg_dma_dst(v8, 19, v5, 2);
      v9 = virt_to_phys(a1 + 248);
      *(_DWORD *)(a1 + 548) = ce_cfg_dma_dst(v9, 20, v5, 2);
      v10 = virt_to_phys(a1 + 328);
      *(_DWORD *)(a1 + 552) = ce_cfg_dma_dst(v10, 21, v5, 2);
      v11 = virt_to_phys(a1 + 408);
      *(_DWORD *)(a1 + 556) = ce_cfg_dma_dst(v11, 22, v2, 1);
      *(_DWORD *)(a1 + 560) = ce_cfg_dma_src(0, 11, v2, 1);
      v12 = virt_to_phys(a1 + 2564);
      *(_DWORD *)(a1 + 564) = ce_cfg_dma_dst(v12, 11, v2, 1);
      *(_DWORD *)(a1 + 568) = ce_cfg_dma_src(0, 9, v2, 1);
      v13 = virt_to_phys(a1 + 2648);
      *(_DWORD *)(a1 + 572) = ce_cfg_dma_dst(v13, 9, v4, 1);
      *(_DWORD *)(a1 + 576) = ce_cmd_field(15, 1, 2, 0, 9, 0, 22, 0);
      *(_DWORD *)(a1 + 580) = ce_cmd_field(1, 1, 3, 0, 0, 0, 0, 0);
      *(_DWORD *)(a1 + 584) = ce_cmd_field(15, 1, 1, 0, 3, 0, 22, 0);
      *(_DWORD *)(a1 + 588) = ce_cmd_field(13, 1, 3, 0, 1, 1, 1, 0);
      *(_DWORD *)(a1 + 592) = ce_cmd_field2(5, 0, 16, 0);
      *(_DWORD *)(a1 + 596) = ce_cmd_field(28, 1, 0, 0, 17, 0, 0, 0);
      *(_DWORD *)(a1 + 600) = ce_cmd_field(29, 1, 4, 0, 18, 0, 1, 2);
      *(_DWORD *)(a1 + 604) = ce_cmd_field(2, 1, 5, 0, 20, 0, 21, 0);
      *(_DWORD *)(a1 + 608) = ce_cmd_field2(5, 0, 17, 0);
      *(_DWORD *)(a1 + 612) = ce_cmd_field(15, 1, 3, 0, 4, 0, 22, 0);
      *(_DWORD *)(a1 + 616) = ce_cmd_field(13, 1, 6, 0, 3, 1, 1, 0);
      *(_DWORD *)(a1 + 620) = ce_cmd_field2(5, 0, 16, 0);
      *(_DWORD *)(a1 + 624) = ce_cmd_field(28, 1, 0, 0, 22, 0, 0, 0);
      *(_DWORD *)(a1 + 628) = ce_cmd_field(6, 1, 6, 0, 3, 0, 11, 0);
      *(_DWORD *)(a1 + 632) = ce_cmd_field(8, 1, 4, 0, 6, 0, 2, 0);
      *(_DWORD *)(a1 + 636) = ce_cmd_field(10, 1, 5, 0, 1, 0, 0, 0);
      *(_DWORD *)(a1 + 640) = ce_cmd_field(6, 1, 2, 0, 5, 0, 4, 0);
      *(_DWORD *)(a1 + 644) = ce_cmd_field(28, 1, 13, 0, 3, 0, 0, 0);
      *(_DWORD *)(a1 + 648) = ce_cmd_field(28, 1, 12, 0, 2, 0, 0, 0);
      v14 = virt_to_phys(a1 + 2732);
      *(_DWORD *)(a1 + 652) = ce_cfg_dma_key(13, v14, v2, 1);
      v15 = virt_to_phys(a1 + 2812);
      *(_DWORD *)(a1 + 656) = ce_cfg_dma_key(12, v15, v2, 1);
      *(_DWORD *)(a1 + 660) = -1;
      ce_nop(a1 + 516, 148);
      dcache_clean2(a1 + 8, 508);
      dcache_clean2(a1 + 516, 2048);
      dcache_clean2(a1 + 2564, 84);
      dcache_clean2(a1 + 2648, v4);
      dcache_invalidate(a1 + 2732, 164);
      goto LABEL_5;
    case 2:
      v17 = 4 * *(_DWORD *)(a1 + 504);
      v18 = *(_DWORD *)(a1 + 500);
      v19 = *(unsigned __int8 *)(a1 + 2808);
      v64 = *(_DWORD *)(a1 + 496);
      memset(v67, 0, v17);
      v20 = 4 * v18;
      v66 = a1 + 2976;
      if ( *(_DWORD *)(a1 + 496) >= 8 * v19 )
      {
        reverse_bytes(v67, a1 + 2728, v19);
      }
      else
      {
        v21 = (unsigned int)(v64 + 7) >> 3;
        reverse_bytes(v67, a1 + 2728, v21);
        v22 = -*(_DWORD *)(a1 + 496) & 7;
        if ( v22 != 0 )
        {
          if ( (unsigned int)(v64 + 7) >> 3 <= 1 )
          {
            v24 = 0;
          }
          else
          {
            v23 = v67;
            do
            {
              *v23 = (v23[1] << (8 - v22)) | ((int)*v23 >> v22);
              ++v23;
            }
            while ( v23 != &v67[v21 - 1] );
            v24 = v21 - 1;
          }
          v67[v24] = (int)(unsigned __int8)v67[v24] >> v22;
        }
        v19 = (unsigned __int8)((unsigned int)(v64 + 7) >> 3);
      }
      memset(a1 + 2728, 0, 80);
      memcpy(a1 + 2728, v67, v19);
      ce_cfg_dma_len(v17, 1);
      ce_cfg_dma_len(v20, 2);
      ce_cfg_dma_addr(a1 + 516, a1 + 516);
      *(_DWORD *)(a1 + 516) = ce_cfg_dma_src(0, 17, v17, 1);
      *(_DWORD *)(a1 + 520) = ce_cfg_dma_src(0, 18, v17, 1);
      *(_DWORD *)(a1 + 524) = ce_cfg_dma_src(0, 19, v17, 1);
      *(_DWORD *)(a1 + 528) = ce_cfg_dma_src(0, 20, v17, 1);
      *(_DWORD *)(a1 + 532) = ce_cfg_dma_src(0, 21, v17, 1);
      v52 = virt_to_phys(a1 + 8);
      *(_DWORD *)(a1 + 536) = ce_cfg_dma_dst(v52, 17, v20, 2);
      v53 = virt_to_phys(a1 + 88);
      *(_DWORD *)(a1 + 540) = ce_cfg_dma_dst(v53, 18, v20, 2);
      v54 = virt_to_phys(a1 + 168);
      *(_DWORD *)(a1 + 544) = ce_cfg_dma_dst(v54, 19, v20, 2);
      v55 = virt_to_phys(a1 + 248);
      *(_DWORD *)(a1 + 548) = ce_cfg_dma_dst(v55, 20, v20, 2);
      v56 = virt_to_phys(a1 + 328);
      *(_DWORD *)(a1 + 552) = ce_cfg_dma_dst(v56, 21, v20, 2);
      v57 = virt_to_phys(a1 + 408);
      *(_DWORD *)(a1 + 556) = ce_cfg_dma_dst(v57, 22, v17, 1);
      *(_DWORD *)(a1 + 560) = ce_cfg_dma_src(0, 13, v17, 1);
      *(_DWORD *)(a1 + 564) = ce_cfg_dma_src(0, 14, v17, 1);
      v58 = virt_to_phys(a1 + 2564);
      *(_DWORD *)(a1 + 568) = ce_cfg_dma_dst(v58, 13, v20, 2);
      v59 = virt_to_phys(a1 + 2644);
      *(_DWORD *)(a1 + 572) = ce_cfg_dma_dst(v59, 14, v20, 2);
      v60 = virt_to_phys(a1 + 2812);
      *(_DWORD *)(a1 + 576) = ce_cfg_dma_dst(v60, 11, v17, 1);
      v61 = virt_to_phys(a1 + 2892);
      *(_DWORD *)(a1 + 580) = ce_cfg_dma_dst(v61, 12, v17, 1);
      *(_DWORD *)(a1 + 584) = ce_cfg_dma_src(0, 10, v17, 1);
      v62 = virt_to_phys(a1 + 2728);
      *(_DWORD *)(a1 + 588) = ce_cfg_dma_dst(v62, 10, v17, 1);
      *(_DWORD *)(a1 + 592) = ce_cmd_field(15, 1, 1, 0, 10, 0, 22, 0);
      *(_DWORD *)(a1 + 596) = ce_cmd_field(28, 1, 0, 0, 22, 0, 0, 0);
      *(_DWORD *)(a1 + 600) = ce_cmd_field(10, 1, 2, 0, 12, 0, 0, 0);
      *(_DWORD *)(a1 + 604) = ce_cmd_field(6, 1, 3, 0, 1, 0, 2, 0);
      *(_DWORD *)(a1 + 608) = ce_cmd_field(6, 1, 4, 0, 11, 0, 2, 0);
      *(_DWORD *)(a1 + 612) = ce_cmd_field(28, 1, 0, 0, 17, 0, 0, 0);
      *(_DWORD *)(a1 + 616) = ce_cmd_field(29, 1, 5, 0, 18, 0, 3, 2);
      *(_DWORD *)(a1 + 620) = ce_cmd_field(2, 1, 6, 0, 20, 0, 21, 0);
      *(_DWORD *)(a1 + 624) = ce_cmd_field(29, 1, 1, 0, 18, 0, 4, 2);
      *(_DWORD *)(a1 + 628) = ce_cmd_field(2, 1, 2, 0, 13, 0, 14, 0);
      *(_DWORD *)(a1 + 632) = ce_cmd_field(26, 0, 4, 0, 5, 0, 6, 0);
      *(_DWORD *)(a1 + 636) = ce_cmd_field(3, 1, 3, 0, 1, 0, 2, 0);
      v63 = virt_to_phys(v66);
      *(_DWORD *)(a1 + 640) = ce_cfg_dma_key(4, v63, v17, 1);
      *(_DWORD *)(a1 + 644) = -1;
      ce_nop(a1 + 516, 132);
      dcache_clean2(a1 + 8, 508);
      dcache_clean2(a1 + 516, 2048);
      dcache_clean2(a1 + 2564, 164);
      dcache_clean2(a1 + 2728, v19);
      dcache_clean2(a1 + 2812, 164);
      dcache_invalidate(v66, v17);
      result = 0;
      break;
    case 3:
      v36 = 4 * *(_DWORD *)(a1 + 504);
      v37 = 4 * *(_DWORD *)(a1 + 500);
      ce_cfg_dma_len(v36, 1);
      ce_cfg_dma_len(v37, 2);
      ce_cfg_dma_addr(a1 + 516, a1 + 516);
      *(_DWORD *)(a1 + 516) = ce_cfg_dma_src(0, 17, v36, 1);
      *(_DWORD *)(a1 + 520) = ce_cfg_dma_src(0, 18, v36, 1);
      *(_DWORD *)(a1 + 524) = ce_cfg_dma_src(0, 19, v36, 1);
      *(_DWORD *)(a1 + 528) = ce_cfg_dma_src(0, 20, v36, 1);
      *(_DWORD *)(a1 + 532) = ce_cfg_dma_src(0, 21, v36, 1);
      v38 = virt_to_phys(a1 + 8);
      *(_DWORD *)(a1 + 536) = ce_cfg_dma_dst(v38, 17, v37, 2);
      v39 = virt_to_phys(a1 + 88);
      *(_DWORD *)(a1 + 540) = ce_cfg_dma_dst(v39, 18, v37, 2);
      v40 = virt_to_phys(a1 + 168);
      *(_DWORD *)(a1 + 544) = ce_cfg_dma_dst(v40, 19, v37, 2);
      v41 = virt_to_phys(a1 + 248);
      *(_DWORD *)(a1 + 548) = ce_cfg_dma_dst(v41, 20, v37, 2);
      v42 = virt_to_phys(a1 + 328);
      *(_DWORD *)(a1 + 552) = ce_cfg_dma_dst(v42, 21, v37, 2);
      v43 = virt_to_phys(a1 + 408);
      *(_DWORD *)(a1 + 556) = ce_cfg_dma_dst(v43, 22, v36, 1);
      *(_DWORD *)(a1 + 560) = ce_cfg_dma_src(0, 4, v36, 1);
      v44 = virt_to_phys(a1 + 2564);
      *(_DWORD *)(a1 + 564) = ce_cfg_dma_dst(v44, 4, v36, 1);
      *(_DWORD *)(a1 + 568) = ce_cfg_dma_src(0, 13, v36, 1);
      v45 = virt_to_phys(a1 + 2648);
      *(_DWORD *)(a1 + 572) = ce_cfg_dma_dst(v45, 13, v37, 2);
      *(_DWORD *)(a1 + 576) = ce_cfg_dma_src(0, 14, v36, 1);
      v46 = virt_to_phys(a1 + 2728);
      *(_DWORD *)(a1 + 580) = ce_cfg_dma_dst(v46, 14, v37, 2);
      *(_DWORD *)(a1 + 584) = ce_cmd_field(28, 1, 0, 0, 17, 0, 0, 0);
      *(_DWORD *)(a1 + 588) = ce_cmd_field(29, 1, 1, 0, 18, 0, 4, 2);
      *(_DWORD *)(a1 + 592) = ce_cmd_field(2, 1, 2, 0, 13, 0, 14, 0);
      v47 = virt_to_phys(a1 + 2812);
      *(_DWORD *)(a1 + 596) = ce_cfg_dma_key(1, v47, v37, 2);
      *(_DWORD *)(a1 + 600) = -1;
      ce_nop(a1 + 516, 88);
      dcache_clean2(a1 + 8, 508);
      dcache_clean2(a1 + 516, 2048);
      dcache_clean2(a1 + 2648, 164);
      dcache_clean2(a1 + 2564, 84);
      dcache_invalidate(a1 + 2812, 128);
      result = 0;
      break;
    default:
LABEL_5:
      result = 0;
      break;
  }
  return result;
}

/* ===== reverse_bytes @ 0x9403A604 size 52 ===== */
_BYTE *__fastcall reverse_bytes(_BYTE *result, __int64 a2, unsigned int a3)
{
  __int64 v3; // x4
  char *v4; // x1
  _BYTE *v5; // x2
  _BYTE *v6; // x4
  char v7; // t1

  v3 = a3 - 1;
  v4 = (char *)(a2 + a3 - 1LL);
  if ( a3 != 0 )
  {
    v5 = result;
    v6 = &result[v3 + 1];
    do
    {
      v7 = *v4--;
      *v5++ = v7;
    }
    while ( v5 != v6 );
  }
  return result;
}

/* ===== ce_cmd_field @ 0x9403A638 size 136 ===== */
__int64 __fastcall ce_cmd_field(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        unsigned __int8 a5,
        unsigned __int8 a6,
        unsigned __int8 a7,
        unsigned __int8 a8)
{
  int v8; // w8
  bool v9; // zf
  __int64 result; // x0

  v8 = a1;
  v9 = (a1 & 0xE0) == 0;
  result = 0xFFFFFFFFLL;
  if ( v9
    && (a2 & 0xF0) == 0
    && (a3 & 0xE0) == 0
    && (a4 & 0xFE) == 0
    && (a5 & 0xE0) == 0
    && (a6 & 0xFE) == 0
    && (a7 & 0xE0) == 0
    && (a8 & 0xC0) == 0 )
  {
    return a8 | (a7 << 6) | (a6 << 11) | (a5 << 12) | (a4 << 17) | (a3 << 18) | (a2 << 23) | (unsigned int)(v8 << 27);
  }
  return result;
}

/* ===== ce_cfg_dma_addr @ 0x9403A6C0 size 116 ===== */
__int64 __fastcall ce_cfg_dma_addr(__int64 a1, __int64 a2)
{
  unsigned __int64 v2; // x20
  int v5; // [xsp+4Ch] [xbp+4Ch] BYREF

  v5 = ((unsigned __int64)virt_to_phys(a1) >> 17) & 0x7FFFF;
  v2 = ((unsigned __int64)virt_to_phys(a2) >> 17) & 0x7FFFF;
  ce_write_cmd_pka(0x610u, 1u, (__int64)&v5);
  v5 = v2;
  ce_write_cmd_pka(0x60Cu, 1u, (__int64)&v5);
  return 0;
}

/* ===== ce_cmd_field2 @ 0x9403A734 size 64 ===== */
__int64 __fastcall ce_cmd_field2(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  int v4; // w4
  bool v5; // zf
  __int64 result; // x0

  v4 = a1;
  v5 = (a1 & 0xE0) == 0;
  result = 0xFFFFFFFFLL;
  if ( v5 && (a2 & 0xF0) == 0 && (a3 & 0xE0) == 0 )
    return a4 & 0x1FFFF | (a3 << 18) | (a2 << 23) | (unsigned int)(v4 << 27);
  return result;
}

/* ===== ce_cfg_dma_len @ 0x9403A774 size 88 ===== */
__int64 __fastcall ce_cfg_dma_len(int a1, unsigned int a2)
{
  __int64 result; // x0
  int v4; // [xsp+1Ch] [xbp+1Ch] BYREF

  result = 258;
  if ( a2 <= 3 && (a1 & 0xFFFFFC00) == 0 )
  {
    v4 = a1 << (16 * (a2 & 1));
    ce_write_cmd_pka(4 * ((a2 >> 1) + 52), 1u, (__int64)&v4);
    return 0;
  }
  return result;
}

/* ===== ce_cfg_dma_src @ 0x9403A7CC size 36 ===== */
__int64 __fastcall ce_cfg_dma_src(unsigned __int8 a1, unsigned __int8 a2, __int64 a3, unsigned __int8 a4)
{
  return ce_cmd_field(0x1Cu, a4, a2, 0, a1, 0, 0, 3u);
}

/* ===== ce_cfg_dma_dst @ 0x9403A7F0 size 24 ===== */
__int64 __fastcall ce_cfg_dma_dst(int a1, unsigned __int8 a2, __int64 a3, unsigned __int8 a4)
{
  return ce_cmd_field2(0x16u, a4, a2, a1);
}

/* ===== ce_cfg_dma_key @ 0x9403A808 size 24 ===== */
__int64 __fastcall ce_cfg_dma_key(unsigned __int8 a1, int a2, __int64 a3, unsigned __int8 a4)
{
  return ce_cmd_field2(0x17u, a4, a1, a2);
}

/* ===== ce_nop @ 0x9403A820 size 8 ===== */
__int64 ce_nop()
{
  return 0;
}

/* ===== sprd_pkcs1_v1_5_encode @ 0x9403A828 size 584 ===== */
__int64 __fastcall sprd_pkcs1_v1_5_encode(__int64 a1, unsigned int a2, int a3, __int64 a4, _BYTE *a5, _DWORD *a6)
{
  __int64 v7; // x0
  const void *v12; // x0
  __int64 v14; // x0
  const void *v15; // x0
  const void *v16; // x0
  int v17; // w25
  unsigned int v18; // w20
  unsigned int v19; // w19
  __int64 v20; // x0
  unsigned int v21; // w23
  __int64 v22; // x0
  __int64 i; // x4
  int v24; // w1
  const void *v25; // x0
  __int64 v26; // [xsp+68h] [xbp+68h]
  int v27; // [xsp+68h] [xbp+68h]
  int v28; // [xsp+68h] [xbp+68h]
  _BYTE v29[512]; // [xsp+70h] [xbp+70h] BYREF

  v7 = (unsigned int)(a3 - 1);
  if ( (unsigned int)v7 <= 1 )
  {
    v14 = a2 + 11;
    if ( (unsigned int)v14 > (unsigned int)a4 )
    {
      v16 = (const void *)get_current_thread(v14);
      sprd_log(3, "%p: %s: %s: msglen(%d) is too big\n", v16, "SPRD_CE", "sprd_pkcs1_v1_5_encode", a2);
      return 4294901767LL;
    }
    else if ( a5 != nullptr && a6 != nullptr && (v14 = (unsigned int)*a6, (unsigned int)a4 <= (unsigned int)v14) )
    {
      *a5 = 0;
      a5[1] = a3;
      v17 = a4 - a2;
      v18 = a4 - a2 - 3;
      if ( a3 == 2 )
      {
        v19 = 0;
        while ( 1 )
        {
          v26 = a4;
          v20 = sprd_rng_gen(v29, 512);
          v21 = v20;
          if ( (_DWORD)v20 != 0 )
            break;
          a4 = v26;
          v22 = 0;
LABEL_14:
          for ( i = v19 + 2; (unsigned int)v22 <= 0x1FF; i = ++v19 + 2 )
          {
            if ( v19 >= v18 )
              break;
            v24 = (unsigned __int8)v29[v22++];
            if ( v24 == 0 )
              goto LABEL_14;
            a5[i] = v24;
          }
          if ( v18 <= v19 )
            goto LABEL_19;
        }
        v25 = (const void *)get_current_thread(v20);
        sprd_log(3, "%p: %s: %s: get rng failed\n", v25, "SPRD_CE", "sprd_pkcs1_v1_5_encode");
        return v21;
      }
      else
      {
        v28 = a4;
        memset(a5 + 2, 0xFFFFFFFFLL, v18);
        LODWORD(a4) = v28;
LABEL_19:
        v27 = a4;
        a5[v17 - 1] = 0;
        memcpy(&a5[v17], a1, a2);
        *a6 = v27;
        return 0;
      }
    }
    else
    {
      v15 = (const void *)get_current_thread(v14);
      sprd_log(
        3,
        "%p: %s: %s: out(%p) or outlen(%p) is less than required\n",
        v15,
        "SPRD_CE",
        "sprd_pkcs1_v1_5_encode",
        a5,
        a6);
      return 4294901767LL;
    }
  }
  else
  {
    v12 = (const void *)get_current_thread(v7);
    sprd_log(3, "%p: %s: %s: invalid block type in padding(0x%x)\n", v12, "SPRD_CE", "sprd_pkcs1_v1_5_encode", a3);
    return 4294901765LL;
  }
}

/* ===== sprd_pkcs1_v1_5_decode @ 0x9403AA70 size 796 ===== */
__int64 __fastcall sprd_pkcs1_v1_5_decode(
        unsigned __int8 *a1,
        unsigned int a2,
        unsigned int a3,
        unsigned int a4,
        const void *a5,
        _DWORD *a6,
        _DWORD *a7)
{
  unsigned int v9; // w21
  __int64 v12; // x0
  __int64 v13; // x2
  const void *v15; // x0
  const void *v16; // x0
  const void *v17; // x0
  unsigned __int64 v18; // x0
  int v19; // w1
  unsigned int v20; // w5
  unsigned int v21; // w21
  __int64 v22; // x2
  const void *v23; // x0
  const void *v24; // x0
  int v25; // w1
  unsigned __int8 *v26; // x24
  const void *v27; // x0
  __int64 v28; // x0
  const void *v29; // x0

  v9 = a3;
  if ( a1 == nullptr || a2 == 0 )
  {
    v15 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: msg is %p or msglen is %d\n", v15, "SPRD_CE", "sprd_pkcs1_v1_5_decode", a1, a2);
    return 4294901767LL;
  }
  if ( a7 == nullptr )
  {
    v17 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: is_valid is NULL\n", v17, "SPRD_CE", "sprd_pkcs1_v1_5_decode");
    return 4294901767LL;
  }
  *a7 = 0;
  if ( a2 > a4 || a4 <= 0xA )
  {
    v16 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: msglen(%d) is too big or too small\n", v16, "SPRD_CE", "sprd_pkcs1_v1_5_decode", a2);
    return 4294901768LL;
  }
  v12 = *a1;
  if ( (_DWORD)v12 != 0 || (_DWORD)(v12 = a1[1]) != (unsigned __int8)a3 )
  {
    v13 = get_current_thread(v12);
    sprd_log(
      3,
      "%p: %s: %s: bad msg[0](0x%x) or msg[1](0x%x)\n",
      v13,
      "SPRD_CE",
      "sprd_pkcs1_v1_5_decode",
      *a1,
      a1[1]);
    return 4294901768LL;
  }
  if ( a3 == 1 )
  {
    v18 = (unsigned __int64)(a1 + 2);
    v9 = 2;
    while ( 1 )
    {
      v25 = *(unsigned __int8 *)v18;
      v26 = (unsigned __int8 *)v18++;
      if ( v25 != 255 )
        break;
      if ( a4 <= ++v9 )
      {
        v18 = v9;
        v26 = &a1[v9];
        v25 = *v26;
        break;
      }
    }
    if ( v25 != 0 )
    {
      v27 = (const void *)get_current_thread(v18);
      sprd_log(
        3,
        "%p: %s: %s: There was no 0x00 to separate ps from msg. msg[%d] = 0x%x\n",
        v27,
        "SPRD_CE",
        "sprd_pkcs1_v1_5_decode",
        v9,
        *v26);
      return 4294901768LL;
    }
  }
  else
  {
    if ( a3 != 2 )
    {
      v24 = (const void *)get_current_thread(v12);
      sprd_log(3, "%p: %s: %s: invalid block type in padding(0x%x)\n", v24, "SPRD_CE", "sprd_pkcs1_v1_5_decode", v9);
      return 4294901765LL;
    }
    v18 = (unsigned __int64)(a1 + 2);
    do
    {
      v19 = *(unsigned __int8 *)v18++;
      if ( v19 == 0 )
        break;
      ++v9;
    }
    while ( a4 > v9 );
  }
  v20 = v9 + 1;
  if ( a4 <= v9 + 1 )
  {
    v28 = get_current_thread(v18);
    sprd_log(
      3,
      "%p: %s: %s: There was no 0x00 to separate ps from msg. msg[%d] = 0x%x\n",
      v28,
      "SPRD_CE",
      "sprd_pkcs1_v1_5_decode",
      v9 + 1,
      a1[v9 + 1]);
    return 4294901768LL;
  }
  v21 = v9 - 2;
  if ( v21 <= 7 )
  {
    v29 = (const void *)get_current_thread(v18);
    sprd_log(3, "%p: %s: %s: the length of ps(%d) is less than 8\n", v29, "SPRD_CE", "sprd_pkcs1_v1_5_decode", v21);
    return 4294901768LL;
  }
  else if ( a5 != nullptr
         && a6 != nullptr
         && (v18 = (unsigned int)*a6, v22 = a2 - 3 - v21, (unsigned int)v18 >= (unsigned int)v22) )
  {
    *a6 = v22;
    memcpy(a5, &a1[v20], v22);
    *a7 = 1;
    return 0;
  }
  else
  {
    v23 = (const void *)get_current_thread(v18);
    sprd_log(
      3,
      "%p: %s: %s: out(%p) or outlen(%p) is less than required\n",
      v23,
      "SPRD_CE",
      "sprd_pkcs1_v1_5_decode",
      a5,
      a6);
    return 4294901767LL;
  }
}

/* ===== cmp_big_endian @ 0x9403AD8C size 88 ===== */
__int64 __fastcall cmp_big_endian(unsigned __int8 *a1, int a2, unsigned __int8 *a3)
{
  unsigned int v3; // w4
  unsigned int v4; // w3
  unsigned __int8 *v5; // x2
  unsigned __int8 *v6; // x1
  unsigned int v7; // t1
  unsigned int v8; // t1

  if ( a2 <= 0 )
    return 0;
  v3 = *a1;
  v4 = *a3;
  if ( v3 == v4 )
  {
    v5 = a3 + 1;
    v6 = &a1[a2 - 1];
    while ( a1 != v6 )
    {
      v7 = *++a1;
      v3 = v7;
      v8 = *v5++;
      v4 = v8;
      if ( v3 != v8 )
        goto LABEL_7;
    }
    return 0;
  }
LABEL_7:
  if ( v3 <= v4 )
    return 0xFFFFFFFFLL;
  else
    return 1;
}

/* ===== sprd_rsa_nopad @ 0x9403ADE4 size 884 ===== */
__int64 __fastcall sprd_rsa_nopad(
        int a1,
        __int64 a2,
        unsigned int a3,
        __int64 a4,
        unsigned int a5,
        __int64 a6,
        unsigned int a7,
        __int64 a8,
        unsigned int *a9)
{
  __int64 v16; // x0
  int v17; // w0
  __int64 v18; // x0
  __int64 v19; // x22
  const void *v20; // x0
  unsigned int v21; // w21
  const void *v23; // x0
  __int64 v24; // x0
  const void *v25; // x0
  const void *v26; // x0
  unsigned int v28; // [xsp+74h] [xbp+74h] BYREF
  __int64 v29; // [xsp+78h] [xbp+78h] BYREF
  _QWORD v30[44]; // [xsp+80h] [xbp+80h] BYREF

  v29 = 0;
  v16 = memset(v30, 0, 352);
  if ( a3 == 256 )
  {
    if ( a1 == 1 )
      v17 = 83951618;
    else
      v17 = 83951623;
    goto LABEL_11;
  }
  if ( a3 > 0x100 )
  {
    if ( a3 == 384 )
    {
      if ( a1 == 1 )
        v17 = 83951619;
      else
        v17 = 83951624;
    }
    else
    {
      if ( a3 != 512 )
        goto LABEL_21;
      if ( a1 == 1 )
        v17 = 83951620;
      else
        v17 = 83951625;
    }
LABEL_11:
    LODWORD(v30[0]) = v17;
    goto LABEL_12;
  }
  if ( a3 == 32 )
  {
    if ( a1 == 1 )
      v17 = 83951616;
    else
      v17 = 83951621;
    goto LABEL_11;
  }
  if ( a3 != 128 )
  {
LABEL_21:
    v23 = (const void *)get_current_thread(v16);
    sprd_log(3, "%p: %s: %s: bad key len!\n", v23, "SPRD_CE", "sprd_rsa_nopad");
    return 4294901769LL;
  }
  if ( a1 == 1 )
    LODWORD(v30[0]) = 83951617;
  else
    LODWORD(v30[0]) = 83951622;
LABEL_12:
  v18 = sprd_crypto_lock_init(v30);
  if ( (_DWORD)v18 != 0 )
  {
    v26 = (const void *)get_current_thread(v18);
    sprd_log(3, "%p: %s: %s: FAILED!\n", v26, "SPRD_CE", "sprd_rsa_nopad");
    return 4294901760LL;
  }
  else
  {
    v19 = sprd_semaphore_create(v18);
    if ( v19 != 0 )
    {
      sprd_crypto_malloc_buf((__int64)v30, 0x1000u, &v29, (int *)&v28);
      if ( v29 != 0 && v28 > 0xFFF )
      {
        memcpy(v29, a2, a3);
        memset(v29 + 512, 0, a3);
        memcpy(v29 + 512LL - a5 + a3, a4, a5);
        memcpy(v29 + 1024, a6, a7);
        LODWORD(v30[4]) = a3;
        v30[2] = v29;
        v30[3] = v29 + 512;
        LODWORD(v30[1]) = 1;
        v30[37] = v29 + 1024;
        v30[39] = v29 + 1536;
        v30[5] = v29 + 4096;
        HIDWORD(v30[0]) = 0;
        LODWORD(v30[38]) = a7;
        LODWORD(v30[40]) = a7;
        v30[43] = v19;
        dcache_clean(v29, 0x2000);
        v24 = sprd_crypto_work((int *)v30);
        v21 = v24;
        if ( (_DWORD)v24 != 0 )
        {
          v25 = (const void *)get_current_thread(v24);
          sprd_log(3, "%p: %s: %s: sprd_crypto_process return 0x%x\n", v25, "SPRD_CE", "sprd_rsa_nopad", v21);
        }
        else
        {
          sprd_semaphore_wait(v19);
          if ( a9 != nullptr )
            *a9 = a7;
          dcache_invalidate(v29 + 1536, 512);
          memcpy(a8, v29 + 1536, a7);
        }
      }
      else
      {
        v20 = (const void *)get_current_thread(v29);
        v21 = -65526;
        sprd_log(3, "%p: %s: %s: buf_len is %d, too small!\n", v20, "SPRD_CE", "sprd_rsa_nopad", v28);
      }
      if ( v29 != 0 )
        sprd_crypto_free_buf(v29);
      sprd_semaphore_destroy(v19);
      sprd_crypto_lock_deinit((int *)v30);
      return v21;
    }
    else
    {
      return 4294901770LL;
    }
  }
}

/* ===== sprd_rsa_public_encrypt @ 0x9403B158 size 452 ===== */
__int64 __fastcall sprd_rsa_public_encrypt(__int64 a1, unsigned __int8 *a2, int a3, __int64 a4, unsigned int *a5, int *a6)
{
  unsigned int v6; // w6
  __int64 v7; // x7
  int v8; // w5
  unsigned int v12; // w20
  unsigned __int8 *v13; // x22
  __int64 v14; // x0
  const void *v16; // x0
  const void *v17; // x0
  const void *v18; // x0
  const void *v19; // x0
  const void *v20; // x0
  int v24; // [xsp+58h] [xbp+48h]

  v6 = a3;
  v7 = a4;
  v8 = *a6;
  if ( a1 != 0 )
  {
    if ( a2 != nullptr && a3 != 0 )
    {
      if ( a4 != 0 )
      {
        if ( v8 != 0 )
        {
          v24 = v8;
          v18 = (const void *)get_current_thread(a1);
          sprd_log(3, "%p: %s: %s: Bad padding type(%d)!\n", v18, "SPRD_CE", "sprd_rsa_public_encrypt", v24);
          return 4294901765LL;
        }
        else
        {
          v12 = *(_DWORD *)(a1 + 16);
          v13 = *(unsigned __int8 **)a1;
          v14 = a3 - v12;
          if ( a3 == v12 )
          {
            v14 = cmp_big_endian(a2, a3, v13);
            v7 = a4;
            v6 = a3;
          }
          if ( (v14 & 0x80000000) != 0 )
          {
            return sprd_rsa_nopad(
                     1,
                     (__int64)v13,
                     v12,
                     *(_QWORD *)(a1 + 8),
                     *(_DWORD *)(a1 + 20),
                     (__int64)a2,
                     v6,
                     v7,
                     a5);
          }
          else
          {
            v16 = (const void *)get_current_thread(v14);
            sprd_log(3, "%p: %s: %s: Bad data too lager for modulus!\n", v16, "SPRD_CE", "sprd_rsa_public_encrypt");
            return 4294901772LL;
          }
        }
      }
      else
      {
        v20 = (const void *)get_current_thread(a1);
        sprd_log(3, "%p: %s: %s: Bad dst(%p)\n", v20, "SPRD_CE", "sprd_rsa_public_encrypt", nullptr);
        return 4294901767LL;
      }
    }
    else
    {
      v17 = (const void *)get_current_thread(a1);
      sprd_log(3, "%p: %s: %s: Bad src(%p) or src_size(%d)\n", v17, "SPRD_CE", "sprd_rsa_public_encrypt", a2, a3);
      return 4294901767LL;
    }
  }
  else
  {
    v19 = (const void *)get_current_thread(0);
    sprd_log(3, "%p: %s: %s: Bad pub key(%p)!\n", v19, "SPRD_CE", "sprd_rsa_public_encrypt", nullptr);
    return 4294901762LL;
  }
}

/* ===== sprd_rsa_private_decrypt @ 0x9403B31C size 452 ===== */
__int64 __fastcall sprd_rsa_private_decrypt(__int64 a1, unsigned __int8 *a2, int a3, __int64 a4, unsigned int *a5, int *a6)
{
  unsigned int v6; // w6
  __int64 v7; // x7
  int v8; // w5
  unsigned int v12; // w20
  unsigned __int8 *v13; // x22
  __int64 v14; // x0
  const void *v16; // x0
  const void *v17; // x0
  const void *v18; // x0
  const void *v19; // x0
  const void *v20; // x0
  int v24; // [xsp+58h] [xbp+48h]

  v6 = a3;
  v7 = a4;
  v8 = *a6;
  if ( a1 != 0 )
  {
    if ( a2 != nullptr && a3 != 0 )
    {
      if ( a4 != 0 )
      {
        if ( v8 != 0 )
        {
          v24 = v8;
          v18 = (const void *)get_current_thread(a1);
          sprd_log(3, "%p: %s: %s: Bad padding type(%d)!\n", v18, "SPRD_CE", "sprd_rsa_private_decrypt", v24);
          return 4294901765LL;
        }
        else
        {
          v12 = *(_DWORD *)(a1 + 24);
          v13 = *(unsigned __int8 **)a1;
          v14 = a3 - v12;
          if ( a3 == v12 )
          {
            v14 = cmp_big_endian(a2, a3, v13);
            v7 = a4;
            v6 = a3;
          }
          if ( (v14 & 0x80000000) != 0 )
          {
            return sprd_rsa_nopad(
                     0,
                     (__int64)v13,
                     v12,
                     *(_QWORD *)(a1 + 16),
                     *(_DWORD *)(a1 + 32),
                     (__int64)a2,
                     v6,
                     v7,
                     a5);
          }
          else
          {
            v16 = (const void *)get_current_thread(v14);
            sprd_log(3, "%p: %s: %s: Bad data too lager for modulus!\n", v16, "SPRD_CE", "sprd_rsa_private_decrypt");
            return 4294901772LL;
          }
        }
      }
      else
      {
        v20 = (const void *)get_current_thread(a1);
        sprd_log(3, "%p: %s: %s: Bad dst(%p)\n", v20, "SPRD_CE", "sprd_rsa_private_decrypt", nullptr);
        return 4294901767LL;
      }
    }
    else
    {
      v17 = (const void *)get_current_thread(a1);
      sprd_log(3, "%p: %s: %s: Bad src(%p) or src_size(%d)\n", v17, "SPRD_CE", "sprd_rsa_private_decrypt", a2, a3);
      return 4294901767LL;
    }
  }
  else
  {
    v19 = (const void *)get_current_thread(0);
    sprd_log(3, "%p: %s: %s: Bad priv key(%p)!\n", v19, "SPRD_CE", "sprd_rsa_private_decrypt", nullptr);
    return 4294901762LL;
  }
}

/* ===== sprd_rsa_key_gen @ 0x9403B4E0 size 756 ===== */
__int64 __fastcall sprd_rsa_key_gen(__int64 a1, unsigned int a2, int a3, __int64 a4, __int64 a5)
{
  __int64 v10; // x0
  __int64 v11; // x0
  __int64 v12; // x23
  const void *v13; // x0
  unsigned int v14; // w21
  const void *v16; // x0
  __int64 v17; // x0
  const void *v18; // x0
  const void *v19; // x0
  unsigned int v20; // [xsp+64h] [xbp+64h] BYREF
  __int64 v21; // [xsp+68h] [xbp+68h] BYREF
  _QWORD v22[44]; // [xsp+70h] [xbp+70h] BYREF

  v10 = memset(v22, 0, 352);
  if ( a3 == 256 )
  {
    LODWORD(v22[4]) = 256;
    LODWORD(v22[0]) = 84017154;
  }
  else if ( a3 > 256 )
  {
    if ( a3 == 384 )
    {
      LODWORD(v22[4]) = 384;
      LODWORD(v22[0]) = 84017155;
    }
    else
    {
      if ( a3 != 512 )
        goto LABEL_17;
      LODWORD(v22[4]) = 512;
      LODWORD(v22[0]) = 84017156;
    }
  }
  else
  {
    if ( a3 != 32 )
    {
      if ( a3 == 128 )
      {
        LODWORD(v22[4]) = 128;
        LODWORD(v22[0]) = 84017153;
        goto LABEL_6;
      }
LABEL_17:
      v16 = (const void *)get_current_thread(v10);
      sprd_log(3, "%p: %s: %s: bad key len!\n", v16, "SPRD_CE", "sprd_rsa_key_gen");
      return 4294901769LL;
    }
    LODWORD(v22[4]) = 32;
    LODWORD(v22[0]) = 84017152;
  }
LABEL_6:
  v11 = sprd_crypto_lock_init(v22);
  if ( (_DWORD)v11 != 0 )
  {
    v19 = (const void *)get_current_thread(v11);
    sprd_log(3, "%p: %s: %s: FAILED!\n", v19, "SPRD_CE", "sprd_rsa_key_gen");
    return 4294901760LL;
  }
  else
  {
    v12 = sprd_semaphore_create(v11);
    if ( v12 != 0 )
    {
      sprd_crypto_malloc_buf((__int64)v22, 0x1000u, &v21, (int *)&v20);
      if ( v21 != 0 && v20 > 0xFFF )
      {
        memset(v21 + 1024, 0, (unsigned int)a3);
        memcpy(v21 + 1024, a1, a2);
        HIDWORD(v22[0]) = 0;
        LODWORD(v22[38]) = a2;
        v22[37] = v21 + 1024;
        LODWORD(v22[1]) = 1;
        v22[39] = v21 + 1536;
        LODWORD(v22[40]) = 2 * a3;
        v22[5] = v21 + 4096;
        v22[43] = v12;
        dcache_clean(v21, 0x2000);
        v17 = sprd_crypto_work((int *)v22);
        v14 = v17;
        if ( (_DWORD)v17 != 0 )
        {
          v18 = (const void *)get_current_thread(v17);
          sprd_log(3, "%p: %s: %s: sprd_crypto_process return 0x%x\n", v18, "SPRD_CE", "sprd_rsa_key_gen", v14);
        }
        else
        {
          sprd_semaphore_wait(v12);
          dcache_invalidate(v21 + 1536, 1024);
          memcpy(a4, v21 + 1536, (unsigned int)a3);
          memcpy(a5, v21 + a3 + 1536LL, (unsigned int)a3);
        }
      }
      else
      {
        v13 = (const void *)get_current_thread(v21);
        v14 = -65526;
        sprd_log(3, "%p: %s: %s: buf_len is %d, too small!\n", v13, "SPRD_CE", "sprd_rsa_key_gen", v20);
      }
      if ( v21 != 0 )
        sprd_crypto_free_buf(v21);
      sprd_semaphore_destroy(v12);
      sprd_crypto_lock_deinit((int *)v22);
      return v14;
    }
    else
    {
      return 4294901770LL;
    }
  }
}

/* ===== sprd_rsa_prime_gen @ 0x9403B7D4 size 528 ===== */
__int64 __fastcall sprd_rsa_prime_gen(unsigned int a1, __int64 a2)
{
  __int64 v4; // x0
  __int64 v5; // x0
  __int64 v6; // x23
  __int64 v7; // x0
  const void *v8; // x0
  unsigned int v9; // w21
  __int64 v11; // x0
  const void *v12; // x0
  const void *v13; // x0
  const void *v14; // x0
  unsigned int v15; // [xsp+44h] [xbp+44h] BYREF
  __int64 v16; // [xsp+48h] [xbp+48h] BYREF
  _QWORD v17[44]; // [xsp+50h] [xbp+50h] BYREF

  memset(v17, 0, 352);
  v4 = 84213760;
  LODWORD(v17[0]) = 84213760;
  if ( a1 - 32 > 0xE9 || (v4 = a1 & 3, (a1 & 3) != 0) )
  {
    v13 = (const void *)get_current_thread(v4);
    sprd_log(
      3,
      "%p: %s: %s: prime_len: range [32byte-265byte] and must be integral multiple of 4!\n",
      v13,
      "SPRD_CE",
      "sprd_rsa_prime_gen");
    return 4294901769LL;
  }
  else
  {
    LODWORD(v17[3]) = a1;
    v5 = sprd_crypto_lock_init(v17);
    if ( (_DWORD)v5 != 0 )
    {
      v14 = (const void *)get_current_thread(v5);
      sprd_log(3, "%p: %s: %s: FAILED!\n", v14, "SPRD_CE", "sprd_rsa_prime_gen");
      return 4294901760LL;
    }
    else
    {
      v6 = sprd_semaphore_create(v5);
      if ( v6 != 0 )
      {
        v7 = sprd_crypto_malloc_buf((__int64)v17, 0x1000u, &v16, (int *)&v15);
        if ( v16 != 0 && (v7 = v15, v15 > 0xFFF) )
        {
          LODWORD(v17[1]) = 1;
          v17[39] = v16;
          v17[4] = v16 + 1024;
          HIDWORD(v17[0]) = 0;
          v17[37] = 0;
          LODWORD(v17[38]) = a1;
          LODWORD(v17[40]) = a1;
          v17[43] = v6;
          dcache_clean(v16, 4096);
          v11 = sprd_crypto_work((int *)v17);
          v9 = v11;
          if ( (_DWORD)v11 != 0 )
          {
            v12 = (const void *)get_current_thread(v11);
            sprd_log(3, "%p: %s: %s: sprd_crypto_process return 0x%x\n", v12, "SPRD_CE", "sprd_rsa_prime_gen", v9);
          }
          else
          {
            sprd_semaphore_wait(v6);
            dcache_invalidate(v16, 1024);
            memcpy(a2, v16, a1);
          }
        }
        else
        {
          v8 = (const void *)get_current_thread(v7);
          v9 = -65526;
          sprd_log(3, "%p: %s: %s: buf_len is %d, too small!\n", v8, "SPRD_CE", "sprd_rsa_prime_gen", v15);
        }
        if ( v16 != 0 )
          sprd_crypto_free_buf(v16);
        sprd_semaphore_destroy(v6);
        sprd_crypto_lock_deinit((int *)v17);
        return v9;
      }
      else
      {
        return 4294901770LL;
      }
    }
  }
}

/* ===== sprd_rsa_sign @ 0x9403B9E4 size 568 ===== */
__int64 __fastcall sprd_rsa_sign(__int64 a1, __int64 a2, unsigned int a3, const void *a4, unsigned int *a5, int *a6)
{
  __int64 v6; // x20
  unsigned __int8 *v7; // x23
  int v10; // w5
  unsigned int v11; // w8
  __int64 v12; // x0
  unsigned int v13; // w19
  unsigned int v14; // w6
  unsigned int v15; // w19
  __int64 v16; // x0
  unsigned __int8 *v17; // x24
  const void *v19; // x0
  const void *v20; // x0
  const void *v21; // x0
  const void *v22; // x0
  const void *v23; // x0
  unsigned int v24; // [xsp+68h] [xbp+58h]
  int v25; // [xsp+68h] [xbp+58h]
  unsigned int v26; // [xsp+7Ch] [xbp+6Ch] BYREF
  _BYTE v27[512]; // [xsp+80h] [xbp+70h] BYREF

  v6 = a1;
  v7 = (unsigned __int8 *)a2;
  v10 = *a6;
  if ( a1 == 0 )
  {
    v23 = (const void *)get_current_thread(0);
    sprd_log(3, "%p: %s: %s: Bad priv key(%p)!\n", v23, "SPRD_CE", "sprd_rsa_sign", nullptr);
    return 4294901762LL;
  }
  if ( a4 == nullptr || a5 == nullptr || (v11 = *(_DWORD *)(a1 + 24), (unsigned int)(a1 = *a5) < v11) )
  {
    v22 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: Bad sig(%p) or sig_size(%p)!\n", v22, "SPRD_CE", "sprd_rsa_sign", a4, a5);
    return 4294901767LL;
  }
  if ( v10 != 0 )
  {
    if ( v10 != 20 )
    {
      v25 = v10;
      v19 = (const void *)get_current_thread(a1);
      sprd_log(3, "%p: %s: %s: Bad padding type(%d)!\n", v19, "SPRD_CE", "sprd_rsa_sign", v25);
      return 4294901765LL;
    }
    v26 = v11;
    v12 = sprd_pkcs1_v1_5_encode(a2, a3, 1, v11, v27, &v26);
    v13 = v12;
    if ( (_DWORD)v12 != 0 )
    {
      v20 = (const void *)get_current_thread(v12);
      sprd_log(3, "%p: %s: %s: rsa padding encode failed(0x%x)!\n", v20, "SPRD_CE", "sprd_rsa_sign", v13);
      return v13;
    }
    v14 = v26;
    v7 = v27;
    v15 = *(_DWORD *)(v6 + 24);
  }
  else
  {
    v15 = v11;
    v14 = a3;
    v26 = a3;
  }
  v16 = v14 - v15;
  v17 = *(unsigned __int8 **)v6;
  if ( v14 == v15 )
  {
    v24 = v14;
    v16 = cmp_big_endian(v7, v14, *(unsigned __int8 **)v6);
    v14 = v24;
  }
  if ( (v16 & 0x80000000) != 0 )
    return sprd_rsa_nopad(
             0,
             (__int64)v17,
             v15,
             *(_QWORD *)(v6 + 16),
             *(_DWORD *)(v6 + 32),
             (__int64)v7,
             v14,
             (__int64)a4,
             a5);
  v21 = (const void *)get_current_thread(v16);
  sprd_log(3, "%p: %s: %s: Bad data too lager for modulus!\n", v21, "SPRD_CE", "sprd_rsa_sign");
  return 4294901772LL;
}

/* ===== sprd_rsa_verify @ 0x9403BC1C size 916 ===== */
__int64 __fastcall sprd_rsa_verify(
        __int64 a1,
        __int64 a2,
        unsigned int a3,
        unsigned __int8 *a4,
        unsigned int a5,
        int *a6,
        unsigned int *a7)
{
  int v12; // w26
  unsigned __int8 *v13; // x27
  unsigned int v14; // w21
  __int64 v15; // x0
  __int64 v16; // x0
  unsigned int v17; // w20
  unsigned int v18; // w3
  __int64 v19; // x0
  unsigned int v20; // w20
  __int64 v21; // x0
  const void *v22; // x0
  const void *v24; // x0
  const void *v25; // x0
  const void *v26; // x0
  const void *v27; // x0
  const void *v28; // x0
  const void *v29; // x0
  __int64 v30; // x2
  __int64 v31; // x2
  unsigned int v33; // [xsp+84h] [xbp+74h] BYREF
  unsigned int v34; // [xsp+88h] [xbp+78h] BYREF
  unsigned int v35; // [xsp+8Ch] [xbp+7Ch] BYREF
  unsigned __int8 v36[512]; // [xsp+90h] [xbp+80h] BYREF
  _BYTE v37[512]; // [xsp+290h] [xbp+280h] BYREF

  v12 = *a6;
  if ( a1 == 0 )
  {
    v29 = (const void *)get_current_thread(0);
    sprd_log(3, "%p: %s: %s: Bad pub key(%p)!\n", v29, "SPRD_CE", "sprd_rsa_verify", nullptr);
    return 4294901762LL;
  }
  if ( a2 == 0 )
  {
    v30 = get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: Bad dig(%p)!\n", v30, "SPRD_CE", "sprd_rsa_verify", 0);
    return 4294901767LL;
  }
  if ( a4 == nullptr || a5 == 0 )
  {
    v28 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: Bad sig(%p) or sig_size(%d)!\n", v28, "SPRD_CE", "sprd_rsa_verify", a4, a5);
    return 4294901767LL;
  }
  if ( a7 == nullptr )
  {
    v31 = get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: Bad result(%p)!\n", v31, "SPRD_CE", "sprd_rsa_verify", 0);
    return 4294901767LL;
  }
  *a7 = -1;
  v13 = *(unsigned __int8 **)a1;
  v14 = *(_DWORD *)(a1 + 16);
  v15 = a5 - v14;
  if ( a5 == v14 )
    v15 = cmp_big_endian(a4, a5, *(unsigned __int8 **)a1);
  if ( (v15 & 0x80000000) != 0 )
  {
    v16 = sprd_rsa_nopad(
            1,
            (__int64)v13,
            v14,
            *(_QWORD *)(a1 + 8),
            *(_DWORD *)(a1 + 20),
            (__int64)a4,
            a5,
            (__int64)v36,
            &v33);
    v17 = v16;
    if ( (_DWORD)v16 != 0 )
    {
      v26 = (const void *)get_current_thread(v16);
      sprd_log(3, "%p: %s: %s: sprd_rsa_nopad failed(0x%x)!\n", v26, "SPRD_CE", "sprd_rsa_verify", v17);
      return v17;
    }
    else if ( v12 != 0 )
    {
      if ( v12 == 20 )
      {
        v18 = *(_DWORD *)(a1 + 16);
        v34 = 512;
        v19 = sprd_pkcs1_v1_5_decode(v36, v33, 1u, v18, v37, &v34, &v35);
        v20 = v19;
        if ( (_DWORD)v19 != 0 || (v19 = v35, v35 == 0) )
        {
          v25 = (const void *)get_current_thread(v19);
          sprd_log(
            3,
            "%p: %s: %s: rsa padding decode failed(0x%x), is_valid(%d)!\n",
            v25,
            "SPRD_CE",
            "sprd_rsa_verify",
            v20,
            v35);
          *a7 = -1;
          return v20;
        }
        else
        {
          if ( a3 != 0 )
          {
            v21 = v34;
            if ( v34 == a3 )
            {
              v21 = memcmp(v37, a2, a3);
              if ( (_DWORD)v21 == 0 )
                goto LABEL_20;
            }
            v22 = (const void *)get_current_thread(v21);
            sprd_log(
              3,
              "%p: %s: %s: temp_len(%d) is not equal dig_size(%d) or memcmp is failed\n",
              v22,
              "SPRD_CE",
              "sprd_rsa_verify",
              v34,
              a3);
            goto LABEL_17;
          }
          memcpy(a2, v37, v34);
          *a7 = v34;
          return 0;
        }
      }
      else
      {
        v24 = (const void *)get_current_thread(v16);
        sprd_log(3, "%p: %s: %s: Bad padding type(%d)!\n", v24, "SPRD_CE", "sprd_rsa_verify", v12);
        return 4294901765LL;
      }
    }
    else
    {
      if ( a3 != 0 )
      {
        if ( (unsigned int)memcmp(v36, a2, a3) == 0 )
        {
LABEL_20:
          *a7 = 0;
          return 0;
        }
LABEL_17:
        *a7 = -1;
        return 0;
      }
      memcpy(a2, v36, v33);
      *a7 = v33;
      return 0;
    }
  }
  else
  {
    v27 = (const void *)get_current_thread(v15);
    sprd_log(3, "%p: %s: %s: Bad data too lager for modulus!\n", v27, "SPRD_CE", "sprd_rsa_verify");
    return 4294901772LL;
  }
}

/* ===== sprd_rng_gen @ 0x9403BFB0 size 540 ===== */
__int64 __fastcall sprd_rng_gen(__int64 a1, int a2)
{
  __int64 v4; // x0
  unsigned int v5; // w24
  __int64 v6; // x23
  __int64 v7; // x0
  const void *v8; // x0
  unsigned int v10; // w20
  __int64 v11; // x22
  __int64 v12; // x0
  unsigned int v13; // w25
  unsigned int v14; // w1
  const void *v15; // x0
  const void *v16; // x0
  unsigned int v17; // [xsp+64h] [xbp+64h] BYREF
  char *v18; // [xsp+68h] [xbp+68h] BYREF
  _QWORD v19[44]; // [xsp+70h] [xbp+70h] BYREF

  v18 = nullptr;
  memset(v19, 0, 352);
  LODWORD(v19[0]) = 84148224;
  v4 = sprd_crypto_lock_init(v19);
  v5 = v4;
  if ( (_DWORD)v4 != 0 )
  {
    v16 = (const void *)get_current_thread(v4);
    sprd_log(3, "%p: %s: %s: FAILED!\n", v16, "SPRD_CE", "sprd_rng_gen");
    return 4294901760LL;
  }
  else
  {
    v6 = sprd_semaphore_create(v4);
    if ( v6 != 0 )
    {
      v7 = sprd_crypto_malloc_buf((__int64)v19, 0x40u, &v18, (int *)&v17);
      if ( v18 != nullptr && (v7 = v17, v17 > 0x1FF) )
      {
        v19[39] = v18;
        v10 = (unsigned int)(a2 + 511) >> 9;
        HIDWORD(v19[0]) = 0;
        v11 = a1;
        v19[37] = 0;
        LODWORD(v19[1]) = 1;
        LODWORD(v19[38]) = 0;
        LODWORD(v19[40]) = 512;
        v19[2] = v18 + 4096;
        v19[43] = v6;
        dcache_clean(v18, 0x2000);
        if ( v10 != 0 )
        {
          while ( 1 )
          {
            v13 = 512;
            if ( v10 == 1 )
              v13 = a2 + a1 - v11;
            dcache_clean(v18, 512);
            v14 = sprd_crypto_work((int *)v19);
            if ( v14 != 0 )
              break;
            sprd_semaphore_wait(v6);
            dcache_invalidate(v18, 512);
            v12 = v11;
            v11 += v13;
            memcpy(v12, v18, v13);
            if ( --v10 == 0 )
              goto LABEL_6;
          }
          v5 = v14;
          v15 = (const void *)get_current_thread(v6);
          sprd_log(3, "%p: %s: %s: sprd_crypto_work return 0x%x\n", v15, "SPRD_CE", "sprd_rng_gen", v5);
        }
      }
      else
      {
        v8 = (const void *)get_current_thread(v7);
        v5 = -65526;
        sprd_log(3, "%p: %s: %s: buf = %p, buf_len is %d!\n", v8, "SPRD_CE", "sprd_rng_gen", v18, v17);
      }
LABEL_6:
      if ( v18 != nullptr )
        sprd_crypto_free_buf((__int64)v18);
      sprd_semaphore_destroy(v6);
      sprd_crypto_lock_deinit((int *)v19);
      return v5;
    }
    else
    {
      return 4294901770LL;
    }
  }
}

/* ===== sprd_dma_irq_handler @ 0x9403C1CC size 436 ===== */
__int64 sprd_dma_irq_handler()
{
  int v0; // w23
  int v1; // w0
  int v2; // w2
  int v3; // w2
  __int64 v4; // x19
  unsigned int v5; // w2
  unsigned int v6; // w3
  __int64 v7; // x1
  int v8; // w4
  unsigned __int64 v9; // x4
  int v10; // w5

  v0 = *(_DWORD *)(MEMORY[0xFFFFFFFFE0061EC0] + 20LL);
  if ( v0 == 0 )
    return 0;
  while ( 1 )
  {
    v1 = v0;
    v2 = 32;
    if ( (v0 & 0xFFFF0000) == 0 )
    {
      v1 = v0 << 16;
      v2 = 16;
    }
    if ( (v1 & 0xFF000000) == 0 )
    {
      v1 <<= 8;
      v2 -= 8;
    }
    if ( (v1 & 0xF0000000) == 0 )
    {
      v1 *= 16;
      v2 -= 4;
    }
    if ( (v1 & 0xC0000000) == 0 )
    {
      v1 *= 4;
      v2 -= 2;
    }
    v3 = v2 - (v1 >= 0);
    if ( v3 <= 28 )
      break;
    v0 &= v0 - 1;
    v5 = v3 - 29;
    v4 = v5;
    v6 = 16;
    v7 = *(_QWORD *)(80LL * v5 - 536469792);
    v8 = *(_DWORD *)(v7 + 12);
    if ( (v8 & 0x100000) != 0 || (v6 = 8, (v8 & 0x80000) != 0) )
    {
      v9 = ((unsigned __int64)*(unsigned int *)(v7 + 24) >> 24) & 3;
    }
    else
    {
      v6 = 4;
      if ( (v8 & 0x40000) == 0 )
      {
        v6 = 2;
        if ( (v8 & 0x20000) == 0 )
        {
          if ( (v8 & 0x10000) == 0 )
          {
            v6 = 0;
            v10 = 0;
            v9 = ((unsigned __int64)*(unsigned int *)(v7 + 24) >> 24) & 3;
            goto LABEL_14;
          }
          v6 = 1;
        }
      }
      v9 = ((unsigned __int64)*(unsigned int *)(v7 + 24) >> 24) & 3;
      if ( 1 << (HIBYTE(*(_DWORD *)(v7 + 24)) & 3) > v6 )
      {
        v10 = 0;
        goto LABEL_14;
      }
    }
    v10 = 1;
LABEL_14:
    *(_DWORD *)(80LL * v5 - 536469752) = v10;
    *(_DWORD *)(v7 + 12) = 520093696;
    sprd_log(2, "DMA [%d] irq,int_type=%d,req_type=%d!\n", v5, v6, v9);
    if ( *(_DWORD *)(80 * v4 - 536469752) != 0 && *(_QWORD *)(80 * (v4 + 1) - 536469824) != 0 )
      (*(void (__fastcall **)(_QWORD))(80 * (v4 + 1) - 536469824))(*(_QWORD *)(80 * (v4 + 1) - 536469816));
    if ( v0 == 0 )
      return 0;
  }
  sprd_log(2, "DMA %d is not security channel!\n", v3);
  return 0;
}

/* ===== sprd_dma_init @ 0x9403C380 size 256 ===== */
__int64 sprd_dma_init()
{
  memset(-536469824, 0, 336);
  memset(-536472904, 0, 3080);
  if ( (unsigned int)sprd_iomap("sprd-dma", 537919488, 12288, 2, -536469824) != 0 )
    return sprd_log(2, "%s: mem map failed %d\n");
  MEMORY[0xFFFFFFFFE0061F30] = MEMORY[0xFFFFFFFFE0061EC0] + 5952LL;
  MEMORY[0xFFFFFFFFE0061EE0] = MEMORY[0xFFFFFFFFE0061EC0] + 5888LL;
  MEMORY[0xFFFFFFFFE0061ED0] = 28;
  MEMORY[0xFFFFFFFFE0061F80] = MEMORY[0xFFFFFFFFE0061EC0] + 6016LL;
  MEMORY[0xFFFFFFFFE0061F20] = 29;
  MEMORY[0xFFFFFFFFE0061F70] = 30;
  MEMORY[0xFFFFFFFFE0061FD0] = MEMORY[0xFFFFFFFFE0061EC0] + 6080LL;
  MEMORY[0xFFFFFFFFE0061FC0] = 31;
  MEMORY[0xFFFFFFFFE0061EC8] = 4;
  irq_register(84, sprd_dma_irq_handler, 0);
  irq_enable(0x54u);
  return sprd_log(2, "sprd dma init ok!\n");
}

/* ===== efuse_set_bits @ 0x9403C480 size 92 ===== */
__int64 __fastcall efuse_set_bits(__int64 a1, int a2)
{
  unsigned int v3; // w20
  __int64 result; // x0
  int v5; // [xsp+2Ch] [xbp+2Ch] BYREF

  v3 = a1;
  result = ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(a1, &v5);
  if ( (_DWORD)result == 0 )
  {
    result = 0;
    if ( (a2 & ~v5) != 0 )
    {
      if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, _QWORD))loc_9403D3C4)(v3, a2 & (unsigned int)~v5) != 0 )
        return 4294901762LL;
      else
        return 0;
    }
  }
  return result;
}

/* ===== efuse_lock @ 0x9403C4DC size 116 ===== */
__int64 __fastcall efuse_lock(unsigned int a1, unsigned int a2)
{
  unsigned int v2; // w2
  int v4; // w0

  v2 = -65535;
  if ( a1 <= a2 )
  {
    v4 = ((__int64 (*)(void))loc_9403CFA8)();
    v2 = -65531;
    if ( v4 == 0 )
      return 0;
  }
  return v2;
}

/* ===== efuse_write_bits @ 0x9403C550 size 128 ===== */
__int64 __fastcall efuse_write_bits(__int64 a1, int a2)
{
  unsigned int v3; // w19
  unsigned int v4; // w1
  int v6; // w0
  int v7; // [xsp+28h] [xbp+28h] BYREF
  int v8; // [xsp+2Ch] [xbp+2Ch] BYREF

  v3 = a1;
  v8 = 0;
  v7 = 0;
  if ( (unsigned int)((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(a1, &v8) != 0 )
    return (unsigned int)-65533;
  v6 = efuse_set_bits(v3, a2);
  v4 = -65534;
  if ( v6 != 0 )
    return v4;
  if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v3, &v7) != 0 )
  {
    return (unsigned int)-65533;
  }
  else if ( (a2 | v8) == v7 )
  {
    return 0;
  }
  else
  {
    return (unsigned int)-65532;
  }
}

/* ===== efuse_write_blocks @ 0x9403C5D0 size 232 ===== */
__int64 __fastcall efuse_write_blocks(unsigned int a1, unsigned int a2, int *a3)
{
  unsigned int v6; // w19
  int v7; // w22
  int v9; // [xsp+58h] [xbp+58h] BYREF
  int v10; // [xsp+5Ch] [xbp+5Ch] BYREF

  if ( a2 < a1 )
    return efuse_lock(a1, a2);
  v6 = a1;
  while ( 1 )
  {
    v7 = *a3;
    v9 = 0;
    v10 = 0;
    if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v6, &v10) != 0 )
      return 4294901763LL;
    if ( (unsigned int)efuse_set_bits(v6, v7) != 0 )
      return 4294901762LL;
    if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v6, &v9) != 0 )
      return 4294901763LL;
    if ( (v7 | v10) != v9 )
      break;
    ++v6;
    ++a3;
    if ( v6 > a2 )
      return efuse_lock(a1, a2);
  }
  return 4294901764LL;
}

/* ===== efuse_init @ 0x9403C6B8 size 96 ===== */
__int64 efuse_init()
{
  __int64 result; // x0
  int v1; // [xsp+18h] [xbp+18h] BYREF
  int v2; // [xsp+1Ch] [xbp+1Ch] BYREF

  ((void (*)(void))loc_9403CF84)();
  v1 = 0;
  v2 = 0;
  result = ((__int64 (__fastcall *)(_QWORD, __int64, int *, int *))loc_9403CFA8)(0, 7, &v1, &v2);
  if ( (_DWORD)result == 0 && (v1 == 0 || (_DWORD)(result = efuse_set_bits(34, v1)) == 0) && v2 != 0 )
    return efuse_set_bits(35, v2);
  return result;
}

/* ===== efuse_set_block_bits @ 0x9403C718 size 168 ===== */
__int64 __fastcall efuse_set_block_bits(int *a1)
{
  int *v1; // x20
  unsigned int v2; // w19
  int v3; // w21
  __int64 result; // x0
  int v5; // [xsp+3Ch] [xbp+3Ch] BYREF

  v1 = a1;
  if ( a1 == nullptr )
    return 4294901761LL;
  v2 = 8;
  while ( 1 )
  {
    v3 = *v1++;
    result = ((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v2, &v5);
    if ( (_DWORD)result != 0 )
      break;
    if ( (v3 & ~v5) != 0
      && (unsigned int)((__int64 (__fastcall *)(_QWORD, _QWORD))loc_9403D3C4)(v2, v3 & (unsigned int)~v5) != 0 )
    {
      return 4294901762LL;
    }
    if ( ++v2 == 16 )
      return efuse_lock(8u, 0xFu);
  }
  return result;
}

/* ===== efuse_set_secure_bits @ 0x9403C7C0 size 28 ===== */
__int64 __fastcall efuse_set_secure_bits(int *a1)
{
  if ( a1 != nullptr )
    return efuse_write_blocks(0x19u, 0x20u, a1);
  else
    return 4294901761LL;
}

/* ===== efuse_lock_secure @ 0x9403C7DC size 80 ===== */
__int64 efuse_lock_secure()
{
  __int64 result; // x0
  int v1; // [xsp+1Ch] [xbp+1Ch] BYREF

  result = ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(33, &v1);
  if ( (_DWORD)result == 0 )
  {
    result = 0;
    if ( (~(_BYTE)v1 & 2) != 0 )
    {
      if ( (unsigned int)((__int64 (__fastcall *)(__int64, _QWORD))loc_9403D3C4)(33, ~(_BYTE)v1 & 2) != 0 )
        return 4294901762LL;
      else
        return 0;
    }
  }
  return result;
}

/* ===== efuse_read_version @ 0x9403C82C size 176 ===== */
__int64 __fastcall efuse_read_version(int a1, _DWORD *a2)
{
  unsigned int v3; // w19
  int v4; // w21
  __int64 result; // x0
  int v6; // w0
  int i; // w2
  int v8; // [xsp+3Ch] [xbp+3Ch] BYREF

  if ( a2 == nullptr )
    return 4294901761LL;
  if ( a1 == 0 )
    return ((__int64 (__fastcall *)(__int64))loc_9403CFF8)(24);
  if ( a1 != 1 )
    return 4294901761LL;
  v3 = 36;
  v4 = 0;
  while ( 1 )
  {
    result = ((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v3, &v8);
    if ( (_DWORD)result != 0 )
      break;
    v6 = v8;
    for ( i = 0; v6 != 0; v6 &= v6 - 1 )
      ++i;
    ++v3;
    v4 += i;
    if ( v3 == 43 )
    {
      *a2 = v4;
      return 0;
    }
  }
  return result;
}

/* ===== efuse_write_version @ 0x9403C8DC size 296 ===== */
__int64 __fastcall efuse_write_version(int a1, unsigned int a2)
{
  __int64 result; // x0
  unsigned int v4; // w19
  unsigned int v5; // w20
  int v6; // w21
  unsigned __int64 v7; // x21
  bool v8; // zf
  int v9; // [xsp+58h] [xbp+58h] BYREF
  int v10; // [xsp+5Ch] [xbp+5Ch] BYREF

  result = 4294901761LL;
  v4 = a2;
  if ( a2 != 0 )
  {
    if ( a1 != 0 )
    {
      if ( a1 == 1 && a2 <= 0xDF )
      {
        v5 = 36;
        while ( 1 )
        {
          if ( v4 > 0x20 )
            v6 = 32;
          else
            v6 = v4;
          v4 -= v6;
          v9 = 0;
          v10 = 0;
          if ( (unsigned int)((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v5, &v10) != 0 )
            return 4294901763LL;
          v7 = 0xFFFFFFFFuLL >> (32 - (unsigned __int8)v6);
          if ( (unsigned int)efuse_set_bits(v5, v7) != 0 )
            return 4294901762LL;
          result = ((__int64 (__fastcall *)(_QWORD, int *))loc_9403CFF8)(v5, &v9);
          if ( (_DWORD)result != 0 )
            return 4294901763LL;
          if ( (v10 | (unsigned int)v7) != v9 )
            break;
          v8 = v5++ == 42;
          if ( v8 || v4 == 0 )
            return result;
        }
        return 4294901764LL;
      }
    }
    else
    {
      return efuse_write_bits(24, a2);
    }
  }
  return result;
}

/* ===== efuse_read_lock_status @ 0x9403CA04 size 28 ===== */
__int64 efuse_read_lock_status()
{
  char v1; // [xsp+1Ch] [xbp+1Ch] BYREF

  return ((__int64 (__fastcall *)(__int64, char *))loc_9403CFF8)(33, &v1);
}

/* ===== efuse_get_lcs @ 0x9403CA20 size 392 ===== */
__int64 __fastcall efuse_get_lcs(_DWORD *a1)
{
  __int64 result; // x0
  _DWORD *v3; // x19
  int v4; // w0
  int v5; // w1
  int v6; // [xsp+2Ch] [xbp+2Ch] BYREF
  int v7; // [xsp+30h] [xbp+30h] BYREF
  int v8; // [xsp+34h] [xbp+34h] BYREF
  int v9; // [xsp+38h] [xbp+38h] BYREF
  int v10; // [xsp+3Ch] [xbp+3Ch] BYREF
  int v11; // [xsp+40h] [xbp+40h] BYREF
  int v12; // [xsp+44h] [xbp+44h] BYREF
  int v13; // [xsp+48h] [xbp+48h] BYREF
  int v14; // [xsp+4Ch] [xbp+4Ch] BYREF

  result = 4294901761LL;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  if ( a1 != nullptr )
  {
    v3 = a1;
    result = ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(34, &v6);
    if ( (_DWORD)result == 0 )
    {
      if ( v6 == 0 )
        *v3 = 0;
      ((void (__fastcall *)(_QWORD, __int64, int *, int *))loc_9403CFA8)(0, 7, &v8, &v9);
      ((void (__fastcall *)(__int64, __int64, int *, int *))loc_9403CFA8)(16, 23, &v10, &v11);
      ((void (__fastcall *)(__int64, __int64, int *, int *))loc_9403CFA8)(25, 32, &v12, &v13);
      if ( v8 == (v8 & v6) )
        *v3 = 1;
      if ( v9 != 0 || v11 != 0 || v13 != 0 )
        ((void (__fastcall *)(__int64, int *))loc_9403CFF8)(35, &v7);
      v14 = 0;
      result = ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(33, &v14);
      if ( (_DWORD)result == 0 )
      {
        if ( (v14 & 2) != 0 )
        {
          if ( (v12 | v8) != ((v12 | v8) & v6) )
            goto LABEL_13;
          v4 = v9;
          v5 = v13;
        }
        else
        {
          if ( (v10 | v8) != ((v10 | v8) & v6) )
          {
LABEL_13:
            v14 = 0;
            return ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(33, &v14);
          }
          v4 = v9;
          v5 = v11;
        }
        if ( (v5 | v4) == ((v5 | v4) & v7) )
          *v3 = 5;
        goto LABEL_13;
      }
    }
  }
  return result;
}

/* ===== efuse_read_blocks @ 0x9403CBA8 size 136 ===== */
__int64 __fastcall efuse_read_blocks(unsigned int a1, unsigned int a2, __int64 a3)
{
  unsigned int v3; // w19
  __int64 result; // x0
  __int64 v6; // x0
  __int64 v7; // [xsp+28h] [xbp+28h]

  v3 = a1;
  if ( a3 == 0 || a1 <= 0xF || a2 <= 0xF )
    return 4294901761LL;
  if ( a1 > a2 )
    return 0;
  while ( 1 )
  {
    v6 = v3++;
    v7 = a3 + 4;
    result = ((__int64 (__fastcall *)(__int64, __int64))loc_9403CFF8)(v6, a3);
    if ( (_DWORD)result != 0 )
      break;
    a3 = v7;
    if ( a2 < v3 )
      return 0;
    if ( v7 == 0 )
      return 4294901766LL;
  }
  return result;
}

/* ===== efuse_read_secure_blocks @ 0x9403CC30 size 16 ===== */
__int64 __fastcall efuse_read_secure_blocks(__int64 a1)
{
  return efuse_read_blocks(0x10u, 0x17u, a1);
}

/* ===== efuse_read_ns_blocks @ 0x9403CC40 size 16 ===== */
__int64 __fastcall efuse_read_ns_blocks(__int64 a1)
{
  return efuse_read_blocks(0x19u, 0x20u, a1);
}

/* ===== efuse_is_secure @ 0x9403CC50 size 60 ===== */
__int64 __fastcall efuse_is_secure(_DWORD *a1)
{
  __int64 result; // x0
  int v3; // [xsp+2Ch] [xbp+2Ch] BYREF

  v3 = 0;
  result = ((__int64 (__fastcall *)(__int64, int *))loc_9403CFF8)(33, &v3);
  if ( (_DWORD)result == 0 )
    *a1 = (v3 & 2) != 0;
  return result;
}

/* ===== sprd_sec_hw_init @ 0x9403CC8C size 4 ===== */
// attributes: thunk
void sprd_sec_hw_init(void)
{
  JUMPOUT(0x9403D464LL);
}

/* ===== sprd_sec_hw_deinit @ 0x9403CC90 size 2308 ===== */
__int64 sprd_sec_hw_deinit()
{
  unsigned int v1; // [xsp+7Ch] [xbp-4h] BYREF

  sprd_spin_lock_irqsave(&qword_94067AF0, &v1, 3221225472LL);
  return sprd_spin_unlock_irqrestore(&qword_94067AF0, v1, 3221225472LL);
}

/* ===== efuse_write_drv @ 0x9403D594 size 420 ===== */
__int64 __fastcall efuse_write_drv(unsigned int a1, unsigned int a2, __int64 a3, int a4)
{
  int v6; // w0
  __int64 v7; // x2
  unsigned int v9; // w0
  unsigned int i; // w0
  unsigned int v11; // w3
  __int64 v12; // x1
  unsigned int v13; // w19
  int v14; // w3
  int v16; // [xsp+30h] [xbp+30h]
  __int64 v18; // [xsp+38h] [xbp+38h]

  v6 = sprd_mutex_lock(0);
  v7 = a3;
  if ( v6 != 0 )
    return 2;
  v16 = a4;
  v18 = v7;
  ((void (*)(void))loc_9403D46C)();
  MEMORY[0x4C] = 34832;
  MEMORY[0x40] |= 0x10u;
  MEMORY[0x54] |= 4u;
  MEMORY[0x54] &= ~2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 1u;
  thread_sleep_ms(1u);
  MEMORY[0x40] |= 2u;
  if ( v16 != 0 )
    v9 = MEMORY[0x40] | 4;
  else
    v9 = MEMORY[0x40] & 0xFFFFFFFB;
  MEMORY[0x40] = v9;
  for ( i = a1; a2 >= i; *(_DWORD *)(v12 + 4096) = *(_DWORD *)(v18 + 4LL * v11) )
  {
    v11 = i - a1;
    v12 = 4LL * (i++ & 0x3FFFFFFF);
  }
  if ( MEMORY[0x44] != 0 )
  {
    v14 = a1;
    v13 = 2;
    sprd_log(2, "efuse_write_drv(): err = %x start_id = %d end_id = %d\n", MEMORY[0x44], v14, a2);
  }
  else
  {
    v13 = 0;
  }
  MEMORY[0x54] &= ~1u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] &= ~4u;
  MEMORY[0x40] &= ~0x10u;
  MEMORY[0x4C] = 0;
  ((void (*)(void))loc_9403D4F8)();
  if ( (unsigned int)sprd_mutex_unlock(0) != 0 )
    return 2;
  else
    return v13;
}

/* ===== efuse_read_drv @ 0x9403D738 size 248 ===== */
__int64 __fastcall efuse_read_drv(unsigned int a1, unsigned int a2, __int64 a3, int a4)
{
  unsigned int v9; // w0
  unsigned int i; // w0
  __int64 v11; // x3
  unsigned int v12; // w1
  unsigned int v13; // w19
  int v14; // w3

  if ( (unsigned int)sprd_mutex_lock(0) != 0 )
    return 1;
  ((void (*)(void))loc_9403D46C)();
  if ( a4 != 0 )
    v9 = MEMORY[0x40] | 4;
  else
    v9 = MEMORY[0x40] & 0xFFFFFFFB;
  MEMORY[0x40] = v9;
  for ( i = a1; a2 >= i; *(_DWORD *)(a3 + 4LL * v12) = *(_DWORD *)(v11 + 4096) )
  {
    v11 = 4LL * (i & 0x3FFFFFFF);
    v12 = i - a1;
    ++i;
  }
  if ( MEMORY[0x44] != 0 )
  {
    v14 = a1;
    v13 = 1;
    sprd_log(2, "efuse_read_drv(): err = %x start_id = %d end_id = %d\n", MEMORY[0x44], v14, a2);
  }
  else
  {
    v13 = 0;
  }
  ((void (*)(void))loc_9403D4F8)();
  if ( (unsigned int)sprd_mutex_unlock(0) != 0 )
    return 1;
  else
    return v13;
}

/* ===== efuse_rewrite_double_bit @ 0x9403D830 size 324 ===== */
__int64 __fastcall efuse_rewrite_double_bit(int a1, int a2)
{
  unsigned int v4; // w19

  if ( (unsigned int)sprd_mutex_lock(0) != 0 )
    return 2;
  ((void (*)(void))loc_9403D46C)();
  v4 = 0;
  MEMORY[0x4C] = 34832;
  MEMORY[0x54] |= 4u;
  MEMORY[0x54] &= ~2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 1u;
  thread_sleep_ms(1u);
  MEMORY[0x40] &= ~2u;
  MEMORY[0x40] |= 4u;
  *(_DWORD *)(4LL * (a1 & 0x3FFFFFFF) + 0x1000) = a2;
  if ( MEMORY[0x44] != 0 )
  {
    v4 = 2;
    sprd_log(2, "efuse_rewrite_double_bit(): err = %x block_id = %d\n", MEMORY[0x44], a1);
  }
  MEMORY[0x54] &= ~1u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] &= ~4u;
  MEMORY[0x4C] = 0;
  ((void (*)(void))loc_9403D4F8)();
  if ( (unsigned int)sprd_mutex_unlock(0) != 0 )
    return 2;
  else
    return v4;
}

/* ===== efuse_huk_program @ 0x9403D974 size 408 ===== */
__int64 efuse_huk_program()
{
  unsigned int v1; // w19

  if ( (unsigned int)sprd_mutex_lock(0) != 0 )
    return 2;
  ((void (*)(void))loc_9403D46C)();
  MEMORY[0x4C] = 34832;
  MEMORY[0x40] |= 0x10u;
  MEMORY[0x54] |= 4u;
  MEMORY[0x54] &= ~2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 1u;
  thread_sleep_ms(1u);
  MEMORY[0x40] |= 2u;
  MEMORY[0x40] |= 4u;
  MEMORY[0x3038] |= 1u;
  MEMORY[0x18] = 32;
  MEMORY[0x200] = 3;
  MEMORY[0x340] |= 0x80000000;
  while ( (MEMORY[0x340] & 0x80000000) != 0 )
    ;
  MEMORY[0x200] = 0;
  v1 = 0;
  MEMORY[0x18] = 0;
  MEMORY[0x3038] &= ~1u;
  if ( MEMORY[0x44] != 0 )
  {
    v1 = 2;
    sprd_log(2, "efuse_huk_program(): err = %x\n", MEMORY[0x44]);
  }
  MEMORY[0x54] &= ~1u;
  thread_sleep_ms(1u);
  MEMORY[0x54] |= 2u;
  thread_sleep_ms(1u);
  MEMORY[0x54] &= ~4u;
  MEMORY[0x40] &= ~0x10u;
  MEMORY[0x4C] = 0;
  ((void (*)(void))loc_9403D4F8)();
  if ( (unsigned int)sprd_mutex_unlock(0) != 0 )
    return 2;
  else
    return v1;
}

/* ===== fp_driver_register @ 0x9403DC08 size 76 ===== */
__int64 fp_driver_register()
{
  __int64 result; // x0

  result = trusty_install_handler(7u, (__int64)qword_9405C718);
  if ( (_DWORD)result != 0 && MEMORY[0xFFFFFFFFE003CB98] > 1 )
    return log_printf("fp_driver can not install std in handler: %d\n", result);
  return result;
}

/* ===== sprd_fp_default_init @ 0x9403DC54 size 240 ===== */
__int64 __fastcall sprd_fp_default_init(int a1, char a2, char a3, char a4, unsigned __int8 a5)
{
  __int64 v9; // x0
  unsigned int v10; // w19

  v9 = fp_spi_get_ctrl(a5);
  MEMORY[0xFFFFFFFFE0062010] = v9;
  if ( v9 != 0 )
  {
    *(_DWORD *)v9 = a1;
    *(_BYTE *)(v9 + 4) = a2;
    *(_BYTE *)(v9 + 5) = a3;
    *(_BYTE *)(v9 + 6) = a4;
    if ( MEMORY[0xFFFFFFFFE0047B28] != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      log_printf((const char *)&loc_94053648);
    v10 = spi_setup_wrap(MEMORY[0xFFFFFFFFE0062010]);
    if ( MEMORY[0xFFFFFFFFE0047B28] != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      log_printf("fp_driver after spi_setup ret:%d\n", v10);
  }
  else
  {
    v10 = -1;
    if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
      log_printf((const char *)&loc_94053608);
  }
  return v10;
}

/* ===== fp_driver_ioctl @ 0x9403DD44 size 1088 ===== */
__int64 __fastcall fp_driver_ioctl(__int64 a1, int a2, unsigned int a3)
{
  __int64 v4; // x21
  __int64 v5; // x0
  int v6; // w19
  __int64 v7; // x0
  __int64 v8; // x19
  __int64 v9; // x22
  int v10; // w21
  int v12; // [xsp+30h] [xbp+30h] BYREF
  unsigned __int8 v13; // [xsp+34h] [xbp+34h]
  unsigned __int8 v14; // [xsp+35h] [xbp+35h]
  unsigned __int8 v15; // [xsp+36h] [xbp+36h]
  unsigned __int8 v16; // [xsp+37h] [xbp+37h]
  unsigned int v17; // [xsp+38h] [xbp+38h]
  unsigned int v18; // [xsp+3Ch] [xbp+3Ch]
  unsigned int v19; // [xsp+40h] [xbp+40h]
  char v20; // [xsp+44h] [xbp+44h]
  _QWORD v21[3]; // [xsp+48h] [xbp+48h] BYREF

  if ( a3 == 0 )
    return 4294967288LL;
  switch ( a2 )
  {
    case 0:
      copy_from_user(&v12, a3, 24);
      MEMORY[0xFFFFFFFFE0047B28] = v20;
      if ( v20 != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf((const char *)&loc_94053690, v13, v14, v15, v16, v19);
      v6 = sprd_fp_default_init(v12, v13, v14, v15, v16);
      if ( MEMORY[0xFFFFFFFFE0047B28] != 0 )
      {
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
        {
          if ( v6 != 0 )
            return 0xFFFFFFFFLL;
          goto LABEL_34;
        }
        log_printf("fp_driver after sprd_fp_default_init\n");
      }
      if ( v6 == 0 )
      {
LABEL_34:
        v7 = malloc(v19);
        v8 = v7;
        if ( v7 == 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("malloc txbuf error\n");
          return 4294967291LL;
        }
        copy_from_user(v7, v18, v19);
        v9 = malloc(v19);
        if ( v9 == 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf("malloc rxbuf error\n");
          free(v8);
          return 4294967291LL;
        }
        v21[0] = v8;
        v21[1] = v9;
        v21[2] = v19;
        if ( MEMORY[0xFFFFFFFFE0047B28] != 0 && (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf((const char *)fp_spi_sync_stub);
        v10 = spi_sync_wrap(MEMORY[0xFFFFFFFFE0062010], v21);
        if ( MEMORY[0xFFFFFFFFE0047B28] != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
          {
            if ( v10 != 0 )
            {
LABEL_45:
              free(v8);
              free(v9);
              return 0xFFFFFFFFLL;
            }
LABEL_52:
            copy_to_user(v17, v9, v19);
            free(v8);
            free(v9);
            return 0;
          }
          log_printf("fp_driver after spi_sync ret:%d\n", v10);
        }
        if ( v10 != 0 )
        {
          if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
            log_printf((const char *)&loc_940537B8);
          goto LABEL_45;
        }
        goto LABEL_52;
      }
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
        return 0xFFFFFFFFLL;
      log_printf((const char *)&loc_94053718);
      return 0xFFFFFFFFLL;
    case 1:
      copy_from_user(-536577244, a3, 4);
      return 0;
    case 2:
      copy_to_user(a3, -536577244, 4);
      return 0;
    case 3:
      if ( MEMORY[0xFFFFFFFFE0062020] != 0 )
      {
        free(MEMORY[0xFFFFFFFFE0062020]);
        MEMORY[0xFFFFFFFFE0062020] = 0;
      }
      MEMORY[0xFFFFFFFFE0062018] = 0;
      copy_from_user(-536469480, a3, 4);
      v4 = (unsigned int)(4 * MEMORY[0xFFFFFFFFE0062018]);
      if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
        log_printf("IFAA_SET_FP_ENROLLED_ID_LIST--> list_num = %d, fps_len = %d\n", MEMORY[0xFFFFFFFFE0062018], v4);
      v5 = malloc(v4);
      MEMORY[0xFFFFFFFFE0062020] = v5;
      if ( v5 != 0 )
      {
        memset(v5, 0, v4);
        copy_from_user(MEMORY[0xFFFFFFFFE0062020], a3 + 4, v4);
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
          log_printf("IFAA_SET_FP_ENROLLED_ID_LIST--> id[0] = 0x%x\n", *MEMORY[0xFFFFFFFFE0062020]);
        return 0;
      }
      else
      {
        if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) != 0 )
          return 0xFFFFFFFFLL;
        log_printf("IFAA_SET_FP_ENROLLED_ID_LIST malloc failed.\n");
        return 0xFFFFFFFFLL;
      }
    case 4:
      if ( MEMORY[0xFFFFFFFFE0062020] == 0 )
        return 0xFFFFFFFFLL;
      copy_to_user(a3, -536469480, 4);
      copy_to_user(a3 + 4, MEMORY[0xFFFFFFFFE0062020], 4LL * MEMORY[0xFFFFFFFFE0062018]);
      return 0;
    case 5:
      copy_from_user(-536469464, a3, 136);
      return 0;
    case 6:
      copy_to_user(a3, -536469464, 136);
      return 0;
    case 7:
      copy_from_user(-536577248, a3, 2);
      return 0;
    case 8:
      copy_to_user(a3, -536577248, 2);
      return 0;
    default:
      return 4294967272LL;
  }
}

/* ===== sprd_pal_fw_init @ 0x9403E184 size 292 ===== */
__int64 sprd_pal_fw_init()
{
  __int64 v0; // x0
  __int64 v1; // x0
  __int64 v2; // x0
  const void *v3; // x0
  __int64 v4; // x0
  const void *v6; // x0
  const void *v7; // x0
  int v8; // [xsp+18h] [xbp+18h]
  int v9; // [xsp+18h] [xbp+18h]
  int v10; // [xsp+18h] [xbp+18h]
  __int64 v11; // [xsp+20h] [xbp+20h] BYREF
  __int64 v12; // [xsp+28h] [xbp+28h] BYREF

  v0 = trusty_install_handler(6u, (__int64)qword_9405C730);
  if ( (_DWORD)v0 != 0 )
  {
    v10 = v0;
    v7 = (const void *)get_current_thread(v0);
    sprd_log(3, "%p: %s: %s: failed to install firewall handler: %d\n", v7, "SPRD_FW", "sprd_pal_fw_init", v10);
  }
  v1 = sprd_iomap("sprd_fw_iram", 57344, 0x2000, 2, &v11);
  if ( (_DWORD)v1 != 0 )
  {
    v9 = v1;
    v6 = (const void *)get_current_thread(v1);
    sprd_log(3, "%p: %s: %s: map sprd_fw_iram failed[0x%x]\n", v6, "SPRD_FW", "sprd_pal_fw_init", v9);
  }
  v11 += 3072;
  v2 = sprd_iomap("sprd_fw", 838926336, 0x10000, 2, &v12);
  if ( (_DWORD)v2 != 0 )
  {
    v8 = v2;
    v3 = (const void *)get_current_thread(v2);
    sprd_log(3, "%p: %s: %s: map fw_vaddr failed[0x%x]\n", v3, "SPRD_FW", "sprd_pal_fw_init", v8);
  }
  v4 = tzfw_init(v12, v11);
  return sprd_fw_config_default(v4);
}

/* ===== sprd_fw_save_config @ 0x9403E2A8 size 32 ===== */
__int64 sprd_fw_save_config()
{
  __int64 result; // x0

  result = arch_curr_cpu_num();
  if ( (_DWORD)result == 0 )
    return sprd_fw_save_config_all();
  return result;
}

/* ===== sprd_fw_restore_config @ 0x9403E2C8 size 32 ===== */
__int64 sprd_fw_restore_config()
{
  __int64 result; // x0

  result = arch_curr_cpu_num();
  if ( (_DWORD)result == 0 )
    return sprd_fw_restore_config_all();
  return result;
}

/* ===== sprd_fw_lock_cp @ 0x9403E2E8 size 184 ===== */
__int64 __fastcall sprd_fw_lock_cp(__int64 a1, int a2)
{
  unsigned int v2; // w19
  __int64 v4; // x0
  __int64 v5; // x2
  __int64 v6; // x0
  __int64 v7; // x2

  if ( a2 == 1 )
  {
    v6 = sprd_recreate_cp_modem();
    v2 = v6;
    if ( (_DWORD)v6 == 0 )
      return v2;
    v7 = get_current_thread(v6);
    sprd_log(3, "%p: %s: %s: lock CP error. res = 0x%x\n", v7, "SPRD_FW", &loc_940540D8, v2);
    return v2;
  }
  if ( a2 == 0 )
  {
    v4 = sprd_destroy_cp_modem();
    v2 = v4;
    if ( (_DWORD)v4 == 0 )
      return v2;
    v5 = get_current_thread(v4);
    sprd_log(3, "%p: %s: %s: unlock CP error. res = 0x%x\n", v5, "SPRD_FW", &loc_940540D8, v2);
    return v2;
  }
  if ( a2 != 2 )
    return (unsigned int)-24;
  sprd_fw_lock();
  return 0;
}

/* ===== sprd_fw_null @ 0x9403E3A0 size 8 ===== */
__int64 sprd_fw_null()
{
  return 0;
}

/* ===== sprd_fw_config_default @ 0x9403E3A8 size 416 ===== */
__int64 sprd_fw_config_default()
{
  __int64 v0; // x0
  unsigned int v1; // w19
  __int64 v2; // x0
  __int64 v3; // x0
  unsigned int v4; // w19
  __int64 v5; // x0
  const void *v7; // x0
  __int64 v8; // x0
  const void *v9; // x0
  __int64 v10; // x0
  __int64 v11; // x2
  __int64 v12; // x0
  const void *v13; // x0
  __int64 v14; // x0
  __int64 v15; // x2
  _QWORD v16[10]; // [xsp+20h] [xbp+20h] BYREF

  sprd_fw_lock2();
  v0 = tzfw_cfg_slv_fw(3, 275, 1, 1);
  v1 = v0;
  if ( (_DWORD)v0 != 0 )
  {
    v7 = (const void *)get_current_thread(v0);
    v8 = sprd_log(
           3,
           "%p: %s: %s: config SLV_FW_AP SLV_ID_SCE Error(0x%x)!\n",
           v7,
           "SPRD_FW",
           "sprd_config_default_slave_fw",
           v1);
    v9 = (const void *)get_current_thread(v8);
    v10 = sprd_log(
            3,
            "%p: %s: %s: config default slave fw failed(0x%x)!\n",
            v9,
            "SPRD_FW",
            "sprd_fw_config_default",
            v1);
    sprd_fw_unlock(v10);
    return v1;
  }
  else
  {
    v2 = virt_to_phys(-536465408);
    v3 = tzfw_cfg_dft_addr(10, v2);
    v4 = v3;
    if ( (_DWORD)v3 != 0 )
    {
      v11 = get_current_thread(v3);
      v12 = sprd_log(
              3,
              "%p: %s: %s: config default addr Error(0x%x)!\n",
              v11,
              "SPRD_FW",
              "sprd_config_default_memory_fw",
              v4);
    }
    else
    {
      v16[1] = 2516582399LL;
      v16[0] = 2483027968LL;
      v16[2] = -1;
      v16[4] = 0;
      v16[6] = -1;
      v16[8] = 0;
      v16[3] = -1;
      v16[5] = 0;
      v16[7] = -1;
      v16[9] = 0;
      v5 = tzfw_cfg_mem_fw_seg(10, 256, v16);
      v4 = v5;
      if ( (_DWORD)v5 == 0 )
      {
        sprd_fw_unlock(v5);
        return 0;
      }
      v15 = get_current_thread(v5);
      v12 = sprd_log(
              3,
              "%p: %s: %s: config region TOS_MEMORY Error(0x%x)!\n",
              v15,
              "SPRD_FW",
              "sprd_config_default_memory_fw",
              v4);
    }
    v13 = (const void *)get_current_thread(v12);
    v14 = sprd_log(
            3,
            "%p: %s: %s: config default memory fw failed(0x%x)!\n",
            v13,
            "SPRD_FW",
            "sprd_fw_config_default",
            v4);
    sprd_fw_unlock(v14);
    return v4;
  }
}

/* ===== sprd_fw_save_config_all @ 0x9403E548 size 216 ===== */
__int64 sprd_fw_save_config_all()
{
  __int64 v0; // x0
  unsigned int v1; // w19
  __int64 v2; // x0
  __int64 v3; // x0
  __int64 v4; // x0
  __int64 v5; // x2
  __int64 v6; // x2
  __int64 v8; // x2
  __int64 v9; // x2

  sprd_fw_lock2();
  v0 = tzfw_save_ap_cfg(1);
  v1 = v0;
  if ( (_DWORD)v0 != 0 )
  {
    v8 = get_current_thread(v0);
    v4 = sprd_log(3, "%p: %s: %s: save MST_CTRL_AP failed(0x%x)!\n", v8, "SPRD_FW", "sprd_fw_save_config", v1);
  }
  else
  {
    v2 = tzfw_save_ap_cfg(3);
    v1 = v2;
    if ( (_DWORD)v2 != 0 )
    {
      v6 = get_current_thread(v2);
      v4 = sprd_log(3, "%p: %s: %s: save SLV_FW_AP failed(0x%x)!\n", v6, "SPRD_FW", "sprd_fw_save_config", v1);
    }
    else
    {
      v3 = tzfw_save_ap_cfg(7);
      v1 = v3;
      if ( (_DWORD)v3 != 0 )
      {
        v9 = get_current_thread(v3);
        v4 = sprd_log(3, "%p: %s: %s: save REG_FW_AP_APB failed(0x%x)!\n", v9, "SPRD_FW", "sprd_fw_save_config", v1);
      }
      else
      {
        v4 = tzfw_save_ap_cfg(8);
        v1 = v4;
        if ( (_DWORD)v4 != 0 )
        {
          v5 = get_current_thread(v4);
          v4 = sprd_log(
                 3,
                 "%p: %s: %s: save REG_FW_AP_AHB failed(0x%x)!\n",
                 v5,
                 "SPRD_FW",
                 "sprd_fw_save_config",
                 v1);
        }
      }
    }
  }
  sprd_fw_unlock(v4);
  return v1;
}

/* ===== sprd_fw_restore_config_all @ 0x9403E620 size 216 ===== */
__int64 sprd_fw_restore_config_all()
{
  __int64 v0; // x0
  unsigned int v1; // w19
  __int64 v2; // x0
  __int64 v3; // x0
  __int64 v4; // x0
  __int64 v5; // x2
  __int64 v6; // x2
  __int64 v8; // x2
  __int64 v9; // x2

  sprd_fw_lock2();
  v0 = tzfw_restore_ap_cfg(1);
  v1 = v0;
  if ( (_DWORD)v0 != 0 )
  {
    v8 = get_current_thread(v0);
    v4 = sprd_log(3, "%p: %s: %s: restore MST_CTRL_AP failed(0x%x)!\n", v8, "SPRD_FW", "sprd_fw_restore_config", v1);
  }
  else
  {
    v2 = tzfw_restore_ap_cfg(3);
    v1 = v2;
    if ( (_DWORD)v2 != 0 )
    {
      v6 = get_current_thread(v2);
      v4 = sprd_log(3, "%p: %s: %s: restore SLV_FW_AP failed(0x%x)!\n", v6, "SPRD_FW", "sprd_fw_restore_config", v1);
    }
    else
    {
      v3 = tzfw_restore_ap_cfg(7);
      v1 = v3;
      if ( (_DWORD)v3 != 0 )
      {
        v9 = get_current_thread(v3);
        v4 = sprd_log(
               3,
               "%p: %s: %s: restore REG_FW_AP_APB failed(0x%x)!\n",
               v9,
               "SPRD_FW",
               "sprd_fw_restore_config",
               v1);
      }
      else
      {
        v4 = tzfw_restore_ap_cfg(8);
        v1 = v4;
        if ( (_DWORD)v4 != 0 )
        {
          v5 = get_current_thread(v4);
          v4 = sprd_log(
                 3,
                 "%p: %s: %s: restore REG_FW_AP_AHB failed(0x%x)!\n",
                 v5,
                 "SPRD_FW",
                 "sprd_fw_restore_config",
                 v1);
        }
      }
    }
  }
  sprd_fw_unlock(v4);
  return v1;
}

/* ===== sprd_fw_lock @ 0x9403E6F8 size 24 ===== */
__int64 sprd_fw_lock()
{
  __int64 v0; // x0
  __int64 v1; // x0

  v0 = sprd_fw_lock2();
  v1 = tzfw_build_table(v0);
  return sprd_fw_unlock(v1);
}

/* ===== sprd_destroy_cp_modem @ 0x9403E710 size 244 ===== */
__int64 sprd_destroy_cp_modem()
{
  __int64 v0; // x0
  unsigned int v1; // w19
  __int64 v2; // x0
  __int64 v3; // x2
  __int64 v5; // x2
  _QWORD v6[10]; // [xsp+20h] [xbp+20h] BYREF

  sprd_fw_lock2();
  memset(v6, 0, 80);
  v6[1] = 0;
  v6[0] = -1;
  v0 = tzfw_cfg_mem_fw_seg(10, 257, v6);
  v1 = v0;
  if ( (_DWORD)v0 != 0 )
  {
    v5 = get_current_thread(v0);
    v2 = sprd_log(
           3,
           "%p: %s: %s: config region CP_MODEM Error(0x%x)!\n",
           v5,
           "SPRD_FW",
           "sprd_destroy_cp_modem",
           v1);
  }
  else
  {
    v2 = tzfw_cfg_slv_fw(2, 74, 3, 3);
    v1 = v2;
    if ( (_DWORD)v2 != 0
      || (v2 = tzfw_cfg_slv_fw(2, 73, 3, 3), v1 = v2, (_DWORD)v2 != 0)
      || (v2 = tzfw_cfg_slv_fw(2, 72, 3, 3), v1 = v2, (_DWORD)v2 != 0) )
    {
      v3 = get_current_thread(v2);
      v2 = sprd_log(
             3,
             "%p: %s: %s: config SLV_FW_AON SLV_ID_SM4_IRAM1 Error(0x%x)!\n",
             v3,
             "SPRD_FW",
             "sprd_destroy_cp_modem",
             v1);
    }
  }
  sprd_fw_unlock(v2);
  return v1;
}

/* ===== sprd_recreate_cp_modem @ 0x9403E804 size 384 ===== */
__int64 sprd_recreate_cp_modem()
{
  unsigned int v0; // w3
  int v1; // w0
  int v2; // w1
  __int64 v3; // x0
  unsigned int v4; // w19
  __int64 v5; // x0
  __int64 v6; // x0
  __int64 v7; // x0
  __int64 v8; // x2
  __int64 v9; // x2
  __int64 v11; // x2
  __int64 v12; // x2
  _QWORD v13[9]; // [xsp+20h] [xbp+20h] BYREF
  unsigned __int64 v14; // [xsp+68h] [xbp+68h]

  sprd_fw_lock2();
  memset(v13, 0, 80);
  v13[8] = 0;
  v13[0] = 2304770048LL;
  v0 = 0;
  v13[1] = 2371616767LL;
  memset(&v13[2], 255, 48);
  v1 = 72;
  v14 = 0;
  do
  {
    v2 = 1 << v1++;
    v0 |= v2;
  }
  while ( v1 != 96 );
  v14 = __PAIR64__(HIDWORD(v14), v0) | 0x3F00000000000000LL;
  v3 = tzfw_cfg_mem_fw_seg(10, 257, v13);
  v4 = v3;
  if ( (_DWORD)v3 != 0 )
  {
    v11 = get_current_thread(v3);
    v7 = sprd_log(
           3,
           "%p: %s: %s: config region CP_MODEM Error(0x%x)!\n",
           v11,
           "SPRD_FW",
           "sprd_recreate_cp_modem",
           v4);
  }
  else
  {
    v5 = tzfw_cfg_slv_fw(2, 74, 3, 1);
    v4 = v5;
    if ( (_DWORD)v5 != 0 )
    {
      v9 = get_current_thread(v5);
      v7 = sprd_log(
             3,
             "%p: %s: %s: config SLV_FW_AON SLV_ID_SM4_IRAM1 Error(0x%x)!\n",
             v9,
             "SPRD_FW",
             "sprd_recreate_cp_modem",
             v4);
    }
    else
    {
      v6 = tzfw_cfg_slv_fw(2, 73, 3, 1);
      v4 = v6;
      if ( (_DWORD)v6 != 0 )
      {
        v12 = get_current_thread(v6);
        v7 = sprd_log(
               3,
               "%p: %s: %s: config SLV_FW_AON SLV_ID_SM4_IRAM2 Error(0x%x)!\n",
               v12,
               "SPRD_FW",
               "sprd_recreate_cp_modem",
               v4);
      }
      else
      {
        v7 = tzfw_cfg_slv_fw(2, 72, 3, 1);
        v4 = v7;
        if ( (_DWORD)v7 != 0 )
        {
          v8 = get_current_thread(v7);
          v7 = sprd_log(
                 3,
                 "%p: %s: %s: config SLV_FW_AON SLV_ID_SM4_IRAM3 Error(0x%x)!\n",
                 v8,
                 "SPRD_FW",
                 "sprd_recreate_cp_modem",
                 v4);
        }
      }
    }
  }
  sprd_fw_unlock(v7);
  return v4;
}

/* ===== tzfw_get_ap_cfg_addr @ 0x9403E984 size 352 ===== */
__int64 __fastcall tzfw_get_ap_cfg_addr(__int64 a1, _QWORD *a2, _QWORD *a3, _DWORD *a4, _QWORD *a5, _DWORD *a6)
{
  const void *v6; // x0
  __int64 result; // x0
  int v8; // [xsp+18h] [xbp+18h]

  switch ( (int)a1 )
  {
    case 1:
      *a2 = 0;
      *a3 = 0;
      *a4 = 0;
      *a5 = 0x8000;
      *a6 = 2;
      result = 0;
      break;
    case 3:
      *a2 = 16;
      *a3 = 28672;
      *a4 = 4;
      *a5 = 28704;
      *a6 = 198;
      result = 0;
      break;
    case 7:
      *a2 = 848;
      *a3 = 0;
      *a4 = 0;
      *a5 = 36864;
      *a6 = 34;
      result = 0;
      break;
    case 8:
      *a2 = 992;
      *a3 = 0;
      *a4 = 0;
      *a5 = 40960;
      *a6 = 36;
      result = 0;
      break;
    default:
      v8 = a1;
      v6 = (const void *)get_current_thread(a1);
      sprd_log(3, "%p: %s: %s: bad fw_id:%d\n", v6, "SPRD_FW", "tzfw_get_ap_cfg_addr", v8);
      result = 4294901761LL;
      break;
  }
  return result;
}

/* ===== tzfw_save_ap_cfg @ 0x9403EAE4 size 264 ===== */
__int64 __fastcall tzfw_save_ap_cfg(__int64 a1)
{
  __int64 v1; // x0
  unsigned int v2; // w19
  _DWORD *v3; // x0
  _DWORD *v4; // x1
  _DWORD *v5; // x2
  _DWORD *v6; // x0
  int i; // w3
  int *v8; // x2
  int j; // w0
  int v10; // t1
  const void *v12; // x0
  int v13; // [xsp+20h] [xbp+20h] BYREF
  int v14; // [xsp+24h] [xbp+24h] BYREF
  _DWORD *v15; // [xsp+28h] [xbp+28h] BYREF
  _DWORD *v16; // [xsp+30h] [xbp+30h] BYREF
  int *v17; // [xsp+38h] [xbp+38h] BYREF

  v1 = tzfw_get_ap_cfg_addr(a1, &v15, &v16, &v13, &v17, &v14);
  v2 = v1;
  if ( (_DWORD)v1 != 0 )
  {
    v12 = (const void *)get_current_thread(v1);
    sprd_log(3, "%p: %s: %s: tzfw_get_ap_cfg_addr Error(%d)\n", v12, "SPRD_FW", "tzfw_save_ap_cfg", v2);
    return v2;
  }
  else
  {
    v3 = v15;
    v4 = ++v15;
    *v3 = 1739273421;
    if ( v13 > 0 )
    {
      v5 = v16;
      v6 = v3 + 2;
      for ( i = 0; i < v13; ++i )
      {
        *(v6 - 1) = *v5++;
        v4 = v6++;
      }
      v15 = v4;
      v16 = v5;
    }
    if ( v14 > 0 )
    {
      v8 = v17;
      for ( j = 0; j < v14; ++j )
      {
        v10 = *v8++;
        *v4++ = v10;
      }
    }
    *v4 = -1145324613;
    return 0;
  }
}

/* ===== tzfw_restore_ap_cfg @ 0x9403EBEC size 364 ===== */
__int64 __fastcall tzfw_restore_ap_cfg(__int64 a1)
{
  int v1; // w20
  __int64 v2; // x0
  unsigned int v3; // w19
  _DWORD *v4; // x0
  int v5; // w2
  const void *v6; // x0
  const void *v8; // x0
  _DWORD *v9; // x1
  _DWORD *v10; // x0
  int v11; // w2
  _DWORD *v12; // x4
  _DWORD *v13; // x2
  int v14; // w0
  int *v15; // x1
  int v16; // t1
  int v17; // [xsp+20h] [xbp+20h] BYREF
  int v18; // [xsp+24h] [xbp+24h] BYREF
  _DWORD *v19; // [xsp+28h] [xbp+28h] BYREF
  _DWORD *v20; // [xsp+30h] [xbp+30h] BYREF
  _DWORD *v21; // [xsp+38h] [xbp+38h] BYREF

  v1 = a1;
  v2 = tzfw_get_ap_cfg_addr(a1, &v19, &v20, &v17, &v21, &v18);
  v3 = v2;
  if ( (_DWORD)v2 != 0 )
  {
    v8 = (const void *)get_current_thread(v2);
    sprd_log(3, "%p: %s: %s: tzfw_get_ap_cfg_addr Error(%d)\n", v8, "SPRD_FW", "tzfw_restore_ap_cfg", v3);
    return v3;
  }
  else
  {
    v4 = v19;
    if ( *v19 == 1739273421 && (v5 = v18, v19[v18 + 1 + (__int64)v17] == -1145324613) )
    {
      ++v19;
      if ( v17 > 0 )
      {
        v9 = v20;
        v10 = v4 + 2;
        v11 = 0;
        do
        {
          ++v11;
          *v9 = *(v10 - 1);
          v12 = v10;
          ++v9;
          ++v10;
        }
        while ( v17 > v11 );
        v5 = v18;
        v19 = v12;
        v20 = v9;
      }
      if ( v5 > 0 )
      {
        v13 = v21;
        v14 = 0;
        v15 = v19;
        do
        {
          v16 = *v15++;
          ++v14;
          *v13++ = v16;
        }
        while ( v18 > v14 );
      }
      return 0;
    }
    else
    {
      v6 = (const void *)get_current_thread(v19);
      sprd_log(3, "%p: %s: %s: no data to restore for fw_id(%d)\n", v6, "SPRD_FW", "tzfw_restore_ap_cfg", v1);
      return 0;
    }
  }
}

/* ===== tzfw_cfg_slv_fw @ 0x9403ED58 size 420 ===== */
__int64 __fastcall tzfw_cfg_slv_fw(__int64 a1, int a2, char a3, char a4)
{
  int v5; // w19
  int v6; // w1
  char v7; // w19
  int v8; // w5
  __int64 v9; // x1
  const void *v11; // x0
  char v12; // w19
  __int64 v13; // x1
  int v14; // w4
  __int64 v15; // x2
  __int64 v16; // x2
  int v17; // [xsp+28h] [xbp+28h]

  if ( (_DWORD)a1 == 2 )
  {
    if ( (unsigned int)a2 <= 0x4A )
    {
      v12 = 2 * (a2 & 0xF);
      v13 = 4 * (a2 >> 4);
      v14 = ~(3 << v12);
      *(_DWORD *)(v13 + 36) = *(_DWORD *)(v13 + 36) & v14 | ((a3 & 3) << v12);
      *(_DWORD *)(v13 + 56) = *(_DWORD *)(v13 + 56) & v14 | ((a4 & 3) << v12);
      return 0;
    }
    v16 = get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: bad SLV_FW_AON slv_id:%d\n", v16, "SPRD_FW", "tzfw_cfg_slv_fw", (unsigned int)a2);
    return 4294901764LL;
  }
  if ( (_DWORD)a1 == 3 )
  {
    v5 = a2 - 256;
    if ( (unsigned int)(a2 - 256) <= 0x120 )
    {
      v6 = v5 >> 4;
      v7 = 2 * (v5 & 0xF);
      v8 = ~(3 << v7);
      v9 = 4 * v6;
      *(_DWORD *)(v9 + 28704) = *(_DWORD *)(v9 + 28704) & v8 | ((a3 & 3) << v7);
      *(_DWORD *)(v9 + 28716) = *(_DWORD *)(v9 + 28716) & v8 | ((a4 & 3) << v7);
      return 0;
    }
    v15 = get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: bad SLV_FW_AP slv_id:%d\n", v15, "SPRD_FW", "tzfw_cfg_slv_fw", (unsigned int)v5);
    return 4294901764LL;
  }
  v17 = a1;
  v11 = (const void *)get_current_thread(a1);
  sprd_log(3, "%p: %s: %s: bad fw_id:%d\n", v11, "SPRD_FW", "tzfw_cfg_slv_fw", v17);
  return 4294901761LL;
}

/* ===== tzfw_cfg_mem_fw_pub_seg @ 0x9403EEFC size 380 ===== */
__int64 __fastcall tzfw_cfg_mem_fw_pub_seg(__int64 a1, __int64 *a2)
{
  int v2; // w20
  __int64 result; // x0
  _DWORD *v5; // x20
  __int64 v6; // x5
  __int64 v7; // x4
  const void *v8; // x0

  v2 = a1 - 256;
  if ( (unsigned int)(a1 - 256) > 7 )
  {
    v8 = (const void *)get_current_thread(a1);
    sprd_log(3, "%p: %s: %s: MEM_FW_PUB: seg_id: %d is invalid!\n", v8, "SPRD_FW", "tzfw_cfg_mem_fw_pub_seg", v2);
    return 4294901764LL;
  }
  else
  {
    memcpy(80LL * v2 - 536461264, a2, 80);
    result = 0;
    if ( v2 != 0 )
    {
      v5 = (_DWORD *)(72 * v2);
      v5[11273] = -1;
      v5[11275] = *((_DWORD *)a2 + 4);
      v5[11279] = *((_DWORD *)a2 + 8);
      v5[11283] = *((_DWORD *)a2 + 12);
      v5[11287] = *((_DWORD *)a2 + 16);
      v5[11276] = *((_DWORD *)a2 + 5);
      v5[11280] = *((_DWORD *)a2 + 9);
      v5[11284] = *((_DWORD *)a2 + 13);
      v5[11288] = *((_DWORD *)a2 + 17);
      v5[11277] = *((_DWORD *)a2 + 6);
      v5[11281] = *((_DWORD *)a2 + 10);
      v5[11285] = *((_DWORD *)a2 + 14);
      v5[11289] = *((_DWORD *)a2 + 18);
      v5[11278] = *((_DWORD *)a2 + 7);
      v5[11282] = *((_DWORD *)a2 + 11);
      v5[11286] = *((_DWORD *)a2 + 15);
      v5[11290] = *((_DWORD *)a2 + 19);
      v6 = *a2;
      v7 = a2[1];
      if ( *a2 != -1 || v7 != 0 )
      {
        v5[11274] = (unsigned __int64)(v7 - 0x80000000LL) >> 12;
        v5[11273] = (unsigned __int64)(v6 - 0x80000000LL) >> 12;
        return 0;
      }
      else
      {
        *(_QWORD *)(v5 + 11273) = (unsigned int)v6;
      }
    }
  }
  return result;
}

/* ===== tzfw_cfg_mem_fw_seg @ 0x9403F078 size 96 ===== */
__int64 __fastcall tzfw_cfg_mem_fw_seg(__int64 a1, unsigned int a2, __int64 *a3)
{
  const void *v4; // x0
  int v5; // [xsp+18h] [xbp+18h]

  if ( (_DWORD)a1 == 10 )
    return tzfw_cfg_mem_fw_pub_seg(a2, a3);
  v5 = a1;
  v4 = (const void *)get_current_thread(a1);
  sprd_log(3, "%p: %s: %s: bad fw_id:%d\n", v4, "SPRD_FW", "tzfw_cfg_mem_fw_seg", v5);
  return 4294901761LL;
}

/* ===== tzfw_cfg_dft_addr @ 0x9403F0D8 size 312 ===== */
__int64 __fastcall tzfw_cfg_dft_addr(int a1, unsigned __int64 a2)
{
  unsigned int v3; // w0
  const void *v4; // x0
  __int64 result; // x0
  unsigned __int64 v6; // x0
  __int64 v7; // kr00_8
  const void *v8; // x0
  int v9; // [xsp+18h] [xbp+18h]

  if ( (a2 & 0xFFF) != 0 )
  {
    v8 = (const void *)get_current_thread(a2 & 0xFFF);
    sprd_log(3, "%p: %s: %s: dft_phy_addr is not aligned to 4K!\n", v8, "SPRD_FW", "tzfw_cfg_dft_addr");
    return 4294901767LL;
  }
  else
  {
    v3 = a1 - 2;
    v7 = v3;
    v6 = (unsigned __int64)&loc_9403F14C + 4 * jpt_9403F148[v3];
    switch ( v7 )
    {
      case 0LL:
        MEMORY[0] = a2;
        MEMORY[4] = a2;
        MEMORY[8] = a2;
        MEMORY[0xC] = a2;
        MEMORY[0x10] = a2;
        result = 0;
        break;
      case 1LL:
        MEMORY[0x7000] = a2;
        MEMORY[0x7004] = (a2 & 0x100000000LL) != 0;
        MEMORY[0x7008] = a2;
        MEMORY[0x700C] = (a2 & 0x100000000LL) != 0;
        result = 0;
        break;
      case 2LL:
      case 3LL:
      case 4LL:
      case 5LL:
      case 6LL:
        goto LABEL_3;
      case 7LL:
        MEMORY[0x1000] = (a2 >> 12) & 0x3F;
        result = 0;
        break;
      case 8LL:
        MEMORY[0xB000] = ((unsigned int)a2 >> 12) ^ 0x80000;
        result = 0;
        break;
      default:
        v6 = (unsigned int)(a1 - 2);
LABEL_3:
        v9 = a1;
        v4 = (const void *)get_current_thread(v6);
        sprd_log(3, "%p: %s: %s: bad fw_id:%d\n", v4, "SPRD_FW", "tzfw_cfg_dft_addr", v9);
        result = 4294901761LL;
        break;
    }
  }
  return result;
}

/* ===== tzfw_build_table @ 0x9403F210 size 680 ===== */
__int64 tzfw_build_table()
{
  _DWORD *v0; // x10
  int v1; // w9
  __int64 v2; // x0
  int v3; // w2
  _DWORD *v4; // x16
  int v5; // w7
  _DWORD *v6; // x15
  int v7; // w6
  _DWORD *v8; // x14
  int v9; // w5
  _DWORD *v10; // x8
  int v11; // w4
  _DWORD *v12; // x1

  v0 = nullptr;
  v1 = -1576947676;
  MEMORY[4] = 10;
  MEMORY[0xC] = -1576726528;
  MEMORY[0x10] = 1;
  v2 = 28;
  MEMORY[0x14] = -1576947712;
  v3 = 0;
  MEMORY[0x18] = MEMORY[0xB000];
  do
  {
    *(_DWORD *)v2 = v1;
    *(_DWORD *)(v2 + 4) = -1;
    *(_DWORD *)(v2 + 8) = v3 - 1576947668;
    *(_DWORD *)(v2 + 12) = v0[11275];
    *(_DWORD *)(v2 + 16) = v3 - 1576947664;
    *(_DWORD *)(v2 + 20) = v0[11276];
    *(_DWORD *)(v2 + 24) = v3 - 1576947660;
    *(_DWORD *)(v2 + 28) = v0[11277];
    *(_DWORD *)(v2 + 32) = v3 - 1576947656;
    *(_DWORD *)(v2 + 36) = v0[11278];
    *(_DWORD *)(v2 + 40) = v3 - 1576947652;
    *(_DWORD *)(v2 + 44) = v0[11279];
    *(_DWORD *)(v2 + 48) = v3 - 1576947648;
    *(_DWORD *)(v2 + 52) = v0[11280];
    *(_DWORD *)(v2 + 56) = v3 - 1576947644;
    *(_DWORD *)(v2 + 60) = v0[11281];
    *(_DWORD *)(v2 + 64) = v3 - 1576947640;
    *(_DWORD *)(v2 + 68) = v0[11282];
    *(_DWORD *)(v2 + 72) = v3 - 1576947636;
    *(_DWORD *)(v2 + 76) = v0[11283];
    *(_DWORD *)(v2 + 80) = v3 - 1576947632;
    v2 += 152;
    *(_DWORD *)(v2 - 68) = v0[11284];
    v4 = v0 + 11288;
    *(_DWORD *)(v2 - 64) = v3 - 1576947628;
    v5 = v3 - 1576947616;
    v6 = v0 + 11289;
    *(_DWORD *)(v2 - 60) = v0[11285];
    *(_DWORD *)(v2 - 56) = v3 - 1576947624;
    v7 = v3 - 1576947612;
    v8 = v0 + 11290;
    *(_DWORD *)(v2 - 52) = v0[11286];
    v9 = v3 - 1576947608;
    *(_DWORD *)(v2 - 48) = v3 - 1576947620;
    v10 = v0 + 11274;
    v11 = v3 - 1576947672;
    *(_DWORD *)(v2 - 44) = v0[11287];
    v12 = v0 + 11273;
    v3 += 72;
    v0 += 18;
    *(_DWORD *)(v2 - 40) = v5;
    *(_DWORD *)(v2 - 36) = *v4;
    *(_DWORD *)(v2 - 32) = v7;
    *(_DWORD *)(v2 - 28) = *v6;
    *(_DWORD *)(v2 - 24) = v9;
    *(_DWORD *)(v2 - 20) = *v8;
    *(_DWORD *)(v2 - 16) = v11;
    *(_DWORD *)(v2 - 12) = *v10;
    *(_DWORD *)(v2 - 8) = v1;
    v1 += 72;
    *(_DWORD *)(v2 - 4) = *v12;
  }
  while ( v3 != 576 );
  MEMORY[0x4DC] = -1576722432;
  MEMORY[0x4E0] = 1;
  MEMORY[8] = 1240;
  MEMORY[0x4E4] = -1145324613;
  MEMORY[0] = 1739273421;
  return 0;
}

/* ===== sprd_fw_lock2 @ 0x9403F4B8 size 8 ===== */
__int64 sprd_fw_lock2()
{
  return clk_enable(24);
}

/* ===== sprd_fw_unlock @ 0x9403F4C0 size 8 ===== */
__int64 sprd_fw_unlock()
{
  return clk_disable(24);
}

/* ===== tzfw_init @ 0x9403F4C8 size 168 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall tzfw_init(void *a1, __int64 a2)
{
  __int64 v2; // x0
  const void *v3; // x0

  off_94067B40 = a1;
  qword_94067B30 = a2;
  memset(-536461312, 0, 688);
  v2 = malloc(1144);
  qword_94067B38 = v2;
  if ( v2 != 0 )
    return memset(v2, 0, 1144);
  v3 = (const void *)get_current_thread(0);
  sprd_log(3, "%p: %s: %s: can NOT malloc memory for fw!\n", v3, "SPRD_FW", "tzfw_init");
  assert_fail(1);
  return memset(0, 0, 1144);
}

/* ===== GPIO_Init @ 0x9403F570 size 456 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 GPIO_Init()
{
  __int64 v0; // x0
  int v1; // w4
  unsigned int v2; // w19
  __int64 v3; // x3
  _DWORD v5[6]; // [xsp+48h] [xbp+48h] BYREF

  sprd_log(2, "%s:Init GPIO !\n", "GPIO_Init");
  v0 = clk_enable(9);
  v1 = gpio_mem_map(v0);
  if ( v1 != 0 )
  {
    sprd_log(2, "%s:%s: mem map failed %d\n", "GPIO_Init", "GPIO_Init", v1);
    return 0xFFFFFFFFLL;
  }
  else
  {
    v2 = 0;
    GPIO_PHY_SetBaseAddr(MEMORY[0xFFFFFFFFE0047DC8]);
    dword_94067B64 = 255;
    dword_94067BA4 = 255;
    dword_94067BE4 = 255;
    dword_94067C24 = 255;
    dword_94067C64 = 255;
    dword_94067CA4 = 255;
    dword_94067CE4 = 255;
    dword_94067D24 = 255;
    dword_94067D64 = 255;
    dword_94067DA4 = 255;
    irq_register(95, gpio_irq_handler, 0);
    irq_enable(0x5Fu);
    do
    {
      while ( 1 )
      {
        GPIO_PHY_GetBaseInfo(v2, v5);
        if ( (v5[0] & 0xFFFFFFFD) == 0 && (unsigned int)GPIO_PHY_GetIntMask(v5) != 0 && v2 != 0 )
          break;
        if ( ++v2 == 16 )
          return 0;
      }
      v3 = v2++;
      sprd_log(2, "%s:GPIO_Init GPIO_%lu interrupt has not been registed!\n", "GPIO_Init", v3);
      GPIO_PHY_ClearIntMask(v5);
    }
    while ( v2 != 16 );
    return 0;
  }
}

/* ===== sprd_pal_gpio_init @ 0x9403F738 size 72 ===== */
__int64 sprd_pal_gpio_init()
{
  if ( (unsigned int)GPIO_Init() != 0 )
    return sprd_log(2, "%s:sprd_gpio_init failed[0x%x]\n", "sprd_pal_gpio_init");
  else
    return sprd_log(2, "%s:sprd_gpio_init successful\n", "sprd_pal_gpio_init");
}

/* ===== gpio_enable_irq @ 0x9403F780 size 44 ===== */
__int64 __fastcall gpio_enable_irq(__int64 a1)
{
  _BYTE v2[24]; // [xsp+28h] [xbp+28h] BYREF

  GPIO_PHY_GetBaseInfo(a1, v2);
  return GPIO_PHY_SetIntMask(v2);
}

/* ===== gpio_disable_irq @ 0x9403F7AC size 44 ===== */
__int64 __fastcall gpio_disable_irq(__int64 a1)
{
  _BYTE v2[24]; // [xsp+28h] [xbp+28h] BYREF

  GPIO_PHY_GetBaseInfo(a1, v2);
  return GPIO_PHY_ClearIntMask(v2);
}

/* ===== gpio_irq_handler @ 0x9403F7D8 size 188 ===== */
__int64 gpio_irq_handler()
{
  unsigned int v0; // w20
  int *i; // x19
  __int64 *v2; // x22
  void (__fastcall *v3)(_QWORD, _QWORD); // x19
  unsigned int v4; // w0
  _BYTE v6[24]; // [xsp+38h] [xbp+38h] BYREF

  v0 = 0;
  for ( i = &dword_94067B64; ; i += 16 )
  {
    if ( *i != 255 )
    {
      GPIO_PHY_GetBaseInfo((unsigned int)*i, v6);
      if ( (unsigned int)GPIO_PHY_GetIntState(v6) != 0 )
      {
        GPIO_PHY_ClearIntStatus(v6);
        gpio_disable_irq((unsigned int)*i);
        if ( i[8] != 0 )
          break;
      }
    }
    if ( ++v0 == 10 )
      return 1;
  }
  v2 = &qword_94067B48[8 * (unsigned __int64)v0];
  v3 = (void (__fastcall *)(_QWORD, _QWORD))v2[4];
  v4 = GPIO_PHY_GetGpioData(v6);
  v3(v0, v4);
  GPIO_PHY_EnableGPIDetect(v6);
  gpio_enable_irq(*((unsigned int *)v2 + 7));
  return 1;
}

/* ===== gpio_get_base_info @ 0x9403F894 size 20 ===== */
__int64 *__fastcall gpio_get_base_info(_DWORD *a1)
{
  *a1 = 1;
  return &qword_9405C748;
}

/* ===== GPIO_PHY_GetBaseInfo @ 0x9403F8A8 size 268 ===== */
__int64 __fastcall GPIO_PHY_GetBaseInfo(unsigned int a1, __int64 a2)
{
  __int64 *v4; // x20
  unsigned int v5; // w3
  unsigned __int64 v6; // x0
  unsigned int v7; // w1
  unsigned int v8; // w19
  __int64 *v9; // x2
  __int64 result; // x0
  unsigned int v11; // [xsp+4Ch] [xbp+4Ch] BYREF

  v11 = 0;
  v4 = gpio_get_base_info(&v11);
  v5 = a1 & 0xF;
  *(_WORD *)(a2 + 16) = a1 & 0xF;
  v6 = MEMORY[0xFFFFFFFFE0047DC8] + ((unsigned __int64)((a1 >> 4) & 0x1FFFFFF) << 7);
  v7 = v11;
  *(_QWORD *)(a2 + 8) = v6;
  if ( v7 == 0 )
  {
LABEL_6:
    *(_DWORD *)a2 = 3;
    return 3;
  }
  if ( v6 != *v4 )
  {
    v8 = 0;
    while ( 1 )
    {
      ++v8;
      sprd_log(2, "%s:GPIO_PHY_GetBaseInfo gpio_%lu can not be used\n", "GPIO_PHY_GetBaseInfo", a1);
      v9 = &v4[2 * v8];
      if ( v11 <= v8 )
        goto LABEL_6;
      if ( v4[2 * v8] == *(_QWORD *)(a2 + 8) )
      {
        v5 = *(unsigned __int16 *)(a2 + 16);
        goto LABEL_8;
      }
    }
  }
  v9 = v4;
LABEL_8:
  if ( *((_DWORD *)v9 + 2) <= v5 )
    goto LABEL_6;
  result = *((unsigned int *)v9 + 3);
  *(_DWORD *)a2 = result;
  return result;
}

/* ===== GPIO_PHY_SetBaseAddr @ 0x9403F9B4 size 88 ===== */
__int64 *__fastcall GPIO_PHY_SetBaseAddr(__int64 a1)
{
  __int64 *result; // x0
  int v3; // [xsp+2Ch] [xbp+2Ch] BYREF

  v3 = 0;
  result = gpio_get_base_info(&v3);
  *result = a1;
  if ( a1 == 0 )
    return (__int64 *)sprd_log(2, "%s:can not get base addr!!!\n", "GPIO_PHY_SetBaseAddr");
  return result;
}

/* ===== GPIO_PHY_GetGpioData @ 0x9403FA0C size 140 ===== */
bool __fastcall GPIO_PHY_GetGpioData(__int64 a1)
{
  unsigned int v2; // w0
  _DWORD *v3; // x20

  v2 = *(_DWORD *)a1;
  v3 = *(_DWORD **)(a1 + 8);
  if ( v2 <= 2 )
    return ((1 << *(_WORD *)(a1 + 16)) & *v3) != 0;
  if ( v2 != 3 )
  {
    sprd_log(2, "%s:_GPIO_GetGpioDataRegAddr error\n", "_GPIO_GetGpioDataRegAddr");
    return ((1 << *(_WORD *)(a1 + 16)) & *v3) != 0;
  }
  sprd_log(2, "%s:_GPIO_GetGpioDataRegAddr GPIO_ID Invalid\n", "_GPIO_GetGpioDataRegAddr");
  return false;
}

/* ===== GPIO_PHY_GetIntMask @ 0x9403FA98 size 200 ===== */
bool __fastcall GPIO_PHY_GetIntMask(__int64 a1)
{
  __int64 v2; // x20
  __int64 v3; // x0
  _BOOL8 result; // x0

  v2 = *(_QWORD *)(a1 + 8);
  switch ( *(_DWORD *)a1 )
  {
    case 0:
    case 2:
      v3 = 24;
      goto LABEL_3;
    case 1:
      sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr gpo\n", "_GPIO_GetGpioIntMaskAddr");
      result = false;
      break;
    case 3:
      sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr GPIO_ID Invalid\n", "_GPIO_GetGpioIntMaskAddr");
      result = false;
      break;
    default:
      sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr error\n", "_GPIO_GetGpioIntMaskAddr");
      v3 = 0;
LABEL_3:
      result = (*(_DWORD *)(v2 + v3) & (1 << *(_WORD *)(a1 + 16))) != 0;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_SetIntMask @ 0x9403FB60 size 200 ===== */
__int64 __fastcall GPIO_PHY_SetIntMask(__int64 a1)
{
  __int64 v2; // x20
  __int64 v3; // x2
  __int64 result; // x0

  v2 = *(_QWORD *)(a1 + 8);
  switch ( *(_DWORD *)a1 )
  {
    case 0:
    case 2:
      v3 = 24;
      goto LABEL_3;
    case 1:
      result = sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr gpo\n", "_GPIO_GetGpioIntMaskAddr");
      break;
    case 3:
      result = sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr GPIO_ID Invalid\n", "_GPIO_GetGpioIntMaskAddr");
      break;
    default:
      sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr error\n", "_GPIO_GetGpioIntMaskAddr");
      v3 = 0;
LABEL_3:
      result = *(_DWORD *)(v2 + v3) & ~(unsigned int)(1LL << *(_WORD *)(a1 + 16)) | (1 << *(_WORD *)(a1 + 16));
      *(_DWORD *)(v2 + v3) = result;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_ClearIntMask @ 0x9403FC28 size 192 ===== */
__int64 __fastcall GPIO_PHY_ClearIntMask(__int64 a1)
{
  __int64 v2; // x20
  __int64 v3; // x1
  __int64 result; // x0

  v2 = *(_QWORD *)(a1 + 8);
  switch ( *(_DWORD *)a1 )
  {
    case 0:
    case 2:
      v3 = 24;
      goto LABEL_3;
    case 1:
      result = sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr gpo\n", "_GPIO_GetGpioIntMaskAddr");
      break;
    case 3:
      result = sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr GPIO_ID Invalid\n", "_GPIO_GetGpioIntMaskAddr");
      break;
    default:
      sprd_log(2, "%s:_GPIO_GetGpioIntMaskAddr error\n", "_GPIO_GetGpioIntMaskAddr");
      v3 = 0;
LABEL_3:
      result = *(_DWORD *)(v2 + v3) & ~(unsigned int)(1LL << *(_WORD *)(a1 + 16));
      *(_DWORD *)(v2 + v3) = result;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_GetIntState @ 0x9403FCE8 size 180 ===== */
bool __fastcall GPIO_PHY_GetIntState(__int64 a1)
{
  _DWORD *v2; // x20
  _BOOL8 result; // x0

  v2 = *(_DWORD **)(a1 + 8);
  switch ( *(_DWORD *)a1 )
  {
    case 0:
    case 2:
      v2 += 8;
      goto LABEL_3;
    case 1:
      result = false;
      break;
    case 3:
      sprd_log(2, "%s:GPIO_PHY_GetIntState GPIO_ID Invalid\n", "GPIO_PHY_GetIntState");
      result = false;
      break;
    default:
      sprd_log(2, "%s:GPIO_PHY_GetIntState error\n", "GPIO_PHY_GetIntState");
LABEL_3:
      result = (*v2 & (1 << *(_WORD *)(a1 + 16))) != 0;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_ClearIntStatus @ 0x9403FD9C size 164 ===== */
__int64 __fastcall GPIO_PHY_ClearIntStatus(unsigned int *a1)
{
  unsigned int v2; // w0
  _DWORD *v3; // x20
  __int64 result; // x0
  __int64 v5; // kr00_8

  v2 = *a1;
  v3 = *((_DWORD **)a1 + 1);
  v5 = v2;
  result = (__int64)&loc_9403FE18 + 4 * jpt_9403FE14[v2];
  switch ( v5 )
  {
    case 0LL:
    case 2LL:
      v3 += 9;
      goto LABEL_3;
    case 1LL:
      return result;
    case 3LL:
      result = sprd_log(2, "%s:GPIO_PHY_ClearIntStatus GPIO_ID Invalid\n", "GPIO_PHY_ClearIntStatus");
      break;
    default:
      sprd_log(2, "%s:GPIO_PHY_ClearIntStatus error\n", "GPIO_PHY_ClearIntStatus");
LABEL_3:
      result = *v3 & ~(unsigned int)(1LL << *((_WORD *)a1 + 8)) | (1 << *((_WORD *)a1 + 8));
      *v3 = result;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_TrigGPIDetect @ 0x9403FE40 size 196 ===== */
__int64 __fastcall GPIO_PHY_TrigGPIDetect(__int64 a1)
{
  _DWORD *v2; // x20
  __int64 result; // x0

  v2 = *(_DWORD **)(a1 + 8);
  switch ( *(_DWORD *)a1 )
  {
    case 0:
      v2 += 18;
      goto LABEL_3;
    case 1:
    case 2:
      result = sprd_log(2, "%s:GPIO_PHY_TrigGPIDetect can not belong to GPO", "GPIO_PHY_TrigGPIDetect");
      break;
    case 3:
      result = sprd_log(2, "%s:GPIO_PHY_TrigGPIDetect GPIO_ID Invalid\n", "GPIO_PHY_TrigGPIDetect");
      break;
    default:
      sprd_log(2, "%s:GPIO_PHY_TrigGPIDetect error\n", "GPIO_PHY_TrigGPIDetect");
LABEL_3:
      result = *v2 & ~(unsigned int)(1LL << *(_WORD *)(a1 + 16)) | (1 << *(_WORD *)(a1 + 16));
      *v2 = result;
      break;
  }
  return result;
}

/* ===== GPIO_PHY_EnableGPIDetect @ 0x9403FF04 size 48 ===== */
_DWORD *__fastcall GPIO_PHY_EnableGPIDetect(_DWORD *result)
{
  if ( *result == 0 )
    return (_DWORD *)GPIO_PHY_TrigGPIDetect((__int64)result);
  if ( *result > 2u )
    return (_DWORD *)sprd_log(2, "%s:GPIO_PHY_EnableGPIDetect error\n", "GPIO_PHY_EnableGPIDetect");
  return result;
}

/* ===== gpio_mem_map @ 0x9403FF34 size 96 ===== */
__int64 gpio_mem_map()
{
  int v0; // w4
  __int64 result; // x0

  v0 = sprd_iomap("gpio", 839254016, 4096, 2, -536576568);
  result = 0;
  if ( v0 != 0 )
  {
    sprd_log(2, "%s:%s: mem map failed %d\n", "gpio_mem_map", "gpio_mem_map", v0);
    return 0xFFFFFFFFLL;
  }
  return result;
}

/* ===== sprd_hwspinlock_init @ 0x9403FF94 size 116 ===== */
__int64 sprd_hwspinlock_init()
{
  if ( (unsigned int)sprd_iomap("hwspinlock", 855638016, 4096, 2, &qword_94067DD0) != 0 )
    return sprd_log(2, "%s: mem map failed %d\n");
  *MEMORY[0xFFFFFFFFE0061250] |= 0x400000u;
  return sprd_log(2, "sprd hwspinlock is ok!\n");
}

/* ===== delay_loop @ 0x94040008 size 44 ===== */
__int64 __fastcall delay_loop(char a1)
{
  __int64 result; // x0
  __int64 v2; // [xsp+8h] [xbp-8h]

  v2 = 1000 << a1;
  do
    result = v2--;
  while ( result != 0 );
  return result;
}

/* ===== sprd_i2c_transfer @ 0x94040034 size 1420 ===== */
__int64 __fastcall sprd_i2c_transfer(__int64 a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned __int8 *v4; // x1
  unsigned __int8 *v5; // x24
  __int64 v6; // x25
  unsigned int *v7; // x19
  unsigned int v8; // w0
  __int16 v9; // w0
  _DWORD *v10; // x27
  int v11; // w22
  unsigned __int8 *v12; // x21
  int v13; // w0
  int v14; // w22
  int v15; // w0
  int i; // w20
  __int16 v18; // w0
  _BYTE *v19; // x22
  int v20; // w23
  _DWORD *v21; // x20
  int v22; // w28
  int v23; // w0
  __int64 v25; // [xsp+78h] [xbp+78h]
  unsigned int v27; // [xsp+84h] [xbp+84h]

  clk_enable(*(_DWORD *)(a1 + 56));
  if ( a3 != 0 )
  {
    v27 = a3 - 1;
    v4 = a2;
    v25 = a3 - 1 + 1LL;
    v5 = v4;
    v6 = 0;
    while ( 1 )
    {
      v7 = *(unsigned int **)(a1 + 48);
      v7[1] = 2 * *v5;
      v8 = *v7;
      if ( v27 == (_DWORD)v6 )
      {
        *v7 = v8 & 0xFFEFFFFF;
        v9 = *((_WORD *)v5 + 1);
        v10 = v7 + 2;
        v7[2] = *((_DWORD *)v5 + 1);
        if ( (v9 & 1) == 0 )
          goto LABEL_5;
      }
      else
      {
        *v7 = v8 | 0x100000;
        v18 = *((_WORD *)v5 + 1);
        v10 = v7 + 2;
        v7[2] = *((_DWORD *)v5 + 1);
        if ( (v18 & 1) == 0 )
        {
LABEL_5:
          v11 = *((_DWORD *)v5 + 1);
          v12 = *((unsigned __int8 **)v5 + 1);
          if ( v11 > 15 )
            v13 = 15;
          else
            v13 = *((_DWORD *)v5 + 1);
          *v7 &= ~8u;
          if ( v13 > 0 )
          {
            v7[4] = *v12;
            if ( v13 != 1 )
            {
              v7[4] = v12[1];
              if ( v13 != 2 )
              {
                v7[4] = v12[2];
                if ( v13 != 3 )
                {
                  v7[4] = v12[3];
                  if ( v13 != 4 )
                  {
                    v7[4] = v12[4];
                    if ( v13 != 5 )
                    {
                      v7[4] = v12[5];
                      if ( v13 != 6 )
                      {
                        v7[4] = v12[6];
                        if ( v13 != 7 )
                        {
                          v7[4] = v12[7];
                          if ( v13 != 8 )
                          {
                            v7[4] = v12[8];
                            if ( v13 != 9 )
                            {
                              v7[4] = v12[9];
                              if ( v13 != 10 )
                              {
                                v7[4] = v12[10];
                                if ( v13 != 11 )
                                {
                                  v7[4] = v12[11];
                                  if ( v13 != 12 )
                                  {
                                    v7[4] = v12[12];
                                    if ( v13 != 13 )
                                    {
                                      v7[4] = v12[13];
                                      if ( v13 == 15 )
                                        v7[4] = v12[14];
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          v14 = v11 - v13;
          *v7 |= 1u;
          while ( v14 != 0 )
          {
            if ( v14 > 15 )
              v15 = 15;
            else
              v15 = v14;
            if ( v15 > 0 )
            {
              v7[4] = *v12;
              if ( v15 != 1 )
              {
                v7[4] = v12[1];
                if ( v15 != 2 )
                {
                  v7[4] = v12[2];
                  if ( v15 != 3 )
                  {
                    v7[4] = v12[3];
                    if ( v15 != 4 )
                    {
                      v7[4] = v12[4];
                      if ( v15 != 5 )
                      {
                        v7[4] = v12[5];
                        if ( v15 != 6 )
                        {
                          v7[4] = v12[6];
                          if ( v15 != 7 )
                          {
                            v7[4] = v12[7];
                            if ( v15 != 8 )
                            {
                              v7[4] = v12[8];
                              if ( v15 != 9 )
                              {
                                v7[4] = v12[9];
                                if ( v15 != 10 )
                                {
                                  v7[4] = v12[10];
                                  if ( v15 != 11 )
                                  {
                                    v7[4] = v12[11];
                                    if ( v15 != 12 )
                                    {
                                      v7[4] = v12[12];
                                      if ( v15 != 13 )
                                      {
                                        v7[4] = v12[13];
                                        if ( v15 == 15 )
                                          v7[4] = v12[14];
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            v14 -= v15;
            v12 += v15;
            if ( (v7[5] & 8) == 0 )
            {
              for ( i = 1000; i != 0; --i )
                delay_loop(1);
            }
          }
          goto LABEL_48;
        }
      }
      v19 = *((_BYTE **)v5 + 1);
      v20 = *((_DWORD *)v5 + 1);
      *v7 |= 8u;
      *v7 |= 1u;
      v21 = v7 + 5;
      if ( v20 != 0 )
      {
        do
        {
          v22 = 1000;
          while ( 1 )
          {
            delay_loop(200);
            if ( (*v21 & 0x14) != 0 )
              break;
            if ( --v22 == -1 )
              goto LABEL_79;
          }
          if ( v22 != 0 )
          {
            *v21 &= ~4u;
            goto LABEL_57;
          }
LABEL_79:
          sprd_log(2, "Timed out in wait_for_data_ready: status=%04x\n");
          sprd_log(2, "I2C_CTL \t= 0x%x\n", *v7);
          sprd_log(2, "I2C_ADDR_CFG \t= 0x%x\n", v7[1]);
          sprd_log(2, "I2C_COUNT = 0x%x\n", *v10);
          sprd_log(2, "I2C_STATUS = 0x%x\n", *v21);
          sprd_log(2, "ADDR_DVD0 = 0x%x\n", v7[8]);
          sprd_log(2, "ADDR_DVD1 = 0x%x\n", v7[9]);
          sprd_log(2, "ADDR_STA0_DVD = 0x%x\n", v7[10]);
          *v7 &= ~1u;
LABEL_57:
          if ( v20 > 15 )
            v23 = 15;
          else
            v23 = v20;
          if ( v23 > 0 )
          {
            *v19 = v7[3];
            if ( v23 != 1 )
            {
              v19[1] = v7[3];
              if ( v23 != 2 )
              {
                v19[2] = v7[3];
                if ( v23 != 3 )
                {
                  v19[3] = v7[3];
                  if ( v23 != 4 )
                  {
                    v19[4] = v7[3];
                    if ( v23 != 5 )
                    {
                      v19[5] = v7[3];
                      if ( v23 != 6 )
                      {
                        v19[6] = v7[3];
                        if ( v23 != 7 )
                        {
                          v19[7] = v7[3];
                          if ( v23 != 8 )
                          {
                            v19[8] = v7[3];
                            if ( v23 != 9 )
                            {
                              v19[9] = v7[3];
                              if ( v23 != 10 )
                              {
                                v19[10] = v7[3];
                                if ( v23 != 11 )
                                {
                                  v19[11] = v7[3];
                                  if ( v23 != 12 )
                                  {
                                    v19[12] = v7[3];
                                    if ( v23 != 13 )
                                    {
                                      v19[13] = v7[3];
                                      if ( v23 == 15 )
                                        v19[14] = v7[3];
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          v20 -= v23;
          v19 += v23;
        }
        while ( v20 != 0 );
        ++v6;
        v5 += 16;
        if ( v6 == v25 )
          break;
      }
      else
      {
LABEL_48:
        ++v6;
        v5 += 16;
        if ( v6 == v25 )
          break;
      }
    }
  }
  clk_disable(*(_DWORD *)(a1 + 56));
  return a3;
}

/* ===== sprd_i2c_bus_init @ 0x940405C0 size 456 ===== */
__int64 sprd_i2c_bus_init()
{
  int v0; // w19
  __int64 v1; // x24
  __int64 v2; // x1
  __int64 v3; // x0
  int v4; // w3
  _DWORD *v5; // x25
  int v6; // w3
  _DWORD *v7; // x4
  unsigned int v8; // w0
  unsigned int v9; // w1
  unsigned __int64 v10; // x0
  __int64 result; // x0

  v0 = 0;
  v1 = -536623216;
  do
  {
    v2 = *(_QWORD *)(v1 - 8);
    v3 = *(_QWORD *)(v1 - 16);
    *(_DWORD *)(v1 - 40) = v0;
    *(_DWORD *)(v1 - 32) = 0;
    *(_QWORD *)(v1 - 24) = qword_9405C758;
    v4 = sprd_iomap(v3, v2, 4096, 2, v1);
    if ( v4 != 0 )
    {
      result = sprd_log(2, "%s: mem map failed %d\n", "sprd_i2c_bus_init", v4);
    }
    else
    {
      clk_enable(*(_DWORD *)(v1 + 8));
      v5 = *(_DWORD **)v1;
      **(_DWORD **)v1 = **(_DWORD **)v1 & 0xFFF00EBB | 0x82100;
      sprd_log(2, "i2c%d, freq=%d\n", *(_DWORD *)(v1 - 40), *(_DWORD *)(v1 + 12));
      v6 = *(_DWORD *)(v1 + 12);
      v7 = *(_DWORD **)v1;
      v8 = 0x18CBA80u / (4 * v6) - 1;
      v9 = 4 * v8 / 5;
      v10 = (3435973837u * (unsigned __int64)(6 * v8)) >> 32;
      v7[8] = (unsigned __int16)(v10 >> 2) | (v9 << 16);
      v7[9] = ((unsigned int)v10 >> 18) | v9 & 0x3FFF0000;
      if ( v6 == 400000 )
      {
        v7[10] = 15;
      }
      else if ( v6 == 100000 )
      {
        v7[10] = 104;
      }
      v5[11] = 1;
      v5[5] &= ~4u;
      *v5 |= 4u;
      clk_disable(*(_DWORD *)(v1 + 8));
      result = sprd_log(2, "%s is ok!\n", *(const char **)(v1 - 16));
    }
    ++v0;
    v1 += 72;
  }
  while ( v0 != 5 );
  return result;
}

/* ===== irq_enable @ 0x94040788 size 4 ===== */
// attributes: thunk
__int64 __fastcall irq_enable(unsigned int a1)
{
  return gic_enable_irq(a1);
}

/* ===== irq_register @ 0x9404078C size 24 ===== */
__int64 __fastcall irq_register(unsigned int a1, __int64 a2, __int64 a3)
{
  register_int_handler(a1, a2, a3);
  return 0;
}

/* ===== assert_fail @ 0x940407A4 size 56 ===== */
__int64 __fastcall assert_fail(__int64 result)
{
  __int64 v1; // x30
  __int64 v2; // x0
  const char *v3; // x1

  if ( (_DWORD)result == 0 )
  {
    v2 = panic(
           v1,
           "ASSERT FAILED at (%s:%d): %s\n",
           "external/lk/platform/sprd/pal/src/sprd_pal_debug.c",
           31,
           "x");
    return sprd_log(v2, v3);
  }
  return result;
}

/* ===== sprd_log @ 0x940407DC size 148 ===== */
__int64 sprd_log(
        unsigned int a1,
        const char *a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        ...)
{
  __int64 v10; // x3
  __int64 result; // x0
  va_list va1; // [xsp+10h] [xbp+10h] BYREF
  va_list va; // [xsp+30h] [xbp+30h] BYREF

  va_start(va, a10);
  if ( a1 > 7 )
    v10 = 2;
  else
    v10 = *((unsigned int *)qword_94054AF8 + a1);
  result = MEMORY[0xFFFFFFFFE003CB98];
  if ( v10 <= MEMORY[0xFFFFFFFFE003CB98] )
  {
    va_copy(va1, va);
    return log_vprintf(a2, va1);
  }
  return result;
}

/* ===== memcmp @ 0x94040870 size 8 ===== */
__int64 __fastcall memcmp(__int64 a1, __int64 a2, unsigned int a3)
{
  return memcmp(a1, a2, a3);
}

/* ===== strcmp @ 0x94040878 size 4 ===== */
// attributes: thunk
__int64 __fastcall strcmp(__int64 a1, __int64 a2)
{
  return strcmp(a1, a2);
}

/* ===== rtc_read @ 0x9404087C size 4 ===== */
// attributes: thunk
__int64 rtc_read()
{
  return strstr();
}

/* ===== memcpy @ 0x94040880 size 8 ===== */
__int64 __fastcall memcpy(__int64 a1, __int64 a2, unsigned int a3)
{
  return memcpy(a1, a2, a3);
}

/* ===== memset @ 0x94040888 size 12 ===== */
__int64 __fastcall memset(__int64 a1, unsigned __int8 a2, unsigned int a3)
{
  return memset(a1, a2, a3);
}

/* ===== malloc @ 0x94040894 size 8 ===== */
__int64 __fastcall malloc(unsigned int a1)
{
  return malloc(a1);
}

/* ===== memalign @ 0x9404089C size 16 ===== */
__int64 __fastcall memalign(unsigned int a1, unsigned int a2)
{
  return memalign(a2, a1);
}

/* ===== free @ 0x940408AC size 4 ===== */
// attributes: thunk
__int64 __fastcall free(__int64 a1)
{
  return free(a1);
}

/* ===== dcache_clean @ 0x940408B0 size 8 ===== */
__int64 __fastcall dcache_clean(__int64 a1, unsigned int a2)
{
  return dcache_clean_range(a1, a2);
}

/* ===== dcache_clean2 @ 0x940408B8 size 8 ===== */
__int64 __fastcall dcache_clean2(__int64 result, unsigned int a2)
{
  unsigned __int64 v2; // x3

  v2 = result & 0xFFFFFFFFFFFFFFE0LL;
  do
  {
    __asm { DC              CVAC, X3 }
    v2 += 32LL;
  }
  while ( v2 < result + (unsigned __int64)a2 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_invalidate @ 0x940408C0 size 8 ===== */
__int64 __fastcall dcache_invalidate(__int64 a1, unsigned int a2)
{
  return dcache_invalidate_range(a1, a2);
}

/* ===== virt_to_phys @ 0x940408C8 size 4 ===== */
// attributes: thunk
__int64 __fastcall virt_to_phys(__int64 a1)
{
  return pmm_phys_to_virt(a1);
}

/* ===== sprd_iomap @ 0x940408CC size 40 ===== */
__int64 __fastcall sprd_iomap(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, __int64 a5)
{
  return vmm_map(-536460256, a1, a3, a5, 12, a2, 0, a4);
}

/* ===== sprd_iounmap @ 0x940408F4 size 16 ===== */
__int64 __fastcall sprd_iounmap(__int64 a1)
{
  return vmm_free_region(-536460256, a1);
}

/* ===== sprd_dma_alloc @ 0x94040904 size 56 ===== */
__int64 __fastcall sprd_dma_alloc(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        unsigned __int8 a4,
        unsigned int a5,
        unsigned int a6)
{
  return vmm_alloc_physical(-536460256, a1, a2, a3, a4, a5, a6);
}

/* ===== sprd_mutex_create @ 0x9404093C size 48 ===== */
__int64 sprd_mutex_create()
{
  __int64 v0; // x0
  __int64 v1; // x19

  v0 = malloc(56);
  v1 = v0;
  if ( v0 != 0 )
    mutex_init(v0);
  return v1;
}

/* ===== sprd_mutex_lock @ 0x9404096C size 8 ===== */
__int64 __fastcall sprd_mutex_lock(__int64 a1)
{
  return mutex_acquire_timeout(a1, 0xFFFFFFFFLL);
}

/* ===== sprd_mutex_unlock @ 0x94040974 size 4 ===== */
// attributes: thunk
__int64 __fastcall sprd_mutex_unlock(__int64 a1)
{
  return mutex_release(a1);
}

/* ===== sprd_spin_lock_irqsave @ 0x94040978 size 64 ===== */
unsigned __int64 *__fastcall sprd_spin_lock_irqsave(unsigned __int64 *result, int *a2, int a3)
{
  int v3; // w3

  v3 = 0;
  if ( (a3 & 0x40000000) != 0 && (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v3 = 1;
    if ( (a3 & 0x80000000) == 0 )
      goto LABEL_4;
  }
  else if ( (a3 & 0x80000000) == 0 )
  {
    goto LABEL_4;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) == 0 )
  {
    __asm { MSR             DAIFSet, #1 }
    *a2 = v3 | 2;
    return spin_lock(result);
  }
LABEL_4:
  *a2 = v3;
  return spin_lock(result);
}

/* ===== sprd_spin_unlock_irqrestore @ 0x940409B8 size 64 ===== */
unsigned __int64 *__fastcall sprd_spin_unlock_irqrestore(unsigned __int64 *a1, char a2, int a3)
{
  unsigned __int64 *result; // x0

  result = spin_unlock(a1);
  if ( a3 < 0 && (a2 & 2) != 0 )
    __asm { MSR             DAIFClr, #1 }
  if ( (a3 & 0x40000000) != 0 && (a2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== sprd_semaphore_create @ 0x940409F8 size 60 ===== */
__int64 __fastcall sprd_semaphore_create(int a1)
{
  __int64 v1; // x0
  __int64 v2; // x19

  v1 = malloc(40);
  v2 = v1;
  if ( v1 != 0 )
    semaphore_init(v1, a1);
  return v2;
}

/* ===== sprd_semaphore_destroy @ 0x94040A34 size 64 ===== */
__int64 __fastcall sprd_semaphore_destroy(__int64 a1)
{
  if ( a1 == 0 )
    return 1;
  semaphore_destroy(a1);
  free(a1);
  return 0;
}

/* ===== sprd_semaphore_wait @ 0x94040A74 size 8 ===== */
__int64 __fastcall sprd_semaphore_wait(__int64 a1)
{
  return semaphore_wait(a1, 0xFFFFFFFFLL);
}

/* ===== sprd_semaphore_post @ 0x94040A7C size 12 ===== */
__int64 __fastcall sprd_semaphore_post(__int64 a1, int a2)
{
  return semaphore_post(a1, a2 != 0);
}

/* ===== thread_sleep_ms @ 0x94040A88 size 4 ===== */
// attributes: thunk
unsigned __int64 *__fastcall thread_sleep_ms(unsigned int a1)
{
  return thread_sleep(a1);
}

/* ===== sprd_thread_create @ 0x94040A8C size 8 ===== */
__int64 __fastcall sprd_thread_create(__int64 a1, __int64 a2, __int64 a3, unsigned int a4, unsigned int a5)
{
  return thread_create_simple(a1, a2, a3, a4, a5);
}

/* ===== sprd_thread_resume @ 0x94040A94 size 4 ===== */
// attributes: thunk
unsigned __int64 *__fastcall sprd_thread_resume(_DWORD *a1)
{
  return thread_resume_full(a1);
}

/* ===== get_current_thread @ 0x94040A98 size 8 ===== */
unsigned __int64 get_current_thread()
{
  return _ReadStatusReg(TPIDR_EL1);
}

/* ===== arch_curr_cpu_num @ 0x94040AA0 size 36 ===== */
unsigned __int64 arch_curr_cpu_num()
{
  unsigned __int64 StatusReg; // x1

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( (StatusReg & 0x1000000) != 0 )
    StatusReg >>= 8;
  return (unsigned __int8)StatusReg | (4 * ((StatusReg >> 8) & 0xF));
}

/* ===== strlen @ 0x94040AC4 size 20 ===== */
__int64 __fastcall strlen(__int64 a1)
{
  return strlen(a1);
}

/* ===== rpmb_handler_register @ 0x94040AD8 size 76 ===== */
__int64 rpmb_handler_register()
{
  __int64 result; // x0

  result = trusty_install_handler(9u, (__int64)qword_9405C8C8);
  if ( (_DWORD)result != 0 && MEMORY[0xFFFFFFFFE003CB98] > 1 )
    return log_printf("can not install sprd_rpmb_op in handler: %d\n", result);
  return result;
}

/* ===== sys_get_rpmb_size @ 0x94040B24 size 184 ===== */
__int64 __fastcall sys_get_rpmb_size(__int64 a1, int a2, unsigned int a3)
{
  unsigned int v3; // w19

  if ( a3 == 0 )
    return (unsigned int)-8;
  if ( a2 != 0 )
  {
    if ( a2 != 1 )
      return (unsigned int)-24;
    copy_to_user(a3, &dword_9405C8E0, 4);
    return 4;
  }
  else
  {
    v3 = -1;
    if ( MEMORY[0xFFFFFFFFE003CB98] <= 1 )
      return v3;
    log_printf("uboot don't set rpmb size, return error\n", &qword_94067DD8);
    return 0xFFFFFFFFLL;
  }
}

/* ===== process_rpmb_size_smc @ 0x94040BDC size 264 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall process_rpmb_size_smc(__int64 a1)
{
  unsigned int v1; // w21
  int v2; // w19
  __int64 result; // x0
  __int64 *v4; // x1
  __int64 v5; // x0
  int v6; // w20
  __int64 *v7; // [xsp+38h] [xbp+38h] BYREF

  v1 = *(_DWORD *)(a1 + 8);
  v7 = nullptr;
  v2 = vmm_map(-536460256, "sprdrpmbsize", 4096, &v7, 12, v1, 0, 48);
  if ( v2 != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("can not map phy 0x%x , ret:%d\n", v1, v2);
    return v2;
  }
  else
  {
    v4 = v7;
    v5 = *v7;
    qword_94067DD8 = *v7;
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    {
      log_printf((const char *)&loc_94054BA8, v5);
      v4 = v7;
    }
    v6 = vmm_free_region(-536460256, v4);
    result = 0;
    if ( v6 != 0 )
    {
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
        log_printf("can not unmap virt addr, ret:%d\n", v6);
      return v6;
    }
  }
  return result;
}

/* ===== process_rpmb_key_smc @ 0x94040CE4 size 264 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall process_rpmb_key_smc(__int64 a1)
{
  unsigned int v1; // w21
  int v2; // w19
  __int64 result; // x0
  int *v4; // x1
  int v5; // w0
  int v6; // w20
  int *v7; // [xsp+38h] [xbp+38h] BYREF

  v1 = *(_DWORD *)(a1 + 8);
  v7 = nullptr;
  v2 = vmm_map(-536460256, "sprdisrpmbkey", 4096, &v7, 12, v1, 0, 48);
  if ( v2 != 0 )
  {
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
      log_printf("can not map phy 0x%x , ret:%d\n", v1, v2);
    return v2;
  }
  else
  {
    v4 = v7;
    v5 = *v7;
    dword_9405C8E0 = *v7;
    if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
    {
      log_printf("is written rpmb key %d\n", v5);
      v4 = v7;
    }
    v6 = vmm_free_region(-536460256, v4);
    result = 0;
    if ( v6 != 0 )
    {
      if ( MEMORY[0xFFFFFFFFE003CB98] > 1 )
        log_printf("can not unmap virt addr, ret:%d\n", v6);
      return v6;
    }
  }
  return result;
}

/* ===== sprd_timer_get_counter @ 0x94040DEC size 68 ===== */
unsigned __int64 sprd_timer_get_counter()
{
  return 1000 * (0xFFFF00000000LL - *(_QWORD *)(MEMORY[0xFFFFFFFFE0047DE0] + 24LL)) / 0x21uLL;
}

/* ===== sprd_timer_secure_init @ 0x94040E30 size 204 ===== */
__int64 sprd_timer_secure_init()
{
  _DWORD *v0; // x0
  __int64 result; // x0

  if ( MEMORY[0xFFFFFFFFE0047DE8] != 0
    || (_DWORD)(result = sprd_iomap((__int64)"sprd_timer_secure", 839188480, 0x10000u, 2u, -536576536)) == 0 )
  {
    v0 = (_DWORD *)MEMORY[0xFFFFFFFFE0047DE0];
    if ( MEMORY[0xFFFFFFFFE0047DE0] == 0 )
    {
      result = sprd_iomap((__int64)"sprd_timer_secure", 838991872, 0x10000u, 2u, -536576544);
      if ( (_DWORD)result != 0 )
        return result;
      v0 = (_DWORD *)MEMORY[0xFFFFFFFFE0047DE0];
    }
    *MEMORY[0xFFFFFFFFE0047DE8] |= 6u;
    *v0 = 0;
    v0[1] = 0xFFFF;
    v0[4] |= 0x10001u;
    v0[4] |= 2u;
    result = -536577768;
    MEMORY[0xFFFFFFFFE0047918] = (__int64 (*)(void))-536736276LL;
  }
  return result;
}

/* ===== secboot_data_init @ 0x94040EFC size 48 ===== */
__int64 __fastcall secboot_data_init(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  __int64 result; // x0

  result = -536576248;
  if ( MEMORY[0xFFFFFFFFE0047F08] != 0 )
    return sprd_log(2u, "SECUREBOOTDataVal is not NULL.\n", a1, a2, a3, a4, a5, a6, a7, a8);
  MEMORY[0xFFFFFFFFE0047F08] = -536460568;
  return result;
}

/* ===== sprd_kbc_init @ 0x94040F2C size 240 ===== */
__int64 __fastcall sprd_kbc_init(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  double v16; // d0
  double v17; // d1
  double v18; // d2
  double v19; // d3
  double v20; // d4
  double v21; // d5
  double v22; // d6
  double v23; // d7
  unsigned int v24; // w0
  double v25; // d0
  double v26; // d1
  double v27; // d2
  double v28; // d3
  double v29; // d4
  double v30; // d5
  double v31; // d6
  double v32; // d7
  __int64 v33; // x2
  double v34; // d0
  double v35; // d1
  double v36; // d2
  double v37; // d3
  double v38; // d4
  double v39; // d5
  double v40; // d6
  double v41; // d7
  unsigned int v42; // w0
  const char *v43; // x1

  sprd_log(2u, "sprd_kbc_init() enter.\n", a1, a2, a3, a4, a5, a6, a7, a8);
  sprd_log(2u, "map size = %d \n", v8, v9, v10, v11, v12, v13, v14, v15, 0x10000);
  sprd_log(2u, "CTL_BASE_AON_APB = %p \n", v16, v17, v18, v19, v20, v21, v22, v23, 1076756480);
  v24 = sprd_iomap((__int64)"sprdsec", 1076559872, 0x10000u, 2u, (__int64)&qword_94067DF0);
  v33 = v24;
  if ( v24 != 0
    || (sprd_log(2u, "pmu_vaddr = %p \n", v25, v26, v27, v28, v29, v30, v31, v32, 0),
        sprd_log(2u, "CTL_BASE_PMU_APB = %p \n", v34, v35, v36, v37, v38, v39, v40, v41, 1076559872),
        v42 = sprd_iomap((__int64)"sprdsec", 1076756480, 0x10000u, 2u, (__int64)&qword_94067DF8),
        v33 = v42,
        v42 != 0) )
  {
    v43 = "can not map, err = %d \n";
  }
  else
  {
    v33 = 0;
    v43 = "aon_vaddr = %p \n";
  }
  return sprd_log(2u, v43, v25, v26, v27, v28, v29, v30, v31, v32, v33);
}

/* ===== sprd_dump_hex @ 0x9404101C size 204 ===== */
__int64 __fastcall sprd_dump_hex(
        __int64 a1,
        __int64 a2,
        int a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x20
  __int64 v22; // x19
  __int64 v23; // x2
  __int64 v24; // x2
  double v25; // d0
  double v26; // d1
  double v27; // d2
  double v28; // d3
  double v29; // d4
  double v30; // d5
  double v31; // d6
  double v32; // d7

  sprd_log(2u, "%s", a4, a5, a6, a7, a8, a9, a10, a11, a1);
  if ( a3 > 0 )
  {
    v21 = (unsigned int)(a3 - 1) + 1LL;
    v22 = 0;
    do
    {
      while ( (v22 & 0xF) != 0 )
      {
        v23 = *(unsigned __int8 *)(a2 + v22++);
        sprd_log(2u, " %02x", v13, v14, v15, v16, v17, v18, v19, v20, v23);
        if ( v22 == v21 )
          return sprd_log(2u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
      }
      sprd_log(2u, "\n%04x", v13, v14, v15, v16, v17, v18, v19, v20, (unsigned int)v22);
      v24 = *(unsigned __int8 *)(a2 + v22++);
      sprd_log(2u, " %02x", v25, v26, v27, v28, v29, v30, v31, v32, v24);
    }
    while ( v22 != v21 );
  }
  return sprd_log(2u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
}

/* ===== process_save_hubkey_smc @ 0x940410E8 size 368 ===== */
__int64 __fastcall process_save_hubkey_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  unsigned int v9; // w19
  __int64 v10; // x3
  unsigned int v11; // w19
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  __int64 v20; // x21
  unsigned int v21; // w19
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  unsigned int v30; // w19
  double v31; // d0
  double v32; // d1
  double v33; // d2
  double v34; // d3
  double v35; // d4
  double v36; // d5
  double v37; // d6
  double v38; // d7
  __int64 result; // x0
  __int64 v40; // [xsp+40h] [xbp+40h] BYREF
  __int64 *v41; // [xsp+48h] [xbp+48h] BYREF

  v9 = *(_DWORD *)(a1 + 8);
  v10 = *(unsigned int *)(a1 + 12);
  v41 = nullptr;
  v40 = 0;
  sprd_log(2u, "from uboot smc...addr:0x%x len:0x%x\n", a2, a3, a4, a5, a6, a7, a8, a9, v9, v10);
  v11 = sprd_iomap((__int64)"sprdsec", v9, 0x1000u, 0x30u, (__int64)&v41);
  if ( v11 != 0 )
  {
    sprd_log(2u, "can not map phy addr 1 , ret:%d\n", v12, v13, v14, v15, v16, v17, v18, v19, v11);
    return (int)v11;
  }
  else
  {
    v20 = v41[1];
    sprd_log(
      2u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v12,
      v13,
      v14,
      v15,
      v16,
      v17,
      v18,
      v19,
      *v41,
      (unsigned int)v20);
    v21 = sprd_iomap((__int64)"sprdsec", *v41, ((unsigned int)v20 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v40);
    if ( v21 != 0 )
    {
      sprd_log(2u, "can not map phy addr 2 , ret:%d\n", v22, v23, v24, v25, v26, v27, v28, v29, v21);
      return (int)v21;
    }
    else
    {
      sprd_log(2u, "##before process_ns_save_hubkey##### \n", v22, v23, v24, v25, v26, v27, v28, v29);
      process_save_pubkey_smc(v40);
      v30 = sprd_iounmap((__int64)v41);
      if ( v30 != 0 || (v30 = sprd_iounmap(v40), result = 0, v30 != 0) )
      {
        sprd_log(2u, "can not unmap virt addr, ret:%d\n", v31, v32, v33, v34, v35, v36, v37, v38, v30);
        return (int)v30;
      }
    }
  }
  return result;
}

/* ===== process_verify_img_smc @ 0x94041258 size 532 ===== */
__int64 __fastcall process_verify_img_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  unsigned int v9; // w19
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  unsigned int v18; // w19
  double v19; // d0
  double v20; // d1
  double v21; // d2
  double v22; // d3
  double v23; // d4
  double v24; // d5
  double v25; // d6
  double v26; // d7
  __int64 v27; // x21
  unsigned int v28; // w19
  double v29; // d0
  double v30; // d1
  double v31; // d2
  double v32; // d3
  double v33; // d4
  double v34; // d5
  double v35; // d6
  double v36; // d7
  unsigned int v37; // w19
  double v38; // d0
  double v39; // d1
  double v40; // d2
  double v41; // d3
  double v42; // d4
  double v43; // d5
  double v44; // d6
  double v45; // d7
  unsigned int v46; // w0
  double v47; // d0
  double v48; // d1
  double v49; // d2
  double v50; // d3
  double v51; // d4
  double v52; // d5
  double v53; // d6
  double v54; // d7
  unsigned int v55; // w19
  double v56; // d0
  double v57; // d1
  double v58; // d2
  double v59; // d3
  double v60; // d4
  double v61; // d5
  double v62; // d6
  double v63; // d7
  __int64 result; // x0
  __int64 v66; // [xsp+58h] [xbp+58h] BYREF
  __int64 v67; // [xsp+60h] [xbp+60h] BYREF
  __int64 *v68; // [xsp+68h] [xbp+68h] BYREF

  v68 = nullptr;
  v66 = 0;
  v67 = 0;
  secboot_data_init(a2, a3, a4, a5, a6, a7, a8, a9);
  v9 = *(_DWORD *)(a1 + 8);
  sprd_log(
    2u,
    "from uboot smc...addr:0x%x len:0x%x\n",
    v10,
    v11,
    v12,
    v13,
    v14,
    v15,
    v16,
    v17,
    v9,
    *(unsigned int *)(a1 + 12));
  v18 = sprd_iomap((__int64)"sprdsec", v9, 0x1000u, 0x30u, (__int64)&v68);
  if ( v18 != 0 )
  {
    sprd_log(2u, "can not map phy addr 1 , ret:%d\n", v19, v20, v21, v22, v23, v24, v25, v26, v18);
    return (int)v18;
  }
  else
  {
    v27 = v68[1];
    sprd_log(
      2u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v19,
      v20,
      v21,
      v22,
      v23,
      v24,
      v25,
      v26,
      *v68,
      (unsigned int)v27);
    v28 = sprd_iomap((__int64)"sprdsec", *v68, ((unsigned int)v27 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v66);
    if ( v28 != 0 )
    {
      sprd_log(2u, "can not map phy addr 2 , ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v28);
      return (int)v28;
    }
    else
    {
      sprd_log(
        2u,
        "from uboot smc...addr:0x%x len:0x%x flag:0x%x\n",
        v29,
        v30,
        v31,
        v32,
        v33,
        v34,
        v35,
        v36,
        v68[2],
        *((unsigned int *)v68 + 6),
        v68[4]);
      v37 = sprd_iomap((__int64)"sprdsec", v68[2], 0x1000u, 0x30u, (__int64)&v67);
      if ( v37 != 0 )
      {
        sprd_log(2u, "can not map phy addr 3 , ret:%d\n", v38, v39, v40, v41, v42, v43, v44, v45, v37);
        return (int)v37;
      }
      else
      {
        sprd_log(2u, (const char *)&loc_94054DA8, v38, v39, v40, v41, v42, v43, v44, v45);
        v46 = sprd_verify_img(v67, v66);
        sprd_log(2u, "sprd_verify_img , ret:%d\n", v47, v48, v49, v50, v51, v52, v53, v54, v46);
        v55 = sprd_iounmap((__int64)v68);
        if ( v55 != 0 || (v55 = sprd_iounmap(v66)) != 0 || (v55 = sprd_iounmap(v67), result = 0, v55 != 0) )
        {
          sprd_log(2u, "can not unmap virt addr, ret:%d\n", v56, v57, v58, v59, v60, v61, v62, v63, v55);
          return (int)v55;
        }
      }
    }
  }
  return result;
}

/* ===== kbc_image_verify @ 0x9404146C size 464 ===== */
__int64 __fastcall kbc_image_verify(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v10; // x19
  unsigned int v11; // w20
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  __int64 v36; // x0
  unsigned int v38; // w21
  double v39; // d0
  double v40; // d1
  double v41; // d2
  double v42; // d3
  double v43; // d4
  double v44; // d5
  double v45; // d6
  double v46; // d7
  double v47; // d0
  double v48; // d1
  double v49; // d2
  double v50; // d3
  double v51; // d4
  double v52; // d5
  double v53; // d6
  double v54; // d7
  double v55; // d0
  double v56; // d1
  double v57; // d2
  double v58; // d3
  double v59; // d4
  double v60; // d5
  double v61; // d6
  double v62; // d7
  unsigned int v63; // w21
  __int64 v64; // [xsp+58h] [xbp+58h] BYREF

  v64 = 0;
  sprd_log(2u, "kbc_image_verify() enter.\n", a2, a3, a4, a5, a6, a7, a8, a9);
  v10 = a1 + 112;
  v11 = 0;
  sprd_dump_hex((__int64)"pubkhash:", MEMORY[0xFFFFFFFFE0047F08] + 32LL, 32, v12, v13, v14, v15, v16, v17, v18, v19);
  while ( 1 )
  {
    if ( *(_QWORD *)(v10 - 112) == 0 )
    {
      sprd_log(2u, "invalid image [%d]\n", v20, v21, v22, v23, v24, v25, v26, v27, v11);
      if ( v11 == 3 )
        goto LABEL_5;
      goto LABEL_4;
    }
    sprd_log(
      2u,
      (const char *)&loc_94054E30,
      v20,
      v21,
      v22,
      v23,
      v24,
      v25,
      v26,
      v27,
      *(_QWORD *)(v10 - 112),
      *(unsigned int *)(v10 - 100));
    v38 = sprd_iomap(
            (__int64)"sprdsec",
            *(_QWORD *)(v10 - 112),
            (*(_DWORD *)(v10 - 100) & 0xFFFFF000) + 4096,
            0x19u,
            (__int64)&v64);
    if ( v38 != 0 )
    {
      sprd_log(2u, "can not map, ret = %d \n", v39, v40, v41, v42, v43, v44, v45, v46, v38);
      return (int)v38;
    }
    sprd_log(2u, "after map:pAddr = %p\n", v39, v40, v41, v42, v43, v44, v45, v46, v64);
    sprd_log(
      2u,
      "after map:pAddr = %p, img_len = 0x%x\n",
      v47,
      v48,
      v49,
      v50,
      v51,
      v52,
      v53,
      v54,
      v64,
      *(unsigned int *)(v10 - 104));
    sprd_verify_img_kbc(MEMORY[0xFFFFFFFFE0047F08] + 32LL, v64, *(unsigned int *)(v10 - 104));
    sprd_log(2u, (const char *)&loc_94054EA0, v55, v56, v57, v58, v59, v60, v61, v62, v64);
    v63 = sprd_iounmap(v64);
    if ( v63 != 0 )
      break;
    if ( v11 == 3 )
    {
LABEL_5:
      sprd_log(2u, "secboot_verify return success\n", v20, v21, v22, v23, v24, v25, v26, v27);
      v36 = sprd_log(2u, "will update version\n", v28, v29, v30, v31, v32, v33, v34, v35);
      update_sec_version(v36);
      return 0;
    }
LABEL_4:
    ++v11;
    v10 += 112;
    if ( v11 == 4 )
      goto LABEL_5;
  }
  sprd_log(2u, "can not unmap virt addr, ret = %d \n", v20, v21, v22, v23, v24, v25, v26, v27, v63);
  return (int)v63;
}

/* ===== kbc_set_bit @ 0x9404163C size 108 ===== */
__int64 __fastcall kbc_set_bit(
        unsigned int *a1,
        char a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7

  sprd_log(2u, "reg_addr = %p\n", a3, a4, a5, a6, a7, a8, a9, a10, a1);
  sprd_log(2u, (const char *)kbc_set_bit_log, v12, v13, v14, v15, v16, v17, v18, v19, *a1);
  *a1 |= 1 << a2;
  return sprd_log(2u, (const char *)kbc_set_bit_log2, v20, v21, v22, v23, v24, v25, v26, v27, *a1);
}

/* ===== kbc_clear_bit @ 0x940416A8 size 108 ===== */
__int64 __fastcall kbc_clear_bit(
        unsigned int *a1,
        char a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7

  sprd_log(2u, "reg_addr = %p\n", a3, a4, a5, a6, a7, a8, a9, a10, a1);
  sprd_log(2u, (const char *)kbc_set_bit_log, v12, v13, v14, v15, v16, v17, v18, v19, *a1);
  *a1 &= ~(1 << a2);
  return sprd_log(2u, (const char *)kbc_set_bit_log2, v20, v21, v22, v23, v24, v25, v26, v27, *a1);
}

/* ===== kbc_start_cp @ 0x94041714 size 140 ===== */
__int64 __fastcall kbc_start_cp(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  double v16; // d0
  double v17; // d1
  double v18; // d2
  double v19; // d3
  double v20; // d4
  double v21; // d5
  double v22; // d6
  double v23; // d7
  double v24; // d0
  double v25; // d1
  double v26; // d2
  double v27; // d3
  double v28; // d4
  double v29; // d5
  double v30; // d6
  double v31; // d7
  double v32; // d0
  double v33; // d1
  double v34; // d2
  double v35; // d3
  double v36; // d4
  double v37; // d5
  double v38; // d6
  double v39; // d7
  double v40; // d0
  double v41; // d1
  double v42; // d2
  double v43; // d3
  double v44; // d4
  double v45; // d5
  double v46; // d6
  double v47; // d7

  sprd_log(2u, "kbc_start_cp() enter \n", a1, a2, a3, a4, a5, a6, a7, a8);
  kbc_clear_bit((unsigned int *)0x48, 25, v8, v9, v10, v11, v12, v13, v14, v15);
  kbc_clear_bit((unsigned int *)0xCC, 18, v16, v17, v18, v19, v20, v21, v22, v23);
  kbc_clear_bit((unsigned int *)0x284, 10, v24, v25, v26, v27, v28, v29, v30, v31);
  kbc_clear_bit((unsigned int *)0xB0, 1, v32, v33, v34, v35, v36, v37, v38, v39);
  return sprd_log(2u, "kbc_start_cp() enter \n", v40, v41, v42, v43, v44, v45, v46, v47);
}

/* ===== kbc_stop_cp @ 0x940417A0 size 140 ===== */
__int64 __fastcall kbc_stop_cp(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  double v16; // d0
  double v17; // d1
  double v18; // d2
  double v19; // d3
  double v20; // d4
  double v21; // d5
  double v22; // d6
  double v23; // d7
  double v24; // d0
  double v25; // d1
  double v26; // d2
  double v27; // d3
  double v28; // d4
  double v29; // d5
  double v30; // d6
  double v31; // d7
  double v32; // d0
  double v33; // d1
  double v34; // d2
  double v35; // d3
  double v36; // d4
  double v37; // d5
  double v38; // d6
  double v39; // d7
  double v40; // d0
  double v41; // d1
  double v42; // d2
  double v43; // d3
  double v44; // d4
  double v45; // d5
  double v46; // d6
  double v47; // d7

  sprd_log(2u, "kbc_stop_cp() enter \n", a1, a2, a3, a4, a5, a6, a7, a8);
  kbc_set_bit((unsigned int *)0x284, 10, v8, v9, v10, v11, v12, v13, v14, v15);
  kbc_set_bit((unsigned int *)0xB0, 1, v16, v17, v18, v19, v20, v21, v22, v23);
  kbc_set_bit((unsigned int *)0xCC, 18, v24, v25, v26, v27, v28, v29, v30, v31);
  kbc_set_bit((unsigned int *)0x48, 25, v32, v33, v34, v35, v36, v37, v38, v39);
  return sprd_log(2u, "kbc_stop_cp() leave \n", v40, v41, v42, v43, v44, v45, v46, v47);
}

/* ===== process_get_lcs_smc @ 0x9404182C size 156 ===== */
__int64 __fastcall process_get_lcs_smc(__int64 a1)
{
  __int64 v1; // x1
  int v2; // w0
  double v3; // d0
  double v4; // d1
  double v5; // d2
  double v6; // d3
  double v7; // d4
  double v8; // d5
  double v9; // d6
  double v10; // d7
  __int64 v11; // x19
  unsigned int *v12; // x20
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  unsigned int *v22; // [xsp+28h] [xbp+28h] BYREF

  v1 = *(unsigned int *)(a1 + 8);
  v22 = nullptr;
  v2 = sprd_iomap((__int64)"fastboot", v1, 0x1000u, 0x30u, (__int64)&v22);
  v11 = v2;
  if ( v2 != 0 )
  {
    sprd_log(
      2u,
      "process_sip_call, case FUNCTYPE_GET_LCS can not map phy addr error:%ld\n",
      v3,
      v4,
      v5,
      v6,
      v7,
      v8,
      v9,
      v10,
      v2);
  }
  else
  {
    v12 = v22;
    v11 = (unsigned int)efuse_get_lcs(v22);
    sprd_log(
      2u,
      "process_sip_call, case FUNCTYPE_GET_LCS res:%ld, tmp is %d\n",
      v13,
      v14,
      v15,
      v16,
      v17,
      v18,
      v19,
      v20,
      v11,
      *v12);
    sprd_iounmap((__int64)v22);
  }
  return v11;
}

/* ===== process_get_socid_smc @ 0x940418C8 size 148 ===== */
__int64 __fastcall process_get_socid_smc(__int64 a1)
{
  __int64 v1; // x1
  int v2; // w0
  double v3; // d0
  double v4; // d1
  double v5; // d2
  double v6; // d3
  double v7; // d4
  double v8; // d5
  double v9; // d6
  double v10; // d7
  __int64 v11; // x19
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  __int64 v21; // [xsp+28h] [xbp+28h] BYREF

  v1 = *(unsigned int *)(a1 + 8);
  v21 = 0;
  v2 = sprd_iomap((__int64)"fastboot", v1, 0x1000u, 0x30u, (__int64)&v21);
  v11 = v2;
  if ( v2 != 0 )
  {
    sprd_log(
      2u,
      "process_sip_call, case FUNCTYPE_GET_LCS can not map phy addr error:%ld\n",
      v3,
      v4,
      v5,
      v6,
      v7,
      v8,
      v9,
      v10,
      v2);
  }
  else
  {
    v11 = (int)sprd_socid_get(v21);
    sprd_log(
      2u,
      "process_sip_call, case FUNCTYPE_GET_SOCID, res is:%ld\n",
      v12,
      v13,
      v14,
      v15,
      v16,
      v17,
      v18,
      v19,
      v11);
    sprd_iounmap(v21);
  }
  return v11;
}

/* ===== process_set_rma_smc @ 0x9404195C size 56 ===== */
__int64 process_set_rma_smc()
{
  __int64 v0; // x19
  double v1; // d0
  double v2; // d1
  double v3; // d2
  double v4; // d3
  double v5; // d4
  double v6; // d5
  double v7; // d6
  double v8; // d7

  v0 = (unsigned int)efuse_read_lock_status();
  sprd_log(2u, "process_sip_call, case FUNCTYPE_SET_RMA, res is:%ld\n", v1, v2, v3, v4, v5, v6, v7, v8, v0);
  return v0;
}

/* ===== cal_sha256 @ 0x94041994 size 164 ===== */
__int64 __fastcall cal_sha256(
        __int64 a1,
        unsigned int a2,
        __int64 a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v14; // d0
  double v15; // d1
  double v16; // d2
  double v17; // d3
  double v18; // d4
  double v19; // d5
  double v20; // d6
  double v21; // d7
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  double v31; // d0
  double v32; // d1
  double v33; // d2
  double v34; // d3
  double v35; // d4
  double v36; // d5
  double v37; // d6
  double v38; // d7

  sprd_log(1u, "%s(): ", a4, a5, a6, a7, a8, a9, a10, a11, "cal_sha256");
  sprd_log(1u, "enter cal_sha256 \r\n", v14, v15, v16, v17, v18, v19, v20, v21);
  if ( a1 != 0 && a3 != 0 )
    return sha256_csum_wd(a1, a2, a3);
  sprd_log(1u, "%s(): ", v22, v23, v24, v25, v26, v27, v28, v29, "cal_sha256");
  return sprd_log(1u, "\r\tthe pointer is error,pls check it\n", v31, v32, v33, v34, v35, v36, v37, v38);
}

/* ===== update_sec_version @ 0x94041A38 size 604 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall update_sec_version(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  double v16; // d0
  double v17; // d1
  double v18; // d2
  double v19; // d3
  double v20; // d4
  double v21; // d5
  double v22; // d6
  double v23; // d7
  double v24; // d0
  double v25; // d1
  double v26; // d2
  double v27; // d3
  double v28; // d4
  double v29; // d5
  double v30; // d6
  double v31; // d7
  double v32; // d0
  double v33; // d1
  double v34; // d2
  double v35; // d3
  double v36; // d4
  double v37; // d5
  double v38; // d6
  double v39; // d7
  double v40; // d0
  double v41; // d1
  double v42; // d2
  double v43; // d3
  double v44; // d4
  double v45; // d5
  double v46; // d6
  double v47; // d7
  double v48; // d0
  double v49; // d1
  double v50; // d2
  double v51; // d3
  double v52; // d4
  double v53; // d5
  double v54; // d6
  double v55; // d7
  unsigned int v56; // w1
  unsigned int v57; // w19
  int v58; // w2
  double v59; // d0
  double v60; // d1
  double v61; // d2
  double v62; // d3
  double v63; // d4
  double v64; // d5
  double v65; // d6
  double v66; // d7
  double v67; // d0
  double v68; // d1
  double v69; // d2
  double v70; // d3
  double v71; // d4
  double v72; // d5
  double v73; // d6
  double v74; // d7
  double v75; // d0
  double v76; // d1
  double v77; // d2
  double v78; // d3
  double v79; // d4
  double v80; // d5
  double v81; // d6
  double v82; // d7
  double v84; // d0
  double v85; // d1
  double v86; // d2
  double v87; // d3
  double v88; // d4
  double v89; // d5
  double v90; // d6
  double v91; // d7
  const char *v92; // x1

  sprd_log(1u, "%s(): ", a1, a2, a3, a4, a5, a6, a7, a8, "update_sec_version");
  sprd_log(1u, (const char *)&loc_94055108, v8, v9, v10, v11, v12, v13, v14, v15);
  sprd_log(1u, "%s(): ", v16, v17, v18, v19, v20, v21, v22, v23, "update_sec_version");
  sprd_log(1u, "reset index \r\n", v24, v25, v26, v27, v28, v29, v30, v31);
  dword_94067E00 = 0;
  sprd_log(1u, "%s(): ", v32, v33, v34, v35, v36, v37, v38, v39, "update_sec_version");
  sprd_log(
    1u,
    "num = %d \r\n",
    v40,
    v41,
    v42,
    v43,
    v44,
    v45,
    v46,
    v47,
    *(unsigned int *)(MEMORY[0xFFFFFFFFE0047F08] + 148LL));
  v56 = *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 148LL);
  if ( v56 != 0 )
  {
    v57 = *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 72LL);
    if ( v56 <= 1
      || *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 80LL) == v57
      && (v56 == 2
       || (v58 = *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 88LL)) == v57
       && (v56 == 3
        || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 96LL)
        && (v56 == 4
         || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 104LL)
         && (v56 == 5
          || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 112LL)
          && (v56 == 6
           || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 120LL)
           && (v56 == 7
            || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 128LL)
            && (v56 == 8
             || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 136LL)
             && (v56 == 9 || v58 == *(_DWORD *)(MEMORY[0xFFFFFFFFE0047F08] + 144LL))))))))) )
    {
      sprd_log(1u, "%s(): ", v48, v49, v50, v51, v52, v53, v54, v55, "update_sec_version");
      sprd_log(1u, "nosecure_update_version = %d \r\n", v59, v60, v61, v62, v63, v64, v65, v66, v57);
      if ( v57 > 0xFFFF )
      {
        sprd_log(1u, "%s(): ", v67, v68, v69, v70, v71, v72, v73, v74, "update_sec_version");
        sprd_log(1u, (const char *)&loc_94055188, v75, v76, v77, v78, v79, v80, v81, v82);
        return efuse_write_version(1, v57);
      }
      sprd_log(1u, "%s(): ", v67, v68, v69, v70, v71, v72, v73, v74, "update_sec_version");
      v92 = "no need to update \r\n";
    }
    else
    {
      sprd_log(1u, "%s(): ", v48, v49, v50, v51, v52, v53, v54, v55, "update_sec_version");
      v92 = "\r\rollback version not unified\n";
    }
  }
  else
  {
    sprd_log(1u, "%s(): ", v48, v49, v50, v51, v52, v53, v54, v55, "update_sec_version");
    v92 = "version num is 0 ! \r\n";
  }
  return sprd_log(1u, v92, v84, v85, v86, v87, v88, v89, v90, v91);
}

/* ===== sprd_anti_rollback @ 0x94041C94 size 604 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_anti_rollback(
        unsigned int a1,
        unsigned int a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  unsigned int v36; // w19
  double v37; // d0
  double v38; // d1
  double v39; // d2
  double v40; // d3
  double v41; // d4
  double v42; // d5
  double v43; // d6
  double v44; // d7
  double v46; // d0
  double v47; // d1
  double v48; // d2
  double v49; // d3
  double v50; // d4
  double v51; // d5
  double v52; // d6
  double v53; // d7
  double v54; // d0
  double v55; // d1
  double v56; // d2
  double v57; // d3
  double v58; // d4
  double v59; // d5
  double v60; // d6
  double v61; // d7
  double v62; // d0
  double v63; // d1
  double v64; // d2
  double v65; // d3
  double v66; // d4
  double v67; // d5
  double v68; // d6
  double v69; // d7
  double v70; // d0
  double v71; // d1
  double v72; // d2
  double v73; // d3
  double v74; // d4
  double v75; // d5
  double v76; // d6
  double v77; // d7
  double v78; // d0
  double v79; // d1
  double v80; // d2
  double v81; // d3
  double v82; // d4
  double v83; // d5
  double v84; // d6
  double v85; // d7
  double v86; // d0
  double v87; // d1
  double v88; // d2
  double v89; // d3
  double v90; // d4
  double v91; // d5
  double v92; // d6
  double v93; // d7
  double v94; // d0
  double v95; // d1
  double v96; // d2
  double v97; // d3
  double v98; // d4
  double v99; // d5
  double v100; // d6
  double v101; // d7
  double v102; // d0
  double v103; // d1
  double v104; // d2
  double v105; // d3
  double v106; // d4
  double v107; // d5
  double v108; // d6
  double v109; // d7
  double v110; // d0
  double v111; // d1
  double v112; // d2
  double v113; // d3
  double v114; // d4
  double v115; // d5
  double v116; // d6
  double v117; // d7

  sprd_log(1u, "%s(): ", a3, a4, a5, a6, a7, a8, a9, a10, "sprd_anti_rollback");
  sprd_log(1u, "image type = %d\n", v12, v13, v14, v15, v16, v17, v18, v19, a1);
  if ( a1 == 1 )
  {
    efuse_read_version(0, &dword_9405C8E8);
    sprd_log(1u, "%s(): ", v102, v103, v104, v105, v106, v107, v108, v109, "sprd_anti_rollback");
    sprd_log(1u, "read efuse version: 0X%x\n", v110, v111, v112, v113, v114, v115, v116, v117, 4660);
    v36 = 1;
    sprd_log(1u, "%s(): ", v46, v47, v48, v49, v50, v51, v52, v53, "sprd_anti_rollback");
    sprd_log(
      1u,
      "Trusted_rollback_version = 0X%x  certversion = 0X%x\n",
      v54,
      v55,
      v56,
      v57,
      v58,
      v59,
      v60,
      v61,
      4660,
      a2);
    if ( a2 < 0x1234 )
    {
      sprd_log(1u, "%s(): ", v62, v63, v64, v65, v66, v67, v68, v69, "sprd_anti_rollback");
      v36 = 0;
      sprd_log(1u, "SEC ANTI_ROLLBACK ERR version = 0X%x\n", v70, v71, v72, v73, v74, v75, v76, v77, a2);
    }
    return v36;
  }
  if ( a1 == 0 )
  {
    efuse_read_version(1, &dword_9405C8E4);
    sprd_log(1u, "%s(): ", v86, v87, v88, v89, v90, v91, v92, v93, "sprd_anti_rollback");
    sprd_log(1u, "version efuse: %d\n", v94, v95, v96, v97, v98, v99, v100, v101, 0xFFFF);
    sprd_log(1u, "%s(): ", v28, v29, v30, v31, v32, v33, v34, v35, "sprd_anti_rollback");
    v36 = 0;
    sprd_log(1u, "NOSEC ANTI_ROLLBACK ERR version = %x\n", v37, v38, v39, v40, v41, v42, v43, v44, a2);
    return v36;
  }
  sprd_log(1u, "%s(): ", v20, v21, v22, v23, v24, v25, v26, v27, "sprd_anti_rollback");
  sprd_log(1u, "certtype mismatch!! \r\n", v78, v79, v80, v81, v82, v83, v84, v85);
  return 0;
}

/* ===== sprd_verify_cert @ 0x94041EF0 size 740 ===== */
__int64 __fastcall sprd_verify_cert(
        __int64 a1,
        __int64 a2,
        unsigned __int8 *a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  unsigned int v14; // w19
  double v15; // d0
  double v16; // d1
  double v17; // d2
  double v18; // d3
  double v19; // d4
  double v20; // d5
  double v21; // d6
  double v22; // d7
  double v23; // d0
  double v24; // d1
  double v25; // d2
  double v26; // d3
  double v27; // d4
  double v28; // d5
  double v29; // d6
  double v30; // d7
  unsigned int v31; // w25
  double v32; // d0
  double v33; // d1
  double v34; // d2
  double v35; // d3
  double v36; // d4
  double v37; // d5
  double v38; // d6
  double v39; // d7
  double v41; // d0
  double v42; // d1
  double v43; // d2
  double v44; // d3
  double v45; // d4
  double v46; // d5
  double v47; // d6
  double v48; // d7
  double v49; // d0
  double v50; // d1
  double v51; // d2
  double v52; // d3
  double v53; // d4
  double v54; // d5
  double v55; // d6
  double v56; // d7
  double v57; // d0
  double v58; // d1
  double v59; // d2
  double v60; // d3
  double v61; // d4
  double v62; // d5
  double v63; // d6
  double v64; // d7
  double v65; // d0
  double v66; // d1
  double v67; // d2
  double v68; // d3
  double v69; // d4
  double v70; // d5
  double v71; // d6
  double v72; // d7
  unsigned int v73; // w0
  double v74; // d0
  double v75; // d1
  double v76; // d2
  double v77; // d3
  double v78; // d4
  double v79; // d5
  double v80; // d6
  double v81; // d7
  double v82; // d0
  double v83; // d1
  double v84; // d2
  double v85; // d3
  double v86; // d4
  double v87; // d5
  double v88; // d6
  double v89; // d7
  double v90; // d0
  double v91; // d1
  double v92; // d2
  double v93; // d3
  double v94; // d4
  double v95; // d5
  double v96; // d6
  double v97; // d7
  double v98; // d0
  double v99; // d1
  double v100; // d2
  double v101; // d3
  double v102; // d4
  double v103; // d5
  double v104; // d6
  double v105; // d7
  double v106; // d0
  double v107; // d1
  double v108; // d2
  double v109; // d3
  double v110; // d4
  double v111; // d5
  double v112; // d6
  double v113; // d7
  double v114; // d0
  double v115; // d1
  double v116; // d2
  double v117; // d3
  double v118; // d4
  double v119; // d5
  double v120; // d6
  double v121; // d7
  double v122; // d0
  double v123; // d1
  double v124; // d2
  double v125; // d3
  double v126; // d4
  double v127; // d5
  double v128; // d6
  double v129; // d7
  double v130; // d0
  double v131; // d1
  double v132; // d2
  double v133; // d3
  double v134; // d4
  double v135; // d5
  double v136; // d6
  double v137; // d7
  double v138; // d0
  double v139; // d1
  double v140; // d2
  double v141; // d3
  double v142; // d4
  double v143; // d5
  double v144; // d6
  double v145; // d7
  double v146; // d0
  double v147; // d1
  double v148; // d2
  double v149; // d3
  double v150; // d4
  double v151; // d5
  double v152; // d6
  double v153; // d7
  _BYTE v154[32]; // [xsp+60h] [xbp+60h] BYREF

  v14 = *a3;
  sprd_log(1u, "%s(): ", a4, a5, a6, a7, a8, a9, a10, a11, "sprd_verify_cert");
  sprd_log(1u, "#####cert type: %d #######\n", v15, v16, v17, v18, v19, v20, v21, v22, v14);
  if ( v14 <= 1 )
  {
    if ( v14 == 1 )
    {
      cal_sha256((__int64)(a3 + 4), 0x108u, (__int64)v154, v23, v24, v25, v26, v27, v28, v29, v30);
      if ( (unsigned int)memcmp_simple(a2, a3 + 268, 32) != 0 || (unsigned int)memcmp_simple(a1, v154, 32) != 0 )
      {
        v31 = 0;
        sprd_log(1u, "%s(): ", v98, v99, v100, v101, v102, v103, v104, v105, "sprd_verify_cert");
        sprd_log(1u, "cmp hash of pubk diffent\r\n", v106, v107, v108, v109, v110, v111, v112, v113);
        return v31;
      }
      RSA_PubDec((__int64)(a3 + 8), (__int64)(a3 + 12), *((_DWORD *)a3 + 1), (__int64)(a3 + 340), -536576504);
      if ( (unsigned int)memcmp_simple(a3 + 268, -536576504, 72) == 0 )
      {
        sprd_log(1u, "%s(): ", v74, v75, v76, v77, v78, v79, v80, v81, "sprd_verify_cert");
        sprd_log(1u, "\nRSA verify Success\n", v138, v139, v140, v141, v142, v143, v144, v145);
        return (unsigned int)sprd_anti_rollback(
                               *((_DWORD *)a3 + 83),
                               *((_DWORD *)a3 + 84),
                               v146,
                               v147,
                               v148,
                               v149,
                               v150,
                               v151,
                               v152,
                               v153);
      }
    }
    else
    {
      cal_sha256((__int64)(a3 + 4), 0x108u, (__int64)v154, v23, v24, v25, v26, v27, v28, v29, v30);
      v31 = memcmp_simple(a2, a3 + 268, 32);
      if ( v31 != 0 )
      {
        v31 = 0;
        sprd_log(1u, "%s(): ", v41, v42, v43, v44, v45, v46, v47, v48, "sprd_verify_cert");
        sprd_log(1u, "cmp hash data diffent\r\n", v114, v115, v116, v117, v118, v119, v120, v121);
        return v31;
      }
      sprd_log(1u, "%s(): ", v41, v42, v43, v44, v45, v46, v47, v48, "sprd_verify_cert");
      sprd_log(1u, "cmp hash data SUCCESS\r\n", v49, v50, v51, v52, v53, v54, v55, v56);
      if ( (unsigned int)memcmp_simple(a1, v154, 32) != 0 )
      {
        sprd_log(1u, "%s(): ", v57, v58, v59, v60, v61, v62, v63, v64, "sprd_verify_cert");
        sprd_log(1u, "cmp hash key diffent\r\n", v122, v123, v124, v125, v126, v127, v128, v129);
        return v31;
      }
      sprd_log(1u, "%s(): ", v57, v58, v59, v60, v61, v62, v63, v64, "sprd_verify_cert");
      sprd_log(1u, "cmp hash key SUCCESS\r\n", v65, v66, v67, v68, v69, v70, v71, v72);
      v73 = RSA_PubDec((__int64)(a3 + 8), (__int64)(a3 + 12), *((_DWORD *)a3 + 1), (__int64)(a3 + 308), -536576504);
      if ( (unsigned int)memcmp_simple(a3 + 268, -536576504, v73) == 0 )
      {
        sprd_log(1u, "%s(): ", v74, v75, v76, v77, v78, v79, v80, v81, "sprd_verify_cert");
        sprd_log(1u, "\nRSA verify Success\n", v82, v83, v84, v85, v86, v87, v88, v89);
        return (unsigned int)sprd_anti_rollback(
                               *((_DWORD *)a3 + 75),
                               *((_DWORD *)a3 + 76),
                               v90,
                               v91,
                               v92,
                               v93,
                               v94,
                               v95,
                               v96,
                               v97);
      }
    }
    v31 = 0;
    sprd_log(1u, "%s(): ", v74, v75, v76, v77, v78, v79, v80, v81, "sprd_verify_cert");
    sprd_log(1u, "\nRSA verify err\n", v130, v131, v132, v133, v134, v135, v136, v137);
    return v31;
  }
  v31 = 0;
  sprd_log(1u, "%s(): ", v23, v24, v25, v26, v27, v28, v29, v30, "sprd_verify_cert");
  sprd_log(1u, "invalid cert type %d!!", v32, v33, v34, v35, v36, v37, v38, v39, v14);
  return v31;
}

/* ===== sprd_get_sechdr_addr @ 0x940421D4 size 108 ===== */
__int64 __fastcall sprd_get_sechdr_addr(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7

  if ( a1 != 0 )
    return a1 + *(unsigned int *)(a1 + 48) + 512LL;
  sprd_log(1u, "%s(): ", a2, a3, a4, a5, a6, a7, a8, a9, "sprd_get_sechdr_addr");
  sprd_log(1u, "\r\t input of get_sechdr_Addr err\n", v10, v11, v12, v13, v14, v15, v16, v17);
  return MEMORY[0x30] + 512LL;
}

/* ===== sprd_get_img_addr @ 0x94042240 size 40 ===== */
__int64 __fastcall sprd_get_img_addr(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  return a1 + *(_QWORD *)(sprd_get_sechdr_addr(a1, a2, a3, a4, a5, a6, a7, a8, a9) + 24);
}

/* ===== sprd_get_cert_addr @ 0x94042268 size 40 ===== */
__int64 __fastcall sprd_get_cert_addr(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  return a1 + *(_QWORD *)(sprd_get_sechdr_addr(a1, a2, a3, a4, a5, a6, a7, a8, a9) + 40);
}

/* ===== sprd_get_img_end @ 0x94042290 size 16 ===== */
__int64 __fastcall sprd_get_img_end(__int64 a1, unsigned int a2)
{
  return a1 + a2 + 96LL;
}

/* ===== sprd_save_img_hash @ 0x940422A0 size 124 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall sprd_save_img_hash(__int64 a1)
{
  memcpy_simple(MEMORY[0xFFFFFFFFE0047F08] + 32LL, a1, 32);
  dword_94067E04 = 1;
  return 1;
}

/* ===== sprd_verify_efuse_hash @ 0x9404231C size 80 ===== */
__int64 __fastcall sprd_verify_efuse_hash(__int64 a1)
{
  int v3; // [xsp+2Ch] [xbp+2Ch] BYREF

  v3 = 0;
  efuse_is_secure(&v3);
  if ( v3 != 0 )
    return efuse_read_ns_blocks(a1);
  else
    return efuse_read_secure_blocks(a1);
}

/* ===== sprd_verify_img @ 0x9404236C size 720 ===== */
__int64 __fastcall sprd_verify_img(
        __int64 a1,
        __int64 a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  __int64 v12; // x25
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x20
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  double v30; // d0
  double v31; // d1
  double v32; // d2
  double v33; // d3
  double v34; // d4
  double v35; // d5
  double v36; // d6
  double v37; // d7
  double v38; // d0
  double v39; // d1
  double v40; // d2
  double v41; // d3
  double v42; // d4
  double v43; // d5
  double v44; // d6
  double v45; // d7
  __int16 v46; // w0
  char *v47; // x1
  __int64 v48; // x27
  unsigned int v49; // w28
  unsigned int v50; // w26
  double v51; // d0
  double v52; // d1
  double v53; // d2
  double v54; // d3
  double v55; // d4
  double v56; // d5
  double v57; // d6
  double v58; // d7
  double v59; // d0
  double v60; // d1
  double v61; // d2
  double v62; // d3
  double v63; // d4
  double v64; // d5
  double v65; // d6
  double v66; // d7
  double v67; // d0
  double v68; // d1
  double v69; // d2
  double v70; // d3
  double v71; // d4
  double v72; // d5
  double v73; // d6
  double v74; // d7
  double v75; // d0
  double v76; // d1
  double v77; // d2
  double v78; // d3
  double v79; // d4
  double v80; // d5
  double v81; // d6
  double v82; // d7
  unsigned __int8 *v83; // x20
  double v84; // d0
  double v85; // d1
  double v86; // d2
  double v87; // d3
  double v88; // d4
  double v89; // d5
  double v90; // d6
  double v91; // d7
  double v92; // d0
  double v93; // d1
  double v94; // d2
  double v95; // d3
  double v96; // d4
  double v97; // d5
  double v98; // d6
  double v99; // d7
  double v100; // d0
  double v101; // d1
  double v102; // d2
  double v103; // d3
  double v104; // d4
  double v105; // d5
  double v106; // d6
  double v107; // d7
  __int64 result; // x0
  double v109; // d0
  double v110; // d1
  double v111; // d2
  double v112; // d3
  double v113; // d4
  double v114; // d5
  double v115; // d6
  double v116; // d7
  int v117; // [xsp+6Ch] [xbp+6Ch] BYREF
  _BYTE v118[32]; // [xsp+70h] [xbp+70h] BYREF
  __int64 v119; // [xsp+90h] [xbp+90h] BYREF
  _QWORD v120[2]; // [xsp+98h] [xbp+98h] BYREF
  __int64 v121; // [xsp+A8h] [xbp+A8h] BYREF
  _QWORD v122[2]; // [xsp+B0h] [xbp+B0h] BYREF
  __int64 v123; // [xsp+C0h] [xbp+C0h] BYREF
  _QWORD v124[2]; // [xsp+C8h] [xbp+C8h] BYREF
  __int64 v125; // [xsp+D8h] [xbp+D8h] BYREF
  _QWORD v126[2]; // [xsp+E0h] [xbp+E0h] BYREF

  v12 = sprd_get_sechdr_addr(a2, a3, a4, a5, a6, a7, a8, a9, a10);
  v21 = sprd_get_img_addr(a2, v13, v14, v15, v16, v17, v18, v19, v20);
  if ( (unsigned int)memcmp_simple(v21, "SCI1", 5) == 0 )
  {
    sprd_log(1u, "%s(): ", v22, v23, v24, v25, v26, v27, v28, v29, "sprd_verify_img");
    sprd_log(1u, "the image is new packed modem image\n", v30, v31, v32, v33, v34, v35, v36, v37);
    v119 = 0;
    v120[0] = 0;
    v120[1] = 0;
    v121 = 0;
    v122[0] = 0;
    v122[1] = 0;
    v123 = 0;
    v124[0] = 0;
    v124[1] = 0;
    v125 = 0;
    v126[0] = 0;
    v126[1] = 0;
    memcpy_simple(&v119, v21, 96);
    if ( (unsigned int)memcmp_simple(&v119, "SCI1", 5) == 0 )
    {
      v46 = WORD2(v120[0]);
      if ( BYTE4(v120[0]) == 1 )
      {
        v47 = (char *)v120 + 4;
      }
      else
      {
        v46 = v121;
        v47 = (char *)&v121;
        if ( (unsigned __int8)v121 != 1 )
        {
          v46 = WORD2(v122[0]);
          v47 = (char *)v122 + 4;
          if ( BYTE4(v122[0]) != 1 )
          {
            v46 = v123;
            v47 = (char *)&v123;
            if ( (unsigned __int8)v123 != 1 )
            {
              v46 = WORD2(v124[0]);
              v47 = (char *)v124 + 4;
              if ( BYTE4(v124[0]) != 1 )
              {
                v46 = v125;
                v47 = (char *)&v125;
                if ( (unsigned __int8)v125 != 1 )
                {
                  v46 = WORD2(v126[0]);
                  v47 = (char *)v126 + 4;
                  if ( BYTE4(v126[0]) != 1 )
                  {
                    v48 = 0;
                    v49 = 0;
                    sprd_log(1u, "%s(): ", v38, v39, v40, v41, v42, v43, v44, v45, "get_modem_info");
                    v50 = 0;
                    sprd_log(1u, "no MODEM exe found in SCI header!", v51, v52, v53, v54, v55, v56, v57, v58);
LABEL_11:
                    v21 += v48;
                    sprd_log(1u, "%s(): ", v38, v39, v40, v41, v42, v43, v44, v45, "sprd_verify_img");
                    sprd_log(1u, "modem offset: %d, length: %d\n", v59, v60, v61, v62, v63, v64, v65, v66, v50, v49);
                    goto LABEL_12;
                  }
                }
              }
            }
          }
        }
      }
      v50 = *((_DWORD *)v47 + 1);
      v49 = *((_DWORD *)v47 + 2);
      if ( (v46 & 0x400) != 0 )
        v50 += 20;
      v48 = v50;
      goto LABEL_11;
    }
    v48 = 0;
    v49 = 0;
    sprd_log(1u, "%s(): ", v38, v39, v40, v41, v42, v43, v44, v45, "get_modem_info");
    v50 = 0;
    sprd_log(1u, "old image format!\n", v109, v110, v111, v112, v113, v114, v115, v116);
    goto LABEL_11;
  }
LABEL_12:
  v117 = 0;
  memset_simple(&v119, 255, 32);
  sprd_save_img_hash(a1);
  cal_sha256(v21, *(_DWORD *)(v12 + 16), (__int64)v118, v67, v68, v69, v70, v71, v72, v73, v74);
  v83 = (unsigned __int8 *)sprd_get_cert_addr(a2, v75, v76, v77, v78, v79, v80, v81, v82);
  if ( (unsigned int)memcmp_simple(a1, &v119, 32) == 0 )
  {
    efuse_get_lcs(&v117);
    if ( v117 != 5 )
    {
      sprd_log(1u, "%s(): ", v92, v93, v94, v95, v96, v97, v98, v99, "sprd_verify_img");
      sprd_log(1u, "not secure lcs\n", v100, v101, v102, v103, v104, v105, v106, v107);
      return 1;
    }
    sprd_verify_efuse_hash(a1);
  }
  result = sprd_verify_cert(a1, (__int64)v118, v83, v84, v85, v86, v87, v88, v89, v90, v91);
  if ( (_DWORD)result == 0 )
  {
    while ( 1 )
      ;
  }
  return result;
}

/* ===== sprd_verify_img_kbc @ 0x9404263C size 316 ===== */
__int64 __fastcall sprd_verify_img_kbc(
        __int64 a1,
        __int64 a2,
        unsigned int a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v14; // d0
  double v15; // d1
  double v16; // d2
  double v17; // d3
  double v18; // d4
  double v19; // d5
  double v20; // d6
  double v21; // d7
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  double v30; // d0
  double v31; // d1
  double v32; // d2
  double v33; // d3
  double v34; // d4
  double v35; // d5
  double v36; // d6
  double v37; // d7
  double v38; // d0
  double v39; // d1
  double v40; // d2
  double v41; // d3
  double v42; // d4
  double v43; // d5
  double v44; // d6
  double v45; // d7
  double v46; // d0
  double v47; // d1
  double v48; // d2
  double v49; // d3
  double v50; // d4
  double v51; // d5
  double v52; // d6
  double v53; // d7
  double v54; // d0
  double v55; // d1
  double v56; // d2
  double v57; // d3
  double v58; // d4
  double v59; // d5
  double v60; // d6
  double v61; // d7
  unsigned __int8 *v62; // x22
  double v63; // d0
  double v64; // d1
  double v65; // d2
  double v66; // d3
  double v67; // d4
  double v68; // d5
  double v69; // d6
  double v70; // d7
  double v71; // d0
  double v72; // d1
  double v73; // d2
  double v74; // d3
  double v75; // d4
  double v76; // d5
  double v77; // d6
  double v78; // d7
  double v79; // d0
  double v80; // d1
  double v81; // d2
  double v82; // d3
  double v83; // d4
  double v84; // d5
  double v85; // d6
  double v86; // d7
  __int64 result; // x0
  double v88; // d0
  double v89; // d1
  double v90; // d2
  double v91; // d3
  double v92; // d4
  double v93; // d5
  double v94; // d6
  double v95; // d7
  double v96; // d0
  double v97; // d1
  double v98; // d2
  double v99; // d3
  double v100; // d4
  double v101; // d5
  double v102; // d6
  double v103; // d7
  _BYTE v104[32]; // [xsp+40h] [xbp+40h] BYREF

  sprd_log(1u, "%s(): ", a4, a5, a6, a7, a8, a9, a10, a11, "sprd_verify_img_kbc");
  sprd_log(
    1u,
    "sprd_verify_img_kbc enter imgbuf = %p imgSize = 0x%x \r\n",
    v14,
    v15,
    v16,
    v17,
    v18,
    v19,
    v20,
    v21,
    a2,
    a3);
  memset_simple(v104, 255, 32);
  sprd_log(1u, "%s(): ", v22, v23, v24, v25, v26, v27, v28, v29, "sprd_verify_img_kbc");
  sprd_log(1u, "call cal_sha256() imgSize = 0x%x\r\n", v30, v31, v32, v33, v34, v35, v36, v37, a3);
  cal_sha256(a2, a3, (__int64)v104, v38, v39, v40, v41, v42, v43, v44, v45);
  sprd_log(1u, "%s(): ", v46, v47, v48, v49, v50, v51, v52, v53, "sprd_verify_img_kbc");
  sprd_log(1u, (const char *)&loc_940554F8, v54, v55, v56, v57, v58, v59, v60, v61);
  v62 = (unsigned __int8 *)sprd_get_img_end(a2, a3);
  sprd_log(1u, "%s(): ", v63, v64, v65, v66, v67, v68, v69, v70, "sprd_verify_img_kbc");
  sprd_log(1u, (const char *)&loc_94055520, v71, v72, v73, v74, v75, v76, v77, v78);
  result = sprd_verify_cert(a1, (__int64)v104, v62, v79, v80, v81, v82, v83, v84, v85, v86);
  if ( (_DWORD)result == 0 )
  {
    sprd_log(1u, "%s(): ", v88, v89, v90, v91, v92, v93, v94, v95, "sprd_verify_img_kbc");
    sprd_log(1u, "sprd_verify_cert() failed , enter while(1) \r\n", v96, v97, v98, v99, v100, v101, v102, v103);
    while ( 1 )
      ;
  }
  return result;
}

/* ===== sprd_get_pubkey @ 0x94042778 size 44 ===== */
__int64 __fastcall sprd_get_pubkey(
        __int64 a1,
        __int64 a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  __int64 v11; // x0

  v11 = sprd_get_cert_addr(a1, a3, a4, a5, a6, a7, a8, a9, a10);
  return memcpy_simple(a2, v11 + 4, 264);
}

/* ===== process_save_pubkey_smc @ 0x940427A4 size 124 ===== */
__int64 __fastcall process_save_pubkey_smc(__int64 a1)
{
  double v2; // d0
  double v3; // d1
  double v4; // d2
  double v5; // d3
  double v6; // d4
  double v7; // d5
  double v8; // d6
  double v9; // d7
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  _BYTE v19[32]; // [xsp+38h] [xbp+38h] BYREF
  _BYTE v20[264]; // [xsp+58h] [xbp+58h] BYREF

  memset(v20, 0, 264);
  memset(v19, 0, sizeof(v19));
  sprd_get_pubkey(a1, (__int64)v20, v2, v3, v4, v5, v6, v7, v8, v9);
  cal_sha256((__int64)v20, 0x108u, (__int64)v19, v10, v11, v12, v13, v14, v15, v16, v17);
  return memcpy_simple(MEMORY[0xFFFFFFFFE0047F08], v19, 32);
}

/* ===== memset_simple @ 0x94042820 size 40 ===== */
_BYTE *__fastcall memset_simple(_BYTE *result, char a2, int a3)
{
  __int64 v3; // x3
  _BYTE *v4; // x2
  _BYTE *v5; // x3

  v3 = (unsigned int)(a3 - 1);
  if ( a3 != 0 )
  {
    v4 = result;
    v5 = &result[v3 + 1];
    do
      *v4++ = a2;
    while ( v4 != v5 );
  }
  return result;
}

/* ===== memcpy_simple @ 0x94042848 size 40 ===== */
__int64 __fastcall memcpy_simple(__int64 result, __int64 a2, int a3)
{
  __int64 v3; // x4
  __int64 v4; // x2
  __int64 v5; // x4

  v3 = (unsigned int)(a3 - 1);
  if ( a3 != 0 )
  {
    v4 = 0;
    v5 = v3 + 1;
    do
    {
      *(_BYTE *)(result + v4) = *(_BYTE *)(a2 + v4);
      ++v4;
    }
    while ( v4 != v5 );
  }
  return result;
}

/* ===== memcmp_simple @ 0x94042870 size 92 ===== */
__int64 __fastcall memcmp_simple(unsigned __int8 *a1, unsigned __int8 *a2, int a3)
{
  unsigned __int8 *v3; // x3
  __int64 result; // x0
  unsigned __int8 *v5; // x5
  unsigned int v6; // w2

  v3 = a1;
  if ( a3 == 0 )
    return 0;
  result = *a1 - (unsigned int)*a2;
  if ( (_DWORD)result == 0 )
  {
    v5 = &v3[a3 - 1 + 1];
    while ( 1 )
    {
      ++v3;
      ++a2;
      if ( v3 == v5 )
        break;
      v6 = *v3 - *a2;
      if ( v6 != 0 )
        return v6;
    }
  }
  return result;
}

/* ===== kbc_verify_init @ 0x940428CC size 64 ===== */
__int64 __fastcall kbc_verify_init(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  __int64 result; // x0
  double v9; // d0
  double v10; // d1
  double v11; // d2
  double v12; // d3
  double v13; // d4
  double v14; // d5
  double v15; // d6
  double v16; // d7

  sprd_kbc_init(a1, a2, a3, a4, a5, a6, a7, a8);
  result = trusty_install_handler(5u, (__int64)qword_9405C8F0);
  if ( (_DWORD)result != 0 )
    return sprd_log(
             2u,
             "failed to install kbc_verify_ops handler: %d\n",
             v9,
             v10,
             v11,
             v12,
             v13,
             v14,
             v15,
             v16,
             (unsigned int)result);
  return result;
}

/* ===== dump_table @ 0x9404290C size 120 ===== */
__int64 __fastcall dump_table(
        __int64 *a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 *v9; // x19
  __int64 *v11; // x22
  __int64 v12; // x2
  __int64 v13; // x3
  __int64 v14; // t1
  double v15; // d0
  double v16; // d1
  double v17; // d2
  double v18; // d3
  double v19; // d4
  double v20; // d5
  double v21; // d6
  double v22; // d7

  v9 = a1;
  v11 = a1 + 56;
  do
  {
    v12 = *((unsigned int *)v9 + 2);
    v13 = *((unsigned int *)v9 + 3);
    v14 = *v9;
    v9 += 14;
    sprd_log(2u, "dump_table() len = %x maplen = %x addr = %llx \n", a2, a3, a4, a5, a6, a7, a8, a9, v12, v13, v14);
  }
  while ( v9 != v11 );
  sprd_log(2u, "dump_table() flag = %d \n", a2, a3, a4, a5, a6, a7, a8, a9, *((unsigned __int16 *)a1 + 224));
  return sprd_log(
           2u,
           "dump_table() is_packed = %d \n",
           v15,
           v16,
           v17,
           v18,
           v19,
           v20,
           v21,
           v22,
           *((unsigned __int16 *)a1 + 225));
}

/* ===== kbc_verify_ops @ 0x94042984 size 396 ===== */
__int64 __fastcall kbc_verify_ops(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        __int64 a9,
        int a10,
        unsigned int a11)
{
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  double v36; // d0
  double v37; // d1
  double v38; // d2
  double v39; // d3
  double v40; // d4
  double v41; // d5
  double v42; // d6
  double v43; // d7
  double v44; // d0
  double v45; // d1
  double v46; // d2
  double v47; // d3
  double v48; // d4
  double v49; // d5
  double v50; // d6
  double v51; // d7
  double v52; // d0
  double v53; // d1
  double v54; // d2
  double v55; // d3
  double v56; // d4
  double v57; // d5
  double v58; // d6
  double v59; // d7
  double v60; // d0
  double v61; // d1
  double v62; // d2
  double v63; // d3
  double v64; // d4
  double v65; // d5
  double v66; // d6
  double v67; // d7
  __int64 result; // x0
  __int64 v69[57]; // [xsp+28h] [xbp+28h] BYREF

  switch ( a10 )
  {
    case 0:
      sprd_log(2u, "enter SEC_KBC_STOP_CP\n", a1, a2, a3, a4, a5, a6, a7, a8);
      kbc_stop_cp(v52, v53, v54, v55, v56, v57, v58, v59);
      result = 0;
      break;
    case 1:
      sprd_log(2u, "enter SEC_KBC_VERIFY_ALL\n", a1, a2, a3, a4, a5, a6, a7, a8);
      if ( (unsigned int)copy_from_user(v69, a11, 456) != 0 )
        goto LABEL_11;
      dump_table(v69, v12, v13, v14, v15, v16, v17, v18, v19);
      sprd_log(2u, (const char *)&loc_94055668, v20, v21, v22, v23, v24, v25, v26, v27);
      kbc_image_verify((__int64)v69, v28, v29, v30, v31, v32, v33, v34, v35);
      sprd_log(2u, "verify succ,will update version\n", v36, v37, v38, v39, v40, v41, v42, v43);
      result = 0;
      break;
    case 2:
      sprd_log(2u, "enter SEC_KBC_START_CP\n", a1, a2, a3, a4, a5, a6, a7, a8);
      kbc_start_cp(v60, v61, v62, v63, v64, v65, v66, v67);
      result = 0;
      break;
    case 3:
      sprd_log(2u, "enter SEC_KBC_VERIFY_ALL_V2\n", a1, a2, a3, a4, a5, a6, a7, a8);
      if ( (unsigned int)copy_from_user(v69, a11, 456) != 0 )
      {
LABEL_11:
        sprd_log(2u, "copy_from_user failed!! \n", v12, v13, v14, v15, v16, v17, v18, v19);
        result = 4294967288LL;
      }
      else
      {
        dump_table(v69, v12, v13, v14, v15, v16, v17, v18, v19);
        result = kbc_image_verify_v2(v69);
      }
      break;
    case 4:
      sprd_log(2u, "enter SEC_KBC_GET_VERSION\n", a1, a2, a3, a4, a5, a6, a7, a8);
      copy_to_user(a11, -536460624, 56);
      sprd_log(2u, (const char *)&loc_94055710, v44, v45, v46, v47, v48, v49, v50, v51);
      MEMORY[0xFFFFFFFFE00642E4] = 0;
      result = 0;
      break;
    default:
      result = 4294967272LL;
      break;
  }
  return result;
}

/* ===== avb_chain_partition_validate @ 0x94042B10 size 276 ===== */
__int64 __fastcall avb_chain_partition_validate(__int64 a1, __int64 a2)
{
  __int64 result; // x0
  double v5; // d0
  double v6; // d1
  double v7; // d2
  double v8; // d3
  double v9; // d4
  double v10; // d5
  double v11; // d6
  double v12; // d7
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x1
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  unsigned __int64 v30; // [xsp+28h] [xbp+28h] BYREF

  memcpy(a2, a1, 92);
  result = avb_desc_header_validate(a1, a2);
  if ( (_DWORD)result != 0 )
  {
    if ( *(_QWORD *)a2 == 4 )
    {
      *(_DWORD *)(a2 + 16) = be32_to_cpu(*(unsigned int *)(a2 + 16));
      *(_DWORD *)(a2 + 20) = be32_to_cpu(*(unsigned int *)(a2 + 20));
      *(_DWORD *)(a2 + 24) = be32_to_cpu(*(unsigned int *)(a2 + 24));
      if ( *(_DWORD *)(a2 + 16) != 0 )
      {
        v21 = *(unsigned int *)(a2 + 20);
        v30 = 76;
        if ( (unsigned int)add_overflow(&v30, v21) != 0
          && (unsigned int)add_overflow(&v30, *(unsigned int *)(a2 + 24)) != 0 )
        {
          result = 1;
          if ( *(_QWORD *)(a2 + 8) < v30 )
          {
            sprd_log(0, "Descriptor payload size overflow.\n", v22, v23, v24, v25, v26, v27, v28, v29);
            return 0;
          }
        }
        else
        {
          sprd_log(0, "Overflow while adding up sizes.\n", v22, v23, v24, v25, v26, v27, v28, v29);
          return 0;
        }
      }
      else
      {
        sprd_log(0, "Invalid rollback index location value.\n", v13, v14, v15, v16, v17, v18, v19, v20);
        return 0;
      }
    }
    else
    {
      sprd_log(0, "Invalid tag for chain partition descriptor.\n", v5, v6, v7, v8, v9, v10, v11, v12);
      return 0;
    }
  }
  return result;
}

/* ===== avb_get_algorithm @ 0x94042C24 size 44 ===== */
__int64 *__fastcall avb_get_algorithm(unsigned int a1)
{
  if ( a1 > 6 )
    return nullptr;
  else
    return &qword_9405C908[3 * a1];
}

/* ===== avb_hash_desc_validate @ 0x94042C50 size 72 ===== */
__int64 __fastcall avb_hash_desc_validate(__int64 a1, unsigned int *a2)
{
  memcpy(a2, a1, 8);
  *a2 = be32_to_cpu(*a2);
  a2[1] = be32_to_cpu(a2[1]);
  return 1;
}

/* ===== avb_count_descriptor @ 0x94042C98 size 20 ===== */
__int64 __fastcall avb_count_descriptor(__int64 a1, _QWORD *a2)
{
  ++*a2;
  return 1;
}

/* ===== avb_store_descriptor @ 0x94042CAC size 28 ===== */
__int64 __fastcall avb_store_descriptor(__int64 a1, __int64 *a2)
{
  __int64 v2; // x2
  __int64 v3; // x3

  v2 = *a2;
  v3 = a2[1];
  ++*a2;
  *(_QWORD *)(v3 + 8 * v2) = a1;
  return 1;
}

/* ===== avb_desc_header_validate @ 0x94042CC8 size 88 ===== */
__int64 __fastcall avb_desc_header_validate(_QWORD *a1, _QWORD *a2)
{
  __int64 v4; // x0
  double v5; // d0
  double v6; // d1
  double v7; // d2
  double v8; // d3
  double v9; // d4
  double v10; // d5
  double v11; // d6
  double v12; // d7
  __int64 v13; // x1
  __int64 result; // x0

  *a2 = be64_to_cpu(*a1);
  v4 = be64_to_cpu(a1[1]);
  v13 = v4 & 7;
  a2[1] = v4;
  result = 1;
  if ( v13 != 0 )
  {
    sprd_log(0, "Descriptor size is not divisible by 8.\n", v5, v6, v7, v8, v9, v10, v11, v12);
    return 0;
  }
  return result;
}

/* ===== avb_foreach_descriptor @ 0x94042D20 size 552 ===== */
__int64 __fastcall avb_foreach_descriptor(
        unsigned __int64 a1,
        unsigned __int64 a2,
        unsigned int (__fastcall *a3)(unsigned __int64, __int64),
        __int64 a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12)
{
  double v16; // d0
  double v17; // d1
  double v18; // d2
  double v19; // d3
  double v20; // d4
  double v21; // d5
  double v22; // d6
  double v23; // d7
  unsigned __int64 v24; // x20
  __int64 v25; // x21
  unsigned __int64 v26; // x21
  unsigned __int64 v27; // x22
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  unsigned __int64 v36; // x19
  __int64 v38; // x0
  double v39; // d0
  double v40; // d1
  double v41; // d2
  double v42; // d3
  double v43; // d4
  double v44; // d5
  double v45; // d6
  double v46; // d7
  __int64 v47; // x2
  unsigned __int64 v48; // x20
  bool v49; // cc
  unsigned __int64 v50; // x0

  if ( a1 != 0 )
  {
    if ( a3 != nullptr )
    {
      if ( a2 <= 0xFF )
      {
        sprd_log(0, "Length is smaller than header.\n", a5, a6, a7, a8, a9, a10, a11, a12);
        return 0;
      }
      else if ( (unsigned int)memcmp(a1, (__int64)"AVB0", 4u) != 0 )
      {
        sprd_log(0, "Magic is incorrect.\n", v16, v17, v18, v19, v20, v21, v22, v23);
        return 0;
      }
      else
      {
        if ( (a1 & 7) != 0 )
          sprd_log(
            0,
            "assert fail: (((uintptr_t)image_data) & (AVB_ALIGNMENT_SIZE - 1)) == 0\n",
            v16,
            v17,
            v18,
            v19,
            v20,
            v21,
            v22,
            v23);
        v24 = a1 + a2;
        v25 = be64_to_cpu(*(_QWORD *)(a1 + 12));
        v26 = a1 + v25 + be64_to_cpu(*(_QWORD *)(a1 + 96)) + 256;
        v27 = v26 + be64_to_cpu(*(_QWORD *)(a1 + 104));
        if ( a1 > v26 || v24 < v26 || a1 > v27 || v24 < v27 || v26 > v27 )
        {
          sprd_log(0, "Descriptors not inside passed-in data.\n", v28, v29, v30, v31, v32, v33, v34, v35);
          return 0;
        }
        else
        {
          v36 = v26;
          if ( v26 < v27 )
          {
            while ( 1 )
            {
              if ( (v36 & 7) != 0 )
                sprd_log(
                  0,
                  "assert fail: (((uintptr_t)dh) & (AVB_ALIGNMENT_SIZE - 1)) == 0\n",
                  v28,
                  v29,
                  v30,
                  v31,
                  v32,
                  v33,
                  v34,
                  v35);
              v38 = be64_to_cpu(*(_QWORD *)(v36 + 8)) + 16;
              v47 = v38 & 7;
              v48 = v36 + v38;
              v49 = v26 > v36 + v38;
              v50 = v36;
              v36 = v48;
              if ( v47 != 0 )
              {
                sprd_log(0, "Invalid descriptor length.\n", v39, v40, v41, v42, v43, v44, v45, v46);
                return 0;
              }
              if ( v49 || v27 < v48 )
              {
                sprd_log(0, "Invalid data in descriptors array.\n", v39, v40, v41, v42, v43, v44, v45, v46);
                return 0;
              }
              if ( a3(v50, a4) == 0 )
                break;
              if ( v27 <= v48 )
                return 1;
            }
            return 0;
          }
          else
          {
            return 1;
          }
        }
      }
    }
    else
    {
      sprd_log(0, "foreach_func is NULL\n.", a5, a6, a7, a8, a9, a10, a11, a12);
      return 0;
    }
  }
  else
  {
    sprd_log(0, "image_data is NULL\n.", a5, a6, a7, a8, a9, a10, a11, a12);
    return 0;
  }
}

/* ===== avb_get_all_descriptors @ 0x94042F48 size 172 ===== */
__int64 __fastcall avb_get_all_descriptors(
        unsigned __int64 a1,
        unsigned __int64 a2,
        _QWORD *a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v14; // d0
  double v15; // d1
  double v16; // d2
  double v17; // d3
  double v18; // d4
  double v19; // d5
  double v20; // d6
  double v21; // d7
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  __int64 v31; // [xsp+38h] [xbp+38h] BYREF
  __int64 v32; // [xsp+40h] [xbp+40h] BYREF
  __int64 v33; // [xsp+48h] [xbp+48h]

  v31 = 0;
  avb_foreach_descriptor(
    a1,
    a2,
    (unsigned int (__fastcall *)(unsigned __int64, __int64))avb_count_descriptor,
    (__int64)&v31,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11);
  v32 = 0;
  v33 = avb_calloc(8 * (v31 + 1));
  if ( v33 == 0 )
    return 0;
  avb_foreach_descriptor(
    a1,
    a2,
    (unsigned int (__fastcall *)(unsigned __int64, __int64))avb_store_descriptor,
    (__int64)&v32,
    v14,
    v15,
    v16,
    v17,
    v18,
    v19,
    v20,
    v21);
  if ( v32 != v31 )
    sprd_log(0, "assert fail: data.descriptor_number == num_descriptors\n", v22, v23, v24, v25, v26, v27, v28, v29);
  if ( a3 != nullptr )
    *a3 = v31;
  return v33;
}

/* ===== avb_footer_validate @ 0x94042FF4 size 216 ===== */
__int64 __fastcall avb_footer_validate(__int64 a1, __int64 a2)
{
  double v3; // d0
  double v4; // d1
  double v5; // d2
  double v6; // d3
  double v7; // d4
  double v8; // d5
  double v9; // d6
  double v10; // d7

  memcpy(a2, a1, 64);
  *(_DWORD *)(a2 + 4) = be32_to_cpu(*(unsigned int *)(a2 + 4));
  *(_DWORD *)(a2 + 8) = be32_to_cpu(*(unsigned int *)(a2 + 8));
  *(_QWORD *)(a2 + 12) = be64_to_cpu(*(_QWORD *)(a2 + 12));
  *(_QWORD *)(a2 + 20) = be64_to_cpu(*(_QWORD *)(a2 + 20));
  *(_QWORD *)(a2 + 28) = be64_to_cpu(*(_QWORD *)(a2 + 28));
  if ( (unsigned int)memcmp_neq(a2, "AVBf", 4) != 0 )
  {
    sprd_log(0, "Footer magic is incorrect.\n", v3, v4, v5, v6, v7, v8, v9, v10);
    return 0;
  }
  else if ( *(_DWORD *)(a2 + 4) <= 1u )
  {
    return 1;
  }
  else
  {
    sprd_log(0, "No support for footer version.\n", v3, v4, v5, v6, v7, v8, v9, v10);
    return 0;
  }
}

/* ===== avb_hash_desc_parse @ 0x940430CC size 280 ===== */
__int64 __fastcall avb_hash_desc_parse(_QWORD *a1, __int64 a2)
{
  __int64 result; // x0
  double v5; // d0
  double v6; // d1
  double v7; // d2
  double v8; // d3
  double v9; // d4
  double v10; // d5
  double v11; // d6
  double v12; // d7
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  unsigned __int64 v21; // [xsp+28h] [xbp+28h] BYREF

  memcpy(a2, a1, 132);
  result = avb_desc_header_validate(a1, (_QWORD *)a2);
  if ( (_DWORD)result != 0 )
  {
    if ( *(_QWORD *)a2 == 2 )
    {
      *(_QWORD *)(a2 + 16) = be64_to_cpu(*(_QWORD *)(a2 + 16));
      *(_DWORD *)(a2 + 56) = be32_to_cpu(*(unsigned int *)(a2 + 56));
      *(_DWORD *)(a2 + 60) = be32_to_cpu(*(unsigned int *)(a2 + 60));
      *(_DWORD *)(a2 + 64) = be32_to_cpu(*(unsigned int *)(a2 + 64));
      v21 = 116;
      if ( (unsigned int)add_overflow(&v21, *(unsigned int *)(a2 + 56)) != 0
        && (unsigned int)add_overflow(&v21, *(unsigned int *)(a2 + 60)) != 0
        && (unsigned int)add_overflow(&v21, *(unsigned int *)(a2 + 64)) != 0 )
      {
        result = 1;
        if ( *(_QWORD *)(a2 + 8) < v21 )
        {
          sprd_log(0, "Descriptor payload size overflow.\n", v13, v14, v15, v16, v17, v18, v19, v20);
          return 0;
        }
      }
      else
      {
        sprd_log(0, "Overflow while adding up sizes.\n", v13, v14, v15, v16, v17, v18, v19, v20);
        return 0;
      }
    }
    else
    {
      sprd_log(0, "Invalid tag for hash descriptor.\n", v5, v6, v7, v8, v9, v10, v11, v12);
      return 0;
    }
  }
  return result;
}

/* ===== avb_cmdline_desc_parse @ 0x940431E4 size 216 ===== */
__int64 __fastcall avb_cmdline_desc_parse(_QWORD *a1, __int64 a2)
{
  unsigned int v4; // w20
  double v5; // d0
  double v6; // d1
  double v7; // d2
  double v8; // d3
  double v9; // d4
  double v10; // d5
  double v11; // d6
  double v12; // d7
  unsigned int v14; // w0
  double v15; // d0
  double v16; // d1
  double v17; // d2
  double v18; // d3
  double v19; // d4
  double v20; // d5
  double v21; // d6
  double v22; // d7
  unsigned __int64 v23; // [xsp+28h] [xbp+28h] BYREF

  memcpy(a2, a1, 24);
  v4 = avb_desc_header_validate(a1, (_QWORD *)a2);
  if ( v4 != 0 )
  {
    if ( *(_QWORD *)a2 == 3 )
    {
      *(_DWORD *)(a2 + 16) = be32_to_cpu(*(unsigned int *)(a2 + 16));
      v14 = be32_to_cpu(*(unsigned int *)(a2 + 20));
      *(_DWORD *)(a2 + 20) = v14;
      v23 = 8;
      v4 = add_overflow(&v23, v14);
      if ( v4 != 0 )
      {
        v4 = 1;
        if ( *(_QWORD *)(a2 + 8) < v23 )
        {
          v4 = 0;
          sprd_log(0, "Descriptor payload size overflow.\n", v15, v16, v17, v18, v19, v20, v21, v22);
        }
      }
      else
      {
        sprd_log(0, "Overflow while adding up sizes.\n", v15, v16, v17, v18, v19, v20, v21, v22);
      }
    }
    else
    {
      v4 = 0;
      sprd_log(0, "Invalid tag for kernel cmdline descriptor.\n", v5, v6, v7, v8, v9, v10, v11, v12);
    }
  }
  return v4;
}

/* ===== avb_rsa_modmult @ 0x940432BC size 280 ===== */
__int64 __fastcall avb_rsa_modmult(__int64 result, _DWORD *a2, __int64 a3, _DWORD *a4)
{
  unsigned int v4; // w4
  unsigned int v5; // w6
  unsigned int *v6; // x11
  unsigned int i; // w12
  unsigned int v8; // w14
  bool v9; // cc
  unsigned __int64 v10; // x5
  unsigned int v11; // w13
  unsigned __int64 v12; // x6
  unsigned int v13; // w4
  __int64 v14; // x10
  unsigned int v15; // w8
  unsigned int v16; // w7
  unsigned int v17; // w9
  unsigned __int64 v18; // x5
  __int64 v19; // x4
  unsigned int v20; // w5
  __int64 v21; // x4
  __int64 v22; // x4

  v4 = 0;
  if ( *(_DWORD *)result != 0 )
  {
    do
    {
      a2[v4++] = 0;
      v5 = *(_DWORD *)result;
    }
    while ( *(_DWORD *)result > v4 );
    if ( v5 != 0 )
    {
      v6 = *(unsigned int **)(result + 8);
      for ( i = 0; i < v5; ++i )
      {
        while ( 1 )
        {
          v8 = *(_DWORD *)(a3 + 4LL * i);
          v9 = v5 > 1;
          v10 = (unsigned int)*a2 + v8 * (unsigned __int64)(unsigned int)*a4;
          v11 = *(_DWORD *)(result + 4) * v10;
          v12 = *a2 + v8 * *a4 + v11 * (unsigned __int64)*v6;
          if ( v9 )
          {
            v13 = 1;
            do
            {
              v14 = (unsigned int)a2[v13];
              v15 = v13 - 1;
              v16 = v6[v13];
              v17 = a4[v13++];
              v10 = v14 + HIDWORD(v10) + v17 * (unsigned __int64)v8;
              v12 = HIDWORD(v12) + v16 * (unsigned __int64)v11 + (unsigned int)v10;
              a2[v15] = v12;
            }
            while ( v13 < *(_DWORD *)result );
            v22 = v13 - 1;
          }
          else
          {
            v22 = 0;
          }
          v18 = HIDWORD(v12) + HIDWORD(v10);
          a2[v22] = v18;
          if ( HIDWORD(v18) != 0 )
            break;
          v5 = *(_DWORD *)result;
          if ( ++i >= *(_DWORD *)result )
            return result;
        }
        if ( *(_DWORD *)result == 0 )
          break;
        v19 = 0;
        v20 = 0;
        do
        {
          v21 = (unsigned int)a2[v20] + v19 - v6[v20];
          a2[v20++] = v21;
          v19 = v21 >> 32;
          v5 = *(_DWORD *)result;
        }
        while ( v20 < *(_DWORD *)result );
      }
    }
  }
  return result;
}

/* ===== avb_parse_rsa_key @ 0x940433D4 size 384 ===== */
__int64 __fastcall avb_parse_rsa_key(__int64 a1, __int64 a2)
{
  double v4; // d0
  double v5; // d1
  double v6; // d2
  double v7; // d3
  double v8; // d4
  double v9; // d5
  double v10; // d6
  double v11; // d7
  unsigned __int64 v13; // x0
  __int64 v14; // x21
  __int64 v15; // x0
  __int64 v16; // x20
  __int64 v17; // x24
  __int64 v18; // x1
  unsigned int v19; // w19
  __int64 v20; // x24
  unsigned int v21[2]; // [xsp+48h] [xbp+48h] BYREF

  if ( (unsigned int)avb_hash_desc_validate(a1, v21) != 0 )
  {
    if ( ((v21[0] - 2048) & 0xFFFFF7FF) == 0 || v21[0] == 0x2000 )
    {
      v13 = ((unsigned __int64)v21[0] >> 2) & 0x1FFFFFFF;
      if ( a2 == v13 + 8 )
      {
        v14 = (v21[0] >> 3) + 8LL;
        v15 = avb_malloc(v13 + 24);
        v16 = v15;
        if ( v15 != 0 )
        {
          v17 = v15 + 24;
          v18 = v21[0] >> 5;
          *(_DWORD *)(v15 + 4) = v21[1];
          *(_DWORD *)v15 = v18;
          *(_QWORD *)(v15 + 8) = v15 + 24;
          *(_QWORD *)(v15 + 16) = v15 + 24 + 4 * v18;
          if ( (_DWORD)v18 != 0 )
          {
            v19 = 0;
            while ( 1 )
            {
              *(_DWORD *)(v17 + 4LL * v19) = be32_to_cpu(*(unsigned int *)(a1 + 4LL * ((unsigned int)v18 + ~v19) + 8));
              v20 = *(_QWORD *)(v16 + 16);
              *(_DWORD *)(v20 + 4LL * v19) = be32_to_cpu(*(unsigned int *)(a1 + v14 + 4LL * (*(_DWORD *)v16 - 1 - v19)));
              ++v19;
              LODWORD(v18) = *(_DWORD *)v16;
              if ( *(_DWORD *)v16 <= v19 )
                break;
              v17 = *(_QWORD *)(v16 + 8);
            }
          }
          return v16;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        sprd_log(0, "Key does not match expected length.\n", v4, v5, v6, v7, v8, v9, v10, v11);
        return 0;
      }
    }
    else
    {
      sprd_log(0, "Unexpected key length.\n", v4, v5, v6, v7, v8, v9, v10, v11);
      return 0;
    }
  }
  else
  {
    sprd_log(0, "Invalid key.\n", v4, v5, v6, v7, v8, v9, v10, v11);
    return 0;
  }
}

/* ===== avb_free_key @ 0x94043554 size 4 ===== */
// attributes: thunk
__int64 __fastcall avb_free_key(__int64 a1)
{
  return free(a1);
}

/* ===== avb_rsa_verify_sw @ 0x94043558 size 1120 ===== */
__int64 __fastcall avb_rsa_verify_sw(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13,
        double a14,
        double a15,
        double a16)
{
  unsigned int *v16; // x0
  double v17; // d0
  double v18; // d1
  double v19; // d2
  double v20; // d3
  double v21; // d4
  double v22; // d5
  double v23; // d6
  double v24; // d7
  signed int *v25; // x20
  __int64 v26; // x22
  __int64 v28; // x19
  __int64 v29; // x0
  __int64 v30; // x3
  double v31; // d0
  double v32; // d1
  double v33; // d2
  double v34; // d3
  double v35; // d4
  double v36; // d5
  double v37; // d6
  double v38; // d7
  __int64 v39; // x21
  int *v40; // x23
  _DWORD *v41; // x22
  __int64 v42; // x0
  _DWORD *v43; // x24
  __int64 v44; // x4
  __int64 v45; // x5
  __int64 v46; // x6
  signed int v47; // w2
  int *v48; // x7
  signed int i; // w1
  int v50; // w0
  __int64 v51; // x3
  int v52; // w25
  __int64 v53; // x4
  __int64 v54; // x5
  __int64 v55; // x6
  signed int v56; // w1
  unsigned int v57; // w0
  __int64 v58; // x7
  unsigned int v59; // w2
  unsigned int v60; // w3
  unsigned int v61; // w3
  unsigned int v62; // w2
  __int64 v63; // x0
  unsigned int v64; // w2
  __int64 v65; // x0
  int v66; // w1
  __int64 v67; // x0
  int *v68; // x3
  int v69; // t1
  double v70; // d0
  double v71; // d1
  double v72; // d2
  double v73; // d3
  double v74; // d4
  double v75; // d5
  double v76; // d6
  double v77; // d7
  unsigned int v78; // w19
  __int64 v79; // x0
  double v80; // d0
  double v81; // d1
  double v82; // d2
  double v83; // d3
  double v84; // d4
  double v85; // d5
  double v86; // d6
  double v87; // d7
  __int64 v92; // [xsp+68h] [xbp+68h]
  __int64 v93; // [xsp+68h] [xbp+68h]
  __int64 v94; // [xsp+68h] [xbp+68h]
  __int64 v95; // [xsp+68h] [xbp+68h]
  __int64 v97; // [xsp+70h] [xbp+70h]
  __int64 v98; // [xsp+70h] [xbp+70h]
  __int64 v99; // [xsp+70h] [xbp+70h]
  __int64 v100; // [xsp+70h] [xbp+70h]
  __int64 v101; // [xsp+70h] [xbp+70h]
  __int64 v103; // [xsp+78h] [xbp+78h]
  __int64 v104; // [xsp+78h] [xbp+78h]
  __int64 v105; // [xsp+78h] [xbp+78h]
  __int64 v106; // [xsp+78h] [xbp+78h]
  __int64 v107; // [xsp+78h] [xbp+78h]

  if ( a1 == 0 || a3 == 0 || a5 == 0 || a7 == 0 )
  {
    sprd_log(0, "Invalid input.\n", a9, a10, a11, a12, a13, a14, a15, a16);
    return 0;
  }
  v16 = (unsigned int *)avb_parse_rsa_key(a1, a2);
  v25 = (signed int *)v16;
  if ( v16 == nullptr )
  {
    sprd_log(0, "Error parsing key.\n", v17, v18, v19, v20, v21, v22, v23, v24, a3, a4, a5, a6, a7, a8);
    return 0;
  }
  v26 = 4LL * *v16;
  if ( v26 != a4 )
  {
    sprd_log(
      0,
      "Signature length does not match key length.\n",
      v17,
      v18,
      v19,
      v20,
      v21,
      v22,
      v23,
      v24,
      a3,
      a4,
      a5,
      a6,
      a7,
      a8);
LABEL_8:
    avb_free_key((__int64)v25);
    return 0;
  }
  v28 = v26 - a6;
  if ( v26 - a6 != a8 )
  {
    sprd_log(
      0,
      "Padding length does not match hash and signature lengths.\n",
      v17,
      v18,
      v19,
      v20,
      v21,
      v22,
      v23,
      v24,
      a3);
    goto LABEL_8;
  }
  v29 = avb_malloc(4LL * *v16);
  v39 = v29;
  if ( v29 == 0 )
  {
    sprd_log(0, "Error allocating memory.\n", v31, v32, v33, v34, v35, v36, v37, v38, a3, v30, a5, a6, a7);
    goto LABEL_8;
  }
  memcpy(v29, a3, v26);
  v40 = (int *)avb_malloc(4LL * (unsigned int)*v25);
  v41 = (_DWORD *)avb_malloc(4LL * (unsigned int)*v25);
  v42 = avb_malloc(4LL * (unsigned int)*v25);
  v43 = (_DWORD *)v42;
  v44 = a5;
  v45 = a6;
  v46 = a7;
  if ( v41 != nullptr && v40 != nullptr )
  {
    if ( v42 != 0 )
    {
      v47 = *v25;
      v48 = v40;
      for ( i = 0; i < *v25; v47 = *v25 )
      {
        v50 = 0x3FFFFFFF - i++;
        v51 = (unsigned int)(4 * (v47 + v50));
        *v48++ = *(unsigned __int8 *)(v39 + (unsigned int)(v51 + 3))
               | (*(unsigned __int8 *)(v39 + v51) << 24)
               | (*(unsigned __int8 *)(v39 + (unsigned int)(v51 + 1)) << 16)
               | (*(unsigned __int8 *)(v39 + (unsigned int)(v51 + 2)) << 8);
      }
      v52 = 8;
      avb_rsa_modmult((__int64)v25, v41, (__int64)v40, *((_DWORD **)v25 + 2));
      v53 = a5;
      v54 = a6;
      v55 = a7;
      do
      {
        v92 = v55;
        v97 = v54;
        v103 = v53;
        avb_rsa_modmult((__int64)v25, v43, (__int64)v41, v41);
        avb_rsa_modmult((__int64)v25, v41, (__int64)v43, v43);
        --v52;
        v53 = v103;
        v54 = v97;
        v55 = v92;
      }
      while ( v52 != 0 );
      avb_rsa_modmult((__int64)v25, v43, (__int64)v41, v40);
      v56 = *v25;
      v44 = v103;
      v45 = v97;
      v46 = v92;
      if ( *v25 != 0 )
      {
        v57 = v56 - 1;
        v58 = *((_QWORD *)v25 + 1);
        v59 = v43[v56 - 1];
        v60 = *(_DWORD *)(v58 + 4LL * (unsigned int)(v56 - 1));
        if ( v60 <= v59 )
        {
          if ( v60 >= v59 )
          {
            do
            {
              if ( v57 == 0 )
                break;
              v61 = v43[--v57];
              v62 = *(_DWORD *)(v58 + 4LL * v57);
              if ( v61 < v62 )
                goto LABEL_30;
            }
            while ( v61 <= v62 );
          }
          v63 = 0;
          v64 = 0;
          do
          {
            v65 = (unsigned int)v43[v64] + v63 - *(unsigned int *)(v58 + 4LL * v64);
            v43[v64++] = v65;
            v63 = v65 >> 32;
            v56 = *v25;
          }
          while ( v64 < *v25 );
        }
LABEL_30:
        v66 = v56 - 1;
        if ( v66 >= 0 )
        {
          v67 = v39;
          v68 = &v43[v66];
          do
          {
            v69 = *v68--;
            v67 += 4;
            --v66;
            *(_BYTE *)(v67 - 1) = v69;
            *(_BYTE *)(v67 - 4) = HIBYTE(v69);
            *(_BYTE *)(v67 - 3) = BYTE2(v69);
            *(_BYTE *)(v67 - 2) = BYTE1(v69);
          }
          while ( v66 != -1 );
        }
      }
    }
  }
  else if ( v40 == nullptr )
  {
    goto LABEL_34;
  }
  v93 = v46;
  v98 = v45;
  v104 = v44;
  free((__int64)v40);
  v44 = v104;
  v45 = v98;
  v46 = v93;
LABEL_34:
  if ( v41 != nullptr )
  {
    v94 = v46;
    v99 = v45;
    v105 = v44;
    free((__int64)v41);
    v46 = v94;
    v45 = v99;
    v44 = v105;
  }
  if ( v43 != nullptr )
  {
    v95 = v46;
    v100 = v45;
    v106 = v44;
    free((__int64)v43);
    v46 = v95;
    v45 = v100;
    v44 = v106;
  }
  v101 = v45;
  v107 = v44;
  if ( (unsigned int)memcmp_neq(v39, v46, v28) != 0 )
  {
    v78 = 0;
    sprd_log(0, "Padding check failed.\n", v70, v71, v72, v73, v74, v75, v76, v77);
  }
  else
  {
    v79 = v39 + v28;
    v78 = 1;
    if ( (unsigned int)memcmp_neq(v79, v107, v101) != 0 )
    {
      v78 = 0;
      sprd_log(0, "Hash check failed.\n", v80, v81, v82, v83, v84, v85, v86, v87);
    }
  }
  avb_free_key((__int64)v25);
  free(v39);
  return v78;
}

/* ===== sha256_transform @ 0x940439B8 size 548 ===== */
unsigned int *__fastcall sha256_transform(unsigned int *result, __int64 a2, int a3)
{
  unsigned int v3; // w28
  int v4; // w26
  unsigned int v5; // w27
  unsigned int v6; // w25
  unsigned int v7; // w24
  unsigned int v8; // w23
  unsigned int v9; // w22
  unsigned int v10; // w21
  __int64 i; // x5
  __int64 *v12; // x7
  unsigned int v13; // w2
  int v14; // w3
  unsigned __int64 v15; // t2
  int v16; // w5
  unsigned int v17; // w11
  unsigned int v18; // w14
  unsigned int v19; // w13
  unsigned int v20; // w17
  unsigned int v21; // w10
  unsigned int v22; // w16
  unsigned int v23; // w15
  unsigned int v24; // w1
  __int64 v25; // x12
  int v26; // w4
  unsigned __int64 v27; // t2
  int v28; // w3
  unsigned __int64 v29; // t2
  int v30; // w2
  int v31; // w5
  int v32; // w9
  int v33; // w5
  unsigned __int64 v34; // t2
  unsigned int v35; // w2
  unsigned int v36; // w4
  unsigned int v37; // w2
  unsigned int v38; // [xsp+50h] [xbp-110h]
  _DWORD v41[48]; // [xsp+60h] [xbp-100h] BYREF
  __int64 v42; // [xsp+120h] [xbp-40h] BYREF

  if ( a3 > 0 )
  {
    v3 = *result;
    v4 = 0;
    v5 = result[1];
    v6 = result[2];
    v7 = result[3];
    v8 = result[4];
    v9 = result[5];
    v10 = result[6];
    v38 = result[7];
    do
    {
      for ( i = 0; i != 16; ++i )
        v41[i] = _byteswap_ulong(*(_DWORD *)(a2 + (v4 << 6) + 4 * (int)i));
      v12 = (__int64 *)v41;
      do
      {
        v13 = *((_DWORD *)v12 + 14);
        v12 = (__int64 *)((char *)v12 + 4);
        HIDWORD(v15) = v13;
        LODWORD(v15) = v13;
        v14 = v15 >> 17;
        HIDWORD(v15) = v13;
        LODWORD(v15) = v13;
        v16 = (v15 >> 19) ^ v14;
        HIDWORD(v15) = *(_DWORD *)v12;
        LODWORD(v15) = *(_DWORD *)v12;
        *((_DWORD *)v12 + 15) = *((_DWORD *)v12 - 1)
                              + *((_DWORD *)v12 + 8)
                              + (v16 ^ (v13 >> 10))
                              + ((v15 >> 18) ^ __ROR4__(*(_DWORD *)v12, 7) ^ (*(_DWORD *)v12 >> 3));
      }
      while ( v12 != &v42 );
      v17 = v3;
      v18 = v5;
      v19 = v6;
      v20 = v7;
      v21 = v8;
      v22 = v9;
      v23 = v10;
      v24 = v38;
      v25 = 0;
      while ( 1 )
      {
        HIDWORD(v27) = v21;
        LODWORD(v27) = v21;
        v26 = v27 >> 6;
        v29 = __PAIR64__(v21, __ROR4__(v21, 11));
        v28 = v26 ^ v29;
        LODWORD(v29) = v21;
        v30 = v28 ^ (v29 >> 25);
        HIDWORD(v29) = v17;
        LODWORD(v29) = v17;
        v31 = v29 >> 2;
        v32 = v41[v25] + *(_DWORD *)((char *)qword_94058968 + v25 * 4);
        v34 = __PAIR64__(v17, __ROR4__(v17, 13));
        v33 = v31 ^ v34;
        LODWORD(v34) = v17;
        ++v25;
        v35 = v32 + v30 + (v23 & ~v21 ^ v22 & v21) + v24;
        v24 = v23;
        v36 = v20 + v35;
        v37 = ((v19 ^ v18) & v17 ^ v19 & v18) + (v33 ^ (v34 >> 22)) + v35;
        v20 = v19;
        if ( v25 == 64 )
          break;
        v19 = v18;
        v23 = v22;
        v18 = v17;
        v22 = v21;
        v17 = v37;
        v21 = v36;
      }
      v3 += v37;
      v8 += v36;
      ++v4;
      v5 += v17;
      v6 += v18;
      v7 += v19;
      v9 += v21;
      v10 += v22;
      v38 += v23;
      *result = v3;
      result[1] = v5;
      result[2] = v6;
      result[3] = v7;
      result[4] = v8;
      result[5] = v9;
      result[6] = v10;
      result[7] = v38;
    }
    while ( v4 != a3 );
  }
  return result;
}

/* ===== sha256_init @ 0x94043BDC size 108 ===== */
_DWORD *__fastcall sha256_init(_DWORD *result)
{
  *result = 1779033703;
  result[1] = -1150833019;
  result[2] = 1013904242;
  result[3] = -1521486534;
  result[4] = 1359893119;
  result[5] = -1694144372;
  result[6] = 528734635;
  result[7] = 1541459225;
  result[9] = 0;
  result[8] = 0;
  return result;
}

/* ===== sha256_update @ 0x94043C48 size 224 ===== */
__int64 __fastcall sha256_update(unsigned int *a1, __int64 a2, unsigned int a3)
{
  unsigned int v3; // w3
  unsigned int v5; // w19
  __int64 v7; // x22
  __int64 result; // x0
  unsigned int v10; // w19
  __int64 v11; // x22
  unsigned int v12; // w21
  int v13; // w2
  int v14; // w19

  v3 = a1[9];
  if ( a3 > 64 - v3 )
    v5 = 64 - v3;
  else
    v5 = a3;
  v7 = v5;
  memcpy((char *)a1 + v3 + 40, a2, v5);
  result = a3 + a1[9];
  if ( (unsigned int)result > 0x3F )
  {
    v10 = a3 - v5;
    v11 = a2 + v7;
    sha256_transform(a1, (__int64)(a1 + 10), 1);
    v12 = v10 >> 6;
    v13 = v10 >> 6;
    v14 = v10 & 0x3F;
    sha256_transform(a1, v11, v13);
    memcpy(a1 + 10, v11 + ((unsigned __int64)v12 << 6), v14 & 0x3F);
    a1[9] = v14;
    result = a1[8];
    a1[8] = result + ((v12 + 1) << 6);
  }
  else
  {
    a1[9] = result;
  }
  return result;
}

/* ===== sha256_final @ 0x94043D28 size 520 ===== */
__int64 __fastcall sha256_final(__int64 a1)
{
  unsigned int v1; // w3
  unsigned int v3; // w0
  __int64 v4; // x21
  __int64 v5; // x22
  __int64 v6; // x23
  __int64 v7; // x24
  int v8; // w2
  __int64 v9; // x2
  int v10; // w25
  unsigned int v11; // w20
  int v13; // w3
  int v14; // w2
  int v15; // w9
  int v16; // w1
  int v17; // w8
  int v18; // w7
  int v19; // w13
  int v20; // w6
  int v21; // w5
  int v22; // w1

  v1 = *(_DWORD *)(a1 + 36);
  v3 = v1 & 0x3F;
  v4 = 60;
  if ( v3 >= 0x38 )
    v4 = 124;
  v5 = 125;
  if ( v3 < 0x38 )
    v5 = 61;
  v6 = 126;
  if ( v3 < 0x38 )
    v6 = 62;
  v7 = 127;
  if ( v3 >= 0x38 )
  {
    v8 = 128;
  }
  else
  {
    v7 = 63;
    v8 = 64;
  }
  v9 = v8 - v1;
  if ( v3 < 0x38 )
    v10 = 1;
  else
    v10 = 2;
  v11 = v1 + *(_DWORD *)(a1 + 32);
  memset(a1 + v1 + 40, 0, v9);
  v11 *= 8;
  *(_BYTE *)(a1 + *(unsigned int *)(a1 + 36) + 40) = 0x80;
  *(_BYTE *)(a1 + v7 + 40) = v11;
  *(_BYTE *)(a1 + v6 + 40) = BYTE1(v11);
  *(_BYTE *)(a1 + v5 + 40) = BYTE2(v11);
  *(_BYTE *)(a1 + v4 + 40) = HIBYTE(v11);
  sha256_transform((unsigned int *)a1, a1 + 40, v10);
  v13 = *(_DWORD *)(a1 + 4);
  v14 = *(_DWORD *)(a1 + 8);
  v15 = *(_DWORD *)a1 >> 8;
  v16 = *(_DWORD *)(a1 + 12);
  v17 = HIWORD(*(_DWORD *)a1);
  v18 = *(_DWORD *)(a1 + 16);
  v19 = HIBYTE(*(_DWORD *)a1);
  v20 = *(_DWORD *)(a1 + 20);
  v21 = *(_DWORD *)(a1 + 24);
  *(_BYTE *)(a1 + 171) = *(_DWORD *)a1;
  *(_BYTE *)(a1 + 170) = v15;
  *(_BYTE *)(a1 + 169) = v17;
  *(_BYTE *)(a1 + 175) = v13;
  *(_BYTE *)(a1 + 168) = v19;
  *(_BYTE *)(a1 + 174) = BYTE1(v13);
  *(_BYTE *)(a1 + 173) = BYTE2(v13);
  *(_BYTE *)(a1 + 172) = HIBYTE(v13);
  *(_BYTE *)(a1 + 179) = v14;
  *(_BYTE *)(a1 + 178) = BYTE1(v14);
  *(_BYTE *)(a1 + 177) = BYTE2(v14);
  *(_BYTE *)(a1 + 176) = HIBYTE(v14);
  *(_BYTE *)(a1 + 183) = v16;
  *(_BYTE *)(a1 + 182) = BYTE1(v16);
  *(_BYTE *)(a1 + 181) = BYTE2(v16);
  *(_BYTE *)(a1 + 180) = HIBYTE(v16);
  *(_BYTE *)(a1 + 187) = v18;
  *(_BYTE *)(a1 + 186) = BYTE1(v18);
  *(_BYTE *)(a1 + 185) = BYTE2(v18);
  *(_BYTE *)(a1 + 184) = HIBYTE(v18);
  *(_BYTE *)(a1 + 191) = v20;
  *(_BYTE *)(a1 + 190) = BYTE1(v20);
  *(_BYTE *)(a1 + 189) = BYTE2(v20);
  *(_BYTE *)(a1 + 188) = HIBYTE(v20);
  *(_BYTE *)(a1 + 195) = v21;
  *(_BYTE *)(a1 + 194) = BYTE1(v21);
  *(_BYTE *)(a1 + 193) = BYTE2(v21);
  v22 = *(_DWORD *)(a1 + 28);
  *(_BYTE *)(a1 + 192) = HIBYTE(v21);
  *(_BYTE *)(a1 + 199) = v22;
  *(_BYTE *)(a1 + 198) = BYTE1(v22);
  *(_BYTE *)(a1 + 197) = BYTE2(v22);
  *(_BYTE *)(a1 + 196) = HIBYTE(v22);
  return a1 + 168;
}

/* ===== sha512_transform @ 0x94043F30 size 584 ===== */
__int64 *__fastcall sha512_transform(__int64 *result, __int64 a2, int a3)
{
  __int64 v3; // x28
  int v4; // w26
  __int64 v5; // x27
  __int64 v6; // x25
  __int64 v7; // x24
  __int64 v8; // x23
  __int64 v9; // x22
  __int64 v10; // x21
  __int64 i; // x7
  __int64 *v12; // x7
  unsigned __int64 v13; // x2
  __int64 v14; // x11
  __int64 v15; // x14
  __int64 v16; // x13
  __int64 v17; // x17
  __int64 v18; // x10
  __int64 v19; // x16
  __int64 v20; // x15
  __int64 v21; // x1
  __int64 v22; // x12
  __int64 v23; // x9
  __int64 v24; // x2
  __int64 v25; // x4
  __int64 v26; // x2
  __int64 v27; // [xsp+58h] [xbp-298h]
  _QWORD v30[64]; // [xsp+70h] [xbp-280h] BYREF
  __int64 v31; // [xsp+270h] [xbp-80h] BYREF

  if ( a3 > 0 )
  {
    v3 = *result;
    v4 = 0;
    v5 = result[1];
    v6 = result[2];
    v7 = result[3];
    v8 = result[4];
    v9 = result[5];
    v10 = result[6];
    v27 = result[7];
    do
    {
      for ( i = 0; i != 16; ++i )
        v30[i] = _byteswap_uint64(*(_QWORD *)(a2 + (v4 << 7) + 8 * (int)i));
      v12 = v30;
      do
      {
        v13 = v12[14];
        ++v12;
        v12[15] = *(v12 - 1)
                + v12[8]
                + (__ROR8__(v13, 61) ^ __ROR8__(v13, 19) ^ (v13 >> 6))
                + (__ROR8__(*v12, 1) ^ __ROR8__(*v12, 8) ^ ((unsigned __int64)*v12 >> 7));
      }
      while ( v12 != &v31 );
      v14 = v3;
      v15 = v5;
      v16 = v6;
      v17 = v7;
      v18 = v8;
      v19 = v9;
      v20 = v10;
      v21 = v27;
      v22 = 0;
      while ( 1 )
      {
        v23 = v30[v22] + *(_QWORD *)((char *)&unk_94058A68 + v22 * 8);
        ++v22;
        v24 = v23 + (__ROR8__(v18, 14) ^ __ROR8__(v18, 18) ^ __ROR8__(v18, 41)) + (v20 & ~v18 ^ v19 & v18) + v21;
        v21 = v20;
        v25 = v17 + v24;
        v26 = ((v16 ^ v15) & v14 ^ v16 & v15) + (__ROR8__(v14, 34) ^ __ROR8__(v14, 28) ^ __ROR8__(v14, 39)) + v24;
        v17 = v16;
        if ( v22 == 80 )
          break;
        v16 = v15;
        v20 = v19;
        v15 = v14;
        v19 = v18;
        v14 = v26;
        v18 = v25;
      }
      v3 += v26;
      v8 += v25;
      ++v4;
      v5 += v14;
      v6 += v15;
      v7 += v16;
      v9 += v18;
      v10 += v19;
      v27 += v20;
      *result = v3;
      result[1] = v5;
      result[2] = v6;
      result[3] = v7;
      result[4] = v8;
      result[5] = v9;
      result[6] = v10;
      result[7] = v27;
    }
    while ( v4 != a3 );
  }
  return result;
}

/* ===== sha512_init @ 0x94044178 size 172 ===== */
__int64 __fastcall sha512_init(__int64 result)
{
  *(_QWORD *)result = 0x6A09E667F3BCC908LL;
  *(_QWORD *)(result + 8) = 0xBB67AE8584CAA73BLL;
  *(_QWORD *)(result + 16) = 0x3C6EF372FE94F82BLL;
  *(_QWORD *)(result + 24) = 0xA54FF53A5F1D36F1LL;
  *(_QWORD *)(result + 32) = 0x510E527FADE682D1LL;
  *(_QWORD *)(result + 40) = 0x9B05688C2B3E6C1FLL;
  *(_QWORD *)(result + 48) = 0x1F83D9ABFB41BD6BLL;
  *(_QWORD *)(result + 56) = 0x5BE0CD19137E2179LL;
  *(_DWORD *)(result + 68) = 0;
  *(_DWORD *)(result + 64) = 0;
  return result;
}

/* ===== sha512_update @ 0x94044224 size 224 ===== */
__int64 __fastcall sha512_update(__int64 a1, __int64 a2, unsigned int a3)
{
  unsigned int v3; // w3
  unsigned int v5; // w19
  __int64 v7; // x22
  __int64 result; // x0
  unsigned int v10; // w19
  __int64 v11; // x22
  unsigned int v12; // w21
  int v13; // w2
  int v14; // w19

  v3 = *(_DWORD *)(a1 + 68);
  if ( a3 > 128 - v3 )
    v5 = 128 - v3;
  else
    v5 = a3;
  v7 = v5;
  memcpy(a1 + v3 + 72, a2, v5);
  result = a3 + *(_DWORD *)(a1 + 68);
  if ( (unsigned int)result > 0x7F )
  {
    v10 = a3 - v5;
    v11 = a2 + v7;
    sha512_transform((__int64 *)a1, a1 + 72, 1);
    v12 = v10 >> 7;
    v13 = v10 >> 7;
    v14 = v10 & 0x7F;
    sha512_transform((__int64 *)a1, v11, v13);
    memcpy(a1 + 72, v11 + ((unsigned __int64)v12 << 7), v14 & 0x7F);
    *(_DWORD *)(a1 + 68) = v14;
    result = *(unsigned int *)(a1 + 64);
    *(_DWORD *)(a1 + 64) = result + ((v12 + 1) << 7);
  }
  else
  {
    *(_DWORD *)(a1 + 68) = result;
  }
  return result;
}

/* ===== sha512_final @ 0x94044304 size 352 ===== */
__int64 __fastcall sha512_final(__int64 a1)
{
  unsigned int v1; // w3
  unsigned int v3; // w0
  __int64 v4; // x21
  __int64 v5; // x22
  __int64 v6; // x23
  __int64 v7; // x24
  int v8; // w2
  __int64 v9; // x2
  unsigned int v10; // w20
  int v11; // w25
  int v12; // w20
  __int64 v13; // x2
  __int64 v14; // x1
  int v15; // w0
  _BYTE *v16; // x0

  v1 = *(_DWORD *)(a1 + 68);
  v3 = v1 & 0x7F;
  v4 = 124;
  if ( v3 >= 0x70 )
    v4 = 252;
  v5 = 253;
  if ( v3 < 0x70 )
    v5 = 125;
  v6 = 254;
  if ( v3 < 0x70 )
    v6 = 126;
  v7 = 255;
  if ( v3 >= 0x70 )
  {
    v8 = 256;
  }
  else
  {
    v7 = 127;
    v8 = 128;
  }
  v9 = v8 - v1;
  v10 = v1 + *(_DWORD *)(a1 + 64);
  if ( v3 < 0x70 )
    v11 = 1;
  else
    v11 = 2;
  memset(a1 + v1 + 72, 0, v9);
  v12 = 8 * v10;
  *(_BYTE *)(a1 + *(unsigned int *)(a1 + 68) + 72) = 0x80;
  *(_BYTE *)(a1 + v7 + 72) = v12;
  *(_BYTE *)(a1 + v6 + 72) = BYTE1(v12);
  *(_BYTE *)(a1 + v5 + 72) = BYTE2(v12);
  *(_BYTE *)(a1 + v4 + 72) = HIBYTE(v12);
  sha512_transform((__int64 *)a1, a1 + 72, v11);
  v13 = 0;
  do
  {
    v14 = *(_QWORD *)(a1 + 8 * v13);
    v15 = 8 * v13++;
    v16 = (_BYTE *)(a1 + v15);
    v16[335] = v14;
    v16[334] = BYTE1(v14);
    v16[333] = BYTE2(v14);
    v16[332] = BYTE3(v14);
    v16[331] = BYTE4(v14);
    v16[330] = BYTE5(v14);
    v16[329] = BYTE6(v14);
    v16[328] = HIBYTE(v14);
  }
  while ( v13 != 8 );
  return a1 + 328;
}

/* ===== uint_to_str @ 0x94044464 size 132 ===== */
__int64 __fastcall uint_to_str(unsigned __int64 a1, __int64 a2)
{
  __int64 v2; // x3
  int v3; // w2
  __int64 v4; // x6
  __int64 result; // x0
  _BYTE v6[32]; // [xsp-20h] [xbp-20h] BYREF

  v2 = 0;
  do
  {
    ++v2;
    v3 = a1 % 0xA;
    a1 /= 0xAu;
    v6[v2 - 1] = v3 + 48;
    if ( a1 == 0 )
    {
      v4 = v2 - 1;
      goto LABEL_5;
    }
  }
  while ( v2 != 31 );
  v4 = 30;
LABEL_5:
  result = 0;
  do
  {
    *(_BYTE *)(a2 + result) = v6[v4 - result];
    ++result;
  }
  while ( result != v2 );
  *(_BYTE *)(a2 + result) = 0;
  return result;
}

/* ===== avb_cmdline_append @ 0x940444E8 size 296 ===== */
__int64 __fastcall avb_cmdline_append(__int64 *a1, __int64 a2, __int64 a3)
{
  __int64 v6; // x22
  __int64 v7; // x24
  __int64 v8; // x0
  __int64 v9; // x27
  __int64 v10; // x20
  __int64 v11; // x21
  __int64 v12; // x0
  __int64 v13; // x19

  v6 = strlen(a2);
  v7 = strlen(a3);
  if ( *a1 != 0 )
  {
    v8 = strlen(*a1);
    v9 = v8;
    if ( v8 != 0 )
    {
      v10 = v8 + 1;
      v11 = v8 + 1 + v6;
      v12 = avb_calloc(v7 + 2 + v11);
      v13 = v12;
      if ( v12 != 0 )
      {
        if ( v10 != 0 )
        {
          memcpy(v12, *a1, v9);
          *(_BYTE *)(v13 + v9) = 32;
        }
        goto LABEL_6;
      }
      return 0;
    }
  }
  v13 = avb_calloc(v6 + v7 + 2);
  if ( v13 == 0 )
    return 0;
  v11 = v6;
  v10 = 0;
LABEL_6:
  memcpy(v13 + v10, a2, v6);
  *(_BYTE *)(v13 + v11) = 61;
  memcpy(v13 + v11 + 1, a3, v7);
  if ( *a1 != 0 )
    free(*a1);
  *a1 = v13;
  return 1;
}

/* ===== avb_cmdline_append_hash @ 0x94044610 size 204 ===== */
__int64 __fastcall avb_cmdline_append_hash(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // x21
  __int64 v5; // x19
  __int64 result; // x0
  __int64 v7; // x3
  __int64 i; // x0
  char v9; // w4
  unsigned int v10; // w20
  char v13[24]; // [xsp+48h] [xbp+48h] BYREF

  v3 = 2 * a3;
  strcpy(v13, "0123456789abcdef");
  v5 = avb_malloc(2 * a3 + 1);
  result = 0;
  if ( v5 != 0 )
  {
    v7 = v5;
    for ( i = 0; i != a3; ++i )
    {
      v7 += 2;
      *(_BYTE *)(v7 - 2) = v13[*(_BYTE *)(a2 + i) >> 4];
      v9 = *(_BYTE *)(a2 + i);
      *(_BYTE *)(v7 - 1) = v13[v9 & 0xF];
    }
    *(_BYTE *)(v5 + v3) = 0;
    v10 = avb_cmdline_append((__int64 *)(a1 + 40), (__int64)"androidboot.vbmeta.digest", v5);
    free(v5);
    return v10;
  }
  return result;
}

/* ===== load_and_verify_vbmeta @ 0x940446DC size 4620 ===== */
__int64 __fastcall load_and_verify_vbmeta(
        __int64 a1,
        __int64 *a2,
        __int64 a3,
        unsigned int a4,
        int a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13,
        double a14,
        double a15,
        double a16,
        __int64 a17,
        _QWORD *a18,
        _DWORD *a19,
        __int64 a20)
{
  int v28; // w20
  double v29; // d0
  double v30; // d1
  double v31; // d2
  double v32; // d3
  double v33; // d4
  double v34; // d5
  double v35; // d6
  double v36; // d7
  unsigned int v37; // w20
  __int64 v39; // x0
  double v40; // d0
  double v41; // d1
  double v42; // d2
  double v43; // d3
  double v44; // d4
  double v45; // d5
  double v46; // d6
  double v47; // d7
  unsigned __int64 v48; // x20
  __int64 v49; // x25
  double v50; // d0
  double v51; // d1
  double v52; // d2
  double v53; // d3
  double v54; // d4
  double v55; // d5
  double v56; // d6
  double v57; // d7
  unsigned int v58; // w0
  double v59; // d0
  double v60; // d1
  double v61; // d2
  double v62; // d3
  double v63; // d4
  double v64; // d5
  double v65; // d6
  double v66; // d7
  double v67; // d0
  double v68; // d1
  double v69; // d2
  double v70; // d3
  double v71; // d4
  double v72; // d5
  double v73; // d6
  double v74; // d7
  double v75; // d0
  double v76; // d1
  double v77; // d2
  double v78; // d3
  double v79; // d4
  double v80; // d5
  double v81; // d6
  double v82; // d7
  __int64 v83; // x1
  double v84; // d0
  double v85; // d1
  double v86; // d2
  double v87; // d3
  double v88; // d4
  double v89; // d5
  double v90; // d6
  double v91; // d7
  double v92; // d0
  double v93; // d1
  double v94; // d2
  double v95; // d3
  double v96; // d4
  double v97; // d5
  double v98; // d6
  double v99; // d7
  __int64 v100; // x0
  double v101; // d0
  double v102; // d1
  double v103; // d2
  double v104; // d3
  double v105; // d4
  double v106; // d5
  double v107; // d6
  double v108; // d7
  __int64 v109; // x3
  unsigned int v110; // w0
  double v111; // d0
  double v112; // d1
  double v113; // d2
  double v114; // d3
  double v115; // d4
  double v116; // d5
  double v117; // d6
  double v118; // d7
  int v119; // w0
  double v120; // d0
  double v121; // d1
  double v122; // d2
  double v123; // d3
  double v124; // d4
  double v125; // d5
  double v126; // d6
  double v127; // d7
  double v128; // d0
  double v129; // d1
  double v130; // d2
  double v131; // d3
  double v132; // d4
  double v133; // d5
  double v134; // d6
  double v135; // d7
  double v136; // d0
  double v137; // d1
  double v138; // d2
  double v139; // d3
  double v140; // d4
  double v141; // d5
  double v142; // d6
  double v143; // d7
  unsigned __int64 v144; // x0
  __int64 v145; // x1
  __int64 v146; // x22
  __int64 v147; // x24
  __int64 v148; // x0
  __int64 v149; // x4
  __int64 v150; // x3
  __int64 v151; // x1
  unsigned __int64 v152; // x1
  double v153; // d0
  double v154; // d1
  double v155; // d2
  double v156; // d3
  double v157; // d4
  double v158; // d5
  double v159; // d6
  double v160; // d7
  double v161; // d0
  double v162; // d1
  double v163; // d2
  double v164; // d3
  double v165; // d4
  double v166; // d5
  double v167; // d6
  double v168; // d7
  double v169; // d0
  double v170; // d1
  double v171; // d2
  double v172; // d3
  double v173; // d4
  double v174; // d5
  double v175; // d6
  double v176; // d7
  __int64 v177; // x24
  double v178; // d0
  double v179; // d1
  double v180; // d2
  double v181; // d3
  double v182; // d4
  double v183; // d5
  double v184; // d6
  double v185; // d7
  double v186; // d0
  double v187; // d1
  double v188; // d2
  double v189; // d3
  double v190; // d4
  double v191; // d5
  double v192; // d6
  double v193; // d7
  __int64 v194; // x23
  __int64 v195; // x0
  __int64 v196; // x19
  __int64 v197; // x0
  __int64 v198; // x28
  unsigned int v199; // w0
  double v200; // d0
  double v201; // d1
  double v202; // d2
  double v203; // d3
  double v204; // d4
  double v205; // d5
  double v206; // d6
  double v207; // d7
  double v208; // d0
  double v209; // d1
  double v210; // d2
  double v211; // d3
  double v212; // d4
  double v213; // d5
  double v214; // d6
  double v215; // d7
  _QWORD *v216; // x23
  double v217; // d0
  double v218; // d1
  double v219; // d2
  double v220; // d3
  double v221; // d4
  double v222; // d5
  double v223; // d6
  double v224; // d7
  __int64 v225; // x3
  int v226; // w4
  double v227; // d0
  double v228; // d1
  double v229; // d2
  double v230; // d3
  double v231; // d4
  double v232; // d5
  double v233; // d6
  double v234; // d7
  double v235; // d0
  double v236; // d1
  double v237; // d2
  double v238; // d3
  double v239; // d4
  double v240; // d5
  double v241; // d6
  double v242; // d7
  __int64 v243; // x23
  __int64 v244; // x19
  double v245; // d0
  double v246; // d1
  double v247; // d2
  double v248; // d3
  double v249; // d4
  double v250; // d5
  double v251; // d6
  double v252; // d7
  __int64 v253; // x0
  double v254; // d0
  double v255; // d1
  double v256; // d2
  double v257; // d3
  double v258; // d4
  double v259; // d5
  double v260; // d6
  double v261; // d7
  __int64 v262; // x0
  double v263; // d0
  double v264; // d1
  double v265; // d2
  double v266; // d3
  double v267; // d4
  double v268; // d5
  double v269; // d6
  double v270; // d7
  int v271; // w0
  __int64 v272; // x0
  char *v273; // x23
  double v274; // d0
  double v275; // d1
  double v276; // d2
  double v277; // d3
  double v278; // d4
  double v279; // d5
  double v280; // d6
  double v281; // d7
  __int64 v282; // x0
  double v283; // d0
  double v284; // d1
  double v285; // d2
  double v286; // d3
  double v287; // d4
  double v288; // d5
  double v289; // d6
  double v290; // d7
  __int64 v291; // x0
  __int64 v292; // x0
  __int64 v293; // x28
  __int64 v294; // x19
  __int64 v295; // x0
  double v296; // d0
  double v297; // d1
  double v298; // d2
  double v299; // d3
  double v300; // d4
  double v301; // d5
  double v302; // d6
  double v303; // d7
  __int64 v304; // x2
  const char *v305; // x2
  double v306; // d0
  double v307; // d1
  double v308; // d2
  double v309; // d3
  double v310; // d4
  double v311; // d5
  double v312; // d6
  double v313; // d7
  __int64 v314; // x0
  double v315; // d0
  double v316; // d1
  double v317; // d2
  double v318; // d3
  double v319; // d4
  double v320; // d5
  double v321; // d6
  double v322; // d7
  __int64 v323; // x0
  __int64 v324; // x1
  __int64 v325; // x19
  __int64 v326; // x23
  __int64 v327; // x0
  __int64 v328; // x4
  __int64 v329; // x3
  double v330; // d0
  double v331; // d1
  double v332; // d2
  double v333; // d3
  double v334; // d4
  double v335; // d5
  double v336; // d6
  double v337; // d7
  __int64 v338; // x0
  __int64 v339; // x1
  __int64 v340; // x19
  __int64 v341; // x23
  __int64 v342; // x0
  __int64 v343; // x1
  double v344; // d0
  double v345; // d1
  double v346; // d2
  double v347; // d3
  double v348; // d4
  double v349; // d5
  double v350; // d6
  double v351; // d7
  double v352; // d0
  double v353; // d1
  double v354; // d2
  double v355; // d3
  double v356; // d4
  double v357; // d5
  double v358; // d6
  double v359; // d7
  double v360; // d0
  double v361; // d1
  double v362; // d2
  double v363; // d3
  double v364; // d4
  double v365; // d5
  double v366; // d6
  double v367; // d7
  __int64 v368; // [xsp+80h] [xbp+60h]
  int v369; // [xsp+98h] [xbp+78h]
  unsigned int v370; // [xsp+9Ch] [xbp+7Ch]
  __int64 v371; // [xsp+A0h] [xbp+80h]
  unsigned int v372; // [xsp+A8h] [xbp+88h]
  __int64 v373; // [xsp+A8h] [xbp+88h]
  char v374; // [xsp+B0h] [xbp+90h]
  unsigned int v375; // [xsp+C8h] [xbp+A8h]
  int v376; // [xsp+D8h] [xbp+B8h]
  __int64 v377; // [xsp+D8h] [xbp+B8h]
  BOOL v378; // [xsp+E8h] [xbp+C8h]
  __int64 v379; // [xsp+E8h] [xbp+C8h]
  __int64 v380; // [xsp+F0h] [xbp+D0h]
  BOOL v381; // [xsp+F0h] [xbp+D0h]
  int v382; // [xsp+F8h] [xbp+D8h]
  unsigned __int64 v383; // [xsp+108h] [xbp+E8h] BYREF
  __int64 v384; // [xsp+110h] [xbp+F0h] BYREF
  __int64 v385; // [xsp+118h] [xbp+F8h] BYREF
  unsigned __int64 v386; // [xsp+120h] [xbp+100h] BYREF
  unsigned __int64 v387; // [xsp+128h] [xbp+108h] BYREF
  __int64 v388; // [xsp+130h] [xbp+110h] BYREF
  char v389[32]; // [xsp+140h] [xbp+120h] BYREF
  char v390[32]; // [xsp+160h] [xbp+140h] BYREF
  _QWORD v391[3]; // [xsp+180h] [xbp+160h] BYREF
  unsigned int v392[28]; // [xsp+198h] [xbp+178h] BYREF
  _QWORD v393[32]; // [xsp+208h] [xbp+1E8h] BYREF
  unsigned int v394[4]; // [xsp+308h] [xbp+2E8h] BYREF
  int v395; // [xsp+318h] [xbp+2F8h]
  __int64 v396; // [xsp+31Ch] [xbp+2FCh]
  unsigned __int64 v397; // [xsp+324h] [xbp+304h]

  if ( a18 == nullptr )
    sprd_log(0, "assert fail: slot_data != NULL\n", a9, a10, a11, a12, a13, a14, a15, a16);
  v28 = strcmp(a6, (__int64)"vbmeta");
  if ( (unsigned int)is_valid_utf8(a6, a7) == 0 )
  {
    v37 = 6;
    sprd_log(0, "Partition name is not valid UTF-8.\n", v29, v30, v31, v32, v33, v34, v35, v36);
    return v37;
  }
  v39 = strlen(a3);
  if ( (unsigned int)concat_partition_name_suffix(v389, 32, a6, a7, a3, v39) == 0 )
  {
    v37 = 6;
    sprd_log(0, "Partition name and suffix does not fit.\n", v40, v41, v42, v43, v44, v45, v46, v47);
    return v37;
  }
  v378 = v28 == 0;
  sprd_log(7u, "Loading vbmeta struct from partition '%s'.\n", v40, v41, v42, v43, v44, v45, v46, v47, v389, 0);
  if ( v28 != 0 )
  {
    if ( (unsigned int)strcmp(a6, (__int64)"system") != 0
      && (unsigned int)strcmp(a6, (__int64)"vendor") != 0 )
    {
      v199 = (*(__int64 (__fastcall **)(__int64, char *, __int64, __int64, _QWORD *, _QWORD *))(a1 + 24))(
               a1,
               v389,
               -64,
               64,
               v393,
               v391);
      if ( v199 == 1 )
      {
        v37 = 1;
        sprd_log(
          7u,
          "in %s, l:%d, return err %d. \n",
          v200,
          v201,
          v202,
          v203,
          v204,
          v205,
          v206,
          v207,
          "load_and_verify_vbmeta",
          327);
        return v37;
      }
      if ( v199 != 0 )
      {
        v37 = 2;
        sprd_log(0, v389, v200, v201, v202, v203, v204, v205, v206, v207, ": Error loading footer.\n", 0, v199);
        return v37;
      }
      if ( v391[0] != 64 )
        sprd_log(
          0,
          "assert fail: footer_num_read == AVB_FOOTER_SIZE\n",
          v200,
          v201,
          v202,
          v203,
          v204,
          v205,
          v206,
          v207);
      if ( (unsigned int)avb_footer_validate((__int64)v393, (__int64)v394) == 0 )
      {
        v37 = 6;
        sprd_log(0, v389, v208, v209, v210, v211, v212, v213, v214, v215, ": Error validating footer.\n", 0);
        return v37;
      }
      v48 = v397;
      if ( v397 > 0x10000 )
      {
        v37 = 6;
        sprd_log(0, v389, v208, v209, v210, v211, v212, v213, v214, v215, ": Invalid vbmeta size in footer.\n", 0);
        return v37;
      }
      v380 = v396;
    }
    else
    {
      v380 = 0;
      v48 = MEMORY[0xFFFFFFFFE0064404];
    }
  }
  else
  {
    v380 = 0;
    v48 = MEMORY[0xFFFFFFFFE0064408];
  }
  v49 = avb_malloc(v48);
  if ( v49 == 0 )
  {
    v37 = 1;
    sprd_log(
      7u,
      "in %s, l:%d, return err %d. \n",
      v50,
      v51,
      v52,
      v53,
      v54,
      v55,
      v56,
      v57,
      "load_and_verify_vbmeta",
      358);
    return v37;
  }
  sprd_log(7u, ">>> begin to load vbmeta image of partition:%s.\n", v50, v51, v52, v53, v54, v55, v56, v57, v389, 0);
  v58 = (*(__int64 (__fastcall **)(__int64, char *, __int64, unsigned __int64, __int64, unsigned __int64 *))(a1 + 24))(
          a1,
          v389,
          v380,
          v48,
          v49,
          &v383);
  if ( v58 == 1 )
  {
    v37 = 1;
    sprd_log(
      7u,
      "in %s, l:%d, return err %d. \n",
      v59,
      v60,
      v61,
      v62,
      v63,
      v64,
      v65,
      v66,
      "load_and_verify_vbmeta",
      371);
    goto LABEL_27;
  }
  v381 = a5 == 0;
  if ( v58 != 0 )
  {
    if ( v378 && a5 == 0 && v58 == 3 )
    {
      sprd_log(7u, v389, v59, v60, v61, v62, v63, v64, v65, v66, ": No such partition. Trying 'boot' instead.\n", 0);
      v272 = strlen("boot");
      v37 = load_and_verify_vbmeta(a1, a2, a3, a4, 0, "boot", v272, 0, 0, a18, a19, a20);
    }
    else
    {
      v37 = 2;
      sprd_log(0, v389, v59, v60, v61, v62, v63, v64, v65, v66, ": Error loading vbmeta data.\n", 0, v58);
    }
    goto LABEL_27;
  }
  if ( v48 < v383 )
    sprd_log(0, "assert fail: vbmeta_num_read <= vbmeta_size\n", v59, v60, v61, v62, v63, v64, v65, v66);
  if ( !v378 || MEMORY[0xFFFFFFFFE0057F10] == 0 )
  {
    v375 = avb_vbmeta_verify(v49, v383, &v384, &v385, 0);
    sprd_log(
      7u,
      "partition: %s vbmeta_verify_ret is :%d. \n",
      v84,
      v85,
      v86,
      v87,
      v88,
      v89,
      v90,
      v91,
      v389,
      v375,
      0);
    switch ( v375 )
    {
      case 0u:
        if ( v384 == 0 || (v37 = 0, v385 == 0) )
        {
          v37 = 0;
          sprd_log(0, "assert fail: pk_data != NULL && pk_len > 0\n", v92, v93, v94, v95, v96, v97, v98, v99);
        }
        goto LABEL_18;
      case 1u:
      case 4u:
      case 5u:
        v37 = 3;
        v100 = avb_vbmeta_verify_result_to_string(v375);
        sprd_log(
          0,
          v389,
          v101,
          v102,
          v103,
          v104,
          v105,
          v106,
          v107,
          v108,
          ": Error verifying vbmeta image: ",
          v100,
          "\n",
          0);
        if ( a4 != 0 )
          goto LABEL_18;
        goto LABEL_27;
      case 2u:
        v37 = 6;
        sprd_log(
          0,
          v389,
          v92,
          v93,
          v94,
          v95,
          v96,
          v97,
          v98,
          v99,
          ": Error verifying vbmeta image: invalid vbmeta header\n",
          0);
        goto LABEL_27;
      case 3u:
        v37 = 7;
        sprd_log(
          0,
          v389,
          v92,
          v93,
          v94,
          v95,
          v96,
          v97,
          v98,
          v99,
          ": Error verifying vbmeta image: unsupported AVB version\n",
          0);
        goto LABEL_27;
      default:
        v37 = 0;
        goto LABEL_18;
    }
  }
  v37 = 0;
  v375 = 0;
  v384 = 0;
  v385 = 0;
LABEL_18:
  avb_vbmeta_header_parse(v49, v393);
  if ( a5 != 0 )
  {
    v374 = 0;
    if ( LODWORD(v393[15]) != 0 )
    {
      v37 = 6;
      sprd_log(0, v389, v67, v68, v69, v70, v71, v72, v73, v74, ": chained vbmeta image has non-zero flags\n", 0);
      goto LABEL_27;
    }
  }
  else
  {
    v374 = v393[15];
  }
  if ( v384 != 0 )
  {
    nullsub_9("pk_data", v384, (unsigned int)v385);
    v83 = v384;
    if ( v384 != 0 )
    {
      if ( a8 != 0 )
      {
        if ( a5 == 0 )
          sprd_log(0, "assert fail: !is_main_vbmeta\n", v75, v76, v77, v78, v79, v80, v81, v82);
        if ( v385 != a17 || (unsigned int)memcmp_neq(a8, v384, a17) != 0 )
        {
          v37 = 5;
          sprd_log(
            0,
            v389,
            v75,
            v76,
            v77,
            v78,
            v79,
            v80,
            v81,
            v82,
            ": Public key used to sign data does not match key in chain partition descriptor.\n",
            0);
          if ( a4 == 0 )
            goto LABEL_27;
        }
      }
      else
      {
        v394[0] = 0;
        v109 = 0;
        if ( v393[11] != 0 )
          v109 = v49 + *(_QWORD *)((char *)&v393[1] + 4) + v393[10] + 256LL;
        if ( a5 != 0 )
        {
          v373 = v109;
          sprd_log(0, "assert fail: is_main_vbmeta\n", v75, v76, v77, v78, v79, v80, v81, v82);
          v109 = v373;
          v83 = v384;
        }
        v110 = (*(__int64 (__fastcall **)(__int64, __int64, __int64, __int64))(a1 + 40))(a1, v83, v385, v109);
        if ( v110 == 1 )
        {
          v37 = 1;
          sprd_log(
            7u,
            "in %s, l:%d, return err %d. \n",
            v111,
            v112,
            v113,
            v114,
            v115,
            v116,
            v117,
            v118,
            "load_and_verify_vbmeta",
            508);
          goto LABEL_27;
        }
        if ( v110 != 0 )
        {
          v37 = 2;
          sprd_log(
            0,
            v389,
            v111,
            v112,
            v113,
            v114,
            v115,
            v116,
            v117,
            v118,
            ": Error while checking public key used to sign data.\n",
            0,
            v110);
          goto LABEL_27;
        }
        if ( v394[0] == 0 )
        {
          v37 = 5;
          sprd_log(
            0,
            v389,
            v111,
            v112,
            v113,
            v114,
            v115,
            v116,
            v117,
            v118,
            ": Public key used to sign data rejected.\n",
            0,
            v110);
          if ( a4 == 0 )
            goto LABEL_27;
        }
        if ( v378 )
          MEMORY[0xFFFFFFFFE0057F10] = 1;
      }
    }
  }
  v379 = a5;
  v119 = (*(__int64 (__fastcall **)(__int64, _QWORD, unsigned __int64 *))(a1 + 48))(a1, a5, &v386);
  if ( v119 == 1 )
  {
    v37 = 1;
    goto LABEL_27;
  }
  if ( v119 != 0 )
  {
    v37 = 2;
    sprd_log(
      0,
      v389,
      v120,
      v121,
      v122,
      v123,
      v124,
      v125,
      v126,
      v127,
      ": Error getting rollback index for location.\n",
      0);
    goto LABEL_27;
  }
  if ( v393[14] >= v386 )
  {
    sprd_log(
      7u,
      "Info: vbmeta_header.rollback_index:%d, >= stored_rollback_index:%d.\n",
      v120,
      v121,
      v122,
      v123,
      v124,
      v125,
      v126,
      v127);
    v144 = v393[14];
    *(_DWORD *)(4LL * a5 - 536460624) = v393[14];
  }
  else
  {
    v37 = 4;
    sprd_log(
      7u,
      "Error: vbmeta_header.rollback_index:%d, < stored_rollback_index:%d.\n",
      v120,
      v121,
      v122,
      v123,
      v124,
      v125,
      v126,
      v127);
    sprd_log(
      0,
      v389,
      v128,
      v129,
      v130,
      v131,
      v132,
      v133,
      v134,
      v135,
      ": Image rollback index is less than the stored rollback index.\n",
      0);
    if ( a4 == 0 )
      goto LABEL_27;
    v144 = v393[14];
    *(_DWORD *)(4LL * a5 - 536460624) = v386;
  }
  if ( v386 < v144 )
  {
    sprd_log(7u, "set update version flag.\n", v136, v137, v138, v139, v140, v141, v142, v143);
    MEMORY[0xFFFFFFFFE00642E4] = 1;
  }
  if ( a5 != 0 )
  {
    v291 = a18[2];
    if ( v291 == 0 )
    {
      sprd_log(0, "assert fail: slot_data->num_vbmeta_images > 0\n", v136, v137, v138, v139, v140, v141, v142, v143);
      v291 = a18[2];
    }
  }
  else
  {
    v145 = a18[2];
    if ( v145 == 0 )
      goto LABEL_65;
    sprd_log(0, "assert fail: slot_data->num_vbmeta_images == 0\n", v136, v137, v138, v139, v140, v141, v142, v143);
    v291 = a18[2];
  }
  v145 = v291;
  if ( v291 == 32 )
  {
    v37 = 1;
    sprd_log(0, v389, v136, v137, v138, v139, v140, v141, v142, v143, ": Too many vbmeta images.\n", 0);
    goto LABEL_27;
  }
LABEL_65:
  v146 = 32 * v145;
  v147 = a18[1];
  a18[2] = v145 + 1;
  v148 = avb_strdup(a6);
  v149 = v147 + v146;
  v150 = *(_QWORD *)((char *)&v393[1] + 4);
  v151 = *(_QWORD *)((char *)&v393[2] + 4);
  *(_QWORD *)(v147 + v146) = v148;
  *(_QWORD *)(v149 + 16) = v150 + v151 + 256;
  v152 = v383;
  *(_QWORD *)(v149 + 8) = v49;
  *(_DWORD *)(v149 + 24) = v375;
  v49 = avb_get_all_descriptors(v49, v152, &v387, v153, v154, v155, v156, v157, v158, v159, v160);
  sprd_log(
    7u,
    "in %s, l:%d. num_descriptors:%d.\n",
    v161,
    v162,
    v163,
    v164,
    v165,
    v166,
    v167,
    v168,
    "load_and_verify_vbmeta",
    605,
    v387,
    0);
  if ( v387 != 0 )
  {
    v376 = v37;
    v177 = 0;
    v382 = 0;
    v372 = a4;
    v369 = a5;
    while ( 1 )
    {
      if ( (unsigned int)avb_desc_header_validate(*(_QWORD **)(v49 + 8 * v177), &v388) == 0 )
      {
        v37 = 6;
        sprd_log(0, v389, v178, v179, v180, v181, v182, v183, v184, v185, &loc_940562B0, 0);
        goto LABEL_27;
      }
      sprd_log(
        7u,
        "in %s, l:%d. desc.tag:0x%llx.\n",
        v178,
        v179,
        v180,
        v181,
        v182,
        v183,
        v184,
        v185,
        "load_and_verify_vbmeta",
        615,
        v388,
        0);
      switch ( v388 )
      {
        case 3LL:
          if ( (unsigned int)avb_cmdline_desc_parse(*(_QWORD **)(v49 + 8 * v177), (__int64)v394) == 0 )
          {
            v37 = 6;
            sprd_log(
              0,
              v389,
              v186,
              v187,
              v188,
              v189,
              v190,
              v191,
              v192,
              v193,
              ": Kernel cmdline descriptor is invalid.\n",
              0);
            goto LABEL_27;
          }
          v194 = *(_QWORD *)(v49 + 8 * v177) + 24LL;
          if ( (unsigned int)is_valid_utf8(v194, (unsigned int)v396) == 0 )
          {
            v37 = 6;
            sprd_log(
              0,
              v389,
              v169,
              v170,
              v171,
              v172,
              v173,
              v174,
              v175,
              v176,
              ": Kernel cmdline is not valid UTF-8.\n",
              0);
            sprd_log(
              7u,
              "in %s, l:%d. \n",
              v360,
              v361,
              v362,
              v363,
              v364,
              v365,
              v366,
              v367,
              "load_and_verify_vbmeta",
              727,
              0);
            goto LABEL_27;
          }
          if ( (v374 & 1) != 0 )
          {
            if ( (v395 & 1) == 0 )
              goto LABEL_76;
          }
          else if ( (v395 & 2) == 0 )
          {
LABEL_76:
            v195 = a18[5];
            if ( v195 != 0 )
            {
              v196 = strlen(v195);
              v197 = avb_calloc((unsigned int)v396 + 2LL + v196);
              v198 = v197;
              if ( v197 == 0 )
                goto LABEL_165;
              memcpy(v197, a18[5], v196);
              *(_BYTE *)(v198 + v196) = 32;
              memcpy(v198 + v196 + 1, v194, (unsigned int)v396);
              free(a18[5]);
              a18[5] = v198;
            }
            else
            {
              v314 = avb_calloc((unsigned int)(v396 + 1));
              a18[5] = v314;
              if ( v314 == 0 )
              {
LABEL_165:
                v37 = 1;
                goto LABEL_27;
              }
              memcpy(v314, v194, (unsigned int)v396);
            }
          }
          break;
        case 4LL:
          if ( v382 == 0 )
          {
            if ( !v381 )
            {
              v37 = 6;
              sprd_log(
                0,
                v389,
                v169,
                v170,
                v171,
                v172,
                v173,
                v174,
                v175,
                v176,
                ": Encountered chain descriptor not in main image.\n",
                0);
              sprd_log(
                7u,
                "in %s, l:%d, return err %d. \n",
                v352,
                v353,
                v354,
                v355,
                v356,
                v357,
                v358,
                v359,
                "load_and_verify_vbmeta",
                650,
                6,
                0);
              goto LABEL_27;
            }
            if ( (unsigned int)avb_chain_partition_validate(*(_QWORD *)(v49 + 8 * v177), (__int64)v394) == 0 )
            {
              v37 = 6;
              sprd_log(
                0,
                v389,
                v235,
                v236,
                v237,
                v238,
                v239,
                v240,
                v241,
                v242,
                ": Chain partition descriptor is invalid.\n",
                0);
              sprd_log(
                7u,
                "in %s, l:%d, return err %d. \n",
                v344,
                v345,
                v346,
                v347,
                v348,
                v349,
                v350,
                v351,
                "load_and_verify_vbmeta",
                660,
                6,
                0);
              goto LABEL_27;
            }
            if ( v395 == 0 )
            {
              v37 = 6;
              sprd_log(
                0,
                v389,
                v235,
                v236,
                v237,
                v238,
                v239,
                v240,
                v241,
                v242,
                ": Chain partition has invalid rollback_index_location field.\n",
                0);
              goto LABEL_27;
            }
            v243 = (unsigned int)v396;
            v244 = *(_QWORD *)(v49 + 8 * v177) + 92LL;
            if ( *(_QWORD *)(v49 + 8 * v177) != -92 && *a2 != 0 && (unsigned int)memcmp(v244, *a2, v396) != 0 )
            {
              v376 = 6;
              sprd_log(
                7u,
                "Info::>>> chain_partition_name:%s != requested_partitions[0]:%s. skip .... \n",
                v245,
                v246,
                v247,
                v248,
                v249,
                v250,
                v251,
                v252,
                v244,
                *a2,
                0);
            }
            else
            {
              v253 = avb_malloc((unsigned int)(v396 + 1));
              *(_QWORD *)(a20 + 8) = v253;
              if ( v253 != 0 )
              {
                memcpy(v253, v244, (unsigned int)v396);
                *(_BYTE *)(*(_QWORD *)(a20 + 8) + (unsigned int)v396) = 0;
              }
              else
              {
                sprd_log(0, "partname buffer NULL\n", v254, v255, v256, v257, v258, v259, v260, v261);
              }
              v262 = avb_malloc(HIDWORD(v396));
              *(_QWORD *)(a20 + 16) = v262;
              if ( v262 != 0 )
                memcpy(v262, v244 + v243, HIDWORD(v396));
              else
                sprd_log(0, (const char *)&loc_94056568, v263, v264, v265, v266, v267, v268, v269, v270);
              v382 = 1;
              v271 = v395;
              v376 = 0;
              *(_QWORD *)(a20 + 24) = HIDWORD(v396);
              *(_DWORD *)a20 = v271;
            }
          }
          break;
        case 2LL:
          v216 = *(_QWORD **)(v49 + 8 * v177);
          if ( (unsigned int)avb_hash_desc_parse(v216, (__int64)v391) == 0 )
          {
            v225 = 100;
            v226 = 6;
            goto LABEL_89;
          }
          v273 = (char *)v216 + 132;
          v371 = v392[8];
          v370 = v392[9];
          if ( (unsigned int)is_valid_utf8(v273, v392[8]) == 0 )
          {
            v37 = 6;
            sprd_log(0, "Partition name is not valid UTF-8.\n", v274, v275, v276, v277, v278, v279, v280, v281);
            v225 = 112;
            goto LABEL_90;
          }
          v368 = v392[8];
          v282 = strlen(a3);
          if ( (unsigned int)concat_partition_name_suffix(v390, 32, v273, v368, a3, v282) == 0 )
          {
            v37 = 6;
            sprd_log(0, "Partition name and suffix does not fit.\n", v283, v284, v285, v286, v287, v288, v289, v290);
            goto LABEL_91;
          }
          v292 = sprd_log(
                   7u,
                   "in %s, l:%d.hash_desc.image_size:0x%llx.\n",
                   v283,
                   v284,
                   v285,
                   v286,
                   v287,
                   v288,
                   v289,
                   v290,
                   "load_and_verify_hash_partition",
                   127,
                   v391[2],
                   0);
          v293 = avb_get_image_buffer(v292);
          if ( v293 == 0 )
          {
            v225 = 135;
            v226 = 1;
LABEL_89:
            v37 = v226;
LABEL_90:
            sprd_log(
              7u,
              "in %s, l:%d, return err %d. \n",
              v217,
              v218,
              v219,
              v220,
              v221,
              v222,
              v223,
              v224,
              "load_and_verify_hash_partition",
              v225);
LABEL_91:
            sprd_log(
              7u,
              "in %s, l:%d.sub_ret:%d.\n",
              v227,
              v228,
              v229,
              v230,
              v231,
              v232,
              v233,
              v234,
              "load_and_verify_vbmeta",
              627,
              v37,
              0);
            goto LABEL_92;
          }
          v294 = (__int64)&v273[v371];
          sprd_log(
            7u,
            "in %s, l:%d. Warning: Read partition to be verified... name:%s, size:0x%llx >>>>> \n",
            v217,
            v218,
            v219,
            v220,
            v221,
            v222,
            v223,
            v224,
            "load_and_verify_hash_partition",
            139,
            v390,
            v391[2],
            0);
          if ( (unsigned int)strcmp((__int64)v392, (__int64)"sha256") != 0 )
          {
            if ( (unsigned int)strcmp((__int64)v392, (__int64)"sha512") != 0 )
            {
              v305 = ": Unsupported hash algorithm.\n";
              v37 = 6;
              goto LABEL_126;
            }
            sha512_init((__int64)v394);
            sha512_update((__int64)v394, v294, v392[9]);
            sha512_update((__int64)v394, v293, v391[2]);
            v295 = sha512_final((__int64)v394);
            v304 = 64;
          }
          else
          {
            sha256_init(v394);
            sha256_update(v394, v294, v392[9]);
            sha256_update(v394, v293, v391[2]);
            v295 = sha256_final((__int64)v394);
            v304 = 32;
          }
          if ( v392[10] != v304 )
          {
            v305 = ": Digest in descriptor not of expected size.\n";
            v37 = 6;
            goto LABEL_126;
          }
          if ( (unsigned int)memcmp_neq(v295, v294 + v370, v304) != 0 )
          {
            sprd_log(
              0,
              v390,
              v315,
              v316,
              v317,
              v318,
              v319,
              v320,
              v321,
              v322,
              ": Hash of data does not match digest in descriptor.\n",
              0);
            v338 = avb_str_in_list(a2, v273, v392[8]);
            if ( v338 != 0 )
            {
              v339 = a18[4];
              if ( v339 == 32 )
              {
LABEL_163:
                v305 = ": Too many loaded partitions.\n";
                v37 = 1;
LABEL_126:
                sprd_log(0, v390, v296, v297, v298, v299, v300, v301, v302, v303, v305, 0);
                sprd_log(
                  7u,
                  "in %s, l:%d.sub_ret:%d.\n",
                  v306,
                  v307,
                  v308,
                  v309,
                  v310,
                  v311,
                  v312,
                  v313,
                  "load_and_verify_vbmeta",
                  627,
                  v37,
                  0);
LABEL_92:
                sprd_log(
                  7u,
                  "in %s, l:%d. \n",
                  v169,
                  v170,
                  v171,
                  v172,
                  v173,
                  v174,
                  v175,
                  v176,
                  "load_and_verify_vbmeta",
                  632,
                  0);
                goto LABEL_27;
              }
              v340 = 24 * v339;
              v377 = a18[3];
              v341 = v377 + 24 * v339;
              a18[4] = v339 + 1;
              v342 = avb_strdup(v338);
              v343 = v391[2];
              *(_QWORD *)(v377 + v340) = v342;
              *(_QWORD *)(v341 + 16) = v343;
              *(_QWORD *)(v341 + 8) = v293;
            }
            sprd_log(
              7u,
              "in %s, l:%d.sub_ret:%d.\n",
              v296,
              v297,
              v298,
              v299,
              v300,
              v301,
              v302,
              v303,
              "load_and_verify_vbmeta",
              627,
              3,
              0);
            if ( v372 == 0 )
            {
              v37 = 3;
              goto LABEL_92;
            }
            v376 = 3;
          }
          else
          {
            v323 = avb_str_in_list(a2, v273, v392[8]);
            if ( v323 != 0 )
            {
              v324 = a18[4];
              if ( v324 == 32 )
                goto LABEL_163;
              v325 = 24 * v324;
              v326 = a18[3];
              a18[4] = v324 + 1;
              v327 = avb_strdup(v323);
              v328 = v326 + v325;
              v329 = v391[2];
              *(_QWORD *)(v326 + v325) = v327;
              *(_QWORD *)(v328 + 16) = v329;
              *(_QWORD *)(v328 + 8) = v293;
              sprd_log(
                7u,
                "in %s, l:%d.sub_ret:%d.\n",
                v330,
                v331,
                v332,
                v333,
                v334,
                v335,
                v336,
                v337,
                "load_and_verify_vbmeta",
                627,
                0,
                0);
            }
            else
            {
              sprd_log(
                7u,
                "in %s, l:%d.sub_ret:%d.\n",
                v296,
                v297,
                v298,
                v299,
                v300,
                v301,
                v302,
                v303,
                "load_and_verify_vbmeta",
                627,
                0,
                0);
            }
          }
          break;
        default:
          break;
      }
      if ( ++v177 >= v387 )
      {
        v37 = v376;
        a5 = v369;
        break;
      }
    }
  }
  if ( a5 <= 31 )
  {
    a18[v379 + 6] = v393[14];
    if ( a19 != nullptr )
      *a19 = HIDWORD(v393[3]);
    if ( v49 == 0 )
      return v37;
LABEL_27:
    free(v49);
    return v37;
  }
  v37 = 6;
  sprd_log(0, v389, v169, v170, v171, v172, v173, v174, v175, v176, ": Invalid rollback_index_location.\n", 0);
  if ( v49 != 0 )
    goto LABEL_27;
  return v37;
}

/* ===== avb_slot_data_free @ 0x940458E8 size 220 ===== */
__int64 __fastcall avb_slot_data_free(__int64 *a1)
{
  __int64 v2; // x0
  __int64 v3; // x0
  __int64 v4; // x0
  unsigned __int64 v5; // x20
  __int64 v6; // x1
  __int64 v7; // x21
  __int64 v8; // x0
  __int64 v9; // x0
  __int64 v10; // x2
  unsigned __int64 v11; // x3
  __int64 v12; // x21
  unsigned __int64 i; // x20
  __int64 v14; // x1

  v2 = *a1;
  if ( v2 != 0 )
    free(v2);
  v3 = a1[5];
  if ( v3 != 0 )
    free(v3);
  v4 = a1[1];
  if ( v4 != 0 )
  {
    if ( a1[2] != 0 )
    {
      v5 = 0;
      do
      {
        v6 = 32 * v5++;
        v7 = v4 + v6;
        v8 = *(_QWORD *)(v4 + v6);
        if ( v8 != 0 )
          free(v8);
        v9 = *(_QWORD *)(v7 + 8);
        if ( v9 != 0 )
          free(v9);
        v4 = a1[1];
      }
      while ( a1[2] > v5 );
    }
    free(v4);
  }
  v10 = a1[3];
  if ( v10 != 0 )
  {
    v11 = a1[4];
    if ( v11 != 0 )
    {
      v12 = 0;
      for ( i = 0; i < v11; ++i )
      {
        v14 = *(_QWORD *)(v10 + v12);
        v12 += 24;
        if ( v14 != 0 )
        {
          free(v14);
          v11 = a1[4];
          v10 = a1[3];
        }
      }
    }
    free(v10);
  }
  return free((__int64)a1);
}

/* ===== avb_slot_verify @ 0x940459C4 size 2384 ===== */
__int64 __fastcall avb_slot_verify(
        __int64 a1,
        __int64 *a2,
        __int64 a3,
        unsigned int a4,
        __int64 *a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13)
{
  __int64 v18; // x19
  double v19; // d0
  double v20; // d1
  double v21; // d2
  double v22; // d3
  double v23; // d4
  double v24; // d5
  double v25; // d6
  double v26; // d7
  __int64 v27; // x0
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  __int64 v36; // x0
  double v37; // d0
  double v38; // d1
  double v39; // d2
  double v40; // d3
  double v41; // d4
  double v42; // d5
  double v43; // d6
  double v44; // d7
  __int64 v45; // x0
  double v46; // d0
  double v47; // d1
  double v48; // d2
  double v49; // d3
  double v50; // d4
  double v51; // d5
  double v52; // d6
  double v53; // d7
  unsigned int v54; // w20
  double v55; // d0
  double v56; // d1
  double v57; // d2
  double v58; // d3
  double v59; // d4
  double v60; // d5
  double v61; // d6
  double v62; // d7
  double v63; // d0
  double v64; // d1
  double v65; // d2
  double v66; // d3
  double v67; // d4
  double v68; // d5
  double v69; // d6
  double v70; // d7
  __int64 v72; // x0
  double v73; // d0
  double v74; // d1
  double v75; // d2
  double v76; // d3
  double v77; // d4
  double v78; // d5
  double v79; // d6
  double v80; // d7
  unsigned int v81; // w0
  double v82; // d0
  double v83; // d1
  double v84; // d2
  double v85; // d3
  double v86; // d4
  double v87; // d5
  double v88; // d6
  double v89; // d7
  double v90; // d0
  double v91; // d1
  double v92; // d2
  double v93; // d3
  double v94; // d4
  double v95; // d5
  double v96; // d6
  double v97; // d7
  double v98; // d0
  double v99; // d1
  double v100; // d2
  double v101; // d3
  double v102; // d4
  double v103; // d5
  double v104; // d6
  double v105; // d7
  __int64 v106; // x0
  double v107; // d0
  double v108; // d1
  double v109; // d2
  double v110; // d3
  double v111; // d4
  double v112; // d5
  double v113; // d6
  double v114; // d7
  double v115; // d0
  double v116; // d1
  double v117; // d2
  double v118; // d3
  double v119; // d4
  double v120; // d5
  double v121; // d6
  double v122; // d7
  int v123; // w0
  double v124; // d0
  double v125; // d1
  double v126; // d2
  double v127; // d3
  double v128; // d4
  double v129; // d5
  double v130; // d6
  double v131; // d7
  const char *v132; // x6
  const char *v133; // x5
  __int64 v134; // x28
  __int64 v135; // x0
  double v136; // d0
  double v137; // d1
  double v138; // d2
  double v139; // d3
  double v140; // d4
  double v141; // d5
  double v142; // d6
  double v143; // d7
  int v144; // w0
  double v145; // d0
  double v146; // d1
  double v147; // d2
  double v148; // d3
  double v149; // d4
  double v150; // d5
  double v151; // d6
  double v152; // d7
  __int64 v153; // x1
  __int64 v154; // x1
  __int64 v155; // x0
  int v156; // w0
  double v157; // d0
  double v158; // d1
  double v159; // d2
  double v160; // d3
  double v161; // d4
  double v162; // d5
  double v163; // d6
  double v164; // d7
  const char *v165; // x2
  double v166; // d0
  double v167; // d1
  double v168; // d2
  double v169; // d3
  double v170; // d4
  double v171; // d5
  double v172; // d6
  double v173; // d7
  double v174; // d0
  double v175; // d1
  double v176; // d2
  double v177; // d3
  double v178; // d4
  double v179; // d5
  double v180; // d6
  double v181; // d7
  __int64 v182; // x1
  unsigned __int64 v183; // x26
  unsigned __int64 v184; // x25
  __int64 v185; // x23
  __int64 v186; // x2
  __int64 v187; // x1
  unsigned __int64 v188; // x26
  unsigned __int64 v189; // x25
  __int64 v190; // x23
  __int64 v191; // x2
  double v192; // d0
  double v193; // d1
  double v194; // d2
  double v195; // d3
  double v196; // d4
  double v197; // d5
  double v198; // d6
  double v199; // d7
  __int64 v200; // x0
  __int64 v201; // x0
  __int64 v202; // [xsp+80h] [xbp+60h]
  __int64 v203; // [xsp+90h] [xbp+70h]
  __int64 v204; // [xsp+90h] [xbp+70h]
  __int64 *v205; // [xsp+98h] [xbp+78h]
  __int64 v206; // [xsp+A0h] [xbp+80h]
  __int64 v207; // [xsp+A0h] [xbp+80h]
  int v208; // [xsp+A8h] [xbp+88h]
  __int64 v209; // [xsp+B0h] [xbp+90h]
  int v210; // [xsp+B8h] [xbp+98h]
  __int64 v211; // [xsp+B8h] [xbp+98h]
  unsigned int v212; // [xsp+CCh] [xbp+ACh] BYREF
  _QWORD v213[2]; // [xsp+D0h] [xbp+B0h]
  const char *v214; // [xsp+E0h] [xbp+C0h]
  __int64 v215[4]; // [xsp+E8h] [xbp+C8h] BYREF
  _QWORD v216[4]; // [xsp+108h] [xbp+E8h] BYREF
  _BYTE v217[32]; // [xsp+128h] [xbp+108h] BYREF
  unsigned int v218[98]; // [xsp+148h] [xbp+128h] BYREF

  v212 = 0;
  if ( a5 != nullptr )
    *a5 = 0;
  sprd_log(7u, "### enter avb_slot_verify. ###\n", a6, a7, a8, a9, a10, a11, a12, a13);
  v18 = avb_calloc(304);
  if ( v18 == 0 )
  {
    v54 = 1;
    sprd_log(7u, "in %s, l:%d. \n", v19, v20, v21, v22, v23, v24, v25, v26, "avb_slot_verify", 1024, 0);
    goto LABEL_10;
  }
  v27 = avb_calloc(1024);
  *(_QWORD *)(v18 + 8) = v27;
  if ( v27 != 0 )
  {
    v36 = avb_calloc(768);
    *(_QWORD *)(v18 + 24) = v36;
    if ( v36 != 0 )
    {
      v45 = strlen("vbmeta");
      v54 = load_and_verify_vbmeta(
              a1,
              a2,
              a3,
              a4,
              0,
              (__int64)"vbmeta",
              v45,
              0,
              v46,
              v47,
              v48,
              v49,
              v50,
              v51,
              v52,
              v53,
              0,
              (_QWORD *)v18,
              &v212,
              (__int64)v215);
      if ( v54 != 0 && a4 == 0 )
        goto LABEL_8;
      sprd_log(7u, "allow_verification_error:%d, ret:%d\n", v55, v56, v57, v58, v59, v60, v61, v62, a4, v54, 0);
      v208 = v215[0];
      v209 = v215[1];
      v72 = strlen(v215[1]);
      v81 = load_and_verify_vbmeta(
              a1,
              a2,
              a3,
              a4,
              v208,
              v209,
              v72,
              v215[2],
              v73,
              v74,
              v75,
              v76,
              v77,
              v78,
              v79,
              v80,
              v215[3],
              (_QWORD *)v18,
              &v212,
              (__int64)v215);
      v54 |= v81;
      sprd_log(
        7u,
        "allow_verification_error:%d, subret:%d, ret:%d\n",
        v82,
        v83,
        v84,
        v85,
        v86,
        v87,
        v88,
        v89,
        a4,
        v81,
        v54,
        0);
      if ( v215[1] != 0 )
        free(v215[1]);
      if ( v215[2] != 0 )
        free(v215[2]);
      if ( v54 != 0 && a4 == 0 )
      {
LABEL_8:
        sprd_log(7u, "allow_verification_error:%d, ret:%d\n", v55, v56, v57, v58, v59, v60, v61, v62, 0, v54, 0);
      }
      else
      {
        v210 = 0;
        sprd_log(
          7u,
          "in %s, l:%d. load_and_verify_vbmeta ret is %d, algorithm_type: %d. \n",
          v55,
          v56,
          v57,
          v58,
          v59,
          v60,
          v61,
          v62,
          "avb_slot_verify",
          1088,
          v54,
          v212,
          0);
        if ( (unsigned int)strcmp(**(_QWORD **)(v18 + 8), (__int64)"vbmeta") != 0 )
        {
          v210 = 1;
          if ( (unsigned int)strcmp(**(_QWORD **)(v18 + 8), (__int64)"boot") != 0 )
            sprd_log(
              0,
              "assert fail: avb_strcmp(slot_data->vbmeta_images[0].partition_name, \"boot\") == 0\n",
              v90,
              v91,
              v92,
              v93,
              v94,
              v95,
              v96,
              v97);
        }
        sprd_log(
          7u,
          "in %s, l:%d, %s, %d, %d\n",
          v90,
          v91,
          v92,
          v93,
          v94,
          v95,
          v96,
          v97,
          "avb_slot_verify",
          1097,
          **(_QWORD **)(v18 + 8),
          *(_QWORD *)(v18 + 16),
          *(_QWORD *)(v18 + 32),
          0);
        if ( v54 != 0 && v54 - 3 > 2 )
        {
LABEL_21:
          sprd_log(7u, "in %s, l:%d. \n", v98, v99, v100, v101, v102, v103, v104, v105, "avb_slot_verify", 1234, 0);
          return v54;
        }
        v106 = avb_strdup(a3);
        *(_QWORD *)v18 = v106;
        if ( v106 != 0 )
        {
          v205 = (__int64 *)(v18 + 40);
          sprd_log(
            7u,
            "in %s, l:%d. \n",
            v107,
            v108,
            v109,
            v110,
            v111,
            v112,
            v113,
            v114,
            "avb_slot_verify",
            1109,
            0);
          if ( (unsigned int)avb_cmdline_append(
                               (__int64 *)(v18 + 40),
                               (__int64)"androidboot.vbmeta.device",
                               (__int64)"PARTUUID=$(ANDROID_VBMETA_PARTUUID)") != 0 )
          {
            sprd_log(
              7u,
              "in %s, l:%d. \n",
              v115,
              v116,
              v117,
              v118,
              v119,
              v120,
              v121,
              v122,
              "avb_slot_verify",
              1118,
              0);
            v206 = uint_to_str(1u, (__int64)v216);
            v203 = uint_to_str(0, (__int64)v217);
            memcpy(v218, v216, v206);
            *((_BYTE *)v218 + v206) = 46;
            memcpy((char *)v218 + v206 + 1, v217, v203);
            *((_BYTE *)v218 + v206 + v203 + 1) = 0;
            v123 = avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.avb_version", (__int64)v218);
            v132 = "in %s, l:%d. \n";
            v133 = "avb_slot_verify";
            if ( v123 != 0 )
            {
              v202 = *(_QWORD *)(v18 + 40);
              if ( v202 != 0 )
              {
                v213[0] = "system";
                v213[1] = "boot";
                v214 = "vbmeta";
                v216[0] = "$(ANDROID_SYSTEM_PARTUUID)";
                v216[1] = "$(ANDROID_BOOT_PARTUUID)";
                v216[2] = "$(ANDROID_VBMETA_PARTUUID)";
                if ( v210 != 0 )
                  v214 = "boot";
                v211 = 0;
                v134 = 0;
                while ( 1 )
                {
                  v204 = v213[v211];
                  v207 = strlen(v204);
                  v135 = strlen(a3);
                  if ( (unsigned int)concat_partition_name_suffix(v217, 32, v204, v207, a3, v135) == 0 )
                  {
                    sprd_log(
                      0,
                      "Partition name and suffix does not fit.\n",
                      v136,
                      v137,
                      v138,
                      v139,
                      v140,
                      v141,
                      v142,
                      v143);
                    goto LABEL_71;
                  }
                  v144 = (*(__int64 (__fastcall **)(__int64, _BYTE *, unsigned int *, __int64))(a1 + 72))(
                           a1,
                           v217,
                           v218,
                           37);
                  if ( v144 == 1 )
                    goto LABEL_73;
                  if ( v144 != 0 )
                    break;
                  v153 = v216[v211];
                  if ( v134 != 0 )
                  {
                    v154 = avb_str_replace(v134, v153, v218);
                    v155 = v134;
                    v134 = v154;
                    free(v155);
                  }
                  else
                  {
                    v134 = avb_str_replace(v202, v153, v218);
                  }
                  if ( v134 == 0 )
                    goto LABEL_73;
                  if ( ++v211 == 3 )
                  {
                    free(*(_QWORD *)(v18 + 40));
                    *(_QWORD *)(v18 + 40) = v134;
                    goto LABEL_40;
                  }
                }
                sprd_log(
                  0,
                  "Error getting unique GUID for partition.\n",
                  v145,
                  v146,
                  v147,
                  v148,
                  v149,
                  v150,
                  v151,
                  v152);
LABEL_71:
                if ( v134 != 0 )
                  free(v134);
LABEL_73:
                v54 = 1;
                sprd_log(
                  7u,
                  "in %s, l:%d. \n",
                  v145,
                  v146,
                  v147,
                  v148,
                  v149,
                  v150,
                  v151,
                  v152,
                  "avb_slot_verify",
                  1136,
                  0);
                goto LABEL_9;
              }
LABEL_40:
              sprd_log(
                7u,
                "in %s, l:%d. \n",
                v124,
                v125,
                v126,
                v127,
                v128,
                v129,
                v130,
                v131,
                "avb_slot_verify",
                1142,
                0,
                v133,
                v132);
              v156 = (*(__int64 (__fastcall **)(__int64, _QWORD *))(a1 + 64))(a1, v216);
              if ( v156 != 1 )
              {
                if ( v156 != 0 )
                {
                  v54 = 2;
                  sprd_log(0, "Error getting device state.\n", v157, v158, v159, v160, v161, v162, v163, v164);
                  goto LABEL_9;
                }
                if ( LODWORD(v216[0]) != 0 )
                  v165 = "unlocked";
                else
                  v165 = "locked";
                if ( (unsigned int)avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.device_state", (__int64)v165) != 0 )
                {
                  sprd_log(
                    7u,
                    "in %s, l:%d. \n",
                    v166,
                    v167,
                    v168,
                    v169,
                    v170,
                    v171,
                    v172,
                    v173,
                    "avb_slot_verify",
                    1160,
                    0);
                  switch ( v212 )
                  {
                    case 0u:
                    case 1u:
                    case 2u:
                    case 3u:
                      sha256_init(v218);
                      if ( *(_QWORD *)(v18 + 16) != 0 )
                      {
                        v187 = *(_QWORD *)(v18 + 8);
                        v188 = 0;
                        v189 = 0;
                        do
                        {
                          v190 = 32 * v189;
                          v191 = v187 + 32 * v189++;
                          sha256_update(v218, *(_QWORD *)(v191 + 8), *(_DWORD *)(v191 + 16));
                          v187 = *(_QWORD *)(v18 + 8);
                          v188 += *(_QWORD *)(v187 + v190 + 16);
                        }
                        while ( *(_QWORD *)(v18 + 16) > v189 );
                      }
                      else
                      {
                        v188 = 0;
                      }
                      if ( (unsigned int)avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.hash_alg", (__int64)"sha256") != 0 )
                      {
                        uint_to_str(v188, (__int64)v217);
                        if ( (unsigned int)avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.size", (__int64)v217) != 0 )
                        {
                          v200 = sha256_final((__int64)v218);
                          if ( (unsigned int)avb_cmdline_append_hash(v18, v200, 32) != 0 )
                            goto LABEL_61;
                        }
                      }
                      v54 = 1;
                      sprd_log(
                        7u,
                        "in %s, l:%d. \n",
                        v174,
                        v175,
                        v176,
                        v177,
                        v178,
                        v179,
                        v180,
                        v181,
                        "avb_slot_verify",
                        1188,
                        0);
                      goto LABEL_9;
                    case 4u:
                    case 5u:
                    case 6u:
                      sha512_init((__int64)v218);
                      if ( *(_QWORD *)(v18 + 16) != 0 )
                      {
                        v182 = *(_QWORD *)(v18 + 8);
                        v183 = 0;
                        v184 = 0;
                        do
                        {
                          v185 = 32 * v184;
                          v186 = v182 + 32 * v184++;
                          sha512_update((__int64)v218, *(_QWORD *)(v186 + 8), *(_DWORD *)(v186 + 16));
                          v182 = *(_QWORD *)(v18 + 8);
                          v183 += *(_QWORD *)(v182 + v185 + 16);
                        }
                        while ( *(_QWORD *)(v18 + 16) > v184 );
                      }
                      else
                      {
                        v183 = 0;
                      }
                      if ( (unsigned int)avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.hash_alg", (__int64)"sha512") != 0 )
                      {
                        uint_to_str(v183, (__int64)v217);
                        if ( (unsigned int)avb_cmdline_append(v205, (__int64)"androidboot.vbmeta.size", (__int64)v217) != 0 )
                        {
                          v201 = sha512_final((__int64)v218);
                          if ( (unsigned int)avb_cmdline_append_hash(v18, v201, 64) != 0 )
                            goto LABEL_61;
                        }
                      }
                      v54 = 1;
                      sprd_log(
                        7u,
                        "in %s, l:%d. \n",
                        v174,
                        v175,
                        v176,
                        v177,
                        v178,
                        v179,
                        v180,
                        v181,
                        "avb_slot_verify",
                        1214,
                        0);
                      goto LABEL_9;
                    case 7u:
                      sprd_log(0, (const char *)&loc_940568B0, v174, v175, v176, v177, v178, v179, v180, v181);
                      goto LABEL_61;
                    default:
LABEL_61:
                      sprd_log(
                        7u,
                        "in %s, l:%d. \n",
                        v174,
                        v175,
                        v176,
                        v177,
                        v178,
                        v179,
                        v180,
                        v181,
                        "avb_slot_verify",
                        1222,
                        0);
                      if ( a5 != nullptr )
                      {
                        *a5 = v18;
                        sprd_log(
                          7u,
                          "in %s, l:%d. \n",
                          v192,
                          v193,
                          v194,
                          v195,
                          v196,
                          v197,
                          v198,
                          v199,
                          "avb_slot_verify",
                          1225,
                          0);
                      }
                      else
                      {
                        avb_slot_data_free((__int64 *)v18);
                      }
                      goto LABEL_21;
                  }
                }
              }
              v54 = 1;
            }
            else
            {
              v54 = 1;
              sprd_log(
                7u,
                "in %s, l:%d. \n",
                v124,
                v125,
                v126,
                v127,
                v128,
                v129,
                v130,
                v131,
                "avb_slot_verify",
                1125,
                0);
            }
          }
          else
          {
            v54 = 1;
            sprd_log(
              7u,
              "in %s, l:%d. \n",
              v115,
              v116,
              v117,
              v118,
              v119,
              v120,
              v121,
              v122,
              "avb_slot_verify",
              1115,
              0);
          }
        }
        else
        {
          v54 = 1;
          sprd_log(
            7u,
            "in %s, l:%d. \n",
            v107,
            v108,
            v109,
            v110,
            v111,
            v112,
            v113,
            v114,
            "avb_slot_verify",
            1106,
            0);
        }
      }
    }
    else
    {
      v54 = 1;
      sprd_log(7u, "in %s, l:%d. \n", v37, v38, v39, v40, v41, v42, v43, v44, "avb_slot_verify", 1038, 0);
    }
  }
  else
  {
    v54 = 1;
    sprd_log(7u, "in %s, l:%d. \n", v28, v29, v30, v31, v32, v33, v34, v35, "avb_slot_verify", 1031, 0);
  }
LABEL_9:
  avb_slot_data_free((__int64 *)v18);
LABEL_10:
  sprd_log(7u, "in %s, l:%d. \n", v63, v64, v65, v66, v67, v68, v69, v70, "avb_slot_verify", 1241, 0);
  return v54;
}

/* ===== avb_slot_verify_result_to_string @ 0x94046314 size 200 ===== */
const char *__fastcall avb_slot_verify_result_to_string(
        int a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  const char *result; // x0

  switch ( a1 )
  {
    case 0:
      result = "OK";
      break;
    case 1:
      result = "ERROR_OOM";
      break;
    case 2:
      result = "ERROR_IO";
      break;
    case 3:
      result = "ERROR_VERIFICATION";
      break;
    case 4:
      result = "ERROR_ROLLBACK_INDEX";
      break;
    case 5:
      result = "ERROR_PUBLIC_KEY_REJECTED";
      break;
    case 6:
      result = "ERROR_INVALID_METADATA";
      break;
    case 7:
      result = "ERROR_UNSUPPORTED_VERSION";
      break;
    default:
      sprd_log(0, "Unknown AvbSlotVerifyResult value.\n", a2, a3, a4, a5, a6, a7, a8, a9);
      result = "(unknown)";
      break;
  }
  return result;
}

/* ===== memcmp @ 0x940463DC size 4 ===== */
// attributes: thunk
__int64 __fastcall memcmp(__int64 a1, __int64 a2, unsigned int a3)
{
  return memcmp(a1, a2, a3);
}

/* ===== memcpy @ 0x940463E0 size 24 ===== */
__int64 __fastcall memcpy(__int64 a1, __int64 a2, unsigned int a3)
{
  memcpy(a1, a2, a3);
  return 0;
}

/* ===== memset @ 0x940463F8 size 24 ===== */
__int64 __fastcall memset(__int64 a1, unsigned __int8 a2, unsigned int a3)
{
  memset(a1, a2, a3);
  return 0;
}

/* ===== strcmp @ 0x94046410 size 4 ===== */
// attributes: thunk
__int64 __fastcall strcmp(__int64 a1, __int64 a2)
{
  return strcmp(a1, a2);
}

/* ===== strlen @ 0x94046414 size 24 ===== */
__int64 __fastcall strlen(__int64 a1)
{
  return (unsigned int)strlen(a1);
}

/* ===== malloc @ 0x9404642C size 4 ===== */
// attributes: thunk
__int64 __fastcall malloc(unsigned int a1)
{
  return malloc(a1);
}

/* ===== free @ 0x94046430 size 4 ===== */
// attributes: thunk
__int64 __fastcall free(__int64 a1)
{
  return free(a1);
}

/* ===== be32_to_cpu @ 0x94046434 size 36 ===== */
__int64 __fastcall be32_to_cpu(unsigned int a1)
{
  return (BYTE1(a1) << 16) | (a1 << 24) | HIBYTE(a1) | (BYTE2(a1) << 8);
}

/* ===== be64_to_cpu @ 0x94046458 size 68 ===== */
unsigned __int64 __fastcall be64_to_cpu(unsigned __int64 a1)
{
  return ((unsigned __int64)BYTE1(a1) << 48)
       | (a1 << 56)
       | HIBYTE(a1)
       | ((unsigned __int64)BYTE2(a1) << 40)
       | ((unsigned __int64)BYTE3(a1) << 32)
       | ((unsigned __int64)BYTE4(a1) << 24)
       | ((unsigned __int64)BYTE5(a1) << 16)
       | ((unsigned __int64)BYTE6(a1) << 8);
}

/* ===== memcmp_neq @ 0x9404649C size 64 ===== */
__int64 __fastcall memcmp_neq(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned int v3; // w3
  __int64 v4; // x4
  int v5; // w5
  char v6; // w6
  char v7; // w3

  v3 = 0;
  if ( a3 != 0 )
  {
    v4 = 0;
    v5 = 0;
    do
    {
      v6 = *(_BYTE *)(a2 + v4);
      v7 = *(_BYTE *)(a1 + v4++);
      v5 |= (unsigned __int8)(v6 ^ v7);
    }
    while ( v4 != a3 );
    return v5 != 0;
  }
  return v3;
}

/* ===== add_overflow @ 0x940464DC size 100 ===== */
__int64 __fastcall add_overflow(
        unsigned __int64 *a1,
        __int64 a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  unsigned __int64 v12; // x2
  __int64 result; // x0
  unsigned __int64 v14; // x1

  if ( a1 == nullptr )
    sprd_log(0, "assert fail: value != NULL\n", a3, a4, a5, a6, a7, a8, a9, a10);
  v12 = *a1;
  result = 1;
  v14 = *a1 + a2;
  *a1 = v14;
  if ( v12 > v14 )
  {
    sprd_log(0, "Overflow when adding values.\n", a3, a4, a5, a6, a7, a8, a9, a10);
    return 0;
  }
  return result;
}

/* ===== add_overflow_set @ 0x94046540 size 48 ===== */
__int64 __fastcall add_overflow_set(
        unsigned __int64 *a1,
        unsigned __int64 a2,
        __int64 a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  unsigned __int64 *v11; // x3
  char v13; // [xsp+18h] [xbp+18h] BYREF

  v11 = a1;
  if ( a1 == nullptr )
    v11 = (unsigned __int64 *)&v13;
  *v11 = a2;
  return add_overflow(v11, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

/* ===== is_valid_utf8 @ 0x94046570 size 152 ===== */
__int64 __fastcall is_valid_utf8(char *a1, __int64 a2)
{
  int v2; // w3
  char *v3; // x1
  char v4; // w2

  if ( a2 != 0 )
  {
    v2 = 0;
    v3 = &a1[a2];
    while ( 1 )
    {
      while ( 1 )
      {
        v4 = *a1;
        if ( v2 != 0 )
        {
          if ( (v4 & 0xC0) != 0x80 )
            return 0;
          --v2;
          goto LABEL_5;
        }
        if ( *a1 < 0 )
          break;
LABEL_5:
        if ( ++a1 == v3 )
          return v2 == 0;
      }
      if ( (v4 & 0xE0) == 0xC0 )
      {
        v2 = 1;
        goto LABEL_5;
      }
      if ( (v4 & 0xF0) == 0xE0 )
      {
        v2 = 2;
        goto LABEL_5;
      }
      if ( (v4 & 0xF8) != 0xF0 )
        return 0;
      ++a1;
      v2 = 3;
      if ( a1 == v3 )
        return v2 == 0;
    }
  }
  return 1;
}

/* ===== concat_partition_name_suffix @ 0x94046608 size 248 ===== */
__int64 __fastcall concat_partition_name_suffix(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        unsigned __int64 a4,
        __int64 a5,
        __int64 a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13,
        double a14)
{
  unsigned int v19; // w22
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  unsigned __int64 v29; // [xsp+58h] [xbp+58h] BYREF

  v19 = a6;
  if ( (unsigned int)add_overflow_set(&v29, a4, a6, a7, a8, a9, a10, a11, a12, a13, a14) != 0 )
  {
    if ( a2 - 1 < v29 )
    {
      sprd_log(0, "Insufficient buffer space.\n", v20, v21, v22, v23, v24, v25, v26, v27);
      return 0;
    }
    else
    {
      memcpy(a1, a3, a4);
      memcpy(a1 + a4, a5, v19);
      *(_BYTE *)(a1 + v29) = 0;
      return 1;
    }
  }
  else
  {
    sprd_log(0, "Overflow when adding string sizes.\n", v20, v21, v22, v23, v24, v25, v26, v27);
    return 0;
  }
}

/* ===== avb_malloc @ 0x94046700 size 72 ===== */
__int64 __fastcall avb_malloc(__int64 a1)
{
  __int64 v2; // x19
  double v3; // d0
  double v4; // d1
  double v5; // d2
  double v6; // d3
  double v7; // d4
  double v8; // d5
  double v9; // d6
  double v10; // d7

  v2 = malloc(a1);
  if ( v2 == 0 )
    sprd_log(7u, "Failed to allocate memory. size:%d\n", v3, v4, v5, v6, v7, v8, v9, v10, a1, 0);
  return v2;
}

/* ===== avb_calloc @ 0x94046748 size 56 ===== */
__int64 __fastcall avb_calloc(__int64 a1)
{
  __int64 v1; // x0
  __int64 v2; // x19
  unsigned int v4; // [xsp+28h] [xbp+28h]

  v4 = a1;
  v1 = avb_malloc(a1);
  v2 = v1;
  if ( v1 != 0 )
    memset(v1, 0, v4);
  return v2;
}

/* ===== avb_strdup @ 0x94046780 size 72 ===== */
__int64 __fastcall avb_strdup(__int64 a1)
{
  __int64 v1; // x20
  __int64 v2; // x0
  __int64 v3; // x19

  v1 = strlen(a1);
  v2 = avb_malloc(v1 + 1);
  v3 = v2;
  if ( v2 != 0 )
  {
    memcpy(v2, a1, v1);
    *(_BYTE *)(v3 + v1) = 0;
  }
  return v3;
}

/* ===== avb_strstr @ 0x940467C8 size 132 ===== */
_BYTE *__fastcall avb_strstr(_BYTE *result, unsigned __int8 *a2)
{
  int v2; // w8
  _BYTE *v3; // x4
  unsigned __int8 *v4; // x7
  int i; // w6
  __int64 v6; // x2

  if ( *result != 0 )
  {
    v2 = *a2;
    v3 = result;
    v4 = result + 1;
    if ( v2 == (unsigned __int8)*result )
      goto LABEL_6;
LABEL_3:
    for ( i = *v4; i != 0; i = *v4 )
    {
LABEL_5:
      ++v3;
      ++v4;
      result = v3;
      if ( v2 != i )
        goto LABEL_3;
LABEL_6:
      i = a2[1];
      if ( a2[1] == 0 )
        return result;
      if ( i == *v4 )
      {
        v6 = 1;
        while ( 1 )
        {
          if ( a2[++v6] == 0 )
            return result;
          if ( (unsigned __int8)v3[v6] != a2[v6] )
            goto LABEL_5;
        }
      }
    }
  }
  return nullptr;
}

/* ===== avb_str_in_list @ 0x9404684C size 120 ===== */
__int64 __fastcall avb_str_in_list(__int64 *a1, __int64 a2, __int64 a3)
{
  __int64 *v3; // x19
  __int64 v4; // x0
  __int64 v7; // t1

  v3 = a1;
  v4 = *a1;
  if ( v4 == 0 )
    return 0;
  while ( strlen(v4) != a3 || (unsigned int)memcmp(*v3, a2, a3) != 0 )
  {
    v7 = v3[1];
    ++v3;
    v4 = v7;
    if ( v7 == 0 )
      return 0;
  }
  return *v3;
}

/* ===== avb_str_replace @ 0x940468C4 size 416 ===== */
__int64 __fastcall avb_str_replace(_BYTE *a1, unsigned __int8 *a2, __int64 a3)
{
  __int64 v4; // x26
  __int64 v5; // x25
  __int64 v6; // x23
  __int64 v7; // x20
  __int64 v8; // x21
  __int64 v9; // x1
  __int64 v10; // x0
  __int64 v11; // x0
  _BYTE *v12; // x0
  __int64 v13; // x27
  _BYTE *v14; // x19
  __int64 v15; // x28
  __int64 v16; // x24
  __int64 v17; // x0
  __int64 v18; // x0
  __int64 v19; // x21
  unsigned int v20; // w24
  __int64 v21; // x19

  v4 = strlen((__int64)a2);
  v5 = strlen(a3);
  if ( *a1 == 0 )
    return avb_strdup((__int64)a1);
  v6 = 0;
  v7 = 0;
  while ( 1 )
  {
    v12 = avb_strstr(a1, a2);
    v13 = v12 - a1;
    v14 = v12;
    v15 = v12 - a1 + v6;
    if ( v12 == nullptr )
      break;
    v16 = v15 + v5;
    if ( v7 != 0 )
    {
      v8 = avb_malloc(v16 + 1);
      memcpy(v8, v7, v6);
      v9 = (__int64)a1;
      v10 = v8 + v6;
      v6 = v15 + v5;
      a1 = &v14[v4];
      memcpy(v10, v9, v13);
      memcpy(v8 + v15, a3, v5);
      *(_BYTE *)(v8 + v16) = 0;
      v11 = v7;
      v7 = v8;
      free(v11);
      if ( v14[v4] == 0 )
        break;
    }
    else
    {
      v6 = v13 + v5;
      v17 = avb_malloc(v13 + v5 + 1);
      v7 = v17;
      if ( v17 == 0 )
        return 0;
      memcpy(v17, (__int64)a1, v13);
      a1 = &v14[v4];
      memcpy(v7 + v13, a3, v5);
      *(_BYTE *)(v7 + v6) = 0;
      if ( v14[v4] == 0 )
        break;
    }
  }
  if ( v7 == 0 )
    return avb_strdup((__int64)a1);
  v18 = strlen((__int64)a1);
  v19 = v18 + v6;
  v20 = v18;
  v21 = avb_malloc(v18 + v6 + 1);
  memcpy(v21, v7, v6);
  memcpy(v21 + v6, (__int64)a1, v20);
  *(_BYTE *)(v21 + v19) = 0;
  free(v7);
  return v21;
}

/* ===== avb_vbmeta_header_parse @ 0x94046A64 size 248 ===== */
__int64 __fastcall avb_vbmeta_header_parse(__int64 a1, __int64 a2)
{
  __int64 result; // x0

  memcpy(a2, a1, 0x100u);
  *(_DWORD *)(a2 + 4) = be32_to_cpu(*(_DWORD *)(a2 + 4));
  *(_DWORD *)(a2 + 8) = be32_to_cpu(*(_DWORD *)(a2 + 8));
  *(_QWORD *)(a2 + 12) = be64_to_cpu(*(_QWORD *)(a2 + 12));
  *(_QWORD *)(a2 + 20) = be64_to_cpu(*(_QWORD *)(a2 + 20));
  *(_DWORD *)(a2 + 28) = be32_to_cpu(*(_DWORD *)(a2 + 28));
  *(_QWORD *)(a2 + 32) = be64_to_cpu(*(_QWORD *)(a2 + 32));
  *(_QWORD *)(a2 + 40) = be64_to_cpu(*(_QWORD *)(a2 + 40));
  *(_QWORD *)(a2 + 48) = be64_to_cpu(*(_QWORD *)(a2 + 48));
  *(_QWORD *)(a2 + 56) = be64_to_cpu(*(_QWORD *)(a2 + 56));
  *(_QWORD *)(a2 + 64) = be64_to_cpu(*(_QWORD *)(a2 + 64));
  *(_QWORD *)(a2 + 72) = be64_to_cpu(*(_QWORD *)(a2 + 72));
  *(_QWORD *)(a2 + 80) = be64_to_cpu(*(_QWORD *)(a2 + 80));
  *(_QWORD *)(a2 + 88) = be64_to_cpu(*(_QWORD *)(a2 + 88));
  *(_QWORD *)(a2 + 96) = be64_to_cpu(*(_QWORD *)(a2 + 96));
  *(_QWORD *)(a2 + 104) = be64_to_cpu(*(_QWORD *)(a2 + 104));
  *(_QWORD *)(a2 + 112) = be64_to_cpu(*(_QWORD *)(a2 + 112));
  result = be32_to_cpu(*(_DWORD *)(a2 + 120));
  *(_DWORD *)(a2 + 120) = result;
  return result;
}

/* ===== avb_vbmeta_verify @ 0x94046B5C size 1268 ===== */
__int64 __fastcall avb_vbmeta_verify(unsigned __int64 a1, unsigned __int64 a2, _QWORD *a3, _QWORD *a4, _QWORD *a5)
{
  __int64 v10; // x21
  unsigned int *v11; // x19
  __int64 v12; // x0
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x20
  double v22; // d0
  double v23; // d1
  double v24; // d2
  double v25; // d3
  double v26; // d4
  double v27; // d5
  double v28; // d6
  double v29; // d7
  unsigned int v30; // w24
  double v32; // d0
  double v33; // d1
  double v34; // d2
  double v35; // d3
  double v36; // d4
  double v37; // d5
  double v38; // d6
  double v39; // d7
  __int64 v40; // x1
  double v41; // d0
  double v42; // d1
  double v43; // d2
  double v44; // d3
  double v45; // d4
  double v46; // d5
  double v47; // d6
  double v48; // d7
  double v49; // d0
  double v50; // d1
  double v51; // d2
  double v52; // d3
  double v53; // d4
  double v54; // d5
  double v55; // d6
  double v56; // d7
  double v57; // d0
  double v58; // d1
  double v59; // d2
  double v60; // d3
  double v61; // d4
  double v62; // d5
  double v63; // d6
  double v64; // d7
  double v65; // d0
  double v66; // d1
  double v67; // d2
  double v68; // d3
  double v69; // d4
  double v70; // d5
  double v71; // d6
  double v72; // d7
  double v73; // d0
  double v74; // d1
  double v75; // d2
  double v76; // d3
  double v77; // d4
  double v78; // d5
  double v79; // d6
  double v80; // d7
  __int64 v81; // x2
  unsigned int v82; // w0
  __int64 *v83; // x0
  double v84; // d0
  double v85; // d1
  double v86; // d2
  double v87; // d3
  double v88; // d4
  double v89; // d5
  double v90; // d6
  double v91; // d7
  __int64 *v92; // x28
  double v93; // d0
  double v94; // d1
  double v95; // d2
  double v96; // d3
  double v97; // d4
  double v98; // d5
  double v99; // d6
  double v100; // d7
  __int64 v101; // x27
  __int64 v102; // x0
  double v103; // d0
  double v104; // d1
  double v105; // d2
  double v106; // d3
  double v107; // d4
  double v108; // d5
  double v109; // d6
  double v110; // d7
  __int64 v111; // x1
  unsigned __int64 v112; // [xsp+68h] [xbp+68h]
  unsigned __int64 v113; // [xsp+78h] [xbp+78h] BYREF
  unsigned __int64 v114; // [xsp+80h] [xbp+80h] BYREF
  unsigned __int64 v115; // [xsp+88h] [xbp+88h] BYREF
  unsigned __int64 v116; // [xsp+90h] [xbp+90h] BYREF
  unsigned __int64 v117; // [xsp+98h] [xbp+98h] BYREF

  if ( a3 != nullptr )
    *a3 = 0;
  if ( a4 != nullptr )
    *a4 = 0;
  v10 = avb_malloc(256);
  v11 = (unsigned int *)avb_malloc(200);
  v12 = avb_malloc(392);
  v21 = v12;
  if ( v11 != nullptr && v10 != 0 )
  {
    if ( v12 != 0 )
    {
      if ( (unsigned int)memcmp_neq(a1, (__int64)"AVB0", 4) != 0 )
      {
        v30 = 2;
        sprd_log(0, "Magic is incorrect.\n", v22, v23, v24, v25, v26, v27, v28, v29);
      }
      else
      {
        if ( a2 <= 0xFF )
        {
          v30 = 2;
          sprd_log(0, "Length is smaller than header.\n", v22, v23, v24, v25, v26, v27, v28, v29);
          free(v10);
          goto LABEL_11;
        }
        avb_vbmeta_header_parse(a1, v10);
        if ( *(_DWORD *)(v10 + 4) != 1 || *(_DWORD *)(v10 + 8) != 0 )
        {
          v30 = 3;
          sprd_log(
            0,
            "Mismatch between image version and libavb version.\n",
            v32,
            v33,
            v34,
            v35,
            v36,
            v37,
            v38,
            v39);
        }
        else if ( *(_BYTE *)(v10 + 175) != 0 )
        {
          v30 = 2;
          sprd_log(0, "Release string does not end with a NUL byte.\n", v32, v33, v34, v35, v36, v37, v38, v39);
        }
        else
        {
          v40 = *(_QWORD *)(v10 + 12);
          if ( (v40 & 0x3F) != 0 || (*(_QWORD *)(v10 + 20) & 0x3FLL) != 0 )
          {
            v30 = 2;
            sprd_log(0, "Block size is not a multiple of 64.\n", v32, v33, v34, v35, v36, v37, v38, v39);
          }
          else
          {
            v113 = 256;
            if ( (unsigned int)add_overflow(&v113, v40, v32, v33, v34, v35, v36, v37, v38, v39) != 0
              && (unsigned int)add_overflow(&v113, *(_QWORD *)(v10 + 20), v41, v42, v43, v44, v45, v46, v47, v48) != 0 )
            {
              if ( a2 >= v113 )
              {
                if ( (unsigned int)add_overflow_set(nullptr, a1, a2, v41, v42, v43, v44, v45, v46, v47, v48) != 0 )
                {
                  if ( (unsigned int)add_overflow_set(
                                       &v114,
                                       *(_QWORD *)(v10 + 32),
                                       *(_QWORD *)(v10 + 40),
                                       v49,
                                       v50,
                                       v51,
                                       v52,
                                       v53,
                                       v54,
                                       v55,
                                       v56) != 0
                    && *(_QWORD *)(v10 + 12) >= v114 )
                  {
                    if ( (unsigned int)add_overflow_set(
                                         &v115,
                                         *(_QWORD *)(v10 + 48),
                                         *(_QWORD *)(v10 + 56),
                                         v57,
                                         v58,
                                         v59,
                                         v60,
                                         v61,
                                         v62,
                                         v63,
                                         v64) != 0
                      && *(_QWORD *)(v10 + 12) >= v115 )
                    {
                      if ( (unsigned int)add_overflow_set(
                                           &v116,
                                           *(_QWORD *)(v10 + 64),
                                           *(_QWORD *)(v10 + 72),
                                           v65,
                                           v66,
                                           v67,
                                           v68,
                                           v69,
                                           v70,
                                           v71,
                                           v72) != 0
                        && *(_QWORD *)(v10 + 20) >= v116 )
                      {
                        v81 = *(_QWORD *)(v10 + 88);
                        if ( v81 == 0
                          || (unsigned int)add_overflow_set(
                                             &v117,
                                             *(_QWORD *)(v10 + 80),
                                             v81,
                                             v73,
                                             v74,
                                             v75,
                                             v76,
                                             v77,
                                             v78,
                                             v79,
                                             v80) != 0
                          && *(_QWORD *)(v10 + 20) >= v117 )
                        {
                          v82 = *(_DWORD *)(v10 + 28);
                          v30 = 1;
                          if ( v82 != 0 )
                          {
                            v83 = avb_get_algorithm(v82);
                            v92 = v83;
                            if ( v83 != nullptr )
                            {
                              if ( *(_QWORD *)(v10 + 40) == v83[2] )
                              {
                                v112 = a1 + 256;
                                v101 = a1 + 256 + *(_QWORD *)(v10 + 12);
                                switch ( *(_DWORD *)(v10 + 28) )
                                {
                                  case 1:
                                  case 2:
                                  case 3:
                                    sha256_init(v11);
                                    sha256_update(v11, a1, 0x100u);
                                    sha256_update(v11, v101, *(_DWORD *)(v10 + 20));
                                    v102 = sha256_final((__int64)v11);
                                    goto LABEL_56;
                                  case 4:
                                  case 5:
                                  case 6:
                                    sha512_init(v21);
                                    sha512_update(v21, a1, 0x100u);
                                    sha512_update(v21, v101, *(_DWORD *)(v10 + 20));
                                    v102 = sha512_final(v21);
LABEL_56:
                                    if ( (unsigned int)memcmp_neq(
                                                         v112 + *(_QWORD *)(v10 + 32),
                                                         v102,
                                                         *(_QWORD *)(v10 + 40)) != 0 )
                                    {
                                      v30 = 4;
                                      sprd_log(
                                        0,
                                        "Hash does not match!\n",
                                        v103,
                                        v104,
                                        v105,
                                        v106,
                                        v107,
                                        v108,
                                        v109,
                                        v110);
                                    }
                                    else
                                    {
                                      v30 = 5;
                                      if ( (unsigned int)avb_rsa_verify_sw(
                                                           v101 + *(_QWORD *)(v10 + 64),
                                                           *(_QWORD *)(v10 + 72),
                                                           v112 + *(_QWORD *)(v10 + 48),
                                                           *(_QWORD *)(v10 + 56),
                                                           v112 + *(_QWORD *)(v10 + 32),
                                                           *(_QWORD *)(v10 + 40),
                                                           *v92,
                                                           v92[1],
                                                           v103,
                                                           v104,
                                                           v105,
                                                           v106,
                                                           v107,
                                                           v108,
                                                           v109,
                                                           v110) != 0 )
                                      {
                                        v111 = *(_QWORD *)(v10 + 72);
                                        if ( v111 != 0 )
                                        {
                                          if ( a3 != nullptr )
                                            *a3 = v101 + *(_QWORD *)(v10 + 64);
                                          if ( a4 != nullptr )
                                            *a4 = v111;
                                        }
                                        v30 = 0;
                                        if ( a5 != nullptr )
                                          *a5 = *(_QWORD *)(v10 + 112);
                                      }
                                    }
                                    break;
                                  default:
                                    v30 = 2;
                                    sprd_log(0, "Unknown algorithm.\n", v84, v85, v86, v87, v88, v89, v90, v91);
                                    break;
                                }
                              }
                              else
                              {
                                v30 = 2;
                                sprd_log(
                                  0,
                                  "Embedded hash has wrong size.\n",
                                  v84,
                                  v85,
                                  v86,
                                  v87,
                                  v88,
                                  v89,
                                  v90,
                                  v91);
                              }
                            }
                            else
                            {
                              v30 = 2;
                              sprd_log(0, "Invalid or unknown algorithm.\n", v84, v85, v86, v87, v88, v89, v90, v91);
                            }
                          }
                        }
                        else
                        {
                          v30 = 2;
                          sprd_log(0, (const char *)&loc_94056CC8, v93, v94, v95, v96, v97, v98, v99, v100);
                        }
                      }
                      else
                      {
                        v30 = 2;
                        sprd_log(0, (const char *)&loc_94056C98, v73, v74, v75, v76, v77, v78, v79, v80);
                      }
                    }
                    else
                    {
                      v30 = 2;
                      sprd_log(
                        0,
                        "Signature is not entirely in its block.\n",
                        v65,
                        v66,
                        v67,
                        v68,
                        v69,
                        v70,
                        v71,
                        v72);
                    }
                  }
                  else
                  {
                    v30 = 2;
                    sprd_log(0, "Hash is not entirely in its block.\n", v57, v58, v59, v60, v61, v62, v63, v64);
                  }
                }
                else
                {
                  v30 = 2;
                  sprd_log(0, "Boot image location and length mismatch.\n", v49, v50, v51, v52, v53, v54, v55, v56);
                }
              }
              else
              {
                v30 = 2;
                sprd_log(
                  0,
                  "Block sizes add up to more than given length.\n",
                  v41,
                  v42,
                  v43,
                  v44,
                  v45,
                  v46,
                  v47,
                  v48);
              }
            }
            else
            {
              v30 = 2;
              sprd_log(0, "Overflow while computing size of boot image.\n", v41, v42, v43, v44, v45, v46, v47, v48);
            }
          }
        }
      }
    }
    else
    {
      v30 = 2;
      sprd_log(0, "malloc failed.\n", v13, v14, v15, v16, v17, v18, v19, v20);
    }
    goto LABEL_17;
  }
  v30 = 2;
  sprd_log(0, "malloc failed.\n", v13, v14, v15, v16, v17, v18, v19, v20);
  if ( v10 != 0 )
LABEL_17:
    free(v10);
LABEL_11:
  if ( v11 != nullptr )
    free((__int64)v11);
  if ( v21 != 0 )
    free(v21);
  return v30;
}

/* ===== avb_vbmeta_verify_result_to_string @ 0x94047050 size 168 ===== */
const char *__fastcall avb_vbmeta_verify_result_to_string(
        int a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  const char *result; // x0

  switch ( a1 )
  {
    case 0:
      result = "OK";
      break;
    case 1:
      result = "OK_NOT_SIGNED";
      break;
    case 2:
      result = "INVALID_VBMETA_HEADER";
      break;
    case 3:
      result = "UNSUPPORTED_VERSION";
      break;
    case 4:
      result = "HASH_MISMATCH";
      break;
    case 5:
      result = "SIGNATURE_MISMATCH";
      break;
    default:
      sprd_log(0, "Unknown AvbVBMetaVerifyResult value.\n", a2, a3, a4, a5, a6, a7, a8, a9);
      result = "(unknown)";
      break;
  }
  return result;
}

/* ===== avb_stub_ret0 @ 0x940470F8 size 8 ===== */
__int64 avb_stub_ret0()
{
  return 0;
}

/* ===== avb_write_rollback_index @ 0x94047100 size 36 ===== */
__int64 __fastcall avb_write_rollback_index(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  sprd_log(7u, "TODO: implement write_rollback_index().\n", a1, a2, a3, a4, a5, a6, a7, a8);
  return 0;
}

/* ===== avb_read_is_device_unlocked @ 0x94047124 size 68 ===== */
__int64 __fastcall avb_read_is_device_unlocked(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        __int64 a9,
        _DWORD *a10)
{
  *a10 = MEMORY[0xFFFFFFFFE0064418] == 1;
  sprd_log(
    7u,
    "read_is_device_unlocked() get vb_unlock_status 0x%x, *out_is_unlocked is %d.\n",
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    MEMORY[0xFFFFFFFFE0064418]);
  return 0;
}

/* ===== avb_read_rollback_index @ 0x94047168 size 76 ===== */
__int64 __fastcall avb_read_rollback_index(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        __int64 a9,
        __int64 a10,
        _QWORD *a11)
{
  sprd_log(7u, (const char *)&loc_94056E88, a1, a2, a3, a4, a5, a6, a7, a8);
  if ( a11 != nullptr )
    *a11 = *(unsigned int *)(4 * a10 - 536460624);
  return 0;
}

/* ===== avb_read_from_partition @ 0x940471B4 size 408 ===== */
__int64 __fastcall avb_read_from_partition(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 *a6)
{
  double v11; // d0
  double v12; // d1
  double v13; // d2
  double v14; // d3
  double v15; // d4
  double v16; // d5
  double v17; // d6
  double v18; // d7
  unsigned __int64 v19; // x0
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  unsigned __int64 v29; // x1
  double v30; // d0
  double v31; // d1
  double v32; // d2
  double v33; // d3
  double v34; // d4
  double v35; // d5
  double v36; // d6
  double v37; // d7

  if ( (unsigned int)strcmp(a2, (__int64)"vbmeta") != 0 )
  {
    v19 = MEMORY[0xFFFFFFFFE0064404];
    if ( (a3 & 0x8000000000000000LL) == 0 )
      goto LABEL_3;
  }
  else
  {
    v19 = MEMORY[0xFFFFFFFFE0064408];
    if ( (a3 & 0x8000000000000000LL) == 0 )
      goto LABEL_3;
  }
  v29 = -a3;
  a3 += v19;
  if ( v19 < v29 )
  {
    sprd_log(7u, "Offset outside range.\n", v11, v12, v13, v14, v15, v16, v17, v18);
    return 4;
  }
LABEL_3:
  sprd_log(
    7u,
    "read partition %s, offset: 0x%llx, bytes: 0x%x.\n",
    v11,
    v12,
    v13,
    v14,
    v15,
    v16,
    v17,
    v18,
    a2,
    a3,
    a4);
  if ( (unsigned int)strcmp(a2, (__int64)"vbmeta") != 0 )
  {
    sprd_log(
      7u,
      "buf:0x%x, g_avbUserData.img_addr:0x%x, offset_from_partition:0x%llx num_bytes:0x%llx\n",
      v20,
      v21,
      v22,
      v23,
      v24,
      v25,
      v26,
      v27,
      a5,
      MEMORY[0xFFFFFFFFE00643D8],
      a3,
      a4);
    memcpy(a5, MEMORY[0xFFFFFFFFE00643D8] + a3, a4);
    *a6 = a4;
  }
  else
  {
    sprd_log(
      7u,
      "buf:0x%x, g_avbUserData.vbmeta_img_addr:0x%x, offset_from_partition:0x%llx num_bytes:0x%llx\n",
      v20,
      v21,
      v22,
      v23,
      v24,
      v25,
      v26,
      v27,
      a5,
      MEMORY[0xFFFFFFFFE00643E0],
      a3,
      a4);
    memcpy(a5, MEMORY[0xFFFFFFFFE00643E0] + a3, a4);
    *a6 = a4;
    sprd_log(7u, "[kbc] save vbmeta image for cp verify.\n", v30, v31, v32, v33, v34, v35, v36, v37);
    memcpy(-536576240, MEMORY[0xFFFFFFFFE00643E0] + a3, a4);
  }
  return 0;
}

/* ===== avb_dump_hex @ 0x9404734C size 204 ===== */
__int64 __fastcall avb_dump_hex(
        __int64 a1,
        __int64 a2,
        int a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x20
  __int64 v22; // x19
  __int64 v23; // x2
  __int64 v24; // x2
  double v25; // d0
  double v26; // d1
  double v27; // d2
  double v28; // d3
  double v29; // d4
  double v30; // d5
  double v31; // d6
  double v32; // d7

  sprd_log(7u, "%s", a4, a5, a6, a7, a8, a9, a10, a11, a1);
  if ( a3 > 0 )
  {
    v21 = (unsigned int)(a3 - 1) + 1LL;
    v22 = 0;
    do
    {
      while ( (v22 & 0xF) != 0 )
      {
        v23 = *(unsigned __int8 *)(a2 + v22++);
        sprd_log(7u, " %02x", v13, v14, v15, v16, v17, v18, v19, v20, v23);
        if ( v22 == v21 )
          return sprd_log(7u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
      }
      sprd_log(7u, "\n%04x", v13, v14, v15, v16, v17, v18, v19, v20, (unsigned int)v22);
      v24 = *(unsigned __int8 *)(a2 + v22++);
      sprd_log(7u, " %02x", v25, v26, v27, v28, v29, v30, v31, v32, v24);
    }
    while ( v22 != v21 );
  }
  return sprd_log(7u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
}

/* ===== avb_read_from_partition_kbc @ 0x94047418 size 364 ===== */
__int64 __fastcall avb_read_from_partition_kbc(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13,
        __int64 *a14)
{
  unsigned int v14; // w20
  double v19; // d0
  double v20; // d1
  double v21; // d2
  double v22; // d3
  double v23; // d4
  double v24; // d5
  double v25; // d6
  double v26; // d7
  double v27; // d0
  double v28; // d1
  double v29; // d2
  double v30; // d3
  double v31; // d4
  double v32; // d5
  double v33; // d6
  double v34; // d7
  double v35; // d0
  double v36; // d1
  double v37; // d2
  double v38; // d3
  double v39; // d4
  double v40; // d5
  double v41; // d6
  double v42; // d7
  double v43; // d0
  double v44; // d1
  double v45; // d2
  double v46; // d3
  double v47; // d4
  double v48; // d5
  double v49; // d6
  double v50; // d7
  double v52; // d0
  double v53; // d1
  double v54; // d2
  double v55; // d3
  double v56; // d4
  double v57; // d5
  double v58; // d6
  double v59; // d7

  v14 = a11;
  sprd_log(
    7u,
    "[kbc]read partition name: %s, offset = 0x%llx, num_bytes = 0x%x\n",
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a10,
    a11,
    a12);
  if ( (unsigned int)strcmp(a10, (__int64)"vbmeta") != 0 )
  {
    if ( a12 == 64 )
    {
      sprd_log(7u, "[kbc]read footer\n", v19, v20, v21, v22, v23, v24, v25, v26);
      memcpy(a13, MEMORY[0xFFFFFFFFE00643F8], 0x40u);
      avb_dump_hex((__int64)"dump footer", a13, 64, v52, v53, v54, v55, v56, v57, v58, v59);
    }
    else
    {
      sprd_log(
        7u,
        "[kbc]read certificate: img_addr = 0x%x\n",
        v19,
        v20,
        v21,
        v22,
        v23,
        v24,
        v25,
        v26,
        MEMORY[0xFFFFFFFFE00643D8]);
      if ( rtc_read() != 0 )
        v14 -= MEMORY[0xFFFFFFFFE0064414];
      sprd_log(7u, "[kbc]read certificate: offset = 0x%x\n", v27, v28, v29, v30, v31, v32, v33, v34, v14);
      memcpy(a13, MEMORY[0xFFFFFFFFE00643D8] + v14, a12);
      avb_dump_hex((__int64)kbc_read_footer_stub, a13, 16, v35, v36, v37, v38, v39, v40, v41, v42);
    }
    *a14 = a12;
  }
  else
  {
    memcpy(a13, -536576240, a12);
    *a14 = a12;
  }
  sprd_log(7u, "[kbc]read_from_partition_kbc leave buf = 0x%x\n", v43, v44, v45, v46, v47, v48, v49, v50, a13);
  return 0;
}

/* ===== avb_ops_init @ 0x94047584 size 100 ===== */
__int64 avb_ops_init()
{
  MEMORY[0xFFFFFFFFE00643A8] = -536709184;
  MEMORY[0xFFFFFFFFE0064388] = 0;
  MEMORY[0xFFFFFFFFE0064398] = -536710732;
  MEMORY[0xFFFFFFFFE00643A0] = 0;
  MEMORY[0xFFFFFFFFE00643B0] = avb_read_rollback_index;
  MEMORY[0xFFFFFFFFE00643B8] = -536710912;
  MEMORY[0xFFFFFFFFE00643C0] = -536710876;
  MEMORY[0xFFFFFFFFE00643C8] = -536710920;
  MEMORY[0xFFFFFFFFE0064380] = 0;
  return 0;
}

/* ===== avb_get_image_buffer @ 0x940475E8 size 448 ===== */
__int64 __fastcall avb_get_image_buffer(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  __int64 v8; // x19
  double v9; // d0
  double v10; // d1
  double v11; // d2
  double v12; // d3
  double v13; // d4
  double v14; // d5
  double v15; // d6
  double v16; // d7
  double v17; // d0
  double v18; // d1
  double v19; // d2
  double v20; // d3
  double v21; // d4
  double v22; // d5
  double v23; // d6
  double v24; // d7
  double v25; // d0
  double v26; // d1
  double v27; // d2
  double v28; // d3
  double v29; // d4
  double v30; // d5
  double v31; // d6
  double v32; // d7
  __int16 v33; // w0
  char *v34; // x1
  __int64 v35; // x3
  __int64 v36; // x2
  __int64 v38; // [xsp+30h] [xbp+30h] BYREF
  _QWORD v39[2]; // [xsp+38h] [xbp+38h] BYREF
  __int64 v40; // [xsp+48h] [xbp+48h] BYREF
  _QWORD v41[2]; // [xsp+50h] [xbp+50h] BYREF
  __int64 v42; // [xsp+60h] [xbp+60h] BYREF
  _QWORD v43[2]; // [xsp+68h] [xbp+68h] BYREF
  __int64 v44; // [xsp+78h] [xbp+78h] BYREF
  _QWORD v45[2]; // [xsp+80h] [xbp+80h] BYREF

  v8 = 0;
  sprd_log(
    7u,
    "avb_ops_get_image_buffer: img_addr = 0x%x\n",
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    MEMORY[0xFFFFFFFFE00643D8]);
  sprd_log(7u, "check dat cp\n", v9, v10, v11, v12, v13, v14, v15, v16);
  if ( (unsigned int)memcmp_neq(MEMORY[0xFFFFFFFFE00643D8], (__int64)"SCI1", 5) == 0 )
  {
    sprd_log(7u, "the image is new packed modem image\n", v17, v18, v19, v20, v21, v22, v23, v24);
    v38 = 0;
    v39[0] = 0;
    v39[1] = 0;
    v40 = 0;
    v41[0] = 0;
    v41[1] = 0;
    v42 = 0;
    v43[0] = 0;
    v43[1] = 0;
    v44 = 0;
    v45[0] = 0;
    v45[1] = 0;
    memcpy((__int64)&v38, MEMORY[0xFFFFFFFFE00643D8], 0x60u);
    if ( (unsigned int)memcmp_neq((__int64)&v38, (__int64)"SCI1", 5) == 0 )
    {
      v33 = WORD2(v39[0]);
      if ( BYTE4(v39[0]) == 1 )
      {
        v34 = (char *)v39 + 4;
      }
      else
      {
        v33 = v40;
        v34 = (char *)&v40;
        if ( (unsigned __int8)v40 != 1 )
        {
          v33 = WORD2(v41[0]);
          v34 = (char *)v41 + 4;
          if ( BYTE4(v41[0]) != 1 )
          {
            v33 = v42;
            v34 = (char *)&v42;
            if ( (unsigned __int8)v42 != 1 )
            {
              v33 = WORD2(v43[0]);
              v34 = (char *)v43 + 4;
              if ( BYTE4(v43[0]) != 1 )
              {
                v33 = v44;
                v34 = (char *)&v44;
                if ( (unsigned __int8)v44 != 1 )
                {
                  v33 = WORD2(v45[0]);
                  v34 = (char *)v45 + 4;
                  if ( BYTE4(v45[0]) != 1 )
                  {
                    v8 = 0;
                    sprd_log(7u, "no MODEM exe found in SCI header!", v25, v26, v27, v28, v29, v30, v31, v32);
                    v35 = 0;
                    v36 = 0;
LABEL_11:
                    sprd_log(
                      7u,
                      "modem offset: 0x%x, length: 0x%x\n",
                      v25,
                      v26,
                      v27,
                      v28,
                      v29,
                      v30,
                      v31,
                      v32,
                      v36,
                      v35);
                    return MEMORY[0xFFFFFFFFE00643D8] + v8;
                  }
                }
              }
            }
          }
        }
      }
      LODWORD(v36) = *((_DWORD *)v34 + 1);
      v35 = *((unsigned int *)v34 + 2);
      if ( (v33 & 0x400) != 0 )
        v36 = (unsigned int)(v36 + 20);
      else
        v36 = (unsigned int)v36;
      v8 = (unsigned int)v36;
      goto LABEL_11;
    }
    v8 = 0;
    sprd_log(7u, "old image format!\n", v25, v26, v27, v28, v29, v30, v31, v32);
    v35 = 0;
    v36 = 0;
    goto LABEL_11;
  }
  return MEMORY[0xFFFFFFFFE00643D8] + v8;
}

/* ===== avb_get_pubkey_hash @ 0x940477A8 size 24 ===== */
__int64 __fastcall avb_get_pubkey_hash(_QWORD *a1)
{
  *a1 = MEMORY[0xFFFFFFFFE006440C];
  return MEMORY[0xFFFFFFFFE00643E8];
}

/* ===== avb_validate_public_key @ 0x940477C0 size 436 ===== */
__int64 __fastcall avb_validate_public_key(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13,
        _DWORD *a14)
{
  double v17; // d0
  double v18; // d1
  double v19; // d2
  double v20; // d3
  double v21; // d4
  double v22; // d5
  double v23; // d6
  double v24; // d7
  __int64 v25; // x23
  double v26; // d0
  double v27; // d1
  double v28; // d2
  double v29; // d3
  double v30; // d4
  double v31; // d5
  double v32; // d6
  double v33; // d7
  double v34; // d0
  double v35; // d1
  double v36; // d2
  double v37; // d3
  double v38; // d4
  double v39; // d5
  double v40; // d6
  double v41; // d7
  double v42; // d0
  double v43; // d1
  double v44; // d2
  double v45; // d3
  double v46; // d4
  double v47; // d5
  double v48; // d6
  double v49; // d7
  double v50; // d0
  double v51; // d1
  double v52; // d2
  double v53; // d3
  double v54; // d4
  double v55; // d5
  double v56; // d6
  double v57; // d7
  double v59; // d0
  double v60; // d1
  double v61; // d2
  double v62; // d3
  double v63; // d4
  double v64; // d5
  double v65; // d6
  double v66; // d7
  double v67; // d0
  double v68; // d1
  double v69; // d2
  double v70; // d3
  double v71; // d4
  double v72; // d5
  double v73; // d6
  double v74; // d7
  double v75; // d0
  double v76; // d1
  double v77; // d2
  double v78; // d3
  double v79; // d4
  double v80; // d5
  double v81; // d6
  double v82; // d7
  __int64 v83; // [xsp+48h] [xbp+48h] BYREF
  _BYTE v84[32]; // [xsp+50h] [xbp+50h] BYREF

  sprd_log(7u, (const char *)&loc_94057158, a1, a2, a3, a4, a5, a6, a7, a8);
  if ( a10 == 0 || a11 == 0 || a14 == nullptr )
  {
    sprd_log(0, "invalid: para is null.\n", v17, v18, v19, v20, v21, v22, v23, v24, 0);
    sprd_log(0, "Info: out_key_is_trusted is 0x%llx.\n", v59, v60, v61, v62, v63, v64, v65, v66, a14, 0);
    sprd_log(0, "Info: public_key_data is 0x%llx.\n", v67, v68, v69, v70, v71, v72, v73, v74, a10, 0);
    sprd_log(0, "Info: public_key_length is 0x%llx.\n", v75, v76, v77, v78, v79, v80, v81, v82, a11, 0);
    return 1;
  }
  else
  {
    v25 = avb_get_pubkey_hash(&v83);
    sprd_log(
      7u,
      "dump public_key_hash: public_key_hash_length:%d. \n",
      v26,
      v27,
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v83,
      0);
    if ( v25 != 0 && v83 != 0 )
      nullsub_9("vboot key hash from uboot", v25, v83);
    cal_sha256(a10, a11, (__int64)v84, v34, v35, v36, v37, v38, v39, v40, v41);
    nullsub_9("pk_data sha256", v84, 32);
    if ( v83 != 32 || (unsigned int)memcmp_neq(v25, (__int64)v84, 32) != 0 )
    {
      sprd_log(7u, "expected_public_key is not matched.\n", v42, v43, v44, v45, v46, v47, v48, v49, 0);
      sprd_log(
        0,
        "vbmeta",
        v50,
        v51,
        v52,
        v53,
        v54,
        v55,
        v56,
        v57,
        ": Public key used to sign data does not match key in chain partition descriptor.\n",
        0);
      *a14 = 0;
      return 5;
    }
    else
    {
      sprd_log(7u, "expected_public_key is matched.\n", v42, v43, v44, v45, v46, v47, v48, v49, 0);
      *a14 = 1;
      return 0;
    }
  }
}

/* ===== avb_ops_init_kbc @ 0x94047974 size 96 ===== */
__int64 avb_ops_init_kbc()
{
  MEMORY[0xFFFFFFFFE00643A8] = -536709184;
  MEMORY[0xFFFFFFFFE0064388] = 0;
  MEMORY[0xFFFFFFFFE0064398] = -536710120;
  MEMORY[0xFFFFFFFFE00643A0] = 0;
  MEMORY[0xFFFFFFFFE00643B0] = avb_read_rollback_index;
  MEMORY[0xFFFFFFFFE00643B8] = -536710912;
  MEMORY[0xFFFFFFFFE00643C0] = -536710876;
  MEMORY[0xFFFFFFFFE00643C8] = -536710920;
  MEMORY[0xFFFFFFFFE0064380] = 0;
  return -536460416;
}

/* ===== avb_check_image_kbc @ 0x940479D4 size 308 ===== */
__int64 __fastcall avb_check_image_kbc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  unsigned int v18; // w3
  unsigned int v19; // w20
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  const char *v36; // x0
  double v37; // d0
  double v38; // d1
  double v39; // d2
  double v40; // d3
  double v41; // d4
  double v42; // d5
  double v43; // d6
  double v44; // d7
  double v45; // d0
  double v46; // d1
  double v47; // d2
  double v48; // d3
  double v49; // d4
  double v50; // d5
  double v51; // d6
  double v52; // d7
  double v53; // d0
  double v54; // d1
  double v55; // d2
  double v56; // d3
  double v57; // d4
  double v58; // d5
  double v59; // d6
  double v60; // d7
  int v62; // w0
  __int64 v63[2]; // [xsp+30h] [xbp+30h] BYREF

  v63[0] = 0;
  v63[1] = 0;
  if ( a1 != 0 )
  {
    sprd_log(1u, "avb check image name:%s.\n", a2, a3, a4, a5, a6, a7, a8, a9, a1);
    v63[0] = a1;
  }
  else
  {
    sprd_log(1u, "avb check image name is null.\n", a2, a3, a4, a5, a6, a7, a8, a9);
    v63[0] = (__int64)"";
  }
  v18 = 0;
  if ( MEMORY[0xFFFFFFFFE0064418] == 1 )
  {
    v62 = strcmp(a1, (__int64)"boot");
    v18 = 1;
    if ( v62 != 0 )
      v18 = strcmp(a1, (__int64)"recovery") == 0;
  }
  v19 = avb_slot_verify(
          -536460416,
          v63,
          (__int64)"",
          v18,
          (__int64 *)0xFFFFFFFFE0057F18LL,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17);
  sprd_log(1u, ">>>>>>>>>>>>>>>>  avb_slot_verify result is %d.\n", v20, v21, v22, v23, v24, v25, v26, v27, v19);
  v36 = avb_slot_verify_result_to_string(v19, v28, v29, v30, v31, v32, v33, v34, v35);
  sprd_log(1u, ">>>>>>>>>>>>>>>>  avb_slot_verify result is %s.\n", v37, v38, v39, v40, v41, v42, v43, v44, v36);
  sprd_log(1u, "slot_data[0] is 0x%x.\n", v45, v46, v47, v48, v49, v50, v51, v52, MEMORY[0xFFFFFFFFE0057F18]);
  sprd_log(1u, "slot_data[1] is 0x%x.\n", v53, v54, v55, v56, v57, v58, v59, v60, MEMORY[0xFFFFFFFFE0057F20]);
  return v19;
}

/* ===== nullsub_9 @ 0x94047B08 size 4 ===== */
void nullsub_9()
{
  ;
}

/* ===== process_set_version_smc @ 0x94047B0C size 292 ===== */
__int64 __fastcall process_set_version_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  unsigned int v10; // w19
  double v11; // d0
  double v12; // d1
  double v13; // d2
  double v14; // d3
  double v15; // d4
  double v16; // d5
  double v17; // d6
  double v18; // d7
  unsigned int v19; // w19
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  unsigned int v28; // w19
  double v29; // d0
  double v30; // d1
  double v31; // d2
  double v32; // d3
  double v33; // d4
  double v34; // d5
  double v35; // d6
  double v36; // d7
  __int64 v38; // [xsp+38h] [xbp+38h]
  __int64 v39; // [xsp+48h] [xbp+48h] BYREF

  sprd_log(1u, "enter vboot set_version\n", a2, a3, a4, a5, a6, a7, a8, a9);
  v10 = *(_DWORD *)(a1 + 8);
  v38 = *(unsigned int *)(a1 + 12);
  memset(-536460624, 0, 0x38u);
  sprd_log(1u, "from uboot smc...addr:0x%x len:0x%x\n", v11, v12, v13, v14, v15, v16, v17, v18, v10, v38);
  v19 = sprd_iomap((__int64)"sprdsec", v10, 0x1000u, 0x30u, (__int64)&v39);
  if ( v19 != 0 )
  {
    sprd_log(1u, "can not map phy addr 1 , ret:%d\n", v20, v21, v22, v23, v24, v25, v26, v27, v19);
    return (int)v19;
  }
  else
  {
    memcpy(-536460624, v39, 0x38u);
    nullsub_9();
    if ( v39 != 0 && (v28 = sprd_iounmap(v39)) != 0 )
    {
      sprd_log(1u, "can not unmap virt addr, ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v28);
      return (int)v28;
    }
    else
    {
      return 0;
    }
  }
}

/* ===== process_vboot_verify_smc @ 0x94047C30 size 1928 ===== */
__int64 __fastcall process_vboot_verify_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  unsigned int v18; // w20
  unsigned int v19; // w19
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  __int64 v36; // x0
  unsigned int v37; // w25
  unsigned int v38; // w24
  unsigned int v39; // w23
  unsigned int v40; // w22
  unsigned int v41; // w20
  unsigned int v42; // w21
  unsigned int v43; // w19
  double v44; // d0
  double v45; // d1
  double v46; // d2
  double v47; // d3
  double v48; // d4
  double v49; // d5
  double v50; // d6
  double v51; // d7
  double v52; // d0
  double v53; // d1
  double v54; // d2
  double v55; // d3
  double v56; // d4
  double v57; // d5
  double v58; // d6
  double v59; // d7
  int v60; // w1
  unsigned int v61; // w19
  double v62; // d0
  double v63; // d1
  double v64; // d2
  double v65; // d3
  double v66; // d4
  double v67; // d5
  double v68; // d6
  double v69; // d7
  double v70; // d0
  double v71; // d1
  double v72; // d2
  double v73; // d3
  double v74; // d4
  double v75; // d5
  double v76; // d6
  double v77; // d7
  double v78; // d0
  double v79; // d1
  double v80; // d2
  double v81; // d3
  double v82; // d4
  double v83; // d5
  double v84; // d6
  double v85; // d7
  unsigned int v86; // w19
  unsigned int v87; // w27
  double v88; // d0
  double v89; // d1
  double v90; // d2
  double v91; // d3
  double v92; // d4
  double v93; // d5
  double v94; // d6
  double v95; // d7
  unsigned int v96; // w0
  __int64 v97; // x0
  unsigned int v98; // w0
  double v99; // d0
  double v100; // d1
  double v101; // d2
  double v102; // d3
  double v103; // d4
  double v104; // d5
  double v105; // d6
  double v106; // d7
  unsigned int v107; // w19
  double v108; // d0
  double v109; // d1
  double v110; // d2
  double v111; // d3
  double v112; // d4
  double v113; // d5
  double v114; // d6
  double v115; // d7
  unsigned int v117; // w19
  double v118; // d0
  double v119; // d1
  double v120; // d2
  double v121; // d3
  double v122; // d4
  double v123; // d5
  double v124; // d6
  double v125; // d7
  double v126; // d0
  double v127; // d1
  double v128; // d2
  double v129; // d3
  double v130; // d4
  double v131; // d5
  double v132; // d6
  double v133; // d7
  unsigned int v134; // w0
  double v135; // d0
  double v136; // d1
  double v137; // d2
  double v138; // d3
  double v139; // d4
  double v140; // d5
  double v141; // d6
  double v142; // d7
  double v143; // d0
  double v144; // d1
  double v145; // d2
  double v146; // d3
  double v147; // d4
  double v148; // d5
  double v149; // d6
  double v150; // d7
  __int64 v151; // x27
  unsigned int v152; // w0
  __int64 v153; // x19
  double v154; // d0
  double v155; // d1
  double v156; // d2
  double v157; // d3
  double v158; // d4
  double v159; // d5
  double v160; // d6
  double v161; // d7
  __int64 v162; // [xsp+68h] [xbp+68h]
  unsigned int v163; // [xsp+70h] [xbp+70h] BYREF
  unsigned int v164; // [xsp+74h] [xbp+74h] BYREF
  __int64 v165; // [xsp+78h] [xbp+78h] BYREF
  __int64 v166; // [xsp+80h] [xbp+80h] BYREF
  unsigned __int64 v167; // [xsp+88h] [xbp+88h] BYREF
  __int64 v168; // [xsp+90h] [xbp+90h] BYREF
  __int64 v169; // [xsp+98h] [xbp+98h] BYREF
  __int64 v170; // [xsp+A0h] [xbp+A0h] BYREF
  __int64 v171; // [xsp+A8h] [xbp+A8h] BYREF
  __int64 v172; // [xsp+B0h] [xbp+B0h] BYREF
  __int64 v173; // [xsp+B8h] [xbp+B8h] BYREF
  unsigned __int64 v174; // [xsp+C0h] [xbp+C0h] BYREF
  unsigned __int64 v175; // [xsp+C8h] [xbp+C8h] BYREF

  v165 = 0;
  v166 = 0;
  v167 = 0;
  v168 = 0;
  v169 = 0;
  v170 = 0;
  v163 = 0;
  v171 = 0;
  v172 = 0;
  v173 = 0;
  v164 = 0;
  v174 = 0;
  v175 = 0;
  sprd_log(1u, "enter vboot verify\n", a2, a3, a4, a5, a6, a7, a8, a9);
  secboot_data_init(v10, v11, v12, v13, v14, v15, v16, v17);
  v18 = *(_DWORD *)(a1 + 12);
  v19 = *(_DWORD *)(a1 + 8);
  sprd_log(1u, "from uboot smc...addr:0x%x len:0x%x\n", v20, v21, v22, v23, v24, v25, v26, v27, v19, v18);
  if ( v18 != 0 && v19 != 0 )
  {
    v117 = sprd_iomap((__int64)"sprdsec", v19, 0x1000u, 0x30u, (__int64)&v171);
    if ( v117 != 0 )
    {
      sprd_log(1u, "can not map phy addr 1 , ret:%d\n", v28, v29, v30, v31, v32, v33, v34, v35, v117);
      return (int)v117;
    }
  }
  v36 = v171;
  v37 = *(_DWORD *)(v171 + 8);
  if ( v37 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      *(_QWORD *)v171,
      v37);
    v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)v171, (v37 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v165);
    if ( v43 != 0 )
      goto LABEL_55;
    v36 = v171;
  }
  v38 = *(_DWORD *)(v36 + 24);
  if ( v38 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      *(_QWORD *)(v36 + 16),
      v38);
    v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v171 + 16), (v38 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v166);
    if ( v43 != 0 )
      goto LABEL_55;
    v36 = v171;
  }
  v39 = *(_DWORD *)(v36 + 40);
  if ( v39 == 0 )
  {
    v40 = *(_DWORD *)(v36 + 56);
    if ( v40 == 0 )
      goto LABEL_7;
LABEL_44:
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      *(_QWORD *)(v36 + 48),
      v40);
    v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v171 + 48), (v40 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v168);
    if ( v43 != 0 )
      goto LABEL_55;
    v36 = v171;
    v41 = *(_DWORD *)(v171 + 72);
    if ( v41 == 0 )
      goto LABEL_8;
    goto LABEL_46;
  }
  sprd_log(
    1u,
    "from uboot smc...addr:0x%x len:0x%x\n",
    v28,
    v29,
    v30,
    v31,
    v32,
    v33,
    v34,
    v35,
    *(_QWORD *)(v36 + 32),
    v39);
  v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v171 + 32), (v39 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v167);
  if ( v43 != 0 )
    goto LABEL_55;
  v36 = v171;
  v40 = *(_DWORD *)(v171 + 56);
  if ( v40 != 0 )
    goto LABEL_44;
LABEL_7:
  v41 = *(_DWORD *)(v36 + 72);
  if ( v41 != 0 )
  {
LABEL_46:
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      *(_QWORD *)(v36 + 64),
      v41);
    v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v171 + 64), (v41 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v169);
    if ( v43 == 0 )
    {
      v36 = v171;
      goto LABEL_8;
    }
LABEL_55:
    sprd_log(1u, "can not map phy addr 2 , ret:%d\n", v28, v29, v30, v31, v32, v33, v34, v35, v43);
    return (int)v43;
  }
LABEL_8:
  v42 = *(_DWORD *)(v36 + 88);
  if ( v42 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v28,
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      *(_QWORD *)(v36 + 80),
      v42);
    v43 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v171 + 80), (v42 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v170);
    if ( v43 != 0 )
      goto LABEL_55;
  }
  sprd_log(1u, "vb_cmdline_len:%d, vbmeta_pubkey_addr:0x%x\n", v28, v29, v30, v31, v32, v33, v34, v35, v41, v169);
  sprd_log(1u, "vb_cmdline_len:%d, vbmeta_pubkey_addr:0x%x\n", v44, v45, v46, v47, v48, v49, v50, v51, v42, v170);
  MEMORY[0xFFFFFFFFE00643D0] = v165;
  MEMORY[0xFFFFFFFFE00643E0] = v167;
  v60 = *(_DWORD *)(v171 + 92);
  MEMORY[0xFFFFFFFFE00643E8] = v168;
  MEMORY[0xFFFFFFFFE0064400] = v37;
  MEMORY[0xFFFFFFFFE00643D8] = v166;
  MEMORY[0xFFFFFFFFE0064404] = v38;
  MEMORY[0xFFFFFFFFE0064408] = v39;
  MEMORY[0xFFFFFFFFE006440C] = v40;
  MEMORY[0xFFFFFFFFE0064410] = v41;
  MEMORY[0xFFFFFFFFE00643F0] = v169;
  MEMORY[0xFFFFFFFFE0064418] = v60;
  if ( v166 != 0 && v38 != 0 )
  {
    avb_ops_init();
    v87 = 0;
    sprd_log(
      1u,
      "img_name:%s, g_avbUserData.img_name:%s.\n",
      v118,
      v119,
      v120,
      v121,
      v122,
      v123,
      v124,
      v125,
      v165,
      MEMORY[0xFFFFFFFFE00643D0]);
    v86 = avb_check_image_kbc(v165, v126, v127, v128, v129, v130, v131, v132, v133);
    v163 = v86;
  }
  else
  {
    sprd_log(1u, "enter vbmeta check\n", v52, v53, v54, v55, v56, v57, v58, v59);
    avb_ops_init();
    v61 = avb_vbmeta_verify(v167, v39, &v172, &v173, &v174);
    sprd_log(1u, (const char *)vbmeta_check_log_stub, v62, v63, v64, v65, v66, v67, v68, v69, v61);
    sprd_log(1u, "rollback_index is %lld.\n", v70, v71, v72, v73, v74, v75, v76, v77, v174);
    if ( v61 != 0 )
    {
      v86 = 1;
      v163 = 1;
      v87 = 1;
    }
    else
    {
      v87 = 1;
      v163 = MEMORY[0xFFFFFFFFE00643A8](-536460416, v172, v173, 0, 0, &v164);
      sprd_log(1u, (const char *)&loc_94057488, v154, v155, v156, v157, v158, v159, v160, v161, v163, v164);
      v86 = v163;
      if ( v163 == 0 )
      {
        sprd_log(1u, "Check rollback index for vbmeta \n", v78, v79, v80, v81, v82, v83, v84, v85);
        if ( (unsigned int)MEMORY[0xFFFFFFFFE00643B0](-536460416, 0, &v175) != 0 )
        {
          v86 = 4;
          v163 = 4;
        }
        else if ( v174 >= v175 )
        {
          sprd_log(
            1u,
            "Info: vbmeta rollback_index:%lld, >= stored_rollback_index:%lld.\n",
            v78,
            v79,
            v80,
            v81,
            v82,
            v83,
            v84,
            v85);
          v163 = 0;
        }
        else
        {
          sprd_log(
            1u,
            "Error: vbmeta rollback_index:%lld, < stored_rollback_index:%lld.\n",
            v78,
            v79,
            v80,
            v81,
            v82,
            v83,
            v84,
            v85);
          v163 = 4;
          v86 = 4;
        }
      }
    }
  }
  sprd_log(1u, (const char *)&loc_940575A0, v78, v79, v80, v81, v82, v83, v84, v85, v86);
  if ( (unsigned int)strcmp(v165, (__int64)"boot") == 0 && MEMORY[0xFFFFFFFFE0064418] == 1 )
  {
    v96 = v163;
    if ( v163 == 5 )
      goto LABEL_60;
  }
  else
  {
    v96 = v163;
  }
  if ( v96 != 0 )
  {
    while ( 1 )
      ;
  }
  if ( v87 == 0 )
  {
    if ( MEMORY[0xFFFFFFFFE0057F18] != 0 )
    {
      v97 = *(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL);
      if ( v97 != 0 )
      {
        if ( (unsigned int)strlen(v97) != 0 )
        {
          v134 = strlen(*(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL));
          sprd_log(1u, (const char *)&loc_940575C0, v135, v136, v137, v138, v139, v140, v141, v142, v134);
          strlen(*(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL));
          nullsub_9();
          sprd_log(
            1u,
            "avb_slot_data[0]->cmdline is %s\n",
            v143,
            v144,
            v145,
            v146,
            v147,
            v148,
            v149,
            v150,
            *(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL));
          v151 = v169;
          v162 = *(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL);
          v152 = strlen(v162);
          memcpy(v151, v162, v152);
          v153 = v169;
          *(_BYTE *)(v153 + (unsigned int)strlen(*(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL))) = 0;
          dcache_clean(v169, v41);
LABEL_24:
          if ( MEMORY[0xFFFFFFFFE0057F18] != 0 )
            avb_slot_data_free(MEMORY[0xFFFFFFFFE0057F18]);
          goto LABEL_26;
        }
        v97 = *(_QWORD *)(MEMORY[0xFFFFFFFFE0057F18] + 40LL);
      }
    }
    else
    {
      v97 = MEMORY[0x28];
    }
    v98 = strlen(v97);
    sprd_log(1u, "avb_slot_data[0]->cmdline para error,  %d\n", v99, v100, v101, v102, v103, v104, v105, v106, v98);
    goto LABEL_24;
  }
LABEL_60:
  sprd_log(1u, (const char *)&loc_94057648, v88, v89, v90, v91, v92, v93, v94, v95, v87);
LABEL_26:
  memcpy(v170, (__int64)&v163, 4u);
  if ( (v171 == 0 || (v107 = sprd_iounmap(v171)) == 0)
    && (v165 == 0 || (v107 = sprd_iounmap(v165)) == 0)
    && (v166 == 0 || (v107 = sprd_iounmap(v166)) == 0)
    && (v167 == 0 || (v107 = sprd_iounmap(v167)) == 0)
    && (v168 == 0 || (v107 = sprd_iounmap(v168)) == 0)
    && (v169 == 0 || (v107 = sprd_iounmap(v169)) == 0) )
  {
    if ( v170 == 0 )
      return 0;
    v107 = sprd_iounmap(v170);
    if ( v107 == 0 )
      return 0;
  }
  sprd_log(1u, "can not unmap virt addr, ret:%d\n", v108, v109, v110, v111, v112, v113, v114, v115, v107);
  return (int)v107;
}

/* ===== process_vboot_verify_sn_smc @ 0x940483B8 size 1564 ===== */
__int64 __fastcall process_vboot_verify_sn_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  unsigned int v18; // w20
  unsigned int v19; // w19
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  unsigned int v28; // w19
  double v29; // d0
  double v30; // d1
  double v31; // d2
  double v32; // d3
  double v33; // d4
  double v34; // d5
  double v35; // d6
  double v36; // d7
  __int64 v37; // x0
  unsigned int v38; // w24
  unsigned int v39; // w20
  unsigned int v40; // w21
  unsigned int v41; // w22
  unsigned int v42; // w23
  unsigned int v43; // w19
  unsigned int v44; // w19
  double v45; // d0
  double v46; // d1
  double v47; // d2
  double v48; // d3
  double v49; // d4
  double v50; // d5
  double v51; // d6
  double v52; // d7
  unsigned int v53; // w25
  double v54; // d0
  double v55; // d1
  double v56; // d2
  double v57; // d3
  double v58; // d4
  double v59; // d5
  double v60; // d6
  double v61; // d7
  double v62; // d0
  double v63; // d1
  double v64; // d2
  double v65; // d3
  double v66; // d4
  double v67; // d5
  double v68; // d6
  double v69; // d7
  unsigned int v70; // w19
  unsigned int v71; // w19
  unsigned int v72; // w19
  unsigned int v73; // w19
  unsigned int *v75; // x19
  double v76; // d0
  double v77; // d1
  double v78; // d2
  double v79; // d3
  double v80; // d4
  double v81; // d5
  double v82; // d6
  double v83; // d7
  __int64 *v84; // x0
  double v85; // d0
  double v86; // d1
  double v87; // d2
  double v88; // d3
  double v89; // d4
  double v90; // d5
  double v91; // d6
  double v92; // d7
  double v93; // d0
  double v94; // d1
  double v95; // d2
  double v96; // d3
  double v97; // d4
  double v98; // d5
  double v99; // d6
  double v100; // d7
  unsigned int v101; // w19
  double v102; // d0
  double v103; // d1
  double v104; // d2
  double v105; // d3
  double v106; // d4
  double v107; // d5
  double v108; // d6
  double v109; // d7
  __int64 v110; // [xsp+58h] [xbp+58h]
  int v111; // [xsp+68h] [xbp+68h] BYREF
  int v112; // [xsp+6Ch] [xbp+6Ch] BYREF
  unsigned __int64 v113; // [xsp+70h] [xbp+70h] BYREF
  __int64 v114; // [xsp+78h] [xbp+78h] BYREF
  __int64 v115; // [xsp+80h] [xbp+80h] BYREF
  __int64 v116; // [xsp+88h] [xbp+88h] BYREF
  __int64 v117; // [xsp+90h] [xbp+90h] BYREF
  __int64 v118; // [xsp+98h] [xbp+98h] BYREF
  __int64 v119; // [xsp+A0h] [xbp+A0h] BYREF
  __int64 v120; // [xsp+A8h] [xbp+A8h] BYREF

  v113 = 0;
  v114 = 0;
  v115 = 0;
  v116 = 0;
  v117 = 0;
  v118 = 0;
  v119 = 0;
  v120 = 0;
  v111 = 0;
  sprd_log(1u, "enter vboot verify\n", a2, a3, a4, a5, a6, a7, a8, a9);
  secboot_data_init(v10, v11, v12, v13, v14, v15, v16, v17);
  v18 = *(_DWORD *)(a1 + 12);
  v19 = *(_DWORD *)(a1 + 8);
  sprd_log(1u, "from uboot smc...addr:0x%x len:0x%x\n", v20, v21, v22, v23, v24, v25, v26, v27, v19, v18);
  if ( v18 == 0 || v19 == 0 )
    return -1;
  v28 = sprd_iomap((__int64)"sprdsec", v19, 0x1000u, 0x30u, (__int64)&v118);
  if ( v28 != 0 )
  {
    sprd_log(1u, "can not map phy addr ns_addr , ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v28);
    return (int)v28;
  }
  v37 = v118;
  if ( v118 == 0 )
  {
    sprd_log(1u, "imginfo address error\n", v29, v30, v31, v32, v33, v34, v35, v36);
    return -1;
  }
  v38 = *(_DWORD *)(v118 + 8);
  if ( v38 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      v36,
      *(_QWORD *)v118,
      v38);
    v73 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)v118, (v38 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v113);
    if ( v73 != 0 )
    {
      sprd_log(1u, "can not map phy addr vbmeta_img_paddr , ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v73);
      return (int)v73;
    }
    v37 = v118;
  }
  v39 = *(_DWORD *)(v37 + 24);
  if ( v39 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      v36,
      *(_QWORD *)(v37 + 16),
      v39);
    v72 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v118 + 16), (v39 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v114);
    if ( v72 != 0 )
    {
      sprd_log(
        1u,
        "can not map phy addr vbmeta_pubkey_addr , ret:%d\n",
        v29,
        v30,
        v31,
        v32,
        v33,
        v34,
        v35,
        v36,
        v72);
      return (int)v72;
    }
    v37 = v118;
  }
  v40 = *(_DWORD *)(v37 + 40);
  if ( v40 != 0 )
  {
    sprd_log(
      1u,
      "from uboot smc...addr:0x%x len:0x%x\n",
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      v36,
      *(_QWORD *)(v37 + 32),
      v40);
    v70 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v118 + 32), (v40 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v115);
    if ( v70 != 0 )
    {
      sprd_log(1u, "can not map phy addr product_sn_addr , ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v70);
      return (int)v70;
    }
    v37 = v118;
    v41 = *(_DWORD *)(v118 + 56);
    if ( v41 == 0 )
      goto LABEL_9;
  }
  else
  {
    v41 = *(_DWORD *)(v37 + 56);
    if ( v41 == 0 )
      goto LABEL_9;
  }
  sprd_log(
    1u,
    "from uboot smc...addr:0x%x len:0x%x\n",
    v29,
    v30,
    v31,
    v32,
    v33,
    v34,
    v35,
    v36,
    *(_QWORD *)(v37 + 48),
    v41);
  v71 = sprd_iomap((__int64)"sprdsec", *(_QWORD *)(v118 + 48), (v41 & 0xFFFFF000) + 4096, 0x30u, (__int64)&v116);
  if ( v71 != 0 )
  {
    sprd_log(
      1u,
      "can not map phy addr product_sn_signature_addr , ret:%d\n",
      v29,
      v30,
      v31,
      v32,
      v33,
      v34,
      v35,
      v36,
      v71);
    return (int)v71;
  }
  v37 = v118;
LABEL_9:
  v42 = *(_DWORD *)(v37 + 72);
  if ( v42 != 0
    && (sprd_log(
          1u,
          "from uboot smc...addr:0x%x len:0x%x\n",
          v29,
          v30,
          v31,
          v32,
          v33,
          v34,
          v35,
          v36,
          *(_QWORD *)(v37 + 64),
          v42),
        (v43 = sprd_iomap(
                 (__int64)"sprdsec",
                 *(_QWORD *)(v118 + 64),
                 (v42 & 0xFFFFF000) + 4096,
                 0x30u,
                 (__int64)&v117)) != 0) )
  {
    sprd_log(1u, "can not map phy addr 2 , ret:%d\n", v29, v30, v31, v32, v33, v34, v35, v36, v43);
    return (int)v43;
  }
  else
  {
    v44 = 1;
    sprd_log(1u, (const char *)&loc_94057780, v29, v30, v31, v32, v33, v34, v35, v36, v42, v117);
    MEMORY[0xFFFFFFFFE00643E0] = v113;
    MEMORY[0xFFFFFFFFE00643E8] = v114;
    MEMORY[0xFFFFFFFFE0064408] = v38;
    MEMORY[0xFFFFFFFFE006440C] = v39;
    sprd_log(1u, "Enter vbmeta check\n", v45, v46, v47, v48, v49, v50, v51, v52);
    avb_ops_init();
    v53 = avb_vbmeta_verify(v113, v38, &v119, &v120, nullptr);
    sprd_log(1u, (const char *)vbmeta_check_log_stub, v54, v55, v56, v57, v58, v59, v60, v61, v53);
    if ( v53 == 0 )
      v44 = MEMORY[0xFFFFFFFFE00643A8](-536460416, v119, v120, 0, 0, &v111);
    sprd_log(1u, (const char *)&loc_940575A0, v62, v63, v64, v65, v66, v67, v68, v69, v44);
    if ( v44 != 0 )
    {
      while ( 1 )
        ;
    }
    v75 = (unsigned int *)avb_malloc(200);
    if ( v75 != nullptr )
    {
      sprd_log(1u, "Calculate hash with product_sn\n", v76, v77, v78, v79, v80, v81, v82, v83);
      sha256_init(v75);
      sha256_update(v75, v115, v40);
      v110 = sha256_final((__int64)v75);
      v84 = avb_get_algorithm(2u);
      if ( v84 != nullptr )
      {
        v112 = avb_rsa_verify_sw(
                 v119,
                 v120,
                 v116,
                 v41,
                 v110,
                 *((unsigned int *)v84 + 4),
                 *v84,
                 v84[1],
                 v85,
                 v86,
                 v87,
                 v88,
                 v89,
                 v90,
                 v91,
                 v92);
        if ( v112 != 0 )
          sprd_log(1u, (const char *)&loc_940577F8, v93, v94, v95, v96, v97, v98, v99, v100);
      }
      else
      {
        sprd_log(0, "Invalid or unknown algorithm.\n", v85, v86, v87, v88, v89, v90, v91, v92);
      }
      free((__int64)v75);
    }
    else
    {
      sprd_log(0, "malloc failed.\n", v76, v77, v78, v79, v80, v81, v82, v83);
    }
    memcpy(v117, (__int64)&v112, 4u);
    v101 = sprd_iounmap(v118);
    if ( v101 != 0
      || v113 != 0 && (v101 = sprd_iounmap(v113)) != 0
      || v114 != 0 && (v101 = sprd_iounmap(v114)) != 0
      || v115 != 0 && (v101 = sprd_iounmap(v115)) != 0
      || v116 != 0 && (v101 = sprd_iounmap(v116)) != 0
      || v117 != 0 && (v101 = sprd_iounmap(v117)) != 0 )
    {
      sprd_log(1u, "can not unmap virt addr, ret:%d\n", v102, v103, v104, v105, v106, v107, v108, v109, v101);
      return (int)v101;
    }
    else
    {
      return 0;
    }
  }
}

/* ===== process_config_os_version_smc @ 0x940489D4 size 472 ===== */
__int64 __fastcall process_config_os_version_smc(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  unsigned int v10; // w19
  double v11; // d0
  double v12; // d1
  double v13; // d2
  double v14; // d3
  double v15; // d4
  double v16; // d5
  double v17; // d6
  double v18; // d7
  unsigned int v19; // w19
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  unsigned int v28; // w19
  unsigned __int64 v29; // x25
  unsigned __int64 v30; // x22
  double v31; // d0
  double v32; // d1
  double v33; // d2
  double v34; // d3
  double v35; // d4
  double v36; // d5
  double v37; // d6
  double v38; // d7
  int v39; // w4
  int v40; // w23
  unsigned int v41; // w19
  double v42; // d0
  double v43; // d1
  double v44; // d2
  double v45; // d3
  double v46; // d4
  double v47; // d5
  double v48; // d6
  double v49; // d7
  unsigned int v50; // w19
  double v51; // d0
  double v52; // d1
  double v53; // d2
  double v54; // d3
  double v55; // d4
  double v56; // d5
  double v57; // d6
  double v58; // d7
  __int64 v60; // [xsp+58h] [xbp+58h]
  unsigned int v61; // [xsp+6Ch] [xbp+6Ch] BYREF
  __int64 v62; // [xsp+70h] [xbp+70h] BYREF
  _DWORD v63[2]; // [xsp+78h] [xbp+78h] BYREF

  v61 = 0;
  sprd_log(1u, "enter sprd_vboot_config_os_version\n", a2, a3, a4, a5, a6, a7, a8, a9);
  v10 = *(_DWORD *)(a1 + 8);
  v60 = *(unsigned int *)(a1 + 12);
  memset(-536477112, 0, 0x1000u);
  sprd_log(1u, "from uboot smc...addr:0x%x len:0x%x\n", v11, v12, v13, v14, v15, v16, v17, v18, v10, v60);
  v19 = sprd_iomap((__int64)"sprdsec", v10, 0x1000u, 0x30u, (__int64)&v62);
  if ( v19 != 0 )
  {
    sprd_log(1u, "can not map phy addr 1 , ret:%d\n", v20, v21, v22, v23, v24, v25, v26, v27, v19);
    return (int)v19;
  }
  else
  {
    memcpy((__int64)&v61, v62, 4u);
    v28 = v61 >> 25;
    v29 = ((unsigned __int64)v61 >> 18) & 0x7F;
    v30 = ((unsigned __int64)v61 >> 11) & 0x7F;
    sprd_log(
      1u,
      "System version(Major.Minor.Sub_minor): (%d.%d.%d)\n",
      v31,
      v32,
      v33,
      v34,
      v35,
      v36,
      v37,
      v38,
      v61 >> 25,
      (unsigned int)v29,
      (unsigned int)v30);
    v39 = v29 + 100 * v28;
    v40 = v61 & 0xF;
    v41 = ((v61 >> 4) & 0x7F) + 2000;
    v63[0] = v30 + 100 * v39;
    sprd_log(
      1u,
      "System security patch level(Year-Month): (%04d-%02d)\n",
      v42,
      v43,
      v44,
      v45,
      v46,
      v47,
      v48,
      v49,
      v41,
      v61 & 0xF);
    v63[1] = v40 + 100 * v41;
    memcpy(-536477112, (__int64)v63, 8u);
    MEMORY[0xFFFFFFFFE0061248] = 8;
    nullsub_9();
    if ( v62 != 0 && (v50 = sprd_iounmap(v62)) != 0 )
    {
      sprd_log(1u, "can not unmap virt addr, ret:%d\n", v51, v52, v53, v54, v55, v56, v57, v58, v50);
      return (int)v50;
    }
    else
    {
      return 0;
    }
  }
}

/* ===== dump_hex @ 0x94048BAC size 204 ===== */
__int64 __fastcall dump_hex(
        __int64 a1,
        __int64 a2,
        int a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  double v13; // d0
  double v14; // d1
  double v15; // d2
  double v16; // d3
  double v17; // d4
  double v18; // d5
  double v19; // d6
  double v20; // d7
  __int64 v21; // x20
  __int64 v22; // x19
  __int64 v23; // x2
  __int64 v24; // x2
  double v25; // d0
  double v26; // d1
  double v27; // d2
  double v28; // d3
  double v29; // d4
  double v30; // d5
  double v31; // d6
  double v32; // d7

  sprd_log(1u, "%s", a4, a5, a6, a7, a8, a9, a10, a11, a1);
  if ( a3 > 0 )
  {
    v21 = (unsigned int)(a3 - 1) + 1LL;
    v22 = 0;
    do
    {
      while ( (v22 & 0xF) != 0 )
      {
        v23 = *(unsigned __int8 *)(a2 + v22++);
        sprd_log(1u, " %02x", v13, v14, v15, v16, v17, v18, v19, v20, v23);
        if ( v22 == v21 )
          return sprd_log(1u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
      }
      sprd_log(1u, "\n%04x", v13, v14, v15, v16, v17, v18, v19, v20, (unsigned int)v22);
      v24 = *(unsigned __int8 *)(a2 + v22++);
      sprd_log(1u, " %02x", v25, v26, v27, v28, v29, v30, v31, v32, v24);
    }
    while ( v22 != v21 );
  }
  return sprd_log(1u, "\n", v13, v14, v15, v16, v17, v18, v19, v20);
}

/* ===== kbc_version_name @ 0x94048C78 size 200 ===== */
const char *__fastcall kbc_version_name(int a1)
{
  const char *result; // x0

  switch ( a1 )
  {
    case 0:
      result = "VBMETA";
      break;
    case 1:
      result = "BOOT";
      break;
    case 2:
      result = "RECOVERY";
      break;
    case 3:
      result = "SYSTEM";
      break;
    case 4:
      result = "VENDOR";
      break;
    case 5:
      result = "MODEM";
      break;
    case 6:
      result = "LDSP";
      break;
    case 7:
      result = "LGDSP";
      break;
    case 8:
      result = "PM_SYS";
      break;
    case 9:
      result = "AGDSP";
      break;
    case 10:
      result = "WCN";
      break;
    case 11:
      result = "GPS";
      break;
    case 12:
      result = "GPU";
      break;
    default:
      result = "Unknown";
      break;
  }
  return result;
}

/* ===== kbc_v2_dump_version @ 0x94048D40 size 108 ===== */
__int64 __fastcall kbc_v2_dump_version(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v10; // x19
  __int64 result; // x0
  const char *v12; // x0
  __int64 v13; // x3
  double v14; // d0
  double v15; // d1
  double v16; // d2
  double v17; // d3
  double v18; // d4
  double v19; // d5
  double v20; // d6
  double v21; // d7

  v10 = 0;
  result = sprd_log(1u, "kbc_v2_dump_version \n", a2, a3, a4, a5, a6, a7, a8, a9);
  if ( a1 != 0 )
  {
    do
    {
      v12 = kbc_version_name(v10);
      v13 = *(unsigned int *)(a1 + 4 * v10++);
      result = sprd_log(1u, "%8s ver = %d \n", v14, v15, v16, v17, v18, v19, v20, v21, v12, v13);
    }
    while ( v10 != 13 );
  }
  return result;
}

/* ===== avb_userdata_set @ 0x94048DAC size 104 ===== */
__int64 __fastcall avb_userdata_set(
        __int64 a1,
        __int64 a2,
        int a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  sprd_log(1u, "[kbc]avb_userdata_set() packed offset = 0x%x\n", a4, a5, a6, a7, a8, a9, a10, a11);
  memset(-536460336, 0, 0x50u);
  MEMORY[0xFFFFFFFFE00643D8] = a1;
  MEMORY[0xFFFFFFFFE00643F8] = a2;
  MEMORY[0xFFFFFFFFE0064414] = a3;
  MEMORY[0xFFFFFFFFE0064408] = 0x10000;
  return 0x10000;
}

/* ===== avb_check_kbc_image @ 0x94048E14 size 216 ===== */
__int64 __fastcall avb_check_kbc_image(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  double v10; // d0
  double v11; // d1
  double v12; // d2
  double v13; // d3
  double v14; // d4
  double v15; // d5
  double v16; // d6
  double v17; // d7
  unsigned int v18; // w20
  double v19; // d0
  double v20; // d1
  double v21; // d2
  double v22; // d3
  double v23; // d4
  double v24; // d5
  double v25; // d6
  double v26; // d7
  double v27; // d0
  double v28; // d1
  double v29; // d2
  double v30; // d3
  double v31; // d4
  double v32; // d5
  double v33; // d6
  double v34; // d7
  const char *v35; // x0
  double v36; // d0
  double v37; // d1
  double v38; // d2
  double v39; // d3
  double v40; // d4
  double v41; // d5
  double v42; // d6
  double v43; // d7
  double v44; // d0
  double v45; // d1
  double v46; // d2
  double v47; // d3
  double v48; // d4
  double v49; // d5
  double v50; // d6
  double v51; // d7
  double v52; // d0
  double v53; // d1
  double v54; // d2
  double v55; // d3
  double v56; // d4
  double v57; // d5
  double v58; // d6
  double v59; // d7
  __int64 v61[2]; // [xsp+20h] [xbp+20h] BYREF

  v61[1] = 0;
  sprd_log(1u, "[kbc]avb_check_kbc_image() name = %s\n", a2, a3, a4, a5, a6, a7, a8, a9, a1);
  v61[0] = a1;
  v18 = avb_slot_verify(
          -536460416,
          v61,
          (__int64)"",
          0,
          (__int64 *)0xFFFFFFFFE0057F18LL,
          v10,
          v11,
          v12,
          v13,
          v14,
          v15,
          v16,
          v17);
  sprd_log(1u, "[kbc]avb_slot_verify result is %d.\n", v19, v20, v21, v22, v23, v24, v25, v26, v18);
  v35 = avb_slot_verify_result_to_string(v18, v27, v28, v29, v30, v31, v32, v33, v34);
  sprd_log(1u, "[kbc]avb_slot_verify result is %s.\n", v36, v37, v38, v39, v40, v41, v42, v43, v35);
  sprd_log(1u, "[kbc]slot_data[0] is 0x%x.\n", v44, v45, v46, v47, v48, v49, v50, v51, MEMORY[0xFFFFFFFFE0057F18]);
  sprd_log(1u, "[kbc]slot_data[1] is 0x%x.\n", v52, v53, v54, v55, v56, v57, v58, v59, MEMORY[0xFFFFFFFFE0057F20]);
  if ( MEMORY[0xFFFFFFFFE0057F18] != 0 )
    avb_slot_data_free(MEMORY[0xFFFFFFFFE0057F18]);
  return v18;
}

/* ===== kbc_image_verify_v2 @ 0x94048EEC size 480 ===== */
__int64 __fastcall kbc_image_verify_v2(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v10; // x19
  unsigned int v11; // w20
  double v12; // d0
  double v13; // d1
  double v14; // d2
  double v15; // d3
  double v16; // d4
  double v17; // d5
  double v18; // d6
  double v19; // d7
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  double v28; // d0
  double v29; // d1
  double v30; // d2
  double v31; // d3
  double v32; // d4
  double v33; // d5
  double v34; // d6
  double v35; // d7
  unsigned int v37; // w21
  double v38; // d0
  double v39; // d1
  double v40; // d2
  double v41; // d3
  double v42; // d4
  double v43; // d5
  double v44; // d6
  double v45; // d7
  double v46; // d0
  double v47; // d1
  double v48; // d2
  double v49; // d3
  double v50; // d4
  double v51; // d5
  double v52; // d6
  double v53; // d7
  double v54; // d0
  double v55; // d1
  double v56; // d2
  double v57; // d3
  double v58; // d4
  double v59; // d5
  double v60; // d6
  double v61; // d7
  double v62; // d0
  double v63; // d1
  double v64; // d2
  double v65; // d3
  double v66; // d4
  double v67; // d5
  double v68; // d6
  double v69; // d7
  double v70; // d0
  double v71; // d1
  double v72; // d2
  double v73; // d3
  double v74; // d4
  double v75; // d5
  double v76; // d6
  double v77; // d7
  unsigned int v78; // w21
  double v79; // d0
  double v80; // d1
  double v81; // d2
  double v82; // d3
  double v83; // d4
  double v84; // d5
  double v85; // d6
  double v86; // d7
  double v87; // d0
  double v88; // d1
  double v89; // d2
  double v90; // d3
  double v91; // d4
  double v92; // d5
  double v93; // d6
  double v94; // d7
  unsigned int v95; // w21
  __int64 v96; // [xsp+58h] [xbp+58h] BYREF

  v10 = a1 + 112;
  v11 = 0;
  v96 = 0;
  sprd_log(1u, "[kbc]kbc_image_verify_v2() enter.\n", a2, a3, a4, a5, a6, a7, a8, a9);
  avb_ops_init_kbc();
  while ( 1 )
  {
    if ( *(_QWORD *)(v10 - 112) == 0 )
    {
      sprd_log(1u, "[kbc]invalid image [%d]\n", v12, v13, v14, v15, v16, v17, v18, v19, v11);
      goto LABEL_4;
    }
    sprd_log(
      1u,
      "[kbc]call mem map:ns addr = %p map len = 0x%x \n",
      v12,
      v13,
      v14,
      v15,
      v16,
      v17,
      v18,
      v19,
      *(_QWORD *)(v10 - 112),
      *(unsigned int *)(v10 - 100));
    v37 = sprd_iomap(
            (__int64)"sprdsec",
            *(_QWORD *)(v10 - 112),
            (*(_DWORD *)(v10 - 100) & 0xFFFFF000) + 4096,
            0x30u,
            (__int64)&v96);
    if ( v37 != 0 )
      break;
    sprd_log(1u, "[kbc]after map:pAddr = %p\n", v38, v39, v40, v41, v42, v43, v44, v45, v96);
    dump_hex((__int64)"pAddr:", v96, 16, v46, v47, v48, v49, v50, v51, v52, v53);
    avb_userdata_set(v96, v10 - 96, *(_DWORD *)(a1 + 452), v54, v55, v56, v57, v58, v59, v60, v61);
    sprd_log(1u, "[kbc]start verify... \n", v62, v63, v64, v65, v66, v67, v68, v69);
    v78 = avb_check_kbc_image(v10 - 32, v70, v71, v72, v73, v74, v75, v76, v77);
    sprd_log(1u, "[kbc]ret = %d\n", v79, v80, v81, v82, v83, v84, v85, v86, v78);
    if ( v78 != 0 )
    {
      sprd_log(1u, "[kbc]kbc verify failed!\n", v87, v88, v89, v90, v91, v92, v93, v94);
      thread_sleep_ms(0x3E8u);
      while ( 1 )
        ;
    }
    v95 = sprd_iounmap(v96);
    if ( v95 != 0 )
    {
      sprd_log(1u, "[kbc]can not unmap virt addr, ret = %d \n", v12, v13, v14, v15, v16, v17, v18, v19, v95);
      return (int)v95;
    }
LABEL_4:
    ++v11;
    v10 += 112;
    if ( v11 == 4 )
    {
      sprd_log(1u, "[kbc]verify success. \n", v12, v13, v14, v15, v16, v17, v18, v19);
      dump_hex((__int64)"version:", -536460624, 56, v20, v21, v22, v23, v24, v25, v26, v27);
      kbc_v2_dump_version(-536460624, v28, v29, v30, v31, v32, v33, v34, v35);
      return 0;
    }
  }
  sprd_log(1u, "[kbc]can not map, ret = %d \n", v38, v39, v40, v41, v42, v43, v44, v45, v37);
  return (int)v37;
}

/* ===== spi_sync_wrap @ 0x940490CC size 24 ===== */
__int64 __fastcall spi_sync_wrap(__int64 a1)
{
  return (*(__int64 (**)(void))(a1 + 48))();
}

/* ===== spi_setup_wrap @ 0x940490E4 size 24 ===== */
__int64 __fastcall spi_setup_wrap(__int64 a1)
{
  return (*(__int64 (**)(void))(a1 + 40))();
}

/* ===== fp_spi_get_ctrl @ 0x940490FC size 20 ===== */
__int64 __fastcall fp_spi_get_ctrl(int a1)
{
  return ((__int64)a1 << 6) - 536622672;
}

/* ===== spi_wait_done @ 0x94049110 size 32 ===== */
__int64 __fastcall spi_wait_done(__int64 a1)
{
  if ( (*(_DWORD *)(**(_QWORD **)(a1 + 56) + 24LL) & 0x1FF) == *(_DWORD *)(**(_QWORD **)(a1 + 56) + 60LL) )
    return 0;
  else
    return 0xFFFFFFFFLL;
}

/* ===== spi_set_cs @ 0x94049130 size 52 ===== */
__int64 __fastcall spi_set_cs(__int64 *a1, __int64 a2, unsigned int a3)
{
  __int64 v3; // x1

  v3 = *a1;
  *(_DWORD *)(v3 + 24) &= 0xFFFFFC00;
  *(_DWORD *)(v3 + 24) |= a3 & 0x1FF;
  *(_DWORD *)(v3 + 24) |= 0x200u;
  return a3;
}

/* ===== spi_fifo_write8 @ 0x94049164 size 48 ===== */
__int64 __fastcall spi_fifo_write8(_BYTE **a1, __int64 a2, unsigned int a3)
{
  __int64 v3; // x3
  char v4; // w5

  if ( a3 == 0 )
    return 0;
  v3 = 0;
  do
  {
    v4 = *(_BYTE *)(a2 + v3++);
    **a1 = v4;
  }
  while ( a3 > (unsigned int)v3 );
  return a3;
}

/* ===== spi_fifo_write16 @ 0x94049194 size 48 ===== */
__int64 __fastcall spi_fifo_write16(_WORD **a1, __int64 a2, unsigned int a3)
{
  _WORD *v3; // x0
  __int64 v4; // x3
  __int16 v5; // w4

  if ( a3 == 0 )
    return 0;
  v3 = *a1;
  v4 = 0;
  do
  {
    v5 = *(_WORD *)(a2 + 2 * v4++);
    *v3 = v5;
  }
  while ( a3 > (unsigned int)v4 );
  return 2 * a3;
}

/* ===== spi_fifo_write32 @ 0x940491C4 size 48 ===== */
__int64 __fastcall spi_fifo_write32(_DWORD **a1, __int64 a2, unsigned int a3)
{
  _DWORD *v3; // x0
  __int64 v4; // x3
  int v5; // w4

  if ( a3 == 0 )
    return 0;
  v3 = *a1;
  v4 = 0;
  do
  {
    v5 = *(_DWORD *)(a2 + 4 * v4++);
    *v3 = v5;
  }
  while ( a3 > (unsigned int)v4 );
  return 4 * a3;
}

/* ===== spi_fifo_read8 @ 0x940491F4 size 48 ===== */
__int64 __fastcall spi_fifo_read8(_BYTE **a1, __int64 a2, unsigned int a3)
{
  __int64 v3; // x3

  if ( a3 == 0 )
    return 0;
  v3 = 0;
  do
    *(_BYTE *)(a2 + v3++) = **a1;
  while ( a3 > (unsigned int)v3 );
  return a3;
}

/* ===== spi_fifo_read16 @ 0x94049224 size 48 ===== */
__int64 __fastcall spi_fifo_read16(_WORD **a1, __int64 a2, unsigned int a3)
{
  _WORD *v3; // x0
  __int64 v4; // x3

  if ( a3 == 0 )
    return 0;
  v3 = *a1;
  v4 = 0;
  do
    *(_WORD *)(a2 + 2 * v4++) = *v3;
  while ( a3 > (unsigned int)v4 );
  return 2 * a3;
}

/* ===== spi_fifo_read32 @ 0x94049254 size 48 ===== */
__int64 __fastcall spi_fifo_read32(_DWORD **a1, __int64 a2, unsigned int a3)
{
  _DWORD *v3; // x0
  __int64 v4; // x3

  if ( a3 == 0 )
    return 0;
  v3 = *a1;
  v4 = 0;
  do
    *(_DWORD *)(a2 + 4 * v4++) = *v3;
  while ( a3 > (unsigned int)v4 );
  return 4 * a3;
}

/* ===== spi_set_clk @ 0x94049284 size 56 ===== */
__int64 __fastcall spi_set_clk(__int64 result, int a2)
{
  __int64 v2; // x3
  int v3; // w2
  int v4; // w2

  v2 = **(_QWORD **)(result + 56);
  v3 = *(_DWORD *)(v2 + 8);
  if ( a2 != 0 )
  {
    result = (unsigned int)(1 << (*(_BYTE *)(result + 4) + 8));
    v4 = v3 & ~(_DWORD)result;
  }
  else
  {
    v4 = v3 | 0xF00;
  }
  *(_DWORD *)(v2 + 8) = v4;
  return result;
}

/* ===== spi_transfer @ 0x940492BC size 324 ===== */
__int64 __fastcall spi_transfer(__int64 a1, __int64 *a2)
{
  __int64 v2; // x19
  unsigned int v4; // w21
  unsigned int v6; // w22
  __int64 v7; // x1
  __int64 (__fastcall *v8)(__int64, __int64, __int64); // x3
  unsigned int (__fastcall *v9)(__int64); // x2
  __int64 v11; // x1
  __int64 (__fastcall *v12)(__int64, __int64, _QWORD); // x3

  v2 = *(_QWORD *)(a1 + 56);
  v4 = *(_DWORD *)(v2 + 12);
  v6 = 0;
  while ( v4 > 0x1F )
  {
    v7 = *a2;
    v8 = *(__int64 (__fastcall **)(__int64, __int64, __int64))(v2 + 56);
    v4 -= 32;
    *(_DWORD *)(*(_QWORD *)v2 + 88LL) = 32;
    v6 += v8(v2, v7, 32);
    v9 = *(unsigned int (__fastcall **)(__int64))(v2 + 88);
    *a2 += 32;
    if ( v9(a1) != 0 )
      return 0xFFFFFFFFLL;
    if ( *(_DWORD *)(v2 + 40) != 2 )
    {
      (*(void (__fastcall **)(__int64, __int64))(v2 + 48))(v2, a2[1]);
      a2[1] += 32;
    }
  }
  if ( v4 != 0 )
  {
    v11 = *a2;
    v12 = *(__int64 (__fastcall **)(__int64, __int64, _QWORD))(v2 + 56);
    *(_DWORD *)(*(_QWORD *)v2 + 88LL) = v4;
    v6 += v12(v2, v11, v4);
    if ( (*(unsigned int (__fastcall **)(__int64))(v2 + 88))(a1) != 0 )
      return 0xFFFFFFFFLL;
    if ( *(_DWORD *)(v2 + 40) != 2 )
      (*(void (__fastcall **)(__int64, __int64, _QWORD))(v2 + 48))(v2, a2[1], v4);
  }
  *(_DWORD *)(*(_QWORD *)v2 + 12LL) &= 0xFFFFCFFF;
  return v6;
}

/* ===== spi_config @ 0x94049400 size 320 ===== */
__int64 __fastcall spi_config(unsigned __int64 a1, __int64 *a2)
{
  int v2; // w2
  __int64 v3; // x3
  _DWORD *v5; // x2
  __int64 v6; // x5
  __int64 v7; // x1
  __int64 v8; // x0
  int v9; // w2
  int v10; // w2

  v2 = *((unsigned __int8 *)a2 + 21);
  v3 = *(_QWORD *)(a1 + 56);
  if ( *((_BYTE *)a2 + 21) == 0 )
    v2 = *(unsigned __int8 *)(a1 + 6);
  switch ( v2 )
  {
    case 16:
      v10 = *((_DWORD *)a2 + 4);
      *(_QWORD *)(v3 + 48) = spi_fifo_read16;
      *(_DWORD *)(v3 + 12) = (unsigned int)(v10 + 1) >> 1;
      *(_QWORD *)(v3 + 56) = spi_fifo_write16;
      break;
    case 32:
      v9 = *((_DWORD *)a2 + 4);
      *(_QWORD *)(v3 + 48) = spi_fifo_read32;
      *(_DWORD *)(v3 + 12) = (unsigned int)(v9 + 3) >> 2;
      *(_QWORD *)(v3 + 56) = spi_fifo_write32;
      break;
    case 8:
      *(_DWORD *)(v3 + 12) = *((_DWORD *)a2 + 4);
      *(_QWORD *)(v3 + 48) = spi_fifo_read8;
      *(_QWORD *)(v3 + 56) = spi_fifo_write8;
      break;
    default:
      return 0xFFFFFFFFLL;
  }
  v5 = *(_DWORD **)v3;
  v6 = *a2;
  v7 = a2[1];
  v5[2] = (4 * (*(_BYTE *)(a1 + 6) & 0x1F)) | *(_DWORD *)(*(_QWORD *)v3 + 8LL);
  LODWORD(a1) = v5[3] & 0xFFFFCFFF;
  if ( v6 != 0 )
    LODWORD(a1) = a1 | 0x2000;
  if ( v7 != 0 )
    a1 = (unsigned int)a1 | 0x1000;
  else
    a1 = (unsigned int)a1;
  v5[3] = a1;
  v8 = (a1 >> 12) & 3;
  *(_DWORD *)(v3 + 40) = v8;
  *(_QWORD *)(v3 + 88) = spi_wait_tx_done;
  if ( (_DWORD)v8 == 1 )
  {
    *(_QWORD *)(v3 + 56) = spi_set_cs;
    *(_QWORD *)(v3 + 88) = spi_wait_done;
  }
  v5[18] = 1;
  v5[18] = 0;
  v5[9] = 256;
  return 0;
}

/* ===== spi_sync @ 0x94049540 size 140 ===== */
__int64 __fastcall spi_sync(__int64 a1, __int64 a2)
{
  __int64 v3; // x20
  int v5; // w22

  v3 = *(_QWORD *)(a1 + 56);
  clk_enable(*(_DWORD *)(a1 + 28));
  (*(void (__fastcall **)(__int64, __int64))(v3 + 64))(a1, a2);
  (*(void (__fastcall **)(__int64, __int64))(v3 + 72))(a1, 1);
  v5 = (*(__int64 (__fastcall **)(__int64, __int64))(v3 + 80))(a1, a2);
  (*(void (__fastcall **)(__int64, _QWORD))(v3 + 72))(a1, 0);
  clk_disable(*(_DWORD *)(a1 + 28));
  if ( v5 == *(_DWORD *)(a2 + 16) )
    return 0;
  else
    return 0xFFFFFFFFLL;
}

/* ===== spi_setup @ 0x940495CC size 248 ===== */
__int64 __fastcall spi_setup(__int64 a1)
{
  __int64 v1; // x19
  int v3; // w0
  bool v4; // zf
  __int64 v5; // x0
  unsigned int v6; // w1
  __int64 v7; // x0
  unsigned int v8; // w3
  __int64 v9; // x2
  _DWORD *v10; // x19

  v1 = *(_QWORD *)(a1 + 56);
  *(_DWORD *)(v1 + 16) = *(_DWORD *)a1;
  *(_QWORD *)(v1 + 32) = 4LL * (*(_BYTE *)(a1 + 6) & 0x1F);
  v3 = *(_BYTE *)(a1 + 5) & 3;
  if ( v3 == 2 )
  {
    *(_QWORD *)(v1 + 24) |= 0x2002uLL;
  }
  else if ( v3 == 3 )
  {
    *(_QWORD *)(v1 + 24) |= 0x2001uLL;
  }
  else
  {
    v4 = v3 == 1;
    v5 = *(_QWORD *)(v1 + 24);
    if ( v4 )
      *(_QWORD *)(v1 + 24) = v5 | 1;
    else
      *(_QWORD *)(v1 + 24) = v5 | 2;
  }
  clk_enable(*(_DWORD *)(a1 + 28));
  v6 = *(_DWORD *)(v1 + 20);
  v7 = *(_QWORD *)(v1 + 32);
  v8 = 2 * *(_DWORD *)(v1 + 16);
  v9 = *(_QWORD *)(v1 + 24);
  v10 = *(_DWORD **)v1;
  LODWORD(v9) = v7 | v9;
  LODWORD(v7) = *(_DWORD *)(a1 + 28);
  v10[2] = v9 | 0xF00;
  v10[1] = v6 / v8 - 1;
  v10[3] = 0;
  v10[4] = 0;
  v10[6] = 0;
  v10[7] = 0;
  v10[8] = 0;
  v10[18] = 1;
  v10[18] = 0;
  clk_disable(v7);
  return 0;
}

/* ===== spi_wait_tx_done @ 0x940496C4 size 92 ===== */
__int64 __fastcall spi_wait_tx_done(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 *v9; // x1
  int v10; // w0
  __int64 v11; // x2

  v9 = *(__int64 **)(a1 + 56);
  v10 = 16711681;
  v11 = *v9;
  do
  {
    --v10;
    if ( (*(_DWORD *)(v11 + 40) & 0x100) != 0 )
    {
      *(_DWORD *)(v11 + 36) = 256;
      return 0;
    }
  }
  while ( v10 != 0 );
  sprd_log(0, "SPI error, spi send timeout = %x!\n", a2, a3, a4, a5, a6, a7, a8, a9);
  return 0xFFFFFFFFLL;
}

/* ===== sprd_spi_bus_init @ 0x94049720 size 252 ===== */
__int64 sprd_spi_bus_init()
{
  unsigned int v0; // w20
  __int64 v1; // x19
  __int64 result; // x0
  __int64 v3; // x5
  __int64 v4; // x4
  __int64 v5; // x1
  __int64 v6; // x0
  double v7; // d0
  double v8; // d1
  double v9; // d2
  double v10; // d3
  double v11; // d4
  double v12; // d5
  double v13; // d6
  double v14; // d7

  v0 = 0;
  v1 = -536622664;
  do
  {
    result = malloc(0x60u);
    v3 = result;
    v4 = result;
    if ( result != 0 )
    {
      *(_QWORD *)(result + 64) = spi_config;
      *(_QWORD *)(result + 72) = spi_set_clk;
      *(_QWORD *)(result + 80) = spi_transfer;
      *(_DWORD *)(result + 20) = *(_DWORD *)(v1 + 16);
      *(_QWORD *)(result + 24) = 0;
      *(_WORD *)(v1 + 26) = 4;
      v5 = *(_QWORD *)(v1 + 8);
      *(_QWORD *)(v1 + 32) = spi_setup;
      v6 = *(_QWORD *)v1;
      *(_WORD *)(v1 + 24) = v0;
      *(_QWORD *)(v1 + 40) = spi_sync;
      *(_QWORD *)(v1 + 48) = v3;
      if ( (unsigned int)sprd_iomap(v6, v5, 0x1000u, 2u, v4) != 0 )
        result = sprd_log(2u, "%s: mem map failed %d\n", v7, v8, v9, v10, v11, v12, v13, v14, "sprd_spi_bus_init");
      else
        result = sprd_log(2u, "spi%d init ok\n", v7, v8, v9, v10, v11, v12, v13, v14, v0);
    }
    ++v0;
    v1 += 64;
  }
  while ( v0 != 3 );
  return result;
}

/* ===== sprd_timer_init @ 0x9404981C size 80 ===== */
bool sprd_timer_init()
{
  return (unsigned int)sprd_iomap((__int64)"sprd_timer", 1076035584, 0x10000u, 2u, (__int64)&qword_94077F28) != 0;
}

/* ===== nullsub_7 @ 0x9404986C size 4 ===== */
void nullsub_7()
{
  ;
}

/* ===== nullsub_8 @ 0x94049870 size 4 ===== */
void nullsub_8()
{
  ;
}

/* ===== pmm_early_alloc @ 0x94049874 size 40 ===== */
unsigned __int64 __fastcall pmm_early_alloc(__int64 a1)
{
  unsigned __int64 v1; // x1
  unsigned __int64 result; // x0

  v1 = (a1 + 7) & 0xFFFFFFFFFFFFFFF8LL;
  result = (MEMORY[0xFFFFFFFFE003CA78] + 7LL) & 0xFFFFFFFFFFFFFFF8LL;
  MEMORY[0xFFFFFFFFE003CA78] = v1 + result;
  return result;
}

/* ===== pmm_query_page @ 0x9404989C size 100 ===== */
__int64 __fastcall pmm_query_page(unsigned __int64 a1)
{
  __int64 v1; // x1
  unsigned __int64 v2; // x3

  v1 = -536622408;
  if ( &qword_9405CAB8 == (__int64 *)-536622408LL )
    return 0;
  while ( 1 )
  {
    v2 = *(_QWORD *)(v1 + 32);
    if ( v2 <= a1 && a1 <= v2 + *(_QWORD *)(v1 + 40) - 1 )
      break;
    v1 = *(_QWORD *)(v1 + 8);
    if ( (__int64 *)v1 == &qword_9405CAB8 )
      return 0;
  }
  return *(_QWORD *)(v1 + 56) + 24 * ((a1 - v2) >> 12);
}

/* ===== pmm_add_arena @ 0x94049900 size 844 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall pmm_add_arena(__int64 a1)
{
  __int64 v1; // x30
  unsigned __int64 v3; // x22
  __int64 v4; // x0
  unsigned int v5; // w2
  unsigned __int64 v6; // x22
  unsigned __int64 v7; // x0
  _QWORD *v8; // x0
  _QWORD *v9; // x1
  __int64 v10; // x4
  _QWORD *v11; // x3
  __int64 v13; // x0
  unsigned int v14; // w1
  __int64 v15; // x2
  unsigned int v16; // w3
  __int64 v17; // x30
  __int64 v18; // x21
  unsigned int v19; // w23
  __int64 v20; // x20
  unsigned __int64 v21; // x19
  unsigned int v22; // w22
  __int64 *v23; // x9
  __int64 v24; // x6
  unsigned __int64 v25; // x1
  unsigned __int64 v26; // x7
  unsigned __int64 v27; // x8
  unsigned __int64 v28; // x7
  unsigned __int64 v29; // x3
  __int64 v30; // x5
  __int64 v31; // x3
  __int64 v32; // x4
  __int64 v33; // x0
  __int64 *v34; // x2
  __int64 v35; // x0

  if ( (*(_QWORD *)(a1 + 32) & 0xFFFLL) != 0 )
  {
    panic(
      v1,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/vm/pmm.c",
      83,
      "IS_PAGE_ALIGNED(arena->base)");
    goto LABEL_17;
  }
  v3 = *(_QWORD *)(a1 + 40);
  if ( (v3 & 0xFFF) != 0 )
  {
LABEL_17:
    panic(
      v1,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/vm/pmm.c",
      84,
      "IS_PAGE_ALIGNED(arena->size)");
    goto LABEL_18;
  }
  if ( v3 != 0 )
  {
    v4 = -536622408;
    if ( &qword_9405CAB8 != (__int64 *)-536622408LL )
    {
      v5 = *(_DWORD *)(a1 + 28);
      if ( MEMORY[0xFFFFFFFFE003CAD4] > v5 )
      {
LABEL_15:
        *(_QWORD *)a1 = *(_QWORD *)v4;
        *(_QWORD *)(a1 + 8) = v4;
        *(_QWORD *)(*(_QWORD *)v4 + 8LL) = a1;
        *(_QWORD *)v4 = a1;
        goto LABEL_10;
      }
      while ( 1 )
      {
        v4 = *(_QWORD *)(v4 + 8);
        if ( (__int64 *)v4 == &qword_9405CAB8 )
          break;
        if ( v5 < *(_DWORD *)(v4 + 28) )
          goto LABEL_15;
      }
    }
    *(_QWORD *)a1 = -536622408;
    *(_QWORD *)(a1 + 8) = &qword_9405CAB8;
    qword_9405CAB8 = a1;
    MEMORY[0xFFFFFFFFE003CAC0] = a1;
LABEL_10:
    v6 = v3 >> 12;
    *(_QWORD *)(a1 + 48) = 0;
    *(_QWORD *)(a1 + 72) = a1 + 64;
    *(_QWORD *)(a1 + 64) = a1 + 64;
    v7 = pmm_early_alloc(24 * v6);
    *(_QWORD *)(a1 + 56) = v7;
    memset(v7, 0, 24 * v6);
    if ( v6 != 0 )
    {
      v8 = *(_QWORD **)(a1 + 56);
      v9 = *(_QWORD **)(a1 + 64);
      v10 = *(_QWORD *)(a1 + 48);
      v11 = &v8[3 * v6];
      do
      {
        *v8 = v9;
        v9 = v8;
        v8[1] = a1 + 64;
        *(_QWORD *)(*(_QWORD *)(a1 + 64) + 8LL) = v8;
        *(_QWORD *)(a1 + 64) = v8;
        v8 += 3;
      }
      while ( v8 != v11 );
      *(_QWORD *)(a1 + 48) = v6 + v10;
    }
    return 0;
  }
LABEL_18:
  v13 = panic(v1, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/pmm.c", 85, "arena->size > 0");
  v16 = 0;
  v18 = v17;
  if ( v14 != 0 )
  {
    v19 = v14;
    v20 = v15;
    v21 = v13 & 0xFFFFFFFFFFFFF000LL;
    v22 = 0;
    mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
    v23 = &qword_9405CAB8;
    v24 = -536622408;
    if ( &qword_9405CAB8 != (__int64 *)-536622408LL )
    {
      while ( 1 )
      {
        if ( v19 > v22 )
        {
          v25 = *(_QWORD *)(v24 + 32);
          if ( v21 >= v25 )
          {
            v26 = *(_QWORD *)(v24 + 40);
            v27 = v25 + v26 - 1;
            if ( v21 <= v27 )
            {
              v28 = v26 >> 12;
              v29 = (v21 - v25) >> 12;
              if ( v28 > v29 )
              {
                v30 = *(_QWORD *)(v24 + 56);
                goto LABEL_26;
              }
LABEL_32:
              v33 = panic(
                      v18,
                      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                      "external/lk/kernel/vm/pmm.c",
                      179,
                      "index < a->size / PAGE_SIZE");
LABEL_33:
              if ( v34 != nullptr )
              {
                while ( 1 )
                {
                  *v34 = v33;
                  ++v22;
                  v21 += 4096LL;
                  v35 = *(_QWORD *)(v24 + 48) - 1LL;
                  *(_QWORD *)(*(_QWORD *)(v30 + v31) + 8LL) = v34;
                  *(_QWORD *)(v30 + v31) = 0;
                  *(_BYTE *)(v32 + 16) |= 1u;
                  *(_QWORD *)(v30 + v31) = *(_QWORD *)v20;
                  *(_QWORD *)(v32 + 8) = v20;
                  *(_QWORD *)(*(_QWORD *)v20 + 8LL) = v32;
                  *(_QWORD *)v20 = v32;
                  *(_QWORD *)(v24 + 48) = v35;
                  if ( v19 <= v22 || v21 < v25 || v21 > v27 )
                    break;
                  v29 = (v21 - v25) >> 12;
                  if ( v29 >= v28 )
                    goto LABEL_32;
LABEL_26:
                  v31 = 24 * v29;
                  v32 = v30 + v31;
                  if ( (*(_BYTE *)(v30 + v31 + 16) & 1) != 0 )
                    break;
                  v33 = *(_QWORD *)(v30 + v31);
                  v34 = *(__int64 **)(v32 + 8);
                  if ( v33 == 0 )
                    goto LABEL_33;
                }
              }
              else
              {
                panic(
                  v18,
                  "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                  "external/lk/kernel/vm/pmm.c",
                  187,
                  "list_in_list(&page->node)");
              }
            }
          }
        }
        if ( v19 != v22 )
        {
          v24 = *(_QWORD *)(v24 + 8);
          if ( (__int64 *)v24 != v23 )
            continue;
        }
        break;
      }
    }
    mutex_release((__int64)"xtum");
    return v22;
  }
  return v16;
}

/* ===== pmm_free_page_list @ 0x94049C4C size 296 ===== */
__int64 __fastcall pmm_free_page_list(__int64 a1)
{
  __int64 v1; // x30
  unsigned int v2; // w21
  __int64 v4; // x19
  unsigned __int64 v5; // x3
  _QWORD *v6; // x0
  char v7; // w6
  __int64 v8; // x0
  unsigned __int64 v9; // x1
  __int64 v10; // x1
  __int64 v12; // x0

  v2 = 0;
  v4 = v1;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
LABEL_2:
  v5 = *(_QWORD *)(a1 + 8);
  if ( a1 == v5 )
  {
LABEL_10:
    mutex_release((__int64)"xtum");
    return v2;
  }
  else
  {
    while ( 1 )
    {
      v6 = *(_QWORD **)(v5 + 8);
      *v6 = *(_QWORD *)v5;
      *(_QWORD *)(*(_QWORD *)v5 + 8LL) = v6;
      *(_QWORD *)(v5 + 8) = 0;
      v7 = *(_BYTE *)(v5 + 16);
      *(_QWORD *)v5 = 0;
      if ( (v7 & 1) == 0 )
        break;
      v8 = -536622408;
      if ( &qword_9405CAB8 == (__int64 *)-536622408LL )
        goto LABEL_2;
      while ( 1 )
      {
        v9 = *(_QWORD *)(v8 + 56);
        if ( v9 <= v5 && v5 < 24LL * (*(_QWORD *)(v8 + 40) >> 12) + v9 )
          break;
        v8 = *(_QWORD *)(v8 + 8);
        if ( (__int64 *)v8 == &qword_9405CAB8 )
          goto LABEL_2;
      }
      *(_BYTE *)(v5 + 16) = v7 & 0xFE;
      v10 = *(_QWORD *)(v8 + 48);
      ++v2;
      *(_QWORD *)(v5 + 8) = *(_QWORD *)(v8 + 72);
      *(_QWORD *)v5 = v8 + 64;
      **(_QWORD **)(v8 + 72) = v5;
      *(_QWORD *)(v8 + 72) = v5;
      *(_QWORD *)(v8 + 48) = v10 + 1;
      v5 = *(_QWORD *)(a1 + 8);
      if ( a1 == v5 )
        goto LABEL_10;
    }
    v12 = panic(
            v4,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            "external/lk/kernel/vm/pmm.c",
            219,
            "page->flags & VM_PAGE_FLAG_NONFREE");
    return pmm_free_page_list_init(v12);
  }
}

/* ===== pmm_free_page_list_init @ 0x94049D74 size 48 ===== */
__int64 __fastcall pmm_free_page_list_init(_QWORD *a1)
{
  _QWORD v2[2]; // [xsp+10h] [xbp+10h] BYREF

  a1[1] = v2;
  *a1 = v2;
  v2[0] = a1;
  v2[1] = a1;
  return pmm_free_page_list((__int64)v2);
}

/* ===== pmm_alloc_pages @ 0x94049DA4 size 688 ===== */
__int64 __fastcall pmm_alloc_pages(unsigned int a1, unsigned __int8 a2, _QWORD *a3, __int64 a4)
{
  __int64 v4; // x30
  __int64 v5; // x19
  char v6; // w24
  __int64 *v10; // x0
  __int64 v11; // x2
  __int64 v12; // x9
  int v13; // w13
  __int64 v14; // x12
  int v15; // w10
  unsigned __int64 v16; // x7
  unsigned __int64 v17; // x1
  unsigned __int64 v18; // x3
  unsigned __int64 v19; // x3
  unsigned __int64 v20; // x5
  __int64 v21; // x8
  int v22; // w15
  unsigned int v23; // w14
  __int64 v24; // x11
  int v25; // w16
  __int64 i; // x1
  int v27; // w4
  __int64 v28; // x1
  __int64 v29; // x4
  __int64 v30; // x0
  __int64 v31; // x4
  __int64 v32; // x5
  __int64 v33; // x0
  char v34; // w3
  _QWORD *v35; // x3

  v5 = v4;
  v6 = a2;
  if ( a1 == 0 )
    return 0;
  if ( a2 <= 0xBu )
    v6 = 12;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  v10 = &qword_9405CAB8;
  v11 = -536622408;
  if ( &qword_9405CAB8 == (__int64 *)-536622408LL )
  {
LABEL_27:
    mutex_release((__int64)"xtum");
    return 0;
  }
  v12 = 1LL << v6;
  v13 = 1LL << (v6 - 12);
  v14 = -(1LL << v6);
  v15 = -(1 << (v6 - 12));
  while ( 1 )
  {
    if ( (*(_DWORD *)(v11 + 24) & 1) != 0 )
    {
      v16 = *(_QWORD *)(v11 + 32);
      v17 = (v16 - 1 + v12) & v14;
      if ( v16 <= v17 )
      {
        v18 = *(_QWORD *)(v11 + 40);
        if ( v17 <= v16 + v18 - 1 )
        {
          v19 = v18 >> 12;
          v20 = (v17 - v16) >> 12;
          v21 = (unsigned int)v20;
          v22 = v20;
          if ( v19 > (unsigned int)v20 )
          {
            v23 = a1 + v20;
            if ( v19 >= a1 + (unsigned int)v20 )
              break;
          }
        }
      }
    }
LABEL_26:
    v11 = *(_QWORD *)(v11 + 8);
    if ( (__int64 *)v11 == v10 )
      goto LABEL_27;
  }
  v24 = *(_QWORD *)(v11 + 56);
  v25 = v13 - v20;
  for ( i = v24 + 24LL * (unsigned int)v20; (*(_BYTE *)(i + 16) & 1) != 0; i = v24 + 24LL * (unsigned int)v20 )
  {
    v27 = 0;
LABEL_29:
    LODWORD(v20) = ((v20 + v25 + v27) & v15) + v22;
    v21 = (unsigned int)v20;
    if ( (unsigned int)v20 >= v19 )
      goto LABEL_26;
    v23 = v20 + a1;
    if ( v19 < (unsigned int)v20 + a1 )
      goto LABEL_26;
  }
  v27 = 0;
  while ( 1 )
  {
    ++v27;
    i += 24;
    if ( v27 == a1 )
      break;
    if ( (*(_BYTE *)(i + 16) & 1) != 0 )
      goto LABEL_29;
  }
  if ( v23 <= (unsigned int)v20 )
    goto LABEL_34;
  v28 = v24 + 24LL * (unsigned int)v20;
  if ( (*(_BYTE *)(v28 + 16) & 1) == 0 )
  {
    v29 = (unsigned int)(v20 + 1);
    v30 = v23 - 1 - (unsigned int)v20 + v29;
    v31 = v24 + 24 * v29;
    v32 = v24 + 24 * v30;
    while ( 1 )
    {
      v35 = *(_QWORD **)(v28 + 8);
      if ( *(_QWORD *)v28 == 0 && v35 == nullptr )
        break;
      *v35 = *(_QWORD *)v28;
      v33 = *(_QWORD *)(v11 + 48) - 1LL;
      *(_QWORD *)(*(_QWORD *)v28 + 8LL) = v35;
      *(_QWORD *)(v28 + 8) = 0;
      v34 = *(_BYTE *)(v28 + 16);
      *(_QWORD *)v28 = 0;
      *(_BYTE *)(v28 + 16) = v34 | 1;
      *(_QWORD *)(v11 + 48) = v33;
      if ( a4 != 0 )
      {
        *(_QWORD *)v28 = *(_QWORD *)a4;
        *(_QWORD *)(v28 + 8) = a4;
        *(_QWORD *)(*(_QWORD *)a4 + 8LL) = v28;
        *(_QWORD *)a4 = v28;
      }
      if ( v31 == v32 )
        goto LABEL_34;
      v28 = v31;
      v31 += 24;
      if ( (*(_BYTE *)(v28 + 16) & 1) != 0 )
        goto LABEL_33;
    }
    v10 = (__int64 *)panic(
                       v5,
                       "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                       "external/lk/kernel/vm/pmm.c",
                       318,
                       "list_in_list(&p->node)");
    goto LABEL_26;
  }
LABEL_33:
  panic(
    v5,
    "DEBUG ASSERT FAILED at (%s:%d): %s\n",
    "external/lk/kernel/vm/pmm.c",
    317,
    "!(p->flags & VM_PAGE_FLAG_NONFREE)");
LABEL_34:
  if ( a3 != nullptr )
    *a3 = v16 + (v21 << 12);
  mutex_release((__int64)"xtum");
  return a1;
}

/* ===== pmm_alloc_page @ 0x9404A054 size 56 ===== */
__int64 __fastcall pmm_alloc_page(unsigned int a1, __int64 a2)
{
  __int64 v3; // [xsp+18h] [xbp+18h] BYREF

  if ( (unsigned int)pmm_alloc_pages(a1, 0xCu, &v3, a2) != 0 )
    return pmm_virt_to_phys(v3);
  else
    return 0;
}

/* ===== pmm_free_range @ 0x9404A08C size 252 ===== */
__int64 __fastcall pmm_free_range(__int64 result, __int64 a2)
{
  __int64 v2; // x30
  unsigned __int64 v3; // x20
  unsigned __int64 v4; // x21
  __int64 v5; // x25
  unsigned __int64 v6; // x19
  __int64 v7; // x30
  __int64 v8; // [xsp+8h] [xbp-8h]
  int v9; // [xsp+64h] [xbp+54h] BYREF
  __int64 v10; // [xsp+68h] [xbp+58h] BYREF
  _QWORD v11[2]; // [xsp+70h] [xbp+60h] BYREF

  while ( 1 )
  {
    v3 = (a2 + 4095 + (result & 0xFFF)) & 0xFFFFFFFFFFFFF000LL;
    v11[1] = v11;
    v4 = result & 0xFFFFFFFFFFFFF000LL;
    v11[0] = v11;
    if ( v3 == 0 )
      break;
    v5 = v2;
    v6 = 0;
    while ( (arch_mmu_query(v6 + v4, &v10, &v9) & 0x80000000) == 0 )
    {
      v6 += 4096LL;
      result = ((__int64 (__fastcall *)(__int64, __int64, _QWORD *))loc_94049A9C)(v10, 1, v11);
      if ( v3 <= v6 )
        return result;
    }
    panic(v5, (const char *)&loc_94058F00, v4);
    v8 = v7;
    pmm_free_range(-536870912, 4063232);
    result = MEMORY[0xFFFFFFFFE003CA70];
    if ( MEMORY[0xFFFFFFFFE003CA78] == MEMORY[0xFFFFFFFFE003CA70] )
      break;
    v2 = v8;
    a2 = MEMORY[0xFFFFFFFFE003CA78] - MEMORY[0xFFFFFFFFE003CA70];
  }
  return result;
}

/* ===== pmm_init @ 0x9404A188 size 104 ===== */
__int64 pmm_init()
{
  __int64 result; // x0
  __int64 v1; // x19
  __int64 v2; // x1

  pmm_init_kernel_aspace();
  result = -536633344;
  v1 = -536633336;
  if ( MEMORY[0xFFFFFFFFE003A010] != 0 )
  {
    do
    {
      while ( 1 )
      {
        result = *(unsigned int *)(v1 + 16);
        if ( (result & 1) == 0 )
          break;
        v1 += 40;
        if ( *(_QWORD *)(v1 + 8) == 0 )
          return result;
      }
      v2 = *(_QWORD *)(v1 + 24);
      v1 += 40;
      result = ((__int64 (__fastcall *)(__int64, __int64))loc_9404A720)(-536460256, v2);
    }
    while ( *(_QWORD *)(v1 + 8) != 0 );
  }
  return result;
}

/* ===== pmm_virt_to_phys @ 0x9404A1F0 size 88 ===== */
__int64 __fastcall pmm_virt_to_phys(unsigned __int64 a1)
{
  __int64 v1; // x1
  __int64 v2; // x2
  unsigned __int64 v3; // x2

  v1 = -536633344;
  v2 = MEMORY[0xFFFFFFFFE003A010];
  if ( MEMORY[0xFFFFFFFFE003A010] == 0 )
    return 0;
  while ( 1 )
  {
    if ( (*(_DWORD *)(v1 + 24) & 1) == 0 )
    {
      v3 = *(_QWORD *)v1 - 1LL + v2;
      if ( *(_QWORD *)v1 <= a1 && a1 <= v3 )
        break;
    }
    v1 += 40;
    v2 = *(_QWORD *)(v1 + 16);
    if ( v2 == 0 )
      return 0;
  }
  return a1 + *(_QWORD *)(v1 + 8) - *(_QWORD *)v1;
}

/* ===== pmm_phys_to_virt @ 0x9404A248 size 44 ===== */
__int64 __fastcall pmm_phys_to_virt(unsigned __int64 a1)
{
  int v1; // w0
  __int64 v2; // x1
  __int64 v4; // [xsp+18h] [xbp+18h] BYREF

  v1 = arch_mmu_query(a1, &v4, nullptr);
  v2 = 0;
  if ( v1 == 0 )
    return v4;
  return v2;
}

/* ===== pmm_init_kernel_aspace @ 0x9404A274 size 108 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 *pmm_init_kernel_aspace()
{
  strlcpy(-536460240, "kernel", 32);
  MEMORY[0xFFFFFFFFE0064458] = -536870912;
  MEMORY[0xFFFFFFFFE0064420] = &qword_9405CAC8;
  MEMORY[0xFFFFFFFFE0064470] = -536460184;
  MEMORY[0xFFFFFFFFE0064460] = 0x20000000;
  MEMORY[0xFFFFFFFFE0064468] = -536460184;
  MEMORY[0xFFFFFFFFE0064428] = -536622392;
  MEMORY[0xFFFFFFFFE003CAC8] = -536460256;
  off_9405CAD0 = (_UNKNOWN *)-536460256LL;
  return &qword_9405CAC8;
}

/* ===== align_down_avail @ 0x9404A2E0 size 20 ===== */
__int64 __fastcall align_down_avail(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  return -a5 & (a1 - 1 + a5);
}

/* ===== vmm_alloc @ 0x9404A2F4 size 1412 ===== */
__int64 __fastcall vmm_alloc(
        __int64 *a1,
        __int64 a2,
        unsigned __int64 a3,
        unsigned __int64 a4,
        unsigned __int8 a5,
        char a6,
        int a7,
        int a8)
{
  __int64 v8; // x19
  __int64 v9; // x30
  __int64 v10; // x24
  unsigned int v14; // w21
  __int64 v18; // x0
  __int64 v19; // x26
  _QWORD *v20; // x28
  __int64 i; // x21
  unsigned __int64 v22; // x27
  __int64 v23; // x1
  __int64 v24; // x3
  unsigned __int64 v25; // x23
  unsigned __int64 v26; // x0
  __int64 result; // x0
  __int64 *v28; // x1
  unsigned __int64 v29; // x1
  unsigned __int64 v30; // x0
  unsigned __int64 v31; // x22
  __int64 *v32; // x0
  unsigned __int64 v33; // x21
  __int64 *v34; // x1
  __int64 v35; // x2
  __int64 v36; // x27
  __int64 v37; // x0
  unsigned __int64 v38; // x27
  __int64 v39; // x1
  unsigned __int64 v40; // x23
  __int64 v41; // x3
  unsigned __int64 v42; // x0
  __int64 *v43; // x1
  __int64 v44; // x23
  unsigned __int64 v45; // x23
  __int64 v46; // x0
  char *v47; // x1
  __int64 v48; // x2
  unsigned __int64 v49; // x3
  __int64 v50; // x30
  char *v51; // x20
  __int64 v52; // x21
  __int64 v53; // x19
  unsigned __int64 v54; // x1
  __int64 v55; // x4
  __int64 v56; // x2
  unsigned __int64 v57; // x0
  __int64 v58; // x2
  __int64 v59; // x19
  __int64 v60; // x0
  __int64 v61; // x1
  __int64 v62; // x2
  __int64 v63; // x3
  __int64 v64; // x4
  __int64 v65; // x5
  __int64 v66; // x6
  __int64 v67; // x7
  __int64 v68; // [xsp+8h] [xbp-48h]
  __int64 v69; // [xsp+10h] [xbp-40h]
  __int64 *v70; // [xsp+18h] [xbp-38h]
  unsigned __int64 v71; // [xsp+38h] [xbp-18h]
  unsigned int v72; // [xsp+4Ch] [xbp-4h] BYREF
  __int64 v73; // [xsp+50h] [xbp+0h] BYREF
  __int64 v74; // [xsp+B8h] [xbp+68h]

  v10 = v9;
  v14 = a5;
  if ( a2 == 0 )
  {
    panic(v9, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 105, "name");
LABEL_54:
    v32 = (__int64 *)panic(
                       v10,
                       "DEBUG ASSERT FAILED at (%s:%d): %s\n",
                       "external/lk/kernel/vm/vmm.c",
                       230,
                       "size > 0 && IS_PAGE_ALIGNED(size)");
    goto LABEL_55;
  }
  v74 = a2;
  v18 = malloc(88);
  v8 = v18;
  if ( v18 == 0 )
    return 0;
  strlcpy(v18 + 16, v74, 32);
  *(_QWORD *)(v8 + 56) = a4;
  *(_QWORD *)(v8 + 64) = a3;
  *(_DWORD *)(v8 + 48) = a7;
  *(_DWORD *)(v8 + 52) = a8;
  *(_QWORD *)(v8 + 80) = v8 + 72;
  *(_QWORD *)(v8 + 72) = v8 + 72;
  if ( (a6 & 1) != 0 )
  {
    if ( a1 != nullptr )
    {
      if ( a3 == 0 )
        goto LABEL_44;
      v29 = a1[7];
      if ( a4 < v29 )
        goto LABEL_44;
      v30 = v29 + a1[8] - 1;
      if ( a4 > v30 )
        goto LABEL_44;
      v31 = a3 - 1 + a4;
      if ( a4 > v31 || v30 < v31 )
        goto LABEL_44;
      a1 += 9;
      v32 = (__int64 *)a1[1];
      if ( a1 != v32 && v32 != nullptr )
      {
        v33 = v32[7];
        if ( v33 <= v31 )
        {
          if ( a1 != v32 )
          {
            while ( 1 )
            {
              if ( a4 > v32[8] - 1 + v33 )
              {
                v34 = (__int64 *)v32[1];
                if ( a1 == v34 || v34 == nullptr || v34[7] > v31 )
                {
                  *(_QWORD *)(v8 + 8) = v34;
                  *(_QWORD *)v8 = v32;
                  *(_QWORD *)v32[1] = v8;
                  v32[1] = v8;
                  return v8;
                }
              }
              v32 = (__int64 *)v32[1];
              if ( a1 == v32 )
                break;
              v33 = v32[7];
            }
          }
          goto LABEL_44;
        }
      }
LABEL_55:
      *(_QWORD *)(v8 + 8) = v32;
      *(_QWORD *)v8 = a1;
      *v32 = v8;
      a1[1] = v8;
      return v8;
    }
    goto LABEL_59;
  }
  if ( a1 == nullptr )
  {
    panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 229, "aspace");
LABEL_59:
    panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 125, "aspace");
    return 0;
  }
  if ( a3 == 0 || (a3 & 0xFFF) != 0 )
    goto LABEL_54;
  v19 = 4096;
  if ( v14 > 0xB )
    v19 = 1LL << v14;
  v20 = a1 + 9;
  i = a1[10];
  if ( a1 + 9 == (__int64 *)i || i == 0 )
  {
    v22 = a1[7];
    v45 = v22 + a1[8];
    if ( v22 == v45 )
      goto LABEL_44;
    v25 = v45 - 1;
    v24 = 128;
  }
  else
  {
    v22 = a1[7];
    v23 = *(_QWORD *)(i + 56);
    if ( v22 == v23 )
      goto LABEL_38;
    v24 = *(unsigned int *)(i + 52);
    v25 = v23 - 1;
  }
  v26 = align_down_avail(v22, 128, v25, v24, v19);
  if ( v26 < v22 )
  {
LABEL_44:
    free(v8);
    return 0;
  }
  if ( v25 > v26 && a3 <= v25 + 1 - v26 )
  {
    if ( v26 != -1 )
    {
      *(_QWORD *)(v8 + 8) = a1[10];
      *(_QWORD *)(v8 + 56) = v26;
      v28 = (__int64 *)a1[10];
      *(_QWORD *)v8 = v20;
      *v28 = v8;
      a1[10] = v8;
      return v8;
    }
    goto LABEL_44;
  }
  for ( i = a1[10]; ; i = *(_QWORD *)(i + 8) )
  {
    while ( 1 )
    {
LABEL_38:
      if ( v20 == (_QWORD *)i )
        goto LABEL_44;
      v35 = *(_QWORD *)(i + 8);
      v36 = *(_QWORD *)(i + 64);
      if ( v20 == (_QWORD *)v35 || v35 == 0 )
        break;
      v37 = *(_QWORD *)(v35 + 56);
      v38 = v36 + *(_QWORD *)(i + 56);
      if ( v38 != v37 )
      {
        v39 = *(unsigned int *)(i + 52);
        v40 = v37 - 1;
        v41 = *(unsigned int *)(v35 + 52);
        goto LABEL_43;
      }
      i = *(_QWORD *)(i + 8);
    }
    v38 = v36 + *(_QWORD *)(i + 56);
    v44 = a1[8] + a1[7];
    if ( v44 == v38 )
      goto LABEL_44;
    v39 = *(unsigned int *)(i + 52);
    v40 = v44 - 1;
    v41 = 128;
LABEL_43:
    v42 = align_down_avail(v38, v39, v40, v41, v19);
    if ( v38 > v42 )
      goto LABEL_44;
    if ( v40 > v42 && a3 <= v40 + 1 - v42 )
      break;
  }
  if ( v42 == -1 )
    goto LABEL_44;
  if ( i != 0 )
  {
    *(_QWORD *)(v8 + 8) = *(_QWORD *)(i + 8);
    *(_QWORD *)(v8 + 56) = v42;
    v43 = *(__int64 **)(i + 8);
    *(_QWORD *)v8 = i;
    *v43 = v8;
    *(_QWORD *)(i + 8) = v8;
    return v8;
  }
  v46 = panic(v10, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 295, "before != NULL");
  v68 = v50;
  v69 = v8;
  v70 = a1;
  v51 = v47;
  v52 = v46;
  v53 = v48;
  if ( (v49 & 0xFFF) != 0 )
  {
    panic(
      v50,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/vm/vmm.c",
      311,
      "IS_PAGE_ALIGNED(vaddr)");
  }
  else if ( (v48 & 0xFFF) == 0 )
  {
    if ( v47 == nullptr )
    {
      v51 = "";
      if ( v48 != 0 )
        goto LABEL_65;
      return 0;
    }
    if ( v48 == 0 )
      return 0;
LABEL_65:
    v54 = *(_QWORD *)(v46 + 56);
    result = 4294967259LL;
    if ( v49 >= v54 )
    {
      v55 = *(_QWORD *)(v52 + 64);
      if ( v49 <= v54 + v55 - 1 )
      {
        v56 = v49 - v54;
        v57 = v49 - v54 + v53;
        if ( v49 - v54 > v57 )
        {
          v57 = -2;
          v53 = -2 - v56;
        }
        v58 = v55 - v56;
        if ( v55 - 1 <= v57 )
          v53 = v58;
        v71 = v49;
        mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
        v72 = 0;
        arch_mmu_query(v71, nullptr, (int *)&v72);
        v59 = vmm_alloc(v52, v51, v53, v71, 0, 1, 1, v72, &v73, v68, v69, v70, 0, a3);
        mutex_release((__int64)"xtum");
        if ( v59 == 0 )
          return 4294967291LL;
        return 0;
      }
    }
    return result;
  }
  v60 = panic(
          v50,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          "external/lk/kernel/vm/vmm.c",
          312,
          "IS_PAGE_ALIGNED(size)");
  return vmm_map(v60, v61, v62, v63, v64, v65, v66, v67);
}

/* ===== vmm_map @ 0x9404A878 size 396 ===== */
__int64 __fastcall vmm_map(
        __int64 *a1,
        char *a2,
        unsigned __int64 a3,
        __int64 *a4,
        unsigned __int8 a5,
        __int64 a6,
        char a7,
        int a8)
{
  __int64 v8; // x30
  char *v11; // x20
  __int64 result; // x0
  __int64 v17; // x0
  __int64 v18; // x0
  __int64 v19; // x1
  unsigned int v20; // w21
  unsigned __int64 v21; // [xsp+50h] [xbp+50h]

  v11 = a2;
  if ( (a6 & 0xFFF) != 0 )
  {
    panic(
      v8,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      "external/lk/kernel/vm/vmm.c",
      351,
      "IS_PAGE_ALIGNED(paddr)");
  }
  else if ( (a3 & 0xFFF) == 0 )
  {
    if ( a2 == nullptr )
      v11 = "";
    result = 0;
    if ( a3 != 0 )
    {
      if ( (a7 & 1) == 0 )
      {
        mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
        v17 = vmm_alloc(a1, (__int64)v11, a3, 0, a5, a7, 2, a8);
        if ( v17 != 0 )
        {
          if ( a4 == nullptr )
          {
            v18 = *(_QWORD *)(v17 + 56);
            goto LABEL_10;
          }
LABEL_9:
          v18 = *(_QWORD *)(v17 + 56);
          *a4 = v18;
LABEL_10:
          v19 = a6;
          v20 = 0;
          arm64_mmu_map_page(v18, v19, a3 >> 12, a8);
LABEL_11:
          mutex_release((__int64)"xtum");
          return v20;
        }
LABEL_16:
        v20 = -5;
        goto LABEL_11;
      }
      if ( a4 != nullptr )
      {
        v21 = *a4;
        mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
        v17 = vmm_alloc(a1, (__int64)v11, a3, v21, a5, a7, 2, a8);
        if ( v17 != 0 )
          goto LABEL_9;
        goto LABEL_16;
      }
      return 4294967288LL;
    }
    return result;
  }
  panic(v8, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 352, "IS_PAGE_ALIGNED(size)");
  return 4294967288LL;
}

/* ===== vmm_alloc_physical @ 0x9404AA04 size 472 ===== */
__int64 __fastcall vmm_alloc_physical(
        __int64 *a1,
        char *a2,
        __int64 a3,
        unsigned __int64 *a4,
        unsigned __int8 a5,
        char a6,
        int a7)
{
  unsigned __int64 v7; // x19
  char *v9; // x28
  unsigned __int64 v13; // x27
  unsigned __int64 v14; // x22
  __int64 v16; // x0
  __int64 v17; // x19
  __int64 v18; // x0
  __int64 *v19; // x0
  __int64 v20; // x1
  __int64 *v21; // x2
  __int64 v23; // [xsp+78h] [xbp+78h] BYREF
  __int64 v24; // [xsp+80h] [xbp+80h] BYREF
  __int64 *v25; // [xsp+88h] [xbp+88h]

  v7 = (a3 + 4095) & 0xFFFFFFFFFFFFF000LL;
  v9 = a2;
  if ( v7 != 0 )
  {
    if ( a2 == nullptr )
      v9 = "";
    if ( (a6 & 1) == 0 )
    {
      v13 = 0;
      goto LABEL_7;
    }
    if ( a4 != nullptr )
    {
      v13 = *a4;
LABEL_7:
      v14 = v7 >> 12;
      v23 = 0;
      v25 = &v24;
      v24 = (__int64)&v24;
      if ( v7 >> 12 > (unsigned int)pmm_alloc_pages(v7 >> 12, a5, &v23, (__int64)&v24) )
        return 4294967291LL;
      mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
      v16 = vmm_alloc(a1, (__int64)v9, v7, v13, a5, a6, 2, a7);
      v17 = v16;
      if ( v16 == 0 )
      {
        mutex_release((__int64)"xtum");
        pmm_free_page_list((__int64)&v24);
        return 4294967291LL;
      }
      v18 = *(_QWORD *)(v16 + 56);
      if ( a4 != nullptr )
        *a4 = v18;
      arm64_mmu_map_page(v18, v23, v14, a7);
      v19 = v25;
      if ( v25 != &v24 )
      {
        v20 = v17 + 72;
        do
        {
          v21 = (__int64 *)v19[1];
          *v21 = *v19;
          *(_QWORD *)(*v19 + 8) = v21;
          *v19 = 0;
          *v19 = *(_QWORD *)v20;
          v19[1] = v20;
          *(_QWORD *)(*(_QWORD *)v20 + 8LL) = v19;
          *(_QWORD *)v20 = v19;
          v19 = v25;
        }
        while ( v25 != &v24 );
      }
      mutex_release((__int64)"xtum");
      return 0;
    }
  }
  return 4294967288LL;
}

/* ===== vmm_free_region @ 0x9404ABDC size 256 ===== */
__int64 __fastcall vmm_free_region(__int64 a1, unsigned __int64 a2)
{
  __int64 v2; // x30
  __int64 v5; // x19
  _QWORD *v6; // x19
  unsigned __int64 v7; // x0
  unsigned __int64 v8; // x1
  _QWORD *v10; // x2
  __int64 v11; // x0

  v5 = v2;
  mutex_acquire_timeout((__int64)"xtum", 0xFFFFFFFFLL);
  if ( a1 != 0 )
  {
    v6 = *(_QWORD **)(a1 + 80);
    if ( v6 == (_QWORD *)(a1 + 72) )
    {
LABEL_6:
      mutex_release((__int64)"xtum");
      return 4294967294LL;
    }
    else
    {
      while ( 1 )
      {
        v7 = v6[7];
        if ( a2 >= v7 )
        {
          v8 = v6[8];
          if ( a2 <= v7 + v8 - 1 )
            break;
        }
        v6 = (_QWORD *)v6[1];
        if ( (_QWORD *)(a1 + 72) == v6 )
          goto LABEL_6;
      }
      v10 = (_QWORD *)v6[1];
      *v10 = *v6;
      *(_QWORD *)(*v6 + 8LL) = v10;
      v6[1] = 0;
      *v6 = 0;
      arm64_mmu_unmap_page(v7, v8 >> 12);
      mutex_release((__int64)"xtum");
      pmm_free_page_list((__int64)(v6 + 9));
      free(v6);
      return 0;
    }
  }
  else
  {
    v11 = panic(v5, "DEBUG ASSERT FAILED at (%s:%d): %s\n", "external/lk/kernel/vm/vmm.c", 559, "aspace");
    return vmm_is_empty(v11);
  }
}

/* ===== vmm_is_empty @ 0x9404ACDC size 124 ===== */
bool vmm_is_empty()
{
  return &qword_9405CB88 == (__int64 *)-536622200LL;
}

/* ===== console_getc @ 0x9404AD58 size 36 ===== */
__int64 console_getc()
{
  __int64 result; // x0
  unsigned __int8 v1; // [xsp+1Fh] [xbp+1Fh] BYREF

  result = uart_getc(&v1, 1);
  if ( (result & 0x80000000) == 0 )
    return v1;
  return result;
}

/* ===== console_write @ 0x9404AD7C size 412 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall console_write(unsigned __int8 *a1, unsigned __int64 a2)
{
  unsigned __int8 *v2; // x19
  __int64 result; // x0
  unsigned __int8 *v5; // x20
  unsigned int v6; // t1
  unsigned __int8 *v7; // x21
  unsigned int v8; // t1
  __int64 v9; // x20
  __int64 v10; // x20

  v2 = a1;
  if ( MEMORY[0xFFFFFFFFE0057F30] != 0 )
  {
    result = MEMORY[0xFFFFFFFFE0059F48];
    if ( MEMORY[0xFFFFFFFFE0059F48] != 0 )
    {
      v5 = &v2[a2];
      if ( a2 != 0 )
      {
        do
        {
          v6 = *v2++;
          result = uart_putc(v6);
        }
        while ( v2 != v5 );
      }
    }
    else
    {
      v9 = -536622200;
      if ( &qword_9405CB88 != (__int64 *)-536622200LL )
      {
        do
        {
          result = (*(__int64 (__fastcall **)(__int64, unsigned __int8 *, unsigned __int64))(v9 + 16))(v9, v2, a2);
          v9 = *(_QWORD *)(v9 + 8);
        }
        while ( (__int64 *)v9 != &qword_9405CB88 );
      }
    }
  }
  else
  {
    v10 = 0x2000;
    if ( a2 < 0x2000 )
      v10 = a2;
    memcpy(qword_94077F48, a1, v10);
    dword_94077F40 = v10;
    result = MEMORY[0xFFFFFFFFE0059F48];
    if ( MEMORY[0xFFFFFFFFE0059F48] != 0 && a2 != 0 )
    {
      v7 = &v2[a2];
      do
      {
        v8 = *v2++;
        result = uart_putc(v8);
      }
      while ( v2 != v7 );
    }
  }
  return result;
}

/* ===== console_write_str @ 0x9404AF18 size 52 ===== */
__int64 __fastcall console_write_str(unsigned __int8 *a1, __int64 a2)
{
  unsigned __int64 v3; // x0
  unsigned int v4; // w19

  v3 = strnlen(a1, a2);
  v4 = v3;
  console_write(a1, v3);
  return v4;
}

/* ===== console_register @ 0x9404AF4C size 200 ===== */
// write access to const memory has been detected, the output may be wrong!
unsigned __int64 *__fastcall console_register(__int64 a1)
{
  char v2; // w20
  unsigned __int64 *result; // x0

  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    *(_QWORD *)(a1 + 8) = -536622200;
    *(_QWORD *)a1 = &qword_9405CB88;
    MEMORY[0xFFFFFFFFE003CB88] = a1;
    off_9405CB90 = (_UNKNOWN *)a1;
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    *(_QWORD *)(a1 + 8) = -536622200;
    *(_QWORD *)a1 = &qword_9405CB88;
    MEMORY[0xFFFFFFFFE003CB88] = a1;
    off_9405CB90 = (_UNKNOWN *)a1;
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== console_unregister @ 0x9404B014 size 192 ===== */
unsigned __int64 *__fastcall console_unregister(_QWORD *a1)
{
  char v2; // w20
  _QWORD *v9; // x1
  unsigned __int64 *result; // x0
  _QWORD *v13; // x1

  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v13 = (_QWORD *)a1[1];
    *v13 = *a1;
    *(_QWORD *)(*a1 + 8LL) = v13;
    a1[1] = 0;
    *a1 = 0;
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v9 = (_QWORD *)a1[1];
    *v9 = *a1;
    *(_QWORD *)(*a1 + 8LL) = v9;
    a1[1] = 0;
    *a1 = 0;
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== console_putc @ 0x9404B0D4 size 168 ===== */
unsigned __int64 *__fastcall console_putc(unsigned __int8 a1)
{
  char v2; // w19
  unsigned __int64 *result; // x0
  unsigned __int8 v12; // [xsp+3Fh] [xbp+3Fh] BYREF

  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v12 = a1;
    console_write(&v12, 1u);
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v12 = a1;
    console_write(&v12, 1u);
    result = spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return result;
}

/* ===== console_putc_cb @ 0x9404B17C size 28 ===== */
__int64 __fastcall console_putc_cb(__int64 a1, unsigned __int8 a2)
{
  console_putc(a2);
  return 0;
}

/* ===== console_puts @ 0x9404B198 size 180 ===== */
__int64 __fastcall console_puts(unsigned __int8 *a1)
{
  char v2; // w19
  unsigned __int64 v9; // x0
  unsigned __int64 v13; // x0

  v2 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v2 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v13 = strlen(a1);
    console_write(a1, v13);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v2 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v9 = strlen(a1);
    console_write(a1, v9);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v2 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return 0;
}

/* ===== console_puts_cb @ 0x9404B24C size 8 ===== */
__int64 __fastcall console_puts_cb(__int64 a1, unsigned __int8 *a2)
{
  return console_puts(a2);
}

/* ===== console_write_raw @ 0x9404B254 size 168 ===== */
__int64 __fastcall console_write_raw(unsigned __int8 *a1, unsigned __int64 a2)
{
  char v3; // w19

  v3 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v3 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    console_write(a1, a2);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v3 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    console_write(a1, a2);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v3 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return 0;
}

/* ===== log_printf @ 0x9404B2FC size 288 ===== */
__int64 log_printf(
        const char *a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        ...)
{
  char v10; // w19
  unsigned int v17; // w21
  va_list va1; // [xsp+30h] [xbp+30h] BYREF
  va_list va; // [xsp+50h] [xbp+50h] BYREF

  va_start(va, a9);
  v10 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v10 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    va_copy(va1, va);
    v17 = vprintf_core(console_write_str, 0, a1, va1);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v10 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    va_copy(va1, va);
    v17 = vprintf_core(console_write_str, 0, a1, va1);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v10 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v17;
}

/* ===== log_vprintf @ 0x9404B41C size 236 ===== */
__int64 __fastcall log_vprintf(__int64 a1, _QWORD *a2)
{
  char v3; // w19
  __int64 v10; // x7
  __int64 v11; // x4
  __int64 v12; // x5
  unsigned int v13; // w20
  __int64 v17; // x7
  __int64 v18; // x4
  __int64 v19; // x5
  _QWORD v21[2]; // [xsp+40h] [xbp+40h] BYREF
  __int64 v22; // [xsp+50h] [xbp+50h]
  __int64 v23; // [xsp+58h] [xbp+58h]

  v3 = 0;
  if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
  {
    __asm { MSR             DAIFSet, #2 }
    v3 = 1;
  }
  if ( (_ReadStatusReg(DAIF) & 0x40) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v17 = a2[1];
    v18 = a2[2];
    v19 = a2[3];
    v21[0] = *a2;
    v21[1] = v17;
    v22 = v18;
    v23 = v19;
    v13 = vprintf_core(console_write_str, 0, a1, v21);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
  }
  else
  {
    v3 |= 2u;
    __asm { MSR             DAIFSet, #1 }
    spin_lock((unsigned __int64 *)&qword_94077F38);
    v10 = a2[1];
    v11 = a2[2];
    v12 = a2[3];
    v21[0] = *a2;
    v21[1] = v10;
    v22 = v11;
    v23 = v12;
    v13 = vprintf_core(console_write_str, 0, a1, v21);
    spin_unlock((unsigned __int64 *)&qword_94077F38);
    __asm { MSR             DAIFClr, #1 }
  }
  if ( (v3 & 1) != 0 )
    __asm { MSR             DAIFClr, #2 }
  return v13;
}

/* ===== panic @ 0x9404B508 size 188 ===== */
__int64 panic(
        __int64 a1,
        const char *a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        ...)
{
  __int64 *v11; // x2
  __int64 v12; // x4
  __int64 v13; // x5
  __int64 v14; // x2
  __int64 v15; // x3
  _QWORD *v16; // t2
  __int64 v17; // x1
  _QWORD v19[4]; // [xsp+10h] [xbp-20h] BYREF
  va_list va; // [xsp+50h] [xbp+20h] BYREF
  va_list va1; // [xsp+70h] [xbp+40h] BYREF

  if ( (MEMORY[0xFFFFFFFFE003CB98] & 0x8000000000000000LL) == 0 )
    log_printf("panic (caller %p): ", a3, a4, a5, a6, a7, a8, a9, a10, a1);
  va_start(va1, a10);
  va_start(va, a10);
  log_vprintf((__int64)a2, va);
  halt(0, 9);
  v12 = *v11;
  v13 = v11[1];
  v16 = v11 + 2;
  v14 = v11[2];
  v15 = v16[1];
  v19[0] = v12;
  v19[1] = v13;
  v19[2] = v14;
  v19[3] = v15;
  return log_vprintf(v17, v19);
}

/* ===== heap_free_chunk @ 0x9404B5C4 size 420 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall heap_free_chunk(unsigned __int64 a1)
{
  __int64 v1; // x30
  unsigned __int64 v2; // x19
  __int64 v3; // x23
  __int64 v4; // x22
  double v5; // d0
  double v6; // d1
  double v7; // d2
  double v8; // d3
  double v9; // d4
  double v10; // d5
  double v11; // d6
  double v12; // d7
  __int64 v13; // x3
  unsigned __int64 *v14; // x0
  unsigned __int64 v15; // x1
  __int64 v16; // x2
  __int64 v17; // x1
  _QWORD *v18; // x2
  _QWORD *v19; // x3
  unsigned __int64 *v21; // x4
  __int64 v22; // x0

  v2 = a1;
  v3 = v1;
  v4 = *(_QWORD *)(a1 + 16);
  mutex_acquire_timeout((__int64)qword_94079FA0, 0xFFFFFFFFLL);
  v13 = *(_QWORD *)(v2 + 16);
  v14 = nullptr;
  qword_94079F90 = v13;
  if ( &off_94079FD8 == nullptr )
  {
LABEL_13:
    *(_QWORD *)v2 = 0;
    *(_QWORD *)(v2 + 8) = &off_94079FD8;
    MEMORY[8] = v2;
    off_94079FD8 = (_UNKNOWN *)v2;
    v15 = *(_QWORD *)v2;
    if ( *(_UNKNOWN ***)v2 != &off_94079FD8 && v15 != 0 )
    {
      v16 = *(_QWORD *)(v15 + 16);
      if ( v2 == v15 + v16 )
      {
LABEL_16:
        v21 = *(unsigned __int64 **)(v2 + 8);
        *(_QWORD *)(v15 + 16) = v13 + v16;
        *v21 = v15;
        *(_QWORD *)(*(_QWORD *)v2 + 8LL) = v21;
        *(_QWORD *)(v2 + 8) = 0;
        *(_QWORD *)v2 = 0;
        v2 = v15;
      }
    }
LABEL_9:
    if ( v14 == nullptr )
    {
LABEL_12:
      mutex_release((__int64)qword_94079FA0);
      return v2;
    }
LABEL_10:
    v17 = *(_QWORD *)(v2 + 16);
    if ( v14 == (unsigned __int64 *)(v2 + v17) )
    {
      v18 = (_QWORD *)v14[1];
      v19 = (_QWORD *)*v14;
      *(_QWORD *)(v2 + 16) = v14[2] + v17;
      *v18 = v19;
      *(_QWORD *)(*v14 + 8) = v18;
      v14[1] = 0;
      *v14 = 0;
    }
    goto LABEL_12;
  }
  while ( v2 >= (unsigned __int64)v14 )
  {
    v14 = (unsigned __int64 *)v14[1];
    if ( v14 == (unsigned __int64 *)&off_94079FD8 )
      goto LABEL_13;
  }
  if ( (unsigned __int64)v14 >= v2 + v4 )
  {
    *(_QWORD *)v2 = *v14;
    *(_QWORD *)(v2 + 8) = v14;
    *(_QWORD *)(*v14 + 8) = v2;
    *v14 = v2;
    v15 = *(_QWORD *)v2;
    if ( *(_UNKNOWN ***)v2 == &off_94079FD8 || v15 == 0 )
      goto LABEL_10;
    v16 = *(_QWORD *)(v15 + 16);
    if ( v2 == v15 + v16 )
      goto LABEL_16;
    goto LABEL_9;
  }
  v22 = panic(
          v3,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          v5,
          v6,
          v7,
          v8,
          v9,
          v10,
          v11,
          v12,
          "external/lk/lib/heap/heap.c",
          212,
          "chunk_end <= (vaddr_t)next_chunk");
  return heap_assert_len_aligned(v22);
}

/* ===== heap_assert_len_aligned @ 0x9404B768 size 44 ===== */
__int64 __fastcall heap_assert_len_aligned(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
{
  __int64 v8; // x30
  __int64 v9; // x0

  v9 = panic(
         v8,
         "DEBUG ASSERT FAILED at (%s:%d): %s\n",
         a1,
         a2,
         a3,
         a4,
         a5,
         a6,
         a7,
         a8,
         "external/lk/lib/heap/heap.c",
         258,
         "(len % sizeof(void *)) == 0");
  return heap_merge_free_list(v9);
}

/* ===== heap_merge_free_list @ 0x9404B794 size 316 ===== */
__int64 heap_merge_free_list()
{
  int v5; // w21
  __int64 v6; // x2
  __int64 result; // x0
  __int64 *i; // x1
  __int64 *v10; // x2
  __int64 v12; // [xsp+40h] [xbp+40h] BYREF
  __int64 *v13; // [xsp+48h] [xbp+48h]

  v13 = &v12;
  v12 = (__int64)&v12;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    v5 = 0;
    spin_lock((unsigned __int64 *)&qword_94079FF8);
    if ( &qword_94079FE8 == nullptr )
    {
      result = (__int64)spin_unlock((unsigned __int64 *)&qword_94079FF8);
      goto LABEL_7;
    }
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)&qword_94079FF8);
    if ( &qword_94079FE8 == nullptr )
    {
      result = (__int64)spin_unlock((unsigned __int64 *)&qword_94079FF8);
      __asm { MSR             DAIFClr, #2 }
      goto LABEL_7;
    }
    v5 = 1;
  }
  do
  {
    v6 = MEMORY[8];
    *MEMORY[8] = MEMORY[0];
    *(_QWORD *)(MEMORY[0] + 8LL) = v6;
    MEMORY[8] = v13;
    MEMORY[0] = &v12;
    *v13 = 0;
    v13 = nullptr;
  }
  while ( &qword_94079FE8 != nullptr );
  result = (__int64)spin_unlock((unsigned __int64 *)&qword_94079FF8);
  if ( v5 != 0 )
    __asm { MSR             DAIFClr, #2 }
LABEL_7:
  for ( i = v13; v13 != &v12; i = v13 )
  {
    v10 = (__int64 *)i[1];
    *v10 = *i;
    *(_QWORD *)(*i + 8) = v10;
    i[1] = 0;
    *i = 0;
    result = heap_free_chunk((unsigned __int64)i);
  }
  return result;
}

/* ===== heap_alloc_aligned @ 0x9404B8D0 size 768 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall heap_alloc_aligned(__int64 a1, unsigned int a2)
{
  __int64 v2; // x30
  __int64 v3; // x27
  __int64 v4; // x23
  unsigned __int64 v5; // x19
  unsigned __int64 v6; // x20
  int v7; // w24
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  __int64 v16; // x1
  unsigned __int64 v17; // x0
  __int64 v18; // x0
  unsigned __int64 v19; // x0
  unsigned __int64 v20; // x24
  __int64 v21; // x24
  _UNKNOWN **v23; // x2
  __int64 *v24; // x5
  _UNKNOWN **v25; // x6
  _UNKNOWN **v26; // x4
  unsigned __int64 v27; // x20
  __int64 v28; // x19
  unsigned __int64 v29; // x0
  _QWORD *v30; // x2
  __int64 v31; // [xsp+68h] [xbp+68h]

  v3 = a2;
  v4 = v2;
  if ( &qword_94079FE8 != nullptr )
  {
    v31 = a1;
    heap_merge_free_list();
    a1 = v31;
  }
  if ( (((_DWORD)v3 - 1) & (unsigned int)v3) != 0 )
    return 0;
  v5 = 24;
  if ( (unsigned __int64)(a1 + 24) > 0x17 )
  {
    v5 = (a1 + 31) & 0xFFFFFFFFFFFFFFF8LL;
    if ( (_DWORD)v3 == 0 )
      goto LABEL_6;
  }
  else if ( (_DWORD)v3 == 0 )
  {
    goto LABEL_6;
  }
LABEL_14:
  v18 = (unsigned int)v3;
  if ( (unsigned int)v3 <= 0xF )
  {
    v18 = 16;
    v3 = 16;
  }
  v5 += v18;
LABEL_6:
  v6 = 0x2000;
  v7 = 0;
  if ( ((v5 + 4095) & 0xFFFFFFFFFFFFF000LL) >= 0x2000 )
    v6 = (v5 + 4095) & 0xFFFFFFFFFFFFF000LL;
  while ( 1 )
  {
    mutex_acquire_timeout((__int64)qword_94079FA0, 0xFFFFFFFFLL);
    v16 = 0;
    if ( &off_94079FD8 != nullptr )
      break;
LABEL_19:
    mutex_release((__int64)qword_94079FA0);
    if ( v7 != 0 )
      return 0;
    v19 = pmm_alloc_page(v6 >> 12, 0);
    v20 = v19;
    if ( v19 == 0 )
      goto LABEL_39;
    *(_QWORD *)(v19 + 16) = v6;
    heap_free_chunk(v19);
    v21 = v20 + v6;
    if ( v21 != 0 )
      qword_94079F88 = v21;
    v7 = 1;
    if ( (v6 & 0x8000000000000000LL) != 0 )
      return 0;
  }
  while ( 1 )
  {
    v17 = *(_QWORD *)(v16 + 16);
    if ( (v17 & 7) != 0 )
    {
      panic(
        v4,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        v8,
        v9,
        v10,
        v11,
        v12,
        v13,
        v14,
        v15,
        "external/lk/lib/heap/heap.c",
        344,
        "(chunk->len % sizeof(void *)) == 0");
      goto LABEL_14;
    }
    if ( v5 <= v17 )
      break;
    v16 = *(_QWORD *)(v16 + 8);
    if ( (_UNKNOWN **)v16 == &off_94079FD8 )
      goto LABEL_19;
  }
  v23 = *(_UNKNOWN ***)(v16 + 8);
  v24 = &qword_94079F80;
  v25 = &off_94079FD8;
  *v23 = *(_UNKNOWN **)v16;
  if ( v23 == &off_94079FD8 )
    v26 = nullptr;
  else
    v26 = v23;
  *(_QWORD *)(*(_QWORD *)v16 + 8LL) = v23;
  *(_QWORD *)(v16 + 8) = 0;
  *(_QWORD *)v16 = 0;
  if ( v5 + 24 < v17 )
  {
    v29 = v17 - v5;
    v30 = (_QWORD *)(v16 + v5);
    if ( (v29 & 7) != 0 )
    {
      heap_assert_len_aligned(v8, v9, v10, v11, v12, v13, v14, v15);
LABEL_39:
      printf("%s:%d: failed to grow kernel heap by 0x%zx bytes\n", "heap_grow", 518, v6);
      return 0;
    }
    v30[2] = v29;
    *(_QWORD *)(v16 + 16) = v5;
    if ( v26 != nullptr )
    {
      v27 = v5;
      *v30 = *v26;
      v30[1] = v26;
      *((_QWORD *)*v26 + 1) = v30;
      *v26 = v30;
      goto LABEL_30;
    }
LABEL_37:
    v27 = v5;
    *v30 = v24[11];
    v30[1] = v25;
    *(_QWORD *)(v24[11] + 8) = v30;
    v24[11] = (__int64)v30;
    goto LABEL_30;
  }
  v27 = *(_QWORD *)(v16 + 16);
  if ( v5 > v27 )
  {
    panic(
      v4,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      v8,
      v9,
      v10,
      v11,
      v12,
      v13,
      v14,
      v15,
      "external/lk/lib/heap/heap.c",
      369,
      "chunk->len >= size");
    goto LABEL_37;
  }
LABEL_30:
  v28 = v16 + 24;
  if ( (_DWORD)v3 != 0 )
    v28 = (v3 - 1 + v28) & -v3;
  *(_DWORD *)(v28 - 24) = 1212498256;
  *(_QWORD *)(v28 - 16) = v16;
  *(_QWORD *)(v28 - 8) = v27;
  qword_94079F90 = -(__int64)v27;
  mutex_release((__int64)qword_94079FA0);
  return v28;
}

/* ===== heap_free @ 0x9404BBD0 size 108 ===== */
__int64 __fastcall heap_free(
        __int64 result,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v9; // x30
  __int64 v10; // x1
  unsigned __int64 v11; // x0
  __int64 v12; // x0

  if ( result != 0 )
  {
    if ( *(_DWORD *)(result - 24) == 1212498256 )
    {
      v10 = *(_QWORD *)(result - 8);
      v11 = *(_QWORD *)(result - 16);
      if ( (v10 & 7) == 0 )
      {
        *(_QWORD *)(v11 + 16) = v10;
        return heap_free_chunk(v11);
      }
    }
    else
    {
      panic(
        v9,
        "DEBUG ASSERT FAILED at (%s:%d): %s\n",
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        a8,
        a9,
        "external/lk/lib/heap/heap.c",
        438,
        "as->magic == HEAP_MAGIC");
    }
    v12 = heap_assert_len_aligned(a2, a3, a4, a5, a6, a7, a8, a9);
    return heap_free_to_quarantine(v12);
  }
  return result;
}

/* ===== heap_free_to_quarantine @ 0x9404BC3C size 252 ===== */
// write access to const memory has been detected, the output may be wrong!
unsigned __int64 *__fastcall heap_free_to_quarantine(
        __int64 a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v9; // x30
  __int64 v10; // x1
  __int64 v11; // x19
  unsigned __int64 *result; // x0
  __int64 v19; // x0

  if ( *(_DWORD *)(a1 - 24) != 1212498256 )
  {
    panic(
      v9,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      a2,
      a3,
      a4,
      a5,
      a6,
      a7,
      a8,
      a9,
      "external/lk/lib/heap/heap.c",
      469,
      "as->magic == HEAP_MAGIC");
    goto LABEL_7;
  }
  v10 = *(_QWORD *)(a1 - 8);
  v11 = *(_QWORD *)(a1 - 16);
  if ( (v10 & 7) != 0 )
  {
LABEL_7:
    v19 = heap_assert_len_aligned(a2, a3, a4, a5, a6, a7, a8, a9);
    return (unsigned __int64 *)heap_init(v19);
  }
  *(_QWORD *)(v11 + 16) = v10;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_94079FF8);
    *(_QWORD *)(v11 + 8) = 0;
    *(_QWORD *)v11 = &qword_94079FE8;
    MEMORY[0] = v11;
    off_94079FF0 = (_UNKNOWN *)v11;
    return spin_unlock((unsigned __int64 *)&qword_94079FF8);
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)&qword_94079FF8);
    *(_QWORD *)(v11 + 8) = 0;
    *(_QWORD *)v11 = &qword_94079FE8;
    MEMORY[0] = v11;
    off_94079FF0 = (_UNKNOWN *)v11;
    result = spin_unlock((unsigned __int64 *)&qword_94079FF8);
    __asm { MSR             DAIFClr, #2 }
  }
  return result;
}

/* ===== heap_init @ 0x9404BD38 size 228 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 heap_init()
{
  __int64 v0; // x30
  __int64 v1; // x21
  unsigned __int64 v2; // x0
  double v3; // d0
  double v4; // d1
  double v5; // d2
  double v6; // d3
  double v7; // d4
  double v8; // d5
  double v9; // d6
  double v10; // d7
  _BYTE *v12; // x0
  __int64 v13; // x1
  _QWORD *v14; // x2
  __int64 v15; // x3
  unsigned __int64 v16; // x4

  v1 = v0;
  mutex_init((__int64)qword_94079FA0);
  qword_94079FF8 = 0;
  off_94079FF0 = &qword_94079FE8;
  qword_94079FE8 = (__int64)&qword_94079FE8;
  qword_94079FE0 = (__int64)&off_94079FD8;
  off_94079FD8 = &off_94079FD8;
  v2 = pmm_alloc_page(2u, 0);
  qword_94079F80 = v2;
  qword_94079F88 = 0x2000;
  if ( v2 != 0 )
  {
    qword_94079F90 = 0;
    qword_94079F98 = 0x2000;
    *(_QWORD *)(v2 + 16) = 0x2000;
    return heap_free_chunk(v2);
  }
  else
  {
    v12 = (_BYTE *)panic(v1, "HEAP: error allocating initial heap size\n", v3, v4, v5, v6, v7, v8, v9, v10);
    if ( v13 != 0 && *v12 != 0 )
    {
      v15 = 0;
      do
      {
        v16 = v14[2];
        if ( v16 < v14[1] )
        {
          v14[2] = v16 + 1;
          *(_BYTE *)(*v14 + v16) = v12[v15];
        }
        ++v15;
      }
      while ( v15 != v13 && v12[v15] != 0 );
      return (unsigned int)v15;
    }
    else
    {
      return 0;
    }
  }
}

/* ===== fmt_uint @ 0x9404BE1C size 224 ===== */
_BYTE *__fastcall fmt_uint(__int64 a1, unsigned __int64 a2, __int16 a3, _BYTE *a4)
{
  int v4; // w9
  __int64 v5; // x5
  unsigned __int64 v6; // kr00_8
  int v7; // w4
  _BYTE *v8; // x4

  if ( (a3 & 0x400) != 0 && (a2 & 0x8000000000000000LL) != 0 )
  {
    a2 = -(__int64)a2;
    *(_BYTE *)(a1 + 31) = 0;
    if ( a2 <= 9 )
    {
      v8 = (_BYTE *)(a1 + 30);
      *(_BYTE *)(a1 + 30) = a2 + 48;
LABEL_12:
      *a4 = 45;
      return v8;
    }
    v4 = 1;
  }
  else
  {
    *(_BYTE *)(a1 + 31) = 0;
    v4 = 0;
    if ( a2 <= 9 )
    {
      *(_BYTE *)(a1 + 30) = a2 + 48;
      v8 = (_BYTE *)(a1 + 30);
      if ( (a3 & 0x200) == 0 )
        goto LABEL_8;
LABEL_13:
      *a4 = 43;
      return v8;
    }
  }
  v5 = 31;
  do
  {
    v6 = a2;
    --v5;
    v7 = a2 % 0xA;
    a2 /= 0xAu;
    *(_BYTE *)(a1 + v5) = v7 + 48;
  }
  while ( v6 / 0xA > 9 );
  v8 = (_BYTE *)(a1 + v5 - 1);
  *v8 = a2 + 48;
  if ( v4 != 0 )
    goto LABEL_12;
  if ( (a3 & 0x200) != 0 )
    goto LABEL_13;
LABEL_8:
  if ( (a3 & 0x2000) != 0 )
    *a4 = 32;
  else
    *a4 = 0;
  return v8;
}

/* ===== fmt_hex @ 0x9404BEFC size 60 ===== */
_BYTE *__fastcall fmt_hex(__int64 a1, unsigned __int64 a2, __int16 a3)
{
  char *v3; // x4
  _BYTE *v4; // x3
  __int64 v5; // x2
  _BYTE *result; // x0

  if ( (a3 & 0x100) != 0 )
    v3 = "0123456789ABCDEF%p invalid syscall %d requested\n";
  else
    v3 = "0123456789abcdef0123456789ABCDEF%p invalid syscall %d requested\n";
  *(_BYTE *)(a1 + 31) = 0;
  v4 = (_BYTE *)(a1 + 30);
  do
  {
    v5 = a2 & 0xF;
    result = v4;
    a2 >>= 4;
    *v4-- = v3[v5];
  }
  while ( a2 != 0 );
  return result;
}

/* ===== vprintf_core @ 0x9404BF38 size 2832 ===== */
__int64 __fastcall vprintf_core(
        __int64 (__fastcall *a1)(unsigned __int8 *, __int64, __int64),
        __int64 a2,
        unsigned __int8 *a3)
{
  unsigned __int8 *v5; // x28
  __int64 v6; // x19
  int v7; // w0
  unsigned __int8 *v8; // x24
  int v9; // w0
  int v10; // t1
  __int64 result; // x0
  __int64 v12; // x1
  unsigned __int8 *v13; // x24
  int v14; // w28
  int v15; // t1
  unsigned int v16; // w20
  _BYTE v17[7]; // [xsp+A8h] [xbp+A8h] BYREF
  char v18; // [xsp+AFh] [xbp+AFh]

  v5 = a3;
  v6 = 0;
  v7 = *a3;
  v8 = a3 + 1;
  v18 = 0;
  if ( v7 != 0 )
  {
    while ( v7 == 37 )
    {
      v12 = 0;
LABEL_10:
      result = a1(v5, v12, a2);
      if ( (result & 0x80000000) != 0 )
        return result;
      v6 += (int)result;
      v15 = *v8;
      v13 = v8 + 1;
      v14 = v15;
      if ( v15 == 0 )
        return (unsigned int)v6;
      if ( (unsigned int)(v14 - 32) <= 0x5A )
        __asm { BR              X0; switch jump }
      v17[0] = 37;
      v16 = a1(v17, 1, a2);
      if ( (v16 & 0x80000000) != 0 )
        return v16;
      v17[0] = v14;
      result = a1(v17, 1, a2);
      if ( (result & 0x80000000) != 0 )
        return result;
      v5 = v13;
      v6 += (int)v16 + (__int64)(int)result;
      v18 = 0;
      v8 = v13 + 1;
      v7 = *v5;
      if ( *v5 == 0 )
        goto LABEL_16;
    }
    while ( 1 )
    {
      v12 = v8 - v5;
      v10 = *v8++;
      v9 = v10;
      if ( v10 == 0 )
        break;
      if ( v9 == 37 )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_16:
    v12 = 0;
  }
  result = a1(v5, v12, a2);
  if ( (result & 0x80000000) == 0 )
  {
    LODWORD(v6) = v6 + result;
    return (unsigned int)v6;
  }
  return result;
}

/* ===== vsnprintf @ 0x9404CA48 size 120 ===== */
__int64 __fastcall vsnprintf(__int64 a1, unsigned __int64 a2, unsigned __int8 *a3)
{
  __int64 result; // x0
  _QWORD v6[2]; // [xsp+48h] [xbp+48h] BYREF
  unsigned __int64 v7; // [xsp+58h] [xbp+58h]

  v6[0] = a1;
  v6[1] = a2;
  v7 = 0;
  result = vprintf_core((__int64 (__fastcall *)(unsigned __int8 *, __int64, __int64))&loc_9404BDC0, (__int64)v6, a3);
  if ( a2 <= v7 )
    *(_BYTE *)(a1 + a2 - 1) = 0;
  else
    *(_BYTE *)(a1 + (int)result) = 0;
  return result;
}

/* ===== snprintf @ 0x9404CAC0 size 92 ===== */
__int64 __fastcall snprintf(
        __int64 a1,
        unsigned __int64 a2,
        char *a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8)
{
  return vsnprintf(a1, a2, (unsigned __int8 *)a3);
}

/* ===== log_dispatch @ 0x9404CB1C size 48 ===== */
__int64 __fastcall log_dispatch(__int64 *a1, __int64 a2, _QWORD *a3)
{
  __int64 v3; // x7
  __int64 v4; // x4
  __int64 v5; // x5
  __int64 (__fastcall *v6)(__int64, __int64, _QWORD *); // x3
  __int64 v7; // x0
  _QWORD v9[4]; // [xsp+10h] [xbp+10h] BYREF

  v3 = a3[1];
  v4 = a3[2];
  v5 = a3[3];
  v9[0] = *a3;
  v9[1] = v3;
  v6 = (__int64 (__fastcall *)(__int64, __int64, _QWORD *))a1[4];
  v7 = *a1;
  v9[2] = v4;
  v9[3] = v5;
  return v6(v7, a2, v9);
}

/* ===== printf @ 0x9404CB4C size 120 ===== */
__int64 printf(
        const char *a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        ...)
{
  va_list va; // [xsp+10h] [xbp+10h] BYREF
  va_list va1; // [xsp+30h] [xbp+30h] BYREF

  va_start(va, a9);
  va_start(va1, a9);
  return log_dispatch((__int64 *)0xFFFFFFFFE003CB38LL, (__int64)a1, va);
}

/* ===== malloc @ 0x9404CBC4 size 8 ===== */
__int64 __fastcall malloc(__int64 a1)
{
  return heap_alloc_aligned(a1, 0);
}

/* ===== memalign @ 0x9404CBCC size 16 ===== */
__int64 __fastcall memalign(unsigned int a1, __int64 a2)
{
  return heap_alloc_aligned(a2, a1);
}

/* ===== calloc @ 0x9404CBDC size 68 ===== */
__int64 __fastcall calloc(__int64 a1, __int64 a2)
{
  __int64 v2; // x0
  __int64 v3; // x19
  __int64 v5; // [xsp+28h] [xbp+28h]

  v5 = a1 * a2;
  v2 = heap_alloc_aligned(a1 * a2, 0);
  v3 = v2;
  if ( v2 != 0 )
    memset(v2, 0, v5);
  return v3;
}

/* ===== free @ 0x9404CC20 size 4 ===== */
// attributes: thunk
__int64 __fastcall free(
        __int64 result,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  return heap_free(result, a2, a3, a4, a5, a6, a7, a8, a9);
}

/* ===== memcmp @ 0x9404CC24 size 84 ===== */
__int64 __fastcall memcmp(_BYTE *a1, _BYTE *a2, __int64 a3)
{
  char *v3; // x4
  char *v4; // x2
  char v5; // t1
  __int64 result; // x0

  if ( a3 != 0 )
  {
    if ( *a1 != *a2 )
      return (unsigned int)(char)(*a1 - *a2);
    v3 = a1 + 1;
    v4 = &a1[a3];
    while ( 1 )
    {
      ++a2;
      if ( v3 == v4 )
        break;
      v5 = *v3++;
      result = (unsigned int)(char)(v5 - *a2);
      if ( v5 != *a2 )
        return result;
    }
  }
  return 0;
}

/* ===== memcpy @ 0x9404CC78 size 332 ===== */
_BYTE *__fastcall memcpy(_BYTE *result, _BYTE *a2, unsigned __int64 a3)
{
  _BYTE *v3; // x5
  __int64 v4; // x3
  __int64 v5; // x7
  __int64 v6; // x7
  int v7; // w2
  int v8; // w6
  bool v9; // cc
  __int64 v10; // x3
  __int64 v11; // x6
  __int64 v12; // x6

  if ( result == a2 || a3 == 0 )
    return result;
  v3 = result;
  if ( (((unsigned __int8)result | (unsigned __int8)a2) & 7) != 0 )
  {
    if ( (((unsigned __int8)result ^ (unsigned __int8)a2) & 7) != 0 || a3 <= 7 )
    {
      v8 = a3;
      v3 = result;
      v9 = (int)a3 <= 0;
      a3 -= (int)a3;
      if ( v9 )
        goto LABEL_4;
    }
    else
    {
      v8 = 8 - ((unsigned __int8)result & 7);
      a3 -= v8;
    }
    v10 = 0;
    v11 = (unsigned int)(v8 - 1);
    do
    {
      result[v10] = a2[v10];
      ++v10;
    }
    while ( v10 != v11 + 1 );
    v12 = (int)v11 + 1LL;
    v3 = &result[v12];
    a2 += v12;
  }
LABEL_4:
  if ( (int)(a3 >> 3) > 0 )
  {
    v4 = 0;
    v5 = (unsigned int)(a3 >> 3) - 1;
    do
    {
      *(_QWORD *)&v3[v4] = *(_QWORD *)&a2[v4];
      v4 += 8;
    }
    while ( v4 != 8 * (v5 + 1) );
    v6 = 8 * ((int)v5 + 1LL);
    v3 += v6;
    a2 += v6;
  }
  v7 = a3 & 7;
  if ( v7 != 0 )
  {
    *v3 = *a2;
    if ( v7 != 1 )
    {
      v3[1] = a2[1];
      if ( v7 != 2 )
      {
        v3[2] = a2[2];
        if ( v7 != 3 )
        {
          v3[3] = a2[3];
          if ( v7 != 4 )
          {
            v3[4] = a2[4];
            if ( v7 != 5 )
            {
              v3[5] = a2[5];
              if ( v7 != 6 )
                v3[6] = a2[6];
            }
          }
        }
      }
    }
  }
  return result;
}

/* ===== memset @ 0x9404CDC4 size 276 ===== */
__int64 __fastcall memset(__int64 result, unsigned __int8 a2, unsigned __int64 a3)
{
  unsigned __int64 *v3; // x4
  unsigned __int64 v4; // x3
  unsigned __int64 v5; // x2
  unsigned __int64 v6; // x5
  unsigned __int64 v7; // x5
  unsigned __int64 *v8; // x3

  v3 = (unsigned __int64 *)result;
  v4 = -result & 7;
  if ( v4 < a3 )
  {
    v5 = a3 - v4;
    v6 = a2 | ((unsigned __int64)a2 << 8) | ((a2 | ((unsigned __int64)a2 << 8)) << 16);
    v7 = v6 | (v6 << 32);
    if ( v4 != 0 )
    {
      *(_BYTE *)result = a2;
      if ( v4 != 1 )
      {
        *(_BYTE *)(result + 1) = a2;
        if ( v4 != 2 )
        {
          *(_BYTE *)(result + 2) = a2;
          if ( v4 != 3 )
          {
            *(_BYTE *)(result + 3) = a2;
            if ( v4 != 4 )
            {
              *(_BYTE *)(result + 4) = a2;
              if ( v4 != 5 )
              {
                *(_BYTE *)(result + 5) = a2;
                if ( v4 != 6 )
                  *(_BYTE *)(result + 6) = a2;
              }
            }
          }
        }
      }
      v8 = (unsigned __int64 *)(result + v4);
    }
    else
    {
      v8 = (unsigned __int64 *)result;
    }
    if ( v5 >> 3 != 0 )
    {
      v3 = &v8[v5 >> 3];
      do
        *v8++ = v7;
      while ( v8 != v3 );
      a3 = v5 & 7;
    }
    else
    {
      v3 = v8;
      a3 = v5 & 7;
    }
  }
  if ( a3 != 0 )
  {
    *(_BYTE *)v3 = a2;
    if ( a3 != 1 )
    {
      *((_BYTE *)v3 + 1) = a2;
      if ( a3 != 2 )
      {
        *((_BYTE *)v3 + 2) = a2;
        if ( a3 != 3 )
        {
          *((_BYTE *)v3 + 3) = a2;
          if ( a3 != 4 )
          {
            *((_BYTE *)v3 + 4) = a2;
            if ( a3 != 5 )
            {
              *((_BYTE *)v3 + 5) = a2;
              if ( a3 != 6 )
                *((_BYTE *)v3 + 6) = a2;
            }
          }
        }
      }
    }
  }
  return result;
}

/* ===== strcmp @ 0x9404CED8 size 52 ===== */
__int64 __fastcall strcmp(__int64 a1, __int64 a2)
{
  __int64 v2; // x3
  int v3; // w4
  char v4; // w2
  unsigned int v5; // w2

  v2 = 0;
  do
  {
    v3 = *(unsigned __int8 *)(a1 + v2);
    v4 = *(_BYTE *)(a2 + v2++);
    v5 = (char)(v3 - v4);
    if ( v5 != 0 )
      return v5;
  }
  while ( v3 != 0 );
  return 0;
}

/* ===== strcpy @ 0x9404CF0C size 24 ===== */
__int64 __fastcall strcpy(__int64 result, __int64 a2)
{
  __int64 v2; // x2
  int v3; // w3

  v2 = 0;
  do
  {
    v3 = *(unsigned __int8 *)(a2 + v2);
    *(_BYTE *)(result + v2++) = v3;
  }
  while ( v3 != 0 );
  return result;
}

/* ===== strdup @ 0x9404CF24 size 72 ===== */
_BYTE *__fastcall strdup(_BYTE *a1)
{
  _BYTE *v1; // x0
  _BYTE *v2; // x19
  __int64 v5; // [xsp+28h] [xbp+28h]

  v5 = strlen(a1) + 1;
  v1 = (_BYTE *)malloc(v5);
  v2 = v1;
  if ( v1 != nullptr )
    memcpy(v1, a1, v5);
  return v2;
}

/* ===== strlcpy @ 0x9404CF6C size 136 ===== */
__int64 __fastcall strlcpy(__int64 a1, _BYTE *a2, __int64 a3)
{
  __int64 v3; // x2
  __int64 v4; // x19
  _BYTE *v5; // x5
  unsigned __int8 *v6; // x3
  char v7; // w4
  int v8; // t1

  if ( a3 == 0 )
    return strlen(a2);
  v3 = a3 - 1;
  if ( v3 != 0 )
  {
    v4 = 0;
    v5 = a2;
    v6 = a2 + 1;
    v7 = *a2;
    if ( *a2 != 0 )
    {
      while ( 1 )
      {
        *(_BYTE *)(a1 + v4++) = v7;
        v5 = v6;
        if ( v4 == v3 )
          break;
        v8 = *v6++;
        v7 = v8;
        if ( v8 == 0 )
          goto LABEL_8;
      }
      v5 = &a2[v4];
    }
  }
  else
  {
    v5 = a2;
    v4 = 0;
  }
LABEL_8:
  *(_BYTE *)(a1 + v4) = 0;
  return strlen(v5) + v4;
}

/* ===== strlen @ 0x9404CFF4 size 40 ===== */
__int64 __fastcall strlen(_BYTE *a1)
{
  __int64 result; // x0

  if ( *a1 == 0 )
    return 0;
  result = 0;
  do
    ++result;
  while ( a1[result] != 0 );
  return result;
}

/* ===== strncpy @ 0x9404D01C size 36 ===== */
__int64 __fastcall strncpy(__int64 result, __int64 a2, __int64 a3)
{
  __int64 v3; // x3
  int v4; // w4

  v3 = 0;
  do
  {
    if ( v3 == a3 )
      break;
    v4 = *(unsigned __int8 *)(a2 + v3);
    *(_BYTE *)(result + v3++) = v4;
  }
  while ( v4 != 0 );
  return result;
}

/* ===== strncmp @ 0x9404D040 size 96 ===== */
__int64 __fastcall strncmp(_BYTE *a1, _BYTE *a2, __int64 a3)
{
  char *v3; // x5
  unsigned __int8 *v4; // x4
  char *v5; // x2
  int v6; // w3
  char v7; // t1
  __int64 result; // x0

  if ( a3 != 0 )
  {
    v3 = a2 + 1;
    if ( *a1 != *a2 )
      return (unsigned int)(char)(*a1 - *a2);
    v4 = a1 + 1;
    if ( *a1 != 0 )
    {
      v5 = &a2[a3];
      do
      {
        if ( v3 == v5 )
          break;
        v6 = *v4++;
        v7 = *v3++;
        result = (unsigned int)(char)(v6 - v7);
        if ( (_BYTE)v6 != v7 )
          return result;
      }
      while ( v6 != 0 );
    }
  }
  return 0;
}

/* ===== strnlen @ 0x9404D0A0 size 68 ===== */
__int64 __fastcall strnlen(_BYTE *a1, __int64 a2)
{
  unsigned __int8 *v2; // x2
  unsigned __int8 *v3; // x1
  int v4; // t1
  unsigned __int8 *v5; // x4

  if ( a2 == 0 || *a1 == 0 )
    return 0;
  v2 = a1 + 1;
  v3 = &a1[a2];
  do
  {
    v5 = v2;
    if ( v2 == v3 )
      return v2 - a1;
    v4 = *v2++;
  }
  while ( v4 != 0 );
  return v5 - a1;
}

/* ===== strstr @ 0x9404D0E4 size 160 ===== */
_BYTE *__fastcall strstr(_BYTE *a1, _BYTE *a2)
{
  int v4; // w21
  _BYTE *result; // x0
  int v6; // w19

  v4 = strlen(a2);
  result = a1;
  if ( v4 != 0 )
  {
    v6 = strlen(a1);
    if ( v4 > v6 )
    {
      return nullptr;
    }
    else
    {
      while ( 1 )
      {
        --v6;
        if ( (unsigned int)memcmp(a1, a2, v4) == 0 )
          break;
        ++a1;
        if ( v4 > v6 )
          return nullptr;
      }
      return a1;
    }
  }
  return result;
}

/* ===== syscall_dispatch @ 0x9404D188 size 72 ===== */
__int64 __fastcall syscall_dispatch(__int64 a1)
{
  unsigned __int64 v1; // x12
  __int64 v7; // x14
  __int64 result; // x0

  v1 = *(unsigned int *)(a1 + 96);
  __asm { MSR             DAIFClr, #7 }
  if ( v1 >= MEMORY[0xFFFFFFFFE003CBA0] || (v7 = *(_QWORD *)(8 * v1 - 536622168)) == 0 )
    v7 = -536686104;
  result = ((__int64 (__fastcall *)(_QWORD, _QWORD, _QWORD, _QWORD))v7)(
             *(_QWORD *)a1,
             *(_QWORD *)(a1 + 8),
             *(_QWORD *)(a1 + 16),
             *(_QWORD *)(a1 + 24));
  __asm { MSR             DAIFSet, #7 }
  *(_QWORD *)a1 = result;
  return result;
}

/* ===== copy_to_user @ 0x9404D224 size 32 ===== */
__int64 __fastcall copy_to_user(__int64 a1, unsigned __int8 *a2, unsigned __int64 a3)
{
  int v4; // t1

  if ( a3 != 0 )
  {
    do
    {
      v4 = *a2++;
      _W9 = v4;
      __asm { STTRB           W9, [X0] }
      ++a1;
    }
    while ( a3-- > 1 );
  }
  return 0;
}

/* ===== copy_from_user @ 0x9404D244 size 32 ===== */
__int64 __fastcall copy_from_user(_BYTE *a1, __int64 _X1, unsigned __int64 a3)
{
  if ( a3 == 0 )
    JUMPOUT(0x9404D23CLL);
  do
  {
    __asm { LDTRB           W9, [X1] }
    ++_X1;
    *a1++ = _X9;
  }
  while ( a3-- > 1 );
  return 0;
}

/* ===== copy_from_user_string @ 0x9404D264 size 44 ===== */
__int64 __fastcall copy_from_user_string(_BYTE *a1, __int64 _X1, __int64 a3)
{
  __int64 v3; // x10
  char v10; // w11

  v3 = _X1;
  do
  {
    __asm { LDTRB           W9, [X1] }
    if ( (_DWORD)_X9 != 0 )
      ++_X1;
    if ( a3 != 0 )
    {
      if ( a3-- != 1 )
        v10 = _X9;
      else
        v10 = 0;
      *a1++ = v10;
    }
  }
  while ( (_DWORD)_X9 != 0 );
  return _X1 - v3;
}

/* ===== user_memset @ 0x9404D290 size 24 ===== */
__int64 __fastcall user_memset(_BYTE *a1, __int64 a2, unsigned __int64 a3)
{
  if ( a3 != 0 )
  {
    do
      *a1++ = 0;
    while ( a3-- > 1 );
  }
  return -40;
}

/* ===== uthread_free_mp_list @ 0x9404D2A8 size 104 ===== */
__int64 __fastcall uthread_free_mp_list(
        __int64 result,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 v9; // x1
  __int64 v10; // x20
  _QWORD *v11; // x2
  _QWORD *v12; // x19
  bool v13; // zf

  v9 = *(_QWORD *)(result + 32) - 24LL;
  v10 = result;
  v11 = *(_QWORD **)(*(_QWORD *)(result + 32) + 8LL);
  v12 = v11 - 3;
  if ( result != v9 )
  {
    do
    {
      *v11 = *(_QWORD *)(v9 + 24);
      *(_QWORD *)(*(_QWORD *)(v9 + 24) + 8LL) = v11;
      *(_QWORD *)(v9 + 32) = 0;
      *(_QWORD *)(v9 + 24) = 0;
      result = free(v9, a2, a3, a4, a5, a6, a7, a8, a9);
      v11 = (_QWORD *)v12[4];
      v13 = v10 == (_QWORD)v12;
      v9 = (__int64)v12;
      v12 = v11 - 3;
    }
    while ( !v13 );
  }
  return result;
}

/* ===== uthread_list_init @ 0x9404D310 size 20 ===== */
// write access to const memory has been detected, the output may be wrong!
void uthread_list_init()
{
  qword_9407A010 = (__int64)&qword_9407A010;
  off_9407A018 = &qword_9407A010;
  JUMPOUT(0x9404DCD4LL);
}

/* ===== uthread_start @ 0x9404D324 size 24 ===== */
unsigned __int64 *__fastcall uthread_start(__int64 a1)
{
  _DWORD *v1; // x0

  if ( a1 != 0 && (v1 = *(_DWORD **)(a1 + 120)) != nullptr )
    return thread_resume_full(v1);
  else
    return (unsigned __int64 *)4294967288LL;
}

/* ===== uthread_exit @ 0x9404D33C size 240 ===== */
void __fastcall __noreturn uthread_exit(
        int a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  __int64 *v10; // x19
  double v11; // d0
  double v12; // d1
  double v13; // d2
  double v14; // d3
  double v15; // d4
  double v16; // d5
  double v17; // d6
  double v18; // d7
  _QWORD *v19; // x1
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  _QWORD *v33; // x1

  v10 = *(__int64 **)(_ReadStatusReg(TPIDR_EL1) + 688);
  if ( v10 != nullptr )
  {
    ta_manager_noop();
    uthread_free_mp_list((__int64)v10, a2, a3, a4, a5, a6, a7, a8, a9);
    free(v10[2], v11, v12, v13, v14, v15, v16, v17, v18);
    uthread_destroy_aspace(v10);
    if ( (_ReadStatusReg(DAIF) & 0x80) == 0 )
      goto LABEL_6;
    spin_lock((unsigned __int64 *)&qword_9407A008);
    v19 = (_QWORD *)v10[17];
    *v19 = v10[16];
    *(_QWORD *)(v10[16] + 8) = v19;
    v10[17] = 0;
    v10[16] = 0;
    spin_unlock((unsigned __int64 *)&qword_9407A008);
    while ( 1 )
    {
      free((__int64)v10, v20, v21, v22, v23, v24, v25, v26, v27);
LABEL_5:
      thread_exit(a1);
LABEL_6:
      __asm { MSR             DAIFSet, #2 }
      spin_lock((unsigned __int64 *)&qword_9407A008);
      v33 = (_QWORD *)v10[17];
      *v33 = v10[16];
      *(_QWORD *)(v10[16] + 8) = v33;
      v10[17] = 0;
      v10[16] = 0;
      spin_unlock((unsigned __int64 *)&qword_9407A008);
      __asm { MSR             DAIFClr, #2 }
    }
  }
  printf(
    "%s:%d: WARNING: unexpected call on kernel thread %s!",
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    "uthread_exit",
    386,
    _ReadStatusReg(TPIDR_EL1) + 696);
  goto LABEL_5;
}

/* ===== arch_mmu_switch_aspace @ 0x9404D42C size 12 ===== */
__int64 __fastcall arch_mmu_switch_aspace(__int64 a1, __int64 a2)
{
  return arch_mmu_switch_ttbr(*(_QWORD *)(a1 + 688), *(_QWORD *)(a2 + 688));
}

/* ===== uthread_map @ 0x9404D438 size 944 ===== */
__int64 __fastcall uthread_map(
        unsigned __int64 *a1,
        unsigned __int64 *a2,
        _BYTE *a3,
        unsigned __int64 a4,
        int a5,
        int a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13,
        double a14)
{
  __int64 v14; // x20
  __int64 v15; // x30
  __int64 v17; // x19
  double v23; // d0
  double v24; // d1
  double v25; // d2
  double v26; // d3
  double v27; // d4
  double v28; // d5
  double v29; // d6
  double v30; // d7
  unsigned __int64 v31; // x19
  __int64 v32; // x27
  __int64 v33; // x0
  __int64 v34; // x24
  double v35; // d0
  double v36; // d1
  double v37; // d2
  double v38; // d3
  double v39; // d4
  double v40; // d5
  double v41; // d6
  double v42; // d7
  unsigned __int64 v43; // x5
  unsigned __int64 v44; // x0
  unsigned __int64 v45; // x1
  unsigned __int64 v46; // x2
  unsigned __int64 v47; // x3
  __int64 v48; // x0
  unsigned __int64 v49; // x1
  unsigned int v50; // w24
  unsigned __int64 v51; // x1
  __int64 v52; // x6
  __int64 v53; // x7
  unsigned __int64 *v54; // x2
  unsigned __int64 v55; // x0
  unsigned __int64 v56; // x4
  unsigned __int64 i; // x1
  unsigned __int64 v58; // x3
  __int64 v59; // x5
  unsigned __int64 v60; // x1
  __int64 v62; // x0
  __int64 v63; // x2
  unsigned __int64 *v64; // x2
  __int64 v65; // x5
  unsigned __int64 v66; // x7
  unsigned __int64 *v67; // x4
  __int64 v68; // x1
  unsigned __int64 v69; // x3
  unsigned __int64 v70; // x1
  __int64 v71; // x0
  __int64 v72; // x1
  __int64 v73; // x2
  __int64 v74; // x3
  __int64 v75; // x4
  __int64 v76; // x5

  v17 = v15;
  if ( a1 == nullptr )
  {
    v55 = panic(
            v15,
            "DEBUG ASSERT FAILED at (%s:%d): %s\n",
            a7,
            a8,
            a9,
            a10,
            a11,
            a12,
            a13,
            a14,
            "lk/trusty/lib/uthread/uthread.c",
            45,
            "ut");
    goto LABEL_58;
  }
  v14 = (__int64)(a1 + 5);
  mutex_acquire_timeout((__int64)(a1 + 5), 0xFFFFFFFFLL);
  if ( a2 == nullptr || a3 == nullptr )
    goto LABEL_61;
  if ( (a4 & 0xFFF) != 0 )
  {
    v50 = -7;
    goto LABEL_38;
  }
  if ( (a5 & 0x100) != 0 )
  {
    v31 = *a2;
    goto LABEL_7;
  }
  if ( (a5 & 0x40) == 0 )
  {
    v51 = a1[4];
    v52 = (unsigned int)(a6 - 1);
    v53 = (unsigned int)-a6;
    v54 = (unsigned __int64 *)(v51 - 24);
    v55 = (v52 + *a1) & v53;
    v56 = v55 + a4;
    if ( a1 != (unsigned __int64 *)(v51 - 24) )
    {
      for ( i = *(_QWORD *)(v51 - 24); i < v56; i = *(_QWORD *)(v58 - 24) )
      {
        v58 = v54[4];
        v59 = v52 + v54[1];
        v54 = (unsigned __int64 *)(v58 - 24);
        v60 = (v59 + i) & v53;
        if ( v55 < v60 )
          v55 = v60;
        v56 = v55 + a4;
        if ( a1 == v54 )
          break;
      }
    }
    if ( a1[12] >= v56 && v55 <= v56 )
    {
LABEL_32:
      *a2 = v55;
      v31 = v55;
      v50 = -5;
      if ( v55 == 0 )
        goto LABEL_38;
LABEL_7:
      if ( v31 < v31 + a4 )
      {
        if ( (a5 & 0x20) != 0 )
        {
          v32 = 1;
          v33 = malloc(48);
          v34 = v33;
          if ( v33 != 0 )
          {
LABEL_10:
            *(_QWORD *)v34 = v31;
            *(_QWORD *)(v34 + 8) = a4;
            *(_DWORD *)(v34 + 16) = a5;
            *(_DWORD *)(v34 + 20) = a6;
            memcpy((_BYTE *)(v33 + 40), a3, 8 * v32);
            v43 = a1[12];
            if ( (*(_DWORD *)(v34 + 16) & 0x40) != 0 && v43 > *(_QWORD *)v34 )
              v43 = *(_QWORD *)v34 & 0xFFFFFFFFFFF00000LL;
            v44 = a1[4];
            v45 = v44 - 24;
            if ( a1 != (unsigned __int64 *)(v44 - 24) )
            {
              v46 = *(_QWORD *)(v44 - 24);
              v47 = *(_QWORD *)v34;
              if ( *(_QWORD *)v34 < v46 )
              {
LABEL_42:
                if ( v47 + *(_QWORD *)(v34 + 8) > v46 )
                {
LABEL_41:
                  v62 = v34;
                  v50 = -8;
                  free(v62, v35, v36, v37, v38, v39, v40, v41, v42);
                  goto LABEL_38;
                }
                *(_QWORD *)(v34 + 24) = *(_QWORD *)(v45 + 24);
                a1[12] = v43;
                v63 = *(_QWORD *)(v45 + 24);
                *(_QWORD *)(v34 + 32) = v45 + 24;
                *(_QWORD *)(v63 + 8) = v34 + 24;
                *(_QWORD *)(v45 + 24) = v34 + 24;
                goto LABEL_21;
              }
              if ( v46 + *(_QWORD *)(v44 - 16) > v47 )
                goto LABEL_41;
              while ( 1 )
              {
                v48 = *(_QWORD *)(v45 + 32);
                v45 = v48 - 24;
                if ( a1 == (unsigned __int64 *)(v48 - 24) )
                  break;
                v46 = *(_QWORD *)(v48 - 24);
                if ( v46 > v47 )
                  goto LABEL_42;
                if ( v46 + *(_QWORD *)(v48 - 16) > v47 )
                  goto LABEL_41;
              }
            }
            v49 = a1[3];
            *(_QWORD *)(v34 + 24) = v49;
            a1[12] = v43;
            *(_QWORD *)(v34 + 32) = a1 + 3;
            *(_QWORD *)(v49 + 8) = v34 + 24;
            a1[3] = v34 + 24;
LABEL_21:
            v50 = uthread_arch_map(a1, v34);
LABEL_38:
            mutex_release(v14);
            return v50;
          }
        }
        else
        {
          v32 = (unsigned int)(a4 >> 12);
          v33 = malloc(8 * (v32 + 5));
          v34 = v33;
          if ( v33 != 0 )
            goto LABEL_10;
        }
        v50 = -5;
        goto LABEL_38;
      }
LABEL_61:
      v50 = -8;
      goto LABEL_38;
    }
LABEL_37:
    *a2 = 0;
    v50 = -5;
    goto LABEL_38;
  }
  v64 = (unsigned __int64 *)a1[3];
  v65 = (unsigned int)-a6;
  v55 = (0x2000000 - a4) & v65;
  v66 = v55 + a4;
  if ( a1 + 3 == v64 )
    goto LABEL_58;
  if ( v64 == nullptr )
    goto LABEL_58;
  v67 = v64 - 3;
  if ( v64 == (unsigned __int64 *)24 )
    goto LABEL_58;
  v68 = *(v64 - 3);
  v69 = v68 + *(v64 - 2);
  if ( v55 < v69 )
  {
    while ( (*(_DWORD *)(v64 - 1) & 0x40) != 0 )
    {
      v64 = (unsigned __int64 *)v67[3];
      v70 = (v68 - a4) & v65;
      if ( v55 > v70 )
        v55 = v70;
      v66 = v55 + a4;
      if ( a1 + 3 == v64 )
        goto LABEL_58;
      if ( v64 == nullptr )
        goto LABEL_58;
      v67 = v64 - 3;
      if ( v64 == (unsigned __int64 *)24 )
        goto LABEL_58;
      v68 = *(v64 - 3);
      v69 = v68 + *(v64 - 2);
      if ( v69 <= v55 )
        goto LABEL_34;
    }
    goto LABEL_37;
  }
LABEL_34:
  if ( a1[12] <= v55 )
  {
LABEL_58:
    if ( v55 >= *a1 && v55 <= v66 )
      goto LABEL_32;
    goto LABEL_37;
  }
  if ( (v67[2] & 0x40) == 0 )
  {
    if ( (v55 & 0xFFFFFFFFFFF00000LL) < v69 )
      goto LABEL_37;
    goto LABEL_58;
  }
  v71 = panic(
          v17,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          v23,
          v24,
          v25,
          v26,
          v27,
          v28,
          v29,
          v30,
          "lk/trusty/lib/uthread/uthread.c",
          91,
          "(mp->flags & UTM_NS_MEM) == 0");
  return uthread_create(v71, v72, v73, v74, v75, v76);
}

/* ===== uthread_create @ 0x9404D7E8 size 592 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall uthread_create(__int64 a1, __int64 a2, unsigned int a3, __int64 a4, unsigned __int64 a5, __int64 a6)
{
  __int64 v12; // x0
  __int64 v13; // x19
  unsigned __int64 v14; // x0
  double v15; // d0
  double v16; // d1
  double v17; // d2
  double v18; // d3
  double v19; // d4
  double v20; // d5
  double v21; // d6
  double v22; // d7
  double v23; // d0
  double v24; // d1
  double v25; // d2
  double v26; // d3
  double v27; // d4
  double v28; // d5
  double v29; // d6
  double v30; // d7
  double v31; // d0
  double v32; // d1
  double v33; // d2
  double v34; // d3
  double v35; // d4
  double v36; // d5
  double v37; // d6
  double v38; // d7
  __int64 v39; // x0
  double v40; // d0
  double v41; // d1
  double v42; // d2
  double v43; // d3
  double v44; // d4
  double v45; // d5
  double v46; // d6
  double v47; // d7
  unsigned __int64 v57; // [xsp+60h] [xbp+60h] BYREF
  __int64 v58; // [xsp+68h] [xbp+68h] BYREF

  v12 = calloc(1, 168);
  v13 = v12;
  if ( v12 == 0 )
    return 0;
  *(_QWORD *)(v12 + 32) = v12 + 24;
  *(_QWORD *)(v12 + 24) = v12 + 24;
  mutex_init(v12 + 40);
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_9407A008);
    dword_9407A000 = 1;
    spin_unlock((unsigned __int64 *)&qword_9407A008);
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)&qword_9407A008);
    dword_9407A000 = 1;
    spin_unlock((unsigned __int64 *)&qword_9407A008);
    __asm { MSR             DAIFClr, #2 }
  }
  *(_DWORD *)(v13 + 104) = 0;
  *(_QWORD *)(v13 + 144) = a6;
  *(_QWORD *)(v13 + 8) = a2;
  *(_QWORD *)(v13 + 96) = 0x2000000;
  v14 = memalign(0x1000u, a5);
  *(_QWORD *)(v13 + 16) = v14;
  if ( v14 == 0 )
  {
LABEL_15:
    free(v13, v15, v16, v17, v18, v19, v20, v21, v22);
    return 0;
  }
  v57 = a4 - a5;
  v58 = pmm_phys_to_virt(v14);
  if ( (unsigned int)uthread_map(
                       (unsigned __int64 *)v13,
                       &v57,
                       &v58,
                       a5,
                       307,
                       4096,
                       v23,
                       v24,
                       v25,
                       v26,
                       v27,
                       v28,
                       v29,
                       v30) != 0 )
  {
LABEL_14:
    free(*(_QWORD *)(v13 + 16), v31, v32, v33, v34, v35, v36, v37, v38);
    goto LABEL_15;
  }
  *(_QWORD *)v13 = a4;
  v39 = thread_create_simple(a1, -536683304, 0, a3, 4096);
  *(_QWORD *)(v13 + 120) = v39;
  if ( v39 == 0 || (unsigned int)uthread_set_aspace(v13) != 0 )
  {
    uthread_free_mp_list(v13, v40, v41, v42, v43, v44, v45, v46, v47);
    goto LABEL_14;
  }
  *(_QWORD *)(*(_QWORD *)(v13 + 120) + 688LL) = v13;
  if ( (_ReadStatusReg(DAIF) & 0x80) != 0 )
  {
    spin_lock((unsigned __int64 *)&qword_9407A008);
    *(_QWORD *)(v13 + 128) = &qword_9407A010;
    *(_QWORD *)(v13 + 136) = 0;
    MEMORY[0] = v13 + 128;
    off_9407A018 = (_UNKNOWN *)(v13 + 128);
    spin_unlock((unsigned __int64 *)&qword_9407A008);
    return v13;
  }
  else
  {
    __asm { MSR             DAIFSet, #2 }
    spin_lock((unsigned __int64 *)&qword_9407A008);
    *(_QWORD *)(v13 + 128) = &qword_9407A010;
    *(_QWORD *)(v13 + 136) = 0;
    MEMORY[0] = v13 + 128;
    off_9407A018 = (_UNKNOWN *)(v13 + 128);
    spin_unlock((unsigned __int64 *)&qword_9407A008);
    __asm { MSR             DAIFClr, #2 }
    return v13;
  }
}

/* ===== uthread_unmap @ 0x9404DA38 size 460 ===== */
__int64 __fastcall uthread_unmap(
        _QWORD *a1,
        unsigned __int64 a2,
        __int64 a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  __int64 v11; // x22
  __int64 v12; // x30
  __int64 v14; // x23
  __int64 v16; // x19
  unsigned __int64 v17; // x0
  unsigned int v18; // w20
  double v20; // d0
  double v21; // d1
  double v22; // d2
  double v23; // d3
  double v24; // d4
  double v25; // d5
  double v26; // d6
  double v27; // d7
  _QWORD *v28; // x0
  _QWORD *v29; // x1
  __int64 v30; // x0
  __int64 v31; // x1
  __int64 v32; // x2

  v14 = v12;
  if ( a1 == nullptr )
  {
    panic(
      v12,
      "DEBUG ASSERT FAILED at (%s:%d): %s\n",
      a4,
      a5,
      a6,
      a7,
      a8,
      a9,
      a10,
      a11,
      "lk/trusty/lib/uthread/uthread.c",
      45,
      "ut");
    goto LABEL_25;
  }
  v11 = (__int64)(a1 + 5);
  mutex_acquire_timeout((__int64)(a1 + 5), 0xFFFFFFFFLL);
  if ( a2 == 0 )
  {
LABEL_25:
    v18 = -8;
    goto LABEL_10;
  }
  if ( a2 > a2 + a3 || (v16 = a1[4] - 24LL, a1 == (_QWORD *)v16) )
  {
LABEL_9:
    v18 = -2;
LABEL_10:
    mutex_release(v11);
    return v18;
  }
  while ( 1 )
  {
    if ( a2 >= *(_QWORD *)v16 )
    {
      v17 = *(_QWORD *)v16 + *(_QWORD *)(v16 + 8);
      if ( a2 + a3 <= v17 && a2 < v17 )
        break;
    }
    v16 = *(_QWORD *)(v16 + 32) - 24LL;
    if ( a1 == (_QWORD *)v16 )
      goto LABEL_9;
  }
  v18 = uthread_arch_unmap(a1, v16);
  if ( v18 != 0 )
    goto LABEL_10;
  if ( (*(_DWORD *)(v16 + 16) & 0x40) == 0 )
  {
    v29 = *(_QWORD **)(v16 + 32);
    v28 = *(_QWORD **)(v16 + 24);
    goto LABEL_22;
  }
  v28 = *(_QWORD **)(v16 + 24);
  if ( a1 + 3 != v28 && v28 != nullptr && v28 != (_QWORD *)24 && (*(_DWORD *)(v28 - 1) & 0x40) != 0 )
  {
    v29 = *(_QWORD **)(v16 + 32);
    goto LABEL_22;
  }
  v29 = *(_QWORD **)(v16 + 32);
  if ( a1 + 3 == v29 || v29 == nullptr || v29 == (_QWORD *)24 )
  {
    a1[12] = 0x2000000;
    goto LABEL_22;
  }
  if ( (*(_DWORD *)(v29 - 1) & 0x40) != 0 )
  {
    a1[12] = *(v29 - 3) & 0xFFFFFFFFFFF00000LL;
LABEL_22:
    *v29 = v28;
    *(_QWORD *)(*(_QWORD *)(v16 + 24) + 8LL) = v29;
    *(_QWORD *)(v16 + 32) = 0;
    *(_QWORD *)(v16 + 24) = 0;
    free(v16, v20, v21, v22, v23, v24, v25, v26, v27);
    mutex_release(v11);
    return 0;
  }
  v30 = panic(
          v14,
          "DEBUG ASSERT FAILED at (%s:%d): %s\n",
          v20,
          v21,
          v22,
          v23,
          v24,
          v25,
          v26,
          v27,
          "lk/trusty/lib/uthread/uthread.c",
          252,
          "item->flags & UTM_NS_MEM");
  return uthread_is_mapped(v30, v31, v32);
}

/* ===== uthread_is_mapped @ 0x9404DC04 size 212 ===== */
__int64 __fastcall uthread_is_mapped(
        unsigned __int64 *a1,
        unsigned __int64 a2,
        __int64 a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11)
{
  __int64 v11; // x30
  __int64 v14; // x22
  unsigned __int64 *v15; // x0
  BOOL v16; // w19

  if ( a1 == nullptr )
    return panic(
             v11,
             "DEBUG ASSERT FAILED at (%s:%d): %s\n",
             a4,
             a5,
             a6,
             a7,
             a8,
             a9,
             a10,
             a11,
             "lk/trusty/lib/uthread/uthread.c",
             45,
             "ut");
  v14 = (__int64)(a1 + 5);
  mutex_acquire_timeout((__int64)(a1 + 5), 0xFFFFFFFFLL);
  if ( a2 > a2 + a3 || (v15 = (unsigned __int64 *)(a1[4] - 24), a1 == v15) )
  {
LABEL_7:
    v16 = false;
  }
  else
  {
    while ( 1 )
    {
      if ( a2 >= *v15 )
      {
        v16 = a2 + a3 <= *v15 + v15[1] && a2 < *v15 + v15[1];
        if ( a2 + a3 <= *v15 + v15[1] && a2 < *v15 + v15[1] )
          break;
      }
      v15 = (unsigned __int64 *)(v15[4] - 24);
      if ( a1 == v15 )
        goto LABEL_7;
    }
  }
  mutex_release(v14);
  return v16;
}

/* ===== uthread_return_to_user @ 0x9404DCD8 size 56 ===== */
void __noreturn uthread_return_to_user()
{
  unsigned __int64 v0; // x3

  v0 = *(_QWORD *)(*(_QWORD *)(_ReadStatusReg(TPIDR_EL1) + 688) + 8LL);
  __asm { MSR             DAIFSet, #2 }
  _WriteStatusReg(SPSR_EL1, 0x10u);
  _WriteStatusReg(ELR_EL1, v0);
  __asm { ERET }
}

/* ===== nullsub_10 @ 0x9404DD10 size 4 ===== */
void nullsub_10()
{
  ;
}

/* ===== arch_mmu_switch_ttbr @ 0x9404DD14 size 124 ===== */
__int64 __fastcall arch_mmu_switch_ttbr(__int64 result, __int64 a2)
{
  __int64 v2; // x19

  if ( result == 0 || a2 != 0 )
  {
    if ( a2 != 0 )
    {
      v2 = result;
      result = pmm_phys_to_virt(*(_QWORD *)(a2 + 112)) | ((unsigned __int64)*(unsigned int *)(a2 + 152) << 48);
      _WriteStatusReg(TTBR0_EL1, result);
      __isb(0xFu);
      if ( v2 == 0 )
      {
        _WriteStatusReg(TCR_EL1, 0x2B5233527uLL);
        __isb(0xFu);
        return 0x2B5233527LL;
      }
    }
  }
  else
  {
    result = 0x2B52335A7LL;
    _WriteStatusReg(TCR_EL1, 0x2B52335A7uLL);
    __isb(0xFu);
  }
  return result;
}

/* ===== uthread_set_aspace @ 0x9404DD90 size 24 ===== */
__int64 __fastcall uthread_set_aspace(__int64 a1)
{
  *(_DWORD *)(a1 + 152) = *(_DWORD *)(a1 + 104);
  *(_QWORD *)(a1 + 160) = a1;
  return 0;
}

/* ===== uthread_destroy_aspace @ 0x9404DDA8 size 68 ===== */
__int64 __fastcall uthread_destroy_aspace(__int64 a1)
{
  double v2; // d0
  double v3; // d1
  double v4; // d2
  double v5; // d3
  double v6; // d4
  double v7; // d5
  double v8; // d6
  double v9; // d7

  arm64_mmu_unmap(0, 0x2000000u, 0, 25, 0x15u, 0xCu, *(_QWORD *)(a1 + 112), *(_DWORD *)(a1 + 152));
  return free(*(_QWORD *)(a1 + 112), v2, v3, v4, v5, v6, v7, v8, v9);
}

/* ===== uthread_alloc_aspace @ 0x9404DDEC size 72 ===== */
__int64 __fastcall uthread_alloc_aspace(__int64 a1)
{
  __int64 v2; // x0

  v2 = memalign(0x80u, 128);
  *(_QWORD *)(a1 + 112) = v2;
  if ( v2 == 0 )
    return 4294967291LL;
  memset(v2, 0, 0x80u);
  return 0;
}

/* ===== uthread_arch_map @ 0x9404DE34 size 420 ===== */
__int64 __fastcall uthread_arch_map(
        __int64 a1,
        __int64 a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10)
{
  __int64 v10; // x30
  __int64 v12; // x21
  __int64 v13; // x19
  unsigned __int64 v14; // x0
  __int64 v15; // x25
  int v16; // w19
  __int64 v17; // x20
  __int64 v18; // x24
  __int64 v19; // x24
  unsigned __int64 v20; // x19
  __int64 *v21; // x23
  __int64 v22; // x22
  unsigned __int64 v23; // x20
  unsigned int v24; // w27
  unsigned int i; // w22
  __int64 result; // x0

  v12 = a1;
  v13 = v10;
  if ( *(_QWORD *)(a1 + 112) == 0 )
    goto LABEL_20;
  while ( 1 )
  {
    v14 = *(_QWORD *)(a2 + 8);
    v15 = v14 & 0xFFF;
    if ( (v14 & 0xFFF) == 0 )
      break;
    a1 = panic(
           v13,
           "ASSERT FAILED at (%s:%d): %s\n",
           a3,
           a4,
           a5,
           a6,
           a7,
           a8,
           a9,
           a10,
           "lk/trusty/lib/uthread/arch/arm64/uthread.c",
           138,
           "!(mp->size & USER_PAGE_MASK)");
LABEL_20:
    result = uthread_alloc_aspace(a1);
    if ( (_DWORD)result != 0 )
      return result;
  }
  v16 = *(_DWORD *)(a2 + 16);
  v17 = 3104;
  v18 = 64;
  if ( (v16 & 0x40) == 0 )
    v17 = 3072;
  if ( (v16 & 2) == 0 )
    v18 = 192;
  v19 = v18 | v17;
  if ( (v16 & 0x80) == 0 )
    v19 |= 0x308uLL;
  v20 = 4096;
  if ( (*(_DWORD *)(a2 + 16) & 0x20) != 0 )
    v20 = *(_QWORD *)(a2 + 8);
  if ( v14 / v20 == 0 )
    return 0;
  v21 = (__int64 *)(a2 + 40);
  v22 = 0;
  v23 = 0;
  while ( 1 )
  {
    v24 = arm64_mmu_map(
            v22 + *(_QWORD *)a2,
            *v21,
            v20,
            v19,
            0,
            25,
            0x15u,
            0xCu,
            *(_QWORD *)(v12 + 112),
            *(_DWORD *)(v12 + 152));
    if ( v24 != 0 )
      break;
    ++v23;
    v22 += v20;
    ++v21;
    if ( *(_QWORD *)(a2 + 8) / v20 <= v23 )
      return 0;
  }
  for ( i = 0; v23 > i; v15 = i )
  {
    arm64_mmu_unmap(*(_QWORD *)a2 + v15 * v20, v20, 0, 25, 0x15u, 0xCu, *(_QWORD *)(v12 + 112), *(_DWORD *)(v12 + 152));
    ++i;
  }
  return v24;
}

/* ===== uthread_arch_unmap @ 0x9404DFD8 size 40 ===== */
__int64 __fastcall uthread_arch_unmap(__int64 a1, __int64 a2)
{
  return arm64_mmu_unmap(
           *(_QWORD *)a2,
           *(_QWORD *)(a2 + 8),
           0,
           25,
           0x15u,
           0xCu,
           *(_QWORD *)(a1 + 112),
           *(_DWORD *)(a1 + 152));
}

/* ===== invalid_exception_stub @ 0x9404E298 size 16 ===== */
void __fastcall __noreturn invalid_exception_stub(__int64 a1, char _W1)
{
  __asm { WHILEWR         P0.H, X1, X24 }
  __udf(0xA78u);
}

/* ===== invalid_handle_stub @ 0x94051138 size 24 ===== */
void __noreturn invalid_handle_stub()
{
  __udf(0);
}

/* ===== fp_spi_sync_stub @ 0x94053770 size 28 ===== */
void __fastcall __noreturn fp_spi_sync_stub(double a1, double a2, double a3, __n128 _Q3)
{
  __asm
  {
    FCMLA           Z6.H, P4/M, Z3.H, Z31.H, #270
    FNMLS           Z18.H, P2/M, Z11.H, Z22.H
    FMLS            Z18.H, P0/M, Z3.H, Z2.H
    FNMLS           Z6.H, P3/M, Z27.H, Z18.H
  }
  __udf(0xA63u);
}

/* ===== kbc_set_bit_log @ 0x94054F40 size 20 ===== */
void __fastcall kbc_set_bit_log(int a1, double a2, double a3, double a4, double a5, double a6, __n128 a7)
{
  __int64 v7; // x27

  *(_BYTE *)(v7 + 2073) = a7.n128_u8[0];
  if ( a1 != 0 )
    __udf(0xA78u);
  JUMPOUT(0x940B53F0LL);
}

/* ===== kbc_set_bit_log2 @ 0x94054F58 size 20 ===== */
void __fastcall kbc_set_bit_log2(int a1, double a2, double a3, double a4, double a5, double a6, __n128 a7)
{
  __int64 v7; // x27

  __asm { FNMLS           Z1.H, P1/M, Z19.H, Z20.H }
  *(_BYTE *)(v7 + 2073) = a7.n128_u8[0];
  if ( a1 != 0 )
    __udf(0xA78u);
  JUMPOUT(0x940B5408LL);
}

/* ===== kbc_read_footer_stub @ 0x940570A8 size 20 ===== */
void __noreturn kbc_read_footer_stub()
{
  __asm { FNMLS           Z3.H, P0/M, Z11.H, Z20.H }
  __udf(0);
}

/* ===== vbmeta_check_log_stub @ 0x94057450 size 20 ===== */
void __fastcall __noreturn vbmeta_check_log_stub(
        double a1,
        double a2,
        double a3,
        __n128 _Q3,
        double a5,
        __n128 _Q5,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        __int64 _X3)
{
  __asm { FNMLS           Z22.H, P0/M, Z19.H, Z13.H }
  __asm
  {
    STGP            X5, X29, [X3,#-0x100]
    FMUL            Z19.H, Z3.H, Z5.H[0]
  }
  __udf(0xA2Eu);
}


// END total=715 ok=715 fail=0
