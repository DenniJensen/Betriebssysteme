#include <lib.h>

#include "user_lib.h"

/* Unser Thread beendet sich durch einen Software-Interrupt. */
__attribute__ ((noreturn))
void terminate(void)
{
  thread_close();
}

/* Ein einfaches Testprogamm, was als Thread im Usermode ausgeführt werden soll */
void test_print_thread(void *x)
{
  char c = *(char *)x;
  unsigned i;

  for(i = 0; i < 30; i++) {
    user_printf("%c", c);
    if(c >= 65 && c <= 90){
      busy_wait(500000);
    } else {
      thread_sleep(50);
    }
  }

#if 0
  /* Das Programm zu Testzwecken abstürzen lassen */
  if (c == 'D')
    *(int *)0xa0000000 = 0;
  else if (c == 'U')
    asm (".word 0xE7F000F0");
  else if (c == 'X')
    asm ("mov pc, #0x04");
  else if (c == 'B')
    BUG();
#endif
}

void test_scan_thread() {
  while(1) {
    char h;
    scanf(&h);
    thread_create(h);
  }
}
