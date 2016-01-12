#include "lib.h"

__attribute__((naked))
int syscall(int syscall_action, int arg1) {
  asm(
      "push {lr}\n"
      "swi #0\n"
      "pop {pc}\n"
     );
  return 0;
}

void put_char(char c)
{
  syscall(PUT_CHAR, c);
}
