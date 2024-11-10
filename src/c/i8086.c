#ifndef SIM86_SRC_C_8086_C
#define SIM86_SRC_C_8086_C

local void
help(buf8 *b);

local b32
validate_pfn(buf8 *b,
             void *fn,
             void *stub,
             s8 fn_name);

local i32
i8086_main(int argc,
           char **argv,
           buf8 *b)
{
	BitNamesForEncodings bits;
	void *file;
	b32 err;
	s8 mode;

	err = validate_pfn(b,
	                   (void*)os_write,
	                   (void*)stub_write,
	                   s8("os_write"));
	if (err)
		return SIM86_OS_WRITE_IS_NULL_OR_STUB;

	err = validate_pfn(b,
	                   (void*)os_openfile,
	                   (void*)stub_openfile,
	                   s8("os_openfile"));
	if (err)
		return SIM86_PANIC;

	err = validate_pfn(b,
	                   (void*)os_readfile,
	                   (void*)stub_readfile,
	                   s8("os_readfile")); 
	if (err)
		return SIM86_PANIC;

	if (argc != 3) {
		buf8_append(b, s8("Bad Argument Count. (Got "));
		buf8_appendisz(b, argc);
		buf8_append(b, s8(", not 3)\n\n"));

		help(b);
		return SIM86_PANIC;
	}

	// Note - argv[1] should be decode.
	mode.data = (u8*)argv[1];
	mode.len = c_strlen(argv[1]);
	if (mode.len != 6) {
		buf8_append(b, s8("Bad Command Argument Size. (Got "));
		buf8_append(b, mode);
		buf8_append(b, s8(", not  \"decode\".)\n\n"));

		help(b);
		return SIM86_PANIC;
	}

	// Note - argv[2] should be the filepath to the 8086 asm / binary file.
	file = os_openfile(argv[2]);
	if (!file) {
		buf8_append(b, s8("Unable to open file: "));
		buf8_appendcstr(b, argv[2]);
		buf8_appendbyte(b, '\n');
		buf8_appendbyte(b, '\n');

		help(b);
		return SIM86_PANIC;
	}

	memzero_128((char*)(&bits));
	if (s8eq(mode, s8("decode"))) {
		buf8_appendbyte(b, ';');
		buf8_appendbyte(b, ' ');
		buf8_appendcstr(b, argv[2]);
		buf8_appendlf(b);
		buf8_appendlf(b);

		buf8_append(b, s8("bits 16"));
		buf8_appendlf(b);
		buf8_appendlf(b);

		while (!os_readfile(&bits.opcode, &bits.ip, file, 1)) {
			if (i8086_fn_decodes[bits.opcode](&bits, file, b)) {
				buf8_flush(b);

				buf8_appendlf(b);
				buf8_appendlf(b);
				buf8_append(b, s8("; PANIC OCCURRED ON OPCODE: "));
				buf8_appendhex(b, bits.opcode);
				buf8_appendlf(b);

				return SIM86_PANIC;
			}
		}
	}
	else {
		buf8_append(b, s8("Bad Mode Argument. (Got "));
		buf8_append(b, mode);
		buf8_append(b, s8(", not \"decode\".)\n"));
		buf8_append(b, s8("NOTE: the arg must be in all lowercase. \n\n"));

		help(b);
		return SIM86_PANIC;
	}

	return SIM86_OK;
}

local void
help(buf8 *b)
{
	buf8_append(b, s8(
		"Intel 8086 Simulator Help: \n"
		"========\n"
		"= NAME =\n"
		"========\n"
		"sim86 - Intel 8086 Simulator\n\n"
		"============\n"
		"= Synopsis =\n"
		"============\n"
		"sim86 decode [8086/8088 binary file]\n"
		"===============\n"
		"= Description =\n"
		"===============\n"
		"sim86 simulates the decoding of an 8086 processor "
		"or 8088 procesor.\n"
	));
}

local b32
validate_pfn(buf8 *b,
             void *fn,
             void *stub,
             s8 fn_name)
{
	if (fn == 0 || fn == stub) {
		buf8_append(b, s8("INTERNAL ERROR: "));
		buf8_append(b, fn_name);
		buf8_append(b, s8(" is not correct!\n"));
		buf8_append(b, fn_name);
		buf8_append(b, s8(" ptr: "));
		buf8_appendhex(b, (usz)fn);

		if (os_openfile)
			buf8_append(b, s8(" (Stub Function?)"));

		buf8_appendbyte(b, '\n');
		buf8_appendbyte(b, '\n');

		return SIM86_PANIC;
	}

	return SIM86_OK;
}

#endif // SIM86_SRC_C_8086_C

