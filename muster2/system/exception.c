#include <main.h>
#include <dbgu.h>
#include <helpers.h>
#include <system.h>

#define MC_RCR 0xFFFFFF00 /* Remap Control Register */
#define RCB  (1 << 0) /* Remap command bit */

#define INTERNAL_RAM ((void *)0x00200000)

extern char _exception_vectors_begin[];
extern char _exception_vectors_end[];

/* initital exception and remapping */
void init_exceptions_handlers(void) {
  /* *** install IVT *** */
  write_32(MC_RCR, RCB);
  mem_cp(INTERNAL_RAM, _exception_vectors_begin,
       _exception_vectors_end - _exception_vectors_begin);
}


void handle_undef(void) {
  dbgu_printf("Undefined Instruction");
  main();
}

void handle_swi(void) {
  dbgu_printf("Software Interrupt\n");
  main();
}

void handle_prefetch(void) {
  dbgu_printf("Prefetch abort\n");
  main();
}

void handle_abort(void) {
  volatile unsigned int *addr;

  // LR contains instruction that cause memory abort
  // lr - 8 because pc + 8
  __asm__ __volatile__ (
      "sub lr, lr, #8\n"
      "mov %0, lr" : "=r" (addr)
      );
  dbgu_printf("Data Abort at %p %x\n", addr, *(addr));
  main();
}

void unhandled(void) {
  dbgu_printf("Reset or Reserved");
}

void handle_irq(void) {
  dbgu_printf("IRQ exception\n");
  main();
}

void handle_fiq(void) {
  dbgu_printf("FIQ exception");
  main();
}
