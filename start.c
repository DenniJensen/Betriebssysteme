#include "io_task.h"
#include "my_io.h"


__attribute__((naked, section(".init")))
void _start(void)
{
  my_printf("Programm by Dennis Haegler and Paul Kunze.\n");
  my_printf("Starting simple io programm\n");
  for(;;)
  {
    input_output();
  }
}

