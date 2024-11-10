#ifndef SIM86_SRC_C_STD_ENTRY_H
#define SIM86_SRC_C_STD_ENTRY_H

// Application
#include "i8086_scu.h"

// System
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Platform-Specifics functions
local void *
std_openfile(char *filepath);

local b32
std_readfile(u8 *out,
             u16 *ip,
             void *file,
             usz size);

local void
std_write(buf8 *b);

#endif // SIM86_SRC_C_STD_ENTRY_H

