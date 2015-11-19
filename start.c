#include "io_task.h"
#include "my_io.h"


__attribute__((section(".init")))
void _start(void)
{
  print_string("Programm by Dennis Haegler and Paul Kunze.\n");
  /* print_string("Starting simple io programm\n"); */

  input_output();
  for(;;) {
  }
}

