#define DBGU 0xFFFFF200 // debug unit, 512 Bytes

#define DBGU_CR 0x00 // control register
#define DBGU_SR 0x14 // status register
#define DBGU_RHR 0x18 // receiver
#define DBGU_THR 0x1C // transmitter

#define RXEN (1 << 4) // Turn receiver on
#define RXDIS (1 << 2) // Turn receiver off
#define TXEN (1 << 6) // Turn transmitter on
#define RSTTX (1 << 3) // reset transmitter
#define RXRDY (1 << 0) // receiver ready

#define MAX_CHAR_COUNT 50

static inline void write_u32(unsigned int addr, unsigned int val)
{
  *(volatile unsigned char *)addr = val;
}

static inline unsigned int get_data(unsigned int addr)
{
  return *(volatile unsigned int *)addr;
}

void enable_receiver()
{
  write_u32(DBGU + DBGU_CR, RXEN);
}

void enable_transmitter()
{
  write_u32(DBGU + DBGU_CR, TXEN);
}

void my_printf(char* string, ...)
{
  int i = 0;
  for (i = 0; i < MAX_CHAR_COUNT; ++i) {
    if (string[i] != '\0') {
      if (string[i] == '\r') {
        write_u32(DBGU + DBGU_THR, '\n');
      } else {
        write_u32(DBGU + DBGU_THR, string[i]);
      }
    }
  }
}

void print_last_keystroke()
{
  if(get_data(DBGU + DBGU_SR) & RXRDY) {
    char data = get_data(DBGU + DBGU_RHR);
    if (data == '\r') {
      write_u32(DBGU + DBGU_THR, '\n');
    } else {
      write_u32(DBGU + DBGU_THR, data);
    }
  }
}
