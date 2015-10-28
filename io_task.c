#include <stdarg.h>
#include "my_io.h"

void input_output(void)
{
  enable_receiver();
  enable_transmitter();

  // in THR schreiben
  print_last_keystroke();
}

