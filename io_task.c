#include <stdarg.h>

#define DBGU 0xFFFFF200 // 512 Bytes

#define DBGU_CR 0x00
#define DBGU_SR 0x14
#define DBGU_RHR 0x18
#define DBGU_THR 0x1C

#define TURN_ON 0x01

#define RXEN 0x04
#define TXEN 0x06

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
  // Bad offset
  write_u32(DBGU + DBGU_CR, TXEN);

  // in THR schreiben
  write_u32(DBGU + DBGU_THR, 'h');
  write_u32(DBGU + DBGU_THR, 'a');

  write_u32(DBGU + DBGU_THR, (DBGU + DBGU_RHR));
}

