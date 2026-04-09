#include <stdint.h>

void putchar(char s, uint8_t colour);

int cursor = 0;

void clear() {
	uint16_t* vga = (uint16_t*)0xB8000;
	int i = 0;
	while(i < 2000) {
		vga[i] = (0x00 << 8) | ' ';
		i++;
		cursor++;
	}
	cursor = 0;
}

void setbg(uint8_t colour) {
	uint16_t* vga = (uint16_t*)0xB8000;
	int i = 0;
	while(i < 2000) {
		vga[i] = (colour << 8) | ' ';
		i++;
		cursor++;
	}
	cursor = 0;
}

void putchar(char s, uint8_t colour) {
	uint16_t* vga = (uint16_t*)0xB8000;
	if(s == '\n') {
		cursor = ((cursor / 80) + 1) * 80;
		return;
	}

	if(cursor == 2000) {
		clear();
	}
	
	vga[cursor] = (colour << 8) | s;
	cursor++;
}

void print(char* s, uint8_t colour) {
	while(*s) {
		putchar(*s, colour);
		s++;
	}
}
