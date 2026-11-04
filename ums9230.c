/* Minimal UMS9230 (T606) machine for running the trustos TEE.
 * RAM @0x80000000, PL011 UART @0x200b0000, crypto-engine MMIO @0x54000000 (log-only).
 */
#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/units.h"
#include "hw/core/boards.h"
#include "hw/char/pl011.h"
#include "hw/core/sysbus.h"
#include "system/address-spaces.h"
#include "system/memory.h"
#include "hw/core/cpu.h"
#include "target/arm/cpu.h"
#include "target/arm/cpu-features.h"
#include "system/reset.h"
#include "hw/core/loader.h"
#include "hw/intc/arm_gicv3_common.h"
#include "qobject/qlist.h"
#include "hw/core/qdev-properties.h"

#define UMS9230_RAM_BASE  0x80000000ull
#define UMS9230_UART_BASE 0x200b0000ull
#define UMS9230_CE_BASE   0x54000000ull
#define UMS9230_CE_SIZE   0x1000000ull
#define TRUSTOS_LOAD_ADDR 0x80000000ull

/* ---- crypto engine: log-only MMIO device ---- */
#define TYPE_UMS9230_CE "ums9230-ce"
OBJECT_DECLARE_SIMPLE_TYPE(Ums9230CEState, UMS9230_CE)

struct Ums9230CEState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
};

static uint64_t ce_read(void *opaque, hwaddr offset, unsigned size)
{
    fprintf(stderr, "[CE READ  off=0x%lx size=%u]\n", (unsigned long)offset, size);
    return 0;
}

static void ce_write(void *opaque, hwaddr offset, uint64_t value, unsigned size)
{
    fprintf(stderr, "[CE WRITE off=0x%lx size=%u val=0x%lx]\n",
            (unsigned long)offset, size, (unsigned long)value);
}

static const MemoryRegionOps ce_ops = {
    .read = ce_read,
    .write = ce_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void ce_realize(DeviceState *dev, Error **errp)
{
    Ums9230CEState *s = UMS9230_CE(dev);
    memory_region_init_io(&s->iomem, OBJECT(dev), &ce_ops, s, "ums9230-ce", UMS9230_CE_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);
    fprintf(stderr, "[DBG] CE realize: iomem size=0x%lx\n", (unsigned long)memory_region_size(&s->iomem));
}

static void ce_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->realize = ce_realize;
}

static const TypeInfo ce_info = {
    .name = TYPE_UMS9230_CE,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(Ums9230CEState),
    .class_init = ce_class_init,
};

/* ---- machine ---- */
#include "qemu/timer.h"

static void write_heap(void *opaque)
{
    /* Map VA [16MB, 64MB) -> RAM [0x81000000, ...) via level-1 table 0x356000,
     * indices 8..31 (2MB blocks). Covers the trustos dma-heap (at image_size+0x43000). */
    for (int i = 8; i < 32; i++) {
        uint64_t pa = 0x81000000ULL + (uint64_t)(i - 8) * 0x200000ULL;
        uint64_t entry = 0x40000000000789ULL | pa;
        address_space_write(&address_space_memory, 0x356000ULL + i * 8,
                            MEMTXATTRS_UNSPECIFIED, &entry, 8);
    }
    fprintf(stderr, "[DBG] heap mapped: L1[8]=0x%lx\n",
            (unsigned long)(0x40000000000789ULL | 0x81000000ULL));
}

static void inject_vboot(void *opaque)
{
    ARMCPU *cpu = ARM_CPU(opaque);
    uint64_t VA = 0xffffffffe0600000ULL;  /* scratch VA (past payload, within fill's 16MB map) */
    uint64_t PA = 0x80600000ULL;          /* matching PA (VA 0xffffffffe0000000 -> PA 0x80000000) */
    uint64_t v = 0;
    #define W64(pa,val) do { v = (val); address_space_write(&address_space_memory, (pa), MEMTXATTRS_UNSPECIFIED, &v, 8); } while (0)

    /* crypto context chain (pointers are VAs): [tpidr+0x2b0]->ctx ; [ctx+0x90]->base ; [base+0x80]->table ; table[0]->handle */
    W64(PA + 0x2000 + 0x2b0, VA + 0x3000);
    W64(PA + 0x3000 + 0x90, VA + 0x4000);
    W64(PA + 0x4000 + 0x80, VA + 0x5000);
    W64(PA + 0x5000, VA + 0x6000);
    W64(PA + 0x6000, 1ULL << 0x20);              /* bitmap: bit 0x20 */
    W64(PA + 0x6000 + 0x20*8 + 8, VA + 0x7000);  /* entry */
    W64(PA + 0x7000, 1);                          /* refcount (start >0 so release skips free) */
    W64(PA + 0x7000 + 8, 0xffffffffe004ac44ULL); /* VBOOT_VERIFY_IMG handler entry */
    W64(PA + 0x7000 + 0xa8, 0xffffffffe0700000ULL); /* vbmeta structure */
    W64(0x80700000ULL + 0x18, 0xffffffffe0700100ULL); /* list-next */

    /* verify-context object so 0x4a6d0 calls 0x45d88 (the RSA verify).
     * entry[-0x30] -> VC ; VC[+0x38] = flags (bit0=1 -> do verify) ; VC[+0x50] = verify state */
    W64(PA + 0x7000 - 0x30, VA + 0x9000);          /* entry[-0x30] = verify-context ptr */
    W64(PA + 0x9000 + 0x38, 1);                    /* flags: bit0=1 (needs verify) */
    W64(PA + 0x9000 + 0x50, VA + 0xa000);          /* verify state ptr (non-zero) */
    /* zero the verify state + give it the vbmeta input */
    for (int i = 0; i < 0x200; i += 8) W64(PA + 0xa000 + i, 0);
    /* "verify input" struct (0x10 bytes) for the table[0x22] verify handler */
    for (int i = 0; i < 0x10; i += 8) W64(PA + 0xb000 + i, 0);

    /* the 6MB-8MB block (crypto ctx + vbmeta) is mapped AP=2 (EL1 RO, EL0 none);
     * make it AP=1 (RW for EL0+EL1) so the verify can read/write it. */
    W64(0x80356018ULL, 0x60000080600649ULL);  /* L1[3] = 6MB block, AP=1 RW (bits[7:6]=01) */

    /* map the rodata page holding the "AVB0" magic (VA 0xffffffffe00a5d78 -> PA 0x800a5d78)
     * via the level-3 table at 0x80381000, entry (0xa5d78>>12)=0xa5. */
    W64(0x80381528ULL, 0x800a564bULL);
    {
        uint64_t chk = 0;
        address_space_read(&address_space_memory, 0x80381528ULL, MEMTXATTRS_UNSPECIFIED, &chk, 8);
        fprintf(stderr, "[DBG] L3[0xa5] @0x80381528 = 0x%lx\n", (unsigned long)chk);
    }

    /* initialize the heap free-list sentinels (empty) at 0xffffffffe0375a30 so
     * the allocator inside avb_vbmeta_image_verify can malloc without faulting.
     * [0x60]=[0x58] (used-list head) and [0x70]=[0x68] (free-list head). */
    W64(0x80375a30ULL + 0x58, 0xffffffffe0375a88ULL);
    W64(0x80375a30ULL + 0x60, 0xffffffffe0375a88ULL);
    W64(0x80375a30ULL + 0x68, 0xffffffffe0375a98ULL);
    W64(0x80375a30ULL + 0x70, 0xffffffffe0375a98ULL);

    /* place a single large free chunk so malloc can satisfy the 0x100/0xd0/0x190 allocs.
     * free node at VA 0xffffffffe0800000 (PA 0x81000000): prev/next = sentinel, size = 0x2000 */
    W64(0x81000000ULL,      0xffffffffe0375a98ULL); /* free.prev = sentinel */
    W64(0x81000000ULL + 8,  0xffffffffe0375a98ULL); /* free.next = sentinel */
    W64(0x81000000ULL + 0x10, 0x2000ULL);            /* free.size */
    W64(0x80375a30ULL + 0x70, 0xffffffffe0800000ULL); /* free-list head -> free node */

    /* populate the avb crypto ops table (what 0x6f890 would build) so the hash/RSA
     * engine can run. ops struct at VA 0xffffffffe060c000 (PA 0x8060c000). */
    {
        uint64_t ops = VA + 0xc000;  /* 0xffffffffe060c000 */
        uint64_t gg[6] = {0};
        address_space_read(&address_space_memory, 0x80354708ULL, MEMTXATTRS_UNSPECIFIED, &gg[0], 8);
        address_space_read(&address_space_memory, 0x803547d0ULL, MEMTXATTRS_UNSPECIFIED, &gg[1], 8);
        address_space_read(&address_space_memory, 0x80354968ULL, MEMTXATTRS_UNSPECIFIED, &gg[2], 8);
        address_space_read(&address_space_memory, 0x80354910ULL, MEMTXATTRS_UNSPECIFIED, &gg[3], 8);
        address_space_read(&address_space_memory, 0x803540c8ULL, MEMTXATTRS_UNSPECIFIED, &gg[4], 8);
        address_space_read(&address_space_memory, 0x803547d8ULL, MEMTXATTRS_UNSPECIFIED, &gg[5], 8);
        fprintf(stderr, "[DBG] crypto globals: 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
                (unsigned long)gg[0], (unsigned long)gg[1], (unsigned long)gg[2],
                (unsigned long)gg[3], (unsigned long)gg[4], (unsigned long)gg[5]);
        W64(0x80354780ULL, ops);     /* [0xffffffffe0354780] -> ops struct */
        W64(0x8060c000ULL + 0x00, 0);
        W64(0x8060c000ULL + 0x08, 0);
        W64(0x8060c000ULL + 0x28, 0);
        W64(0x8060c000ULL + 0x18, gg[0]); /* read_is_device_unlocked */
        W64(0x8060c000ULL + 0x30, gg[1]); /* read_from_partition */
        W64(0x8060c000ULL + 0x38, gg[1] + 0x3c0ULL);
        W64(0x8060c000ULL + 0x40, gg[2]);
        W64(0x8060c000ULL + 0x48, gg[3]);
        W64(0x8060c000ULL + 0x50, gg[4]);
        W64(0x8060c000ULL + 0x58, gg[5]);
        fprintf(stderr, "[DBG] ops table populated at 0x%lx\n", (unsigned long)ops);
    }

    /* force version_major != 1 so avb_vbmeta_image_verify returns 3 (ERROR_VERIFICATION -> -11).
     * raw vbmeta has version_major=0x01000000 (BE); bswap32 -> 1 -> version passes.
     * set it to 0x02000000 so bswap32 -> 2 -> version != 1 -> 3. */
    W64(0x80700004ULL, 0x02000000ULL);

    /* drive avb_vbmeta_image_verify (0x6ed70) directly with the loaded vbmeta.
     * x0 = vbmeta data ; w1 = size ; x2 = hash out ; x3 = hash_size out ; x4 = 0 */
    cpu->env.pstate = 0x3C5;            /* EL1h + DAIF masked (keep interrupts from clobbering regs) */
    cpu->env.xregs[0] = 0xffffffffe0700000ULL; /* vbmeta data (VA) */
    cpu->env.xregs[1] = 0x1000;         /* size */
    cpu->env.xregs[2] = VA + 0xb000;    /* hash output ptr */
    cpu->env.xregs[3] = VA + 0xb008;    /* hash size output ptr */
    cpu->env.xregs[4] = 0;              /* is_chained_vbmeta */
    fprintf(stderr, "[DBG] inject: x0=0x%lx x1=0x%lx x2=0x%lx x3=0x%lx\n",
            (unsigned long)cpu->env.xregs[0], (unsigned long)cpu->env.xregs[1],
            (unsigned long)cpu->env.xregs[2], (unsigned long)cpu->env.xregs[3]);
    cpu->env.xregs[30] = 0xffffffffe0001888ULL; /* x30 = return addr (idle loop) */
    cpu->env.cp15.vbar_el[1] = 0xffffffffe0001000ULL; /* vector table */
    cpu->env.cp15.tcr_el[1] = 0x2b52335a4ULL;  /* T1SZ=35 TG1=4KB */
    cpu->env.cp15.ttbr1_el[1] = 0x80356000ULL; /* level-1 page table (PA) */
    cpu->env.sp_el[1] = 0xffffffffe035f000ULL; /* EL1h stack */
    cpu->env.xregs[31] = 0xffffffffe035f000ULL; /* current SP (x31) */
    cpu->env.cp15.esr_el[1] = 0x15ULL << 26;      /* ESR: SMC exception class */
    cpu_set_pc(CPU(cpu), 0xffffffffe006ed70ULL); /* avb_vbmeta_image_verify */
    cpu_resume(CPU(cpu));                         /* wake the vCPU if it was halted in WFI */
    fprintf(stderr, "[DBG] injected avb_vbmeta_image_verify (0x6ed70)\n");
    #undef W64
}

static void dump_regs(void *opaque)
{
    ARMCPU *cpu = ARM_CPU(opaque);
    uint64_t pte = 0, pte2 = 0, result = 0, hash = 0, hashsz = 0, p0 = 0, avb = 0, cmp = 0;
    address_space_read(&address_space_memory, 0x80356018, MEMTXATTRS_UNSPECIFIED, &pte, 8);
    address_space_read(&address_space_memory, 0x80381528, MEMTXATTRS_UNSPECIFIED, &pte2, 8);
    address_space_read(&address_space_memory, 0x80700000, MEMTXATTRS_UNSPECIFIED, &result, 8);
    address_space_read(&address_space_memory, 0x8060b000, MEMTXATTRS_UNSPECIFIED, &hash, 8);
    address_space_read(&address_space_memory, 0x8060b008, MEMTXATTRS_UNSPECIFIED, &hashsz, 8);
    address_space_read(&address_space_memory, 0x8060b010, MEMTXATTRS_UNSPECIFIED, &cmp, 4);
    address_space_read(&address_space_memory, 0x8060b018, MEMTXATTRS_UNSPECIFIED, &p0, 8);
    address_space_read(&address_space_memory, 0x800a5d78, MEMTXATTRS_UNSPECIFIED, &avb, 8);
    address_space_read(&address_space_memory, 0x8060c004, MEMTXATTRS_UNSPECIFIED, &result, 4);
    address_space_read(&address_space_memory, 0x8060c040, MEMTXATTRS_UNSPECIFIED, &cmp, 4);
    fprintf(stderr, "[DBG] PC=0x%lx X0=0x%lx(%ld) ESR=0x%lx EL=%d ELR=0x%lx FAR=0x%lx hash=0x%lx L1=0x%lx L3=0x%lx p0=0x%lx avb=0x%lx cmp=0x%lx ver=0x%lx\n",
            (unsigned long)cpu->env.pc,
            (unsigned long)cpu->env.xregs[0], (long)(int64_t)cpu->env.xregs[0],
            (unsigned long)cpu->env.cp15.esr_el[1],
            (int)(cpu->env.pstate & 0xc) >> 2,
            (unsigned long)cpu->env.elr_el[1],
            (unsigned long)cpu->env.cp15.far_el[1],
            (unsigned long)hash, (unsigned long)pte, (unsigned long)pte2, (unsigned long)p0, (unsigned long)avb, (unsigned long)cmp, (unsigned long)result);
}

static void ums9230_set_el(void *opaque)
{
    ARMCPU *cpu = ARM_CPU(opaque);
    cpu->env.pstate = 0x5;              /* EL1h (trustos runs at EL1) */
    cpu->env.cp15.scr_el3 = 0xC30;      /* NS=0 secure, RW=1, ST=1 (don't trap secure timer) */
    fprintf(stderr, "[DBG] reset handler: pstate=0x%lx el=%d\n",
            (unsigned long)cpu->env.pstate, (int)((cpu->env.pstate & 0xc) >> 2));
}

static void ums9230_init(MachineState *machine)
{
    MemoryRegion *ram = g_new(MemoryRegion, 1);
    MemoryRegion *secram = g_new(MemoryRegion, 1);
    MemoryRegion *lowram = g_new(MemoryRegion, 1);

    memory_region_init_ram(ram, NULL, "ums9230.ram", machine->ram_size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), UMS9230_RAM_BASE, ram);

    /* secure DRAM: the trustos dma-heap physical buffers (PA 0x64000000-0x65000000) */
    memory_region_init_ram(secram, NULL, "ums9230.secram", 512 * MiB, &error_fatal);
    memory_region_add_subregion(get_system_memory(), 0x60000000ULL, secram);

    /* low DRAM: more trustos dma-heap buffers (PA 0x20000000) */
    memory_region_init_ram(lowram, NULL, "ums9230.lowram", 512 * MiB, &error_fatal);
    memory_region_add_subregion(get_system_memory(), 0x20000000ULL, lowram);

    sysbus_create_simple(TYPE_PL011, UMS9230_UART_BASE, NULL);
    sysbus_create_simple(TYPE_UMS9230_CE, UMS9230_CE_BASE, NULL);

    /* create the boot CPU, set x0 (trustos physical base) and PC, load the payload */
    {
        Object *cpuobj = object_new(machine->cpu_type);
        ARM_CPU(cpuobj)->has_el3 = true;    /* keep EL3 (secure registers) */
        ARM_CPU(cpuobj)->has_el2 = false;   /* no EL2 */
        ARM_CPU(cpuobj)->start_secure_el1 = true;  /* start at Secure EL1, not EL3 */
        qdev_realize(DEVICE(cpuobj), NULL, &error_fatal);
        qemu_register_reset(ums9230_set_el, cpuobj);
        ARM_CPU(cpuobj)->env.xregs[0] = 0x1000000;  /* x0 = image size (16MB) */

        /* GICv3: provides the ICC_* CPU-interface system registers */
        {
            DeviceState *gic = qdev_new("arm-gicv3");
            SysBusDevice *gicbusdev;
            QList *redist = qlist_new();
            qdev_prop_set_uint32(gic, "revision", 3);
            qdev_prop_set_uint32(gic, "num-cpu", 1);
            qdev_prop_set_uint32(gic, "num-irq", 32 + 256);
            qdev_prop_set_bit(gic, "has-security-extensions", true);
            qlist_append_int(redist, 1);
            qdev_prop_set_array(gic, "redist-region-count", redist);
            object_property_set_link(OBJECT(gic), "sysmem",
                                     OBJECT(get_system_memory()), &error_fatal);
            gicbusdev = SYS_BUS_DEVICE(gic);
            sysbus_realize_and_unref(gicbusdev, &error_fatal);
            sysbus_mmio_map(gicbusdev, 0, 0x10000000ULL);  /* GICD */
            sysbus_mmio_map(gicbusdev, 1, 0x10040000ULL);  /* GICR */
            qdev_connect_gpio_out_named(DEVICE(cpuobj), "gicv3-maintenance-interrupt", 0,
                                        qdev_get_gpio_in(gic, 32 + 25));
        }

        if (machine->kernel_filename) {
            load_image_targphys_as(machine->kernel_filename, TRUSTOS_LOAD_ADDR,
                                   0x800000, &address_space_memory, &error_fatal);
            cpu_set_pc(CPU(cpuobj), TRUSTOS_LOAD_ADDR);
        }
        {
            uint64_t a = 0, b = 0;
            address_space_read(&address_space_memory, 0x80000000ULL, MEMTXATTRS_UNSPECIFIED, &a, 8);
            address_space_read(&address_space_memory, 0x80a5d78ULL, MEMTXATTRS_UNSPECIFIED, &b, 8);
            fprintf(stderr, "[DBG] post-load ram_size=0x%lx p0=0x%lx avb=0x%lx\n",
                    (unsigned long)machine->ram_size, (unsigned long)a, (unsigned long)b);
        }
        /* load the vbmeta image for the VBOOT_VERIFY_IMG test (VA 0xffffffffe0700000 -> PA 0x80700000) */
        load_image_targphys_as("firmware/vbmeta-stock.img",
                               0x80700000ULL, 0x100000, &address_space_memory, NULL);
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, write_heap, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 1000ULL); /* after fill, before heap use */
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, inject_vboot, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 1000000ULL); /* after boot, run the verify */
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 1500000ULL); /* early: catch fault ELR */
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 1600000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 1800000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2500000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 3000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 4000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 5000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 10000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 50000000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2000000000ULL);
        }
    }
}

static void ums9230_machine_init(MachineClass *mc)
{
    mc->desc = "Unisoc UMS9230 (T606) minimal machine (trustos TEE)";
    mc->init = ums9230_init;
    mc->max_cpus = 1;
    mc->min_cpus = 1;
    mc->default_cpus = 1;
    mc->default_ram_size = 1 * GiB;
}

DEFINE_MACHINE("ums9230", ums9230_machine_init)

static void ums9230_register_types(void)
{
    type_register_static(&ce_info);
}
type_init(ums9230_register_types)
