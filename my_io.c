#include <stdarg.h>

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

#define MAX_CHAR_COUNT 100

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

/**
 * Prints a single char into the Debug Unit console.
 */
void print(char c)
{
  write_u32(DBGU + DBGU_THR, c);
}

/**
 * Prints a complete string into the Debug Unit console.
 */
void print_string(char* string)
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
    char c = get_data(DBGU + DBGU_RHR);
    if (c == '\r' || c == '\n') {
      print('\n');
    } else {
      print(c);
    }
  }
}

static void print_hex(unsigned int val, int do_prefix, int length)
{
  char *hex_mask = "0123456789abcdef";
  int i;

  if (do_prefix) {
    print('0');
    print('x');
  }

  /* Nibble von links nach rechts durchgehen: 0x76543210 */
  for (i = 7; i >= 0; i--) {
    unsigned int nibble = (val >> (4 * i)) & 0xf;

    /* ggf. führende Nullen überspringen */
    if (!nibble && i >= length)
      continue;

    print(hex_mask[nibble]);

    /* nach erster Ausgabe keine weiteren Nullen ignorieren */
    length = 8;
  }
}

/**
 * This is code is inspired by the man page of <stdarg>
 */
void my_printf(char *string, ...)
{
  va_list ap, ap2;
  char c, *s;
  va_start(ap, string);
  va_copy(ap2, ap);

  while (*string != '\0') {
    if(*string != '%') {
      print(*string++);
      continue;
    }
    switch(*string) {
      case 'c':
        c = va_arg(ap, int);
        print(c);
        break;
      case 's':
        s = va_arg(ap, char *);
        print_string(s);
        break;
      case 'd':
        c = (char) va_arg(ap, int);
        print(c);
        break;
      case 'p':
        print_hex(va_arg(ap, unsigned int), 1, 8);
      case '%':
        print('%');
      default:
        print('%');
        print(*string);
    }
    string++;
  }
  va_end(ap);
  va_end(ap2);
}
