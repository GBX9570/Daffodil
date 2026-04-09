CC     := clang
ASM    := nasm
LD     := ld
GRUBMK := grub-mkrescue

SRC_DIR     := ./
LINKER_SCRIPT := $(SRC_DIR)/linker.ld
ISO_DIR     := isofiles
BOOT_DIR    := $(ISO_DIR)/boot

ISO := daffodil.iso
KERNEL := kernel.bin

CFLAGS := --target=i686-elf \
          -m32 \
          -ffreestanding -nostdlib -nostdlibinc \
          -fno-pic -fno-pie \
          -fno-stack-protector \
          -mno-red-zone \
          -Wall -Wextra -O0 -g \
          -Ifiles/source/include \
          -Ifiles/source/arch


ASMFLAGS := -f elf32

LDFLAGS := -m elf_i386 -T $(SRC_DIR)/linker.ld

C_SOURCES   := $(shell find $(SRC_DIR) -type f -name '*.c')
ASM_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.s')

OBJ_C   := $(C_SOURCES:.c=.o)
OBJ_ASM := $(ASM_SOURCES:.s=.o)
OBJ_ALL := $(OBJ_C) $(OBJ_ASM)

all: $(KERNEL) iso

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

$(KERNEL): $(OBJ_ALL)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJ_ALL)

iso: $(KERNEL)
	mkdir -p $(BOOT_DIR)
	mv $(KERNEL) $(BOOT_DIR)/
	$(GRUBMK) -o $(ISO) $(ISO_DIR)
	find $(SRC_DIR) -type f -name '*.o' -delete
	find $(SRC_DIR) -type f -name '*.d' -delete

run:
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f $(KERNEL)
	find $(SRC_DIR) -type f -name '*.o' -delete
	find $(SRC_DIR) -type f -name '*.d' -delete
	rm -f $(ISO)
