section .bss
stack_top:
	resb 8192 ; reserve 8 kilobytes for the stack
stack_bottom:

extern early
global _start

section .text
_start:
	cli
	mov esp, stack_bottom
	push ebx
	push eax
	call early
	hlt
