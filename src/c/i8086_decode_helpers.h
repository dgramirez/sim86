#ifndef SIM86_SRC_C_I8086_DECODE_HELPERS_H
#define SIM86_SRC_C_I8086_DECODE_HELPERS_H

local void
print_dasm_rm_memory(BitNamesForEncodings *bits,
                     buf8 *b)
{
	if (bits->sgmt) {
		print_dasm_sr(bits->sgmt - 1, b);
		buf8_appendbyte(b, ':');
		bits->sgmt = 0;
	}

	buf8_appendbyte(b, '[');
	buf8_appendcstr(b, rm_field_enc[bits->rm]);
	if (bits->disp.U16) {
		buf8_appendbyte(b, ' ');
		buf8_appendbyte(b, '+' + bits->neg);
		buf8_appendbyte(b, ' ');
		buf8_appendusz(b, bits->disp.U16 & 0x7FFF);
	}
	buf8_appendbyte(b, ']');
}

local void
print_dasm_direct(BitNamesForEncodings *bits,
                  buf8 *b)
{
	if (bits->sgmt) {
		print_dasm_sr(bits->sgmt - 1, b);
		buf8_appendbyte(b, ':');
		bits->sgmt = 0;
	}

	buf8_appendbyte(b, '[');
	buf8_appendusz(b, bits->disp.U16);
	buf8_appendbyte(b, ']');
}

local void
print_dasm_rm(BitNamesForEncodings *bits,
              buf8 *b)
{
	if (bits->mod < MASK_MOD_REG) {
		if ((bits->mod == MASK_MOD_MEM) && (bits->rm == MASK_RM_DIRECT))
			print_dasm_direct(bits, b);
		else
			print_dasm_rm_memory(bits, b);
	}
	else
		print_dasm_reg(bits->w, bits->reg, b);
}

local void
print_dasm_mod_reg(BitNamesForEncodings *bits,
                   buf8 *b)
{
	if (bits->ds) {
		print_dasm_reg(bits->w, bits->reg, b);
		print_dasm_separator(b);
		print_dasm_reg(bits->w, bits->rm, b);
	}
	else {
		print_dasm_reg(bits->w, bits->rm, b);
		print_dasm_separator(b);
		print_dasm_reg(bits->w, bits->reg, b);
	}
}

local void
print_dasm_mod_regrm(BitNamesForEncodings *bits,
                     buf8 *b)
{
	if (bits->ds) {
		print_dasm_reg(bits->w, bits->reg, b);
		print_dasm_separator(b);
		print_dasm_rm_memory(bits, b);
	}
	else {
		print_dasm_rm_memory(bits, b);
		print_dasm_separator(b);
		print_dasm_reg(bits->w, bits->reg, b);
	}
}
local void
print_dasm_mod_direct(BitNamesForEncodings *bits,
                      buf8 *b)
{
	if (bits->ds) {
		print_dasm_reg(bits->w, bits->reg, b);
		print_dasm_separator(b);
		print_dasm_direct(bits, b);
	}
	else {
		print_dasm_direct(bits, b);
		print_dasm_separator(b);
		print_dasm_reg(bits->w, bits->reg, b);
	}
}

local void
print_dasm_mod_sr(BitNamesForEncodings *bits,
                  buf8 *b)
{
	if (bits->ds) {
		print_dasm_sr(bits->reg, b);
		print_dasm_separator(b);
		print_dasm_rm_memory(bits, b);
	}
	else {
		print_dasm_rm_memory(bits, b);
		print_dasm_separator(b);
		print_dasm_sr(bits->reg, b);
	}
}

local void
print_dasm_rm_grp(BitNamesForEncodings *bits,
                  const char *instruction,
                  buf8 *b)
{
	buf8_appendcstr(b, instruction);
	if (bits->mod < MASK_MOD_REG) {
		buf8_appendcstr(b, immed_word[bits->w]);
		buf8_appendbyte(b, ' ');
		print_dasm_rm(bits, b);
	}
	else
		print_dasm_reg(bits->w, bits->rm, b);
}

local void
calc_dasm_rm(BitNamesForEncodings *bits,
             void *file)
{
	bits->disp.U16 = 0;
	bits->neg = 0;
	if (bits->mod < MASK_MOD_REG) {
		os_readfile(bits->disp.U8, &bits->ip, file, bits->mod);
		if (bits->mod == MASK_MOD_MEM && bits->rm == MASK_RM_DIRECT) {
			// Note - No bytes were received on last read. (mod was 0)
			os_readfile(bits->disp.U8, &bits->ip, file, 2);
		}
		else if (bits->mod == MASK_MOD_MEM_D8) {
			bits->neg = (bits->disp.U8[0] & 0x80) >> 6;
			if (bits->neg)
				bits->disp.U16 = (i16)(bits->disp.I8[0]) * -1;
		}
		else if (bits->mod == MASK_MOD_MEM_D16) {
			bits->neg = (bits->disp.U16 & 0x8000) >> 14;
			if (bits->neg)
				bits->disp.U16 = (u16)((i32)(bits->disp.I16) * -1);
		}
	}
}

local void
calc_dasm_immed(BitNamesForEncodings *bits,
                void *file,
                usz iswide)
{
	bits->data.U16 = 0;
	os_readfile(bits->data.U8, &bits->ip, file, 1 + iswide);
	if (!iswide && (bits->data.U8[0] & 0x80))
		bits->data.I16 = bits->data.I8[0];
}

local int
decode_dasm_reg_from_immed(BitNamesForEncodings *bits,
                           void *file,
                           buf8 *b)
{
	bits->w = (bits->opcode & MASK_MOV_WREG_W) >> SHIFT_WREG_W;
	bits->reg = bits->opcode & MASK_REG_ALT;
	calc_dasm_immed(bits, file, bits->w);

	print_dasm_reg(bits->w, bits->reg, b);
	print_dasm_separator(b);
	print_dasm_immed(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_rm_from_immed(BitNamesForEncodings *bits,
                          void *file,
                          buf8 *b)
{
	bits->w = bits->opcode & MASK_W;

	os_readfile(&bits->mod, &bits->ip, file, 1);
	bits->rm = bits->mod & MASK_RM;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);
	calc_dasm_immed(bits, file, bits->w);

	print_dasm_rm(bits, b);
	print_dasm_separator(b);
	print_dasm_immed(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_mem_tofrom_accum(BitNamesForEncodings *bits,
                             void *file,
                             buf8 *b)
{
	// Note - There is no D bit, however the bit placement determines the
	//        operation. 0 = accum, rm | 1 = rm, accum.
	bits->ds = !(bits->opcode & MASK_D);
	bits->w = bits->opcode & MASK_W;
	bits->reg = 0;

	os_readfile(bits->disp.U8, &bits->ip, file, 1 + bits->w);
	print_dasm_mod_direct(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_sr_tofrom_rm(BitNamesForEncodings *bits,
                         void *file,
                         buf8 *b)
{
	os_readfile(&bits->mod, &bits->ip, file, 1);
	bits->rm  = bits->mod & MASK_RM;
	bits->reg  = (bits->mod & MASK_SR) >> SHIFT_REG;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);

	print_dasm_mod_sr(bits, b);
	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_reg_tofrom_rm(BitNamesForEncodings *bits,
                          void *file,
                          buf8 *b)
{
	os_readfile(&bits->mod, &bits->ip, file, 1);
	bits->rm  = bits->mod & MASK_RM;
	bits->reg = (bits->mod & MASK_REG) >> SHIFT_REG;
	bits->mod >>= SHIFT_MOD;

	if (bits->mod == MASK_MOD_REG) {
		print_dasm_mod_reg(bits, b);
		buf8_appendlf(b);
		return SIM86_OK;
	}

	calc_dasm_rm(bits, file);

	if (bits->mod == MASK_MOD_MEM && bits->rm == MASK_RM_DIRECT)
		print_dasm_mod_direct(bits, b);
	else
		print_dasm_mod_regrm(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_accum_from_immed(BitNamesForEncodings *bits,
                             void *file,
                             buf8 *b)
{
	bits->w = bits->opcode & MASK_W;
	calc_dasm_immed(bits, file, bits->w);

	print_dasm_reg(bits->w, 0x00, b);
	print_dasm_separator(b);
	print_dasm_immed(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_rm_solo(BitNamesForEncodings *bits,
                    void *file,
                    buf8 *b)
{
	bits->w = 1;

	os_readfile(&bits->mod, &bits->ip, file, 1);
	bits->rm = bits->mod & MASK_RM;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);

	buf8_appendcstr(b, immed_word[bits->w]);
	buf8_appendbyte(b, ' ');
	print_dasm_rm(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dasm_relative_addr(BitNamesForEncodings *bits,
                          void *file,
                          buf8 *b)
{
	c8 sign;

	os_readfile(bits->data.U8, &bits->ip, file, 1);
	sign = (bits->data.U8[0] & 0x80) >> 6;
	bits->data.U8[0] = (bits->data.U8[0] + 2) * (-sign + 1);
	sign += '+';

	buf8_appendbyte(b, '$');
	buf8_appendbyte(b, sign);
	buf8_appendusz(b, bits->data.U8[0]);

	buf8_appendlf(b);
	return SIM86_OK;
}

#endif // SIM86_SRC_C_I8086_DECODE_HELPERS_H

