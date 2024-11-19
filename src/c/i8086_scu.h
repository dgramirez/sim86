#ifndef SIM86_SRC_C_I8086_SCU_H
#define SIM86_SRC_C_I8086_SCU_H

/* I have mixed feelings about this. I do like Single Compilation Units
 * (scu), however this method is a bit bizzare to me. I'm not saying its
 * bad, and it does keep the source files clean from includes, putting them
 * into a single compile heaeder. I'm simply used to knowing what files are
 * required for my source files.
 *
 * Since I've yet to encounter any serious problems because of this,
 * I will continue to do my includes like this.
 *
 * PS: I'm aware many scu projects still use includes on their source files,
 *     I'm simply trying out another method that I was unfamiliar with.
 *     (Just like the coding style in types.h)
*/

// System (For types.h)
#include <stdint.h>
#include <stddef.h>

// Defines & Types
#include "define.h"
#include "types.h"

// Common Functions
#include "buffer.h"

// Sim86 Header Files
#include "i8086.h"
#include "i8086_decode_helpers.h"

// Sim86 C Files
#include "i8086_decode.c"
#include "i8086.c"

#endif // SIM86_SRC_C_I8086_SCU_H

