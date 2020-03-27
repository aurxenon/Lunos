#include "VideoConsole.h"

/*i should probably move a lot of the code in this file
  into ArchSpecific since almost all of the code applies 
  exclusively to x86 BIOS based systems*/

static volatile char *video = (volatile char*)VGA_TEXT_BUFFER;

void KClear() {
	char *text_buffer = (char*)VGA_TEXT_BUFFER;
	unsigned int j = 0;
	unsigned int screensize;

	//clears the screen
	screensize = VGA_COLUMNS * VGA_ROWS * VGA_CELL_BYTES;
	while (j < screensize) {
		text_buffer[j] = ' '; //blank character
		text_buffer[j+1] = 0xff; //color byte
		j = j + 2; //skips ahead 2 bytes to next cell
	}
}

void KPrintString(string outputString) { 
	const char *str = outputString.c_str();
	size_t stringLength = outputString.size();

    int color=0b11110000; //white background black text
	for (size_t i = 0; i < stringLength; i++) {
		*video++ = *str++; //write character into framebuffer
        *video++ = color;
	}
}

void KPrintString(const char* outputString) {
	int color=0b11110000;
	size_t cstringLength = strlen(outputString);
	for (size_t i = 0; i < cstringLength; i++) {
		*video++ = *outputString++;
        *video++ = color;
	}
}