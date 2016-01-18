#include <system.h>
#include <lib.h>
#include <dbgu.h>
#include <st.h>

void init_print() {
  printf("----------------------------------------------------------------\n");
  printf("\nKernel initialisiert\n");
  printf("\nStarte erste Anwendung...");
  printf("\nAnwendung ließt ein Zeichen und startet einen neuen Thread.");
  printf("\nSollte ein groß Buchstaben gelesen, worden sein, \n");
  printf("dann benutzt der Thread aktives Warten, ansonsten passives!");
  printf("\n---------------------------------------------------------------\n\n");
}

/*
 * start_kernel() - unser C-Eintrittspunkt
 *
 * Wird direkt nach Initialisierung des Supervisor-Stacks gestartet.
 */
void start_kernel(void)
{
 	/*
 	 * System initialisieren.
 	 */
  init_other_stacks();
  init_exceptions();

  dbgu_init();

  st_init();
  st_set_interval(500);

  scheduler_init();

  init_print();

  extern void test_scan_thread();
  start_new_thread(test_scan_thread,0 ,0);
}
