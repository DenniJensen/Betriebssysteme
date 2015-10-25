#include "io_task.h"

__attribute__((naked, section(".init")))
void _start(void)
{
  input_output();
  for(;;);
}

