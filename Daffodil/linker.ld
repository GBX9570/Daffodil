ENTRY(_start)

SECTIONS
{
    . = 2M;

    .multiboot :
    {
        *(.multiboot_header)
    }

    .text :
    {
        *(.text*)
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        *(.bss*)
        *(COMMON)
        . = ALIGN(4096);
    }

    . = ALIGN(16);
    stack_bottom = .;
    . += 0x2000;
    stack_top = .;
}
