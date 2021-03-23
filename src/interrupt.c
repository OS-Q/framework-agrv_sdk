#include "interrupt.h"
#include "system.h"

void INT_EnableIRQ(uint32_t irq, uint32_t priority)
{
  PLIC->ENABLE[IRQ_WORD_OFFSET(irq)] |= 1 << IRQ_BIT_OFFSET(irq);
  INT_SetIRQPriority(irq, priority);
}

void INT_DisableIRQ(uint32_t irq)
{
  PLIC->ENABLE[IRQ_WORD_OFFSET(irq)] &= ~(1 << IRQ_BIT_OFFSET(irq));
}

bool INT_IsIRQPending(uint32_t irq)
{
  return PLIC->PENDING[IRQ_WORD_OFFSET(irq)] & (1 << IRQ_BIT_OFFSET(irq));
}

void INT_Init(void)
{
  // Claim and complete any existing interrupt
  INT_SetIRQThreshold(PLIC_MAX_PRIORITY);
  for (int i = 0; i < (PLIC_TOTAL_INTERRUPT_COUNT + XLEN_BITS) / XLEN_BITS; ++i) {
    PLIC->ENABLE[i] = ~0;
  }
  uint32_t irq;
  while ((irq = INT_ClaimIRQ())) {
    INT_CompleteIRQ(irq);
  }
  // Set threshold to 0 (lowest) and disable all PLIC interrupts
  INT_SetIRQThreshold(0);
  for (int i = 0; i < (PLIC_TOTAL_INTERRUPT_COUNT + XLEN_BITS) / XLEN_BITS; ++i) {
    PLIC->ENABLE[i] = 0;
  }
  // Disable all internal interrupts
  write_csr(mie, 0);
}

// Declare all the default isr functions and the default isr tables for both PLIC and CLINT, all with weak attributes so
// that they can be overridden in user code.
INT_DECLAR_ISR_FUNCTIONS(__attribute__((weak)));
__attribute((weak)) INT_DECLARE_PLIC_ISR_TABLE;
__attribute((weak)) INT_DECLARE_CLINT_ISR_TABLE;

__attribute__((weak)) void exception_handler(void) { while (1); }

// This is the isr function that can be called from trap entry. Since it is much faster, it is recommended to use this
// instead of the nested version. Interrupt nesting can be avoided by keeping each isr function short, with only
// minimum code and flags. Time consuming functions should be executed from the main process based on flags set in isr,
// not directly from interrupt context.
__attribute__((weak))
void handle_trap_nonest(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp)
{
  if (mcause & MCAUSE_INT_MASK) { // Caused by interrupt
    uint32_t interrupt = mcause & ~MCAUSE_INT_MASK;
    if (interrupt == IRQ_M_EXT) { // Machine external interrupt from PLIC
      // Use a while loop for tail chaining. Continue to service as long as any interrupt exists.
      while ((interrupt = INT_ClaimIRQ())) {
#ifdef SDK_DEBUG
        if (!plic_isr[interrupt]) {
          exception_handler();
        }
#endif
        plic_isr[interrupt]();
        INT_CompleteIRQ(interrupt); // Clear the pending status. This has to be after the other ISR's otherwise the interrupt will be retriggered
      }
    } else {
#ifdef SDK_DEBUG
      if (!clint_isr[interrupt]) {
        exception_handler();
      }
#endif
      clint_isr[interrupt]();
    }
  } else { // Caused by exception
    exception_handler();
  }
}

// This is the isr that supports nested interrupts. It is much slower than the regular version. Since interrupt enable
// and threshold data are saved and restored before and after each isr, the machine register mie, mstatus and the PLIC
// registers CANNOT be modified in any isr.
__attribute__((weak))
void handle_trap_nested(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp)
{
  if (mcause & MCAUSE_INT_MASK) { // Caused by interrupt
    uint32_t interrupt = mcause & ~MCAUSE_INT_MASK;
    if (interrupt == IRQ_M_EXT) { // Machine external interrupt from PLIC
      uint32_t threshold = INT_GetIRQThreshold();
      uint32_t mie       = clear_csr(mie, MIP_MSIP | MIP_MTIP); // Disable machine software and timer interrupts since they have lower priority.
      uint8_t interrupts[PLIC_TOTAL_INTERRUPT_COUNT];
      uint8_t *ptr = interrupts;
      // Claim all pending bits and save the interrupt numbers. Then service them in order.
      while ((interrupt = INT_ClaimIRQ())) {
        *ptr++ = interrupt;
      }
      *ptr = 0;
      INT_SetIRQThreshold(INT_GetIRQPriorify(interrupts[0]));
      asm("fence"); // Make sure threshold is in effect before turning MIE on
      INT_EnableIntGlobal();
      for (ptr = interrupts; ; ) {
        plic_isr[*ptr]();
        INT_CompleteIRQ(*ptr);
        if (*++ptr == 0) {
          break;
        }
        // After current plic_isr is finished, lower threshold based on the next interrupt
        INT_SetIRQThreshold(INT_GetIRQPriorify(*ptr));
      }
      INT_DisableIntGlobal();
      INT_SetIRQThreshold(threshold); // Reset threshold to the saved value
      write_csr(mcause, mcause);
      write_csr(mepc,   mepc);
      write_csr(mie,    mie);
    } else {
      uint32_t mie_clear = 1 << interrupt; // Clear current enable bit
      if (interrupt == IRQ_M_SOFT) {
        mie_clear |= MIP_MTIP; // Clear timer enable
      } else if (interrupt >= LOCAL_INT0_IRQn) {
        mie_clear |= ~(-1U << interrupt); // Clear all lower bits
      }
      uint32_t mie  = clear_csr(mie, mie_clear);
      asm("fence");
      INT_EnableIntGlobal();
      clint_isr[interrupt]();
      INT_DisableIntGlobal();
      write_csr(mcause, mcause);
      write_csr(mepc,   mepc);
      write_csr(mie,    mie);
    }
  } else { // Caused by exception
    exception_handler();
  }
}

#ifndef AGRV_NESTED_INTERRUPT
__attribute__((weak, alias("handle_trap_nonest"))) void handle_trap(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp);
#else
__attribute__((weak, alias("handle_trap_nested"))) void handle_trap(uintptr_t mcause, uintptr_t mepc, uintptr_t *sp);
#endif
