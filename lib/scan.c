#include <stddef.h>
#include <syscall.h>
#include <lib.h>

int scanf(char *c) {
  getchar();
  *c = global_char_buffer;
  return 0;
}
