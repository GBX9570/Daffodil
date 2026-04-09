section .multiboot_header
header_start:
    dd 0xe85250d6
    dd 0
    dd header_end - header_start

    dd 0xFFFFFFFF - (0xe85250d6 + 0 + (header_end - header_start)) + 1

	; memory map tag
    align 8
	dw 6	; type
	dw 0 	; flags
	dd 16   ; size

	; end tag
    align 8
    dw 0
    dw 0 
    dd 8
header_end:
