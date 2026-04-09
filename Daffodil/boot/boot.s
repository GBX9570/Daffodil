section .data
stack_end:
	resb 8192 ; reserve 8 kilobytes for the stack
stack_start:

extern early
global _start

section .text
_start:
	mov esp, stack_start
	mov ebp, esp
	push ebx
	push eax
	call early
