#ifndef _AGM_AGRV_H
#define _AGM_AGRV_H

#if __riscv_xlen == 64
# define LREG ld
# define SREG sd
# define REGBYTES 8
# define FSTORE fsd
# define FLOAD  fld
# define FREGBYTES 8
#else
# define LREG lw
# define SREG sw
# define REGBYTES 4
# define FSTORE fsw
# define FLOAD  flw
# define FREGBYTES 4
#endif

#ifdef __riscv_flen
#ifndef AGRV_FP_STACK
# define AGRV_FP_STACK 1
#endif
#else
# define AGRV_FP_STACK 0
#endif

#define STKSIZE  32*REGBYTES
#define FSTKSIZE 32*FREGBYTES

#endif
