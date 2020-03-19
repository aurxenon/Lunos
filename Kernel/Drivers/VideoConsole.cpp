#include "VideoConsole.h"

static unsigned int a = 0;

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

void KPrintString(string outputString) {
	const char *str = outputString.c_str();
	
	char *text_buffer = (char*)VGA_TEXT_BUFFER;

    unsigned int b = 0;

	//writes the string to video memory
	while (str[b] != '\0') {
		text_buffer[a] = str[b]; //ascii character
		text_buffer[a+1] = 0b00001111; //color (white text black background)
		b++;
		a = a + 2;
	}
	outputString = "";
}