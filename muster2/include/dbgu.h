#ifndef DBGU_H
#define DBGU_H

void enable_dbgu_interrupts(void);

void dbgu_printf(char* format, ...);

char *dbgu_scan(void);

void memory_dump(unsigned int address, unsigned int length);

#endif
