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
	u8   *data;
	void *fd;
	usz   len;
	usz   cap;
	b32   err;
} buf8;

typedef union {
	u8  U8[2];
	i8  I8[2];
	u16 U16;
	i16 I16;
} U16Union;

/////////////////////////
// Sim86 Types & Enums //
/////////////////////////
typedef struct {
	U16Union data;
	U16Union disp;
	u16 ip;
	u16 cs;

	u8 opcode;
	u8 w;
	u8 ds;
	u8 neg;

	u8 mod;
	u8 reg;
	u8 rm;
	u8 sgmt;
} BitNamesForEncodings;

typedef enum {
	MASK_W           = 0x01,
	MASK_D           = 0x02,
	MASK_S           = 0x02,
	MASK_MOD         = 0xC0,
	MASK_REG         = 0x38,
	MASK_SR          = 0x18,
	MASK_RM          = 0x07,
	MASK_ACCUM       = 0x04,
	MASK_REG_ALT     = 0x07,

	MASK_MOD_MEM     = 0x00,
	MASK_MOD_MEM_D8  = 0x01,
	MASK_MOD_MEM_D16 = 0x02,
	MASK_MOD_REG     = 0x03,

	MASK_RM_DIRECT   = 0x06,
	MASK_MOV_WREG    = 0x0F,
	MASK_MOV_WREG_W  = 0x08,

	SHIFT_MOD        = 6,
	SHIFT_REG        = 3,
	SHIFT_SR         = 3,
	SHIFT_WREG_W     = 3,
} Sim86BitMaskCommon;

typedef enum {
	MASK_MOV_ITORG     = 0xB0,
	MASK_MOV_ITORM     = 0xC0,
	MASK_MOV_ACCUM     = 0xA0,
	MASK_MOV_SEGMT     = 0x8C,
	MASK_PUSH_REG      = 0x50,
	MASK_POP_RM        = 0x8F,
	MASK_POP_REG       = 0x58,
	MASK_XCHG_ACCUM    = 0x90,
	MASK_XCHG_REG      = 0x07,
	MASK_IN_VARPORT    = 0xEC,
	MASK_OUT_VARPORT   = 0xEE,
	MASK_TEST_RM_REG   = 0x84,
	MASK_INT_TYPE_S    = 0xCD,
	MASK_RET_WSGMT     = 0xC3,
	MASK_RET_ISGMT     = 0x08,
	MASK_RET_SP        = 0x03,
	MASK_CALL_DISGMT   = 0x9A,
	MASK_CALL_DWSGMT   = 0xE8,
	MASK_JMP_DWSGMTS   = 0xEB,
	MASK_JMP_DISGMT    = 0xEA,

	SHFT_ROL    = 0x00,
	SHFT_ROR    = 0x01,
	SHFT_RCL    = 0x02,
	SHFT_RCR    = 0x03,
	SHFT_SHL    = 0x04,
	SHFT_SHR    = 0x05,
	SHFT_UNUSED = 0x06,
	SHFT_SAR    = 0x07,

	GRP1_TEST   = 0x00,
	GRP1_UNUSED = 0x01,
	GRP1_NOT    = 0x02,
	GRP1_NEG    = 0x03,
	GRP1_MUL    = 0x04,
	GRP1_IMUL   = 0x05,
	GRP1_DIV    = 0x06,
	GRP1_IDIV   = 0x07,

	GRP2_INC         = 0x00,
	GRP2_DEC         = 0x01,
	GRP2_CALL_IWSGMT = 0x02,
	GRP2_CALL_IISGMT = 0x03,
	GRP2_JMP_IWSGMT  = 0x04,
	GRP2_JMP_IISGMT  = 0x05,
	GRP2_PUSH        = 0x06,
} Sim86BitMaskOps;

typedef int
(*PFN_Instruction)(BitNamesForEncodings *bits,
                   void *file,
                   buf8 *b);

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

