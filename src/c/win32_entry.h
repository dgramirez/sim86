#ifndef SIM86_SRC_C_WIN32_ENTRY_H
#define SIM86_SRC_C_WIN32_ENTRY_H

// Application
#include "i8086_scu.h"

// System
#include <windows.h>
#ifdef _ZIG
	unsigned int _tls_index = 0;
#endif

// Platform-Specific Functions
local void
win32_pause();

local void
win32_print(s8 s);

local void *
win32_getargs(i32 *argc, char **argv);

local void *
win32_openfile(char *filepath);

local b32
win32_readfile(s8 *out,
               void *file,
               usz size);

local void
win32_write(buf8 *b);

#endif // SIM86_SRC_C_WIN32_ENTRY_H

