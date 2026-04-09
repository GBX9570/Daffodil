#include "tty.h"
#include "printf.h"
#include "multiboot2.h"

extern void postgdt(void);

void page(void) {
	print("GDT successfully setup!\n", 0x20);
	
	postgdt();
}

