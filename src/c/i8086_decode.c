#ifndef SIM86_SRC_C_8086_DECODE_C
#define SIM86_SRC_C_8086_DECODE_C

local int
decode_panic(u8 opcode_dw,
             void *file,
             buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_PANIC;
}

local int
decode_add(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_push(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_pop(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_or(u8 opcode_dw,
          void *file,
          buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_adc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_sbb(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_and(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_seg(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_daa(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_sub(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_das(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_xor(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_aaa(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cmp(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_aas(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_inc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_dec(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jo(u8 opcode_dw,
          void *file,
          buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jno(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jb_jnae(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jnb_jae(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_je_jz(u8 opcode_dw,
             void *file,
             buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jne_jnz(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jbe_jna(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jnbe_ja(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_js(u8 opcode_dw,
          void *file,
          buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jns(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jp_jpe(u8 opcode_dw,
              void *file,
              buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jnp_jpo(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jl_jnge(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jnl_jge(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jle_jng(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jnle_jg(u8 opcode_dw,
               void *file,
               buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_immed(u8 opcode_dw,
             void *file,
             buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_test(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_xchg(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_mov(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	buf8_append(b, s8("mov "));
	if (flag_equ(opcode_dw, MOV_MASK_OPCODE_ITORG))
		return mov_immed_to_reg(opcode_dw & 0x0F, file, b);

	if (flag_equ(opcode_dw, MOV_MASK_OPCODE_ITORM))
		return mov_immed_to_rm(opcode_dw & 0x01, file, b);

	if (flag_equ(opcode_dw, MOV_MASK_OPCODE_ACCUM)) {
		return mov_memory_tofrom_accumulator((opcode_dw & MOV_MASK_D) >> 1,
		                                     (opcode_dw & MOV_MASK_W),
		                                     file,
		                                     b);
	}

	if (flag_equ(opcode_dw, MOV_MASK_OPCODE_SEGMT))
		return SIM86_NOT_IMPLEMENTED;

	return mov_regrm_tofrom_reg((opcode_dw & MOV_MASK_D) >> 1,
	                            (opcode_dw & MOV_MASK_W),
	                            file,
	                            b);
}

local int
decode_lea(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cbw(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cwd(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_call(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_wait(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_pushf(u8 opcode_dw,
             void *file,
             buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_popf(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_sahf(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_lahf(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_movs(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cmps(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_stos(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_lods(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_scas(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_ret(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_les(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_lds(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_int(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_into(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_iret(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_shift(u8 opcode_dw,
             void *file,
             buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_aam(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_aad(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_xlat(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_esc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_loopnz_loopne(u8 opcode_dw,
                     void *file,
                     buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_loopz_loope(u8 opcode_dw,
                   void *file,
                   buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_loop(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jcxz(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_in(u8 opcode_dw,
         void *file,
         buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_out(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_jmp(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_lock(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_rep(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_hlt(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cmc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_grp1(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_clc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_stc(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cli(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_sti(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_cld(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_std(u8 opcode_dw,
           void *file,
           buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
}

local int
decode_grp2(u8 opcode_dw,
            void *file,
            buf8 *b)
{
	unref(opcode_dw);
	unref(file);
	unref(b);
	return SIM86_NOT_IMPLEMENTED;
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

