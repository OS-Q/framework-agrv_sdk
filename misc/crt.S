# See LICENSE for license details.

#include "encoding.h"
#include "agrv.h"

  .section ".text.entry"
  .weak   trap_entry
  .globl _start
_start:
  fence.i
  li  x1, 0
  li  x2, 0
  li  x3, 0
  li  x4, 0
  li  x5, 0
  li  x6, 0
  li  x7, 0
  li  x8, 0
  li  x9, 0
  li  x10,0
  li  x11,0
  li  x12,0
  li  x13,0
  li  x14,0
  li  x15,0
  li  x16,0
  li  x17,0
  li  x18,0
  li  x19,0
  li  x20,0
  li  x21,0
  li  x22,0
  li  x23,0
  li  x24,0
  li  x25,0
  li  x26,0
  li  x27,0
  li  x28,0
  li  x29,0
  li  x30,0
  li  x31,0

  # enable FPU and accelerator if present
  li t0, MSTATUS_FS | MSTATUS_XS
  csrs mstatus, t0

#ifdef __riscv_flen
  # initialize FPU if we have one
  la t0, 1f
  csrw mtvec, t0

  fssr    x0
  fmv.s.x f0, x0
  fmv.s.x f1, x0
  fmv.s.x f2, x0
  fmv.s.x f3, x0
  fmv.s.x f4, x0
  fmv.s.x f5, x0
  fmv.s.x f6, x0
  fmv.s.x f7, x0
  fmv.s.x f8, x0
  fmv.s.x f9, x0
  fmv.s.x f10,x0
  fmv.s.x f11,x0
  fmv.s.x f12,x0
  fmv.s.x f13,x0
  fmv.s.x f14,x0
  fmv.s.x f15,x0
  fmv.s.x f16,x0
  fmv.s.x f17,x0
  fmv.s.x f18,x0
  fmv.s.x f19,x0
  fmv.s.x f20,x0
  fmv.s.x f21,x0
  fmv.s.x f22,x0
  fmv.s.x f23,x0
  fmv.s.x f24,x0
  fmv.s.x f25,x0
  fmv.s.x f26,x0
  fmv.s.x f27,x0
  fmv.s.x f28,x0
  fmv.s.x f29,x0
  fmv.s.x f30,x0
  fmv.s.x f31,x0
1:
#endif

  # initialize trap vector
  la t0, trap_entry
  csrw mtvec, t0

  # initialize global pointer
.option push
.option norelax
  la gp, __global_pointer$
.option pop
  la sp, __stack_pointer$

  j _init

  .section ".text.init"
  .align 2
trap_entry:

#if AGRV_FP_STACK == 1
  addi    sp,  sp, -FSTKSIZE
  FSTORE  f0,  0 * FREGBYTES(sp)
  FSTORE  f1,  1 * FREGBYTES(sp)
  FSTORE  f2,  2 * FREGBYTES(sp)
  FSTORE  f3,  3 * FREGBYTES(sp)
  FSTORE  f4,  4 * FREGBYTES(sp)
  FSTORE  f5,  5 * FREGBYTES(sp)
  FSTORE  f6,  6 * FREGBYTES(sp)
  FSTORE  f7,  7 * FREGBYTES(sp)
  FSTORE  f8,  8 * FREGBYTES(sp)
  FSTORE  f9,  9 * FREGBYTES(sp)
  FSTORE  f10, 10 * FREGBYTES(sp)
  FSTORE  f11, 11 * FREGBYTES(sp)
  FSTORE  f12, 12 * FREGBYTES(sp)
  FSTORE  f13, 13 * FREGBYTES(sp)
  FSTORE  f14, 14 * FREGBYTES(sp)
  FSTORE  f15, 15 * FREGBYTES(sp)
  FSTORE  f16, 16 * FREGBYTES(sp)
  FSTORE  f17, 17 * FREGBYTES(sp)
  FSTORE  f18, 18 * FREGBYTES(sp)
  FSTORE  f19, 19 * FREGBYTES(sp)
  FSTORE  f20, 20 * FREGBYTES(sp)
  FSTORE  f21, 21 * FREGBYTES(sp)
  FSTORE  f22, 22 * FREGBYTES(sp)
  FSTORE  f23, 23 * FREGBYTES(sp)
  FSTORE  f24, 24 * FREGBYTES(sp)
  FSTORE  f25, 25 * FREGBYTES(sp)
  FSTORE  f26, 26 * FREGBYTES(sp)
  FSTORE  f27, 27 * FREGBYTES(sp)
  FSTORE  f28, 28 * FREGBYTES(sp)
  FSTORE  f29, 29 * FREGBYTES(sp)
  FSTORE  f30, 30 * FREGBYTES(sp)
  FSTORE  f31, 31 * FREGBYTES(sp)
#endif

  addi sp, sp, -STKSIZE
  SREG x1, 0*REGBYTES(sp)
  SREG x2, 1*REGBYTES(sp)
  SREG x3, 2*REGBYTES(sp)
  SREG x4, 3*REGBYTES(sp)
  SREG x5, 4*REGBYTES(sp)
  SREG x6, 5*REGBYTES(sp)
  SREG x7, 6*REGBYTES(sp)
  SREG x8, 7*REGBYTES(sp)
  SREG x9, 8*REGBYTES(sp)
  SREG x10, 9*REGBYTES(sp)
  SREG x11, 10*REGBYTES(sp)
  SREG x12, 11*REGBYTES(sp)
  SREG x13, 12*REGBYTES(sp)
  SREG x14, 13*REGBYTES(sp)
  SREG x15, 14*REGBYTES(sp)
  SREG x16, 15*REGBYTES(sp)
  SREG x17, 16*REGBYTES(sp)
  SREG x18, 17*REGBYTES(sp)
  SREG x19, 18*REGBYTES(sp)
  SREG x20, 19*REGBYTES(sp)
  SREG x21, 20*REGBYTES(sp)
  SREG x22, 21*REGBYTES(sp)
  SREG x23, 22*REGBYTES(sp)
  SREG x24, 23*REGBYTES(sp)
  SREG x25, 24*REGBYTES(sp)
  SREG x26, 25*REGBYTES(sp)
  SREG x27, 26*REGBYTES(sp)
  SREG x28, 27*REGBYTES(sp)
  SREG x29, 28*REGBYTES(sp)
  SREG x30, 29*REGBYTES(sp)
  SREG x31, 30*REGBYTES(sp)

  csrr a0, mcause
  csrr a1, mepc
  SREG a1, 31*REGBYTES(sp)
  mv a2, sp
  call handle_trap

  # Remain in M-mode after eret
  li t0, MSTATUS_MPP
  csrs mstatus, t0

  LREG x1, 0*REGBYTES(sp)
  LREG x2, 1*REGBYTES(sp)
  LREG x3, 2*REGBYTES(sp)
  LREG x4, 3*REGBYTES(sp)
  LREG x5, 4*REGBYTES(sp)
  LREG x6, 5*REGBYTES(sp)
  LREG x7, 6*REGBYTES(sp)
  LREG x8, 7*REGBYTES(sp)
  LREG x9, 8*REGBYTES(sp)
  LREG x10, 9*REGBYTES(sp)
  LREG x11, 10*REGBYTES(sp)
  LREG x12, 11*REGBYTES(sp)
  LREG x13, 12*REGBYTES(sp)
  LREG x14, 13*REGBYTES(sp)
  LREG x15, 14*REGBYTES(sp)
  LREG x16, 15*REGBYTES(sp)
  LREG x17, 16*REGBYTES(sp)
  LREG x18, 17*REGBYTES(sp)
  LREG x19, 18*REGBYTES(sp)
  LREG x20, 19*REGBYTES(sp)
  LREG x21, 20*REGBYTES(sp)
  LREG x22, 21*REGBYTES(sp)
  LREG x23, 22*REGBYTES(sp)
  LREG x24, 23*REGBYTES(sp)
  LREG x25, 24*REGBYTES(sp)
  LREG x26, 25*REGBYTES(sp)
  LREG x27, 26*REGBYTES(sp)
  LREG x28, 27*REGBYTES(sp)
  LREG x29, 28*REGBYTES(sp)
  LREG x30, 29*REGBYTES(sp)
  LREG x31, 30*REGBYTES(sp)
  addi sp, sp, STKSIZE

#if AGRV_FP_STACK == 1
  FLOAD   f0, 0 * FREGBYTES(sp)
  FLOAD   f1, 1 * FREGBYTES(sp)
  FLOAD   f2, 2 * FREGBYTES(sp)
  FLOAD   f3, 3 * FREGBYTES(sp)
  FLOAD   f4, 4 * FREGBYTES(sp)
  FLOAD   f5, 5 * FREGBYTES(sp)
  FLOAD   f6, 6 * FREGBYTES(sp)
  FLOAD   f7, 7 * FREGBYTES(sp)
  FLOAD   f8, 8 * FREGBYTES(sp)
  FLOAD   f9, 9 * FREGBYTES(sp)
  FLOAD   f10, 10 * FREGBYTES(sp)
  FLOAD   f11, 11 * FREGBYTES(sp)
  FLOAD   f12, 12 * FREGBYTES(sp)
  FLOAD   f13, 13 * FREGBYTES(sp)
  FLOAD   f14, 14 * FREGBYTES(sp)
  FLOAD   f15, 15 * FREGBYTES(sp)
  FLOAD   f16, 16 * FREGBYTES(sp)
  FLOAD   f17, 17 * FREGBYTES(sp)
  FLOAD   f18, 18 * FREGBYTES(sp)
  FLOAD   f19, 19 * FREGBYTES(sp)
  FLOAD   f20, 20 * FREGBYTES(sp)
  FLOAD   f21, 21 * FREGBYTES(sp)
  FLOAD   f22, 22 * FREGBYTES(sp)
  FLOAD   f23, 23 * FREGBYTES(sp)
  FLOAD   f24, 24 * FREGBYTES(sp)
  FLOAD   f25, 25 * FREGBYTES(sp)
  FLOAD   f26, 26 * FREGBYTES(sp)
  FLOAD   f27, 27 * FREGBYTES(sp)
  FLOAD   f28, 28 * FREGBYTES(sp)
  FLOAD   f29, 29 * FREGBYTES(sp)
  FLOAD   f30, 30 * FREGBYTES(sp)
  FLOAD   f31, 31 * FREGBYTES(sp)
  addi    sp, sp, FSTKSIZE
#endif

  mret

.section ".tdata.begin"
.globl _tdata_begin
_tdata_begin:

.section ".tdata.end"
.globl _tdata_end
_tdata_end:

.section ".tbss.end"
.globl _tbss_end
_tbss_end:

