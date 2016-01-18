#ifndef SYSCALL_H
#define SYSCALL_H

enum syscalls {
  PUTCHAR,
  GETCHAR,
  THREAD_CLOSE,
  THREAD_CREATE,
  THREAD_SLEEP
};

extern char global_char_buffer;

/* lib/syscalls */
int putchar(char c);

int getchar();

int thread_close();
int thread_create(char c);
int thread_sleep(int seconds);
#endif
