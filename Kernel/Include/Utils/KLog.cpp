#include "KLog.h"

void KClear() {
	char *text_buffer = (char*)VGA_TEXT_BUFFER;
	unsigned int j = 0;
	unsigned int screensize;

	//clears the screen
	screensize = VGA_COLUMNS * VGA_ROWS * VGA_CELL_BYTES;
	while (j < screensize) {
		text_buffer[j] = ' '; //blank character
		text_buffer[j+1] = 0; //color byte
		j = j + 2; //skips ahead 2 bytes to next cell
	}
}

void KLog(string format) {
    const char *str = format.c_str();
	
	char *text_buffer = (char*)VGA_TEXT_BUFFER;
	unsigned int i = 0;
	unsigned int j = 0;

	KClear();

	//writes the string to video memory
	while (str[j] != '\0') {
		text_buffer[i] = str[j]; //ascii character
		text_buffer[i+1] = 0b00001111; //color (white text black background)
		++j;
		i = i + 2;
	}
}