#include "main.h"

/**
 * init file for qemu
 */
__attribute__((naked, section(".init")))
void _start(void)
{
  kernel_init();
  main();
  for(;;);
}
