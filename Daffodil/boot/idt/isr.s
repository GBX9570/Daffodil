extern central
global isr_stub

isr_stub:
	pusha
	call central
	add esp, 4
	iret

