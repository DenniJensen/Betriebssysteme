#ifndef USERLIB_H
#define USERLIB_H

/* user/lib.c */
__attribute__((format(user_printf, 1, 2)))
void user_printf(char *format, ...);

/* lib/scan.c */
int scanf(char *c);

#endif
