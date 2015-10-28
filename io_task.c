#include <stdarg.h>

#define DBGU 0xFFFFF200 // 512 Bytes

#define DBGU_CR 0x00
#define DBGU_SR 0x14
#define DBGU_RHR 0x18 // receiver
#define DBGU_THR 0x1C // transmitter

#define RXEN (1 << 4) // Turn receiver on
#define RXENX (1 << 2) // Turn receiver off
#define TXEN (1 << 6) // Turn transmitter on
#define RSTTX (1 << 3) // reset transmitter
#define RXRDY (1 << 0)

#define MAX_CHAR_COUNT 11

static inline unsigned int get_data(unsigned int addr)
{
  return *(volatile unsigned int *)addr;
}

static inline void write_u32(unsigned int addr, unsigned int val)
{
  // change to bit not int
  *(volatile unsigned char *)addr = val;
}

void input_output(void)
{
  // Receiver anschalten
  write_u32(DBGU + DBGU_CR, RXEN);

  // Transmitter aktivieren
  write_u32(DBGU + DBGU_CR, TXEN);

  // in THR schreiben
  if(get_data(DBGU + DBGU_SR) & RXRDY) {
    write_u32(DBGU + DBGU_THR, get_data(DBGU + DBGU_RHR));
  }
}

