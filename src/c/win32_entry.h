#ifndef SIM86_SRC_C_WIN32_ENTRY_H
#define SIM86_SRC_C_WIN32_ENTRY_H

// Application
#include "i8086_scu.h"

// System
#include <windows.h>
#ifdef _ZIG
	unsigned int _tls_index = 0;
#endif

////////////////////////
// Required for sim86 //
////////////////////////
local void *
win32_openfile(char *filepath);

local b32
win32_readfile(u8 *out,
               u16 *ip,
               void *file,
               usz size);

local void
win32_write(buf8 *b);

////////////////////////////
// Win32 Helper Functions //
////////////////////////////

local void
win32_pause();

local void
win32_print(s8 s);

local void *
win32_getargs(i32 *argc,
              char **argv,
              void *buffer,
              int size);

#endif // SIM86_SRC_C_WIN32_ENTRY_H

