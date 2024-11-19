#ifndef SIM86_SRC_C_I8086_H
#define SIM86_SRC_C_I8086_H

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

global const char *reg_field_enc[] = {
	"al", "cl", "dl", "bl",
	"ah", "ch", "dh", "bh",
	"ax", "cx", "dx", "bx",
	"sp", "bp", "si", "di"
};

global const char *sr_field_enc[] = {
	"es", "cs", "ss", "ds"
};

global const char *rm_field_enc[] = {
	"bx + si",
	"bx + di",
	"bp + si",
	"bp + di",
	"si",
	"di",
	"bp",
	"bx"
};

global const char *immed_word[] = {
	"byte",
	"word"
};

#define check_sw_bits_01(bits) \
	((bits)->ds | (bits)->w) == 0x01

#define print_dasm_reg(w, reg, b) \
	buf8_appendcstr((b), reg_field_enc[(reg) | ((w) << SHIFT_WREG_W)])

#define print_dasm_sr(sgmt, b) \
	buf8_appendcstr((b), sr_field_enc[(sgmt)])

#define print_dasm_separator(b) \
	buf8_appendbyte((b), ',');  \
	buf8_appendbyte((b), ' ')

#define print_dasm_immed(bits, b)                \
	buf8_appendcstr((b), immed_word[(bits)->w]); \
	buf8_appendbyte((b), ' ');                   \
	buf8_appendisz((b), (bits)->data.I16)

/////////////////
// For i8086.c //
/////////////////
local void
help(buf8 *b);

local b32
validate_all_pfn(buf8 *b);

local b32
validate_mode(int *out_sim,
              buf8 *b,
              char **argv,
              int argc);
local b32
validate_file(void **out_file,
              buf8 *b,
              char **argv,
              int argc);

#endif // SIM86_SRC_C_I8086_H

