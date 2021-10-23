#include "test.h"

#define TEST_S(TYPE, UMAX, MAX, MIN) do { \
	{ \
	signed TYPE svar; \
	TEST_EQ(ckd_sub(&svar, ULLONG_MAX, ULLONG_MAX), 0); \
	TEST_EQ(svar, 0); \
	TEST_EQ(ckd_add(&svar, 1, 1), 0); \
	TEST_EQ(svar, 2); \
	TEST_EQ(ckd_add(&svar, MAX, (signed TYPE)1), 1); \
	TEST_EQ(svar, MIN); \
	TEST_EQ(ckd_sub(&svar, MIN, (signed TYPE)1), 1); \
	TEST_EQ(svar, MAX); \
	TEST_EQ(ckd_add(&svar, MAX, 1), 1); \
	TEST_EQ(svar, MIN); \
	TEST_EQ(ckd_sub(&svar, MIN, 1), 1); \
	TEST_EQ(svar, MAX); \
	TEST_EQ(ckd_mul(&svar, MIN, (signed TYPE)-1), 1); \
	TEST_EQ(svar, MIN); \
	TEST_EQ(ckd_mul(&svar, MIN, -1), 1); \
	TEST_EQ(svar, MIN); \
	} \
	\
	{ \
	unsigned TYPE uvar; \
	TEST_EQ(ckd_sub(&uvar, ULLONG_MAX, ULLONG_MAX), 0); \
	TEST_EQ(uvar, 0); \
	TEST_EQ(ckd_add(&uvar, 1, 1), 0); \
	TEST_EQ(uvar, 2); \
	TEST_EQ(ckd_add(&uvar, (unsigned TYPE)UMAX, (signed TYPE)1), 1); \
	TEST_EQ(uvar, 0); \
	TEST_EQ(ckd_add(&uvar, (unsigned TYPE)UMAX, (unsigned TYPE)1), 1); \
	TEST_EQ(uvar, 0); \
	TEST_EQ(ckd_add(&uvar, UMAX, 1), 1); \
	TEST_EQ(uvar, 0); \
	TEST_EQ(ckd_mul(&uvar, (signed TYPE)-1, 1), 1); \
	TEST_EQ(uvar, UMAX); \
	TEST_EQ(ckd_mul(&uvar, -1, 1), 1); \
	TEST_EQ(uvar, UMAX); \
	TEST_EQ(ckd_mul(&uvar, MIN, 1), 1); \
	TEST_EQ(uvar, (unsigned TYPE)MIN); \
	TEST_EQ(ckd_mul(&uvar, ULLONG_MAX, ULLONG_MAX), 1); \
	TEST_EQ(uvar, 1); \
	TEST_EQ(ckd_mul(&uvar, UMAX, UMAX), 1); \
	TEST_EQ(uvar, 1); \
	} \
	\
	typedef signed TYPE S; \
	typedef unsigned TYPE U; \
	CKDTEST(ckd_add((S)1, (S)1), 2, 0); \
	CKDTEST(ckd_add((U)1, (U)1), 2, 0); \
	CKDTEST(ckd_add((S)1, (U)1), 2, 0); \
	CKDTEST(ckd_add((U)1, (S)1), 2, 0); \
} while(0)

int main() {
	TEST_S(short, USHRT_MAX, SHRT_MAX, SHRT_MIN);
	TEST_S(int, UINT_MAX, INT_MAX, INT_MIN);
	TEST_S(long, ULONG_MAX, LONG_MAX, LONG_MIN);
	TEST_S(long long, ULLONG_MAX, LLONG_MAX, LLONG_MIN);
	TEST_S(char, UCHAR_MAX, SCHAR_MAX, SCHAR_MIN);
	CKDEND();
}

