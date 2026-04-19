#include <stdint.h>
#include "../misc/printf.h"

extern void isr_stub(void);

typedef struct {
		uint16_t offset_l; // 0 - 15, low 16 bits of address to ISR
		uint16_t segment;  // 16 - 31, must point to a code segment of GDT
		uint8_t  reserved; // 32 - 39, reserved
		uint8_t  flags;    // 40 - 47, flags (gate type, DPL and present (must always be set to 1))
		uint16_t offset_h; // 48 - 64, high 16 bits of address to ISR
} __attribute__((packed)) entry;

static entry idt[256];

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr;

void set_gate(uint8_t vector, void* offset, uint8_t seg, uint8_t flags) {
	entry* entries = &idt[vector];

	entries->offset_l = (uint32_t) offset & 0xFFFF;
	entries->segment  = seg;
	entries->reserved = 0;
	entries->flags    = flags;
	entries->offset_h = (uint32_t) offset >> 16;

	// loosely based off the osdev idt descriptor guide for this function ONLY
}


void loadidt() {
	idtr* info;

	const int maxsize = 256;

	info->base =  (uintptr_t)&idt[0];
	info->limit = (maxsize * 8) - 1;

	int i = 0;
	while(i != 32) {
		set_gate(i, isr_stub, 0x08, 0x8E);
		i++;
	}

	asm volatile("lidt %0" : : "m"(info));
	asm volatile("sti");
}
