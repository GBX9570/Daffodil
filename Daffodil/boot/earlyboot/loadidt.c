#include "../misc/printf.h"
#include "../misc/tty.h"
#include "../idt/idt.h"

void idt(void) {
	loadidt();

	print("GDT Successfully Set-up!\n", 0x20);
	print("IDT Successfully Set-up!\n", 0x20);

	int x = 0;
	int y = 0;

	int z = x / y;

	printf("%d", z);

	asm volatile("cli; hlt");
}
