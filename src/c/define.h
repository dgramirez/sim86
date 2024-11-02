#ifndef SIM86_SRC_C_DEFINE_H
#define SIM86_SRC_C_DEFINE_H

#define unref(x) (void)sizeof(x)
#define local static
#define global static
#define persistent static
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)

#define flag_set(x, f) ((x) |= (f))
#define flag_rem(x, f) ((x) &= (~(f)))
#define flag_tog(x, f) ((x) ^= (f))
#define flag_has(x, f) ((x) & (f))
#define flag_equ(x, f) (((x) & (f)) == (f))

#define countof(a) (usz)(sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

#define minmax_bits(x, y) (((x) ^ (y)) & -((x) < (y)))
#define imin(x, y) ((y) ^ minmax_bits((x), (y)))
#define imax(x, y) ((x) ^ minmax_bits((x), (y)))

#define minmaxq_bits(x, y, t) (((x) - (y)) & (((x) - (y)) >> \
	                          ((sizeof(t) << 3) - 1)))
#define iminq(x, y, t) ((y) + minmaxq_bits((x), (y), t))
#define imaxq(x, y, t) ((x) - minmaxq_bits((x), (y), t))

// TODO: Fix this Problem for x86 Platforms!
#define isinf(x) (((x) & 0x7FF0000000000000) == 0x7FF0000000000000)
#define isnan(x) (((x) & 0x7FFFFFFFFFFFFFFF) > 0x7FF0000000000000)

#define hit_eof 1

typedef enum {
	SIM86_OK = 0,
	SIM86_PANIC = -1,
	SIM86_NOT_IMPLEMENTED = -2,
	SIM86_OS_WRITE_IS_NULL_OR_STUB = -3,
	SIM86_DECODE = 1,
	SIM86_ENCODE = 2,
} SIM86_VALUES;

#endif // SIM86_SRC_C_DEFINE_H

