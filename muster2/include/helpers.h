#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>

char *int_to_str(int num);

char *int_to_hex_str(unsigned int num);

void mem_cp(void *dest, const void *src, size_t n);

//void mem_cp(unsigned int from, unsigned int to, unsigned int length);

int str_eql(char *str1, char *str2);

#endif
