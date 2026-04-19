#include "../misc/printf.h"
#include "../misc/tty.h"

void central() {
	printf("Something went wrong\n");

	asm volatile("cli; hlt");
}
