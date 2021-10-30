#include "test.h"

#define FOREACH_TYPESPROP(M, ...) \
	M(shrt, short, SHRT_MAX, SHRT_MIN, ##__VA_ARGS__); \
	M(ushrt, unsigned short, USHRT_MAX, 0, ##__VA_ARGS__); \
	M(int, int, INT_MAX, INT_MIN, ##__VA_ARGS__); \
	M(uint, unsigned, UINT_MAX, 0, ##__VA_ARGS__); \
	M(long, long, LONG_MAX, LONG_MIN, ##__VA_ARGS__); \
	M(ulong, unsigned long, ULONG_MAX, 0, ##__VA_ARGS__); \
	M(llong, long long, LLONG_MAX, LLONG_MIN, ##__VA_ARGS__); \
	M(ullong, unsigned long long, ULLONG_MAX, 0, ##__VA_ARGS__); \
	M(char, char, CHAR_MAX, CHAR_MIN, ##__VA_ARGS__); \
	M(schar, signed char, SCHAR_MAX, SCHAR_MIN, ##__VA_ARGS__); \
	M(uchar, unsigned char, UCHAR_MAX, 0, ##__VA_ARGS__);

#define TEST_S(_, TS, MAXS, MINS, T, UMAX, MAX, MIN) do { \
	typedef unsigned T  U; \
	typedef T S; \
	const bool issigned = MINS; \
	const bool UMAXoverflow = issigned ? (intmax_t)UMAX > (intmax_t)MAXS : (uintmax_t)UMAX > (uintmax_t)MAXS; \
	const bool MAXoverflow = issigned ? (intmax_t)MAX > (intmax_t)MAXS : (uintmax_t)MAX > (uintmax_t)MAXS; \
	S a; (void)a; \
	TEST_OP3(TS, add, (U)UMAX, 0u, (TS)UMAX, UMAXoverflow); \
	TEST_OP3(TS, add, (U)MAX, 0u, (TS)MAX, MAXoverflow); \
	TEST_OP3(TS, add, (S)MAX, 0, (TS)MAX, MAXoverflow); \
} while(0)

void test() {
	FOREACH_TYPESPROP(TEST_S, int, UINT_MAX, INT_MAX, INT_MIN);
	//TEST_S(long, ULONG_MAX, LONG_MAX, LONG_MIN);
	//TEST_S(long long, ULLONG_MAX, LLONG_MAX, LLONG_MIN);
	//TEST_S(char, UCHAR_MAX, SCHAR_MAX, SCHAR_MIN);
	TEST_OP3(signed char, add, INT_MAX, 0, -1, 1);
	TEST_OP3(unsigned short, add, UINT_MAX, 0, USHRT_MAX, 1);
}

