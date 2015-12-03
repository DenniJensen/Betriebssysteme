#include <helpers.h>
#include <system.h>
#include <dbgu.h>

#include <stddef.h>

static const char DIGITS[] = "0123456789ABCDEF";

/**
 * convert an int to a string in decimal representation
 */
char *int_to_str(int num) {
  static char buffer[25];
  char *ptr;
  int local_num = num;
  if(local_num < 0) {
    local_num *= -1;
  }

  ptr = &buffer[24];
  *ptr = '\0';

  do {
    ptr--;
    *ptr = DIGITS[local_num%10];
    local_num /= 10;
  } while (local_num != 0);

  if(num < 0) {
    ptr--;
    *ptr = '-';
  }

  return(ptr);
}

char *int_to_hex_str(unsigned int num){
  static char buffer[25];
  char *ptr;

  ptr = &buffer[24];
  *ptr = '\0';

  do {
    ptr--;
    *ptr = DIGITS[num%16];
    num /= 16;
  } while (num != 0);

  return(ptr);
}

void mem_cp(void *dest, const void *src, size_t n) {
  const char *s = src;
  char *d = dest;

  while (n--) {
    *d++ = *s++;
  }

  return dest;
}

//void mem_cp(unsigned int from, unsigned int to, unsigned int length) {
//  unsigned int offset = 0;
//  while(offset < length) {
//    write_32(to + offset, read_32(from + offset));
//    offset += 4;
//  }
//}

static int is_ending(char x) {
  switch(x){
    case '\0':
      return 1;
    case '\r':
      return 1;
    case '\n':
      return 1;
    default:
      return 0;
  }
}

int str_eql(char *str1, char *str2) {
  int index = 0;
  while(str1[index] == str2[index]) {
    index++;
    if(is_ending(str1[index]) || is_ending(str2[index])) {
      return 1;
    }
  }
  return 0;
}
