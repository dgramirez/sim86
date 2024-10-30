#ifndef SIM86_SRC_C_BUFFER_H
#define SIM86_SRC_C_BUFFER_H

/* Trying out this buffer (and s8) combo from nullprogram
 * https://nullprogram.com/blog/2023/02/13/
 *
 * Will be slightly modified for my taste
 * 
 * Functions in here are also eligible for improvements if needed.
 */

local usz
c_strlen(const char *cstr)
{
	const char *end;

	end = cstr;
	while (*end) end++;

	return end - cstr;
}

local int
s8eq(s8 s1,
     s8 s2)
{
	/* MAJOR NOTE - This function is catered for this program only! */
	i8 count;

	count = 6;
	while (count--) {
		if (s1.data[0] - s2.data[0])
			return 0;

		s1.data++;
		s2.data++;
	}

	return 1;
}

local void
buf8_flush(buf8 *b)
{
	b->err |= ((isz)b->fd < 0);
	if (!b->err && b->len) {
		os_write(b);
		b->len = 0;
	}
}

local void
buf8_append(buf8 *b,
            s8 str)
{
	u8 *end;
	usz count;
	usz remainder;
	usz i;

	end = str.data + str.len;
	while (!b->err && str.data < end) {
		remainder = end - str.data;
		count = iminq(end - str.data, remainder, usz);
		for (i = 0; i < count; ++i)
			b->data[b->len+i] = str.data[i];

		b->len += count;
		str.data += count;

		if (count < remainder) {
			buf8_flush(b);
		}
	}
}

local void
buf8_appendcstr(buf8 *b,
                char *cstr)
{
	s8 str;

	str.data = (u8*)cstr;
	str.len = c_strlen(cstr);
	buf8_append(b, str);
}

local void
buf8_appendbyte(buf8 *b,
                byte c)
{
	if (b->len == b->cap)
		buf8_flush(b);

	b->data[b->len++] = c;
}

local void
buf8_appendlf(buf8 *b)
{
	#if defined _WIN32
		buf8_appendbyte(b, '\r'); // CR
	#endif
	buf8_appendbyte(b, '\n'); // LF
}

local void
buf8_appendcrlf(buf8 *b)
{
	buf8_appendbyte(b, '\r'); // CR
	buf8_appendbyte(b, '\n'); // LF
}

local void
buf8_appendisz(buf8 *b,
           isz x)
{
	u8 tmp[32] = {0};
	s8 input;
	u8 *end = tmp + sizeof(tmp);
	u8 *beg = end;

	if (x < 0) {
		tmp[0] = x < 0;
		x = -x;
	}

	do {
		*--beg = '0' + (x % 10);
	} while (x /= 10);

	if (tmp[0]) {
		*--beg = '-';
	}

	input.data = beg;
	input.len = end - beg;
	buf8_append(b, input);
}

local void
buf8_appendusz(buf8 *b,
           usz x)
{
	u8 tmp[32] = {0};
	s8 input;
	u8 *end;
	u8 *beg;

	end = tmp + sizeof(tmp);
	beg = end;
	do {
		*--beg = '0' + (x % 10);
	} while (x /= 10);

	input.data = beg;
	input.len = end - beg;
	buf8_append(b, input);
}

local void
buf8_appendhex(buf8 *b,
           usz x)
{
	static const u8 hex_table[] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
	};

	u8 tmp[32] = {0};
	s8 input;
	u8 *end;
	u8 *beg;

	end = tmp + sizeof(tmp);
	beg = end;
	do {
		*--beg = hex_table[x & 0xF];
	} while(x >>= 4);

	*--beg = 'x';
	*--beg = '0';

	input.data = beg;
	input.len = end - beg;
	buf8_append(b, input);
}

local void
buf8_appendf64(buf8 *b,
           double d) // [Insert Joke Here.]
{
	usz integral;
	usz fractional; 
	usz dbits;
	i32 precision;
	usz i;

	if (d < 0) {
		buf8_appendbyte(b, '-');
		d = -d;
	}

	d += 0.0000005;
	dbits = *(usz*)(&d);

	if (isinf(dbits)) {
		buf8_append(b, s8("inf"));
		return;
	}

	if (isnan(dbits)) {
		buf8_append(b, s8("nan"));
		return;
	}

	precision = 1000000;
	integral = (usz)d;
	fractional = (usz)((d - integral) * precision);

	buf8_appendusz(b, integral);
	buf8_appendbyte(b, '.');
	for (i = precision/10; i > 1; i /= 10) {
		if (i > fractional)
			buf8_appendbyte(b, '0');
	}

	buf8_appendusz(b, fractional);
}

#endif // SIM86_SRC_C_BUFFER_H

