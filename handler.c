#include "my_io.h"

__attribute__(())
  void handle_swi(void) {
    my_printf("Software Interrupt\n");
  }

__attribute__(())
  void handle_prefetch(void) {
    // TODO 4 steps back
    my_printf("Prefetch abort\n");
  }

__attribute__(())
  void handle_abort(void) {
    volatile unsigned int *addr;

    __asm__ __volatile__ (
        "sub lr, lr, #8\n"
        "mov %0, lr" : "=r" (addr)
        );

    my_printf("ERROR FOUND\n");
    my_printf("Data Abort at %p", *(addr));
    for(;;);
  }
