#include "lib.h"


__attribute__((naked))
int syscall(int syscall_action, int arg1, int arg2) {
  asm(
      "push {lr}\n"
      "swi #0\n"
      "pop {pc}\n"
     );
  return 0;
}

void put_char(char *c)
{
  syscall(PUT_CHAR, *c, 0);
}

/* void get_char(char *c) */
/* { */
/* } */

void banane()
{
  printf("banane");
}

