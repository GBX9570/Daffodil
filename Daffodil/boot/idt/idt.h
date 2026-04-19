#ifndef IDT_H
#define IDT_H

#include <stdint.h>

void set_gate(uint8_t vector, void* offset, uint8_t seg, uint8_t flags);

void loadidt();

#endif
