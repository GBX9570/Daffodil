#include "../misc/tty.h"
#include "../misc/printf.h"
#include <stdint.h>
#include "multiboot.h"

extern void setup(void);

void early(unsigned long magic, unsigned long addr) {
	clear();

 	// multiboot code starts here

	/*
	a lot of this code is sourced from:
	https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Example-OS-code
	because it is better than anything i would cook up
	the copyright notice is in mbcp.txt in /Daffodil/Licenses!!
	Based on version 0.6.96 of the multiboot spec
	*/

	multiboot_info_t *mbi;

	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		print("The multiboot magic number is wrong. ", 0x04);
		printf("0x%x", (unsigned) magic);
		asm volatile("hlt");
	} else {
		print("Multiboot Magic is correct!\n", 0x02);
	}

	mbi = (multiboot_info_t*) addr;

	print("Flags: ", 0x0A);
	printf("0x%x\n", (unsigned) mbi->flags);

	multiboot_memory_map_t *mmap;

	printf("mmap_addr = 0x%x, mmap_length = 0x%x\n", (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);

	for(mmap = (multiboot_memory_map_t*) mbi->mmap_addr;
				(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
				mmap = (multiboot_memory_map_t*) ((unsigned long) mmap + mmap -> size + sizeof(mmap->size)))

		printf("Memory Size = 0x%x, Base Address = 0x%x%x08x,\n length = 0x%x%08x, type = 0x%x\n",
				(unsigned) mmap->size,
				(unsigned) (mmap->addr >> 32),
				(unsigned) (mmap->addr & 0xffffffff),
				(unsigned) (mmap->len >> 32),
				(unsigned) (mmap->len & 0xffffffff),
				(unsigned) mmap->type);
 	
	// multiboot code ends here
	
	
	setup();

	print("Something went wrong. You shouldn't be here.", 0x04);
	asm("cli; hlt");
}

void postgdt(void) {
	asm volatile("cli; hlt");
}
