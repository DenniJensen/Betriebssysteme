#include "io_task.h"
#include "my_io.h"


__attribute__((naked, section(".init")))
void _start(void)
{
  print_string("Programm by Dennis Haegler and Paul Kunze.\n");
  print_string("Starting simple io programm\n");

  my_printf("This is a  %c\n", 'H');
  my_printf("Iam printing a %s", "STRING");

  for(;;) {
    input_output();
  }
}

