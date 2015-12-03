#include <timer.h>
#include <system.h>

#define ST 0xfffffd00

#define ST_PIMR  0x04 /* period interval mode register */
#define MAX_PERIOD 65536

#define ST_IER   0x14 /* enable interrupt register */
/* ST_IER register bitmasks */
#define PITS (1 << 0) /* enable period interval timer status interrups*/

/* ********************************* */
/* SET PERIOD OF INTERRUPTS          */
/* ********************************* */
static void set_period_interval_timer(int val) {
  write_32(ST + ST_PIMR, val);
}

void set_period_interval(int period) {
  if (period < MAX_PERIOD) {
    set_period_interval_timer(period);
  } else {
    set_period_interval_timer(MAX_PERIOD);
  }
}

/* *********************************** */
/* SYSTEM TIMER INTERRUPTS             */
/* *********************************** */
static void enable_period_interrupts(void) {
  write_8(ST + ST_IER, PITS);
}

void enable_system_timer_interrupts(void) {
  enable_period_interrupts();
}
