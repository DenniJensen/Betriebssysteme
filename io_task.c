
#define DBGU 0xFFFFF200

#define DBGU_CR 0x00
#define DBGU_SR 0x14
#define DBGU_RHR 0x18
#define DBGU_THR 0x1C

#define TURN_ON 1

#define RXEN 4
#define TXEN 6

static inline void write_u32(unsigned int addr, unsigned int val)
{
  *(volatile unsigned int *)addr = val;
}

static inline void read(unsigned int addr, volatile unsigned int* val)
{
  *(volatile unsigned int *)addr = (unsigned int)&(*(val));
}

void input_output(void)
{
// Receiver anschalten
write_u32(DBGU + DBGU_CR + RXEN, TURN_ON);
// Transmitter aktivieren
// Bad offset
// write_u32(DBGU + DBGU_CR + TXEN, TURN_ON);

// in THR schreiben
write_u32(DBGU + DBGU_THR, 'h');
write_u32(DBGU + DBGU_THR, 'a');
write_u32(DBGU + DBGU_THR, 'c');
write_u32(DBGU + DBGU_THR, (unsigned int)&(*((volatile unsigned int *)DBGU + DBGU_SR)));

}

