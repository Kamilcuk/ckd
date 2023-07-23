// Originally written by Justine Tunney .
// https://gitlab.com/Kamcuk/ckd/-/issues/3
// https://gist.github.com/jart/d004a1a39940247e5398180c8484ebbd

#if !__GNUC__ || __INTEL_COMPILER
int main() {
}
#else

#include <ckdint.h>
#include <stdio.h>

#ifndef __GNUC__
#error Only for GNUC
#endif

// Have single word for macro tokenizations ##T below.
typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef signed __int128 int128_t;
typedef unsigned __int128 uint128_t;

#define TBIT(T) (sizeof(T) * 8 - 1)
#define TMIN(T) (((T) ~(T)0) > 1 ? (T)0 : (T)((uint128_t)1 << TBIT(T)))
#define TMAX(T) (((T) ~(T)0) > 1 ? (T) ~(T)0 : (T)(((uint128_t)1 << TBIT(T)) - 1))

#define DECLARE_TEST_VECTORS(T) \
	static const T k##T[] = { \
	    0, \
	    1, \
	    2, \
	    3, \
	    4, \
	    5, \
	    6, \
	    (T)-1, \
	    (T)-2, \
	    (T)-3, \
	    (T)-4, \
	    (T)-5, \
	    (T)-6, \
	    TMIN(T), \
	    (T)(TMIN(T) + 1), \
	    (T)(TMIN(T) + 2), \
	    (T)(TMIN(T) + 3), \
	    (T)(TMIN(T) + 4), \
	    TMAX(T), \
	    (T)(TMAX(T) - 1), \
	    (T)(TMAX(T) - 2), \
	    (T)(TMAX(T) - 3), \
	    (T)(TMAX(T) - 4), \
	    (T)(TMIN(T) / 2), \
	    (T)(TMIN(T) / 2 + 1), \
	    (T)(TMIN(T) / 2 + 2), \
	    (T)(TMIN(T) / 2 + 3), \
	    (T)(TMIN(T) / 2 + 4), \
	    (T)(TMAX(T) / 2), \
	    (T)(TMAX(T) / 2 - 1), \
	    (T)(TMAX(T) / 2 - 2), \
	    (T)(TMAX(T) / 2 - 3), \
	    (T)(TMAX(T) / 2 - 4), \
	}

static unsigned errors = 0;

#define BUFLEN 128
static char buf[4][BUFLEN];
static const char *pr128(char buf[static BUFLEN], uint128_t x) {
	unsigned long long up = (unsigned long long)(x >> 64);
	if (up) {
		snprintf(buf, BUFLEN, "0x%llx%016llx", up, (unsigned long long)x);
	} else {
		snprintf(buf, BUFLEN, "%lld", (unsigned long long)x);
	}
	return buf;
}

static void OnTest(const char *name, const char *rstr, const char *astr, const char *bstr, uint128_t a, uint128_t b,
		   uint128_t r1, bool of1, uint128_t r2, bool of2) {
	if (r1 != r2 || of1 != of2) {
		printf("ERROR: (%s)%s %s (%s)%s = (%s): ckd_%s->{%s, %d} != {%s, %d}<-__builtin_%s_overflow\n", astr,
		       pr128(buf[0], a), name, bstr, pr128(buf[1], b), rstr, name, pr128(buf[2], r1), of1,
		       pr128(buf[3], r2), of2, name);
		errors++;
	}
}

#define M(T, U, V) \
	for (unsigned i = 0; i < sizeof(k##U) / sizeof(k##U[0]); ++i) { \
		const U x = k##U[i]; \
		for (unsigned j = 0; j < sizeof(k##V) / sizeof(k##V[0]); ++j) { \
			const V y = k##V[j]; \
			T r1, r2; \
			bool of1, of2; \
\
			of1 = ckd_add(&r1, x, y); \
			of2 = __builtin_add_overflow(x, y, &r2); \
			OnTest("add", #T, #U, #V, x, y, r1, of1, r2, of2); \
\
			of1 = ckd_sub(&r1, x, y); \
			of2 = __builtin_sub_overflow(x, y, &r2); \
			OnTest("sub", #T, #U, #V, x, y, r1, of1, r2, of2); \
\
			of1 = ckd_mul(&r1, x, y); \
			of2 = __builtin_mul_overflow(x, y, &r2); \
			OnTest("mul", #T, #U, #V, x, y, r1, of1, r2, of2); \
		} \
	}

DECLARE_TEST_VECTORS(char);
DECLARE_TEST_VECTORS(schar);
DECLARE_TEST_VECTORS(uchar);
DECLARE_TEST_VECTORS(short);
DECLARE_TEST_VECTORS(ushort);
DECLARE_TEST_VECTORS(int);
DECLARE_TEST_VECTORS(uint);
DECLARE_TEST_VECTORS(long);
DECLARE_TEST_VECTORS(ulong);
DECLARE_TEST_VECTORS(longlong);
DECLARE_TEST_VECTORS(ulonglong);
DECLARE_TEST_VECTORS(int128_t);
DECLARE_TEST_VECTORS(uint128_t);

#define MM(T, U) \
	M(T, U, char) \
	M(T, U, schar) \
	M(T, U, uchar) \
	M(T, U, short) \
	M(T, U, ushort) \
	M(T, U, int) \
	M(T, U, uint) \
	M(T, U, long) \
	M(T, U, ulong) \
	M(T, U, longlong) \
	M(T, U, ulonglong) \
	M(T, U, int128_t) \
	M(T, U, uint128_t)

#define MMM(T) \
	MM(T, char) \
	MM(T, schar) \
	MM(T, uchar) \
	MM(T, short) \
	MM(T, ushort) \
	MM(T, int) \
	MM(T, uint) \
	MM(T, long) \
	MM(T, ulong) \
	MM(T, longlong) \
	MM(T, ulonglong) \
	MM(T, int128_t) \
	MM(T, uint128_t)

static int end() {
	return errors == 0 ? 0 : -1;
}

#ifndef TYPE
#error
#endif

int main() {
	MMM(TYPE);
	return end();
}

#endif
