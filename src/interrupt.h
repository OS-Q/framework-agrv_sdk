#ifndef _AGM_INTERRUPT_H
#define _AGM_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

#define MCAUSE_INT_MASK  (0x80000000)

static inline void INT_SetISR(void *isr)        { write_csr(mtvec,   isr);         }
static inline void INT_EnableIntGlobal(void)    { set_csr  (mstatus, MSTATUS_MIE); }
static inline void INT_DisableIntGlobal(void)   { clear_csr(mstatus, MSTATUS_MIE); }
static inline void INT_EnableIntExternal(void)  { set_csr  (mie,     MIP_MEIP);    }
static inline void INT_DisableIntExternal(void) { clear_csr(mie,     MIP_MEIP);    }
static inline void INT_EnableIntSoftware(void)  { set_csr  (mie,     MIP_MSIP);    }
static inline void INT_DisableIntSoftware(void) { clear_csr(mie,     MIP_MSIP);    }
static inline void INT_EnableIntTimer(void)     { set_csr  (mie,     MIP_MTIP);    }
static inline void INT_DisableIntTimer(void)    { clear_csr(mie,     MIP_MTIP);    }

static inline void INT_EnableIntLocal (uint32_t irq) { set_csr  (mie, (1 << irq)); } // irq must be one of LOCAL_INTx_IRQn
static inline void INT_DisableIntLocal(uint32_t irq) { clear_csr(mie, (1 << irq)); }

static inline void INT_EnablePLIC(void) { INT_EnableIntExternal(); INT_EnableIntGlobal(); }

// Each interrupt has an enable bit, a pending bit, and a priority. The pending bits are set regardless of the enable
// bits. Reading the claim_complete register will return the highest priority pending interrupt number and clear the
// corresponding pending bit (only for enabled interrupts with above threshold priority). Since Interrupts are numbered
// starting from 1, a read value of 0 means no active interrupt. A write to the claim_complete register will complete
// the interrupt.
typedef struct
{
  __IO uint32_t PRIORITY[0x400]; // 0x0000-
  __IO uint32_t PENDING[0x400];  // 0x1000-
  __IO uint32_t ENABLE[0x7f800]; // 0x2000-
  __IO uint32_t THRESHOLD;       // 0x200000
  __IO uint32_t CLAIM_COMPLETE;  // 0x200004
} PLIC_TypeDef;
#define PLIC_BASE (0xc000000)
#define PLIC ((PLIC_TypeDef *) PLIC_BASE)

// The IRQ number can be greater than word size (XLEN_BITS)
#define IRQ_BIT_OFFSET(__irq)  (__irq % XLEN_BITS)
#define IRQ_WORD_OFFSET(__irq) (__irq / XLEN_BITS)

// PLIC functions. INT_ClaimIRQ and INT_CompleteIRQ should be called only within an ISR!
static inline uint32_t INT_GetIRQThreshold(void)                       { return PLIC->THRESHOLD;         }
static inline uint32_t INT_GetIRQPriorify(uint32_t irq)                { return PLIC->PRIORITY[irq];     }
static inline uint32_t INT_ClaimIRQ(void)                              { return PLIC->CLAIM_COMPLETE;    }
static inline void INT_SetIRQThreshold(uint32_t threshold)             { PLIC->THRESHOLD = threshold;    }
static inline void INT_SetIRQPriority(uint32_t irq, uint32_t priority) { PLIC->PRIORITY[irq] = priority; }
static inline void INT_CompleteIRQ(uint32_t irq)                       { PLIC->CLAIM_COMPLETE = irq;     }

void INT_EnableIRQ(uint32_t irq, uint32_t priority);
void INT_DisableIRQ(uint32_t irq);
bool INT_IsIRQPending(uint32_t irq);

typedef struct
{
  __IO uint32_t MSIP;        // 0x0000, Machine software interrupt pending
       uint32_t RESERVED0[0x0fff];
  __IO uint32_t MTIMECMP_LO; // 0x4000, Machine timer compare
  __IO uint32_t MTIMECMP_HI;
       uint32_t RESERVED1[0x1ffc];
  __IO uint32_t MTIME_LO;    // 0xbff8, Machine timer
  __IO uint32_t MTIME_HI;
} CLINT_TypeDef;
#undef CLINT_BASE
#define CLINT_BASE (0x2000000)
#define CLINT ((CLINT_TypeDef *) CLINT_BASE)

// CLINT functions
static inline uint64_t INT_GetMtime(void)    { return ((uint64_t)CLINT->MTIME_HI)    << 32 | CLINT->MTIME_LO;    }
static inline uint64_t INT_GetMtimeCmp(void) { return ((uint64_t)CLINT->MTIMECMP_HI) << 32 | CLINT->MTIMECMP_LO; }
static inline void INT_SetMtimeLo(uint32_t mtime) { CLINT->MTIME_LO = mtime; }
static inline void INT_SetMtimeHi(uint32_t mtime) { CLINT->MTIME_HI = mtime; }
static inline void INT_SetMtime(uint64_t mtime)
{
  CLINT->MTIME_LO = 0; // So that MTIME_HI will not inadvertently increase
  CLINT->MTIME_HI = mtime >> 32;
  CLINT->MTIME_LO = mtime;
}
static inline void INT_SetMtimeCmp(uint64_t mtime)
{
  CLINT->MTIMECMP_LO = -1; // So that interrupt is not triggered by an intermediate mtimecmp value
  CLINT->MTIMECMP_HI = mtime >> 32;
  CLINT->MTIMECMP_LO = mtime;
}
static inline void INT_TriggerSoftwareInt(void) { CLINT->MSIP = 1; }
static inline void INT_ClearSoftwareInt(void)   { CLINT->MSIP = 0; }

// ISR functions
extern void handle_trap_nonest(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp);
extern void handle_trap_nested(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp);
extern void (**plic_isr)(void);
extern void (**clint_isr)(void);
extern void exception_handler(void);

void INT_Init(void);

#ifdef __cplusplus
}
#endif

#endif
