#include <dbgu.h>
#include <helpers.h>
#include <system.h>

#include <stdarg.h>

#define DBGU 0xfffff200

#define DBGU_CR  0x00 /* control register */
/* DBGU_CR register bitmasks */
#define TXEN     (1 << 6)  /* turn on transmitter */
#define TXDIS    (1 << 7)  /* turn off transmitter */
#define RXEN     (1 << 4)  /* turn on receiver */
#define RSTRX    (1 << 2)  /* turn off receiver */

#define DBGU_IER 0x08     /* interrupt enable register */
/* DBGU_IER register bitmasks */
#define RXRDY_IER (1 << 0)  /* enable read interrupts */
#define TXRDY_IER (1 << 1)  /* enable write interrupts */

#define DBGU_SR  0x14 /* status register */
/* DBGU_SR register bitmasks */
#define TXRDY    (1 << 1)  /* transmitter ready */
#define RXRDY    (1 << 0)  /* Receiver ready */

#define DBGU_RHR 0x18 /* receive holding register */
#define DBGU_THR 0x1C /* transmit holding register */

#define READ_COUNT 10 /* number of digits to read */

/* *************************** */
/* ENABLE INTERRUPTS DBGU      */
/* *************************** */
static void enable_read_interrupts(void) {
  write_8(DBGU + DBGU_IER, RXRDY_IER);
}

static void enable_write_interrupts(void) {
  write_8(DBGU + DBGU_IER, TXRDY_IER);
}

void enable_dbgu_interrupts(void) {
  enable_read_interrupts();
//  enable_write_interrupts();
}

/* **************************** */
/* WRITE MESSAGES OVER DBGU     */
/* **************************** */
static void enable_transmitter(void) {
  write_8(DBGU + DBGU_CR, TXEN);
}

static void disable_transmitter(void) {
  write_8(DBGU + DBGU_CR, TXDIS);
}

/* write char to transmit register */
static void print_char(char x) {
  write_8(DBGU + DBGU_THR, x);
}

/* traverse over char pointer till read '\0' to write  */
static void print(char * string) {
  char *traverse;
  for (traverse = string; *traverse != '\0'; traverse++) {
    print_char(*traverse);
  }
}

__attribute__((format(dbgu_printf, 1, 2)))
void dbgu_printf(char* format, ...) {
  enable_transmitter();
  char *traverse;
  unsigned int i;
  int value;
  char *string;

  // initilizing printf arguments
  va_list arg;
  va_start(arg, format);

  for (traverse = format; *traverse != '\0'; traverse++) {
    while(*traverse != '%') {
      if(*traverse == '\0') {
        return;
      }
      print_char(*traverse);
      traverse++;
    }
    traverse++;
    if(*traverse == '\0'){
      return;
    }

    // fetching and executing arguments
    switch(*traverse) {
      case 'c' : value =  va_arg(arg, int); // Fetch integer;
                 if (value < 0) {
                  value = -value;
                  print_char('-');
                  //dbgu print char -
                 }
                 print(int_to_str(value));

                 break;
      case 's' : string = va_arg(arg, char*); // Fetch char argument
                 print(string);
                 break;
      case 'x' : i = va_arg(arg, unsigned int); // unsigned int to hex
                 print("0x");
                 print(int_to_hex_str(i));
                 break;
      case 'p' : i = (int) va_arg(arg, void *); // void * to hex
                 print("0x");
                 print(int_to_hex_str(i));
                 break;
      default:
                 break;
    }
  }

  // closing argument list for clean up
  va_end(arg);
  disable_transmitter();
}

/* **************************** */
/* READ MESSAGES OVER DBGU      */
/* **************************** */

/* enable receiver */
static void enable_receiver(void) {
  write_8(DBGU + DBGU_CR, RXEN);
}

/* disable receiver */
static void disable_receiver(void) {
  write_8(DBGU + DBGU_CR, RSTRX);
}

/* check receive register if receiver on */
static char dbgu_scan_char(void) {
  if(read_32(DBGU + DBGU_SR) & RXRDY) {
    return (char) read_32(DBGU + DBGU_RHR);
  }
  return '\0';
}

/* read from register READ_COUNT  */
char* dbgu_scan(void) {
  static char buffer[READ_COUNT];
  enable_receiver();
  int buffer_index = 0;

  while(buffer_index < READ_COUNT - 1 &&
      buffer[buffer_index - 1] != '\r' && buffer[buffer_index] != '\n') {
    buffer[buffer_index] = dbgu_scan_char();
    if(buffer[buffer_index] != '\0') {
      buffer_index++;
    }
  }
  buffer[buffer_index] = '\0';
  disable_receiver();
  return buffer;
}

void memory_dump(unsigned int address, unsigned int length) {
  unsigned int counter = 0;
  dbgu_printf("Memory Dump: \n");
  while (counter < length) {
    dbgu_printf("%x: %x\n", address + counter, read_32(address + counter));
    counter += 4;
  }
}
