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

/* ---- crypto engine: real SHA-256 + RSA-4096 MMIO device ----
 * Register map (documented interface; the exact Unisoc CE layout is TBD):
 *   0x000  SHA_CTRL    W: bit0=1 reset hash ; bit1=1 finalize -> digest valid
 *   0x100  SHA_DATA    W: streaming data in (each write appends the bytes)
 *   0x300  SHA_DIGEST  R: 32-byte digest
 *   0x400  RSA_CTRL    W: bit0=1 run modpow (sig^65537 mod N)
 *   0x500  RSA_N       W: 512-byte modulus
 *   0x700  RSA_SIG     W: 512-byte signature (base)
 *   0x900  RSA_RESULT  R: 512-byte result
 */
#include <string.h>

#define TYPE_UMS9230_CE "ums9230-ce"
OBJECT_DECLARE_SIMPLE_TYPE(Ums9230CEState, UMS9230_CE)

/* ---------------- SHA-256 ---------------- */
typedef struct { uint32_t h[8]; uint64_t total; uint8_t block[64]; unsigned blen; } Sha256Ctx;
static const uint32_t K[64] = {
0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};
#define ROR32(x,n) (((x)>>(n))|((x)<<(32-(n))))
static void sha256_init(Sha256Ctx *c) {
    c->h[0]=0x6a09e667; c->h[1]=0xbb67ae85; c->h[2]=0x3c6ef372; c->h[3]=0xa54ff53a;
    c->h[4]=0x510e527f; c->h[5]=0x9b05688c; c->h[6]=0x1f83d9ab; c->h[7]=0x5be0cd19;
    c->total=0; c->blen=0;
}
static void sha256_block(Sha256Ctx *c, const uint8_t *p) {
    uint32_t w[64];
    for (int i=0;i<16;i++) w[i] = ((uint32_t)p[4*i]<<24)|((uint32_t)p[4*i+1]<<16)|((uint32_t)p[4*i+2]<<8)|p[4*i+3];
    for (int i=16;i<64;i++) {
        uint32_t s0 = ROR32(w[i-15],7)^ROR32(w[i-15],18)^(w[i-15]>>3);
        uint32_t s1 = ROR32(w[i-2],17)^ROR32(w[i-2],19)^(w[i-2]>>10);
        w[i] = w[i-16]+s0+w[i-7]+s1;
    }
    uint32_t a=c->h[0],b=c->h[1],cc=c->h[2],d=c->h[3],e=c->h[4],f=c->h[5],g=c->h[6],h=c->h[7];
    for (int i=0;i<64;i++) {
        uint32_t S1=ROR32(e,6)^ROR32(e,11)^ROR32(e,25);
        uint32_t ch=(e&f)^((~e)&g);
        uint32_t t1=h+S1+ch+K[i]+w[i];
        uint32_t S0=ROR32(a,2)^ROR32(a,13)^ROR32(a,22);
        uint32_t maj=(a&b)^(a&cc)^(b&cc);
        uint32_t t2=S0+maj;
        h=g; g=f; f=e; e=d+t1; d=cc; cc=b; b=a; a=t1+t2;
    }
    c->h[0]+=a; c->h[1]+=b; c->h[2]+=cc; c->h[3]+=d; c->h[4]+=e; c->h[5]+=f; c->h[6]+=g; c->h[7]+=h;
}
static void sha256_update(Sha256Ctx *c, const uint8_t *p, size_t len) {
    c->total += len;
    while (len > 0) {
        size_t take = 64 - c->blen; if (take > len) take = len;
        memcpy(c->block + c->blen, p, take);
        c->blen += take; p += take; len -= take;
        if (c->blen == 64) { sha256_block(c, c->block); c->blen = 0; }
    }
}
static void sha256_final(Sha256Ctx *c, uint8_t out[32]) {
    uint64_t bits = c->total * 8;
    uint8_t pad = 0x80, zero = 0;
    sha256_update(c, &pad, 1);
    while (c->blen != 56) sha256_update(c, &zero, 1);
    uint8_t lenb[8];
    for (int i=0;i<8;i++) lenb[i] = (uint8_t)(bits >> (56 - 8*i));
    sha256_update(c, lenb, 8);
    for (int i=0;i<8;i++) {
        out[4*i]   = (uint8_t)(c->h[i]>>24);
        out[4*i+1] = (uint8_t)(c->h[i]>>16);
        out[4*i+2] = (uint8_t)(c->h[i]>>8);
        out[4*i+3] = (uint8_t)(c->h[i]);
    }
}

/* ---------------- RSA-4096 (modpow e=65537) ---------------- */
#define BN_LIMBS 64
typedef uint64_t limb;
typedef struct { limb v[BN_LIMBS]; } bn;
static void bn_from_le(bn *x, const uint8_t *p) {
    for (int i=0;i<BN_LIMBS;i++) { x->v[i]=0; for (int j=0;j<8;j++) x->v[i] |= ((limb)p[i*8+j]) << (8*j); }
}
static void bn_to_le(uint8_t *p, const bn *x) {
    for (int i=0;i<BN_LIMBS;i++) for (int j=0;j<8;j++) p[i*8+j] = (uint8_t)(x->v[i] >> (8*j));
}
static int bn_cmp(const bn *a, const bn *b) {
    for (int i=BN_LIMBS-1;i>=0;i--) if (a->v[i]!=b->v[i]) return a->v[i]<b->v[i] ? -1 : 1;
    return 0;
}
static void bn_mul(limb prod[2*BN_LIMBS], const bn *a, const bn *b) {
    memset(prod, 0, 2*BN_LIMBS*sizeof(limb));
    for (int i=0;i<BN_LIMBS;i++) {
        limb carry = 0;
        for (int j=0;j<BN_LIMBS;j++) {
            __uint128_t t = (__uint128_t)a->v[i] * b->v[j] + prod[i+j] + carry;
            prod[i+j] = (limb)t;
            carry = (limb)(t >> 64);
        }
        prod[i+BN_LIMBS] += carry;
    }
}
static void bn_mod(bn *r, const limb prod[2*BN_LIMBS], const bn *n) {
    limb num[2*BN_LIMBS];
    memcpy(num, prod, 2*BN_LIMBS*sizeof(limb));
    int top = 2*BN_LIMBS-1;
    while (top >= 0 && num[top] == 0) top--;
    limb rr[BN_LIMBS+1];
    memset(rr, 0, sizeof(rr));
    for (int bit = top*64 + 63; bit >= 0; bit--) {
        for (int i=BN_LIMBS;i>0;i--) rr[i] = (rr[i]<<1) | (rr[i-1]>>63);
        rr[0] <<= 1;
        int w = bit/64, b = bit%64;
        rr[0] |= (num[w] >> b) & 1;
        if (rr[BN_LIMBS] != 0 || bn_cmp((const bn *)rr, n) >= 0) {
            limb borrow = 0;
            for (int i=0;i<BN_LIMBS;i++) {
                limb bv = n->v[i];
                limb sub = bv + borrow;
                limb nb = (rr[i] < sub) || (borrow && bv == ~(limb)0);
                rr[i] = rr[i] - sub;
                borrow = nb;
            }
            if (borrow) rr[BN_LIMBS]--;
        }
    }
    memcpy(r->v, rr, BN_LIMBS*sizeof(limb));
}
static void bn_modmul(bn *r, const bn *a, const bn *b, const bn *n) {
    limb prod[2*BN_LIMBS];
    bn_mul(prod, a, b);
    bn_mod(r, prod, n);
}
static void bn_modpow_65537(bn *r, const bn *base, const bn *n) {
    bn acc; memset(acc.v, 0, sizeof(acc.v)); acc.v[0] = 1;
    for (int bit = 16; bit >= 0; bit--) {
        bn_modmul(&acc, &acc, &acc, n);
        if ((0x10001 >> bit) & 1) bn_modmul(&acc, &acc, base, n);
    }
    *r = acc;
}
static void rsa_verify(uint8_t out[512], const uint8_t sig[512], const uint8_t n[512]) {
    bn base, mod, res;
    bn_from_le(&base, sig);
    bn_from_le(&mod, n);
    bn_modpow_65537(&res, &base, &mod);
    bn_to_le(out, &res);
}

/* ---------------- device ---------------- */
struct Ums9230CEState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    Sha256Ctx sha;
    uint8_t sha_digest[32];
    uint8_t rsa_n[512];
    uint8_t rsa_sig[512];
    uint8_t rsa_result[512];
};

static uint64_t ce_read(void *opaque, hwaddr offset, unsigned size)
{
    Ums9230CEState *s = UMS9230_CE(opaque);
    uint64_t v = 0;
    if (offset >= 0x300 && offset < 0x300 + 32) {
        memcpy(&v, s->sha_digest + (offset - 0x300), size < 8 ? size : 8);
    } else if (offset >= 0x900 && offset < 0x900 + 512) {
        memcpy(&v, s->rsa_result + (offset - 0x900), size < 8 ? size : 8);
    }
    return v;
}

static void ce_write(void *opaque, hwaddr offset, uint64_t value, unsigned size)
{
    Ums9230CEState *s = UMS9230_CE(opaque);
    uint8_t bytes[8];
    for (unsigned i = 0; i < size && i < 8; i++) bytes[i] = (uint8_t)(value >> (8*i));
    if (offset >= 0x100 && offset < 0x300) {
        sha256_update(&s->sha, bytes, size);
    } else if (offset >= 0x500 && offset < 0x700) {
        for (unsigned i = 0; i < size && i < 8; i++) s->rsa_n[offset - 0x500 + i] = bytes[i];
    } else if (offset >= 0x700 && offset < 0x900) {
        for (unsigned i = 0; i < size && i < 8; i++) s->rsa_sig[offset - 0x700 + i] = bytes[i];
    } else if (offset == 0x000) {
        if (value & 1) sha256_init(&s->sha);
        if (value & 2) sha256_final(&s->sha, s->sha_digest);
    } else if (offset == 0x400) {
        if (value & 1) rsa_verify(s->rsa_result, s->rsa_sig, s->rsa_n);
    }
}

static const MemoryRegionOps ce_ops = {
    .read = ce_read,
    .write = ce_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void ce_realize(DeviceState *dev, Error **errp)
{
    Ums9230CEState *s = UMS9230_CE(dev);
    sha256_init(&s->sha);
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
    /* (list-next write removed: it was clobbering vbmeta[0x18..0x1f], the aux block size) */

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
    W64(0x80356808ULL, 0x60000080200649ULL);  /* L2[0x101] = heap .bss block (PA 0x80200000), AP=1 RW */
    W64(0x80356040ULL, 0x60000081000649ULL);  /* L2[8] = free-node block (VA 0xffffffffe1000000 -> PA 0x81000000), AP=1 RW */
    W64(0x803567f0ULL, 0x6000009fc00649ULL);  /* L2[0xfe] = hwspinlock (VA 0xffffffffffc00000 -> PA 0x9fc00000), AP=1 RW */
    W64(0x803814b8ULL, 0x8009764bULL);        /* L3[0x97] = vbmeta buffer page (VA 0xffffffffe0097000 -> PA 0x80097000), AF=1 AP=1 RW */
    W64(0x803814c0ULL, 0x8009864bULL);        /* L3[0x98] = vbmeta buffer 2nd page (VA 0xffffffffe0098000 -> PA 0x80098000), AF=1 AP=1 RW */
    W64(0x803812f0ULL, 0x8035e64bULL);        /* L3[0x5e] = stack page (VA 0xffffffffe035e000 -> PA 0x8035e000), AF=1 AP=1 RW */
    /* mmu_initial_mappings for paddr_to_kvaddr (0x745f0): entry {phys, virt, size, flags, name} (0x28 B) */
    W64(0x8060d100ULL, 0x80000000ULL);         /* entry0[0] = phys (RAM) */
    W64(0x8060d108ULL, 0xffffffffe0000000ULL); /* entry0[8] = virt */
    W64(0x8060d110ULL, 0x20000000ULL);         /* entry0[0x10] = size (512MB) */
    W64(0x8060d118ULL, 0x0ULL);                /* entry0[0x18] = flags */
    W64(0x8060d128ULL, 0x60000000ULL);         /* entry1[0] = phys (secram) */
    W64(0x8060d130ULL, 0xffffffffc0000000ULL); /* entry1[8] = virt */
    W64(0x8060d138ULL, 0x20000000ULL);         /* entry1[0x10] = size (512MB) */
    W64(0x8060d140ULL, 0x0ULL);                /* entry1[0x18] = flags */
    W64(0x8060d158ULL, 0x0ULL);                /* entry2 size = 0 (end) */
    W64(0x803546a0ULL, 0xffffffffe060d100ULL); /* head -> entry0 (VA) */
    /* "avb heap" size global ([0x354610] -> VA 0xffffffffe03739b0) = 0 by default; set to RAM size */
    W64(0x803739b0ULL, 0x100000ULL);           /* "avb heap" size = vbmeta size (SL8541E MEMORY[0xFFFFFFFFE0064408]) */
    W64(0x80356ff8ULL, 0x6000009fe00649ULL);   /* L2[0x1ff] = avb-heap VA (0xfffffffffffff000) -> PA 0x9fe00000, AP=1 RW */
    W64(0x8060d180ULL, 0xffffffffe060e000ULL); /* bump-allocator pointer -> 0xffffffffe060e000 */

    /* map the rodata page holding the "AVB0" magic (VA 0xffffffffe00a5d78 -> PA 0x800a5d78)
     * via the level-3 table at 0x80381000, entry (0xa5d78>>12)=0xa5. */
    W64(0x80381528ULL, 0x800a564bULL);
    {
        uint64_t chk = 0;
        address_space_read(&address_space_memory, 0x80381528ULL, MEMTXATTRS_UNSPECIFIED, &chk, 8);
        fprintf(stderr, "[DBG] L3[0xa5] @0x80381528 = 0x%lx\n", (unsigned long)chk);
    }

    /* initialize the heap free-list/used-list heads at 0xffffffffe0375a30.
     * malloc reads [heap+0x58]/[heap+0x60] as the FREE-list head (x24 = heap+0x58),
     * and the drain/free use [heap+0x68]/[heap+0x70] as the USED-list head. */
    {
        uint64_t h0 = 0xffffffffe1000000ULL, h1 = 0xffffffffe1000000ULL,
                 h2 = 0xffffffffe0375a98ULL, h3 = 0xffffffffe0375a98ULL;
        address_space_write(&address_space_memory, 0x80375a88ULL, MEMTXATTRS_UNSPECIFIED, &h0, 8);
        address_space_write(&address_space_memory, 0x80375a90ULL, MEMTXATTRS_UNSPECIFIED, &h1, 8);
        address_space_write(&address_space_memory, 0x80375a98ULL, MEMTXATTRS_UNSPECIFIED, &h2, 8);
        address_space_write(&address_space_memory, 0x80375aa0ULL, MEMTXATTRS_UNSPECIFIED, &h3, 8);
        {
            uint64_t rb0 = 0, rb1 = 0;
            address_space_read(&address_space_memory, 0x80375a88ULL, MEMTXATTRS_UNSPECIFIED, &rb0, 8);
            address_space_read(&address_space_memory, 0x80375a90ULL, MEMTXATTRS_UNSPECIFIED, &rb1, 8);
            fprintf(stderr, "[DBG] heap-write-readback: 0x80375a88=0x%lx 0x80375a90=0x%lx\n",
                    (unsigned long)rb0, (unsigned long)rb1);
        }
    }

    /* place a single large free chunk so malloc can satisfy the 0x100/0xd0/0x190 allocs.
     * free node data at PA 0x81000000 -> VA 0xffffffffe1000000 (write_heap maps VA[16MB..64MB)->PA 0x81000000). */
    W64(0x81000000ULL,      0xffffffffe0375a88ULL); /* free.prev = &free-head (heap+0x58) */
    W64(0x81000000ULL + 8,  0xffffffffe0375a88ULL); /* free.next = &free-head (heap+0x58) */
    W64(0x81000000ULL + 0x10, 0x2000ULL);            /* free.size */

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
    /* W64(0x80700004ULL, 0x02000000ULL);  // ENABLE for -11 (returns 3). Comment out to run the full hash+RSA path (returns 0). */

    /* set up the avb_slot_verify (0x713f8) input struct: [x0+8]=offset, [x0+0xc]=size */
    W64(0x8060d000ULL + 8, 0x1000ULL);      /* offset (non-zero to pass the cbz) */
    W64(0x8060d000ULL + 0xc, 0x100000ULL);  /* size (full vbmeta) */

    /* drive avb_slot_verify (0x713f8) with the input struct */
    cpu->env.pstate = 0x3C5;            /* EL1h + DAIF masked */
    cpu->env.xregs[0] = 0xffffffffe060d000ULL; /* input struct (VA) */
    cpu->env.xregs[1] = 0xffffffffe060d000ULL; /* mirror in x1 for clobber test */
    fprintf(stderr, "[DBG] inject: x0=0x%lx\n", (unsigned long)cpu->env.xregs[0]);
    cpu->env.xregs[30] = 0xffffffffe0001888ULL; /* x30 = return addr (idle loop) */
    cpu->env.cp15.vbar_el[1] = 0xffffffffe0001000ULL; /* vector table */
    cpu->env.cp15.tcr_el[1] = 0x2b52335a4ULL;  /* T1SZ=35 TG1=4KB */
    cpu->env.cp15.ttbr1_el[1] = 0x80356000ULL; /* level-1 page table (PA) */
    cpu->env.sp_el[1] = 0xffffffffe035f000ULL; /* EL1h stack */
    cpu->env.xregs[31] = 0xffffffffe035f000ULL; /* current SP (x31) */
    cpu->env.cp15.esr_el[1] = 0x15ULL << 26;      /* ESR: SMC exception class */
    cpu_set_pc(CPU(cpu), 0xffffffffe00713f8ULL); /* avb_slot_verify */
    cpu_resume(CPU(cpu));                         /* wake the vCPU if it was halted in WFI */
    fprintf(stderr, "[DBG] injected avb_slot_verify (0x713f8)\n");
    #undef W64
}

static void dump_regs(void *opaque)
{
    ARMCPU *cpu = ARM_CPU(opaque);
    uint64_t read_ops = 0, ops_base = 0, bdev = 0, l2_0 = 0, l2_ff = 0, l3_97 = 0;
    uint64_t sx0 = 0, sx1 = 0, sx18 = 0, sx19 = 0, sx29 = 0, sx30 = 0;
    /* exception vector (0x1200) saves regs to [sp_orig-0x110 .. ]; sp_orig = 0xffffffffe035ef50 (frame after stp #-0xb0) */
    address_space_read(&address_space_memory, 0x8035ee40ULL, MEMTXATTRS_UNSPECIFIED, &sx0, 8);    /* x0 */
    address_space_read(&address_space_memory, 0x8035ee48ULL, MEMTXATTRS_UNSPECIFIED, &sx1, 8);    /* x1 */
    address_space_read(&address_space_memory, 0x8035eed0ULL, MEMTXATTRS_UNSPECIFIED, &sx18, 8);   /* x18 (elr) */
    address_space_read(&address_space_memory, 0x8035eed8ULL, MEMTXATTRS_UNSPECIFIED, &sx19, 8);   /* x19 */
    address_space_read(&address_space_memory, 0x8035ef28ULL, MEMTXATTRS_UNSPECIFIED, &sx29, 8);   /* x29 */
    address_space_read(&address_space_memory, 0x8035ef30ULL, MEMTXATTRS_UNSPECIFIED, &sx30, 8);   /* x30 */
    uint64_t rhead = 0, rbase = 0, rpa = 0, rsz = 0, avb_c = 0, avb_610 = 0, v1 = 0, v2 = 0;
    address_space_read(&address_space_memory, 0x803546f8, MEMTXATTRS_UNSPECIFIED, &read_ops, 8);
    address_space_read(&address_space_memory, 0x80354780, MEMTXATTRS_UNSPECIFIED, &ops_base, 8);
    address_space_read(&address_space_memory, 0x8035f100, MEMTXATTRS_UNSPECIFIED, &bdev, 8);
    address_space_read(&address_space_memory, 0x80356000, MEMTXATTRS_UNSPECIFIED, &l2_0, 8);
    address_space_read(&address_space_memory, 0x80356ff8, MEMTXATTRS_UNSPECIFIED, &l2_ff, 8);
    address_space_read(&address_space_memory, 0x803814b8, MEMTXATTRS_UNSPECIFIED, &l3_97, 8);
    address_space_read(&address_space_memory, 0x803546a0, MEMTXATTRS_UNSPECIFIED, &rhead, 8);
    if (rhead >= 0xffffffffe0000000ULL && rhead < 0xfffffffff0000000ULL) {
        uint64_t rp = rhead - 0xffffffffe0000000ULL + 0x80000000ULL;
        address_space_read(&address_space_memory, rp, MEMTXATTRS_UNSPECIFIED, &rbase, 8);
        address_space_read(&address_space_memory, rp + 8, MEMTXATTRS_UNSPECIFIED, &rpa, 8);
        address_space_read(&address_space_memory, rp + 0x10, MEMTXATTRS_UNSPECIFIED, &rsz, 8);
    }
    address_space_read(&address_space_memory, 0x803548c0, MEMTXATTRS_UNSPECIFIED, &avb_c, 8);
    address_space_read(&address_space_memory, 0x80354610, MEMTXATTRS_UNSPECIFIED, &avb_610, 8);
    if (avb_c >= 0xffffffffe0000000ULL && avb_c < 0xfffffffff0000000ULL &&
        avb_610 >= 0xffffffffe0000000ULL && avb_610 < 0xfffffffff0000000ULL) {
        uint64_t pa1 = avb_c - 0xffffffffe0000000ULL + 0x80000000ULL;
        uint64_t pa2 = avb_610 - 0xffffffffe0000000ULL + 0x80000000ULL;
        address_space_read(&address_space_memory, pa1, MEMTXATTRS_UNSPECIFIED, &v1, 8);
        address_space_read(&address_space_memory, pa2, MEMTXATTRS_UNSPECIFIED, &v2, 8);
    }
    fprintf(stderr, "[DBG] PC=0x%lx X0=0x%lx X1=0x%lx X19=0x%lx ELR=0x%lx FAR=0x%lx\n",
            (unsigned long)cpu->env.pc,
            (unsigned long)cpu->env.xregs[0],
            (unsigned long)cpu->env.xregs[1],
            (unsigned long)cpu->env.xregs[19],
            (unsigned long)cpu->env.elr_el[1],
            (unsigned long)cpu->env.cp15.far_el[1]);
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
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2000000ULL); /* after boot main-init (1.5ms), before 3ms spinlock */
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
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2000500ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2001000ULL);
        }
        {
            QEMUTimer *t = timer_new_ns(QEMU_CLOCK_VIRTUAL, dump_regs, cpuobj);
            timer_mod(t, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + 2001500ULL);
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
