#include "VideoConsole.h"

/*i should probably move a lot of the code in this file
  into ArchSpecific since almost all of the code applies 
  exclusively to x86 BIOS based systems*/

static volatile char *video = (volatile char*)VGA_TEXT_BUFFER;
static volatile unsigned int currRow;
static volatile unsigned int currColumn;

//clears the framebuffer by filling it with white blank characters sequentially
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
	currRow = 0;
	currColumn = 0;
}

//writes a C++ string to the screen, loops through each character and writes it
//to the framebuffer with a black foreground and white background
void KPrintString(string outputString) { 
	const char *str = outputString.c_str();
	size_t stringLength = outputString.size();

    int color=0b11110000; //white background black text
	for (size_t i = 0; i < stringLength; i++) {
		*video++ = *str++; //write character into framebuffer
        *video++ = color;
		currColumn += 1; //increment the column for each cell that's filled in

		if (currColumn >= VGA_COLUMNS) { //if all the columns on this row are filled in, move on to the next row
			currColumn = 0;
			currRow++;
			video = (char*)(VGA_TEXT_BUFFER + (VGA_CELL_BYTES * VGA_COLUMNS * currRow));
		}
	}
}

//writes a C-style string with a black foreground and white background
void KPrintString(const char* outputString) {
	int color=0b11110000;
	size_t cstringLength = strlen(outputString);
	
	for (size_t i = 0; i < cstringLength; i++) {
		*video++ = *outputString++;
        *video++ = color;
		currColumn += 1; //increment the column for each cell that's filled in

		if (currColumn >= VGA_COLUMNS) { //if all the columns on this row are filled in, move on to the next row
			currColumn = 0;
			currRow++;
			video = (char*)(VGA_TEXT_BUFFER + (VGA_CELL_BYTES * VGA_COLUMNS * currRow));
		}
	}
}