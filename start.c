#include "io_task.h"

__attribute__((naked, section(".init")))
void _start(void)
{
  for(;;)
  {
    input_output();
  }
}

