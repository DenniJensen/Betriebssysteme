#include <system.h>
#include <lib.h>
#include <dbgu.h>
#include <st.h>
 
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
 
  	enable_irq(); 
 
 	/*
 	 * Test-Programm vorübergehend hier, bis es durch etwas richtiges
 	 * ersetzt wird. :)
 	 */
 
 	char c; 
 	unsigned int i;
 
 	while (1) {
 		c = dbgu_getc(); 
  		for (i = 0; i < 10; i++) {
 			printf("%c", c); 
  			busy_wait(50000); 
 		}
 	}
}
