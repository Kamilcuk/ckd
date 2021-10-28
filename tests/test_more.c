#include "test.h"

#define TEST_S(TYPE, UMAX, MAX, MIN) do { \
	typedef signed TYPE S; \
	typedef unsigned TYPE U; \
	\
	TEST_OP3(S, add, ULLONG_MAX - 1, 1, ULLONG_MAX, 1); \
	TEST_OP3(S, add, ULLONG_MAX, (unsigned long long)0, (S)ULLONG_MAX, 1); \
	TEST_OP3(S, add, (unsigned long long)2, (unsigned long long)3, 5, 0); \
	TEST_OP3(S, add, 1, 1, 2, 0); \
	TEST_OP3(S, add, MAX, (S)1, MIN, 1); \
	TEST_OP3(S, add, (S)2, (U)3, 5, 0); \
	TEST_OP3(S, add, (S)MAX, (U)1, MIN, 1); \
	TEST_OP3(S, add, (U)2, (U)3, 5, 0); \
	TEST_OP3(S, add, (U)MAX, (U)1, MIN, 1); \
	TEST_OP3(S, add, (U)2, (S)3, 5, 0); \
	TEST_OP3(S, add, (U)MAX, (S)1, MIN, 1); \
	\
	TEST_OP3(S, sub, ULLONG_MAX, ULLONG_MAX, 0, 0); \
	TEST_OP3(S, sub, MIN, (S)1, MAX, 1); \
	TEST_OP3(S, sub, (U)UMAX, (S)1, -2, 1); \
	TEST_OP3(S, add, MAX, 1, MIN, 1); \
	TEST_OP3(S, sub, MIN, 1, MAX, 1); \
	TEST_OP3(S, sub, (U)MIN, (S)1, MAX, 0); \
	TEST_OP3(S, sub, (S)MIN, (U)1, MAX, 1); \
	TEST_OP3(S, sub, (U)MIN, (U)1, MAX, 0); \
	\
	TEST_OP3(S, mul, ULLONG_MAX, 1, ULLONG_MAX, 1); \
	TEST_OP3(S, mul, LLONG_MAX, 2, (S)((U)LLONG_MAX * (U)2), 1); \
	TEST_OP3(S, mul, LLONG_MAX, (long long)1, (S)LLONG_MAX, LLONG_MAX > MAX); \
	TEST_OP3(S, mul, ULLONG_MAX, (unsigned long long)1, (S)ULLONG_MAX, ULLONG_MAX >= UMAX); \
	TEST_OP3(S, mul, ULLONG_MAX, (unsigned long long)0, 0, 0); \
	TEST_OP3(S, mul, MIN, (S)-1, MIN, 1); \
	TEST_OP3(S, mul, MIN, -1, MIN, 1); \
	TEST_OP3(S, mul, (U)2, (U)3, 6, 0); \
	TEST_OP3(S, mul, (U)2, (S)3, 6, 0); \
	TEST_OP3(S, mul, (S)2, (U)3, 6, 0); \
	TEST_OP3(S, mul, (U)MAX, (U)2, (S)((U)MAX * (U)2), 1); \
	TEST_OP3(S, mul, (S)MAX, (U)2, (S)((U)MAX * (U)2), 1); \
	TEST_OP3(S, mul, (U)MAX, (S)2, (S)((U)MAX * (U)2), 1); \
	\
	TEST_OP3(U, add, ULLONG_MAX, (unsigned long long)0, (U)ULLONG_MAX, ULLONG_MAX > UMAX); \
	TEST_OP3(U, add, (unsigned long long)2, (unsigned long long)3, 5, 0); \
	TEST_OP3(U, add, 1, 1, 2, 0); \
	TEST_OP3(U, add, (U)UMAX, (S)1, 0, 1); \
	TEST_OP3(U, add, (U)UMAX, (U)1, 0, 1); \
	TEST_OP3(U, add, UMAX, 1, 0, 1); \
	\
	TEST_OP3(U, sub, ULLONG_MAX, ULLONG_MAX, 0, 0); \
	TEST_OP3(U, sub, (U)UMAX, (U)1, (U)UMAX - 1, 0); \
	TEST_OP3(U, sub, (S)-1, (U)1, (U)-2, 1); \
	TEST_OP3(U, sub, (U)1, (S)2, (U)-1, 1); \
	TEST_OP3(U, sub, (S)2, (S)1, (U)1, 0); \
	TEST_OP3(U, sub, (S)2, (S)3, (U)-1, 1); \
	TEST_OP3(U, sub, (S)MAX, (S)-1, (U)MAX + 1, 0); \
	\
	TEST_OP3(U, mul, (S)-1, 1, UMAX, 1); \
	TEST_OP3(U, mul, (S)-1, (U)1, UMAX, 1); \
	TEST_OP3(U, mul, -1, 1, UMAX, 1); \
	TEST_OP3(U, mul, MIN, 1, (U)MIN, 1); \
	TEST_OP3(U, mul, ULLONG_MAX, ULLONG_MAX, 1, 1); \
	TEST_OP3(U, mul, UMAX, UMAX, 1, 1); \
	TEST_OP3(U, mul, (U)2, (U)3, 6, 0); \
	TEST_OP3(U, mul, (U)2, (S)3, 6, 0); \
	TEST_OP3(U, mul, (S)2, (U)3, 6, 0); \
	TEST_OP3(U, mul, (U)MAX, (U)3, (U)((U)MAX * (U)3), 1); \
	TEST_OP3(U, mul, (U)2, (S)-3, (U)-6, 1); \
	TEST_OP3(U, mul, (S)-2, (U)3, (U)-6, 1); \
	TEST_OP3(U, mul, ULLONG_MAX, (unsigned long long)1, (U)ULLONG_MAX, ULLONG_MAX > UMAX); \
	TEST_OP3(U, mul, ULLONG_MAX, (unsigned long long)0, 0, 0); \
	\
	CKDTEST(ckd_add((S)1, (S)1), 2, 0); \
	CKDTEST(ckd_add((U)1, (U)1), 2, 0); \
	CKDTEST(ckd_add((S)1, (U)1), 2, 0); \
	CKDTEST(ckd_add((U)1, (S)1), 2, 0); \
} while(0)

int main() {
	TEST_S(short, USHRT_MAX, SHRT_MAX, SHRT_MIN);
	TEST_S(int, UINT_MAX, INT_MAX, INT_MIN);
#if !defined(__INTEL_COMPILER)
	// https://community.intel.com/t5/Intel-C-Compiler/icc-bug-builtin-mul-overflow-wrong-overflow-value-when-casting/m-p/1324099/emcs_t/S2h8ZW1haWx8dG9waWNfc3Vic2NyaXB0aW9ufEtWMlQ3WDdNRjUwMktMfDEzMjQwOTl8U1VCU0NSSVBUSU9OU3xoSw#M39393
	TEST_S(long, ULONG_MAX, LONG_MAX, LONG_MIN);
	TEST_S(long long, ULLONG_MAX, LLONG_MAX, LLONG_MIN);
#endif
	TEST_S(char, UCHAR_MAX, SCHAR_MAX, SCHAR_MIN);
	CKDEND();
}

