#ifndef SIM86_SRC_C_TYPES_H
#define SIM86_SRC_C_TYPES_H

/* Trying this C coding style from null program
 * https://nullprogram.com/blog/2023/10/08/
 *
 * It is **slightly** modified for my taste
 * eg. I like sz for size
 *
 * Also going to attempt to avoid hungarian notation with this.
 * I generally like to reinforce the data types in the name, but
 * maybe I'll get a hang of this without it.
 */

////////////////
// Primitives //
////////////////
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef size_t   usz;

typedef int8_t     i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef ptrdiff_t isz;

typedef float f32;
typedef double f64;

typedef int8_t     c8;
typedef uint8_t  byte;
typedef uint16_t  c16;
typedef int32_t   b32;

///////////////////////
// Buffers & Strings //
///////////////////////
#define s8(s) (s8){(u8 *)s, lengthof(s)}
typedef struct {
	u8 *data;
	usz len;
} s8;

typedef struct {
	u8   *data;
	void *fd;
	usz   len;
	usz   cap;
	b32   err;
} buf8;

//////////////////////////////////////
// Bind Typedefs, Stubs and Globals //
//////////////////////////////////////
typedef void *
(*pfn_osopenfile)(char *filepath);

typedef b32
(*pfn_osreadfile)(s8 *out,
                  void *file,
                  usz size);

typedef void
(*pfn_oswrite)(buf8 *b);

typedef int
(*PFN_Instruction)(u8 opcode_dw,
                   void *removemeplz,
                   buf8 *b);

local void *
stub_openfile(char *filepath)
{
	unref(filepath);

	return (void *)0;
}

local b32
stub_readfile(s8 *out,
              void *file,
              usz size)
{
	unref(out);
	unref(file);
	unref(size);

	return -1;
}

local void
stub_write(buf8 *b)
{
	unref(b);
}

global pfn_osopenfile os_openfile = stub_openfile;
global pfn_osreadfile os_readfile = stub_readfile;
global pfn_oswrite    os_write    = stub_write;

//////////////////////////////
// Program-Specific (Sim86) //
//////////////////////////////
typedef enum {
	MASK_B1_OPCODE = 0xFC,    // [111111] ?  ?
	MASK_B1_D = 0x02,         //  ??????  ? [1]
	MASK_B1_W = 0x01,         //  ?????? [1] ?

	MASK_B2_MODE = 0xC0,      // [11]  ???   ???
	MASK_B2_REG  = 0x38,      //  ??  [???]  ???
	MASK_B2_RM   = 0x07,      //  ??   ???  [111]

	MASK_MODE_MEM_D0  = 0x0,  // [00] ??? ???
	MASK_MODE_MEM_D8  = 0x40, // [01] ??? ???
	MASK_MODE_MEM_D16 = 0x80, // [10] ??? ???
	MASK_MODE_REG     = 0xC0, // [11] ??? ???
} FieldMasks;

#endif // SIM86_SRC_C_TYPES_H

