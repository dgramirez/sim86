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

typedef float  f32;
typedef double f64;

typedef char       c8;
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
	union {
		s8 str;
		struct { u8 *data; usz len; };
	};
	void *fd;
	usz   cap;
	b32   err;
} buf8;

typedef union {
	u8  U8[2];
	i8  I8[2];
	u16 U16;
	i16 I16;
} U16Union;

//////////////////////////////////////
// Bind Typedefs, Stubs and Globals //
//////////////////////////////////////
typedef void *
(*pfn_osopenfile)(char *filepath);

typedef b32
(*pfn_osreadfile)(u8 *out,
                  u16 *ip,
                  void *file,
                  usz size);

typedef void
(*pfn_oswrite)(buf8 *b);

local void *
stub_openfile(char *filepath)
{
	unref(filepath);

	return (void *)0;
}

local b32
stub_readfile(u8 *out,
              u16 *ip,
              void *file,
              usz size)
{
	unref(out);
	unref(ip);
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

#endif // SIM86_SRC_C_TYPES_H

