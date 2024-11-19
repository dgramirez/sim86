#ifndef SIM86_SRC_C_8086_C
#define SIM86_SRC_C_8086_C

local i32
i8086_main(int argc,
           char **argv,
           buf8 *b)
{
	BitNamesForEncodings bits;
	void *file;
	b32 err;
	int sim;

	err = validate_all_pfn(b);
	if (err) return err;

	if (validate_mode(&sim, b, argv, argc))
		return SIM86_PANIC;

	if (validate_file(&file, b, argv, argc))
		return SIM86_PANIC;

	memzero_128((char*)(&bits));
	buf8_appendbyte(b, ';');
	buf8_appendbyte(b, ' ');
	buf8_appendcstr(b, argv[argc-1]);
	buf8_appendlf(b);
	buf8_appendlf(b);

	buf8_append(b, s8("bits 16"));
	buf8_appendlf(b);
	buf8_appendlf(b);

	while (!os_readfile(&bits.opcode, &bits.ip, file, 1)) {
		unref(sim);
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

	return SIM86_OK;
}

local void
help(buf8 *b)
{
	buf8_append(b, s8(
		"Intel 8086 Simulator Help: \n\n"

		"========\n"
		"= NAME =\n"
		"========\n"
		"sim86 - Intel 8086 Simulator\n\n"

		"============\n"
		"= Synopsis =\n"
		"============\n"
		"sim86 decode [8086/8088 binary file]\n"
		"\t- Decodes the binary file and displays the nasm assembly.\n"
		"\t- onto the screen.\n\n"

		"sim86 [8086/8088 binary file]\n"
		"sim86 simulate [8086/8088 binary file]\n"
		"\t- These simulate the instructions for the 8086 and displays\n"
		"\t  the changes onto the screen\n\n"

		"===============\n"
		"= Description =\n"
		"===============\n"
		"sim86 simulates the decoding of an 8086 processor.\n\n"
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

local b32
validate_all_pfn(buf8 *b)
{
	if (validate_pfn(b,
	                 (void*)os_write,
	                 (void*)stub_write,
	                 s8("os_write")))
	{
		return SIM86_OS_WRITE_IS_NULL_OR_STUB;
	}

	if (validate_pfn(b,
	                 (void*)os_openfile,
	                 (void*)stub_openfile,
	                 s8("os_openfile")))
	{
		return SIM86_PANIC;
	}

	if (validate_pfn(b,
	                 (void*)os_readfile,
	                 (void*)stub_readfile,
	                 s8("os_readfile")))
	{
		return SIM86_PANIC;
	}

	return SIM86_OK;
}

local b32
validate_mode(int *out_sim,
              buf8 *b,
              char **argv,
              int argc)
{
	s8 cmd;

	if (argc == 2)
		*out_sim = 1;
	else if (argc == 3) {
		cmd.data = (u8*)argv[1];
		cmd.len = c_strlen(argv[1]);
		if (s8eq(cmd, s8("decode")))
			*out_sim = 0;
		else if (s8eq(cmd, s8("simulate")))
			*out_sim = 1;
		else {
			buf8_append(b, s8("Bad Mode Argument. (Got "));
			buf8_append(b, cmd);
			buf8_append(b, s8(", not \"decode\" or \"simulate\".)\n"));
			buf8_append(b, s8("NOTE: arg must be all lowercase. \n\n"));

			help(b);
			return SIM86_PANIC;
		}
	}
	else {
		buf8_append(b, s8("Bad Argument Count. (Got "));
		buf8_appendisz(b, argc);
		buf8_append(b, s8(", not 2 or 3)\n\n"));

		help(b);
		return SIM86_PANIC;
	}

	return SIM86_OK;
}

local b32
validate_file(void **out_file,
              buf8 *b,
              char **argv,
              int argc)
{
	// NOTE - Make sure "validate_mode" function is called first!
	//        This is to make sure the arguments are in the right order!
	void *file;

	file = os_openfile(argv[argc-1]);
	if (!file) {
		*out_file = (void *)0;

		buf8_append(b, s8("Unable to open file: "));
		buf8_appendcstr(b, argv[argc-1]);
		buf8_appendbyte(b, '\n');
		buf8_appendbyte(b, '\n');

		help(b);
		return SIM86_PANIC;
	}

	*out_file = file;
	return SIM86_OK;
}

#endif // SIM86_SRC_C_8086_C

