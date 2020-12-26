#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>
#include <ArchSpecific/multiboot.h>
#include <LibStandard/Bitmap.h>
#include <LibStandard/CString.h>

#include "PageTable.h"
#include "PageDirectory.h"
#include "CPU.h"

#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE

/*
    Turns on paging.
*/
void InitializeMemoryManager(void* kernelPageArea, multiboot_info_t* mbd);
void CreateKernelPages(void* kernelPageArea);