#include "tty.h"
#include "multiboot2.h"
#include "printf.h"
#include <stdint.h>

extern void setup(void);

void early(unsigned long magic, unsigned long addr) {
	clear();

	struct multiboot_tag *tag;
	unsigned size;

	if(magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		print("The multiboot magic is not correct.\n", 0x04);
		printf("Magic passed: 0x%x\n", magic);
		asm volatile("cli; hlt");
	}

	if(addr & 7) {
		print("The MBI is not correct.\n", 0x04);
		printf("MBI passed: 0x%x\n", addr);
		asm volatile("cli; hlt");
	}

	size = *(unsigned *)addr;
	printf("MBI size: 0x%x\n", size);
	printf("Magic passed: 0x%x\n", magic);

	multiboot_memory_map_t *mmap;

	for(tag = (struct multiboot_tag*) (addr + 8);
		tag -> type != MULTIBOOT_TAG_TYPE_END;
		tag = (struct multiboot_tag*) ((multiboot_uint8_t*) tag + ((tag -> size + 7) & ~7)))

    for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
         (multiboot_uint8_t *) mmap < (multiboot_uint8_t *) tag + tag->size;
         mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + ((struct multiboot_tag_mmap *) tag)->entry_size))

	/*
		this is a very dense piece of code so ill do my best to explain

		mmap = ((struct multiboot_tag_mmap*) tag) -> entries; 

		mmap inherits the value of entries in the struct multiboot_tag_mmap, tag is a pointer that accesses said struct
		in a more normal scenario this would literally by x = (struct*)y -> element; but because the names are long
		it looks more confusing


		(uint8_t*) mmap < (uint8_t*) tag + tag-> size;

		interate through the memory maps till it is no longer smaller than tag + size from the mboot tag struct


		mmap = (multiboot_memory_map_t*) ((unsigned long) mmap + ((struct multiboot_tag_mmap*) tag) -> entry_size))

		the sum of mmap and entry_size from the struct is typecasted into multiboot_memory_map_t* and then that value
		is given to mmap
	*/
              printf (" base_addr = 0x%x%x,"
                      " length = 0x%x%x, type = 0x%x\n",
                      (unsigned) (mmap->addr >> 32),
                      (unsigned) (mmap->addr & 0xffffffff),
                      (unsigned) (mmap->len >> 32),
                      (unsigned) (mmap->len & 0xffffffff),
                      (unsigned) mmap->type);

	setup();

	print("Something went wrong. You shouldn't be here.", 0x04);
	asm("cli; hlt");
}

void postgdt(void) {
	asm volatile("cli; hlt");
}
