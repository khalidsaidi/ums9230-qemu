tcr = 0x2b52335a4
t0sz = tcr & 0x3f
t1sz = (tcr >> 16) & 0x3f
tg0 = (tcr >> 14) & 0x3
tg1 = (tcr >> 30) & 0x3
print('tcr      = 0x%x' % tcr)
print('T0SZ     = %d' % t0sz)
print('T1SZ     = %d' % t1sz)
print('TG0      = %d' % tg0, '(0=4K,1=64K,2=16K)')
print('TG1      = %d' % tg1, '(0=4K,1=64K,2=16K)')

# for 4K granule: initial level = 3 when T1SZ>=35
# VA ranges
import math
ttbr1_base = 0xffffffffffffffff - (1 << (64 - t1sz)) + 1
print('TTBR1 covers [0x%x .. 0xffffffffffffffff]' % ttbr1_base)
va = 0xfffffffffffff000
print('va 0x%x in TTBR1? %s' % (va, va >= ttbr1_base))
print('L2 index (>>21)&0x1ff = 0x%x' % ((va >> 21) & 0x1ff))
print('L3 index (>>12)&0x1ff = 0x%x' % ((va >> 12) & 0x1ff))
