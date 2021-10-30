#include "test.h"

#define TEST_S(TYPE, UMAX, MAX, MIN) do { \
	typedef signed TYPE S; \
	typedef unsigned TYPE U; \
	\
	CKDTEST(ckd_add((S)2, (S)3), 5, 0); \
	CKDTEST(ckd_add((U)2, (S)3), 5, 0); \
	\
	CKDTEST(ckd_sub((S)5, (S)2), 3, 0); \
	CKDTEST(ckd_sub((U)5, (S)2), 3, 0); \
	\
	CKDTEST(ckd_mul((S)3, (S)2), 6, 0); \
	CKDTEST(ckd_mul((U)3, (S)2), 6, 0); \
} while(0)

void test() {
	TEST_S(short, USHRT_MAX, SHRT_MAX, SHRT_MIN);
	TEST_S(int, UINT_MAX, INT_MAX, INT_MIN);
#if !defined(__INTEL_COMPILER)
	TEST_S(long, ULONG_MAX, LONG_MAX, LONG_MIN);
	TEST_S(long long, ULLONG_MAX, LLONG_MAX, LLONG_MIN);
#endif
	TEST_S(char, UCHAR_MAX, SCHAR_MAX, SCHAR_MIN);
}
