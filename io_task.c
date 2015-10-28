#include <stdarg.h>
#include "my_io.h"

int flag = 1;

void input_output(void)
{
  enable_receiver();
  enable_transmitter();

  if (flag) {
    char *text = "Hello World";
    my_printf(text);
    flag = 0;
  }

  // in THR schreiben
  print_last_keystroke();
}

