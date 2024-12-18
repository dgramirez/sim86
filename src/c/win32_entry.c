#include "win32_entry.h"

void
_start()
{
	buf8 b = {0};
	buf8 mem86 = {0};
	c8 *argv[3];
	u8 *mem;
	i32 argc;
	i32 ret;

	os_write = win32_write;
	os_openfile = win32_openfile;
	os_readfile = win32_readfile;

	mem = VirtualAlloc(0, MB(3), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!mem) {
		win32_print(s8("ERROR: Unable to allocate 1 MB for sim86.\r\n"));
		win32_pause();
		ExitProcess((u32)-1);
	}

	mem86.cap = MB(1);
	mem86.data = mem;

	b.cap = MB(1);
	b.data = mem86.data + mem86.cap;
	b.fd = GetStdHandle(STD_OUTPUT_HANDLE);

	win32_getargs(&argc, (char **)argv, b.data + b.cap, KB(4));
	ret = i8086_main(argc, (char **)argv, &b);
	if (ret < 0) {
		win32_print(b.str);
		win32_pause();
	}
	else
		os_write(&b);

	ExitProcess(ret);
}

local void *
win32_openfile(char *filepath)
{
	HANDLE file;

	file = CreateFileA(filepath,
                       GENERIC_READ,
	                   FILE_SHARE_READ,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);
	if (file == INVALID_HANDLE_VALUE)
		return (void*)0;

	return file;
}

local b32
win32_readfile(u8 *out,
               u16 *ip,
               void *file,
               usz count)
{
	BOOL res;
	DWORD written;

	*ip += (u16)count;
	if (!count)
		return 0;

	res = ReadFile((HANDLE)file, out, (u32)count, &written, NULL);

	if (res && !written)
		return hit_eof;

	return 0;
}

local void
win32_write(buf8 *b)
{
	DWORD written;
	WriteFile((HANDLE)b->fd, b->data, (DWORD)b->len, &written, 0);
}

local void
win32_print(s8 s)
{
	DWORD written;
	HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsoleA(std_out, s.data, (DWORD)s.len, &written, 0);
}

local void
win32_pause()
{
	b32 loop;
	HANDLE std_in;

	win32_print(s8("Press the enter key to continue. . .\r\n"));

	loop = 1;
	std_in = GetStdHandle(STD_INPUT_HANDLE);
	while (loop) {
		FlushConsoleInputBuffer(std_in);
		WaitForSingleObject(std_in, INFINITE);

		if (GetAsyncKeyState(VK_RETURN))
			loop = 0;
	}
	FlushConsoleInputBuffer(std_in);
}

local void*
win32_getargs(i32 *argc,
              char **argv,
              void *buffer,
              int size)
{
	buf8 bargv = {0};
	LPWSTR *argvw;

	bargv.cap  = size;
	bargv.data = buffer;

	argv[0] = "";
	argv[1] = (char *)bargv.data;
	argv[2] = (char *)bargv.data + KB(2);

	argvw = CommandLineToArgvW(GetCommandLineW(), argc);
	if ((*argc > 1) && (lstrlenW(argvw[1]) <= KB(2)))
		WideCharToMultiByte(CP_ACP, 0, argvw[1], -1, argv[1], KB(2), 0, 0);

	if ((*argc > 2) && (lstrlenW(argvw[2]) <= KB(3)))
		WideCharToMultiByte(CP_ACP, 0, argvw[2], -1, argv[2], KB(2), 0, 0);

	return bargv.data;
}

