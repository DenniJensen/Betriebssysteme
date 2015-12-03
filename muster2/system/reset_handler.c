#include "dbgu.h"

__attribute__((section(".reset_handler"), interrupt("IRQ")))
void _reset_hander(void) {
  dbgu_printf("System has been resetted");
}
