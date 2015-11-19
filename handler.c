#include "my_io.h"

__attribute__((naked, section(".memory_error")))
void handle_abort_error(void) {
  print_string("O no! A memory error\n");
  volatile unsigned int *addr;

  __asm__ __volatile__ (
      "sub lr, lr, #8\n"
      "mov %0, lr" : "=r" (addr)
      );

  my_printf("Data Abort at %p", *(addr));
  for(;;);
}
