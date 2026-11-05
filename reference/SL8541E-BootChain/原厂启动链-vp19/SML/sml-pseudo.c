// pseudo-C decompilation of sml.elf
/* ===== bl31_entrypoint @ 0x94000000 size 212 ===== */
__int64 __fastcall bl31_entrypoint(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12,
        __int64 a13,
        __int64 a14,
        __int64 a15,
        __int64 a16,
        __int64 a17,
        __int64 a18,
        __int64 a19,
        __int64 a20,
        __int64 a21,
        __int64 a22,
        __int64 a23,
        __int64 a24,
        __int64 a25,
        __int64 a26,
        __int64 a27,
        __int64 a28,
        __int64 a29,
        __int64 a30,
        __int64 a31,
        __int64 a32,
        __int64 a33,
        __int64 a34,
        __int64 a35,
        __int64 a36,
        __int64 a37,
        __int64 a38,
        __int64 a39,
        unsigned __int64 a40,
        unsigned __int64 a41,
        __int64 *a42,
        unsigned __int64 a43,
        unsigned __int64 a44)
{
  __int64 (*v44)(void); // x0
  __int64 v51; // x0
  __int64 v53; // x0
  __int64 v54; // x0
  unsigned __int64 v56; // x16
  unsigned __int64 v57; // x17

  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFDFFFFFFLL);
  __isb(0xFu);
  v44 = (__int64 (*)(void))get_zero();
  if ( v44 == nullptr )
  {
    cpu_init_early();
    _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) | 0x100A);
    __isb(0xFu);
    set_tpidr_el3_cpu();
    _WriteStatusReg(VBAR_EL3, (unsigned __int64)sub_94008000);
    __isb(0xFu);
    _WriteStatusReg(SCR_EL3, 0x238u);
    _WriteStatusReg(MDCR_EL3, 0);
    __asm { MSR             DAIFClr, #4 }
    _WriteStatusReg(CPTR_EL3, _ReadStatusReg(CPTR_EL3) & 0x7FEFFBFF);
    nullsub_7();
    dcache_invalidate(off_9400C000, 2483113984LL - (_QWORD)off_9400C000);
    zeromem(2483081408LL, 13184);
    v51 = zeromem(2483109888LL, 32);
    __asm { MSR             SPSel, #0 }
    set_tpidr_el3(v51);
    v53 = bl31_early_setup(0, 0);
    v54 = sprd_bl31_setup_call(v53);
    bl31_main_init(v54);
    dcache_clean(off_9400C000, (char *)qword_9400C090 - (char *)off_9400C000);
    dcache_clean(2483081408LL, 13184);
    __asm { MSR             SPSel, #1 }
    a42 = &a9;
    v56 = a43;
    v57 = a44;
    _WriteStatusReg(SCR_EL3, a41);
    _WriteStatusReg(SPSR_EL3, v56);
    _WriteStatusReg(ELR_EL3, v57);
    _WriteStatusReg(SP_EL0, a40);
    __asm { ERET }
  }
  return v44();
}

/* ===== bl31_warm_reset_vector @ 0x940000F8 size 116 ===== */
void bl31_warm_reset_vector()
{
  unsigned __int64 v5; // x0
  __int64 v7; // x0

  if ( MEMORY[0x9400D0C0] != 0 )
    get_pc();
  cpu_init_early();
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) | 0x100A);
  __isb(0xFu);
  set_tpidr_el3_cpu();
  _WriteStatusReg(VBAR_EL3, (unsigned __int64)sub_94008000);
  __isb(0xFu);
  _WriteStatusReg(SCR_EL3, 0x238u);
  _WriteStatusReg(MDCR_EL3, 0);
  __asm { MSR             DAIFClr, #4 }
  v5 = _ReadStatusReg(CPTR_EL3) & 0x7FEFFBFF;
  _WriteStatusReg(CPTR_EL3, v5);
  __asm { MSR             SPSel, #0 }
  set_tpidr_el3(v5);
  v7 = enable_mmu_thunk(1);
  psci_cpu_on_handler(v7);
  JUMPOUT(0x94007A78LL);
}

/* ===== bl31_early_setup @ 0x940001C8 size 28 ===== */
__int64 bl31_early_setup()
{
  __int64 v0; // x0
  __int64 v1; // x0
  __int64 v2; // x0

  v0 = sprd_bl31_early_platform_setup();
  v1 = set_boot_flag(v0);
  v2 = get_boot_flag(v1);
  return clear_boot_flag(v2);
}

/* ===== set_psci_state_off @ 0x940001E4 size 16 ===== */
_BYTE *__fastcall set_psci_state_off(_BYTE *result)
{
  *result = 2;
  result[1] = 2;
  return result;
}

/* ===== cpu_standby_wait @ 0x940001F4 size 56 ===== */
__int64 __fastcall cpu_standby_wait(__int64 a1)
{
  while ( (unsigned int)get_affinity_state(a1) != 7 )
    ;
  gicv2_cpuif_disable_cpu(a1);
  return 0;
}

/* ===== system_reset_unhandled @ 0x9400022C size 28 ===== */
void __noreturn system_reset_unhandled()
{
  __int64 v0; // x0

  __wfi();
  v0 = printf_impl("ERROR:   SPRD System Reset: operation not handled.\n");
  panic(v0);
}

/* ===== system_off_unhandled @ 0x94000248 size 28 ===== */
void __noreturn system_off_unhandled()
{
  __int64 v0; // x0

  __wfi();
  v0 = printf_impl("ERROR:   SPRD System Off: operation not handled.\n");
  panic(v0);
}

/* ===== sprd_cpu_standby @ 0x94000264 size 68 ===== */
__int64 __fastcall sprd_cpu_standby(__int64 result)
{
  result = (unsigned __int8)result;
  if ( (unsigned __int8)result != 1 )
    assert_fail("sprd_cpu_standby", "plat/sprd/sharkle/pm.c", 137, "cpu_state == ARM_LOCAL_STATE_RET");
  __dsb(0xFu);
  __wfi();
  return result;
}

/* ===== sprd_validate_power_state @ 0x940002A8 size 80 ===== */
__int64 __fastcall sprd_validate_power_state(__int64 a1, unsigned int a2)
{
  __int64 v3; // x0

  if ( a2 > 1 )
    return 4294967294LL;
  v3 = get_affinity_state(a1);
  if ( (_DWORD)v3 == -1 )
    return 4294967294LL;
  if ( a2 == 1 )
    return ((v3 ^ 0x40000000) & 0x40000000) != 0;
  return ((v3 ^ 0x20000000) & 0x20000000) != 0;
}

/* ===== sprd_pwr_domain_suspend @ 0x940002F8 size 148 ===== */
__int64 __fastcall sprd_pwr_domain_suspend(unsigned __int8 *a1)
{
  __int64 result; // x0
  __int64 v3; // x0
  unsigned __int64 StatusReg; // x19

  result = *a1;
  if ( (_DWORD)result != 1 )
  {
    if ( (_DWORD)result != 2 )
      assert_fail(
        "sprd_pwr_domain_suspend",
        "plat/sprd/sharkle/pm.c",
        216,
        "target_state->pwr_domain_state[ARM_PWR_LVL0] == ARM_LOCAL_STATE_OFF");
    v3 = gicv2_enable_ppi(_ReadStatusReg(MPIDR_EL1));
    gicv2_cpuif_disable_thunk(v3);
    gicv2_cpuif_enable_cpu(_ReadStatusReg(MPIDR_EL1));
    result = a1[1];
    if ( (_DWORD)result == 2 )
    {
      MEMORY[0x9400D0C0] = 1;
      StatusReg = _ReadStatusReg(MPIDR_EL1);
      read_boot_flag();
      return sprd_gic_cpuif_init(StatusReg);
    }
  }
  return result;
}

/* ===== sprd_power_domain_on_finish @ 0x9400038C size 104 ===== */
__int64 __fastcall sprd_power_domain_on_finish(_BYTE *a1)
{
  unsigned __int64 StatusReg; // x19
  __int64 v2; // x0
  __int64 v3; // x0

  if ( *a1 != 2 )
    assert_fail(
      "sprd_power_domain_on_finish_common",
      "plat/sprd/sharkle/pm.c",
      100,
      "target_state->pwr_domain_state[ARM_PWR_LVL0] == ARM_LOCAL_STATE_OFF");
  StatusReg = _ReadStatusReg(MPIDR_EL1);
  if ( a1[1] == 2 )
  {
    v2 = gicv2_cpuif_disable_cpu(StatusReg);
    v3 = sprd_pwr_domain_suspend_finish(v2);
    clear_boot_flag(v3);
  }
  return gicv2_lock_release(StatusReg);
}

/* ===== gicv2_cpuif_enable @ 0x940003F4 size 24 ===== */
_DWORD *__fastcall gicv2_cpuif_enable(_BYTE *a1)
{
  __int64 v1; // x0
  __int64 v2; // x2
  char *v3; // x3
  _DWORD *result; // x0

  v1 = sprd_power_domain_on_finish(a1);
  gicv2_pcpu_distif_init_thunk(v1);
  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v2 = 50;
    v3 = "driver_data";
    goto LABEL_5;
  }
  result = *(_DWORD **)(MEMORY[0x9400D0D0] + 8LL);
  if ( result == nullptr )
  {
    v2 = 51;
    v3 = "driver_data->gicc_base";
LABEL_5:
    assert_fail("gicv2_cpuif_enable", "drivers/arm/gic/v2/gicv2_main.c", v2, v3);
  }
  result[1] = 255;
  *result = 489;
  return result;
}

/* ===== sprd_pwr_domain_on_finish_common @ 0x9400040C size 40 ===== */
_BYTE *__fastcall sprd_pwr_domain_on_finish_common(_BYTE *result)
{
  if ( *result != 1 )
  {
    sprd_power_domain_on_finish(result);
    JUMPOUT(0x94001054LL);
  }
  return result;
}

/* ===== sprd_pwr_domain_off @ 0x94000434 size 128 ===== */
__int64 __fastcall sprd_pwr_domain_off(_BYTE *a1)
{
  __int64 v2; // x0
  __int64 result; // x0
  unsigned __int64 StatusReg; // x19

  if ( *a1 != 2 )
    assert_fail(
      "sprd_pwr_domain_off",
      "plat/sprd/sharkle/pm.c",
      178,
      "target_state->pwr_domain_state[ARM_PWR_LVL0] == ARM_LOCAL_STATE_OFF");
  v2 = gicv2_enable_ppi(_ReadStatusReg(MPIDR_EL1));
  gicv2_cpuif_disable_thunk(v2);
  gicv2_cpuif_enable_cpu(_ReadStatusReg(MPIDR_EL1));
  result = (unsigned __int8)a1[1];
  if ( (_DWORD)result == 2 )
  {
    StatusReg = _ReadStatusReg(MPIDR_EL1);
    read_boot_flag();
    return sprd_gic_cpuif_init(StatusReg);
  }
  return result;
}

/* ===== get_power_domain_tree @ 0x940004B4 size 28 ===== */
unsigned __int64 get_power_domain_tree()
{
  MEMORY[0x9400E680] = 1;
  MEMORY[0x9400E681] = 4;
  return 0x9400E680;
}

/* ===== psci_validate_affinity @ 0x940004D0 size 64 ===== */
__int64 __fastcall psci_validate_affinity(__int64 a1)
{
  if ( (a1 & 0xFF00FF0000LL) == 0 && BYTE1(a1) == 0 && (unsigned __int8)a1 <= 3u )
    JUMPOUT(0x94007E30LL);
  return 0xFFFFFFFFLL;
}

/* ===== get_affinity_state @ 0x94000510 size 92 ===== */
__int64 __fastcall get_affinity_state(char a1)
{
  unsigned int v2; // w20

  bakery_lock_get(0x94014000);
  v2 = MEMORY[0x402B00BC];
  bakery_lock_release(0x94014000);
  return (v2 >> (5 * (a1 + 1))) & 0x1F;
}

/* ===== sprd_pwr_domain_suspend_finish @ 0x9400056C size 108 ===== */
__int64 sprd_pwr_domain_suspend_finish()
{
  __int64 result; // x0

  result = 0x9400D0C0;
  if ( MEMORY[0x9400D0C0] != 0 )
  {
    MEMORY[0x9400D0C0] = 0;
    MEMORY[0x402E0528] = (unsigned __int64)bl31_warm_reset_vector >> 2;
    MEMORY[0x402B2208] = 1;
    MEMORY[0x402B2214] = 1;
    MEMORY[0x402E1000] = 0x80000000;
    MEMORY[0x402E10B0] = 0x8000;
    return 1076760752;
  }
  return result;
}

/* ===== gicv2_raise_priority @ 0x940005D8 size 144 ===== */
_DWORD *__fastcall gicv2_raise_priority(_DWORD *result)
{
  __int64 v1; // x0
  int v2; // w1

  switch ( (int)result )
  {
    case 0:
      v1 = 444;
      v2 = MEMORY[0x402B01BC] | 1;
      goto LABEL_6;
    case 1:
      v1 = 448;
      v2 = MEMORY[0x402B01C0] | 1;
      goto LABEL_6;
    case 2:
      v1 = 452;
      v2 = MEMORY[0x402B01C4] | 1;
      goto LABEL_6;
    case 3:
      v1 = 456;
      v2 = MEMORY[0x402B01C8] | 1;
LABEL_6:
      result = (_DWORD *)(v1 & 0xFFFFFFFF0000FFFFLL | 0x402B0000);
      *result = v2;
      break;
    default:
      return result;
  }
  return result;
}

/* ===== gicv2_set_priority @ 0x94000668 size 144 ===== */
_DWORD *__fastcall gicv2_set_priority(_DWORD *result)
{
  __int64 v1; // x0
  int v2; // w1

  switch ( (int)result )
  {
    case 0:
      v1 = 840;
      v2 = MEMORY[0x402B0348] | 1;
      goto LABEL_6;
    case 1:
      v1 = 844;
      v2 = MEMORY[0x402B034C] | 1;
      goto LABEL_6;
    case 2:
      v1 = 848;
      v2 = MEMORY[0x402B0350] | 1;
      goto LABEL_6;
    case 3:
      v1 = 852;
      v2 = MEMORY[0x402B0354] | 1;
LABEL_6:
      result = (_DWORD *)(v1 & 0xFFFFFFFF0000FFFFLL | 0x402B0000);
      *result = v2;
      break;
    default:
      return result;
  }
  return result;
}

/* ===== gicv2_clear_priority @ 0x940006F8 size 144 ===== */
_DWORD *__fastcall gicv2_clear_priority(_DWORD *result)
{
  __int64 v1; // x0
  unsigned int v2; // w1

  switch ( (int)result )
  {
    case 0:
      v1 = 840;
      v2 = MEMORY[0x402B0348] & 0xFFFFFFFE;
      goto LABEL_6;
    case 1:
      v1 = 844;
      v2 = MEMORY[0x402B034C] & 0xFFFFFFFE;
      goto LABEL_6;
    case 2:
      v1 = 848;
      v2 = MEMORY[0x402B0350] & 0xFFFFFFFE;
      goto LABEL_6;
    case 3:
      v1 = 852;
      v2 = MEMORY[0x402B0354] & 0xFFFFFFFE;
LABEL_6:
      result = (_DWORD *)(v1 & 0xFFFFFFFF0000FFFFLL | 0x402B0000);
      *result = v2;
      break;
    default:
      return result;
  }
  return result;
}

/* ===== gicv2_cpuif_disable_cpu @ 0x94000788 size 432 ===== */
__int64 __fastcall gicv2_cpuif_disable_cpu(unsigned __int16 a1)
{
  unsigned __int64 v1; // x19
  unsigned int v2; // w0

  v1 = a1;
  bakery_lock_get(2483109888LL);
  MEMORY[0x402B0254] |= 1u;
  switch ( (int)v1 )
  {
    case 0:
      MEMORY[0x402B0004] &= ~0x1000000u;
      MEMORY[0x402B0004] &= ~0x2000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFEFF;
      goto LABEL_6;
    case 1:
      MEMORY[0x402B0008] &= ~0x1000000u;
      MEMORY[0x402B0008] &= ~0x2000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFDFF;
      goto LABEL_6;
    case 2:
      MEMORY[0x402B000C] &= ~0x1000000u;
      MEMORY[0x402B000C] &= ~0x2000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFBFF;
      goto LABEL_6;
    case 3:
      MEMORY[0x402B0010] &= ~0x1000000u;
      MEMORY[0x402B0010] &= ~0x2000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFF7FF;
LABEL_6:
      MEMORY[0x402B0174] = v2;
      break;
    default:
      break;
  }
  gicv2_clear_priority((_DWORD *)v1);
  return bakery_lock_release(2483109888LL);
}

/* ===== gicv2_cpuif_enable_cpu @ 0x94000938 size 560 ===== */
__int64 __fastcall gicv2_cpuif_enable_cpu(unsigned __int16 a1)
{
  unsigned __int64 v1; // x19
  unsigned int v2; // w0

  v1 = a1;
  bakery_lock_get(2483109888LL);
  MEMORY[0x7140000C] = -1;
  MEMORY[0x7150000C] = -1;
  MEMORY[0x7160000C] = -1;
  MEMORY[0x7170000C] = -1;
  MEMORY[0x71400008] = MEMORY[0x12001104];
  MEMORY[0x71500008] = MEMORY[0x12001108];
  MEMORY[0x71600008] = MEMORY[0x1200110C];
  MEMORY[0x71700008] = MEMORY[0x12001110];
  switch ( (int)v1 )
  {
    case 0:
      MEMORY[0x402B0004] |= 0x1000000u;
      MEMORY[0x402B0004] &= ~0x8000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFEFF;
      goto LABEL_6;
    case 1:
      MEMORY[0x402B0008] |= 0x1000000u;
      MEMORY[0x402B0008] &= ~0x8000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFDFF;
      goto LABEL_6;
    case 2:
      MEMORY[0x402B000C] |= 0x1000000u;
      MEMORY[0x402B000C] &= ~0x8000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFFBFF;
      goto LABEL_6;
    case 3:
      MEMORY[0x402B0010] |= 0x1000000u;
      MEMORY[0x402B0010] &= ~0x8000000u;
      v2 = MEMORY[0x402B0174] & 0xFFFFF7FF;
LABEL_6:
      MEMORY[0x402B0174] = v2;
      break;
    default:
      break;
  }
  gicv2_set_priority((_DWORD *)v1);
  gicv2_raise_priority((_DWORD *)v1);
  return bakery_lock_release(2483109888LL);
}

/* ===== gicv2_enable_ppi @ 0x94000B68 size 188 ===== */
__int64 __fastcall gicv2_enable_ppi(__int16 a1)
{
  __int64 v2; // x1
  int v3; // w0

  bakery_lock_get(2483109888LL);
  switch ( a1 )
  {
    case 0:
      v2 = 444;
      v3 = MEMORY[0x402B01BC] | 1;
      goto LABEL_6;
    case 1:
      v2 = 448;
      v3 = MEMORY[0x402B01C0] | 1;
      goto LABEL_6;
    case 2:
      v2 = 452;
      v3 = MEMORY[0x402B01C4] | 1;
      goto LABEL_6;
    case 3:
      v2 = 456;
      v3 = MEMORY[0x402B01C8] | 1;
LABEL_6:
      *(_DWORD *)(v2 & 0xFFFFFFFF0000FFFFLL | 0x402B0000) = v3;
      break;
    default:
      return bakery_lock_release(2483109888LL);
  }
  return bakery_lock_release(2483109888LL);
}

/* ===== gicv2_lock_release @ 0x94000C24 size 44 ===== */
__int64 gicv2_lock_release()
{
  bakery_lock_get(0x94014000);
  return bakery_lock_release(0x94014000);
}

/* ===== sprd_gic_cpuif_init @ 0x94000C50 size 324 ===== */
__int64 __fastcall sprd_gic_cpuif_init(__int16 a1)
{
  unsigned __int8 v1; // x20^1

  v1 = HIBYTE(a1);
  bakery_lock_get(2483109888LL);
  if ( v1 == 0 )
  {
    MEMORY[0x402B0000] |= 0x1000000u;
    MEMORY[0x402B0000] &= ~0x8000000u;
    MEMORY[0x402B0214] |= 1u;
    if ( MEMORY[0x9400D0C0] != 0 )
    {
      MEMORY[0x402E1000] = 0x80000000;
      MEMORY[0x402E20B0] = 0x8000;
      MEMORY[0x402B1174] = 256;
      MEMORY[0x402B1348] = 1;
      MEMORY[0x402B1214] = 1;
      MEMORY[0x402B1208] = 1;
      MEMORY[0x402B1018] = 0x1000000;
      MEMORY[0x4020100C] = 0x80000000;
      MEMORY[0x40200008] |= 0x4068214u;
      MEMORY[0x40500008] |= 0xF1001800;
      MEMORY[0x402E0528] = v1;
    }
  }
  return bakery_lock_release(2483109888LL);
}

/* ===== sprd_platform_init @ 0x94000D94 size 148 ===== */
__int64 sprd_platform_init()
{
  unsigned int v0; // w1

  MEMORY[0x402E0590] |= 1u;
  MEMORY[0x402B0230] |= 8u;
  if ( (MEMORY[0x402E00FC] & 0xF) == 2 )
    v0 = MEMORY[0x402E0140] | 0x10000;
  else
    v0 = MEMORY[0x402E0140] & 0xFFFEFFFF;
  MEMORY[0x402E0140] = v0;
  MEMORY[0x402D0274] = 0;
  MEMORY[0x402D0290] = 1;
  return 1076691600;
}

/* ===== sprd_spinlock_init @ 0x94000E28 size 76 ===== */
__int64 sprd_spinlock_init()
{
  MEMORY[0] = -721215457;
  MEMORY[4] = -721215457;
  MEMORY[8] = -721215457;
  MEMORY[0xC] = -721215457;
  return memcpy_simple(16, &dword_94000178, (char *)bl31_early_setup - (char *)&dword_94000178);
}

/* ===== gicd_get_isenabler @ 0x94000F88 size 20 ===== */
__int64 __fastcall gicd_get_isenabler(__int64 a1, unsigned int a2)
{
  return *(unsigned int *)(a1 + 128 + 4LL * (a2 >> 5));
}

/* ===== gicd_set_isenabler @ 0x94000F9C size 20 ===== */
__int64 __fastcall gicd_set_isenabler(__int64 a1, unsigned int a2, int a3)
{
  __int64 result; // x0

  result = a1 + 128;
  *(_DWORD *)(result + 4LL * (a2 >> 5)) = a3;
  return result;
}

/* ===== gicd_set_icenabler @ 0x94000FC4 size 20 ===== */
__int64 __fastcall gicd_set_icenabler(__int64 a1, unsigned int a2, int a3)
{
  __int64 result; // x0

  result = a1 + 384;
  *(_DWORD *)(result + 4LL * (a2 >> 5)) = a3;
  return result;
}

/* ===== gicd_set_icfgr @ 0x94000FD8 size 16 ===== */
__int64 __fastcall gicd_set_icfgr(__int64 a1, int a2, int a3)
{
  __int64 result; // x0

  result = a1 + 1024;
  *(_DWORD *)(result + (a2 & 0xFFFFFFFC)) = a3;
  return result;
}

/* ===== gicd_set_ipriorityr @ 0x94000FE8 size 20 ===== */
__int64 __fastcall gicd_set_ipriorityr(__int64 a1, unsigned int a2, int a3)
{
  __int64 result; // x0

  result = a1 + 3072;
  *(_DWORD *)(result + 4LL * (a2 >> 4)) = a3;
  return result;
}

/* ===== gicd_clear_enable @ 0x94000FFC size 56 ===== */
__int64 __fastcall gicd_clear_enable(__int64 a1, unsigned int a2)
{
  int v4; // w0

  v4 = gicd_get_isenabler(a1, a2);
  return gicd_set_isenabler(a1, a2, v4 & (unsigned int)~(1 << a2));
}

/* ===== gicd_set_pending @ 0x94001034 size 12 ===== */
__int64 __fastcall gicd_set_pending(__int64 a1, unsigned int a2)
{
  __int64 result; // x0

  result = a1 + 256;
  *(_DWORD *)(result + 4LL * (a2 >> 5)) = 1 << a2;
  return result;
}

/* ===== gicd_set_itargetsr @ 0x94001040 size 20 ===== */
__int64 __fastcall gicd_set_itargetsr(__int64 a1, unsigned int a2, char a3)
{
  __int64 result; // x0

  result = a1 + 1024;
  *(_BYTE *)(result + a2) = a3;
  return result;
}

/* ===== gicv2_cpuif_disable @ 0x940010CC size 120 ===== */
unsigned int *gicv2_cpuif_disable()
{
  __int64 v0; // x2
  char *v1; // x3
  unsigned int *result; // x0

  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 73;
    v1 = "driver_data";
    goto LABEL_5;
  }
  result = *(unsigned int **)(MEMORY[0x9400D0D0] + 8LL);
  if ( result == nullptr )
  {
    v0 = 74;
    v1 = "driver_data->gicc_base";
LABEL_5:
    assert_fail("gicv2_cpuif_disable", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  *result = *result & 0xFFFFFE1C | 0x1E0;
  return result;
}

/* ===== gicv2_pcpu_distif_init @ 0x94001144 size 148 ===== */
__int64 gicv2_pcpu_distif_init()
{
  __int64 v0; // x2
  char *v1; // x3

  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 90;
    v1 = "driver_data";
    goto LABEL_5;
  }
  if ( *MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 91;
    v1 = "driver_data->gicd_base";
    goto LABEL_5;
  }
  if ( *(_QWORD *)(MEMORY[0x9400D0D0] + 24LL) == 0 )
  {
    v0 = 92;
    v1 = "driver_data->g0_interrupt_array";
LABEL_5:
    assert_fail("gicv2_pcpu_distif_init", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  return gicv2_secure_ppi_sgi_setup();
}

/* ===== gicv2_distif_init @ 0x940011D8 size 204 ===== */
__int64 gicv2_distif_init()
{
  __int64 v0; // x2
  char *v1; // x3
  int *v2; // x0
  int v3; // w20
  __int64 result; // x0

  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 108;
    v1 = "driver_data";
    goto LABEL_5;
  }
  v2 = (int *)*MEMORY[0x9400D0D0];
  if ( *MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 109;
    v1 = "driver_data->gicd_base";
    goto LABEL_5;
  }
  if ( *(_QWORD *)(MEMORY[0x9400D0D0] + 24LL) == 0 )
  {
    v0 = 110;
    v1 = "driver_data->g0_interrupt_array";
LABEL_5:
    assert_fail("gicv2_distif_init", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  v3 = *v2;
  *v2 &= 0xFFFFFFFC;
  gicv2_distif_clear_config();
  gicv2_secure_spis_configure(
    *MEMORY[0x9400D0D0],
    *(unsigned int *)(MEMORY[0x9400D0D0] + 16LL),
    *(_QWORD *)(MEMORY[0x9400D0D0] + 24LL));
  result = *MEMORY[0x9400D0D0];
  *(_DWORD *)*MEMORY[0x9400D0D0] = v3 | 1;
  return result;
}

/* ===== gicv2_driver_init @ 0x940012A4 size 272 ===== */
__int64 __fastcall gicv2_driver_init(__int64 result)
{
  __int64 v1; // x2
  const char *v2; // x3

  if ( result == 0 )
  {
    v1 = 135;
    v2 = "plat_driver_data";
    goto LABEL_5;
  }
  if ( *(_QWORD *)result == 0 )
  {
    v1 = 136;
    v2 = "plat_driver_data->gicd_base";
    goto LABEL_5;
  }
  if ( *(_QWORD *)(result + 8) == 0 )
  {
    v1 = 137;
    v2 = "plat_driver_data->gicc_base";
    goto LABEL_5;
  }
  if ( *(_QWORD *)(result + 24) == 0 )
  {
    v1 = 143;
    v2 = "plat_driver_data->g0_interrupt_array";
    goto LABEL_5;
  }
  if ( *(_DWORD *)(result + 16) == 0 )
  {
    v1 = 151;
    v2 = "plat_driver_data->g0_interrupt_array ? plat_driver_data->g0_interrupt_num : plat_driver_data->g0_interrupt_num == 0";
    goto LABEL_5;
  }
  if ( (unsigned __int8)*(_DWORD *)(*(_QWORD *)result + 4072LL) >> 4 != 2 )
  {
    v1 = 157;
    v2 = "gic_version == ARCH_REV_GICV2";
LABEL_5:
    assert_fail("gicv2_driver_init", "drivers/arm/gic/v2/gicv2_main.c", v1, v2);
  }
  MEMORY[0x9400D0D0] = result;
  return result;
}

/* ===== gicv2_is_fiq_enabled @ 0x940013B4 size 112 ===== */
bool gicv2_is_fiq_enabled()
{
  __int64 v0; // x2
  char *v1; // x3
  _DWORD *v2; // x0

  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 171;
    v1 = "driver_data";
    goto LABEL_5;
  }
  v2 = *(_DWORD **)(MEMORY[0x9400D0D0] + 8LL);
  if ( v2 == nullptr )
  {
    v0 = 172;
    v1 = "driver_data->gicc_base";
LABEL_5:
    assert_fail("gicv2_is_fiq_enabled", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  return (*v2 & 8LL) != 0;
}

/* ===== gicv2_get_pending_interrupt_type @ 0x94001424 size 112 ===== */
__int64 gicv2_get_pending_interrupt_type()
{
  __int64 v0; // x2
  char *v1; // x3
  __int64 v2; // x0

  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 188;
    v1 = "driver_data";
    goto LABEL_5;
  }
  v2 = *(_QWORD *)(MEMORY[0x9400D0D0] + 8LL);
  if ( v2 == 0 )
  {
    v0 = 189;
    v1 = "driver_data->gicc_base";
LABEL_5:
    assert_fail("gicv2_get_pending_interrupt_type", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  return *(_DWORD *)(v2 + 24) & 0x3FF;
}

/* ===== gicv2_get_interrupt_priority @ 0x94001494 size 12 ===== */
__int64 __fastcall gicv2_get_interrupt_priority(__int64 a1)
{
  return (unsigned __int8)*(_DWORD *)(a1 + 2048);
}

/* ===== gicv2_distif_clear_config @ 0x940014A0 size 160 ===== */
__int64 __fastcall gicv2_distif_clear_config(__int64 result)
{
  __int64 v1; // x19
  unsigned int v2; // w21
  unsigned int i; // w20
  unsigned int v4; // w1
  unsigned int j; // w20
  int v6; // w1
  unsigned int k; // w20
  unsigned int v8; // w1

  v1 = result;
  v2 = 32 * ((*(_DWORD *)(result + 4) & 0x1F) + 1);
  for ( i = 32; i < v2; i += 32 )
  {
    v4 = i;
    result = gicd_set_isenabler(v1, v4, -1);
  }
  for ( j = 32; j < v2; j += 4 )
  {
    v6 = j;
    result = gicd_set_icfgr(v1, v6, -2139062144);
  }
  for ( k = 32; k < v2; k += 16 )
  {
    v8 = k;
    result = gicd_set_ipriorityr(v1, v8, 0);
  }
  return result;
}

/* ===== gicv2_secure_spis_configure @ 0x94001540 size 188 ===== */
__int64 __fastcall gicv2_secure_spis_configure(__int64 result, unsigned int a2, __int64 a3)
{
  __int64 v3; // x19
  __int64 i; // x21
  unsigned int v7; // w20

  v3 = result;
  if ( a3 == 0 && a2 != 0 )
    assert_fail(
      "gicv2_secure_spis_configure",
      "drivers/arm/gic/v2/gicv2_helpers.c",
      158,
      "num_ints ? (uintptr_t)sec_intr_list : 1");
  for ( i = 0; a2 > (unsigned int)i; ++i )
  {
    v7 = *(_DWORD *)(a3 + 4 * i);
    if ( v7 > 0x1F )
    {
      gicd_clear_enable(v3, v7);
      gicd_set_itargetsr(v3, v7, 0);
      *(_BYTE *)(v3 + 2048 + v7) = gicv2_get_interrupt_priority(v3);
      result = gicd_set_pending(v3, v7);
    }
  }
  return result;
}

/* ===== gicv2_secure_ppi_sgi_setup @ 0x940015FC size 228 ===== */
__int64 __fastcall gicv2_secure_ppi_sgi_setup(__int64 a1, unsigned int a2, __int64 a3)
{
  int v7; // w20
  int v8; // w1
  __int64 v9; // x20
  int v10; // w21
  unsigned int v11; // w1

  if ( a3 == 0 && a2 != 0 )
    assert_fail(
      "gicv2_secure_ppi_sgi_setup",
      "drivers/arm/gic/v2/gicv2_helpers.c",
      192,
      "num_ints ? (uintptr_t)sec_intr_list : 1");
  v7 = 0;
  gicd_set_icenabler(a1, 0, -1);
  do
  {
    v8 = v7;
    v7 += 4;
    gicd_set_icfgr(a1, v8, -2139062144);
  }
  while ( v7 != 32 );
  v9 = 0;
  v10 = 0;
  while ( a2 > (unsigned int)v9 )
  {
    v11 = *(_DWORD *)(a3 + 4 * v9);
    if ( v11 <= 0x1F )
    {
      v10 |= 1 << v11;
      gicd_set_itargetsr(a1, v11, 0);
    }
    ++v9;
  }
  gicd_set_isenabler(a1, 0, ~v10);
  *(_DWORD *)(a1 + 256) = v10;
  return a1 + 256;
}

/* ===== gicv2_get_interrupt_type @ 0x940016E0 size 52 ===== */
__int64 gicv2_get_interrupt_type()
{
  unsigned int v0; // w1
  __int64 result; // x0

  v0 = gicv2_get_pending_interrupt_type();
  result = 0;
  if ( v0 > 0x3FD )
  {
    if ( v0 == 1023 )
      return 3;
    else
      return 2;
  }
  return result;
}

/* ===== plat_interrupt_type_to_line @ 0x94001714 size 80 ===== */
__int64 __fastcall plat_interrupt_type_to_line(unsigned int a1)
{
  bool v1; // zf
  __int64 result; // x0

  v1 = a1 == 2;
  if ( a1 > 2 )
    assert_fail(
      "plat_interrupt_type_to_line",
      "plat/common/plat_gicv2.c",
      136,
      "type == INTR_TYPE_S_EL1 || type == INTR_TYPE_EL3 || type == INTR_TYPE_NS");
  result = 1;
  if ( !v1 )
  {
    if ( gicv2_is_fiq_enabled() )
      return 2;
    else
      return 1;
  }
  return result;
}

/* ===== sprd_gic_driver_init @ 0x94001764 size 12 ===== */
__int64 sprd_gic_driver_init()
{
  return gicv2_driver_init((__int64)qword_94009490);
}

/* ===== gicv2_cpuif_enable_all @ 0x94001770 size 24 ===== */
_DWORD *gicv2_cpuif_enable_all()
{
  __int64 v0; // x2
  char *v1; // x3
  _DWORD *result; // x0

  gicv2_distif_init();
  gicv2_pcpu_distif_init();
  if ( MEMORY[0x9400D0D0] == 0 )
  {
    v0 = 50;
    v1 = "driver_data";
    goto LABEL_5;
  }
  result = *(_DWORD **)(MEMORY[0x9400D0D0] + 8LL);
  if ( result == nullptr )
  {
    v0 = 51;
    v1 = "driver_data->gicc_base";
LABEL_5:
    assert_fail("gicv2_cpuif_enable", "drivers/arm/gic/v2/gicv2_main.c", v0, v1);
  }
  result[1] = 255;
  *result = 489;
  return result;
}

/* ===== gicv2_cpuif_disable_thunk @ 0x9400178C size 4 ===== */
// attributes: thunk
unsigned int *__fastcall gicv2_cpuif_disable_thunk()
{
  return gicv2_cpuif_disable();
}

/* ===== gicv2_pcpu_distif_init_thunk @ 0x94001790 size 4 ===== */
// attributes: thunk
__int64 __fastcall gicv2_pcpu_distif_init_thunk()
{
  return gicv2_pcpu_distif_init();
}

/* ===== nullsub_1 @ 0x940017A0 size 4 ===== */
void nullsub_1()
{
  ;
}

/* ===== bl31_get_next_image_ep @ 0x940017A4 size 92 ===== */
unsigned __int64 __fastcall bl31_get_next_image_ep(unsigned int a1)
{
  unsigned __int64 result; // x0

  if ( a1 > 1 )
    assert_fail(
      "bl31_plat_get_next_image_ep_info",
      "plat/sprd/common/sprd_bl31_setup.c",
      83,
      "sec_state_is_valid(type)");
  if ( a1 == 1 )
    result = 0x9400D130;
  else
    result = 0x9400D0D8;
  if ( *(_QWORD *)(result + 8) == 0 )
    return 0;
  return result;
}

/* ===== sprd_bl31_early_platform_setup @ 0x94001800 size 236 ===== */
__int64 __fastcall sprd_bl31_early_platform_setup(__int64 a1, __int64 a2)
{
  __int64 v4; // x2
  char *v5; // x3
  __int64 result; // x0

  uart_init(1880096768, 26000000, 115200);
  if ( a1 != 0 )
  {
    v4 = 118;
    v5 = "from_bl2 == NULL";
    goto LABEL_5;
  }
  if ( a2 != 0 )
  {
    v4 = 119;
    v5 = "plat_params_from_bl2 == NULL";
LABEL_5:
    assert_fail("sprd_bl31_early_platform_setup", "plat/sprd/common/sprd_bl31_setup.c", v4, v5);
  }
  MEMORY[0x9400D0D8] = 1;
  MEMORY[0x9400D0D9] = 1;
  MEMORY[0x9400D0DC] = 0;
  MEMORY[0x9400D0DA] = 88;
  MEMORY[0x9400D0E0] = 2483159040LL;
  MEMORY[0x9400D0E8] = get_secure_ep();
  MEMORY[0x9400D130] = 1;
  MEMORY[0x9400D132] = 88;
  MEMORY[0x9400D134] = 0;
  MEMORY[0x9400D131] = 1;
  MEMORY[0x9400D138] = get_non_secure_ep();
  MEMORY[0x9400D140] = get_scr_el3_config();
  result = MEMORY[0x9400D134] | 1u;
  MEMORY[0x9400D134] |= 1u;
  return result;
}

/* ===== sprd_bl31_platform_setup @ 0x940018EC size 44 ===== */
__int64 sprd_bl31_platform_setup()
{
  sprd_gic_driver_init();
  gicv2_cpuif_enable_all();
  nullsub_1();
  MEMORY[0x32000000] = 1;
  nullsub_5();
  MEMORY[0x9400D0C8] = &dword_94000178;
  MEMORY[0x402E0528] = (unsigned __int64)bl31_warm_reset_vector >> 2;
  MEMORY[0x402E052C] = (unsigned __int64)bl31_warm_reset_vector >> 2;
  MEMORY[0x402E0530] = (unsigned __int64)bl31_warm_reset_vector >> 2;
  MEMORY[0x402E0534] = (unsigned __int64)bl31_warm_reset_vector >> 2;
  MEMORY[0x71300000] |= 0x80000u;
  MEMORY[0x71300000] |= 0x100000u;
  MEMORY[0x71300000] |= 0x200000u;
  MEMORY[0x71300000] |= 0x400000u;
  MEMORY[0x402E00B0] &= ~0x8000u;
  MEMORY[0x402B0230] |= 1u;
  MEMORY[0x402B00C8] |= 0xFu;
  sprd_platform_init();
  sprd_spinlock_init();
  MEMORY[0x402B1018] = 0x1000000;
  MEMORY[0x402B2018] = 0x2000000;
  return 1076568088;
}

/* ===== sprd_bl31_setup_thunk @ 0x94001930 size 4 ===== */
// attributes: thunk
__int64 sprd_bl31_setup_thunk()
{
  return sprd_bl31_platform_setup();
}

/* ===== sprd_bl31_main_setup @ 0x94001938 size 96 ===== */
__int64 sprd_bl31_main_setup()
{
  plat_setup_mmap(
    2483027968LL,
    0x15000u,
    bl31_entrypoint,
    "sprd_cpu_standby",
    "sprd_cpu_standby",
    off_9400C000,
    0x94014000,
    0x94015000);
  return enable_mmu_el3(0);
}

/* ===== sprd_bl31_setup_call @ 0x94001998 size 4 ===== */
// attributes: thunk
__int64 __fastcall sprd_bl31_setup_call()
{
  return sprd_bl31_main_setup();
}

/* ===== sprd_validate_power_state_req @ 0x9400199C size 132 ===== */
__int64 __fastcall sprd_validate_power_state_req(unsigned __int64 a1, _BYTE *a2)
{
  __int64 v2; // x2

  v2 = (a1 >> 24) & 3;
  if ( a2 == nullptr )
    assert_fail(&loc_94009558, "plat/sprd/common/sprd_pm.c", 63, "req_state");
  if ( ((a1 >> 24) & 3) <= 1 )
  {
    if ( (a1 & 0x10000) != 0 )
    {
      *a2 = 2;
      if ( (_DWORD)v2 == 1 )
        a2[1] = 2;
      goto LABEL_9;
    }
    if ( (_DWORD)v2 == 0 )
    {
      *a2 = 1;
LABEL_9:
      if ( (_WORD)a1 != 0 )
        return 4294967294LL;
      else
        return 0;
    }
  }
  return 4294967294LL;
}

/* ===== sprd_check_image_range @ 0x94001A20 size 64 ===== */
__int64 __fastcall sprd_check_image_range(__int64 a1)
{
  bool v1; // cc
  __int64 result; // x0

  v1 = (unsigned __int64)(a1 - 0x80000000LL) > 0x7EFFFFFF;
  result = 0;
  if ( v1 )
  {
    if ( (unsigned __int64)(a1 - 0x880000000LL) <= 0x77FFFFFFFLL )
      return 0;
    else
      return 4294967287LL;
  }
  return result;
}

/* ===== sprd_plat_pm_ops_init @ 0x94001A60 size 32 ===== */
__int64 __fastcall sprd_plat_pm_ops_init(__int64 a1, _QWORD *a2)
{
  *a2 = off_9400C000;
  MEMORY[0x9401F000] = a1;
  return 0;
}

/* ===== plat_get_target_pwr_state @ 0x94001A80 size 88 ===== */
__int64 __fastcall plat_get_target_pwr_state(__int64 a1, __int64 a2, int a3)
{
  __int64 v3; // x3
  __int64 result; // x0
  unsigned int v5; // w4

  v3 = 0;
  LODWORD(result) = 2;
  if ( a3 == 0 )
    assert_fail("plat_get_target_pwr_state", "plat/common/plat_psci_common.c", 54, "ncpu");
  do
  {
    v5 = *(unsigned __int8 *)(a2 + v3++);
    if ( v5 < (unsigned int)result )
      LOBYTE(result) = v5;
    result = (unsigned __int8)result;
  }
  while ( a3 != (_DWORD)v3 );
  return result;
}

/* ===== get_arm_std_svc_args @ 0x94001AD8 size 68 ===== */
__int64 *__fastcall get_arm_std_svc_args(int a1)
{
  if ( a1 != 65504 )
    assert_fail("get_arm_std_svc_args", "bl31/bl31_main.c", 73, "svc_mask == PSCI_FID_MASK");
  return &qword_94009718;
}

/* ===== bl31_main_loop @ 0x94001B1C size 180 ===== */
__int64 bl31_main_loop()
{
  __int64 v0; // x0
  unsigned __int64 v1; // x0
  unsigned __int64 v2; // x20
  __int64 v3; // x2
  const char *v4; // x3

  if ( (unsigned __int8)_ReadStatusReg(ID_AA64PFR0_EL1) >> 4 == 1 )
  {
    v0 = printf_impl("ERROR:   EL1 supports AArch64-only. Please set build flag CTX_INCLUDE_AARCH32_REGS = 0");
    panic(v0);
  }
  v1 = bl31_get_next_image_ep(1u);
  v2 = v1;
  if ( v1 == 0 )
  {
    v3 = 185;
    v4 = "next_image_info";
    goto LABEL_7;
  }
  if ( (*(_DWORD *)(v1 + 4) & 1) != 1 )
  {
    v3 = 186;
    v4 = "image_type == GET_SECURITY_STATE(next_image_info->h.attr)";
LABEL_7:
    assert_fail(&loc_94009608, "bl31/bl31_main.c", v3, v4);
  }
  nullsub_3();
  cm_init_context(v2);
  return cm_prepare_el3_exit(1);
}

/* ===== bl31_main_init @ 0x94001BD0 size 52 ===== */
__int64 bl31_main_init()
{
  __int64 v1; // x0
  __int64 v2; // x0

  v1 = sprd_bl31_setup_thunk();
  v2 = nullsub_2(v1);
  runtime_svc_init(v2);
  if ( MEMORY[0x9400D188] != nullptr )
    MEMORY[0x9400D188]();
  bl31_main_loop();
  return uart_init(1880096768, 26000000, 115200);
}

/* ===== bl31_register_runtime_callback @ 0x94001C04 size 16 ===== */
__int64 (*__fastcall bl31_register_runtime_callback(__int64 (*result)(void)))(void)
{
  MEMORY[0x9400D188] = result;
  return result;
}

/* ===== interrupt_routing_set @ 0x94001C14 size 136 ===== */
__int64 __fastcall interrupt_routing_set(unsigned int a1, unsigned int a2, unsigned int a3)
{
  unsigned int v3; // w20
  __int64 v5; // x21
  unsigned int v6; // w0
  __int64 result; // x0
  __int64 v8; // [xsp+38h] [xbp+38h]

  v3 = (a2 >> a3) & 1;
  v5 = a1;
  v6 = plat_interrupt_type_to_line(a1);
  *(_DWORD *)(0x9400D190 + 4 * (6 * v5 + a3) + 12) = v3 << v6;
  v8 = v6;
  result = cm_get_context(a3);
  if ( result != 0 )
    return cm_write_scr_el3_bit(a3, v8, v3);
  return result;
}

/* ===== get_scr_el3_from_routing_model @ 0x94001C9C size 96 ===== */
__int64 __fastcall get_scr_el3_from_routing_model(unsigned int a1)
{
  if ( a1 > 1 )
    assert_fail("get_scr_el3_from_routing_model", "bl31/interrupt_mgmt.c", 110, "sec_state_is_valid(security_state)");
  return (unsigned int)(*(_DWORD *)(0x9400D190 + 4LL * a1 + 60) | *(_DWORD *)(0x9400D190 + 4LL * a1 + 12))
       | *(_DWORD *)(0x9400D190 + 4LL * a1 + 36);
}

/* ===== interrupt_routing_model_init @ 0x94001CFC size 188 ===== */
__int64 __fastcall interrupt_routing_model_init(unsigned int a1, unsigned int a2)
{
  BOOL v2; // w2
  BOOL v5; // w0
  __int64 result; // x0
  unsigned int v7; // w1

  v2 = a1 == 0;
  v5 = a1 == 2;
  if ( !v2 && !v5 && a1 != 1 )
    return 4294967274LL;
  v7 = a2 & 3;
  if ( v2 )
  {
    v7 -= 2;
LABEL_10:
    result = 4294967274LL;
    if ( v7 > 1 )
      return result;
    goto LABEL_13;
  }
  if ( v5 )
    goto LABEL_10;
  if ( a1 != 1 || v7 - 2 > 1 )
    return 4294967274LL;
LABEL_13:
  *(_DWORD *)(0x9400D190 + 24LL * a1 + 8) = a2;
  interrupt_routing_set(a1, a2, 0);
  interrupt_routing_set(a1, a2, 1u);
  return 0;
}

/* ===== interrupt_register_handler @ 0x94001DB8 size 108 ===== */
__int64 __fastcall interrupt_register_handler(unsigned int a1, __int64 a2, unsigned int a3)
{
  __int64 v4; // x20
  __int64 result; // x0

  if ( a2 == 0 || (a3 & 0xFFFFFFFC) != 0 )
    return 4294967274LL;
  v4 = 24LL * a1;
  if ( *(_QWORD *)(0x9400D190LL + v4) != 0 )
    return 4294967259LL;
  result = interrupt_routing_model_init(a1, a3);
  if ( (_DWORD)result == 0 )
    *(_QWORD *)(0x9400D190LL + v4) = a2;
  return result;
}

/* ===== interrupt_get_handler @ 0x94001E24 size 44 ===== */
__int64 __fastcall interrupt_get_handler(unsigned int a1)
{
  if ( a1 <= 2 )
    return *(_QWORD *)(0x9400D190 + 24LL * a1);
  else
    return 0;
}

/* ===== cm_get_context @ 0x94001E50 size 64 ===== */
__int64 __fastcall cm_get_context(unsigned int a1)
{
  if ( a1 > 1 )
    assert_fail("cm_get_context", "bl31/bl31_context_mgmt.c", 47, "security_state <= NON_SECURE");
  return *(_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 8LL * a1);
}

/* ===== cm_set_context @ 0x94001E90 size 64 ===== */
__int64 __fastcall cm_set_context(__int64 result, unsigned int a2)
{
  if ( a2 > 1 )
    assert_fail("cm_set_context", "bl31/bl31_context_mgmt.c", 58, "security_state <= NON_SECURE");
  *(_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 8LL * a2) = result;
  return result;
}

/* ===== cm_get_context_by_index @ 0x94001ED0 size 72 ===== */
__int64 __fastcall cm_get_context_by_index(__int64 a1, unsigned int a2)
{
  if ( a2 > 1 )
    assert_fail("cm_get_context_by_index", "bl31/bl31_context_mgmt.c", 72, "sec_state_is_valid(security_state)");
  return *(_QWORD *)(get_cpu_context_ptr() + 8LL * a2);
}

/* ===== cm_set_context_by_index @ 0x94001F18 size 80 ===== */
__int64 __fastcall cm_set_context_by_index(__int64 a1, __int64 a2, unsigned int a3)
{
  __int64 result; // x0

  if ( a3 > 1 )
    assert_fail("cm_set_context_by_index", "bl31/bl31_context_mgmt.c", 84, "sec_state_is_valid(security_state)");
  result = get_cpu_context_ptr();
  *(_QWORD *)(result + 8LL * a3) = a2;
  return result;
}

/* ===== runtime_svc_init @ 0x94001F68 size 364 ===== */
void runtime_svc_init()
{
  unsigned __int64 v0; // x19
  unsigned __int64 v1; // x23
  __int64 v2; // x19
  __int64 v3; // x1
  unsigned int v4; // w0
  __int64 (*v5)(void); // x0
  int v6; // w0
  int v7; // w2
  int v8; // w1
  int v9; // w2
  __int64 v10; // x0
  __int64 v11; // [xsp+48h] [xbp+48h]

  if ( &qword_9400B468 > qword_9400B528
    || (v0 = (char *)qword_9400B528 - (char *)&qword_9400B468,
        (unsigned __int64)((char *)qword_9400B528 - (char *)&qword_9400B468) > 0xFFF) )
  {
    assert_fail(
      "runtime_svc_init",
      &loc_94009838,
      119,
      "(RT_SVC_DESCS_END >= RT_SVC_DESCS_START) && (RT_SVC_DECS_NUM < MAX_RT_SVCS)");
  }
  if ( v0 > 0x1F )
  {
    memset_simple(0x9400E688, 0xFFFFFFFFLL, 128);
    v1 = v0 >> 5;
    MEMORY[0x9400D1D8] = &qword_9400B468;
    v2 = 0;
    while ( 1 )
    {
      v3 = MEMORY[0x9400D1D8] + 32 * v2;
      if ( v3 == 0
        || (v4 = *(unsigned __int8 *)(v3 + 1), *(unsigned __int8 *)(MEMORY[0x9400D1D8] + 32 * v2) > v4)
        || v4 > 0x3F
        || *(unsigned __int8 *)(v3 + 2) > 1u )
      {
LABEL_20:
        v10 = printf_impl("ERROR:   Invalid runtime service descriptor %p\n", (const void *)v3);
        panic(v10);
      }
      v5 = *(__int64 (**)(void))(v3 + 16);
      if ( v5 == nullptr )
        break;
      v11 = MEMORY[0x9400D1D8] + 32 * v2;
      v6 = v5();
      v3 = v11;
      if ( v6 == 0 )
        goto LABEL_15;
      printf_impl("ERROR:   Error initializing runtime service %s\n");
LABEL_18:
      if ( ++v2 == v1 )
        return;
    }
    if ( *(_QWORD *)(v3 + 24) == 0 )
      goto LABEL_20;
LABEL_15:
    v7 = (*(_BYTE *)(v3 + 2) & 1) << 6;
    v8 = v7 | *(_BYTE *)(MEMORY[0x9400D1D8] + 32 * v2) & 0x3F;
    v9 = v7 | *(_BYTE *)(MEMORY[0x9400D1D8] + 32 * v2 + 1) & 0x3F;
    while ( v8 <= v9 )
      *(_BYTE *)(0x9400E688LL + v8++) = v2;
    goto LABEL_18;
  }
}

/* ===== std_svc_handler @ 0x940020D4 size 176 ===== */
__int64 *__fastcall std_svc_handler(int a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 *a7)
{
  __int64 v8; // x0

  if ( (a1 & 0xFFE0) == 0 )
  {
    v8 = psci_smc_handler();
LABEL_10:
    *a7 = v8;
    return a7;
  }
  if ( a1 == -2080309503 )
  {
    a7[3] = 3807789398LL;
    a7[1] = 1206450275;
    a7[2] = 4223675822LL;
    v8 = 277712987;
    goto LABEL_10;
  }
  if ( a1 != -2080309501 )
  {
    if ( a1 == -2080309504 )
      v8 = 22;
    else
      v8 = 0xFFFFFFFFLL;
    goto LABEL_10;
  }
  *a7 = 0;
  a7[1] = 1;
  return a7;
}

/* ===== std_svc_setup @ 0x94002184 size 60 ===== */
__int64 std_svc_setup()
{
  if ( get_arm_std_svc_args(65504) == nullptr )
    assert_fail("std_svc_setup", "services/std_svc/std_svc_setup.c", 54, "svc_arg");
  return psci_setup();
}

/* ===== cm_init_context_common @ 0x940021C0 size 312 ===== */
__int64 __fastcall cm_init_context_common(_QWORD *a1, __int64 a2)
{
  unsigned int v4; // w21
  int v5; // w2
  unsigned int v6; // w22
  int v7; // w0
  __int64 v8; // x2
  unsigned __int64 v9; // x1
  __int64 v10; // x0
  __int64 v11; // x4
  bool v12; // zf

  if ( a1 == nullptr )
    assert_fail("cm_init_context_common", "lib/el3_runtime/aarch64/context_mgmt.c", 89, "ctx");
  v4 = *(_DWORD *)(a2 + 4) & 1;
  memset_simple(a1, 0, 1056);
  v5 = _ReadStatusReg(SCR_EL3) & 0xFFFFF2F8 | v4;
  if ( (*(_DWORD *)(a2 + 16) & 0x10LL) == 0 )
    v5 |= 0x400u;
  if ( (*(_DWORD *)(a2 + 4) & 4) != 0 )
    v5 |= 0x800u;
  v6 = v5 & 0xFFFFFFF7;
  v7 = get_scr_el3_from_routing_model(v4);
  v8 = 0x2000000;
  v9 = *(unsigned int *)(a2 + 16);
  v10 = v6 | v7;
  if ( (*(_DWORD *)(a2 + 4) & 2) == 0 )
    v8 = 0;
  if ( (v9 & 0x10) != 0 )
  {
    if ( v4 != 0 )
      v11 = 12912696;
    else
      v11 = 12584984;
  }
  else
  {
    v11 = 818939904;
  }
  a1[38] = v8 | v11;
  if ( (v9 & 0x10) != 0 )
    v12 = (v9 & 0xF) == 10;
  else
    v12 = ((v9 >> 2) & 3) == 2;
  if ( v12 )
    v10 = (unsigned int)v10 | 0x100;
  a1[32] = v10;
  a1[35] = *(_QWORD *)(a2 + 8);
  a1[34] = (unsigned int)v9;
  return memcpy_simple(a1, a2 + 24, 64);
}

/* ===== cm_set_next_context @ 0x940022F8 size 68 ===== */
void cm_set_next_context()
{
  if ( _ReadStatusReg(SPSel) != 0 )
    assert_fail("cm_set_next_context", "include/lib/el3_runtime/context_mgmt.h", 98, "sp_mode == MODE_SP_EL0");
  __asm { MSR             SPSel, #1 }
  __asm { MSR             SPSel, #0 }
}

/* ===== nullsub_2 @ 0x9400233C size 4 ===== */
void nullsub_2()
{
  ;
}

/* ===== cm_init_context_by_index @ 0x94002340 size 44 ===== */
__int64 __fastcall cm_init_context_by_index(__int64 a1, __int64 a2)
{
  _QWORD *v3; // x0

  v3 = (_QWORD *)cm_get_context_by_index(a1, *(_DWORD *)(a2 + 4) & 1);
  return cm_init_context_common(v3, a2);
}

/* ===== cm_init_context @ 0x9400236C size 40 ===== */
__int64 __fastcall cm_init_context(__int64 a1)
{
  _QWORD *v1; // x0

  v1 = (_QWORD *)cm_get_context(*(_DWORD *)(a1 + 4) & 1);
  return cm_init_context_common(v1, a1);
}

/* ===== cm_prepare_el3_exit @ 0x94002394 size 244 ===== */
void __fastcall cm_prepare_el3_exit(unsigned int a1)
{
  __int64 v2; // x0
  __int64 v3; // x19
  __int64 v4; // x0
  bool v5; // zf
  unsigned __int64 v6; // x0

  v2 = cm_get_context(a1);
  v3 = v2;
  if ( v2 == 0 )
    assert_fail("cm_prepare_el3_exit", "lib/el3_runtime/aarch64/context_mgmt.c", 220, "ctx");
  if ( a1 == 1 )
  {
    v4 = *(_QWORD *)(v2 + 256);
    if ( (v4 & 0x100) != 0 )
    {
      _WriteStatusReg(SCTLR_EL2, *(_DWORD *)(v3 + 304) & 0xCD3AF7CF | 0x30C50830);
    }
    else if ( (_ReadStatusReg(ID_AA64PFR0_EL1) & 0xF00) != 0 )
    {
      v5 = (v4 & 0x400) == 0;
      v6 = 0x80000000LL;
      if ( v5 )
        v6 = 0;
      _WriteStatusReg(HCR_EL2, v6);
      _WriteStatusReg(CPTR_EL2, _ReadStatusReg(CPTR_EL2) & 0x7FEFFBFF);
      _WriteStatusReg(CNTHCTL_EL2, 3u);
      _WriteStatusReg(CNTVOFF_EL2, 0);
      _WriteStatusReg(VPIDR_EL2, _ReadStatusReg(MIDR_EL1));
      _WriteStatusReg(VMPIDR_EL2, _ReadStatusReg(MPIDR_EL1));
      _WriteStatusReg(VTTBR_EL2, 0);
      _WriteStatusReg(MDCR_EL2, (unsigned __int16)_ReadStatusReg(PMCR_EL0) >> 11);
      _WriteStatusReg(HSTR_EL2, 0);
      _WriteStatusReg(CNTHP_CTL_EL2, 0);
    }
  }
  el1_sysregs_restore(v3 + 288);
  cm_set_next_context();
}

/* ===== cm_el1_sysregs_context_save @ 0x94002488 size 60 ===== */
unsigned __int64 *__fastcall cm_el1_sysregs_context_save(unsigned int a1)
{
  __int64 v1; // x0
  unsigned __int64 *result; // x0
  unsigned __int64 StatusReg; // x9
  unsigned __int64 v4; // x10
  unsigned __int64 v5; // x15
  unsigned __int64 v6; // x16
  unsigned __int64 v7; // x17
  unsigned __int64 v8; // x9
  unsigned __int64 v9; // x10
  unsigned __int64 v10; // x11
  unsigned __int64 v11; // x12
  unsigned __int64 v12; // x13
  unsigned __int64 v13; // x14
  unsigned __int64 v14; // x15
  unsigned __int64 v15; // x16
  unsigned __int64 v16; // x17
  unsigned __int64 v17; // x9
  unsigned __int64 v18; // x10
  unsigned __int64 v19; // x13
  unsigned __int64 v20; // x14
  unsigned __int64 v21; // x15
  unsigned __int64 v22; // x16
  unsigned __int64 v23; // x17
  unsigned __int64 v24; // x9
  unsigned __int64 v25; // x11
  unsigned __int64 v26; // x12
  unsigned __int64 v27; // x13
  unsigned __int64 v28; // x14
  unsigned __int64 v29; // x15
  unsigned __int64 v30; // x16

  v1 = cm_get_context(a1);
  if ( v1 == 0 )
    assert_fail("cm_el1_sysregs_context_save", "lib/el3_runtime/aarch64/context_mgmt.c", 302, "ctx");
  result = (unsigned __int64 *)(v1 + 288);
  StatusReg = _ReadStatusReg(SPSR_EL1);
  v4 = _ReadStatusReg(ELR_EL1);
  *result = StatusReg;
  result[1] = v4;
  v5 = _ReadStatusReg(SCTLR_EL1);
  v6 = _ReadStatusReg(ACTLR_EL1);
  result[2] = v5;
  result[3] = v6;
  v7 = _ReadStatusReg(CPACR_EL1);
  v8 = _ReadStatusReg(CSSELR_EL1);
  result[4] = v7;
  result[5] = v8;
  v9 = _ReadStatusReg(SP_EL1);
  v10 = _ReadStatusReg(ESR_EL1);
  result[6] = v9;
  result[7] = v10;
  v11 = _ReadStatusReg(TTBR0_EL1);
  v12 = _ReadStatusReg(TTBR1_EL1);
  result[8] = v11;
  result[9] = v12;
  v13 = _ReadStatusReg(MAIR_EL1);
  v14 = _ReadStatusReg(AMAIR_EL1);
  result[10] = v13;
  result[11] = v14;
  v15 = _ReadStatusReg(TCR_EL1);
  v16 = _ReadStatusReg(TPIDR_EL1);
  result[12] = v15;
  result[13] = v16;
  v17 = _ReadStatusReg(TPIDR_EL0);
  v18 = _ReadStatusReg(TPIDRRO_EL0);
  result[14] = v17;
  result[15] = v18;
  v19 = _ReadStatusReg(PAR_EL1);
  v20 = _ReadStatusReg(FAR_EL1);
  result[16] = v19;
  result[17] = v20;
  v21 = _ReadStatusReg(AFSR0_EL1);
  v22 = _ReadStatusReg(AFSR1_EL1);
  result[18] = v21;
  result[19] = v22;
  v23 = _ReadStatusReg(CONTEXTIDR_EL1);
  v24 = _ReadStatusReg(VBAR_EL1);
  result[20] = v23;
  result[21] = v24;
  v25 = _ReadStatusReg(SPSR_abt);
  v26 = _ReadStatusReg(SPSR_und);
  result[22] = v25;
  result[23] = v26;
  v27 = _ReadStatusReg(SPSR_irq);
  v28 = _ReadStatusReg(SPSR_fiq);
  result[24] = v27;
  result[25] = v28;
  v29 = _ReadStatusReg(DACR32_EL2);
  v30 = _ReadStatusReg(IFSR32_EL2);
  result[26] = v29;
  result[27] = v30;
  result[28] = _ReadStatusReg(FPEXC32_EL2);
  return result;
}

/* ===== cm_el1_sysregs_context_restore @ 0x940024C4 size 60 ===== */
__int64 __fastcall cm_el1_sysregs_context_restore(unsigned int a1)
{
  __int64 v1; // x0

  v1 = cm_get_context(a1);
  if ( v1 == 0 )
    assert_fail("cm_el1_sysregs_context_restore", "lib/el3_runtime/aarch64/context_mgmt.c", 312, "ctx");
  return el1_sysregs_restore(v1 + 288);
}

/* ===== cm_set_elr_el3 @ 0x94002500 size 68 ===== */
__int64 __fastcall cm_set_elr_el3(unsigned int a1, __int64 a2)
{
  __int64 result; // x0

  result = cm_get_context(a1);
  if ( result == 0 )
    assert_fail("cm_set_elr_el3", "lib/el3_runtime/aarch64/context_mgmt.c", 327, "ctx");
  *(_QWORD *)(result + 280) = a2;
  return result;
}

/* ===== cm_set_elr_spsr_el3 @ 0x94002544 size 84 ===== */
__int64 __fastcall cm_set_elr_spsr_el3(unsigned int a1, __int64 a2, unsigned int a3)
{
  __int64 result; // x0

  result = cm_get_context(a1);
  if ( result == 0 )
    assert_fail("cm_set_elr_spsr_el3", "lib/el3_runtime/aarch64/context_mgmt.c", 345, "ctx");
  *(_QWORD *)(result + 280) = a2;
  *(_QWORD *)(result + 272) = a3;
  return result;
}

/* ===== cm_write_scr_el3_bit @ 0x94002598 size 184 ===== */
__int64 __fastcall cm_write_scr_el3_bit(unsigned int a1, char a2, unsigned int a3)
{
  __int64 result; // x0
  __int64 v4; // x2
  const char *v5; // x3

  result = cm_get_context(a1);
  if ( result == 0 )
  {
    v4 = 367;
    v5 = "ctx";
    goto LABEL_5;
  }
  if ( ((12175 >> a2) & 1) == 0 )
  {
    v4 = 370;
    v5 = "(1 << bit_pos) & SCR_VALID_BIT_MASK";
    goto LABEL_5;
  }
  if ( a3 > 1 )
  {
    v4 = 373;
    v5 = "value <= 1";
LABEL_5:
    assert_fail("cm_write_scr_el3_bit", "lib/el3_runtime/aarch64/context_mgmt.c", v4, v5);
  }
  *(_QWORD *)(result + 256) = (unsigned int)*(_QWORD *)(result + 256) & ~(1 << a2) | (a3 << a2);
  return result;
}

/* ===== cm_set_next_eret_context @ 0x94002650 size 56 ===== */
void __fastcall cm_set_next_eret_context(unsigned int a1)
{
  if ( cm_get_context(a1) == 0 )
    assert_fail("cm_set_next_eret_context", "lib/el3_runtime/aarch64/context_mgmt.c", 413, "ctx");
  cm_set_next_context();
}

/* ===== psci_do_cpu_off @ 0x94002688 size 316 ===== */
__int64 __fastcall psci_do_cpu_off(unsigned int a1)
{
  unsigned int v2; // w22
  __int64 v3; // x0
  unsigned int v4; // w20
  __int64 (__fastcall *v5)(_QWORD); // x1
  void (__fastcall *v6)(_BYTE *); // x1
  _BYTE v8[8]; // [xsp+38h] [xbp+38h] BYREF

  v2 = get_cpu_id();
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 16LL) == 0 )
    assert_fail("psci_do_cpu_off", "lib/psci/psci_off.c", 74, "psci_plat_pm_ops->pwr_domain_off");
  psci_acquire_pwr_domain_locks(a1, v2);
  if ( MEMORY[0x9400E988] == 0
    || (v5 = *(__int64 (__fastcall **)(_QWORD))(MEMORY[0x9400E988] + 8LL)) == nullptr
    || (v4 = v5(0)) == 0 )
  {
    v8[0] = 2;
    v8[1] = 2;
    psci_do_state_coordination(a1, v8);
    psci_stats_update_pwr_down(a1, v8);
    v3 = psci_get_max_off_lvl(v8);
    cpu_context_save(v3);
    (*(void (__fastcall **)(_BYTE *))(MEMORY[0x9400E980] + 16LL))(v8);
    v4 = 0;
    pmf_capture_timestamp(0, _ReadStatusReg(CNTPCT_EL0));
  }
  psci_release_pwr_domain_locks(a1, v2);
  if ( v4 == 0 )
  {
    dcache_clean_invalidate(_ReadStatusReg(TPIDR_EL3) + 88, 4);
    *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) = 1;
    __dsb(0xBu);
    dcache_invalidate(_ReadStatusReg(TPIDR_EL3) + 88, 4);
    v6 = *(void (__fastcall **)(_BYTE *))(MEMORY[0x9400E980] + 48LL);
    if ( v6 != nullptr )
      v6(v8);
    cpu_power_down();
  }
  return v4;
}

/* ===== psci_cpu_on_start @ 0x940027C4 size 628 ===== */
__int64 __fastcall psci_cpu_on_start(__int64 a1, __int64 a2)
{
  unsigned int v4; // w19
  const char *v5; // x0
  __int64 v6; // x2
  char *v7; // x3
  int v8; // w2
  __int64 v9; // x0
  int v10; // w0
  __int64 v11; // x0
  unsigned int v12; // w0
  unsigned int v13; // w20
  __int64 v14; // x0

  v4 = psci_validate_affinity(a1);
  if ( (v4 & 0x80000000) != 0 )
  {
    v5 = "psci_cpu_on_start";
    v6 = 75;
    v7 = "(int) target_idx >= 0";
    goto LABEL_5;
  }
  if ( a2 == 0 )
  {
    v5 = "psci_cpu_on_start";
    v6 = 76;
    v7 = "ep != NULL";
    goto LABEL_5;
  }
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 8LL) == 0 || *(_QWORD *)(MEMORY[0x9400E980] + 32LL) == 0 )
  {
    v5 = "psci_cpu_on_start";
    v6 = 83;
    v7 = "psci_plat_pm_ops->pwr_domain_on && psci_plat_pm_ops->pwr_domain_on_finish";
    goto LABEL_5;
  }
  spin_lock(16LL * v4 + 0x9400E940LL + 12);
  v8 = *(_DWORD *)(get_cpu_context_ptr(v4) + 88);
  if ( v8 != 0 )
  {
    if ( v8 == 2 )
    {
      v13 = -5;
    }
    else
    {
      if ( v8 != 1 )
      {
        v5 = "cpu_on_validate_state";
        v6 = 53;
        v7 = "aff_state == AFF_STATE_OFF";
        goto LABEL_5;
      }
      if ( MEMORY[0x9400E988] != 0 && *MEMORY[0x9400E988] != 0 )
        ((void (__fastcall *)(__int64))*MEMORY[0x9400E988])(a1);
      *(_DWORD *)(get_cpu_context_ptr(v4) + 88) = 2;
      v9 = get_cpu_context_ptr(v4);
      dcache_clean_invalidate(v9 + 88, 4);
      v10 = *(_DWORD *)(get_cpu_context_ptr(v4) + 88);
      if ( v10 != 2 )
      {
        if ( v10 != 1 )
        {
          v5 = "psci_cpu_on_start";
          v6 = 120;
          v7 = "target_aff_state == AFF_STATE_OFF";
          goto LABEL_5;
        }
        *(_DWORD *)(get_cpu_context_ptr(v4) + 88) = 2;
        v11 = get_cpu_context_ptr(v4);
        dcache_clean_invalidate(v11 + 88, 4);
        if ( *(_DWORD *)(get_cpu_context_ptr(v4) + 88) != 2 )
        {
          v5 = "psci_cpu_on_start";
          v6 = 124;
          v7 = "psci_get_aff_info_state_by_idx(target_idx) == AFF_STATE_ON_PENDING";
          goto LABEL_5;
        }
      }
      v12 = (*(__int64 (__fastcall **)(__int64))(MEMORY[0x9400E980] + 8LL))(a1);
      v13 = v12;
      if ( v12 != -6 && v12 != 0 )
      {
        v5 = "psci_cpu_on_start";
        v6 = 136;
        v7 = "rc == PSCI_E_SUCCESS || rc == PSCI_E_INTERN_FAIL";
LABEL_5:
        assert_fail(v5, "lib/psci/psci_on.c", v6, v7);
      }
      if ( v12 != 0 )
      {
        *(_DWORD *)(get_cpu_context_ptr(v4) + 88) = 1;
        v14 = get_cpu_context_ptr(v4);
        dcache_clean_invalidate(v14 + 88, 4);
      }
      else
      {
        cm_init_context_by_index(v4, a2);
      }
    }
  }
  else
  {
    v13 = -4;
  }
  spin_unlock(16LL * v4 + 0x9400E940LL + 12);
  return v13;
}

/* ===== psci_cpu_on_finish @ 0x94002A38 size 204 ===== */
void __fastcall psci_cpu_on_finish(unsigned int a1, __int64 a2)
{
  __int64 v2; // x19
  __int64 v3; // x0
  __int64 v4; // x0
  void (__fastcall *v5)(_QWORD); // x1

  v2 = a1;
  v3 = (*(__int64 (__fastcall **)(__int64))(MEMORY[0x9400E980] + 32LL))(a2);
  v4 = cpu_context_restore(v3);
  psci_timer_init(v4);
  spin_lock(0x9400E940LL + 16 * v2 + 12);
  spin_unlock(0x9400E940LL + 16 * v2 + 12);
  if ( *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) != 2 )
    assert_fail("psci_cpu_on_finish", "lib/psci/psci_on.c", 190, "psci_get_aff_info_state() == AFF_STATE_ON_PENDING");
  if ( MEMORY[0x9400E988] != 0 )
  {
    v5 = *(void (__fastcall **)(_QWORD))(MEMORY[0x9400E988] + 24LL);
    if ( v5 != nullptr )
      v5(0);
  }
  *(_QWORD *)(0x9400E940LL + 16 * v2) = _ReadStatusReg(MPIDR_EL1) & 0xFF00FFFFFFLL;
  cm_prepare_el3_exit(1u);
}

/* ===== psci_cpu_suspend_start @ 0x94002B04 size 400 ===== */
__int64 __fastcall psci_cpu_suspend_start(__int64 a1, unsigned int a2, __int64 a3, int a4)
{
  unsigned int v8; // w21
  int v9; // w24
  unsigned int v10; // w24
  void (__fastcall *v11)(_QWORD); // x1
  __int64 result; // x0
  void (__fastcall *v13)(__int64); // x1
  char v14; // [xsp+58h] [xbp+58h] BYREF

  v8 = get_cpu_id();
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 24LL) == 0 || *(_QWORD *)(MEMORY[0x9400E980] + 40LL) == 0 )
    assert_fail(
      "psci_cpu_suspend_start",
      "lib/psci/psci_suspend.c",
      153,
      "psci_plat_pm_ops->pwr_domain_suspend && psci_plat_pm_ops->pwr_domain_suspend_finish");
  psci_acquire_pwr_domain_locks(a2, v8);
  v9 = 1;
  if ( _ReadStatusReg(ISR_EL1) == 0 )
  {
    psci_do_state_coordination(a2, a3);
    psci_stats_update_pwr_down(a2, a3);
    if ( a4 != 0 )
    {
      v10 = psci_get_max_off_lvl(a3);
      *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 92) = a2;
      dcache_clean_invalidate(_ReadStatusReg(TPIDR_EL3) + 92, 1);
      if ( MEMORY[0x9400E988] != 0 )
      {
        v11 = *(void (__fastcall **)(_QWORD))(MEMORY[0x9400E988] + 16LL);
        if ( v11 != nullptr )
          v11(v10);
      }
      cm_init_context(a1);
      cpu_context_save(v10);
    }
    (*(void (__fastcall **)(__int64))(MEMORY[0x9400E980] + 24LL))(a3);
    v9 = 0;
    pmf_capture_timestamp(0, _ReadStatusReg(CNTPCT_EL0));
  }
  result = psci_release_pwr_domain_locks(a2, v8);
  if ( v9 == 0 )
  {
    if ( a4 != 0 )
    {
      v13 = *(void (__fastcall **)(__int64))(MEMORY[0x9400E980] + 48LL);
      if ( v13 != nullptr )
        v13(a3);
      cpu_power_down();
    }
    __wfi();
    psci_acquire_pwr_domain_locks(a2, v8);
    psci_get_target_pwr_state(a2, &v14);
    (*(void (__fastcall **)(char *))(MEMORY[0x9400E980] + 40LL))(&v14);
    psci_do_state_coordination_finish(a2);
    return psci_release_pwr_domain_locks(a2, v8);
  }
  return result;
}

/* ===== psci_cpu_suspend_finish @ 0x94002C94 size 224 ===== */
void __fastcall psci_cpu_suspend_finish(__int64 a1, _BYTE *a2)
{
  __int64 v2; // x2
  const char *v3; // x3
  __int64 v4; // x0
  __int64 v5; // x0
  unsigned int v6; // w0

  if ( *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) != 0 || *a2 != 2 )
  {
    v2 = 276;
    v3 = "psci_get_aff_info_state() == AFF_STATE_ON && is_local_state_off( state_info->pwr_domain_state[PSCI_CPU_PWR_LVL])";
    goto LABEL_8;
  }
  v4 = (*(__int64 (__fastcall **)(_BYTE *))(MEMORY[0x9400E980] + 40LL))(a2);
  v5 = cpu_context_restore(v4);
  _WriteStatusReg(CNTFRQ_EL0, (unsigned int)get_uart_clock(v5));
  if ( MEMORY[0x9400E988] != 0 && *(_QWORD *)(MEMORY[0x9400E988] + 16LL) != 0 )
  {
    v6 = psci_get_max_off_lvl(a2);
    if ( v6 == 2 )
    {
      v2 = 305;
      v3 = "max_off_lvl != PSCI_INVALID_PWR_LVL";
LABEL_8:
      assert_fail("psci_cpu_suspend_finish", "lib/psci/psci_suspend.c", v2, v3);
    }
    (*(void (__fastcall **)(_QWORD))(MEMORY[0x9400E988] + 32LL))(v6);
  }
  *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 92) = 2;
  cm_prepare_el3_exit(1u);
}

/* ===== psci_set_req_local_pwr_state @ 0x94002D74 size 40 ===== */
void __noreturn psci_set_req_local_pwr_state()
{
  assert_fail("psci_set_req_local_pwr_state", "lib/psci/psci_common.c", 219, "pwrlvl > PSCI_CPU_PWR_LVL");
}

/* ===== psci_validate_power_state @ 0x94002D9C size 88 ===== */
__int64 __fastcall psci_validate_power_state(int a1)
{
  __int64 (*v1)(void); // x2

  if ( (a1 & 0xFCFE0000) != 0 )
    return 4294967294LL;
  v1 = *(__int64 (**)(void))(MEMORY[0x9400E980] + 72LL);
  if ( v1 == nullptr )
    assert_fail("psci_validate_power_state", "lib/psci/psci_common.c", 142, "psci_plat_pm_ops->validate_power_state");
  return v1();
}

/* ===== psci_query_sys_suspend_pwrstate @ 0x94002DF4 size 68 ===== */
__int64 psci_query_sys_suspend_pwrstate()
{
  __int64 (*v0)(void); // x1

  v0 = *(__int64 (**)(void))(MEMORY[0x9400E980] + 88LL);
  if ( v0 == nullptr )
    assert_fail(
      "psci_query_sys_suspend_pwrstate",
      "lib/psci/psci_common.c",
      158,
      "psci_plat_pm_ops->get_sys_suspend_power_state");
  return v0();
}

/* ===== psci_is_last_on_cpu @ 0x94002E38 size 132 ===== */
__int64 psci_is_last_on_cpu()
{
  unsigned int v0; // w19
  int v1; // w20

  v0 = 0;
  v1 = get_cpu_id();
  while ( 1 )
  {
    if ( v0 == v1 )
    {
      if ( *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) != 0 )
        assert_fail("psci_is_last_on_cpu", "lib/psci/psci_common.c", 178, "psci_get_aff_info_state() == AFF_STATE_ON");
      goto LABEL_4;
    }
    if ( *(_DWORD *)(get_cpu_context_ptr(v0) + 88) != 1 )
      return 0;
LABEL_4:
    if ( ++v0 == 4 )
      return 1;
  }
}

/* ===== psci_clear_aff_info @ 0x94002EBC size 20 ===== */
__int64 psci_clear_aff_info()
{
  return memset_simple(0x9400D1E0, 2, 4);
}

/* ===== psci_get_target_pwr_state @ 0x94002ED0 size 140 ===== */
unsigned __int64 __fastcall psci_get_target_pwr_state(unsigned int a1, _BYTE *a2)
{
  unsigned int v3; // w0
  unsigned int v4; // w2
  unsigned int v5; // w3
  unsigned __int64 result; // x0
  __int64 v7; // x3

  *a2 = *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 93);
  v3 = get_cpu_id();
  v4 = 1;
  v5 = *(_DWORD *)(0x9400E940 + 16LL * v3 + 8);
  result = 0x94014010;
  while ( v4 <= a1 )
  {
    v7 = 0x94014010 + 16LL * v5;
    a2[v4++] = *(_BYTE *)(v7 + 12);
    v5 = *(_DWORD *)(v7 + 8);
  }
  while ( v4 <= 1 )
    a2[v4++] = 0;
  return result;
}

/* ===== psci_get_parent_pwr_lvl @ 0x94002F5C size 68 ===== */
__int64 __fastcall psci_get_parent_pwr_lvl(unsigned int a1, unsigned int a2, unsigned int *a3)
{
  unsigned int v3; // w3
  __int64 result; // x0

  v3 = *(_DWORD *)(0x9400E940 + 16LL * a1 + 8);
  result = 1;
  while ( (unsigned int)result <= a2 )
  {
    *a3++ = v3;
    result = (unsigned int)(result + 1);
    v3 = *(_DWORD *)(0x94014010 + 16LL * v3 + 8);
  }
  return result;
}

/* ===== psci_do_state_coordination_finish @ 0x94002FA0 size 144 ===== */
__int64 __fastcall psci_do_state_coordination_finish(unsigned int a1)
{
  unsigned int v2; // w0
  __int64 v3; // x2

  v2 = get_cpu_id();
  if ( a1 != 0 )
  {
    v3 = 0x94014010 + 16LL * *(unsigned int *)(0x9400E940 + 16LL * v2 + 8);
    *(_BYTE *)(v3 + 12) = 0;
    *(_BYTE *)(0x9400D1E0LL + v2) = 0;
    if ( a1 > 1 )
    {
      *(_BYTE *)(0x94014010 + 16LL * *(unsigned int *)(v3 + 8) + 12) = 0;
      psci_set_req_local_pwr_state();
    }
  }
  *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) = 0;
  *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 93) = 0;
  return dcache_clean_invalidate(_ReadStatusReg(TPIDR_EL3) + 88, 8);
}

/* ===== psci_do_state_coordination @ 0x94003030 size 244 ===== */
__int64 __fastcall psci_do_state_coordination(unsigned int a1, _BYTE *a2)
{
  unsigned int v4; // w0
  __int64 v5; // x2
  unsigned int v6; // w0
  __int64 v7; // x0
  __int64 result; // x0

  v4 = ((__int64 (*)(void))get_cpu_id)();
  if ( a1 > 1 )
    assert_fail("psci_do_state_coordination", "lib/psci/psci_common.c", 396, "end_pwrlvl <= PLAT_MAX_PWR_LVL");
  v5 = v4;
  v6 = *(_DWORD *)(0x9400E940 + 16LL * v4 + 8);
  if ( a1 != 0 )
  {
    *(_BYTE *)(0x9400D1E0LL + v5) = a2[1];
    a2[1] = plat_get_target_pwr_state(
              1,
              0x9400D1E0LL + *(unsigned int *)(0x94014010 + 16LL * v6),
              *(_DWORD *)(0x94014010 + 16LL * v6 + 4));
  }
  *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 93) = *a2;
  v7 = dcache_clean_invalidate(_ReadStatusReg(TPIDR_EL3) + 93, 1);
  result = 16LL * (unsigned int)get_cpu_id(v7);
  if ( a1 != 0 )
  {
    result = 0x94014010 + 16LL * *(unsigned int *)(0x9400E940LL + result + 8);
    *(_BYTE *)(result + 12) = a2[1];
  }
  return result;
}

/* ===== psci_get_max_off_lvl @ 0x94003124 size 44 ===== */
__int64 __fastcall psci_get_max_off_lvl(unsigned __int8 *a1)
{
  int v1; // w1
  __int64 result; // x0

  if ( a1[1] == 2 )
    return 1;
  v1 = *a1;
  result = 2;
  if ( v1 == 2 )
    return 0;
  return result;
}

/* ===== psci_find_target_suspend_lvl @ 0x94003150 size 36 ===== */
__int64 __fastcall psci_find_target_suspend_lvl(unsigned __int8 *a1)
{
  unsigned int v1; // w1
  int v2; // w2
  __int64 result; // x0

  v1 = a1[1];
  if ( a1[1] != 0 )
    return 1;
  v2 = *a1;
  result = 2;
  if ( v2 != 0 )
    return v1;
  return result;
}

/* ===== psci_validate_suspend_req @ 0x94003174 size 180 ===== */
__int64 __fastcall psci_validate_suspend_req(unsigned __int8 *a1, int a2)
{
  int v4; // w0
  int v5; // w19
  int v6; // w2
  unsigned int v7; // w0
  unsigned int v8; // w3
  int v9; // w1
  __int64 result; // x0

  v4 = psci_find_target_suspend_lvl(a1);
  v5 = v4;
  if ( v4 == 2 )
    return 4294967294LL;
  v6 = v4;
  v7 = 0;
  while ( (v6 & 0x80000000) == 0 )
  {
    if ( a1[v6] != 0 )
    {
      v8 = 2;
      if ( a1[v6] > 1u )
        goto LABEL_9;
      v8 = 1;
    }
    else
    {
      v8 = a1[v6];
    }
    if ( v8 < v7 )
      return 4294967294LL;
LABEL_9:
    --v6;
    v7 = v8;
  }
  v9 = psci_get_max_off_lvl(a1);
  if ( v5 == v9 )
    v5 = 2;
  result = 0;
  if ( a2 == 0 )
  {
    if ( v5 != 2 && v9 == 2 )
      return 0;
    return 4294967294LL;
  }
  return result;
}

/* ===== psci_acquire_pwr_domain_locks @ 0x94003228 size 124 ===== */
__int64 __fastcall psci_acquire_pwr_domain_locks(unsigned int a1, unsigned int a2)
{
  __int64 result; // x0
  unsigned int v4; // w20
  unsigned int i; // w19
  __int64 v6; // x20

  result = 0x9400E940;
  v4 = *(_DWORD *)(0x9400E940 + 16LL * a2 + 8);
  for ( i = 1; i <= a1; ++i )
  {
    v6 = 0x94014010 + 16LL * v4;
    result = bakery_lock_get(0x94014008 + 8LL * *(unsigned __int8 *)(v6 + 14));
    v4 = *(_DWORD *)(v6 + 8);
  }
  return result;
}

/* ===== psci_release_pwr_domain_locks @ 0x940032A4 size 116 ===== */
__int64 __fastcall psci_release_pwr_domain_locks(unsigned int a1, unsigned int a2)
{
  int v2; // w19
  __int64 result; // x0
  unsigned int v4[2]; // [xsp+38h] [xbp+38h] BYREF

  v2 = a1;
  v4[0] = 0;
  result = psci_get_parent_pwr_lvl(a2, a1, v4);
  while ( v2 > 0 )
    result = bakery_lock_release(0x94014008 + 8LL * *(unsigned __int8 *)(0x94014010 + 16LL * v4[--v2] + 14));
  return result;
}

/* ===== psci_validate_cpu_on @ 0x94003318 size 8 ===== */
__int64 psci_validate_cpu_on()
{
  return 0;
}

/* ===== psci_setup_ep_info @ 0x94003320 size 272 ===== */
__int64 __fastcall psci_setup_ep_info(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned int (__fastcall *v5)(__int64); // x1
  __int16 StatusReg; // w21
  int v8; // w0
  int v9; // w25
  int v10; // w0
  __int64 result; // x0
  int v12; // w1
  int v13; // w22

  v5 = *(unsigned int (__fastcall **)(__int64))(MEMORY[0x9400E980] + 80LL);
  if ( v5 != nullptr && v5(a2) != 0 )
    return 4294967287LL;
  StatusReg = _ReadStatusReg(SCR_EL3);
  v8 = _ReadStatusReg(SCTLR_EL1);
  if ( (StatusReg & 0x100) != 0 )
    v8 = _ReadStatusReg(SCTLR_EL2);
  v9 = (v8 & 0x2000000) != 0;
  *(_BYTE *)a1 = 1;
  if ( (v8 & 0x2000000) != 0 )
    v10 = 3;
  else
    v10 = 1;
  *(_BYTE *)(a1 + 1) = 1;
  *(_DWORD *)(a1 + 4) = v10;
  *(_WORD *)(a1 + 2) = 88;
  *(_QWORD *)(a1 + 8) = a2;
  memset_simple(a1 + 24, 0, 64);
  *(_QWORD *)(a1 + 24) = a3;
  result = StatusReg & 0x400;
  if ( (StatusReg & 0x400) != 0 )
  {
    result = a2 & 1;
    if ( (a2 & 1) != 0 )
      return 4294967287LL;
    if ( (StatusReg & 0x100) != 0 )
      v12 = 2;
    else
      v12 = 1;
    *(_DWORD *)(a1 + 16) = (4 * v12) | 0x3C1;
  }
  else
  {
    if ( (StatusReg & 0x100) != 0 )
      v13 = 10;
    else
      v13 = 3;
    *(_DWORD *)(a1 + 16) = (32 * (a2 & 1)) | 0x1D0 | (v9 << 9) | v13;
  }
  return result;
}

/* ===== psci_cpu_on_handler @ 0x94003430 size 192 ===== */
__int64 __fastcall psci_cpu_on_handler(__int64 a1)
{
  unsigned int v1; // w20
  __int64 v2; // x0
  unsigned int v3; // w19
  __int16 v5; // [xsp+28h] [xbp+28h] BYREF

  v5 = 0;
  v1 = get_cpu_id(a1);
  if ( *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) == 1 )
  {
    v2 = printf_impl("ERROR:   Unexpected affinity info state");
    panic(v2);
  }
  v3 = *(unsigned __int8 *)(_ReadStatusReg(TPIDR_EL3) + 92);
  if ( v3 == 2 )
    v3 = 1;
  psci_acquire_pwr_domain_locks(v3, v1);
  pmf_capture_timestamp(1, _ReadStatusReg(CNTPCT_EL0));
  psci_get_target_pwr_state(v3, &v5);
  if ( *(_DWORD *)(_ReadStatusReg(TPIDR_EL3) + 88) == 2 )
    psci_cpu_on_finish(v1, (__int64)&v5);
  else
    psci_cpu_suspend_finish(v1, &v5);
  psci_do_state_coordination_finish(v3);
  psci_stats_update_pwr_up(v3, &v5, 1);
  return psci_release_pwr_domain_locks(v3, v1);
}

/* ===== psci_register_spd_pm_hook @ 0x940034F0 size 108 ===== */
unsigned __int64 __fastcall psci_register_spd_pm_hook(__int64 a1)
{
  unsigned __int64 result; // x0

  if ( a1 == 0 )
    assert_fail("psci_register_spd_pm_hook", "lib/psci/psci_common.c", 822, "pm");
  MEMORY[0x9400E988] = a1;
  if ( *(_QWORD *)(a1 + 40) != 0 )
    MEMORY[0x9400E990] |= 0x20u;
  result = *(_QWORD *)(a1 + 48);
  if ( result != 0 )
  {
    MEMORY[0x9400E990] |= 0xC0u;
    return 0x9400E000;
  }
  return result;
}

/* ===== psci_spd_migrate_info @ 0x9400355C size 88 ===== */
__int64 psci_spd_migrate_info()
{
  __int64 (*v0)(void); // x1
  __int64 result; // x0

  if ( MEMORY[0x9400E988] == 0 )
    return 0xFFFFFFFFLL;
  v0 = *(__int64 (**)(void))(MEMORY[0x9400E988] + 48LL);
  if ( v0 == nullptr )
    return 0xFFFFFFFFLL;
  result = v0();
  if ( (unsigned int)(result + 1) > 3 )
    assert_fail(
      "psci_spd_migrate_info",
      "lib/psci/psci_common.c",
      850,
      "rc == PSCI_TOS_UP_MIG_CAP || rc == PSCI_TOS_NOT_UP_MIG_CAP || rc == PSCI_TOS_NOT_PRESENT_MP || rc == PSCI_E_NOT_SUPPORTED");
  return result;
}

/* ===== nullsub_8 @ 0x940035B4 size 4 ===== */
void nullsub_8()
{
  ;
}

/* ===== psci_cpu_on @ 0x940035B8 size 84 ===== */
__int64 __fastcall psci_cpu_on(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 result; // x0
  _BYTE v7[88]; // [xsp+38h] [xbp+38h] BYREF

  if ( (unsigned int)psci_validate_cpu_on() != 0 )
    return 4294967294LL;
  result = psci_setup_ep_info((__int64)v7, a2, a3);
  if ( (_DWORD)result == 0 )
    return psci_cpu_on_start(a1, (__int64)v7);
  return result;
}

/* ===== psci_cpu_suspend @ 0x9400360C size 368 ===== */
__int64 __fastcall psci_cpu_suspend(int a1, __int64 a2, __int64 a3)
{
  int v6; // w0
  unsigned int v7; // w19
  __int64 v8; // x2
  char *v9; // x3
  BOOL v10; // w20
  unsigned int v11; // w0
  unsigned int v12; // w21
  __int64 v13; // x0
  unsigned int v14; // w20
  unsigned int v15; // w0
  unsigned __int8 v17[8]; // [xsp+40h] [xbp+40h] BYREF
  _BYTE v18[88]; // [xsp+48h] [xbp+48h] BYREF

  *(_WORD *)v17 = 0;
  v6 = psci_validate_power_state(a1);
  if ( v6 != 0 )
  {
    if ( v6 == -2 )
      return (unsigned int)-2;
    v8 = 90;
    v9 = "rc == PSCI_E_INVALID_PARAMS";
LABEL_7:
    assert_fail("psci_cpu_suspend", "lib/psci/psci_main.c", v8, v9);
  }
  v10 = (*(_QWORD *)&a1 & 0x10000LL) != 0;
  v7 = psci_validate_suspend_req(v17, v10);
  if ( v7 != 0 )
  {
    v8 = 101;
    v9 = "psci_validate_suspend_req(&state_info, is_power_down_state) == PSCI_E_SUCCESS";
    goto LABEL_7;
  }
  v11 = psci_find_target_suspend_lvl(v17);
  v12 = v11;
  if ( v11 == 2 )
  {
    v13 = printf_impl("ERROR:   Invalid target power level for suspend operation\n");
    panic(v13);
  }
  if ( (v11 | v10) == 0 )
  {
    if ( *MEMORY[0x9400E980] != 0 )
    {
      v14 = v17[0];
      *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 93) = v17[0];
      pmf_capture_timestamp(0, _ReadStatusReg(CNTPCT_EL0));
      ((void (__fastcall *)(_QWORD))*MEMORY[0x9400E980])(v14);
      *(_BYTE *)(_ReadStatusReg(TPIDR_EL3) + 93) = 0;
      pmf_capture_timestamp(1, _ReadStatusReg(CNTPCT_EL0));
      psci_stats_update_pwr_up(0, v17, 0);
      return v7;
    }
    return (unsigned int)-2;
  }
  if ( v10 && (v15 = psci_setup_ep_info((__int64)v18, a2, a3)) != 0 )
    return v15;
  else
    psci_cpu_suspend_start((__int64)v18, v12, (__int64)v17, v10);
  return v7;
}

/* ===== psci_system_suspend @ 0x9400377C size 276 ===== */
__int64 __fastcall psci_system_suspend(__int64 a1, __int64 a2)
{
  unsigned int v4; // w19
  __int64 v5; // x2
  const char *v6; // x3
  unsigned __int8 v8[8]; // [xsp+20h] [xbp+20h] BYREF
  _BYTE v9[88]; // [xsp+28h] [xbp+28h] BYREF

  uart_init(1880096768, 26000000, 115200);
  if ( (unsigned int)psci_is_last_on_cpu() != 0 )
  {
    v4 = psci_setup_ep_info((__int64)v9, a1, a2);
    if ( v4 == 0 )
    {
      psci_query_sys_suspend_pwrstate();
      if ( (unsigned int)psci_find_target_suspend_lvl(v8) != 1 )
      {
        v5 = 209;
        v6 = "psci_find_target_suspend_lvl(&state_info) == PLAT_MAX_PWR_LVL";
        goto LABEL_7;
      }
      v4 = psci_validate_suspend_req(v8, 1);
      if ( v4 != 0 )
      {
        v5 = 211;
        v6 = "psci_validate_suspend_req(&state_info, PSTATE_TYPE_POWERDOWN) == PSCI_E_SUCCESS";
        goto LABEL_7;
      }
      if ( v8[1] != 2 )
      {
        v5 = 212;
        v6 = "is_local_state_off(state_info.pwr_domain_state[PLAT_MAX_PWR_LVL])";
LABEL_7:
        assert_fail("psci_system_suspend", "lib/psci/psci_main.c", v5, v6);
      }
      psci_cpu_suspend_start((__int64)v9, 1u, (__int64)v8, 1);
    }
  }
  else
  {
    return (unsigned int)-3;
  }
  return v4;
}

/* ===== psci_cpu_off @ 0x94003890 size 88 ===== */
__int64 psci_cpu_off()
{
  __int64 result; // x0

  uart_init(1880096768, 26000000, 115200);
  result = psci_do_cpu_off(1u);
  if ( (_DWORD)result != -3 )
    assert_fail("psci_cpu_off", "lib/psci/psci_main.c", 249, "rc == PSCI_E_DENIED");
  return result;
}

/* ===== psci_affinity_info @ 0x940038E8 size 48 ===== */
__int64 __fastcall psci_affinity_info(__int64 a1, int a2)
{
  __int64 v3; // x0

  if ( a2 != 0 )
    return 4294967294LL;
  v3 = psci_validate_affinity(a1);
  if ( (_DWORD)v3 == -1 )
    return 4294967294LL;
  else
    return *(unsigned int *)(get_cpu_context_ptr(v3) + 88);
}

/* ===== psci_migrate @ 0x94003918 size 204 ===== */
__int64 __fastcall psci_migrate(__int64 a1)
{
  int v2; // w0
  __int64 result; // x0
  __int64 (__fastcall *v4)(unsigned __int64, __int64); // x2
  __int64 v5; // x2
  const char *v6; // x3
  __int64 v7; // [xsp+28h] [xbp+28h]

  v2 = psci_spd_migrate_info();
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
      return 4294967293LL;
    else
      return 0xFFFFFFFFLL;
  }
  if ( v7 != _ReadStatusReg(MPIDR_EL1) )
    return 4294967289LL;
  if ( (unsigned int)psci_validate_cpu_on() != 0 )
    return 4294967294LL;
  if ( MEMORY[0x9400E988] == 0
    || (v4 = *(__int64 (__fastcall **)(unsigned __int64, __int64))(MEMORY[0x9400E988] + 40LL)) == nullptr )
  {
    v5 = 293;
    v6 = "psci_spd_pm && psci_spd_pm->svc_migrate";
    goto LABEL_13;
  }
  result = v4(_ReadStatusReg(MPIDR_EL1), a1);
  if ( (_DWORD)result != -6 && (_DWORD)result != 0 )
  {
    v5 = 296;
    v6 = "rc == PSCI_E_SUCCESS || rc == PSCI_E_INTERN_FAIL";
LABEL_13:
    assert_fail("psci_migrate", "lib/psci/psci_main.c", v5, v6);
  }
  return result;
}

/* ===== psci_migrate_info_type @ 0x940039E4 size 24 ===== */
__int64 psci_migrate_info_type()
{
  return psci_spd_migrate_info();
}

/* ===== psci_migrate_info_up_cpu @ 0x940039FC size 40 ===== */
__int64 psci_migrate_info_up_cpu()
{
  bool v0; // cc
  __int64 result; // x0
  __int64 v2; // [xsp+18h] [xbp+18h]

  v0 = (unsigned int)psci_spd_migrate_info() > 1;
  result = -2;
  if ( !v0 )
    return v2;
  return result;
}

/* ===== psci_node_hw_state @ 0x94003A24 size 164 ===== */
__int64 __fastcall psci_node_hw_state(__int64 a1, unsigned int a2)
{
  __int64 (__fastcall *v3)(__int64); // x2
  __int64 v4; // x2
  const char *v5; // x3
  __int64 result; // x0

  if ( (unsigned int)psci_validate_cpu_on() != 0 || a2 > 1 )
    return 4294967294LL;
  v3 = *(__int64 (__fastcall **)(__int64))(MEMORY[0x9400E980] + 112LL);
  if ( v3 == nullptr )
  {
    v4 = 342;
    v5 = "psci_plat_pm_ops->get_node_hw_state";
    goto LABEL_8;
  }
  result = v3(a1);
  if ( (unsigned int)(result + 1) > 3 )
  {
    if ( (_DWORD)result != -2 )
    {
      v4 = 345;
      v5 = "(rc >= HW_ON && rc <= HW_STANDBY) || rc == PSCI_E_NOT_SUPPORTED || rc == PSCI_E_INVALID_PARAMS";
LABEL_8:
      assert_fail("psci_node_hw_state", "lib/psci/psci_main.c", v4, v5);
    }
    return 4294967294LL;
  }
  return result;
}

/* ===== psci_validate_fid @ 0x94003AC8 size 84 ===== */
__int64 __fastcall psci_validate_fid(unsigned __int64 a1)
{
  int v1; // w1

  v1 = MEMORY[0x9400E990];
  if ( (a1 & 0x40000000) != 0 )
    v1 = MEMORY[0x9400E990] & 0x360BA;
  if ( ((a1 >> 24) & 0x3F) != 4 || BYTE2(a1) != 0 || (a1 & 0x80000000) == 0LL || (a1 & 0xFFE0) != 0 )
    return 0xFFFFFFFFLL;
  if ( (v1 & ((unsigned int)a1 >> 31 << a1)) != 0 )
    return 0;
  return 0xFFFFFFFFLL;
}

/* ===== psci_smc_handler @ 0x94003B1C size 284 ===== */
__int64 __fastcall psci_smc_handler(
        int a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        char a8)
{
  __int64 v10; // x4
  __int64 v11; // x1
  __int64 v12; // x2
  __int64 result; // x0

  v10 = 0xFFFFFFFFLL;
  v11 = a3;
  v12 = a4;
  if ( (a8 & 1) == 0 || ((1 << a1) & MEMORY[0x9400E990]) == 0 )
    return v10;
  if ( (a1 & 0x40000000) == 0 )
  {
    a2 = (unsigned int)a2;
    v11 = (unsigned int)v11;
    v12 = (unsigned int)a4;
    switch ( a1 )
    {
      case -2080374784:
        return 0x10000;
      case -2080374783:
        return (int)psci_cpu_suspend(a2, v11, v12);
      case -2080374782:
        return (int)psci_cpu_off();
      case -2080374781:
        return (int)psci_cpu_on(a2, v11, v12);
      case -2080374780:
        return (int)psci_affinity_info(a2, v11);
      case -2080374779:
        return (int)psci_migrate(a2);
      case -2080374778:
        return (int)psci_migrate_info_type();
      case -2080374777:
        goto LABEL_16;
      case -2080374776:
        a2 = psci_system_off((unsigned int)a2, (unsigned int)v11, (unsigned int)a4);
        goto LABEL_9;
      case -2080374775:
LABEL_9:
        a2 = psci_system_reset(a2, v11, v12);
        break;
      case -2080374774:
        return (int)psci_validate_fid(a2);
      case -2080374771:
        return (int)psci_node_hw_state(a2, v11);
      case -2080374770:
        return (int)psci_system_suspend(a2, v11);
      case -2080374768:
        goto LABEL_20;
      case -2080374767:
        goto LABEL_21;
      default:
        return 0xFFFFFFFFLL;
    }
    return (int)psci_validate_fid(a2);
  }
  switch ( a1 )
  {
    case -1006632959:
      return (int)psci_cpu_suspend(a2, v11, v12);
    case -1006632957:
      return (int)psci_cpu_on(a2, v11, v12);
    case -1006632956:
      return (int)psci_affinity_info(a2, v11);
    case -1006632955:
      return (int)psci_migrate(a2);
    case -1006632953:
LABEL_16:
      result = psci_migrate_info_up_cpu();
      break;
    case -1006632947:
      return (int)psci_node_hw_state(a2, v11);
    case -1006632946:
      return (int)psci_system_suspend(a2, v11);
    case -1006632944:
LABEL_20:
      result = psci_stat_residency(a2, v11, v12);
      break;
    case -1006632943:
LABEL_21:
      result = psci_stat_count(a2, v11, v12);
      break;
    default:
      return 0xFFFFFFFFLL;
  }
  return result;
}

/* ===== psci_timer_init @ 0x94003C38 size 28 ===== */
__int64 __fastcall psci_timer_init(__int64 a1)
{
  __int64 result; // x0
  __int64 v2; // x6
  __int64 v3; // x0
  __int64 v4; // x0
  unsigned __int64 v5; // x6
  unsigned __int64 v6; // x4
  unsigned __int64 i; // x5
  unsigned __int64 v8; // x5
  unsigned __int64 v9; // x6

  _WriteStatusReg(CNTFRQ_EL0, (unsigned int)get_uart_clock(a1));
  result = *(_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 16);
  if ( result == 0 )
  {
    result = get_cpu_ops();
    if ( result == 0 )
    {
      if ( get_pc() != 0 )
      {
        v3 = ((__int64 (*)(void))puts)();
        v4 = puts(v3);
        puts(v4);
        if ( (v5 & 0xFFFFFFFFFFFF0000LL) == 0 )
        {
          v6 = v5;
          for ( i = 10000; i != 0; i = v8 / v9 )
            putc(v6 / i + 48);
        }
      }
      while ( 1 )
        ;
    }
    *(_QWORD *)(v2 + 16) = result;
  }
  return result;
}

/* ===== psci_setup @ 0x94003C54 size 892 ===== */
__int64 __fastcall psci_setup(_QWORD *a1)
{
  __int64 v2; // x0
  const char *v3; // x0
  __int64 v4; // x2
  const char *v5; // x3
  int v6; // w21
  unsigned int v7; // w20
  unsigned __int64 v8; // x5
  int v9; // w24
  unsigned int i; // w19
  unsigned __int64 v11; // x6
  int v12; // w28
  unsigned int v13; // w23
  __int64 v14; // x4
  unsigned int v15; // w2
  unsigned __int64 v16; // x1
  __int64 v17; // x0
  int v18; // w20
  unsigned int v19; // w19
  __int64 v20; // x0
  unsigned int v21; // w0
  int v22; // w2
  unsigned __int64 v24; // [xsp+60h] [xbp+60h]
  __int64 v25; // [xsp+68h] [xbp+68h]
  unsigned __int64 v26; // [xsp+70h] [xbp+70h]
  unsigned int v27; // [xsp+88h] [xbp+88h] BYREF

  if ( a1 == nullptr || *a1 != 1048838 || (v2 = a1[1]) == 0 )
  {
    v3 = "psci_setup";
    v4 = 213;
    v5 = "VERIFY_PSCI_LIB_ARGS_V1(lib_args)";
    goto LABEL_12;
  }
  psci_timer_init(v2);
  v6 = 1;
  v7 = 0;
  v8 = get_power_domain_tree();
  v9 = 1;
  i = 0;
  v11 = 0x94014010;
  while ( 1 )
  {
    v14 = v6 + v7;
    v6 = 0;
    v13 = 0;
    while ( v7 != (_DWORD)v14 )
    {
      if ( v7 == 2 )
      {
        v3 = "populate_power_domain_tree";
        v4 = 160;
        v5 = "parent_node_index <= PSCI_NUM_NON_CPU_PWR_DOMAINS";
        goto LABEL_12;
      }
      v12 = *(unsigned __int8 *)(v8 + v7);
      for ( i = v13; i < v12 + v13; ++i )
      {
        v15 = v7 - 1;
        if ( v9 != 0 )
        {
          v16 = v11 + 16LL * i;
          *(_BYTE *)(v16 + 14) = i;
          *(_BYTE *)(v16 + 13) = 1;
          *(_DWORD *)(v16 + 8) = v15;
          *(_BYTE *)(v16 + 12) = 2;
        }
        else
        {
          *(_DWORD *)(0x9400E940 + 16LL * i + 8) = v15;
          *(_QWORD *)(0x9400E940 + 16LL * i) = -1;
          v25 = v14;
          v26 = v8;
          v24 = v11;
          v17 = get_cpu_context_ptr(i);
          *(_DWORD *)(v17 + 88) = 1;
          *(_BYTE *)(v17 + 92) = 2;
          *(_BYTE *)(v17 + 93) = 2;
          dcache_clean_invalidate(v17 + 88, 8);
          cm_set_context_by_index(i, 0x9400D1F0 + 1056LL * i, 1u);
          v11 = v24;
          v8 = v26;
          v14 = v25;
        }
      }
      v6 += v12;
      ++v7;
      v13 = i;
    }
    if ( v9 == 0 )
      break;
    v9 = 0;
  }
  if ( i != 4 )
  {
    v3 = "populate_power_domain_tree";
    v4 = 183;
    v5 = "j == PLATFORM_CORE_COUNT";
    goto LABEL_12;
  }
  v18 = 0;
  v19 = 0;
  while ( 1 )
  {
    psci_get_parent_pwr_lvl(v19, 1u, &v27);
    v20 = v27;
    if ( v27 != v18 )
      *(_DWORD *)(0x94014010 + 16LL * v27) = v19;
    ++v19;
    ++*(_DWORD *)(0x94014010 + 16LL * (unsigned int)v20 + 4);
    if ( v19 == 4 )
      break;
    v18 = v20;
  }
  v21 = get_cpu_id(v20);
  *(_QWORD *)(0x9400E940 + 16LL * v21) = _ReadStatusReg(MPIDR_EL1) & 0xFF00FFFFFFLL;
  psci_clear_aff_info();
  psci_do_state_coordination_finish(1u);
  sprd_plat_pm_ops_init(a1[1], (_QWORD *)0x9400E980LL);
  if ( MEMORY[0x9400E980] == 0 )
  {
    v3 = "psci_setup";
    v4 = 240;
    v5 = "psci_plat_pm_ops";
LABEL_12:
    assert_fail(v3, "lib/psci/psci_setup.c", v4, v5);
  }
  dcache_clean_invalidate(0x9400E980, 8);
  MEMORY[0x9400E990] = 1041;
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 16LL) != 0 )
    MEMORY[0x9400E990] = 1045;
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 8LL) != 0 && *(_QWORD *)(MEMORY[0x9400E980] + 32LL) != 0 )
    MEMORY[0x9400E990] |= 8u;
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 24LL) != 0 && *(_QWORD *)(MEMORY[0x9400E980] + 40LL) != 0 )
  {
    v22 = MEMORY[0x9400E990];
    MEMORY[0x9400E990] |= 2u;
    if ( *(_QWORD *)(MEMORY[0x9400E980] + 88LL) != 0 )
      MEMORY[0x9400E990] = v22 | 0x4002;
  }
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 56LL) != 0 )
    MEMORY[0x9400E990] |= 0x100u;
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 64LL) != 0 )
    MEMORY[0x9400E990] |= 0x200u;
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 112LL) != 0 )
    MEMORY[0x9400E990] |= 0x2000u;
  MEMORY[0x9400E990] |= 0x30000u;
  return 0;
}

/* ===== psci_system_off @ 0x94003FD0 size 104 ===== */
__int64 psci_system_off()
{
  void (*v0)(void); // x0
  __int64 v1; // x0
  __int64 v2; // x1
  __int64 v3; // x2

  nullsub_8();
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 56LL) == 0 )
    assert_fail("psci_system_off", "lib/psci/psci_system_off.c", 42, "psci_plat_pm_ops->system_off");
  if ( MEMORY[0x9400E988] != 0 )
  {
    v0 = *(void (**)(void))(MEMORY[0x9400E988] + 56LL);
    if ( v0 != nullptr )
      v0();
  }
  v1 = (*(__int64 (**)(void))(MEMORY[0x9400E980] + 56LL))();
  return psci_system_reset(v1, v2, v3);
}

/* ===== psci_system_reset @ 0x94004038 size 104 ===== */
__int64 psci_system_reset()
{
  void (*v0)(void); // x0
  __int64 v1; // x0

  nullsub_8();
  if ( *(_QWORD *)(MEMORY[0x9400E980] + 64LL) == 0 )
    assert_fail("psci_system_reset", "lib/psci/psci_system_off.c", 59, "psci_plat_pm_ops->system_reset");
  if ( MEMORY[0x9400E988] != 0 )
  {
    v0 = *(void (**)(void))(MEMORY[0x9400E988] + 64LL);
    if ( v0 != nullptr )
      v0();
  }
  v1 = (*(__int64 (**)(void))(MEMORY[0x9400E980] + 64LL))();
  return bakery_lock_get(v1);
}

/* ===== bakery_lock_get @ 0x940040A0 size 296 ===== */
__int64 __fastcall bakery_lock_get(__int64 a1)
{
  __int64 result; // x0
  const char *v3; // x0
  __int64 v4; // x2
  const char *v5; // x3
  __int64 v6; // x3
  unsigned int v7; // w1
  unsigned int v8; // w2
  unsigned __int16 v9; // w4
  unsigned int v10; // w4
  unsigned int v11; // w1
  unsigned int v12; // w4
  unsigned int i; // w1
  unsigned int v14; // w2
  unsigned int v15; // w2

  result = get_cpu_id(a1);
  if ( a1 == 0 )
  {
    v3 = "bakery_lock_get";
    v4 = 123;
    v5 = "bakery";
    goto LABEL_5;
  }
  if ( (unsigned int)result > 3 )
  {
    v3 = "bakery_lock_get";
    v4 = 123;
    v5 = "me < BAKERY_LOCK_MAX_CPUS";
    goto LABEL_5;
  }
  v6 = 2LL * (unsigned int)result;
  v7 = *(_WORD *)(a1 + v6) >> 1;
  if ( *(_WORD *)(a1 + v6) >> 1 != 0 )
  {
    v3 = "bakery_get_ticket";
    v4 = 73;
    v5 = "!bakery_ticket_number(bakery->lock_data[me])";
LABEL_5:
    assert_fail(v3, "lib/locks/bakery/bakery_lock_coherent.c", v4, v5);
  }
  *(_WORD *)(a1 + 2LL * (unsigned int)result) = 1;
  v8 = v7;
  do
  {
    v9 = *(_WORD *)(a1 + 2LL * v8++);
    v10 = v9 >> 1;
    if ( v7 < v10 )
      v7 = v10;
  }
  while ( v8 != 4 );
  v11 = v7 + 1;
  v12 = result | (v11 << 8);
  *(_WORD *)(a1 + 2LL * (unsigned int)result) = 2 * (v11 & 0x7FFF);
  for ( i = 0; i != 4; ++i )
  {
    if ( (_DWORD)result != i )
    {
      do
        v14 = *(unsigned __int16 *)(a1 + 2LL * i);
      while ( (v14 & 1) != 0 );
      v15 = v14 >> 1;
      if ( v15 != 0 && (i | (v15 << 8)) < v12 )
      {
        do
          __wfe();
        while ( v15 == *(_WORD *)(a1 + 2LL * i) >> 1 );
      }
    }
  }
  return result;
}

/* ===== bakery_lock_release @ 0x940041C8 size 168 ===== */
__int64 __fastcall bakery_lock_release(__int64 a1)
{
  unsigned int v2; // w0
  __int64 v3; // x2
  char *v4; // x3
  __int64 result; // x0

  v2 = get_cpu_id(a1);
  if ( a1 == 0 )
  {
    v3 = 169;
    v4 = "bakery";
    goto LABEL_5;
  }
  if ( v2 > 3 )
  {
    v3 = 169;
    v4 = "me < BAKERY_LOCK_MAX_CPUS";
    goto LABEL_5;
  }
  result = 2LL * v2;
  if ( *(_WORD *)(a1 + result) >> 1 == 0 )
  {
    v3 = 170;
    v4 = "bakery_ticket_number(bakery->lock_data[me])";
LABEL_5:
    assert_fail("bakery_lock_release", "lib/locks/bakery/bakery_lock_coherent.c", v3, v4);
  }
  *(_WORD *)(a1 + result) = 0;
  __dsb(0xFu);
  __sev();
  return result;
}

/* ===== psci_get_stat_idx @ 0x94004270 size 140 ===== */
__int64 __fastcall psci_get_stat_idx(unsigned __int8 a1)
{
  int v1; // w3
  __int64 (__fastcall *v2)(_QWORD); // x2
  __int64 result; // x0
  __int64 v4; // x2
  const char *v5; // x3

  v1 = a1;
  v2 = *(__int64 (__fastcall **)(_QWORD))(MEMORY[0x9400E980] + 96LL);
  if ( v2 != nullptr )
  {
    result = v2(a1);
    if ( (unsigned int)result > 1 )
    {
      v4 = 105;
      v5 = "(idx >= 0) && (idx < PLAT_MAX_PWR_LVL_STATES)";
LABEL_7:
      assert_fail("get_stat_idx", "lib/psci/psci_stat.c", v4, v5);
    }
  }
  else if ( a1 == 1 )
  {
    return 0;
  }
  else
  {
    result = 1;
    if ( v1 != 2 )
    {
      v4 = 100;
      v5 = "is_local_state_off(local_state)";
      goto LABEL_7;
    }
  }
  return result;
}

/* ===== pmf_capture_timestamp @ 0x940042FC size 80 ===== */
__int64 __fastcall pmf_capture_timestamp(unsigned int a1, __int64 a2)
{
  if ( (unsigned __int8)a1 > 1u )
    assert_fail(
      "pmf_capture_timestamp_psci_svc",
      "lib/psci/psci_stat.c",
      67,
      "(tid & PMF_TID_MASK) < (ARRAY_SIZE(pmf_ts_mem_psci_svc))");
  return pmf_set_timestamp(0x94010340, a1, a2);
}

/* ===== pmf_get_timestamp @ 0x9400434C size 88 ===== */
__int64 __fastcall pmf_get_timestamp(unsigned int a1, unsigned int a2, unsigned int a3)
{
  if ( (unsigned __int8)a1 > 1u )
    assert_fail(
      "pmf_get_timestamp_by_index_psci_svc",
      "lib/psci/psci_stat.c",
      67,
      "(tid & PMF_TID_MASK) < (ARRAY_SIZE(pmf_ts_mem_psci_svc))");
  return pmf_get_timestamp_by_index(0x94010340, a1, a2, a3);
}

/* ===== psci_stats_update_pwr_down @ 0x940043A4 size 156 ===== */
__int64 __fastcall psci_stats_update_pwr_down(__int64 a1, __int64 a2)
{
  unsigned int v2; // w19
  __int64 result; // x0
  __int64 v4; // x2
  const char *v5; // x3

  v2 = a1;
  result = get_cpu_id(a1);
  if ( v2 > 1 )
  {
    v4 = 125;
    v5 = "end_pwrlvl <= PLAT_MAX_PWR_LVL";
    goto LABEL_5;
  }
  if ( a2 == 0 )
  {
    v4 = 126;
    v5 = "state_info";
LABEL_5:
    assert_fail("psci_stats_update_pwr_down", "lib/psci/psci_stat.c", v4, v5);
  }
  if ( v2 != 0 && *(_BYTE *)(a2 + 1) != 0 )
    *((_DWORD *)&qword_9400C080 + *(int *)(0x9400E940LL + 16LL * (int)result + 8)) = result;
  return result;
}

/* ===== psci_stats_update_pwr_up @ 0x94004440 size 604 ===== */
_QWORD *__fastcall psci_stats_update_pwr_up(__int64 a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned int v3; // w24
  __int64 v6; // x20
  __int64 v7; // x2
  const char *v8; // x3
  _QWORD *result; // x0
  _QWORD *v10; // x23
  unsigned __int64 v11; // x21
  int v12; // w0
  unsigned __int64 v13; // x3
  _QWORD *v14; // x2
  unsigned __int8 *v15; // x23
  __int64 v16; // x3
  int v17; // w20
  int v18; // w19
  unsigned __int64 v19; // x4
  unsigned __int8 v20; // w28
  unsigned int v21; // w1
  __int64 v22; // x0
  unsigned __int64 v23; // [xsp+68h] [xbp+68h]
  __int64 v24; // [xsp+70h] [xbp+70h]
  unsigned __int64 v25; // [xsp+78h] [xbp+78h]

  v3 = a1;
  v6 = (int)get_cpu_id(a1);
  if ( v3 > 1 )
  {
    v7 = 162;
    v8 = "end_pwrlvl <= PLAT_MAX_PWR_LVL";
    goto LABEL_5;
  }
  if ( a2 == nullptr )
  {
    v7 = 163;
    v8 = "state_info";
    goto LABEL_5;
  }
  if ( MEMORY[0x9400E998] == 0 )
  {
    MEMORY[0x9400E998] = _ReadStatusReg(CNTFRQ_EL0) / 0xF4240;
    if ( MEMORY[0x9400E998] == 0 )
    {
      v7 = 170;
      v8 = "residency_div";
      goto LABEL_5;
    }
  }
  result = (_QWORD *)pmf_get_timestamp(0, v6, a3);
  v10 = result;
  if ( result != nullptr )
  {
    v11 = pmf_get_timestamp(1u, v6, a3);
    v12 = psci_get_stat_idx(*a2);
    __SET_PAIR__(v13, v13, __PAIR128__(v11, v11) - __PAIR128__((unsigned __int64)v10, (unsigned __int64)v10));
    v14 = (_QWORD *)(0x9400E290LL + 16 * (2 * v6 + v12));
    v15 = a2;
    *v14 += v13 / MEMORY[0x9400E998];
    v16 = v3 + 1;
    ++v14[1];
    result = (_QWORD *)0x9400E940LL;
    v17 = *(_DWORD *)(0x9400E940LL + 16 * v6 + 8);
    v18 = 1;
    v19 = 0x94014010;
    while ( 1 )
    {
      if ( v18 == (_DWORD)v16 )
        return result;
      v20 = v15[1];
      if ( v20 == 0 )
        return result;
      v21 = *((_DWORD *)&qword_9400C080 + v17);
      if ( v21 == -1 )
        break;
      v24 = v16;
      v23 = v19;
      v22 = pmf_get_timestamp(0, v21, a3);
      *((_DWORD *)&qword_9400C080 + v17) = -1;
      v25 = v22;
      result = (_QWORD *)(0x9400E270LL + 16 * (2LL * v17 + (int)psci_get_stat_idx(v20)));
      v19 = v23;
      *result += (v11 - (v25 + (v11 < v25))) / MEMORY[0x9400E998];
      v17 = *(_DWORD *)(v23 + 16LL * v17 + 8);
      ++v18;
      ++result[1];
      ++v15;
      v16 = v24;
    }
    v7 = 208;
    v8 = "last_cpu_in_non_cpu_pd[parent_idx] != -1";
LABEL_5:
    assert_fail("psci_stats_update_pwr_up", "lib/psci/psci_stat.c", v7, v8);
  }
  return result;
}

/* ===== psci_stat_get @ 0x9400469C size 344 ===== */
__int64 __fastcall psci_stat_get(__int64 a1, __int64 a2, _QWORD *a3)
{
  int v5; // w0
  __int64 v6; // x23
  __int64 (__fastcall *v8)(__int64, __int64, unsigned __int8 *); // x3
  int v9; // w0
  int v10; // w0
  int v11; // w19
  __int64 v12; // x0
  int v13; // w0
  int v14; // w1
  int v15; // w23
  _QWORD *v16; // x2
  __int64 v17; // x23
  __int64 v18; // x1
  unsigned __int8 v20[8]; // [xsp+58h] [xbp+58h] BYREF

  *(_WORD *)v20 = 0;
  v5 = psci_validate_affinity(a1);
  v6 = v5;
  if ( v5 == -1 )
    return 4294967294LL;
  v8 = *(__int64 (__fastcall **)(__int64, __int64, unsigned __int8 *))(MEMORY[0x9400E980] + 104LL);
  v9 = v8 != nullptr ? v8(a1, a2, v20) : psci_validate_power_state(a2);
  if ( v9 != 0 )
    return 4294967294LL;
  v10 = psci_find_target_suspend_lvl(v20);
  v11 = v10;
  if ( v10 == 2 )
  {
    v12 = printf_impl("ERROR:   Invalid target power level for PSCI statistics operation\n");
    panic(v12);
  }
  v13 = psci_get_stat_idx(v20[v10]);
  if ( v11 <= 0 )
  {
    v17 = 16 * (2 * v6 + v13);
    v18 = *(_QWORD *)(0x9400E290LL + v17);
    a3[1] = *(_QWORD *)(0x9400E290LL + v17 + 8);
    *a3 = v18;
    return 0;
  }
  else
  {
    v14 = 1;
    v15 = *(_DWORD *)(0x9400E940LL + 16 * v6 + 8);
    while ( v14 != v11 )
    {
      ++v14;
      v15 = *(_DWORD *)(0x94014010LL + 16LL * v15 + 8);
    }
    v16 = (_QWORD *)(0x9400E270LL + 16 * (2LL * v15 + v13));
    *a3 = *v16;
    a3[1] = v16[1];
    return 0;
  }
}

/* ===== psci_stat_residency @ 0x940047F4 size 36 ===== */
__int64 __fastcall psci_stat_residency(__int64 a1, __int64 a2)
{
  bool v2; // zf
  __int64 result; // x0
  __int64 v4; // [xsp+10h] [xbp+10h] BYREF

  v2 = (unsigned int)psci_stat_get(a1, a2, &v4) == 0;
  result = v4;
  if ( !v2 )
    return 0;
  return result;
}

/* ===== psci_stat_count @ 0x94004818 size 36 ===== */
__int64 __fastcall psci_stat_count(__int64 a1, __int64 a2)
{
  bool v2; // zf
  __int64 result; // x0
  _QWORD v4[2]; // [xsp+10h] [xbp+10h] BYREF

  v2 = (unsigned int)psci_stat_get(a1, a2, v4) == 0;
  result = v4[1];
  if ( !v2 )
    return 0;
  return result;
}

/* ===== calc_ts_addr @ 0x9400483C size 180 ===== */
__int64 __fastcall calc_ts_addr(unsigned __int64 a1, unsigned __int8 a2, unsigned int a3)
{
  __int64 v3; // x2
  const char *v4; // x3

  if ( a3 > 3 )
  {
    v3 = 220;
    v4 = "cpuid < PLATFORM_CORE_COUNT";
    goto LABEL_5;
  }
  if ( a1 < 0x94010340 )
  {
    v3 = 221;
    v4 = "base_addr >= PMF_TIMESTAMP_ARRAY_START";
    goto LABEL_5;
  }
  if ( a1 >= 0x94010380 - 8 * (unsigned __int64)a2 )
  {
    v3 = 224;
    v4 = "base_addr < ((PMF_TIMESTAMP_ARRAY_START + PMF_PERCPU_TIMESTAMP_SIZE) - ((tid & PMF_TID_MASK) * sizeof(unsigned long long)))";
LABEL_5:
    assert_fail("calc_ts_addr", "lib/pmf/pmf_main.c", v3, v4);
  }
  return a1 + 8LL * a2 + 0x40LL * a3;
}

/* ===== pmf_set_timestamp @ 0x940048F0 size 60 ===== */
_QWORD *__fastcall pmf_set_timestamp(unsigned __int64 a1, unsigned __int8 a2, __int64 a3)
{
  unsigned int v5; // w0
  _QWORD *result; // x0

  v5 = get_cpu_id(a1);
  result = (_QWORD *)calc_ts_addr(a1, a2, v5);
  *result = a3;
  return result;
}

/* ===== pmf_get_timestamp_by_index @ 0x9400492C size 96 ===== */
__int64 __fastcall pmf_get_timestamp_by_index(unsigned __int64 a1, unsigned __int8 a2, unsigned int a3, char a4)
{
  __int64 v4; // x0
  __int64 v5; // x19

  if ( a3 > 3 )
    assert_fail(&loc_9400A708, "lib/pmf/pmf_main.c", 272, "cpuid < PLATFORM_CORE_COUNT");
  v4 = calc_ts_addr(a1, a2, a3);
  v5 = v4;
  if ( (a4 & 1) != 0 )
    dcache_invalidate(v4, 8);
  return *(_QWORD *)v5;
}

/* ===== trusty_context_switch @ 0x9400498C size 304 ===== */
__int64 __usercall trusty_context_switch@<X0>(
        __int64 a1@<X0>,
        __int64 a2@<X1>,
        __int64 a3@<X2>,
        __int64 a4@<X3>,
        __int64 a5@<X4>,
        __int64 a6@<X8>)
{
  unsigned int v6; // w19
  __int64 v8; // x20
  __int64 v9; // x2
  const char *v10; // x3
  __int64 v11; // x0
  __int64 v12; // x0

  v6 = a1;
  v8 = 0x9400E9A0 + 1632LL * (unsigned int)get_cpu_id(a1);
  if ( *(_DWORD *)(v8 + 1064) == v6 )
  {
    v9 = 87;
    v10 = "ctx->saved_security_state != security_state";
    goto LABEL_5;
  }
  v11 = cm_get_context(v6);
  fpregs_context_save(v11 + 528);
  cm_el1_sysregs_context_save(v6);
  *(_DWORD *)(v8 + 1064) = v6;
  setup_eret_context(v8 + 1056, a2, a3, a4, a5);
  if ( *(_DWORD *)(v8 + 1064) != (v6 == 0) )
  {
    v9 = 97;
    v10 = "ctx->saved_security_state == !security_state";
LABEL_5:
    assert_fail("trusty_context_switch", "services/spd/trusty/trusty.c", v9, v10);
  }
  cm_el1_sysregs_context_restore(v6);
  v12 = cm_get_context(v6);
  fpregs_context_restore(v12 + 528);
  cm_set_next_eret_context(v6);
  return a6;
}

/* ===== trusty_fiq_handler @ 0x94004ABC size 228 ===== */
_QWORD *__fastcall trusty_fiq_handler(__int64 a1, char a2, _QWORD *a3)
{
  __int64 v4; // x19
  __int64 v5; // x19
  __int64 v6; // x1
  unsigned int v7; // w2
  __int64 v10; // [xsp+40h] [xbp+40h] BYREF

  v4 = (unsigned int)get_cpu_id(a1);
  if ( (a2 & 1) == 0 )
    assert_fail("trusty_fiq_handler", "services/spd/trusty/trusty.c", 116, "!is_caller_secure(flags)");
  trusty_context_switch(1, -1140850684, 0, 0, 0, (__int64)&v10);
  if ( v10 == 0 )
  {
    v5 = 0x9400E9A0LL + 1632 * v4;
    if ( *(_DWORD *)(v5 + 1068) == 0 )
    {
      *(_DWORD *)(v5 + 1068) = 1;
      memcpy_simple(v5 + 1120, a3, 256);
      *(_QWORD *)(v5 + 1096) = a3[35];
      *(_QWORD *)(v5 + 1104) = a3[34];
      *(_QWORD *)(v5 + 1112) = a3[42];
      v6 = *(_QWORD *)(v5 + 1072);
      v7 = *(_DWORD *)(v5 + 1080);
      a3[42] = *(_QWORD *)(v5 + 1088);
      cm_set_elr_spsr_el3(1u, v6, v7);
    }
  }
  return a3;
}

/* ===== trusty_smc_handler @ 0x94004BA0 size 48 ===== */
__int64 trusty_smc_handler()
{
  char v1; // [xsp+10h] [xbp+10h] BYREF

  return trusty_context_switch(1, -1140850680, 0, 0, 0, (__int64)&v1);
}

/* ===== trusty_smc_thunk @ 0x94004BD0 size 4 ===== */
// attributes: thunk
__int64 trusty_smc_thunk()
{
  return trusty_smc_handler();
}

/* ===== trusty_fiq_exit_handler @ 0x94004BD4 size 48 ===== */
__int64 trusty_fiq_exit_handler()
{
  char v1; // [xsp+10h] [xbp+10h] BYREF

  return trusty_context_switch(1, -1140850681, 0, 0, 0, (__int64)&v1);
}

/* ===== trusty_fiq_exit_thunk @ 0x94004C04 size 4 ===== */
// attributes: thunk
__int64 trusty_fiq_exit_thunk()
{
  return trusty_fiq_exit_handler();
}

/* ===== trusty_smc_exit @ 0x94004C08 size 24 ===== */
__int64 trusty_smc_exit()
{
  trusty_fiq_exit_handler();
  return 0;
}

/* ===== trusty_setup @ 0x94004C20 size 172 ===== */
__int64 trusty_setup()
{
  unsigned __int64 v0; // x0
  int v1; // w2
  int v2; // w1
  unsigned int v3; // w19
  int v4; // w1

  v0 = bl31_get_next_image_ep(0);
  if ( v0 != 0 )
  {
    v1 = *(unsigned __int8 *)(*(_QWORD *)(v0 + 8) + 3LL);
    *(_BYTE *)v0 = 1;
    *(_BYTE *)(v0 + 1) = 1;
    *(_WORD *)(v0 + 2) = 88;
    *(_DWORD *)(v0 + 4) = 4;
    v2 = 965;
    if ( v1 == 234 )
      v2 = 467;
    *(_DWORD *)(v0 + 16) = v2;
    v3 = 0;
    bl31_register_runtime_callback(trusty_init);
    psci_register_spd_pm_hook((__int64)&qword_9400A8B8);
    v4 = interrupt_register_handler(0, (__int64)trusty_fiq_handler, 2u);
    if ( v4 != 0 )
      printf_impl("ERROR:   trusty: failed to register fiq handler, ret = %d\n", v4);
  }
  else
  {
    return (unsigned int)-1;
  }
  return v3;
}

/* ===== trusty_init @ 0x94004CCC size 264 ===== */
__int64 __fastcall trusty_init(__int64 a1)
{
  unsigned int v1; // w0
  __int64 v2; // x19
  int v3; // w22
  BOOL v4; // w21
  unsigned __int64 v5; // x20
  __int64 v7; // [xsp+30h] [xbp+30h] BYREF

  v1 = get_cpu_id(a1);
  v2 = 0x9400E9A0 + 1632LL * v1;
  v3 = get_cpu_id(v1);
  v4 = (*(_QWORD *)(v2 + 272) & 0x10LL) != 0;
  v5 = bl31_get_next_image_ep(0);
  if ( v5 == 0 )
    assert_fail("trusty_init", "services/spd/trusty/trusty.c", 250, "ep_info");
  cm_el1_sysregs_context_save(1u);
  cm_set_context(v2, 0);
  cm_init_context(v5);
  if ( v3 != 0 && v4 )
    cm_set_elr_el3(0, *(_QWORD *)(v5 + 8) + 32LL);
  cm_el1_sysregs_context_restore(0);
  cm_set_next_eret_context(0);
  *(_DWORD *)(v2 + 1064) = -1;
  setup_panic_context(&v7, v2 + 1056, v2 + 1632);
  setup_eret_context(v2 + 1056, 0, 0, 0, 0);
  cm_el1_sysregs_context_restore(1u);
  cm_set_next_eret_context(1u);
  return 0;
}

/* ===== trusty_std_svc_setup @ 0x94004DD4 size 56 ===== */
__int64 __fastcall trusty_std_svc_setup(__int64 a1)
{
  if ( *(_QWORD *)(0x9400E9A0 + 1632LL * (unsigned int)get_cpu_id(a1) + 1056) != 0 )
    return trusty_smc_handler();
  else
    return trusty_init(0);
}

/* ===== trusty_smc_handler_main @ 0x94004E0C size 468 ===== */
__int64 __fastcall trusty_smc_handler_main(
        unsigned int a1,
        unsigned __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 *a7,
        char a8)
{
  __int64 v9; // x0
  _QWORD *v11; // x9
  __int64 v12; // x0
  _QWORD *v13; // x0
  __int64 v14; // x2
  __int64 v15; // x1
  unsigned int v16; // w0
  __int64 v17; // x20
  __int64 v18; // x0
  __int64 v19; // x1
  unsigned int v20; // w2
  _QWORD v21[4]; // [xsp+20h] [xbp+20h] BYREF

  if ( (a8 & 1) == 0 )
  {
    if ( a1 == 1006632960 )
    {
      trusty_context_switch(a8 & 1, a2, a8 & 1, a8 & 1, a8 & 1, (__int64)v21);
      a7[3] = v21[3];
      a7[2] = v21[2];
      a7[1] = v21[1];
LABEL_17:
      v9 = v21[0];
      goto LABEL_18;
    }
    v9 = 0xFFFFFFFFLL;
LABEL_18:
    *a7 = v9;
    return (__int64)a7;
  }
  switch ( a1 )
  {
    case 0xFC000005:
      if ( a2 > 3 )
      {
        printf_impl("ERROR:   %s: cpu %ld >= %d\n", "trusty_set_fiq_handler", a2, 4);
        return -2;
      }
      v11 = (_QWORD *)(0x9400E9A0 + 1632 * a2);
      v12 = a7[34];
      v11[134] = a3;
      v11[135] = v12;
      v11[136] = a4;
      *a7 = 0;
      break;
    case 0xFC000006:
      v13 = (_QWORD *)(0x9400E9A0 + 1632LL * (unsigned int)get_cpu_id(4227858438LL));
      v14 = v13[139];
      a7[2] = v13[171];
      v15 = v13[138];
      a7[3] = v14;
      a7[1] = v15;
      v9 = v13[137];
      goto LABEL_18;
    case 0xBC000001:
      v16 = get_cpu_id(3154116609LL);
      v17 = 0x9400E9A0 + 1632LL * v16;
      if ( *(_DWORD *)(v17 + 1068) == 0 )
      {
        v9 = -2;
        goto LABEL_18;
      }
      trusty_context_switch(1, -1140850687, 0, 0, 0, (__int64)v21);
      memcpy_simple(a7, v17 + 1120, 256);
      v18 = *(_QWORD *)(v17 + 1112);
      *(_DWORD *)(v17 + 1068) = 0;
      v19 = *(_QWORD *)(v17 + 1096);
      v20 = *(_DWORD *)(v17 + 1104);
      a7[42] = v18;
      cm_set_elr_spsr_el3(1u, v19, v20);
      break;
    default:
      trusty_context_switch(1, a1, a2, a3, a4, (__int64)v21);
      goto LABEL_17;
  }
  return (__int64)a7;
}

/* ===== trusty_log_handler @ 0x94004FE0 size 300 ===== */
unsigned __int64 *__fastcall trusty_log_handler(
        int a1,
        int a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        unsigned __int64 *a7,
        char a8)
{
  __int64 v9; // x7
  int v10; // w22
  __int64 v11; // x19
  unsigned int v12; // w1
  char *v13; // x0
  __int64 i; // x21
  __int64 v15; // x0
  unsigned __int64 v16; // x1
  __int64 v17; // x1

  if ( a1 == -1124073471 || a1 == -50331647 )
  {
    if ( a2 != 0 )
    {
      if ( a2 != 1 )
      {
        v16 = 0xFFFFFFFFLL;
LABEL_23:
        *a7 = v16;
        return a7;
      }
      v17 = 0x2000;
    }
    else
    {
      v17 = 4096;
    }
    v16 = v17 & 0xFFFFFFFF0000FFFFLL | 0x12000000;
    goto LABEL_23;
  }
  if ( a1 == -1124073472 )
  {
    if ( MEMORY[0x94010320] == 0 )
    {
      v9 = a8 & 1;
      v10 = (unsigned __int8)a2;
      v11 = 0x9400E310LL + 132 * v9;
      v12 = *(_DWORD *)(v11 + 128);
      *(_DWORD *)(v11 + 128) = v12 + 1;
      *(_BYTE *)(v11 + v12) = v10;
      if ( v12 == 127 || v10 == 10 )
      {
        if ( v9 != 0 )
          v13 = "non-secure os: ";
        else
          v13 = "secure os: ";
        printf_simple(v13);
        for ( i = 0; *(_DWORD *)(v11 + 128) > (unsigned int)i; ++i )
        {
          v15 = *(unsigned __int8 *)(v11 + i);
          putchar(v15);
        }
        if ( v10 != 10 )
          printf_simple(" <...>\n");
        *(_DWORD *)(v11 + 128) = 0;
      }
    }
    *a7 = 0;
  }
  else
  {
    *a7 = 0xFFFFFFFFLL;
  }
  return a7;
}

/* ===== nullsub_3 @ 0x9400510C size 4 ===== */
void nullsub_3()
{
  ;
}

/* ===== print_uint @ 0x94005110 size 108 ===== */
unsigned __int64 __fastcall print_uint(unsigned __int64 result, unsigned int a2)
{
  __int64 v2; // x2
  unsigned __int64 v3; // x3
  int v4; // w19
  unsigned __int64 v5; // x0
  char v6; // w0
  _BYTE v7[24]; // [xsp+28h] [xbp+28h]

  v2 = 0;
  do
  {
    v3 = result / a2;
    v4 = v2 + 1;
    v5 = result % a2;
    if ( (int)v5 > 9 )
      v6 = v5 + 87;
    else
      v6 = v5 + 48;
    v7[v2] = v6;
    result = v3;
    ++v2;
  }
  while ( v3 != 0 );
  while ( --v4 != -1 )
    result = putchar((unsigned __int8)v7[v4]);
  return result;
}

/* ===== printf_impl @ 0x9400517C size 812 ===== */
const char *printf_impl(
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
  const char *result; // x0
  int v11; // w1
  const char *v12; // x19
  int gr_offs; // w1
  unsigned __int64 *stack; // x0
  unsigned __int64 v15; // x20
  int v16; // w1
  char *v17; // x0
  unsigned __int64 v18; // x0
  int v19; // w1
  char *v20; // x0
  _BYTE *j; // x20
  __int64 v22; // x0
  int v23; // w1
  unsigned __int64 *v24; // x0
  unsigned __int64 v25; // x23
  char *i; // x20
  int v27; // w1
  unsigned __int64 *v28; // x0
  int v29; // w1
  char *v30; // x0
  unsigned int v31; // w1
  int v32; // w1
  unsigned __int64 *v33; // x0
  int v34; // w1
  char *v35; // x0
  va_list va; // [xsp+40h] [xbp+40h] BYREF
  char v37; // [xsp+A0h] [xbp+A0h] BYREF

  va_start(va, a9);
  va[0].__gr_offs = -56;
  while ( 1 )
  {
    result = (const char *)*(unsigned __int8 *)a1;
    if ( *a1 == 0 )
      return result;
    if ( (_DWORD)result == 37 )
    {
      result = a1 + 2;
      v11 = 0;
LABEL_5:
      v12 = result - 1;
      switch ( *(result - 1) )
      {
        case 'd':
        case 'i':
          if ( v11 != 0 )
          {
            gr_offs = va[0].__gr_offs;
            stack = (unsigned __int64 *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, gr_offs + 8 <= 0) )
              stack = (unsigned __int64 *)(&v37 + gr_offs);
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 15) & 0xFFFFFFFFFFFFFFF8LL);
            v15 = *stack;
          }
          else
          {
            v16 = va[0].__gr_offs;
            v17 = (char *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v16 + 8 <= 0) )
              v17 = &v37 + v16;
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 11) & 0xFFFFFFFFFFFFFFF8LL);
            v15 = *(int *)v17;
          }
          if ( (v15 & 0x8000000000000000LL) != 0 )
          {
            v15 = -(__int64)v15;
            putchar(45);
          }
          v18 = v15;
          goto LABEL_62;
        case 'l':
          ++v11;
          goto LABEL_7;
        case 'p':
          v23 = va[0].__gr_offs;
          v24 = (unsigned __int64 *)va[0].__stack;
          if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v23 + 8 <= 0) )
            v24 = (unsigned __int64 *)(&v37 + v23);
          else
            va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 15) & 0xFFFFFFFFFFFFFFF8LL);
          v25 = *v24;
          if ( *v24 != 0 )
          {
            for ( i = byte_9400AA71; *(++i - 2) != 0; putchar((unsigned __int8)*(i - 2)) )
              ;
          }
          v18 = v25;
          goto LABEL_49;
        case 's':
          v19 = va[0].__gr_offs;
          v20 = (char *)va[0].__stack;
          if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v19 + 8 <= 0) )
            v20 = &v37 + v19;
          else
            va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 15) & 0xFFFFFFFFFFFFFFF8LL);
          for ( j = *(_BYTE **)v20; ; ++j )
          {
            v22 = (unsigned __int8)*j;
            if ( *j == 0 )
              break;
            putchar(v22);
          }
          goto LABEL_64;
        case 'u':
          if ( v11 != 0 )
          {
            v32 = va[0].__gr_offs;
            v33 = (unsigned __int64 *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v32 + 8 <= 0) )
              v33 = (unsigned __int64 *)(&v37 + v32);
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 15) & 0xFFFFFFFFFFFFFFF8LL);
            v18 = *v33;
          }
          else
          {
            v34 = va[0].__gr_offs;
            v35 = (char *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v34 + 8 <= 0) )
              v35 = &v37 + v34;
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 11) & 0xFFFFFFFFFFFFFFF8LL);
            v18 = *(unsigned int *)v35;
          }
LABEL_62:
          v31 = 10;
          goto LABEL_63;
        case 'x':
          if ( v11 != 0 )
          {
            v27 = va[0].__gr_offs;
            v28 = (unsigned __int64 *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v27 + 8 <= 0) )
              v28 = (unsigned __int64 *)(&v37 + v27);
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 15) & 0xFFFFFFFFFFFFFFF8LL);
            v18 = *v28;
          }
          else
          {
            v29 = va[0].__gr_offs;
            v30 = (char *)va[0].__stack;
            if ( va[0].__gr_offs < 0 && (va[0].__gr_offs += 8, v29 + 8 <= 0) )
              v30 = &v37 + v29;
            else
              va[0].__stack = (void *)(((unsigned __int64)va[0].__stack + 11) & 0xFFFFFFFFFFFFFFF8LL);
            v18 = *(unsigned int *)v30;
          }
LABEL_49:
          v31 = 16;
LABEL_63:
          print_uint(v18, v31);
LABEL_64:
          a1 = v12 + 1;
          continue;
        case 'z':
          v11 = 2;
LABEL_7:
          ++result;
          goto LABEL_5;
        default:
          return result;
      }
    }
    ++a1;
    putchar(result);
  }
}

/* ===== assert_fail @ 0x940054A8 size 28 ===== */
void __fastcall __noreturn assert_fail(
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
  printf_impl("ASSERT: %s <%d> : %s\n", a2, a3, a4, a5, a6, a7, a8, a9, a1);
  while ( 1 )
    ;
}

/* ===== memset_simple @ 0x940054C4 size 28 ===== */
__int64 __fastcall memset_simple(__int64 result, char a2, __int64 a3)
{
  __int64 i; // x3

  for ( i = 0; i != a3; ++i )
    *(_BYTE *)(result + i) = a2;
  return result;
}

/* ===== memcpy_simple @ 0x940054E0 size 32 ===== */
__int64 __fastcall memcpy_simple(__int64 result, __int64 a2, __int64 a3)
{
  __int64 i; // x3

  for ( i = 0; i != a3; ++i )
    *(_BYTE *)(result + i) = *(_BYTE *)(a2 + i);
  return result;
}

/* ===== memmove_simple @ 0x94005500 size 52 ===== */
__int64 __fastcall memmove_simple(__int64 a1, __int64 a2, unsigned __int64 a3)
{
  __int64 result; // x0
  unsigned __int64 v5; // x5
  char v6; // t1

  if ( a1 - a2 >= a3 )
    return memcpy_simple(a1, a2, a3);
  v5 = a2 + a3;
  for ( result = a1 + a3; result != a1; --result )
  {
    v6 = *(_BYTE *)--v5;
    *(_BYTE *)(result - 1) = v6;
  }
  return result;
}

/* ===== printf_simple @ 0x94005534 size 164 ===== */
__int64 printf_simple(
        __int64 a1,
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
  __int64 v9; // x19
  __int64 result; // x0
  __int64 v11; // x0
  va_list va; // [xsp+20h] [xbp+20h] BYREF
  va_list va1; // [xsp+40h] [xbp+40h] BYREF
  _BYTE v14[128]; // [xsp+60h] [xbp+60h] BYREF

  va_start(va, a9);
  va_start(va1, a9);
  v9 = 0;
  snprintf_impl(v14, 127, a1, va);
  v14[127] = 0;
  do
  {
    result = (unsigned int)v9;
    if ( v14[v9] == 0 )
      break;
    v11 = (unsigned __int8)v14[v9++];
    result = putchar(v11);
  }
  while ( (_DWORD)result != -1 );
  return result;
}

/* ===== putchar @ 0x940055D8 size 44 ===== */
__int64 __fastcall putchar(unsigned int a1)
{
  if ( (int)putc_hw((unsigned __int8)a1) < 0 )
    return 0xFFFFFFFFLL;
  else
    return a1;
}

/* ===== strlen_simple @ 0x94005604 size 28 ===== */
_BYTE *__fastcall strlen_simple(_BYTE *a1)
{
  _BYTE *i; // x1

  for ( i = a1; *i != 0; ++i )
    ;
  return (_BYTE *)(i - a1);
}

/* ===== buffer_putchar @ 0x94005620 size 44 ===== */
__int64 __fastcall buffer_putchar(__int64 result, _QWORD *a2)
{
  _BYTE *v2; // x2

  if ( a2[1] > 1u )
  {
    v2 = (_BYTE *)(*a2)++;
    *v2 = result;
    result = a2[1] - 1LL;
    a2[1] = result;
  }
  return result;
}

/* ===== vsnprintf_impl @ 0x9400564C size 3360 ===== */
__int64 __fastcall vsnprintf_impl(const char *a1, void (*a2)(void), char *a3, int a4, __int64 a5)
{
  unsigned __int64 v6; // x27
  __int64 v7; // x20
  int v8; // w21
  char *v9; // x22
  int v10; // w2
  unsigned int v11; // w5
  const char *v12; // x26
  unsigned int v13; // w24
  unsigned int v14; // w23
  int v15; // w0
  const char *v16; // x28
  int v17; // w1
  int v18; // w12
  int v19; // w15
  int v20; // w13
  int v21; // w7
  int v22; // w11
  int v23; // w6
  int v24; // w16
  bool v25; // w10
  int v26; // w25
  int v27; // w24
  int v28; // w9
  int v29; // w8
  char *v30; // x18
  int v31; // w0
  unsigned int v32; // w24
  int v33; // w0
  unsigned __int64 v34; // x14
  int *v35; // x0
  unsigned __int64 v36; // x1
  int v37; // w0
  int *v38; // x3
  int v39; // w14
  int v40; // w14
  unsigned __int64 v41; // x1
  int v42; // w0
  unsigned int *v43; // x3
  unsigned __int64 v44; // x25
  unsigned __int64 v45; // x1
  unsigned __int8 **v46; // x0
  unsigned __int8 *v47; // x24
  unsigned __int64 v48; // x0
  _BYTE *v49; // x28
  unsigned __int64 v50; // x5
  __int64 j; // x26
  int v52; // w0
  char *v53; // x24
  char v54; // w1
  __int64 v55; // x0
  char *v56; // x1
  int v57; // w0
  int *v58; // x0
  unsigned __int64 v59; // x1
  int v60; // w0
  _BYTE **v61; // x3
  _BYTE *v62; // x25
  unsigned __int64 v63; // x1
  char **v64; // x0
  int v65; // w26
  __int64 v66; // x0
  __int64 v67; // x0
  char *i; // x24
  int v69; // w0
  _QWORD **v70; // x0
  _WORD **v71; // x0
  _BYTE **v72; // x0
  _DWORD **v73; // x0
  int v74; // w0
  unsigned __int64 *v75; // x0
  unsigned __int64 v76; // x0
  int v77; // w7
  __int64 v78; // x6
  int v79; // w0
  int v80; // w0
  char **v81; // x0
  char *v82; // x26
  __int64 v83; // x6
  unsigned int v84; // w28
  int v85; // w24
  int k; // w6
  __int64 m; // x6
  __int64 v88; // x0
  int n; // w25
  unsigned __int64 *v90; // x0
  unsigned __int16 *v91; // x0
  unsigned __int8 *v92; // x0
  unsigned int *v93; // x0
  unsigned __int64 *v94; // x0
  __int16 *v95; // x0
  unsigned __int8 *v96; // x0
  int *v97; // x0
  __int64 v98; // x9
  unsigned __int64 v99; // x8
  char *v100; // x26
  unsigned __int64 v101; // x7
  char v102; // w8
  char v103; // w13
  int v104; // w28
  int v105; // w8
  int v106; // w0
  int v107; // w0
  int v108; // w7
  int v109; // w24
  int v110; // w7
  __int64 v111; // x8
  int v112; // w0
  int v113; // w28
  __int64 v114; // x6
  __int64 v115; // x28
  int v116; // w0
  __int64 v117; // x6
  __int64 v118; // x2
  int ii; // w25
  __int64 v120; // x0
  unsigned int v121; // t1
  int v123; // [xsp+68h] [xbp+68h]
  __int64 v124; // [xsp+68h] [xbp+68h]
  __int64 v125; // [xsp+68h] [xbp+68h]
  int v126; // [xsp+68h] [xbp+68h]
  __int64 v127; // [xsp+68h] [xbp+68h]
  __int64 v128; // [xsp+68h] [xbp+68h]
  __int64 v129; // [xsp+70h] [xbp+70h]
  int v130; // [xsp+78h] [xbp+78h]
  __int64 v131; // [xsp+80h] [xbp+80h]
  __int64 v132; // [xsp+80h] [xbp+80h]
  unsigned int v133; // [xsp+8Ch] [xbp+8Ch]
  const char *v134; // [xsp+98h] [xbp+98h]
  unsigned int v135; // [xsp+A0h] [xbp+A0h]
  char *v136; // [xsp+A0h] [xbp+A0h]
  int v137; // [xsp+A0h] [xbp+A0h]
  unsigned int v138; // [xsp+A8h] [xbp+A8h]
  int v139; // [xsp+ACh] [xbp+ACh]
  _BYTE v141[72]; // [xsp+C8h] [xbp+C8h] BYREF

  v134 = a1;
  v6 = *(_QWORD *)a5;
  v7 = *(_QWORD *)(a5 + 8);
  v8 = *(_DWORD *)(a5 + 24);
  if ( a2 != nullptr )
    v9 = nullptr;
  else
    v9 = a3;
  if ( a1 == nullptr )
    v134 = "(fmt null)\n";
  if ( (unsigned int)(a4 - 2) >= 0x23 )
    v10 = 10;
  else
    v10 = a4;
  v11 = 0;
  v138 = v10;
  v139 = 0;
LABEL_10:
  v12 = v134;
  v13 = v11 - (_DWORD)v134;
  while ( 1 )
  {
    v14 = v13 + (_DWORD)v12;
    v16 = v12 + 1;
    v15 = *(unsigned __int8 *)v12;
    if ( v15 != 37 )
      break;
    if ( v139 == 0 )
    {
      v17 = 0;
      v18 = 0;
      v19 = 0;
      v20 = 0;
      v21 = 0;
      v22 = 0;
      v23 = 0;
      v24 = 0;
      v25 = false;
      v26 = 0;
      v27 = 0;
      v28 = 0;
      v29 = 0;
      v133 = v14;
      v30 = v9;
      v135 = 32;
      while ( 2 )
      {
        v134 = v16 + 1;
        v31 = *(unsigned __int8 *)v16;
        switch ( *v16 )
        {
          case '#':
            v25 = true;
            goto LABEL_23;
          case '%':
            if ( a2 != nullptr )
              goto LABEL_100;
            ++v9;
            LOBYTE(v33) = 37;
            goto LABEL_102;
          case '*':
            if ( v23 != 0 )
            {
              if ( (v8 & 0x80000000) == 0 )
              {
                v36 = v6 + 11;
                v37 = v8;
                goto LABEL_42;
              }
              v37 = v8 + 8;
              if ( v8 + 8 <= 0 )
              {
                v38 = (int *)(v7 + v8);
              }
              else
              {
                v36 = v6 + 11;
LABEL_42:
                v38 = (int *)v6;
                v6 = v36 & 0xFFFFFFFFFFFFFFF8LL;
              }
              v17 = *v38;
              v8 = v37;
              goto LABEL_51;
            }
            if ( (v8 & 0x80000000) == 0 )
            {
              v34 = v6 + 11;
LABEL_34:
              v35 = (int *)v6;
              v6 = v34 & 0xFFFFFFFFFFFFFFF8LL;
              goto LABEL_36;
            }
            if ( v8 + 8 > 0 )
            {
              v34 = v6 + 11;
              v8 += 8;
              goto LABEL_34;
            }
            v35 = (int *)(v7 + v8);
            v8 += 8;
LABEL_36:
            v27 = *v35;
            if ( *v35 < 0 )
            {
              v26 = ((unsigned __int8)v26 ^ 1) & 1;
              v27 = -v27;
            }
LABEL_23:
            v16 = v134;
            continue;
          case '+':
            v24 = 1;
            goto LABEL_23;
          case '-':
            v26 = 1;
            goto LABEL_23;
          case '.':
            goto LABEL_51;
          case '0':
            if ( v23 != 0 )
              goto LABEL_45;
            v135 = 48;
            goto LABEL_23;
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
LABEL_45:
            v39 = 0;
            while ( 1 )
            {
              v40 = v31 + 10 * v39;
              v31 = *(unsigned __int8 *)v134;
              v39 = v40 - 48;
              if ( (unsigned int)(v31 - 48) > 9 )
                break;
              ++v134;
            }
            if ( v23 != 0 )
            {
              v17 = v39;
LABEL_51:
              v23 = 1;
            }
            else
            {
              v27 = v39;
            }
            goto LABEL_23;
          case 'D':
            if ( (v8 & 0x80000000) == 0 )
            {
              v59 = v6 + 15;
              v60 = v8;
LABEL_108:
              v61 = (_BYTE **)v6;
              v6 = v59 & 0xFFFFFFFFFFFFFFF8LL;
              goto LABEL_110;
            }
            v60 = v8 + 8;
            if ( v8 + 8 > 0 )
            {
              v59 = v6 + 15;
              goto LABEL_108;
            }
            v61 = (_BYTE **)(v7 + v8);
LABEL_110:
            v62 = *v61;
            if ( (v60 & 0x80000000) == 0 )
            {
              v63 = v6 + 15;
              v8 = v60;
LABEL_114:
              v64 = (char **)v6;
              v6 = v63 & 0xFFFFFFFFFFFFFFF8LL;
              goto LABEL_116;
            }
            v8 = v60 + 8;
            if ( v60 + 8 > 0 )
            {
              v63 = v6 + 15;
              goto LABEL_114;
            }
            v64 = (char **)(v7 + v60);
LABEL_116:
            v136 = *v64;
            if ( v27 == 0 )
              v27 = 16;
            while ( 1 )
            {
              v65 = v27 - 1;
              if ( v27 == 0 )
                break;
              v66 = (unsigned __int8)a0123456789abcd[(unsigned __int8)*v62 >> 4];
              if ( a2 != nullptr )
                ((void (__fastcall *)(__int64, char *))a2)(v66, a3);
              else
                *v9++ = v66;
              v67 = (unsigned __int8)a0123456789abcd[*v62 & 0xF];
              if ( a2 != nullptr )
                ((void (__fastcall *)(__int64, char *))a2)(v67, a3);
              else
                *v9++ = v67;
              v14 += 2;
              ++v62;
              if ( v27 != 1 )
              {
                for ( i = v136; *i != 0; ++i )
                {
                  if ( a2 != nullptr )
                    a2();
                  else
                    *v9++ = *i;
                  ++v14;
                }
              }
              v27 = v65;
            }
            goto LABEL_73;
          case 'X':
            v79 = v8;
            v24 = 1;
            goto LABEL_213;
          case 'b':
            if ( (v8 & 0x80000000) == 0 )
            {
              v41 = v6 + 11;
              v42 = v8;
LABEL_56:
              v43 = (unsigned int *)v6;
              v6 = v41 & 0xFFFFFFFFFFFFFFF8LL;
              goto LABEL_58;
            }
            v42 = v8 + 8;
            if ( v8 + 8 > 0 )
            {
              v41 = v6 + 11;
              goto LABEL_56;
            }
            v43 = (unsigned int *)(v7 + v8);
LABEL_58:
            v44 = *v43;
            if ( (v42 & 0x80000000) == 0 )
            {
              v45 = v6 + 15;
              v8 = v42;
LABEL_62:
              v46 = (unsigned __int8 **)v6;
              v6 = v45 & 0xFFFFFFFFFFFFFFF8LL;
              goto LABEL_64;
            }
            v8 = v42 + 8;
            if ( v42 + 8 > 0 )
            {
              v45 = v6 + 15;
              goto LABEL_62;
            }
            v46 = (unsigned __int8 **)(v7 + v42);
LABEL_64:
            v47 = *v46;
            v141[0] = 0;
            v48 = v44;
            v49 = v141;
            v50 = *v47;
            do
            {
              *++v49 = a0123456789abcd[v48 % v50];
              v48 /= v50;
            }
            while ( v48 != 0 );
            for ( j = 0; ; --j )
            {
              v52 = (unsigned __int8)v49[j];
              v14 = v133 - j;
              if ( v49[j] == 0 )
                break;
              if ( a2 != nullptr )
                a2();
              else
                *v9++ = v52;
            }
            if ( v44 != 0 )
            {
              v53 = (char *)(v47 + 1);
              while ( 1 )
              {
                v54 = *v53;
                if ( *v53 == 0 )
                  break;
                ++v53;
                if ( ((1 << (v54 - 1)) & v44) != 0 )
                {
                  if ( v52 != 0 )
                    v55 = 44;
                  else
                    v55 = 60;
                  if ( a2 != nullptr )
                    ((void (__fastcall *)(__int64, char *))a2)(v55, a3);
                  else
                    *v9++ = v55;
                  ++v14;
                  while ( (unsigned __int8)*v53 > 0x20u )
                  {
                    if ( a2 != nullptr )
                      a2();
                    else
                      *v9++ = *v53;
                    ++v14;
                    ++v53;
                  }
                  v52 = 1;
                }
                else
                {
                  while ( (unsigned __int8)*v53 > 0x20u )
                    ++v53;
                }
              }
              v56 = v9;
              if ( v52 != 0 )
              {
                if ( a2 != nullptr )
                {
LABEL_100:
                  a2();
                }
                else
                {
                  ++v9;
                  *v56 = 62;
                }
LABEL_103:
                ++v14;
              }
            }
LABEL_73:
            v11 = v14;
            break;
          case 'c':
            v57 = v8;
            if ( v8 < 0 && (v8 += 8, v8 <= 0) )
            {
              v58 = (int *)(v7 + v57);
            }
            else
            {
              v58 = (int *)v6;
              v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
            }
            v33 = *v58;
            if ( a2 != nullptr )
              goto LABEL_100;
            ++v9;
LABEL_102:
            *v30 = v33;
            goto LABEL_103;
          case 'd':
          case 'i':
            v79 = v8;
            v78 = 10;
            goto LABEL_244;
          case 'h':
            if ( v21 != 0 )
            {
              v21 = 0;
              v22 = 1;
            }
            else
            {
              v21 = 1;
            }
            goto LABEL_23;
          case 'j':
            v20 = 1;
            goto LABEL_23;
          case 'l':
            if ( v29 != 0 )
            {
              v28 = 1;
              v29 = 0;
            }
            else
            {
              v29 = 1;
            }
            goto LABEL_23;
          case 'n':
            v69 = v8;
            if ( v20 != 0 || v28 != 0 || v29 != 0 || v18 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v70 = (_QWORD **)(v7 + v69);
              }
              else
              {
                v70 = (_QWORD **)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              **v70 = (int)v14;
            }
            else if ( v21 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v71 = (_WORD **)(v7 + v69);
              }
              else
              {
                v71 = (_WORD **)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              **v71 = v14;
            }
            else if ( v22 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v72 = (_BYTE **)(v7 + v69);
              }
              else
              {
                v72 = (_BYTE **)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              **v72 = v14;
            }
            else
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v73 = (_DWORD **)(v7 + v69);
              }
              else
              {
                v73 = (_DWORD **)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              **v73 = v14;
            }
            goto LABEL_73;
          case 'o':
            v79 = v8;
            v24 = 0;
            v78 = 8;
            goto LABEL_214;
          case 'p':
            v74 = v8;
            v25 = v27 == 0;
            if ( v8 < 0 && (v8 += 8, v8 <= 0) )
            {
              v75 = (unsigned __int64 *)(v7 + v74);
            }
            else
            {
              v75 = (unsigned __int64 *)v6;
              v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
            }
            v24 = 0;
            v76 = *v75;
            v77 = 0;
            v78 = 16;
            goto LABEL_272;
          case 'q':
            v28 = 1;
            goto LABEL_23;
          case 'r':
            v79 = v8;
            v78 = v138;
            if ( v24 == 0 )
              goto LABEL_214;
            goto LABEL_244;
          case 's':
            v80 = v8;
            if ( v8 < 0 && (v8 += 8, v8 <= 0) )
            {
              v81 = (char **)(v7 + v80);
            }
            else
            {
              v81 = (char **)v6;
              v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
            }
            v82 = *v81;
            if ( *v81 == nullptr )
              v82 = "(null)";
            if ( v23 != 0 )
            {
              v83 = 0;
              do
              {
                v84 = v83;
                if ( (int)v83 >= v17 )
                  break;
                ++v83;
              }
              while ( v82[v83 - 1] != 0 );
            }
            else
            {
              v84 = (unsigned int)strlen_simple(v82);
            }
            v85 = v27 - v84;
            if ( v85 > 0 && (v26 & 1) == 0 )
            {
              for ( k = v85; k != 0; --k )
              {
                if ( a2 != nullptr )
                {
                  v123 = k;
                  ((void (__fastcall *)(_QWORD, char *))a2)(v135, a3);
                  k = v123;
                }
                else
                {
                  *v9++ = v135;
                }
              }
              v14 += v85;
              v85 = -1;
            }
            for ( m = 0; v84 != (_DWORD)m; ++m )
            {
              v88 = (unsigned __int8)v82[m];
              if ( a2 != nullptr )
              {
                v124 = m;
                ((void (__fastcall *)(__int64, char *))a2)(v88, a3);
                m = v124;
              }
              else
              {
                *v9++ = v88;
              }
            }
            v14 += v84;
            if ( v85 > 0 && (v26 & 1) != 0 )
            {
              for ( n = v85; n != 0; --n )
              {
                if ( a2 != nullptr )
                  ((void (__fastcall *)(_QWORD, char *))a2)(v135, a3);
                else
                  *v9++ = v135;
              }
              v14 += v85;
            }
            goto LABEL_73;
          case 't':
            v19 = 1;
            goto LABEL_23;
          case 'u':
            v79 = v8;
            v24 = 0;
            v78 = 10;
            goto LABEL_214;
          case 'x':
            v79 = v8;
            v24 = 0;
LABEL_213:
            v78 = 16;
LABEL_214:
            if ( v20 != 0 || v28 != 0 || v19 != 0 || v29 != 0 || v18 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v90 = (unsigned __int64 *)(v7 + v79);
              }
              else
              {
                v90 = (unsigned __int64 *)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v90;
            }
            else if ( v21 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v91 = (unsigned __int16 *)(v7 + v79);
              }
              else
              {
                v91 = (unsigned __int16 *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v91;
            }
            else if ( v22 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v92 = (unsigned __int8 *)(v7 + v79);
              }
              else
              {
                v92 = (unsigned __int8 *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v92;
            }
            else
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v93 = (unsigned int *)(v7 + v79);
              }
              else
              {
                v93 = (unsigned int *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v93;
            }
            v77 = 0;
            goto LABEL_272;
          case 'y':
            v79 = v8;
            v78 = 16;
LABEL_244:
            if ( v20 != 0 || v28 != 0 || v19 != 0 || v29 != 0 || v18 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v94 = (unsigned __int64 *)(v7 + v79);
              }
              else
              {
                v94 = (unsigned __int64 *)v6;
                v6 = (v6 + 15) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v94;
            }
            else if ( v21 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v95 = (__int16 *)(v7 + v79);
              }
              else
              {
                v95 = (__int16 *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v95;
            }
            else if ( v22 != 0 )
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v96 = (unsigned __int8 *)(v7 + v79);
              }
              else
              {
                v96 = (unsigned __int8 *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v96;
            }
            else
            {
              if ( v8 < 0 && (v8 += 8, v8 <= 0) )
              {
                v97 = (int *)(v7 + v79);
              }
              else
              {
                v97 = (int *)v6;
                v6 = (v6 + 11) & 0xFFFFFFFFFFFFFFF8LL;
              }
              v76 = *v97;
            }
            v24 = 0;
            v77 = 1;
LABEL_272:
            if ( (v76 & 0x8000000000000000LL) != 0 && v77 != 0 )
            {
              v76 = -(__int64)v76;
              v98 = 1;
            }
            else
            {
              v98 = 0;
            }
            v141[0] = 0;
            v99 = v76;
            v100 = v141;
            do
            {
              v101 = v99 / (int)v78;
              ++v100;
              v102 = a0123456789abcd[v99 % (int)v78];
              if ( v24 != 0 )
              {
                if ( (unsigned __int8)(v102 - 97) <= 0x19u )
                  v103 = 32;
                else
                  v103 = 0;
                v102 -= v103;
              }
              *v100 = v102;
              v99 = v101;
            }
            while ( v101 != 0 );
            v104 = v25 && v76 != 0;
            v105 = (_DWORD)v100 - (unsigned int)v141;
            v106 = 0;
            if ( v104 != 0 )
            {
              if ( (_DWORD)v78 == 8 )
              {
                v106 = 1;
              }
              else if ( (_DWORD)v78 == 16 )
              {
                v106 = 2;
              }
              else
              {
                v106 = 0;
              }
            }
            v107 = v106 + v98;
            if ( (v26 & 1) == 0 && v135 == 48 )
              v17 = v27 - v107;
            if ( v17 < v105 )
              v108 = (_DWORD)v100 - (unsigned int)v141;
            else
              v108 = v17;
            v137 = v17 - v105;
            v109 = v27 - (v107 + v108);
            if ( v26 == 0 )
            {
              v110 = v109;
              v111 = 32;
              while ( v110 > 0 )
              {
                if ( a2 != nullptr )
                {
                  v125 = v78;
                  v130 = v110;
                  v129 = v111;
                  v131 = v98;
                  ((void (__fastcall *)(__int64, char *))a2)(32, a3);
                  v78 = v125;
                  v110 = v130;
                  v111 = v129;
                  v98 = v131;
                }
                else
                {
                  *v9++ = v111;
                }
                --v110;
              }
              if ( v109 < 0 )
                v112 = 0;
              else
                v112 = v109;
              v14 += v112;
              v109 = v109 - 1 - v112;
            }
            if ( (_DWORD)v98 != 0 )
            {
              if ( a2 != nullptr )
              {
                v126 = v78;
                ((void (__fastcall *)(__int64, char *))a2)(45, a3);
                LODWORD(v78) = v126;
              }
              else
              {
                *v9++ = 45;
              }
              ++v14;
            }
            if ( v104 != 0 )
            {
              if ( (_DWORD)v78 == 8 )
              {
                if ( a2 != nullptr )
                  ((void (__fastcall *)(__int64, char *))a2)(48, a3);
                else
                  *v9++ = 48;
                ++v14;
              }
              else if ( (_DWORD)v78 == 16 )
              {
                if ( a2 != nullptr )
                {
                  ((void (__fastcall *)(__int64, char *))a2)(48, a3);
                  ((void (__fastcall *)(__int64, char *))a2)(120, a3);
                }
                else
                {
                  *v9 = 48;
                  v9[1] = 120;
                  v9 += 2;
                }
                v14 += 2;
              }
            }
            v113 = v137;
            v114 = 48;
            while ( v113 > 0 )
            {
              if ( a2 != nullptr )
              {
                v127 = v114;
                ((void (__fastcall *)(__int64, char *))a2)(48, a3);
                v114 = v127;
              }
              else
              {
                *v9++ = v114;
              }
              --v113;
            }
            v115 = 0;
            if ( v137 < 0 )
              v116 = 0;
            else
              v116 = v137;
            v117 = v14 + v116;
            while ( 1 )
            {
              v118 = (unsigned int)(v117 - v115);
              v14 = v117 - v115;
              if ( v100[v115] == 0 )
                break;
              if ( a2 != nullptr )
              {
                v128 = v117;
                a2();
                v117 = v128;
              }
              else
              {
                *v9++ = v100[v115];
              }
              --v115;
            }
            if ( v26 != 0 )
            {
              for ( ii = v109; ii > 0; --ii )
              {
                if ( a2 != nullptr )
                {
                  v132 = v118;
                  ((void (__fastcall *)(__int64, char *))a2)(32, a3);
                  v118 = v132;
                }
                else
                {
                  *v9++ = 32;
                }
              }
              if ( v109 < 0 )
                v109 = 0;
              v14 = v118 + v109;
            }
            goto LABEL_73;
          case 'z':
            v18 = 1;
            goto LABEL_23;
          default:
            v32 = v14 - (_DWORD)v12;
            while ( 1 )
            {
              v14 = v32 + (_DWORD)v12;
              if ( v12 >= v134 )
                break;
              v121 = *(unsigned __int8 *)v12++;
              v120 = v121;
              if ( a2 != nullptr )
                ((void (__fastcall *)(__int64, char *))a2)(v120, a3);
              else
                *v9++ = v120;
            }
            v139 = 1;
            goto LABEL_73;
        }
        goto LABEL_10;
      }
    }
LABEL_13:
    if ( a2 != nullptr )
      a2();
    else
      *v9++ = v15;
    ++v12;
  }
  if ( *v12 != 0 )
    goto LABEL_13;
  return v14;
}

/* ===== snprintf_impl @ 0x9400636C size 96 ===== */
__int64 __fastcall snprintf_impl(_BYTE *a1, __int64 a2, const char *a3, __int64 a4)
{
  __int64 result; // x0
  _BYTE v6[32]; // [xsp+20h] [xbp+20h] BYREF
  _BYTE *v7; // [xsp+40h] [xbp+40h] BYREF
  __int64 v8; // [xsp+48h] [xbp+48h]

  v7 = a1;
  v8 = a2;
  memcpy_simple((__int64)v6, a4, 32);
  result = vsnprintf_impl(a3, (void (*)(void))buffer_putchar, (char *)&v7, 10, (__int64)v6);
  if ( v8 != 0 )
    *v7 = 0;
  return result;
}

/* ===== set_boot_flag @ 0x940063CC size 20 ===== */
unsigned __int64 set_boot_flag()
{
  MEMORY[0x94010328] |= 1uLL;
  return 0x94010000;
}

/* ===== get_boot_flag @ 0x940063E0 size 20 ===== */
__int64 get_boot_flag()
{
  return MEMORY[0x94010328];
}

/* ===== clear_boot_flag @ 0x940063F4 size 20 ===== */
__int64 clear_boot_flag()
{
  return MEMORY[0x94010328];
}

/* ===== read_boot_flag @ 0x94006408 size 20 ===== */
__int64 read_boot_flag()
{
  return MEMORY[0x94010328];
}

/* ===== init_xlation_table_inner @ 0x9400641C size 592 ===== */
_QWORD *__fastcall init_xlation_table_inner(
        _QWORD *result,
        unsigned __int64 a2,
        __int64 *a3,
        unsigned int a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12)
{
  const char *v14; // x0
  __int64 v15; // x24
  __int64 v16; // x25
  __int64 v17; // x19
  unsigned __int64 v18; // x2
  unsigned __int64 v19; // x23
  unsigned __int64 v20; // x3
  _QWORD *v21; // x5
  int v22; // w4
  __int64 v23; // x8
  unsigned __int64 v24; // x6
  unsigned __int64 v25; // x8
  __int64 v26; // x19
  unsigned __int64 v27; // x2
  __int64 v28; // x19
  __int64 v29; // x3
  __int64 v30; // x19
  __int64 v31; // x3
  int v32; // w2
  __int64 v33; // x19
  __int64 v34; // x2
  unsigned int v35; // w2
  unsigned __int64 v36; // x2

  if ( a4 > 3 )
  {
    v14 = "init_xlation_table_inner";
    goto LABEL_34;
  }
  v15 = 1LL << (-9 * (unsigned __int8)a4 + 39);
  v16 = 511LL << (-9 * (unsigned __int8)a4 + 39);
  do
  {
    v17 = result[2];
    v18 = result[1];
    if ( v17 == 0 )
      goto LABEL_8;
    if ( v17 + v18 - 1 >= a2 )
    {
      v17 = -1;
LABEL_8:
      v19 = a2 + v15;
      v20 = a2 + v15 - 1;
      if ( v18 > v20 )
      {
        v17 = 0;
        goto LABEL_42;
      }
      v21 = result;
      v22 = -1;
      while ( 1 )
      {
        v23 = v21[2];
        if ( v23 == 0 )
          break;
        v24 = v21[1];
        if ( v24 > v20 )
          break;
        v25 = v23 + v24 - 1;
        if ( v25 >= a2 && *((_DWORD *)v21 + 6) != v22 )
        {
          if ( v24 > a2 || v25 < v20 )
            goto LABEL_37;
          v22 = *((_DWORD *)v21 + 6);
        }
        v21 += 4;
      }
      if ( (v22 & 0x80000000) == 0 )
      {
        v26 = 3;
        v27 = *result - v18 + a2;
        if ( a4 != 3 )
          v26 = 1;
        v28 = v26 | v27;
        v29 = 32;
        if ( (v22 & 0x10) == 0 )
          v29 = 0;
        v30 = v28 | v29;
        v31 = 128;
        if ( (v22 & 8) != 0 )
          v31 = 0;
        v32 = v22 & 7;
        v33 = v30 | v31;
        if ( (v22 & 7) != 0 )
        {
          if ( (v22 & 0x28) != 0 )
            v33 |= 0x40000000000400uLL;
          else
            v33 |= 0x400uLL;
          if ( v32 == 2 )
          {
            v17 = v33 | 0x300;
            goto LABEL_37;
          }
          if ( v32 != 1 )
          {
            v14 = "mmap_desc";
            goto LABEL_34;
          }
          v34 = 520;
        }
        else
        {
          v34 = 0x40000000000604LL;
        }
        v17 = v33 | v34;
      }
LABEL_37:
      if ( v17 == -1 )
      {
        v35 = MEMORY[0x9400E648]++;
        v36 = 0x94011000 + ((unsigned __int64)v35 << 12);
        if ( MEMORY[0x9400E648] > 3u )
        {
          v14 = "init_xlation_table_inner";
LABEL_34:
          assert_fail((__int64)v14, a5, a6, a7, a8, a9, a10, a11, a12);
        }
        v17 = v36 | 3;
        result = (_QWORD *)init_xlation_table_inner();
      }
LABEL_42:
      *a3 = v17;
      a2 = v19;
      ++a3;
      continue;
    }
    result += 4;
  }
  while ( (a2 & v16) != 0 && a2 - 1 <= 0xFFFFFFFE );
  return result;
}

/* ===== nullsub_4 @ 0x9400666C size 4 ===== */
void nullsub_4()
{
  ;
}

/* ===== mmap_add_region @ 0x94006670 size 748 ===== */
unsigned __int64 __fastcall mmap_add_region(
        unsigned __int64 a1,
        unsigned __int64 a2,
        unsigned __int64 a3,
        int a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12)
{
  unsigned __int64 result; // x0
  unsigned __int64 v16; // x24
  unsigned __int64 v17; // x23
  unsigned __int64 *i; // x1
  unsigned __int64 v19; // x2
  unsigned __int64 v20; // x0
  unsigned __int64 v21; // x4
  unsigned __int64 v22; // x5
  __int64 j; // x19
  unsigned __int64 v24; // x1
  BOOL v25; // w6
  BOOL v26; // w2

  if ( (a1 & 0xFFF) != 0 )
    goto LABEL_3;
  if ( (a2 & 0xFFF) != 0 )
    goto LABEL_3;
  result = a3 & 0xFFF;
  if ( (a3 & 0xFFF) != 0 )
    goto LABEL_3;
  if ( a3 == 0 )
    return result;
  v16 = a3 - 1 + a1;
  if ( a1 >= v16 )
    goto LABEL_3;
  v17 = a2 - 1 + a3;
  if ( a2 >= v17 )
    goto LABEL_3;
  for ( i = (unsigned __int64 *)0x9400E418LL; ; i += 4 )
  {
    v19 = i[2];
    if ( v19 == 0 )
      break;
    v20 = i[1];
    v21 = *i;
    v22 = v19 + v20 - 1;
    if ( a2 >= v20 && v17 <= v22 || v20 >= a2 && v22 <= v17 )
    {
      if ( v20 - v21 != a2 - a1 || a2 == v20 && a3 == v19 )
        goto LABEL_3;
    }
    else
    {
      v25 = true;
      if ( v16 >= v21 )
        v25 = a1 > v19 + v21 - 1;
      v26 = true;
      if ( v17 >= v20 )
        v26 = a2 > v22;
      if ( !v26 || !v25 )
        goto LABEL_3;
    }
  }
  for ( j = 0x9400E418; *(_QWORD *)(j + 8) < a2 && *(_QWORD *)(j + 16) != 0; j += 32 )
    ;
  while ( *(_QWORD *)(j + 8) == a2 && *(_QWORD *)(j + 16) > a3 )
    j += 32;
  memmove_simple(j + 32, j, 0x9400E618LL - j);
  if ( MEMORY[0x9400E628] != 0 )
LABEL_3:
    assert_fail((__int64)"mmap_add_region", a5, a6, a7, a8, a9, a10, a11, a12);
  *(_QWORD *)j = a1;
  *(_QWORD *)(j + 8) = a2;
  v24 = MEMORY[0x9400E640];
  *(_QWORD *)(j + 16) = a3;
  *(_DWORD *)(j + 24) = a4;
  if ( v16 > v24 )
    MEMORY[0x9400E640] = v16;
  result = 0x9400E638;
  if ( v17 > MEMORY[0x9400E638] )
    MEMORY[0x9400E638] = v17;
  return result;
}

/* ===== mmap_add_regions @ 0x9400695C size 60 ===== */
unsigned __int64 __fastcall mmap_add_regions(
        unsigned __int64 result,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  unsigned __int64 i; // x19
  unsigned __int64 v10; // x2
  unsigned __int64 v11; // x0
  unsigned __int64 v12; // x1
  int v13; // w3

  for ( i = result; ; i += 32LL )
  {
    v10 = *(_QWORD *)(i + 16);
    if ( v10 == 0 )
      break;
    v11 = *(_QWORD *)i;
    v12 = *(_QWORD *)(i + 8);
    v13 = *(_DWORD *)(i + 24);
    result = mmap_add_region(v11, v12, v10, v13, a2, a3, a4, a5, a6, a7, a8, a9);
  }
  return result;
}

/* ===== init_xlat_table @ 0x94006998 size 104 ===== */
__int64 __fastcall init_xlat_table(
        unsigned __int64 a1,
        __int64 *a2,
        unsigned int a3,
        _QWORD *a4,
        _QWORD *a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12,
        double a13)
{
  __int64 result; // x0

  init_xlation_table_inner((_QWORD *)0x9400E418LL, a1, a2, a3, a6, a7, a8, a9, a10, a11, a12, a13);
  *a4 = MEMORY[0x9400E638];
  result = MEMORY[0x9400E640];
  *a5 = MEMORY[0x9400E640];
  return result;
}

/* ===== init_xlat_tables @ 0x94006A00 size 208 ===== */
__int64 init_xlat_tables()
{
  double v0; // d0
  double v1; // d1
  double v2; // d2
  double v3; // d3
  double v4; // d4
  double v5; // d5
  double v6; // d6
  double v7; // d7
  double v8; // d0
  double v9; // d1
  double v10; // d2
  double v11; // d3
  double v12; // d4
  double v13; // d5
  double v14; // d6
  double v15; // d7
  const char *v16; // x0
  __int64 v17; // x1
  __int64 result; // x0
  __int64 v19; // [xsp+10h] [xbp+10h] BYREF
  unsigned __int64 v20; // [xsp+18h] [xbp+18h] BYREF

  nullsub_4();
  init_xlat_table(0, (__int64 *)0x9400E660LL, 1u, &v20, &v19, v0, v1, v2, v3, v4, v5, v6, v7);
  if ( (v19 & 0xFFFF000000000000LL) != 0 )
  {
    v16 = "calc_physical_addr_size_bits";
    goto LABEL_10;
  }
  v17 = 5;
  if ( (v19 & 0xF00000000000LL) == 0 )
  {
    v17 = 4;
    if ( (v19 & 0xC0000000000LL) == 0 )
    {
      v17 = 3;
      if ( (v19 & 0x30000000000LL) == 0 )
      {
        v17 = 2;
        if ( (v19 & 0xF000000000LL) == 0 )
          v17 = (v19 & 0xF00000000LL) != 0;
      }
    }
  }
  MEMORY[0x9400E650] = v17;
  result = 0xFFFFFFFFLL;
  if ( v20 > 0xFFFFFFFF )
  {
    v16 = "init_xlat_tables";
LABEL_10:
    assert_fail((__int64)v16, v8, v9, v10, v11, v12, v13, v14, v15);
  }
  return result;
}

/* ===== enable_mmu_el3 @ 0x94006AD0 size 216 ===== */
unsigned __int64 __fastcall enable_mmu_el3(
        char a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  int StatusReg; // w1
  unsigned __int64 result; // x0

  if ( ((_ReadStatusReg(CurrentEL) >> 2) & 3) != 3 || (_ReadStatusReg(SCTLR_EL3) & 1) != 0 )
    assert_fail((__int64)"enable_mmu_el3", a2, a3, a4, a5, a6, a7, a8, a9);
  _WriteStatusReg(MAIR_EL3, 0x4404FFu);
  __asm { TLBI            ALLE3 }
  _WriteStatusReg(TCR_EL3, (MEMORY[0x9400E650] << 16) | 0x80803520LL);
  _WriteStatusReg(TTBR0_EL3, 0x9400E660);
  __dsb(0xFu);
  __isb(0xFu);
  StatusReg = _ReadStatusReg(SCTLR_EL3);
  if ( (a1 & 1) != 0 )
    result = StatusReg & 0xFFF7FFFA | 0x80001;
  else
    result = StatusReg | 0x80005u;
  _WriteStatusReg(SCTLR_EL3, result);
  __isb(0xFu);
  return result;
}

/* ===== get_non_secure_ep @ 0x94006BA8 size 8 ===== */
__int64 get_non_secure_ep()
{
  return 2667577344LL;
}

/* ===== get_secure_ep @ 0x94006BB0 size 8 ===== */
__int64 get_secure_ep()
{
  return 0;
}

/* ===== get_scr_el3_config @ 0x94006BB8 size 140 ===== */
__int64 get_scr_el3_config()
{
  unsigned __int64 v0; // x0
  double v1; // d0
  double v2; // d1
  double v3; // d2
  double v4; // d3
  double v5; // d4
  double v6; // d5
  double v7; // d6
  double v8; // d7
  int v10; // w0

  v0 = bl31_get_next_image_ep(1u);
  if ( v0 != 0 )
  {
    if ( *(unsigned __int8 *)(*(_QWORD *)(v0 + 8) + 3LL) == 234 )
    {
      if ( ((_ReadStatusReg(ID_AA64PFR0_EL1) >> 8) & 0xF) != 2 )
        printf_impl("ERROR:   EL2 is missed or can not support AArch32 state.\n", v1, v2, v3, v4, v5, v6, v7, v8);
      return (32 * (get_non_secure_ep() & 1)) | 0x1DA;
    }
    else
    {
      if ( ((_ReadStatusReg(ID_AA64PFR0_EL1) >> 8) & 0xF) != 0 )
        v10 = 2;
      else
        v10 = 1;
      return (4 * v10) | 0x3C1u;
    }
  }
  else
  {
    printf_impl("ERROR:   non_secure image missing.\n", v1, v2, v3, v4, v5, v6, v7, v8);
    return 0xFFFFFFFFLL;
  }
}

/* ===== nullsub_5 @ 0x94006C44 size 4 ===== */
void nullsub_5()
{
  ;
}

/* ===== get_mmap_regions @ 0x94006C48 size 12 ===== */
__int64 *get_mmap_regions()
{
  return qword_9400AB80;
}

/* ===== plat_setup_mmap @ 0x94006C54 size 152 ===== */
__int64 __fastcall plat_setup_mmap(
        unsigned __int64 a1,
        unsigned __int64 a2,
        unsigned __int64 a3,
        __int64 a4,
        unsigned __int64 a5,
        __int64 a6,
        unsigned __int64 a7,
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
  double v18; // d0
  double v19; // d1
  double v20; // d2
  double v21; // d3
  double v22; // d4
  double v23; // d5
  double v24; // d6
  double v25; // d7
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
  __int64 *v42; // x0
  double v43; // d0
  double v44; // d1
  double v45; // d2
  double v46; // d3
  double v47; // d4
  double v48; // d5
  double v49; // d6
  double v50; // d7

  mmap_add_region(a1, a1, a2, 10, a9, a10, a11, a12, a13, a14, a15, a16);
  mmap_add_region(a3, a3, a4 - a3, 2, v18, v19, v20, v21, v22, v23, v24, v25);
  mmap_add_region(a5, a5, a6 - a5, 34, v26, v27, v28, v29, v30, v31, v32, v33);
  mmap_add_region(a7, a7, a8 - a7, 8, v34, v35, v36, v37, v38, v39, v40, v41);
  v42 = get_mmap_regions();
  mmap_add_regions((unsigned __int64)v42, v43, v44, v45, v46, v47, v48, v49, v50);
  return init_xlat_tables();
}

/* ===== get_uart_clock @ 0x94006CEC size 12 ===== */
__int64 get_uart_clock()
{
  return 26000000;
}

/* ===== enable_mmu_thunk @ 0x94006CF8 size 4 ===== */
// attributes: thunk
unsigned __int64 __fastcall enable_mmu_thunk(
        char a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9)
{
  return enable_mmu_el3(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

/* ===== sprd_arch_secure_timer_handler @ 0x94006CFC size 308 ===== */
unsigned __int64 *__fastcall sprd_arch_secure_timer_handler(
        int a1,
        __int64 a2,
        unsigned __int64 a3,
        __int64 a4,
        double a5,
        double a6,
        double a7,
        double a8,
        double a9,
        double a10,
        double a11,
        double a12,
        __int64 a13,
        __int64 a14,
        unsigned __int64 *a15,
        char a16)
{
  __int64 v19; // x2
  int v20; // w4
  unsigned __int64 StatusReg; // x0
  const char *v22; // x0
  unsigned __int64 v23; // x1

  if ( (unsigned int)(a1 + 2147483407) > 1 || (a16 & 1) != 0 )
    goto LABEL_25;
  v19 = a1 & 0xF;
  v20 = a2 & 0xF;
  if ( (_DWORD)v19 == 1 )
  {
    if ( v20 == 2 )
    {
      StatusReg = _ReadStatusReg(CNTPS_CVAL_EL1);
    }
    else if ( v20 == 3 )
    {
      StatusReg = _ReadStatusReg(CNTPS_TVAL_EL1);
    }
    else
    {
      StatusReg = _ReadStatusReg(CNTPS_CTL_EL1);
      if ( v20 != 1 )
      {
        v22 = "ERROR:   %s: invalid reg type to read %x\n";
LABEL_21:
        v19 = a2 & 0xF;
LABEL_24:
        printf_impl(v22, a5, a6, a7, a8, a9, a10, a11, a12, "sprd_arch_secure_timer_handler", v19);
        goto LABEL_25;
      }
    }
    v23 = HIDWORD(StatusReg);
    StatusReg = (unsigned int)StatusReg;
    a15[1] = v23;
LABEL_26:
    *a15 = StatusReg;
    return a15;
  }
  if ( (_DWORD)v19 != 2 )
  {
    v22 = "ERROR:   %s: invalid access type %x\n";
    goto LABEL_24;
  }
  switch ( v20 )
  {
    case 2:
      _WriteStatusReg(CNTPS_CVAL_EL1, (unsigned int)a3 | (unsigned __int64)(a4 << 32));
      break;
    case 3:
      _WriteStatusReg(CNTPS_TVAL_EL1, a3);
      break;
    case 1:
      if ( (a2 & 0xFFFFFFF8) != 0 )
      {
        printf_impl(
          "ERROR:   %s: invalid value of ctlr %lx\n",
          a5,
          a6,
          a7,
          a8,
          a9,
          a10,
          a11,
          a12,
          "sprd_arch_secure_timer_handler",
          a2);
LABEL_25:
        StatusReg = 0xFFFFFFFFLL;
        goto LABEL_26;
      }
      _WriteStatusReg(CNTPS_CTL_EL1, a3);
      break;
    default:
      v22 = "ERROR:   %s: invalid reg type to write %x\n";
      goto LABEL_21;
  }
  *a15 = 0;
  return a15;
}

/* ===== cache_op_dcache_clean @ 0x94006E30 size 24 ===== */
__int64 cache_op_dcache_clean()
{
  __int64 result; // x0
  unsigned __int64 StatusReg; // x9
  __int64 v2; // x3
  unsigned __int64 v3; // x10

  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
  result = 1;
  StatusReg = _ReadStatusReg(CLIDR_EL1);
  v2 = 2 * ((StatusReg >> 21) & 7);
  v3 = 0;
  if ( v2 != 0 )
  {
    result = StatusReg;
    do
    {
      if ( ((StatusReg >> ((unsigned __int8)v3 + (unsigned __int8)(v3 >> 1))) & 7) >= 2 )
      {
        _WriteStatusReg(CSSELR_EL1, v3);
        __isb(0xFu);
        _ReadStatusReg(CCSIDR_EL1);
        __dsb(0xFu);
        return ((__int64 (*)(void))loc_94007D30)();
      }
      v3 += 2LL;
    }
    while ( v2 > (__int64)v3 );
    _WriteStatusReg(CSSELR_EL1, 0);
    __dsb(0xFu);
    __isb(0xFu);
  }
  return result;
}

/* ===== cache_op_dcache_invalidate @ 0x94006E48 size 24 ===== */
__int64 cache_op_dcache_invalidate()
{
  __int64 result; // x0
  unsigned __int64 StatusReg; // x9
  __int64 v2; // x3
  unsigned __int64 v3; // x10

  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
  result = 1;
  StatusReg = _ReadStatusReg(CLIDR_EL1);
  v2 = 2 * ((StatusReg >> 24) & 7);
  v3 = 0;
  if ( v2 != 0 )
  {
    result = StatusReg;
    do
    {
      if ( ((StatusReg >> ((unsigned __int8)v3 + (unsigned __int8)(v3 >> 1))) & 7) >= 2 )
      {
        _WriteStatusReg(CSSELR_EL1, v3);
        __isb(0xFu);
        _ReadStatusReg(CCSIDR_EL1);
        __dsb(0xFu);
        return ((__int64 (__fastcall *)(unsigned __int64))loc_94007D30)(StatusReg);
      }
      v3 += 2LL;
    }
    while ( v2 > (__int64)v3 );
    _WriteStatusReg(CSSELR_EL1, 0);
    __dsb(0xFu);
    __isb(0xFu);
  }
  return result;
}

/* ===== cache_op_nop @ 0x94006E60 size 8 ===== */
void cache_op_nop()
{
  ;
}

/* ===== dcache_disable_sctlr @ 0x94006E68 size 20 ===== */
void dcache_disable_sctlr()
{
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
}

/* ===== dcache_disable_sysreg @ 0x94006E7C size 24 ===== */
void dcache_disable_sysreg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFFFFFFFFFBFLL);
  __isb(0xFu);
  __dsb(0xFu);
}

/* ===== dcache_enable_sysreg @ 0x94006E94 size 20 ===== */
void dcache_enable_sysreg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) | 0x40);
  __isb(0xFu);
}

/* ===== dcache_disable @ 0x94006EA8 size 24 ===== */
void dcache_disable()
{
  dcache_disable_sctlr();
  dcache_op_lvl1(1);
  dcache_disable_sysreg();
}

/* ===== dcache_disable_all @ 0x94006EC0 size 36 ===== */
void dcache_disable_all()
{
  __int64 v0; // x0

  dcache_disable_sctlr();
  v0 = dcache_op_lvl1(1);
  nullsub_9(v0);
  dcache_op_lvl2(1);
  dcache_disable_sysreg();
}

/* ===== read_cache_config @ 0x94006EE4 size 12 ===== */
void read_cache_config()
{
  _ReadStatusReg(S3_1_C15_C2_1);
}

/* ===== icache_disable_sctlr @ 0x94006EF0 size 20 ===== */
void icache_disable_sctlr()
{
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
}

/* ===== icache_disable_sysreg @ 0x94006F04 size 24 ===== */
void icache_disable_sysreg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFFFFFFFFFBFLL);
  __isb(0xFu);
  __dsb(0xFu);
}

/* ===== set_pmcr2_el1 @ 0x94006F1C size 28 ===== */
unsigned __int64 __fastcall set_pmcr2_el1(unsigned __int64 result)
{
  if ( result <= 3 )
    _WriteStatusReg(PMCR2_EL1, _ReadStatusReg(PMCR2_EL1) | 0x1000000);
  return result;
}

/* ===== pmu_init @ 0x94006F38 size 44 ===== */
void pmu_init()
{
  unsigned __int64 StatusReg; // x0

  StatusReg = _ReadStatusReg(MIDR_EL1);
  set_pmcr2_el1(BYTE2(StatusReg) & 0xF0 | StatusReg & 0xF);
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) | 0x40);
  __isb(0xFu);
}

/* ===== icache_disable @ 0x94006F64 size 24 ===== */
void icache_disable()
{
  icache_disable_sctlr();
  dcache_op_lvl1(1);
  icache_disable_sysreg();
}

/* ===== icache_disable_all @ 0x94006F7C size 36 ===== */
void icache_disable_all()
{
  __int64 v0; // x0

  icache_disable_sctlr();
  v0 = dcache_op_lvl1(1);
  nullsub_9(v0);
  dcache_op_lvl2(1);
  icache_disable_sysreg();
}

/* ===== read_pmu_config @ 0x94006FA0 size 20 ===== */
void read_pmu_config()
{
  _ReadStatusReg(S3_1_C15_C2_1);
  _ReadStatusReg(LD_LATPROF_STS_EL1);
  _ReadStatusReg(AON_CPU_MSTALL_CTL45_EL1);
}

/* ===== disable_sctlr_c @ 0x94006FB4 size 20 ===== */
void disable_sctlr_c()
{
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
}

/* ===== set_sysreg_cache_cfg @ 0x94006FC8 size 36 ===== */
void set_sysreg_cache_cfg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFA4FFFFFFFFLL | 0x4000000000LL);
  __isb(0xFu);
  __dsb(0xBu);
}

/* ===== clear_sysreg_cache_cfg @ 0x94006FEC size 16 ===== */
void clear_sysreg_cache_cfg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFFFFFFFFFBFLL);
}

/* ===== set_osdlr @ 0x94006FFC size 20 ===== */
__int64 set_osdlr()
{
  _WriteStatusReg(OSDLR_EL1, 1u);
  __isb(0xFu);
  __dsb(0xFu);
  return 1;
}

/* ===== set_pmcr2_el1_2 @ 0x94007010 size 28 ===== */
unsigned __int64 __fastcall set_pmcr2_el1_2(unsigned __int64 result)
{
  if ( result <= 0x12 )
    _WriteStatusReg(PMCR2_EL1, _ReadStatusReg(PMCR2_EL1) | 0x10000000000000LL);
  return result;
}

/* ===== pmu_init_2 @ 0x9400702C size 44 ===== */
void pmu_init_2()
{
  unsigned __int64 StatusReg; // x0

  StatusReg = _ReadStatusReg(MIDR_EL1);
  set_pmcr2_el1_2(BYTE2(StatusReg) & 0xF0 | StatusReg & 0xF);
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) | 0x40);
  __isb(0xFu);
}

/* ===== cache_maint_disable @ 0x94007058 size 32 ===== */
__int64 cache_maint_disable()
{
  disable_sctlr_c();
  set_sysreg_cache_cfg();
  dcache_op_lvl1(1);
  clear_sysreg_cache_cfg();
  return set_osdlr();
}

/* ===== cache_maint_disable_all @ 0x94007078 size 44 ===== */
__int64 cache_maint_disable_all()
{
  __int64 v0; // x0

  disable_sctlr_c();
  set_sysreg_cache_cfg();
  v0 = dcache_op_lvl1(1);
  nullsub_9(v0);
  dcache_op_lvl2(1);
  clear_sysreg_cache_cfg();
  return set_osdlr();
}

/* ===== read_cache_maint_cfg @ 0x940070A4 size 20 ===== */
void read_cache_maint_cfg()
{
  _ReadStatusReg(S3_1_C15_C2_1);
  _ReadStatusReg(LD_LATPROF_STS_EL1);
  _ReadStatusReg(AON_CPU_MSTALL_CTL45_EL1);
}

/* ===== disable_sctlr_c_2 @ 0x940070B8 size 20 ===== */
void disable_sctlr_c_2()
{
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
}

/* ===== set_sysreg_cfg_2 @ 0x940070CC size 32 ===== */
void set_sysreg_cfg_2()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFA4FFFFFFFFLL | 0x4000000000LL);
  __isb(0xFu);
}

/* ===== set_pmcr2_3 @ 0x940070EC size 24 ===== */
void set_pmcr2_3()
{
  _WriteStatusReg(PMCR2_EL1, _ReadStatusReg(PMCR2_EL1) | 0x100000000000000LL);
  __isb(0xFu);
  __dsb(0xBu);
}

/* ===== clear_sysreg_cfg_2 @ 0x94007104 size 16 ===== */
void clear_sysreg_cfg_2()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFFFFFFFFFBFLL);
}

/* ===== set_osdlr_2 @ 0x94007114 size 20 ===== */
__int64 set_osdlr_2()
{
  _WriteStatusReg(OSDLR_EL1, 1u);
  __isb(0xFu);
  __dsb(0xFu);
  return 1;
}

/* ===== enable_sysreg_cfg @ 0x94007128 size 20 ===== */
void enable_sysreg_cfg()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) | 0x40);
  __isb(0xFu);
}

/* ===== cache_maint_disable_2 @ 0x9400713C size 36 ===== */
__int64 cache_maint_disable_2()
{
  disable_sctlr_c_2();
  set_sysreg_cfg_2();
  set_pmcr2_3();
  dcache_op_lvl1(1);
  clear_sysreg_cfg_2();
  return set_osdlr_2();
}

/* ===== cache_maint_disable_all_2 @ 0x94007160 size 48 ===== */
__int64 cache_maint_disable_all_2()
{
  __int64 v0; // x0

  disable_sctlr_c_2();
  set_sysreg_cfg_2();
  set_pmcr2_3();
  v0 = dcache_op_lvl1(1);
  nullsub_9(v0);
  dcache_op_lvl2(1);
  clear_sysreg_cfg_2();
  return set_osdlr_2();
}

/* ===== read_cache_maint_cfg_2 @ 0x94007190 size 20 ===== */
void read_cache_maint_cfg_2()
{
  _ReadStatusReg(S3_1_C15_C2_1);
  _ReadStatusReg(LD_LATPROF_STS_EL1);
  _ReadStatusReg(AON_CPU_MSTALL_CTL45_EL1);
}

/* ===== disable_sctlr_c_3 @ 0x940071A4 size 20 ===== */
void disable_sctlr_c_3()
{
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) & 0xFFFFFFFFFFFFFFFBLL);
  __isb(0xFu);
}

/* ===== disable_sysreg_cfg_3 @ 0x940071B8 size 24 ===== */
void disable_sysreg_cfg_3()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) & 0xFFFFFFFFFFFFFFBFLL);
  __isb(0xFu);
  __dsb(0xFu);
}

/* ===== enable_sysreg_cfg_3 @ 0x940071D0 size 20 ===== */
void enable_sysreg_cfg_3()
{
  _WriteStatusReg(S3_1_C15_C2_1, _ReadStatusReg(S3_1_C15_C2_1) | 0x40);
  __isb(0xFu);
}

/* ===== cache_disable_3 @ 0x940071E4 size 24 ===== */
void cache_disable_3()
{
  disable_sctlr_c_3();
  dcache_op_lvl1(1);
  disable_sysreg_cfg_3();
}

/* ===== cache_disable_all_3 @ 0x940071FC size 36 ===== */
void cache_disable_all_3()
{
  __int64 v0; // x0

  disable_sctlr_c_3();
  v0 = dcache_op_lvl1(1);
  nullsub_9(v0);
  dcache_op_lvl2(1);
  disable_sysreg_cfg_3();
}

/* ===== read_cache_cfg_3 @ 0x94007220 size 16 ===== */
void read_cache_cfg_3()
{
  _ReadStatusReg(S3_1_C15_C2_1);
  _ReadStatusReg(AON_CPU_MSTALL_CTL45_EL1);
}

/* ===== get_cpu_data_ptr @ 0x94007230 size 24 ===== */
__int64 __fastcall get_cpu_data_ptr(__int64 a1)
{
  return (get_cpu_id(a1) << 10) + 2483078336LL;
}

/* ===== set_tpidr_el3 @ 0x94007250 size 16 ===== */
__int64 __fastcall set_tpidr_el3(__int64 a1)
{
  return get_cpu_data_ptr(a1);
}

/* ===== el3_exception_handler @ 0x94007260 size 184 ===== */
void __fastcall el3_exception_handler(unsigned __int64 a1)
{
  int v1; // w15
  void (*v7)(void); // x15

  if ( (a1 & 0x40000000) == 0 )
  {
    _ReadStatusReg(SP_EL0);
    v1 = *(unsigned __int8 *)(((a1 >> 24) & 0x3F | ((unsigned __int64)((a1 & 0x80000000) != 0LL) << 6)) + 0x9400E688);
    if ( (v1 & 0x80) == 0 )
    {
      __asm { MSR             SPSel, #0 }
      v7 = *(void (**)(void))((char *)&off_9400B480 + (unsigned int)(32 * v1));
      _ReadStatusReg(SPSR_EL3);
      _ReadStatusReg(ELR_EL3);
      _ReadStatusReg(SCR_EL3);
      if ( v7 != nullptr )
      {
        v7();
        JUMPOUT(0x94007A78LL);
      }
      __asm { MSR             SPSel, #1 }
      el3_panic_stack();
    }
    JUMPOUT(0x94007A38LL);
  }
  __asm { ERET }
}

/* ===== delay_10 @ 0x94007318 size 8 ===== */
__int64 delay_10()
{
  return putc(10);
}

/* ===== dump_registers @ 0x94007320 size 76 ===== */
__int64 __fastcall dump_registers(__int64 result, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, _BYTE *a7)
{
  unsigned __int64 StatusReg; // x7
  __int64 v8; // x0
  __int64 v9; // x0

  StatusReg = _ReadStatusReg(TPIDR_EL3);
  while ( StatusReg != _ReadStatusReg(TPIDR_EL3) + 64 && *a7 != 0 )
  {
    v8 = puts(result);
    v9 = puts(v8);
    puthex(v9);
    result = delay_10();
  }
  return result;
}

/* ===== save_and_dump_regs @ 0x9400736C size 24 ===== */
__int64 __usercall save_and_dump_regs@<X0>(
        __int64 a1@<X1>,
        __int64 a2@<X2>,
        __int64 a3@<X3>,
        __int64 a4@<X4>,
        __int64 a5@<X5>,
        _BYTE *a6@<X6>,
        __int64 a7@<X8>)
{
  __int64 v7; // x9
  __int64 v8; // x10
  __int64 v9; // x11
  __int64 v10; // x12
  __int64 v11; // x13
  __int64 v12; // x14
  __int64 v13; // x15
  _QWORD *StatusReg; // x0

  StatusReg = (_QWORD *)_ReadStatusReg(TPIDR_EL3);
  *StatusReg = a7;
  StatusReg[1] = v7;
  StatusReg[2] = v8;
  StatusReg[3] = v9;
  StatusReg[4] = v10;
  StatusReg[5] = v11;
  StatusReg[6] = v12;
  StatusReg[7] = v13;
  return dump_registers((__int64)StatusReg, a1, a2, a3, a4, a5, a6);
}

/* ===== el3_panic_stack @ 0x94007384 size 40 ===== */
void __fastcall __noreturn el3_panic_stack(
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
  _QWORD *v9; // x0

  v9 = (_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 24);
  _WriteStatusReg(TPIDR_EL3, (unsigned __int64)v9);
  v9[1] = a2;
  *v9 = &a9;
  JUMPOUT(0x94007400LL);
}

/* ===== el3_panic_stack2 @ 0x940073AC size 40 ===== */
void __fastcall __noreturn el3_panic_stack2(
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
  _QWORD *v9; // x0

  v9 = (_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 24);
  _WriteStatusReg(TPIDR_EL3, (unsigned __int64)v9);
  v9[1] = a2;
  *v9 = &a9;
  JUMPOUT(0x94007400LL);
}

/* ===== set_tpidr_el3_cpu @ 0x940075F4 size 20 ===== */
unsigned __int64 __fastcall set_tpidr_el3_cpu(__int64 a1)
{
  __int64 v1; // x0
  unsigned __int64 result; // x0

  v1 = get_cpu_id(a1);
  result = get_cpu_context_ptr(v1);
  _WriteStatusReg(TPIDR_EL3, result);
  return result;
}

/* ===== get_cpu_context_ptr @ 0x94007608 size 12 ===== */
__int64 __fastcall get_cpu_context_ptr(__int64 a1)
{
  return (a1 << 7) + 2483087168LL;
}

/* ===== cpu_init_early @ 0x94007614 size 52 ===== */
__int64 cpu_init_early()
{
  __int64 v0; // x0
  __int64 result; // x0
  __int64 (*v2)(void); // x2
  __int64 v3; // x0
  __int64 v4; // x0
  __int64 v5; // x0
  unsigned __int64 v6; // x6
  unsigned __int64 v7; // x4
  unsigned __int64 i; // x5
  unsigned __int64 v9; // x5
  unsigned __int64 v10; // x6

  v0 = nullsub_6();
  result = get_cpu_ops(v0);
  if ( result == 0 )
  {
    v3 = get_pc();
    if ( v3 != 0 )
    {
      v4 = puts(v3);
      v5 = puts(v4);
      puts(v5);
      if ( (v6 & 0xFFFFFFFFFFFF0000LL) == 0 )
      {
        v7 = v6;
        for ( i = 10000; i != 0; i = v9 / v10 )
          putc(v7 / i + 48);
      }
    }
    while ( 1 )
      ;
  }
  v2 = *(__int64 (**)(void))(result + 8);
  if ( v2 != nullptr )
    return v2();
  return result;
}

/* ===== cpu_reset_handler @ 0x94007648 size 36 ===== */
__int64 __fastcall cpu_reset_handler(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v5; // x0
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 v9; // x0
  unsigned __int64 v10; // x6
  unsigned __int64 v11; // x4
  unsigned __int64 i; // x5
  unsigned __int64 v13; // x5
  unsigned __int64 v14; // x6

  v5 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 16);
  if ( v5 == 0 )
  {
    v7 = get_pc("lib/cpus/aarch64/cpu_helpers.S", 87, a3, a4, a5, "lib/cpus/aarch64/cpu_helpers.S", 87);
    if ( v7 != 0 )
    {
      v8 = puts(v7);
      v9 = puts(v8);
      puts(v9);
      if ( (v10 & 0xFFFFFFFFFFFF0000LL) == 0 )
      {
        v11 = v10;
        for ( i = 10000; i != 0; i = v13 / v14 )
          putc(v11 / i + 48);
      }
    }
    while ( 1 )
      ;
  }
  return (*(__int64 (**)(void))(v5 + 16))();
}

/* ===== cpu_pwr_down_handler @ 0x9400766C size 36 ===== */
__int64 __fastcall cpu_pwr_down_handler(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v5; // x0
  __int64 v7; // x0
  __int64 v8; // x0
  __int64 v9; // x0
  unsigned __int64 v10; // x6
  unsigned __int64 v11; // x4
  unsigned __int64 i; // x5
  unsigned __int64 v13; // x5
  unsigned __int64 v14; // x6

  v5 = *(_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 16);
  if ( v5 == 0 )
  {
    v7 = get_pc("lib/cpus/aarch64/cpu_helpers.S", 106, a3, a4, a5, "lib/cpus/aarch64/cpu_helpers.S", 106);
    if ( v7 != 0 )
    {
      v8 = puts(v7);
      v9 = puts(v8);
      puts(v9);
      if ( (v10 & 0xFFFFFFFFFFFF0000LL) == 0 )
      {
        v11 = v10;
        for ( i = 10000; i != 0; i = v13 / v14 )
          putc(v11 / i + 48);
      }
    }
    while ( 1 )
      ;
  }
  return (*(__int64 (**)(void))(v5 + 24))();
}

/* ===== cpu_pwr_domain_suspend_handler @ 0x940076C4 size 32 ===== */
__int64 __fastcall cpu_pwr_domain_suspend_handler(__int64 a1)
{
  __int64 result; // x0
  __int64 (*v2)(void); // x2

  result = get_cpu_ops(a1);
  if ( result != 0 )
  {
    v2 = *(__int64 (**)(void))(result + 32);
    if ( v2 != nullptr )
      return v2();
  }
  return result;
}

/* ===== get_cpu_ops @ 0x940076E4 size 60 ===== */
__int64 *get_cpu_ops()
{
  __int64 *v0; // x4
  __int64 *result; // x0
  unsigned __int64 v2; // x2
  __int64 v3; // t1

  v0 = qword_9400B528;
  result = nullptr;
  v2 = _ReadStatusReg(MIDR_EL1) & 0xFF00FFF0;
  while ( v0 != qword_9400B640 )
  {
    v3 = *v0;
    v0 += 5;
    if ( (v3 & 0xFF00FFF0) == (_DWORD)v2 )
      return v0 - 5;
  }
  return result;
}

/* ===== spin_lock @ 0x94007720 size 32 ===== */
unsigned int *__fastcall spin_lock(unsigned int *result)
{
  unsigned int v1; // w1

  __sevl();
LABEL_2:
  __wfe();
  do
  {
    v1 = __ldaxr(result);
    if ( v1 != 0 )
      goto LABEL_2;
  }
  while ( __stxr(1u, result) != 0 );
  return result;
}

/* ===== spin_unlock @ 0x94007740 size 8 ===== */
unsigned int *__fastcall spin_unlock(unsigned int *result)
{
  atomic_store(0, result);
  return result;
}

/* ===== cpu_context_save @ 0x94007748 size 76 ===== */
__int64 __fastcall cpu_context_save(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v5; // x0
  __int64 v6; // x19
  _QWORD v8[2]; // [xsp+0h] [xbp-20h] BYREF

  if ( (_DWORD)a1 != 0 )
    v5 = cpu_pwr_down_handler(a1, a2, a3, a4, a5);
  else
    v5 = cpu_reset_handler(a1, a2, a3, a4, a5);
  v6 = get_cpu_data_ptr(v5);
  dcache_clean_invalidate(v8, v6 - (_QWORD)v8);
  return dcache_invalidate(v6 - 1024, (char *)&v8[128] - v6);
}

/* ===== cpu_context_restore @ 0x94007794 size 52 ===== */
void __fastcall cpu_context_restore(__int64 a1)
{
  __int64 v1; // x0
  _QWORD v2[2]; // [xsp+0h] [xbp-10h] BYREF

  __dmb(0xEu);
  v1 = get_cpu_data_ptr(a1);
  dcache_invalidate(v2, v1 - (_QWORD)v2);
  _WriteStatusReg(SCTLR_EL3, _ReadStatusReg(SCTLR_EL3) | 4);
  __isb(0xFu);
}

/* ===== cpu_power_down @ 0x940077C8 size 12 ===== */
void __noreturn cpu_power_down()
{
  __dsb(0xFu);
  __wfi();
  halt();
}

/* ===== el1_sysregs_restore @ 0x94007888 size 180 ===== */
void __fastcall el1_sysregs_restore(unsigned __int64 *a1)
{
  unsigned __int64 v1; // x10
  unsigned __int64 v2; // x16
  unsigned __int64 v3; // x9
  unsigned __int64 v4; // x11
  unsigned __int64 v5; // x13
  unsigned __int64 v6; // x15
  unsigned __int64 v7; // x17
  unsigned __int64 v8; // x10
  unsigned __int64 v9; // x14
  unsigned __int64 v10; // x16
  unsigned __int64 v11; // x9
  unsigned __int64 v12; // x12
  unsigned __int64 v13; // x14
  unsigned __int64 v14; // x16

  v1 = a1[1];
  _WriteStatusReg(SPSR_EL1, *a1);
  _WriteStatusReg(ELR_EL1, v1);
  v2 = a1[3];
  _WriteStatusReg(SCTLR_EL1, a1[2]);
  _WriteStatusReg(ACTLR_EL1, v2);
  v3 = a1[5];
  _WriteStatusReg(CPACR_EL1, a1[4]);
  _WriteStatusReg(CSSELR_EL1, v3);
  v4 = a1[7];
  _WriteStatusReg(SP_EL1, a1[6]);
  _WriteStatusReg(ESR_EL1, v4);
  v5 = a1[9];
  _WriteStatusReg(TTBR0_EL1, a1[8]);
  _WriteStatusReg(TTBR1_EL1, v5);
  v6 = a1[11];
  _WriteStatusReg(MAIR_EL1, a1[10]);
  _WriteStatusReg(AMAIR_EL1, v6);
  v7 = a1[13];
  _WriteStatusReg(TCR_EL1, a1[12]);
  _WriteStatusReg(TPIDR_EL1, v7);
  v8 = a1[15];
  _WriteStatusReg(TPIDR_EL0, a1[14]);
  _WriteStatusReg(TPIDRRO_EL0, v8);
  v9 = a1[17];
  _WriteStatusReg(PAR_EL1, a1[16]);
  _WriteStatusReg(FAR_EL1, v9);
  v10 = a1[19];
  _WriteStatusReg(AFSR0_EL1, a1[18]);
  _WriteStatusReg(AFSR1_EL1, v10);
  v11 = a1[21];
  _WriteStatusReg(CONTEXTIDR_EL1, a1[20]);
  _WriteStatusReg(VBAR_EL1, v11);
  v12 = a1[23];
  _WriteStatusReg(SPSR_abt, a1[22]);
  _WriteStatusReg(SPSR_und, v12);
  v13 = a1[25];
  _WriteStatusReg(SPSR_irq, a1[24]);
  _WriteStatusReg(SPSR_fiq, v13);
  v14 = a1[27];
  _WriteStatusReg(DACR32_EL2, a1[26]);
  _WriteStatusReg(IFSR32_EL2, v14);
  _WriteStatusReg(FPEXC32_EL2, a1[28]);
}

/* ===== fpregs_context_save @ 0x9400793C size 84 ===== */
__int64 __fastcall fpregs_context_save(
        __int64 result,
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
  *(_QWORD *)(result + 512) = _ReadStatusReg(FPSR);
  *(_QWORD *)(result + 520) = _ReadStatusReg(FPCR);
  return result;
}

/* ===== fpregs_context_restore @ 0x94007990 size 84 ===== */
long double __fastcall fpregs_context_restore(__int64 a1)
{
  long double result; // q0

  result = *(long double *)a1;
  _WriteStatusReg(FPSR, *(_QWORD *)(a1 + 512));
  _WriteStatusReg(FPCR, *(_QWORD *)(a1 + 520));
  return result;
}

/* ===== read_sp_el0 @ 0x940079E4 size 72 ===== */
void __spoils<> read_sp_el0()
{
  _ReadStatusReg(SP_EL0);
}

/* ===== setup_eret_context @ 0x94007A9C size 84 ===== */
_QWORD *__usercall setup_eret_context@<X0>(
        _QWORD *result@<X0>,
        __int64 a2@<X1>,
        __int64 a3@<X2>,
        __int64 a4@<X3>,
        __int64 a5@<X4>,
        _QWORD *a6@<X8>)
{
  _QWORD *v6; // x8
  __int64 v7; // [xsp+0h] [xbp-70h] BYREF
  _QWORD *v8; // [xsp+60h] [xbp-10h]

  v8 = a6;
  *result = &v7;
  v6 = v8;
  *v8 = a2;
  v6[1] = a3;
  v6[2] = a4;
  v6[3] = a5;
  return result;
}

/* ===== setup_panic_context @ 0x94007AF0 size 40 ===== */
_QWORD *__usercall setup_panic_context@<X0>(_QWORD *result@<X0>, __int64 a2@<X1>, __int64 a3@<X8>)
{
  __int64 v3; // x1

  *(_QWORD *)(a2 - 16) = a3;
  *(_QWORD *)(a2 - 8) = 0;
  v3 = a2 - 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = 0;
  v3 -= 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = 0;
  v3 -= 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = 0;
  v3 -= 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = 0;
  v3 -= 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = 0;
  v3 -= 16;
  *(_QWORD *)(v3 - 16) = 0;
  *(_QWORD *)(v3 - 8) = &loc_94007A78;
  *result = v3 - 16;
  return result;
}

/* ===== puts @ 0x94007B70 size 24 ===== */
__int64 __fastcall puts(__int64 a1, __int64 a2, __int64 a3, __int64 a4, _BYTE *a5)
{
  __int64 result; // x0

  while ( 1 )
  {
    result = (unsigned __int8)*a5;
    if ( *a5 == 0 )
      break;
    putc(result);
  }
  return result;
}

/* ===== puthex @ 0x94007B88 size 48 ===== */
__int64 __fastcall puthex(__int64 a1, __int64 a2, __int64 a3, __int64 a4, unsigned __int64 a5)
{
  __int64 v5; // x5
  unsigned __int64 v6; // x0
  __int64 result; // x0

  LOBYTE(v5) = 64;
  do
  {
    v6 = (a5 >> ((unsigned __int8)v5 - 4)) & 0xF;
    if ( v6 >= 0xA )
      v6 += 39LL;
    result = putc(v6 + 48);
  }
  while ( v5 != 0 );
  return result;
}

/* ===== panic @ 0x94007BB8 size 64 ===== */
void __fastcall __noreturn panic(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        __int64 a8,
        char a9)
{
  _QWORD *v14; // x0
  _QWORD *StatusReg; // x0
  __int64 v16; // x0
  __int64 v17; // x1
  __int64 v18; // x2
  __int64 v19; // x3
  __int64 v20; // x0
  __int64 v21; // x1
  __int64 v22; // x2
  __int64 v23; // x3
  __int64 v24; // x0
  __int64 v25; // x7
  __int64 v26; // x1
  __int64 v27; // x2
  __int64 v28; // x3
  __int64 v29; // x4
  __int64 v30; // x5
  __int64 v31; // x1
  __int64 v32; // x2
  __int64 v33; // x3
  __int64 v34; // x4
  __int64 v35; // x5
  _BYTE *v36; // x6
  __int64 v37; // x8
  _QWORD *v38; // x0
  __int64 v39; // x16
  __int64 v40; // x17
  __int64 v41; // x1
  __int64 v42; // x2
  __int64 v43; // x3
  __int64 v44; // x4
  __int64 v45; // x5
  _BYTE *v46; // x6
  _QWORD *v47; // x0
  __int64 v48; // x1
  __int64 v49; // x2
  __int64 v50; // x3
  __int64 v51; // x4
  __int64 v52; // x5
  _BYTE *v53; // x6
  __int64 v54; // x8
  __int64 v55; // x1
  __int64 v56; // x2
  __int64 v57; // x3
  __int64 v58; // x4
  __int64 v59; // x5
  __int64 v60; // x8
  __int64 v61; // x1
  __int64 v62; // x2
  __int64 v63; // x3
  __int64 v64; // x4
  __int64 v65; // x5
  _BYTE *v66; // x6
  __int64 v67; // x8
  __int64 v68; // x1
  __int64 v69; // x2
  __int64 v70; // x3
  __int64 v71; // x4
  __int64 v72; // x5
  __int64 v73; // x8
  __int64 v74; // x1
  __int64 v75; // x2
  __int64 v76; // x3
  __int64 v77; // x4
  __int64 v78; // x5
  _BYTE *v79; // x6
  __int64 v80; // x8
  __int64 v81; // x1
  __int64 v82; // x2
  __int64 v83; // x3
  __int64 v84; // x4
  __int64 v85; // x5
  _BYTE *v86; // x6
  __int64 v87; // x8
  __int64 v88; // x1
  __int64 v89; // x2
  __int64 v90; // x3
  __int64 v91; // x4
  __int64 v92; // x5
  _BYTE *v93; // x6
  __int64 v94; // x8
  __int64 v95; // x1
  __int64 v96; // x2
  __int64 v97; // x3
  __int64 v98; // x4
  __int64 v99; // x5
  _BYTE *v100; // x6
  __int64 v101; // x0
  __int64 v102; // x1
  __int64 v103; // x2
  __int64 v104; // x3
  __int64 v105; // x4
  __int64 v106; // x5
  _BYTE *v107; // x6
  __int64 v108; // x8
  __int64 v109; // x1
  __int64 v110; // x2
  __int64 v111; // x3
  __int64 v112; // x4
  __int64 v113; // x5
  __int64 v114; // x8
  __int64 v115; // x0
  __int64 v116; // x1
  __int64 v117; // x2
  __int64 v118; // x3
  __int64 v119; // x0
  __int64 v120; // x1
  __int64 v121; // x2
  __int64 v122; // x3
  __int64 v123; // x7
  __int64 v124; // x16
  __int64 v125; // x0
  __int64 v126; // x1
  __int64 v127; // x2
  __int64 v128; // x3
  __int64 v129; // x0
  unsigned __int64 *v130; // x7
  __int64 v131; // x1
  __int64 v132; // x2
  __int64 v133; // x3
  __int64 v134; // x0
  __int64 v135; // x1
  __int64 v136; // x2
  __int64 v137; // x3
  __int64 v138; // x18
  __int64 v139; // x19
  __int64 v140; // x20
  __int64 v141; // x21
  __int64 v142; // x22
  __int64 v143; // x23
  __int64 v144; // x24
  __int64 v145; // x25
  __int64 v146; // x26
  __int64 v147; // x27
  __int64 v148; // x28
  __int64 v149; // x29
  __int64 v150; // x30
  __int64 v151; // x0
  __int64 v152; // x1
  __int64 v153; // x2
  __int64 v154; // x3
  __int64 v155; // x0
  __int64 v156; // x6
  __int64 v157; // x1
  __int64 v158; // x2
  __int64 v159; // x3

  if ( ((_ReadStatusReg(CurrentEL) >> 2) & 3) != 3 )
  {
    v151 = get_pc(a1, a2, a3, a4, a5, a6, v150);
    if ( v151 != 0 )
    {
      v155 = puts(v151, v152, v153, v154, "PANIC at PC : 0x");
      v151 = puthex(v155, v157, v158, v159, v156 - 4);
    }
    halt(v151);
  }
  __asm { MSR             SPSel, #1 }
  v14 = (_QWORD *)(_ReadStatusReg(TPIDR_EL3) + 24);
  _WriteStatusReg(TPIDR_EL3, (unsigned __int64)v14);
  v14[1] = a2;
  *v14 = &a9;
  StatusReg = (_QWORD *)_ReadStatusReg(TPIDR_EL3);
  StatusReg[2] = a3;
  StatusReg[3] = a4;
  StatusReg[4] = a5;
  StatusReg[5] = a6;
  StatusReg[6] = a7;
  StatusReg[7] = v150;
  v16 = get_pc(StatusReg, &a9, a3, a4, a5, a6, a7);
  if ( v16 != 0 )
  {
    puts(v16, v17, v18, v19, &a9);
    v20 = _ReadStatusReg(TPIDR_EL3);
    puthex(v20, v21, v22, v23, *(_QWORD *)(v20 + 56));
    delay_10();
    v24 = _ReadStatusReg(TPIDR_EL3);
    *(_QWORD *)(v24 + 56) = v25;
    dump_registers(v24, v26, v27, v28, v29, v30, "x0");
    save_and_dump_regs(v31, v32, v33, v34, v35, v36, v37);
    v38 = (_QWORD *)_ReadStatusReg(TPIDR_EL3);
    *v38 = v39;
    v38[1] = v40;
    v38[2] = v138;
    v38[3] = v139;
    v38[4] = v140;
    v38[5] = v141;
    v38[6] = v142;
    v38[7] = v143;
    dump_registers((__int64)v38, v41, v42, v43, v44, v45, v46);
    v47 = (_QWORD *)_ReadStatusReg(TPIDR_EL3);
    *v47 = v144;
    v47[1] = v145;
    v47[2] = v146;
    v47[3] = v147;
    v47[4] = v148;
    v47[5] = v149;
    dump_registers((__int64)v47, v48, v49, v50, v51, v52, v53);
    v54 = _ReadStatusReg(SCR_EL3);
    _ReadStatusReg(SCTLR_EL3);
    _ReadStatusReg(CPTR_EL3);
    _ReadStatusReg(TCR_EL3);
    _ReadStatusReg(DAIF);
    _ReadStatusReg(MAIR_EL3);
    _ReadStatusReg(SPSR_EL3);
    _ReadStatusReg(ELR_EL3);
    save_and_dump_regs(v55, v56, v57, v58, v59, "scr_el3", v54);
    v60 = _ReadStatusReg(TTBR0_EL3);
    _ReadStatusReg(ESR_EL3);
    _ReadStatusReg(FAR_EL3);
    save_and_dump_regs(v61, v62, v63, v64, v65, v66, v60);
    v67 = _ReadStatusReg(SPSR_EL1);
    _ReadStatusReg(ELR_EL1);
    _ReadStatusReg(SPSR_abt);
    _ReadStatusReg(SPSR_und);
    _ReadStatusReg(SPSR_irq);
    _ReadStatusReg(SPSR_fiq);
    _ReadStatusReg(SCTLR_EL1);
    _ReadStatusReg(ACTLR_EL1);
    save_and_dump_regs(v68, v69, v70, v71, v72, "spsr_el1", v67);
    v73 = _ReadStatusReg(CPACR_EL1);
    _ReadStatusReg(CSSELR_EL1);
    _ReadStatusReg(SP_EL1);
    _ReadStatusReg(ESR_EL1);
    _ReadStatusReg(TTBR0_EL1);
    _ReadStatusReg(TTBR1_EL1);
    _ReadStatusReg(MAIR_EL1);
    _ReadStatusReg(AMAIR_EL1);
    save_and_dump_regs(v74, v75, v76, v77, v78, v79, v73);
    v80 = _ReadStatusReg(TCR_EL1);
    _ReadStatusReg(TPIDR_EL1);
    _ReadStatusReg(TPIDR_EL0);
    _ReadStatusReg(TPIDRRO_EL0);
    _ReadStatusReg(DACR32_EL2);
    _ReadStatusReg(IFSR32_EL2);
    _ReadStatusReg(PAR_EL1);
    _ReadStatusReg(MPIDR_EL1);
    save_and_dump_regs(v81, v82, v83, v84, v85, v86, v80);
    v87 = _ReadStatusReg(AFSR0_EL1);
    _ReadStatusReg(AFSR1_EL1);
    _ReadStatusReg(CONTEXTIDR_EL1);
    _ReadStatusReg(VBAR_EL1);
    _ReadStatusReg(CNTP_CTL_EL0);
    _ReadStatusReg(CNTP_CVAL_EL0);
    _ReadStatusReg(CNTV_CTL_EL0);
    _ReadStatusReg(CNTV_CVAL_EL0);
    save_and_dump_regs(v88, v89, v90, v91, v92, v93, v87);
    v94 = _ReadStatusReg(CNTKCTL_EL1);
    _ReadStatusReg(FPEXC32_EL2);
    _ReadStatusReg(SP_EL0);
    _ReadStatusReg(ISR_EL1);
    v101 = save_and_dump_regs(v95, v96, v97, v98, v99, v100, v94);
    cpu_pwr_domain_suspend_handler(v101);
    save_and_dump_regs(v102, v103, v104, v105, v106, v107, v108);
    if ( ((_ReadStatusReg(ID_AA64PFR0_EL1) >> 24) & 0xF) == 1 && (_ReadStatusReg(ICC_SRE_EL3) & 1) != 0 )
    {
      v114 = _ReadStatusReg(ICC_HPPIR0_EL1);
      _ReadStatusReg(ICC_HPPIR1_EL1);
      _ReadStatusReg(ICC_CTLR_EL3);
      v115 = save_and_dump_regs(v109, v110, v111, v112, v113, "icc_hppir0_el1", v114);
    }
    else
    {
      v115 = save_and_dump_regs(v109, v110, v111, v112, v113, "gicc_hppir", MEMORY[0x12002018]);
    }
    v119 = puts(v115, v116, v117, v118, "gicd_ispendr regs (Offsets 0x200 - 0x278)\n");
    while ( v123 - v124 != 640 )
    {
      v125 = puthex(v119, v120, v121, v122, v123 - v124);
      v129 = puts(v125, v126, v127, v128, ":\t\t0x");
      v134 = puthex(v129, v131, v132, v133, *v130);
      v119 = puts(v134, v135, v136, v137, "\n");
    }
    halt(v119);
  }
  ((void (__noreturn *)(void))halt)();
}

/* ===== dcache_clean_invalidate @ 0x94007BF8 size 52 ===== */
unsigned __int64 __fastcall dcache_clean_invalidate(__int64 a1, __int64 a2)
{
  __int64 v2; // x2
  unsigned __int64 v3; // x1
  unsigned __int64 result; // x0

  v2 = 4LL << (((unsigned int)_ReadStatusReg(CTR_EL0) >> 16) & 0xF);
  v3 = a1 + a2;
  result = a1 & ~(v2 - 1);
  do
  {
    __asm { DC              CIVAC, X0 }
    result += v2;
  }
  while ( result < v3 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_clean @ 0x94007C2C size 52 ===== */
unsigned __int64 __fastcall dcache_clean(__int64 a1, __int64 a2)
{
  __int64 v2; // x2
  unsigned __int64 v3; // x1
  unsigned __int64 result; // x0

  v2 = 4LL << (((unsigned int)_ReadStatusReg(CTR_EL0) >> 16) & 0xF);
  v3 = a1 + a2;
  result = a1 & ~(v2 - 1);
  do
  {
    __asm { DC              CVAC, X0 }
    result += v2;
  }
  while ( result < v3 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_invalidate @ 0x94007C60 size 52 ===== */
unsigned __int64 __fastcall dcache_invalidate(__int64 a1, __int64 a2)
{
  __int64 v2; // x2
  unsigned __int64 v3; // x1
  unsigned __int64 result; // x0

  v2 = 4LL << (((unsigned int)_ReadStatusReg(CTR_EL0) >> 16) & 0xF);
  v3 = a1 + a2;
  result = a1 & ~(v2 - 1);
  do
  {
    __asm { DC              IVAC, X0 }
    result += v2;
  }
  while ( result < v3 );
  __dsb(0xFu);
  return result;
}

/* ===== dcache_op_by_range @ 0x94007D50 size 32 ===== */
void __fastcall dcache_op_by_range(__int64 a1, __int64 a2, char a3, __int64 a4, __int64 a5, __int64 a6, int a7)
{
  __int64 v7; // x9
  __int64 v8; // x16
  int v9; // w17
  int v10; // w7
  bool v15; // cc

  while ( 1 )
  {
    v10 = a7 << a3;
    do
    {
      __asm { DC              CSW, X11 }
      _VF = __OFSUB__(v10, v9);
      v10 -= v9;
    }
    while ( v10 < 0 == _VF );
    v15 = v7 < v8;
    v7 -= v8;
    if ( v15 )
      JUMPOUT(0x94007CF4LL);
  }
}

/* ===== dcache_op_lvl1 @ 0x94007D98 size 16 ===== */
__int64 __fastcall dcache_op_lvl1(__int64 a1)
{
  __int64 (__fastcall *v1)(unsigned __int64); // x14
  __int64 result; // x0
  unsigned __int64 StatusReg; // x9
  signed __int64 v4; // x10

  StatusReg = _ReadStatusReg(CLIDR_EL1);
  v4 = 0;
  v1 = (__int64 (__fastcall *)(unsigned __int64))((char *)sub_94007D10 + 32 * a1);
  result = StatusReg;
  do
  {
    if ( ((StatusReg >> ((unsigned __int8)v4 + (unsigned __int8)((unsigned __int64)v4 >> 1))) & 7) >= 2 )
    {
      _WriteStatusReg(CSSELR_EL1, v4);
      __isb(0xFu);
      _ReadStatusReg(CCSIDR_EL1);
      __dsb(0xFu);
      return v1(StatusReg);
    }
    v4 += 2LL;
  }
  while ( v4 < 2 );
  _WriteStatusReg(CSSELR_EL1, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}

/* ===== dcache_op_lvl2 @ 0x94007DA8 size 16 ===== */
__int64 __fastcall dcache_op_lvl2(__int64 a1)
{
  __int64 (__fastcall *v1)(unsigned __int64); // x14
  __int64 result; // x0
  unsigned __int64 StatusReg; // x9
  signed __int64 v4; // x10

  StatusReg = _ReadStatusReg(CLIDR_EL1);
  v4 = 2;
  v1 = (__int64 (__fastcall *)(unsigned __int64))((char *)sub_94007D10 + 32 * a1);
  result = StatusReg;
  do
  {
    if ( ((StatusReg >> ((unsigned __int8)v4 + (unsigned __int8)((unsigned __int64)v4 >> 1))) & 7) >= 2 )
    {
      _WriteStatusReg(CSSELR_EL1, v4);
      __isb(0xFu);
      _ReadStatusReg(CCSIDR_EL1);
      __dsb(0xFu);
      return v1(StatusReg);
    }
    v4 += 2LL;
  }
  while ( v4 < 4 );
  _WriteStatusReg(CSSELR_EL1, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}

/* ===== zeromem @ 0x94007DB8 size 64 ===== */
char *__fastcall zeromem(char *result, __int64 a2, __int64 a3, __int64 a4, __int64 a5)
{
  __int64 v5; // x0
  __int64 v6; // x1
  __int64 v7; // x2
  __int64 v8; // x3
  __int64 v9; // x0
  __int64 v10; // x1
  __int64 v11; // x2
  __int64 v12; // x3
  _BYTE *v13; // x5
  __int64 v14; // x0
  __int64 v15; // x1
  __int64 v16; // x2
  __int64 v17; // x3
  unsigned __int64 v18; // x6
  unsigned __int64 v19; // x4
  unsigned __int64 i; // x5
  unsigned __int64 v21; // x5
  unsigned __int64 v22; // x6
  char *v23; // x2

  if ( ((unsigned __int8)result & 0xF) != 0 )
  {
    v5 = get_pc("lib/aarch64/misc_helpers.S", 88, a3, a4, a5, "lib/aarch64/misc_helpers.S", 88);
    if ( v5 != 0 )
    {
      v9 = puts(v5, v6, v7, v8, "ASSERT: File ");
      v14 = puts(v9, v10, v11, v12, v13);
      puts(v14, v15, v16, v17, " Line ");
      if ( (v18 & 0xFFFFFFFFFFFF0000LL) == 0 )
      {
        v19 = v18;
        for ( i = 10000; i != 0; i = v21 / v22 )
          putc(v19 / i + 48);
      }
    }
    while ( 1 )
      ;
  }
  v23 = &result[a2];
  while ( v23 - result >= 16 )
  {
    *(_QWORD *)result = 0;
    *((_QWORD *)result + 1) = 0;
    result += 16;
  }
  while ( result != v23 )
    *result++ = 0;
  return result;
}

/* ===== nullsub_6 @ 0x94007DF8 size 4 ===== */
void nullsub_6()
{
  ;
}

/* ===== nullsub_9 @ 0x94007DFC size 4 ===== */
void nullsub_9()
{
  ;
}

/* ===== halt @ 0x94007E00 size 8 ===== */
void __noreturn halt()
{
  while ( 1 )
    __wfi();
}

/* ===== get_zero @ 0x94007E08 size 8 ===== */
__int64 get_zero()
{
  return 0;
}

/* ===== get_boot_arg @ 0x94007E10 size 24 ===== */
__int64 get_boot_arg()
{
  __int64 result; // x0

  result = MEMORY[0x9401F000];
  if ( MEMORY[0x9401F000] == 0 )
    halt();
  return result;
}

/* ===== get_cpu_id @ 0x94007E28 size 24 ===== */
unsigned __int64 get_cpu_id()
{
  unsigned __int16 StatusReg; // w0

  StatusReg = _ReadStatusReg(MPIDR_EL1);
  return (unsigned __int8)StatusReg + ((unsigned __int64)(StatusReg & 0xFF00) >> 6);
}

/* ===== get_pc @ 0x94007E40 size 24 ===== */
void get_pc()
{
  JUMPOUT(0x94007E88LL);
}

/* ===== putc @ 0x94007E58 size 8 ===== */
void putc()
{
  JUMPOUT(0x94007EB0LL);
}

/* ===== nullsub_7 @ 0x94007E60 size 4 ===== */
void nullsub_7()
{
  ;
}

/* ===== uart_init @ 0x94007E64 size 20 ===== */
// write access to const memory has been detected, the output may be wrong!
__int64 __fastcall uart_init(__int64 result)
{
  if ( result != 0 )
  {
    qword_9400C088 = result;
    JUMPOUT(0x94007E88LL);
  }
  return result;
}

/* ===== putc_hw @ 0x94007E78 size 124 ===== */
__int64 putc_hw()
{
  return 0xFFFFFFFFLL;
}


// END total=276 ok=276 fail=0
