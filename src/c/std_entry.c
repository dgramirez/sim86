#include "std_entry.h"

int main(int argc,
         char **argv)
{
	buf8 b = {0};
	buf8 mem86 = {0};
	u8 *mem;
	i32 ret;

	os_write = std_write;
	os_openfile = std_openfile;
	os_readfile = std_readfile;

	mem = malloc(MB(2));
	if (!mem) {
		printf("ERROR: Unable to allocate 1 MB of data.\n");
		return SIM86_PANIC;
	}
	memset(mem, 0, MB(2));

	mem86.cap = MB(1);
	mem86.data = mem;

	b.cap = MB(1);
	b.data = mem86.data + mem86.cap;
	b.fd = stdout;

	ret = i8086_main(argc, argv, &b);
	if (ret == SIM86_OS_WRITE_IS_NULL_OR_STUB) {
		fwrite(b.data, sizeof(char), b.len, stdout);
		return SIM86_PANIC;
	}

	os_write(&b);
//	free(mem);
	return ret;
}

local void *
std_openfile(char *filepath)
{
	FILE *file;

	file = fopen(filepath, "r");
	if (!file)
		return (void*)0;

	return file;
}

local b32
std_readfile(u8 *out,
             u16 *ip,
             void *file,
             usz count)
{
	*ip += (u16)count;
	if (!count)
		return 0;

	fread(out, sizeof(char), count, (FILE*)file);
	return feof((FILE*)file) || ferror((FILE*)file);
}

local void
std_write(buf8 *b)
{
	fwrite(b->data, sizeof(char), b->len, stdout);
}

