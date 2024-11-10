#ifndef SIM86_SRC_C_8086_DECODE_C
#define SIM86_SRC_C_8086_DECODE_C

local int
decode_panic(BitNamesForEncodings *bits,
             void *file,
             buf8 *b)
{
	unref(bits);
	unref(file);
	unref(b);
	return SIM86_PANIC;
}

local int
decode_add(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("add "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_push(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("push "));
	unref(file);

	if (flag_equ(bits->opcode, MASK_PUSH_REG))
		print_dasm_reg(1, bits->opcode & MASK_REG_ALT, b);
	else {
		bits->reg = (bits->opcode & MASK_SR) >> SHIFT_SR;
		print_dasm_sr(bits->reg, b);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_pop(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("pop "));

	if (flag_equ(bits->opcode, MASK_POP_RM))
		return decode_dasm_rm_solo(bits, file, b);

	if (flag_equ(bits->opcode, MASK_POP_REG))
		print_dasm_reg(1, (bits->opcode & MASK_REG_ALT), b);
	else {
		bits->reg = (bits->opcode & MASK_SR) >> SHIFT_SR;
		print_dasm_sr(bits->reg, b);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_or(BitNamesForEncodings *bits,
          void *file,
          buf8 *b)
{
	buf8_append(b, s8("or "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_adc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("adc "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_sbb(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("sbb "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_and(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("and "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_seg(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	unref(file);
	unref(b);

	// Note - This value will be subtracted in print functions that uses
	//        it.
	bits->sgmt = ((bits->opcode & MASK_SR) >> SHIFT_SR) + 1 ;
	return SIM86_OK;
}

local int
decode_daa(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("daa"));
	unref(bits);
	unref(file);
	unref(b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_sub(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("sub "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_das(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("das"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_xor(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("xor "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_aaa(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("aaa"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cmp(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cmp "));

	if (flag_equ(bits->opcode, MASK_ACCUM))
		return decode_dasm_accum_from_immed(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_aas(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("aas"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_inc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("inc "));
	unref(file);

	buf8_appendcstr(b, reg_field_enc[(bits->opcode & 0x7) | 0x08]);
	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_dec(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("dec "));
	unref(file);

	buf8_appendcstr(b, reg_field_enc[(bits->opcode & 0x7) | 0x08]);
	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_jo(BitNamesForEncodings *bits,
          void *file,
          buf8 *b)
{
	buf8_append(b, s8("jo "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jno(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("jno "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jb_jnae(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jb "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jnb_jae(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jnb "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_je_jz(BitNamesForEncodings *bits,
             void *file,
             buf8 *b)
{
	buf8_append(b, s8("je "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jne_jnz(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jne "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jbe_jna(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jbe "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jnbe_ja(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("ja "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_js(BitNamesForEncodings *bits,
          void *file,
          buf8 *b)
{
	buf8_append(b, s8("js "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jns(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("jns "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jp_jpe(BitNamesForEncodings *bits,
              void *file,
              buf8 *b)
{
	buf8_append(b, s8("jp "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jnp_jpo(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jnp "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jl_jnge(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jl "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jnl_jge(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jnl "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jle_jng(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jle "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jnle_jg(BitNamesForEncodings *bits,
               void *file,
               buf8 *b)
{
	buf8_append(b, s8("jg "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_immed(BitNamesForEncodings *bits,
             void *file,
             buf8 *b)
{
	bits->ds = bits->opcode & MASK_S;
	bits->w  = bits->opcode & MASK_W;

	os_readfile(&bits->mod, &bits->ip, file, 1);
	bits->opcode = (bits->mod & MASK_REG) >> SHIFT_REG;
	bits->rm = bits->mod & MASK_RM;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);
	calc_dasm_immed(bits, file, check_sw_bits_01(bits));

	switch(bits->opcode) {
		case 0: { buf8_append(b, s8("add ")); } break;
		case 1: { buf8_append(b, s8("or "));  } break;
		case 2: { buf8_append(b, s8("adc ")); } break;
		case 3: { buf8_append(b, s8("sbb ")); } break;
		case 4: { buf8_append(b, s8("and ")); } break;
		case 5: { buf8_append(b, s8("sub ")); } break;
		case 6: { buf8_append(b, s8("xor ")); } break;
		case 7: { buf8_append(b, s8("cmp ")); } break;
		default: { return SIM86_PANIC; }
	}

	if (bits->mod == MASK_MOD_REG)
		print_dasm_reg(bits->w, bits->rm, b);
	else
		print_dasm_rm(bits, b);
	print_dasm_separator(b);
	print_dasm_immed(bits, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_test(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	// NOTE - BEWARE! Table 4-12 8086 Instruction Encoding
	//        Is WRONG for Reg/RM Test!!!! (0x10, 0x11, 0x12 & 0x13)
	//
	//        Refer to Table 4-13. Machine Instruction Decoding Guide!
	//        (0x84, 0x85).
	//
	//        Table 4-14 Machine Instruction Encoding Matrix backs up
	//        Table 4-13.
	buf8_append(b, s8("test "));

	bits->w = bits->opcode & MASK_W;
	if (flag_equ(bits->opcode, MASK_TEST_RM_REG)) {
		bits->ds = bits->opcode & MASK_D;
		return decode_dasm_reg_tofrom_rm(bits, file, b);
	}

	calc_dasm_immed(bits, file, bits->w);
	print_dasm_reg(bits->w, 0x00, b);
	print_dasm_separator(b);
	buf8_appendusz(b, bits->data.U16);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_xchg(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("xchg "));

	if (flag_equ(bits->opcode, MASK_XCHG_ACCUM)) {
		bits->reg = bits->opcode & MASK_XCHG_REG;

		print_dasm_reg(1, 0x00, b);
		print_dasm_separator(b);
		print_dasm_reg(1, bits->reg, b);
	}
	else {
		bits->ds = 0;
		bits->w = bits->opcode & MASK_W;
		return decode_dasm_reg_tofrom_rm(bits, file, b);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_mov(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("mov "));

	if (flag_equ(bits->opcode, MASK_MOV_ITORG))
		return decode_dasm_reg_from_immed(bits, file, b);
	if (flag_equ(bits->opcode, MASK_MOV_ITORM))
		return decode_dasm_rm_from_immed(bits, file, b);
	if (flag_equ(bits->opcode, MASK_MOV_ACCUM))
		return decode_dasm_mem_tofrom_accum(bits, file, b);

	bits->ds = bits->opcode & MASK_D;
	if (flag_equ(bits->opcode, MASK_MOV_SEGMT))
		return decode_dasm_sr_tofrom_rm(bits, file, b);

	bits->w = bits->opcode & MASK_W;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_lea(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("lea "));
	unref(bits);

	bits->ds = 1;
	bits->w = 1;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_cbw(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cbw"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cwd(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cwd"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_call(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("call "));

	if (flag_equ(bits->opcode, MASK_CALL_DISGMT)) {
		os_readfile(bits->disp.U8, &bits->ip, file, 2);
		os_readfile(bits->data.U8, &bits->ip, file, 2);

		buf8_appendusz(b, bits->data.U16);
		buf8_appendbyte(b, ':');
		buf8_appendusz(b, bits->disp.U16);
	}
	else {
		os_readfile(bits->data.U8, &bits->ip, file, 2);
		buf8_appendusz(b, bits->data.U16 + bits->ip);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_wait(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("wait"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_pushf(BitNamesForEncodings *bits,
             void *file,
             buf8 *b)
{
	buf8_append(b, s8("pushf"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_popf(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("popf"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_sahf(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("sahf"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_lahf(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("lahf"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;

}

local int
decode_movs(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("movs"));
	unref(bits);
	unref(file);

	if (bits->opcode & MASK_W)
		buf8_appendbyte(b, 'w');
	else
		buf8_appendbyte(b, 'b');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cmps(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("cmps"));
	unref(bits);
	unref(file);

	if (bits->opcode & MASK_W)
		buf8_appendbyte(b, 'w');
	else
		buf8_appendbyte(b, 'b');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_stos(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("stos"));
	unref(bits);
	unref(file);

	if (bits->opcode & MASK_W)
		buf8_appendbyte(b, 'w');
	else
		buf8_appendbyte(b, 'b');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_lods(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("lods"));
	unref(bits);
	unref(file);

	if (bits->opcode & MASK_W)
		buf8_appendbyte(b, 'w');
	else
		buf8_appendbyte(b, 'b');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_scas(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("scas"));
	unref(bits);
	unref(file);

	if (bits->opcode & MASK_W)
		buf8_appendbyte(b, 'w');
	else
		buf8_appendbyte(b, 'b');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_ret(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("ret"));

	if (flag_equ(bits->opcode, MASK_RET_ISGMT))
		buf8_appendbyte(b, 'f');

	if ((bits->opcode & MASK_RET_SP) == 0x02) {
		calc_dasm_immed(bits, file, 1);

		buf8_appendbyte(b, ' ');
		buf8_appendisz(b, bits->data.I16);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_les(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("les "));

	bits->ds = 1;
	bits->w = 1;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_lds(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("lds "));

	bits->ds = 1;
	bits->w = 1;
	return decode_dasm_reg_tofrom_rm(bits, file, b);
}

local int
decode_int(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("int"));

	if (flag_equ(bits->opcode, MASK_INT_TYPE_S)) {
		os_readfile(bits->data.U8, &bits->ip, file, 1);

		buf8_appendbyte(b, ' ');
		buf8_appendusz(b, bits->data.U8[0]);
	}
	else
		buf8_appendbyte(b, '3');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_into(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("into"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_iret(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("iret"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_shift(BitNamesForEncodings *bits,
             void *file,
             buf8 *b)
{
	bits->w = bits->opcode & MASK_W;
	bits->ds = bits->opcode & MASK_D;
	os_readfile(&bits->mod, &bits->ip, file, 1);

	bits->rm = bits->mod & MASK_RM;
	bits->opcode = (bits->mod & MASK_REG) >> SHIFT_REG;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);

	switch(bits->opcode) {
		case SHFT_ROL: { print_dasm_rm_grp(bits, "rol ", b); } break;
		case SHFT_ROR: { print_dasm_rm_grp(bits, "ror ", b); } break;
		case SHFT_RCL: { print_dasm_rm_grp(bits, "rcl ", b); } break;
		case SHFT_RCR: { print_dasm_rm_grp(bits, "rcr ", b); } break;
		case SHFT_SHL: { print_dasm_rm_grp(bits, "shl ", b); } break;
		case SHFT_SHR: { print_dasm_rm_grp(bits, "shr ", b); } break;
		case SHFT_SAR: { print_dasm_rm_grp(bits, "sar ", b); } break;
		default:       { return SIM86_PANIC; }
	}
	print_dasm_separator(b);

	if (bits->ds)
		buf8_append(b, s8("cl"));
	else
		buf8_appendbyte(b, '1');

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_aam(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("aam"));

	os_readfile(&bits->mod, &bits->ip, file, 1);
	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_aad(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("aad"));

	os_readfile(&bits->mod, &bits->ip, file, 1);
	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_xlat(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("xlat"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_esc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	unref(bits);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_loopnz_loopne(BitNamesForEncodings *bits,
                     void *file,
                     buf8 *b)
{
	buf8_append(b, s8("loopnz "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_loopz_loope(BitNamesForEncodings *bits,
                   void *file,
                   buf8 *b)
{
	buf8_append(b, s8("loopz "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_loop(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("loop "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_jcxz(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("jcxz "));
	return decode_dasm_relative_addr(bits, file ,b);
}

local int
decode_in(BitNamesForEncodings *bits,
          void *file,
          buf8 *b)
{
	buf8_append(b, s8("in "));

	bits->w = bits->opcode & MASK_W;
	print_dasm_reg(bits->w, 0, b);
	print_dasm_separator(b);

	if (flag_equ(bits->opcode, MASK_IN_VARPORT))
		print_dasm_reg(1, 0x2, b);
	else
	{
		os_readfile(bits->data.U8, &bits->ip, file, 1);
		buf8_appendisz(b, bits->data.I8[0]);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_out(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("out "));

	if (flag_equ(bits->opcode, MASK_OUT_VARPORT))
		print_dasm_reg(1, 0x2, b);
	else
	{
		os_readfile(bits->data.U8, &bits->ip, file, 1);
		buf8_appendisz(b, bits->data.I8[0]);
	}

	bits->w = bits->opcode & MASK_W;
	print_dasm_separator(b);
	print_dasm_reg(bits->w, 0, b);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_jmp(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("jmp "));

	if (flag_equ(bits->opcode, MASK_JMP_DISGMT)) {
		os_readfile(bits->disp.U8, &bits->ip, file, 2);
		os_readfile(bits->data.U8, &bits->ip, file, 2);

		buf8_appendusz(b, bits->data.U16);
		buf8_appendbyte(b, ':');
		buf8_appendusz(b, bits->disp.U16);
	}
	else if (flag_equ(bits->opcode, MASK_JMP_DWSGMTS)) {
		os_readfile(bits->data.U8, &bits->ip, file, 1);
		buf8_appendusz(b, bits->data.U16 + bits->ip);
	}
	else {
		os_readfile(bits->data.U8, &bits->ip, file, 2);
		buf8_appendusz(b, bits->data.U16 + bits->ip);
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_lock(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	buf8_append(b, s8("lock "));
	unref(bits);
	unref(file);

	return SIM86_OK;
}

local int
decode_rep(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("rep "));
	unref(bits);
	unref(file);

	return SIM86_OK;
}

local int
decode_hlt(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("hlt"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cmc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cmc"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_grp1(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	bits->w = bits->opcode & MASK_W;
	os_readfile(&bits->mod, &bits->ip, file, 1);

	bits->rm = bits->mod & MASK_RM;
	bits->opcode = (bits->mod & MASK_REG) >> SHIFT_REG;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);

	switch(bits->opcode) {
		case GRP1_TEST: {
			calc_dasm_immed(bits, file, bits->w);

			print_dasm_rm_grp(bits, "test ", b);
			print_dasm_separator(b);
			buf8_appendisz(b, bits->data.I16);
		} break;

		case GRP1_NOT:  { print_dasm_rm_grp(bits, "not ", b); }  break;
		case GRP1_NEG:  { print_dasm_rm_grp(bits, "neg ", b); }  break;
		case GRP1_MUL:  { print_dasm_rm_grp(bits, "mul ", b); }  break;
		case GRP1_IMUL: { print_dasm_rm_grp(bits, "imul ", b); } break;
		case GRP1_DIV:  { print_dasm_rm_grp(bits, "div ", b); }  break;
		case GRP1_IDIV: { print_dasm_rm_grp(bits, "idiv ", b); } break;
		default: { return SIM86_PANIC; }
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_clc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("clc"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_stc(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("stc"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cli(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cli"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_sti(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("sti"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_cld(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("cld"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_std(BitNamesForEncodings *bits,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("std"));
	unref(bits);
	unref(file);

	buf8_appendlf(b);
	return SIM86_OK;
}

local int
decode_grp2(BitNamesForEncodings *bits,
            void *file,
            buf8 *b)
{
	bits->w = bits->opcode & MASK_W;
	os_readfile(&bits->mod, &bits->ip, file, 1);

	bits->rm = bits->mod & MASK_RM;
	bits->opcode = (bits->mod & MASK_REG) >> SHIFT_REG;
	bits->mod >>= SHIFT_MOD;
	calc_dasm_rm(bits, file);

	switch(bits->opcode) {
		case GRP2_INC:  { print_dasm_rm_grp(bits, "inc ", b); }  break;
		case GRP2_DEC:  { print_dasm_rm_grp(bits, "dec ", b); }  break;
		case GRP2_PUSH: { print_dasm_rm_grp(bits, "push ", b); } break;

		case GRP2_CALL_IWSGMT: { print_dasm_rm_grp(bits, "call ", b); } break;
		case GRP2_CALL_IISGMT: { print_dasm_rm_grp(bits, "call far ", b); } break;
		case GRP2_JMP_IWSGMT:  { print_dasm_rm_grp(bits, "jmp ", b); } break;
		case GRP2_JMP_IISGMT:  { print_dasm_rm_grp(bits, "jmp far ", b); } break;

		default: { return SIM86_PANIC; }
	}

	buf8_appendlf(b);
	return SIM86_OK;
}

// Note: This represents the machine instruction encoding matrix, described
//       in the 8086 family user manual on page 178 and 180.
//       It can also verified on between pages 169 to 177 using the
//       machine instruction decoding guide.
//
//       Please read the manual for more information:
//       https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_DECODE_family_Users_Manual_1_.pdf
global PFN_Instruction
i8086_fn_decodes[256] =
{
	decode_add,           // 0x00
	decode_add,           // 0x01
	decode_add,           // 0x02
	decode_add,           // 0x03
	decode_add,           // 0x04
	decode_add,           // 0x05
	decode_push,          // 0x06
	decode_pop,           // 0x07
	decode_or,            // 0x08
	decode_or,            // 0x09
	decode_or,            // 0x0A
	decode_or,            // 0x0B
	decode_or,            // 0x0C
	decode_or,            // 0x0D
	decode_push,          // 0x0E
	decode_panic,         // 0x0F

	decode_adc,           // 0x10
	decode_adc,           // 0x11
	decode_adc,           // 0x12
	decode_adc,           // 0x13
	decode_adc,           // 0x14
	decode_adc,           // 0x15
	decode_push,          // 0x16
	decode_pop,           // 0x17
	decode_sbb,           // 0x18
	decode_sbb,           // 0x19
	decode_sbb,           // 0x1A
	decode_sbb,           // 0x1B
	decode_sbb,           // 0x1C
	decode_sbb,           // 0x1D
	decode_push,          // 0x1E
	decode_pop,           // 0x1F

	decode_and,           // 0x20
	decode_and,           // 0x21
	decode_and,           // 0x22
	decode_and,           // 0x23
	decode_and,           // 0x24
	decode_and,           // 0x25
	decode_seg,           // 0x26
	decode_daa,           // 0x27
	decode_sub,           // 0x28
	decode_sub,           // 0x29
	decode_sub,           // 0x2A
	decode_sub,           // 0x2B
	decode_sub,           // 0x2C
	decode_sub,           // 0x2D
	decode_seg,           // 0x2E
	decode_das,           // 0x2F

	decode_xor,           // 0x30
	decode_xor,           // 0x31
	decode_xor,           // 0x32
	decode_xor,           // 0x33
	decode_xor,           // 0x34
	decode_xor,           // 0x35
	decode_seg,           // 0x36
	decode_aaa,           // 0x37
	decode_cmp,           // 0x38
	decode_cmp,           // 0x39
	decode_cmp,           // 0x3A
	decode_cmp,           // 0x3B
	decode_cmp,           // 0x3C
	decode_cmp,           // 0x3D
	decode_seg,           // 0x3E
	decode_aas,           // 0x3F

	decode_inc,           // 0x40
	decode_inc,           // 0x41
	decode_inc,           // 0x42
	decode_inc,           // 0x43
	decode_inc,           // 0x44
	decode_inc,           // 0x45
	decode_inc,           // 0x46
	decode_inc,           // 0x47
	decode_dec,           // 0x48
	decode_dec,           // 0x49
	decode_dec,           // 0x4A
	decode_dec,           // 0x4B
	decode_dec,           // 0x4C
	decode_dec,           // 0x4D
	decode_dec,           // 0x4E
	decode_dec,           // 0x4F

	decode_push,          // 0x50
	decode_push,          // 0x51
	decode_push,          // 0x52
	decode_push,          // 0x53
	decode_push,          // 0x54
	decode_push,          // 0x55
	decode_push,          // 0x56
	decode_push,          // 0x57
	decode_pop,           // 0x58
	decode_pop,           // 0x59
	decode_pop,           // 0x5A
	decode_pop,           // 0x5B
	decode_pop,           // 0x5C
	decode_pop,           // 0x5D
	decode_pop,           // 0x5E
	decode_pop,           // 0x5F

	decode_panic,         // 0x60
	decode_panic,         // 0x61
	decode_panic,         // 0x62
	decode_panic,         // 0x63
	decode_panic,         // 0x64
	decode_panic,         // 0x65
	decode_panic,         // 0x66
	decode_panic,         // 0x67
	decode_panic,         // 0x68
	decode_panic,         // 0x69
	decode_panic,         // 0x6A
	decode_panic,         // 0x6B
	decode_panic,         // 0x6C
	decode_panic,         // 0x6D
	decode_panic,         // 0x6E
	decode_panic,         // 0x6F

	decode_jo,            // 0x70
	decode_jno,           // 0x71
	decode_jb_jnae,       // 0x72
	decode_jnb_jae,       // 0x73
	decode_je_jz,         // 0x74
	decode_jne_jnz,       // 0x75
	decode_jbe_jna,       // 0x76
	decode_jnbe_ja,       // 0x77
	decode_js,            // 0x78
	decode_jns,           // 0x79
	decode_jp_jpe,        // 0x7A
	decode_jnp_jpo,       // 0x7B
	decode_jl_jnge,       // 0x7C
	decode_jnl_jge,       // 0x7D
	decode_jle_jng,       // 0x7E
	decode_jnle_jg,       // 0x7F

	decode_immed,         // 0x80
	decode_immed,         // 0x81
	decode_immed,         // 0x82
	decode_immed,         // 0x83
	decode_test,          // 0x84
	decode_test,          // 0x85
	decode_xchg,          // 0x86
	decode_xchg,          // 0x87
	decode_mov,           // 0x88
	decode_mov,           // 0x89
	decode_mov,           // 0x8A
	decode_mov,           // 0x8B
	decode_mov,           // 0x8C
	decode_lea,           // 0x8D
	decode_mov,           // 0x8E
	decode_pop,           // 0x8F

	decode_xchg,          // 0x90
	decode_xchg,          // 0x91
	decode_xchg,          // 0x92
	decode_xchg,          // 0x93
	decode_xchg,          // 0x94
	decode_xchg,          // 0x95
	decode_xchg,          // 0x96
	decode_xchg,          // 0x97
	decode_cbw,           // 0x98
	decode_cwd,           // 0x99
	decode_call,          // 0x9A
	decode_wait,          // 0x9B
	decode_pushf,         // 0x9C
	decode_popf,          // 0x9D
	decode_sahf,          // 0x9E
	decode_lahf,          // 0x9F

	decode_mov,           // 0xA0
	decode_mov,           // 0xA1
	decode_mov,           // 0xA2
	decode_mov,           // 0xA3
	decode_movs,          // 0xA4
	decode_movs,          // 0xA5
	decode_cmps,          // 0xA6
	decode_cmps,          // 0xA7
	decode_test,          // 0xA8
	decode_test,          // 0xA9
	decode_stos,          // 0xAA
	decode_stos,          // 0xAB
	decode_lods,          // 0xAC
	decode_lods,          // 0xAD
	decode_scas,          // 0xAE
	decode_scas,          // 0xAF

	decode_mov,           // 0xB0
	decode_mov,           // 0xB1
	decode_mov,           // 0xB2
	decode_mov,           // 0xB3
	decode_mov,           // 0xB4
	decode_mov,           // 0xB5
	decode_mov,           // 0xB6
	decode_mov,           // 0xB7
	decode_mov,           // 0xB8
	decode_mov,           // 0xB9
	decode_mov,           // 0xBA
	decode_mov,           // 0xBB
	decode_mov,           // 0xBC
	decode_mov,           // 0xBD
	decode_mov,           // 0xBE
	decode_mov,           // 0xBF

	decode_panic,         // 0xC0
	decode_panic,         // 0xC1
	decode_ret,           // 0xC2
	decode_ret,           // 0xC3
	decode_les,           // 0xC4
	decode_lds,           // 0xC5
	decode_mov,           // 0xC6
	decode_mov,           // 0xC7
	decode_panic,         // 0xC8
	decode_panic,         // 0xC9
	decode_ret,           // 0xCA
	decode_ret,           // 0xCB
	decode_int,           // 0xCC
	decode_int,           // 0xCD
	decode_into,          // 0xCE
	decode_iret,          // 0xCF

	decode_shift,         // 0xD0
	decode_shift,         // 0xD1
	decode_shift,         // 0xD2
	decode_shift,         // 0xD3
	decode_aam,           // 0xD4
	decode_aad,           // 0xD5
	decode_panic,         // 0xD6
	decode_xlat,          // 0xD7
	decode_esc,           // 0xD8
	decode_esc,           // 0xD9
	decode_esc,           // 0xDA
	decode_esc,           // 0xDB
	decode_esc,           // 0xDC
	decode_esc,           // 0xDD
	decode_esc,           // 0xDE
	decode_esc,           // 0xDF

	decode_loopnz_loopne, // 0xE0
	decode_loopz_loope,   // 0xE1
	decode_loop,          // 0xE2
	decode_jcxz,          // 0xE3
	decode_in,            // 0xE4
	decode_in,            // 0xE5
	decode_out,           // 0xE6
	decode_out,           // 0xE7
	decode_call,          // 0xE8
	decode_jmp,           // 0xE9
	decode_jmp,           // 0xEA
	decode_jmp,           // 0xEB
	decode_in,            // 0xEC
	decode_in,            // 0xED
	decode_out,           // 0xEE
	decode_out,           // 0xEF

	decode_lock,          // 0xF0
	decode_panic,         // 0xF1
	decode_rep,           // 0xF2
	decode_rep,           // 0xF3
	decode_hlt,           // 0xF4
	decode_cmc,           // 0xF5
	decode_grp1,          // 0xF6
	decode_grp1,          // 0xF7
	decode_clc,           // 0xF8
	decode_stc,           // 0xF9
	decode_cli,           // 0xFA
	decode_sti,           // 0xFB
	decode_cld,           // 0xFC
	decode_std,           // 0xFD
	decode_grp2,          // 0xFE
	decode_grp2           // 0xFF
};

#endif // SIM86_SRC_C_8086_DECODE_C

