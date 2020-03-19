#pragma once

#include <ArchSpecific/String.h>

#define VGA_ROWS 25
#define VGA_COLUMNS 80
#define VGA_CELL_BYTES 2
#define VGA_TEXT_BUFFER 0xb8000

void KPrintString(string);
void KClear();