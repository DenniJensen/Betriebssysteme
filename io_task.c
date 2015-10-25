#define PIOB 0xfffff600
#define YELLOW_LED (1 << 27)

#define DBGU_CR 0x00
#define DBGU_SR 0x14
#define DBGU_RHR 0x18
#define DBGU_THR 0x1C

#define DBGU 0xFFFFF200

static inline void write_u32(unsigned int addr, unsigned int val)
{
  *(volatile unsigned int *)addr = val;
}

void yellow_on(void)
{
  /* Initialisieren */
  write_u32(PIOB + PIO_PER, YELLOW_LED);
  write_u32(PIOB + PIO_OER, YELLOW_LED);

  /* Anschalten */
  write_u32(PIOB + PIO_SODR, YELLOW_LED);
}

void input_output(void)
{
  write_u32(DBGU + DBGU_CR, YELLOW_LED);
  write_u32(DBGU + PIO_PER, YELLOW_LED);
}

