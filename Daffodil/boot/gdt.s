;
;	THE GDT
;
; 0 = Access, set to 1 except for edge cases
; 1 = RW, read/write
; always read never write for code
; always write never read for data
; 2 = DC
; if set to 0 then segment can only be executed from DPL defined ring
; if set to 1 then segment can be executed from a ring lower or equal to the DPL
; 3 = Executable, if set then it is a code segment
; 4 = descriptor bit, if set then it is a code/data segment, else it is a system segment
; 5-6 = DPL
; chooses the privilege level of the segment. 0 is kernel, 3 is userland, 1/2 are mostly unused
; 7 = present, set to one for any segment that is going to be used
; 
; an example kernel code segment:
; 0x10011011
;
;

;
; 0 - 15 = limit
; 20 bit value, maximum addressable unit
; 16 - 31 = base
; 32 bit address that says where the segment begins
; 32 - 39 = base
; same as before (i think?)
; 40 - 47 = access
; the stuff above that makes up the kernel code segments
; 48 - 51 = limit
; same as the other limit
; 52 - 55 = flags
; stuff like granularity
; 56 - 64 = base
; same as the other base
;
;

; flags
;
; 0 = reserved
; leave alone
; 1 = long mode flag
; if set then the segment is for long mode
; 2 = size flag
; if = then 16 bit protected mode segment, if 1 then 32 bit protected mode segment
; 3 = granularity
; if 0 then the limit is in 1 byte blocks, if set then the limit is in 4KiB blocks (based on paging)
;

; all in all, the structure is:
; limit (low 16 bits) - dw
; base (low 16 bits) - dw 
; base (middle 8 bits) - db
; access - db
; limit (high 4 bits) and flags - db
; base (high 8 bits) -db
;

BITS 32

start:

	; null
	dd 0x0
	dd 0x0

	; kernel code
	dw 0xffff
	dw 0x0
	db 0x0
	db 0b10011010
	db 0b11001111
	db 0b0
	
	; kernel data
	dw 0xffff
	dw 0x0
	db 0x0
	dq 0b10010010
	db 0b11001111
	db 0x0
end:

descriptor:
	dw end - start - 1
	dd start

global setup
extern page
	
setup:
	lgdt[descriptor]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:return

return:
	call page
	
