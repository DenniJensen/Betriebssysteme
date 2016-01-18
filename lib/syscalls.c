#include <syscall.h>
#include <stddef.h>

char global_char_buffer; /*Buffer for exchange char */

int __attribute__((naked)) syscall(int r0, int r1) {
  asm(
    "push {lr}\n"
    "swi #0\n"
    "pop {pc}\n"
  );
  return 0;
}

int putchar(char c) {
  return syscall(PUTCHAR, (int) c);
}

int getchar() {
  return syscall(GETCHAR, 0);
}

int thread_close() {
  return syscall(THREAD_CLOSE, 0);
}

int thread_create(char c) {
  return syscall(THREAD_CREATE, (int) c);
}

int thread_sleep(int time) {
  return syscall(THREAD_SLEEP, time);
}
