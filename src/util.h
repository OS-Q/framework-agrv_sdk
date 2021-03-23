#ifndef _AGM_UTIL_H
#define _AGM_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "AltaRiscv.h"
#include "encoding.h"

#define __I  volatile const // read only
#define __O  volatile       // write only
#define __IO volatile       // read/write

typedef enum
{
  RET_OK  = 0x00,
  RET_ERR = 0x01,
} ReturnCodeTypedef;

typedef enum
{
  DISABLE = 0x0,
  ENABLE  = 0x1,
} EnableTypeDef;

#define SIZE_OF(VALS) (sizeof(VALS)/sizeof(*(VALS)))
#define XLEN_BITS 32
#define XLEN_BYTES (XLEN_BITS >> 3)
#define XLEN_TYPE uint32_t

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define MODIFY_BIT(REG, CLEARMASK, SETMASK) ((REG) = (((REG) & (~(CLEARMASK))) | (SETMASK)))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG MODIFY_BIT

#define RD_REG(REG) (*(volatile XLEN_TYPE *)(REG))
#define WR_REG(REG, val) (*(volatile XLEN_TYPE *)(REG)) = val
#define SET_REG_BIT(REG, MASK) (WR_REG((REG), RD_REG(REG) |  (MASK)))
#define CLR_REG_BIT(REG, MASK) (WR_REG((REG), RD_REG(REG) & ~(MASK)))
#define MOD_REG_BIT(REG, MASK, BIT) (WR_REG(REG, RD_REG(REG) & ~(MASK) | BIT))
#define GET_REG_BIT(REG, MASK) (RD_REG(REG) & MASK)
#define INV_REG_BIT(REG, MASK) MOD_REG_BIT((REG), (MASK), (MASK) & (~GET_REG_BIT((REG), MASK)));

#define GET_FIELD(reg, mask) (((reg) & (mask)) / ((mask) & ~((mask) << 1)))
#define SET_FIELD(reg, mask, val) (((reg) & ~(mask)) | (((val) * ((mask) & ~((mask) << 1))) & (mask)))

// Use byte access for possibly unaligned address
#define RD_UNALIGNED_U16(REG) ((uint16_t)(*(uint8_t *)(REG)) | (uint16_t)(*(uint8_t *)((uint32_t)(REG) + 1)) << 8)
#define RD_UNALIGNED_U32(REG) ((uint32_t)(*(uint8_t *)(REG)) | (uint32_t)(*(uint8_t *)((uint32_t)(REG) + 1)) << 8 | \
                               (uint32_t)(*(uint8_t *)((uint32_t)(REG) + 2)) << 16 | (uint32_t)(*(uint8_t *)((uint32_t)(REG) + 3)) << 24)
#define WR_UNALIGNED_U16(REG, VAL) \
{ \
  *(uint8_t *)(REG) = (VAL) & 0xff; \
  *(uint8_t *)((uint32_t)(REG) + 1) = ((VAL) >> 8) & 0xff; \
}
#define WR_UNALIGNED_U32(REG, VAL) \
{ \
  *(uint8_t *)(REG) = (VAL) & 0xff; \
  *(uint8_t *)((uint32_t)(REG) + 1) = ((VAL) >>  8) & 0xff; \
  *(uint8_t *)((uint32_t)(REG) + 2) = ((VAL) >> 16) & 0xff; \
  *(uint8_t *)((uint32_t)(REG) + 3) = ((VAL) >> 24) & 0xff; \
}

#define MAX( __x, __y ) ((__x) > (__y) ? (__x) : (__y))
#define MIN( __x, __y ) ((__x) < (__y) ? (__x) : (__y))

static inline void UTIL_JumpToAddress(uint32_t addr) { asm("jr %0" :: "r"(addr)); }
static inline void UTIL_JumpAndLinkToAddress(uint32_t addr) { asm("jalr %0" :: "r"(addr)); }

static inline uint64_t UTIL_GetMcycle(void) { return ((uint64_t)read_csr(mcycleh) << 32) | read_csr(mcycle); }
static inline void UTIL_IdleCycle(uint32_t cycle)
{
  uint64_t mcycle = UTIL_GetMcycle() + cycle;
  while (UTIL_GetMcycle() < mcycle);
}

uint64_t UTIL_UsToMcycle(uint32_t us);
uint32_t UTIL_McycleToUs(uint64_t mcycle);
uint32_t UTIL_GetTick(void);
static uint32_t UTIL_GetUSec(void) { return UTIL_McycleToUs(UTIL_GetMcycle()); }
static uint32_t UTIL_GetMSec(void) { return UTIL_GetTick(); }
void UTIL_IdleUs(uint32_t us);
static inline void UTIL_IdleMs(uint32_t ms) { UTIL_IdleUs(ms * 1000); }

uint8_t UTIL_ReverseBits(uint8_t b);
uint16_t UTIL_ReverseBytes2(uint16_t i);
uint32_t UTIL_ReverseBytes4(uint32_t i);

#ifndef LOGGER_BAUD_RATE
# define LOGGER_BAUD_RATE 500000
#endif
#ifndef BAUD_RATE
# define BAUD_RATE LOGGER_BAUD_RATE
#endif
extern int vprintfmt(void (*putch)(int, void**), void **putdat, const char *fmt, va_list ap, size_t size);
int uart_printf(const char *format, ...);

bool UTIL_StartLogger(void);
bool UTIL_StopLogger (void);

#ifdef SDK_DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)
#define ASSERT(__cond) if (!(__cond)) { printf("Assert failed in function %s, line %d\n", __func__, __LINE__); asm("ebreak"); }
#else
#define dbg_printf(...)
#define ASSERT(__cond)
#endif

void* AlignedMalloc(size_t alignment, size_t required_bytes);
void AlignedFree(void *p);

#ifdef __cplusplus
}
#endif

#endif
