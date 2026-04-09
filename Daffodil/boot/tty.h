#ifndef TTY_H
#define TTY_H

#include <stdint.h>

void clear(void);
void putchar(char s, uint8_t colour);
void print(char* s, uint8_t colour);
void setbg(uint8_t colour);

#endif
