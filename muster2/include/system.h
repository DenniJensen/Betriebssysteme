#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/* system/exception.c */
void init_exceptions_handlers(void);

static inline void write_8(unsigned int addr, char val) {
  *(volatile unsigned int *)addr = val;
}

static inline void write_32(unsigned int addr, unsigned int val) {
  *(volatile unsigned int *)addr = val;
}

static inline char read_8(unsigned int addr) {
  return *(volatile unsigned int *)addr;
}

static inline unsigned int read_32(unsigned int addr) {
  return *(volatile unsigned int *)addr;
}

#endif
