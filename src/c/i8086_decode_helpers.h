#ifndef SIM86_SRC_C_I8086_DECODE_HELPERS_H
#define SIM86_SRC_C_I8086_DECODE_HELPERS_H

#define W_BIT_IN_WREG 3

typedef enum {
	MOD_MODE_MEM      = 0x0, // Bits: 00
	MOD_MODE_MEM_BYTE = 0x1, // Bits: 01
	MOD_MODE_MEM_WORD = 0x2, // Bits: 10
	MOD_MODE_REG      = 0x3, // Bits: 11
	
	MOD_RM_DIRECT  = 0x6,
	MOD_SHIFT_VAL = 6
} MOD_MODE;

typedef enum {
	// Byte 1
	MOV_MASK_OPCODE_ITORG = 0xB0,
	MOV_MASK_OPCODE_ITORM = 0xC0,
	MOV_MASK_OPCODE_ACCUM = 0xA0,
	MOV_MASK_OPCODE_SEGMT = 0x8C,
	MOV_MASK_W       = 0x01, // Bits(hex): 0000 0001 | Bits(x86): 000000 x 1
	MOV_MASK_D       = 0x02, // Bits(hex): 0000 0010 | Bits(x86): 000000 1 x
	MOV_MASK_WREG    = 0x0F, // Bits(hex): 0000 xxxx | Bits(x86): 0000 x xxx
	MOV_MASK_W_ITORG = 0x08, // Bits(hex): 0000 x000 | Bits(x86): 0000 x 000

	// Byte 2
	MOV_MASK_MOD  = 0xC0, // Bits(hex): xx00 0000 | Bits(x86): xx 000 000
	MOV_MASK_REG  = 0x38, // Bits(hex): 00xx x000 | Bits(x86): 00 xxx 000
	MOV_MASK_RM   = 0x07, // Bits(hex): 0000 0xxx | Bits(x86): 00 000 xxx
} I8086_MASKS;

typedef union {
	u8  u8bytes[2];
	i8  i8bytes[2];
	u16 u16bytes;
	i16 i16bytes;
} U16Union;

global const char *reg_field_enc[] = {
	"al", "cl", "dl", "bl",
	"ah", "ch", "dh", "bh",
	"ax", "cx", "dx", "bx",
	"sp", "bp", "si", "di"
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

local void
print_rm_memory(buf8 *b,
                u16 disp,
                u8 rm,
                u8 sign)
{
	buf8_appendbyte(b, '[');
	buf8_appendcstr(b, rm_field_enc[rm]);
	if (disp) {
		buf8_appendbyte(b, ' ');
		buf8_appendbyte(b, sign);
		buf8_appendbyte(b, ' ');
		buf8_appendisz(b, disp);
	}
	buf8_appendbyte(b, ']');
}

local void
print_direct_addr(buf8 *b,
                  u16 disp)
{
	buf8_appendbyte(b, '[');
	buf8_appendusz(b, disp);
	buf8_appendbyte(b, ']');
}

#define print_reg(b, ireg, w) \
	buf8_appendcstr(b, reg_field_enc[ireg | (w << W_BIT_IN_WREG)]);

local void
calculate_rm(u16 *out_disp,
             c8* out_sign,
             void* file,
             u8 mod,
             u8 rm,
             u8 w)
{
	U16Union bytes;
	i16 disp;
	c8 sign;
	i8 neg;

	disp = 0;
	sign = 0;
	if (mod < MOD_MODE_REG) {
		os_readfile(bytes.u8bytes, file, mod);
		if (mod == MOD_MODE_MEM && rm == MOD_RM_DIRECT) {
			// Note - No bytes were received (mod was 0). Get with W.
			os_readfile(bytes.u8bytes, file, 1 + w);
			if (w)
				disp = bytes.u8bytes[0] | (bytes.u8bytes[1] << 8);
			else
				disp = bytes.i8bytes[0];
		}
		else if (mod == MOD_MODE_MEM_BYTE) {
			disp = bytes.i8bytes[0];
			neg  = (bytes.u8bytes[0] & 0x80) >> 6; 
			sign = '+' + neg;
			disp *= -neg + 1;
		}
		else if (mod == MOD_MODE_MEM_WORD) {
			disp = (bytes.u8bytes[0] | (bytes.u8bytes[1] << 8));
			neg  = (bytes.u16bytes & 0x8000) >> 14; 
			sign = '+' + neg;
			disp *= -neg + 1;
		}
	}

	*out_disp = disp;
	*out_sign = sign;
}

local int
mov_immed_to_reg(u8 wreg,
                 void *file,
                 buf8 *b)
{
	b32 w;
	U16Union bytes;
	i16 val;

	//////////////////
	// Calculations //
	//////////////////
	w = (wreg & MOV_MASK_W_ITORG) >> 3;
	os_readfile(&bytes.u8bytes[0], file, 1 + w);
	if (w)
		val = bytes.u8bytes[0] | ((u16)bytes.u8bytes[1] << 8);
	else
		val = bytes.i8bytes[0];

	///////////
	// Print //
	///////////
	buf8_appendcstr(b, reg_field_enc[wreg & MOV_MASK_WREG]);
	buf8_appendbyte(b, ',');
	buf8_appendbyte(b, ' ');
	buf8_appendcstr(b, immed_word[w]);
	buf8_appendbyte(b, ' ');
	buf8_appendisz(b, (isz)val);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
mov_immed_to_rm(u8 w,
                void *file,
                buf8 *b)
{
	U16Union bytes;
	i16 val;
	u16 disp;
	u8  mod;
	u8  rm;
	c8  sign;

	sign = '+';
	disp = 0;
	val = 0;

	//////////////////
	// Calculations //
	//////////////////
	os_readfile(&mod, file, 1);
	rm  = mod & MOV_MASK_RM;
	mod = mod >> MOD_SHIFT_VAL;
	calculate_rm(&disp, &sign, file, mod, rm, w);

	os_readfile(bytes.u8bytes, file, 1 + w);
	if (w)
		val = bytes.u8bytes[0] | ((u16)bytes.u8bytes[1] << 8);
	else
		val = bytes.i8bytes[0];

	///////////
	// Print //
	///////////
	if (mod < MOD_MODE_REG) {
		if ((mod == MOD_MODE_MEM) && (rm == MOD_RM_DIRECT))
			print_direct_addr(b, disp);
		else
			print_rm_memory(b, disp, rm, sign);
	}
	else
		print_reg(b, rm, w);

	buf8_appendbyte(b, ',');
	buf8_appendbyte(b, ' ');
	buf8_appendcstr(b, immed_word[w]);
	buf8_appendbyte(b, ' ');
	buf8_appendisz(b, val);

	buf8_appendlf(b);
	return SIM86_OK;
}

// Note - "mid" (Memory is Destination) determines whether its:
//            - (0): Memory to Accumulator
//            - (1): Accumulator to Memory
//
//        The rest is consistent.
local int
mov_memory_tofrom_accumulator(u8 mid,
                              u8 w,
                              void *file,
                              buf8 *b)
{
	U16Union bytes;
	i16 addr;

	//////////////////
	// Calculations //
	//////////////////
	os_readfile(&bytes.u8bytes[0], file, 1 + w);
	addr = bytes.u8bytes[0] | (bytes.u8bytes[1] << 8);

	///////////
	// Print //
	///////////
	if (mid) {
		print_direct_addr(b, addr);
		buf8_appendbyte(b, ',');
		buf8_appendbyte(b, ' ');
		print_reg(b, 0, 1);
	}
	else {
		print_reg(b, 0, 1);
		buf8_appendbyte(b, ',');
		buf8_appendbyte(b, ' ');
		print_direct_addr(b, addr);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
mov_regrm_tofrom_reg(u8 d,
                     u8 w,
                     void *file,
                     buf8 *b)
{
	u16 disp;
	u8 mod;
	u8 reg;
	u8 rm;
	c8 sign;

	os_readfile(&mod, file, 1);
	rm  = mod & MOV_MASK_RM;
	reg = (mod & MOV_MASK_REG) >> 3;
	mod = mod >> MOD_SHIFT_VAL;

	if (mod == MOD_MODE_REG) {
		if (d) {
			print_reg(b, reg, w);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_reg(b, rm, w);
		}
		else {
			print_reg(b, rm, w);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_reg(b, reg, w);
		}

		buf8_appendlf(b);
		return SIM86_OK;
	}

	calculate_rm(&disp, &sign, file, mod, rm, w);

	///////////
	// Print //
	///////////
	if (mod == MOD_MODE_MEM && rm == MOD_RM_DIRECT) {
		if (d) {
			print_reg(b, reg, w);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_direct_addr(b, disp);
		}
		else {
			print_direct_addr(b, disp);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_reg(b, reg, w);
		}
	}
	else {
		if (d) {
			print_reg(b, reg, w);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_rm_memory(b, disp, rm, sign);
		}
		else {
			print_rm_memory(b, disp, rm, sign);
			buf8_appendbyte(b, ',');
			buf8_appendbyte(b, ' ');
			print_reg(b, reg, w);
		}
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

#endif // SIM86_SRC_C_I8086_DECODE_HELPERS_H

