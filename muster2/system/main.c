#include <main.h>
#include <dbgu.h>
#include <helpers.h>
#include <timer.h>
#include <aic.h>
#include <exception.h>
#include <system.h>

#define MC_RCR 0xFFFFFF00 /* Remap Control Register */
#define RCB  (1 << 0) /* Remap command bit */

#define INTERNAL_RAM ((void *)0x00200000)

extern char _exception_vectors_begin[];
extern char _exception_vectors_end[];

void kernel_init(void) {
  init_exceptions_handlers();
  dbgu_printf("Installed IVT\n");

  enable_irq();
  aic_print_status();
  aic_initialize();
  aic_print_status();
  enable_dbgu_interrupts();
}
/**
 * global file for implementation test, loaded in start.c
 */
void main(void) {
  dbgu_printf("type in [swi, prefetch, abort]\n");

  char *input;
  for(;;) {
    input = dbgu_scan();
    if(str_eql(input, "swi")) {
      __asm__ __volatile__("SWI #1");
    }
    if(str_eql(input, "prefetch")) {
      dbgu_printf("Sorry, I am too stupid to cause a prefetch error\n");
      continue;
    }
    if(str_eql(input, "abort")) {
      dbgu_printf("abort input");
      read_32(0xFFFFF00U);
    }
    dbgu_printf("Unknown: %s\n", input);
  }
}
