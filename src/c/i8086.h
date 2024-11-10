#ifndef SIM86_SRC_C_I8086_H
#define SIM86_SRC_C_I8086_H

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

#endif // SIM86_SRC_C_I8086_H

