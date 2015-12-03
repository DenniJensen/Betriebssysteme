#include <aic.h>
#include <system.h>
#include <dbgu.h>

#define AIC      0xFFFFF000 /* *** Avanced Interrupt Controller *** */

#define AIC_IECR 0x00000120 /* *** Interrupt Enable Command Register *** */
#define AIC_ISR  0x00000108 /* *** Interrupt Status Register *** */
#define AIC_IPR  0x0000010C /* *** Interrupt Pending Register *** */
#define AIC_IMR  0x00000110 /* *** Interrupt Mask Register *** */

#define SYS_INTERRUPT_MASK (1 << 1) /* *** Mask system (FIQ) interrupts *** */

void aic_initialize(void) {
  write_32(AIC + AIC_IECR, 2);
}

void aic_print_status(void) {
  dbgu_printf("Interrupt Status: %x\n", read_32(AIC + AIC_ISR));
  dbgu_printf("Interrupt Pending: %x\n", read_32(AIC + AIC_IPR));
  dbgu_printf("Interrupt Mask: %x\n", read_32(AIC + AIC_IMR));
  dbgu_printf("Interrupt Core Status: %x\n", read_32(AIC + 0x114));
}
