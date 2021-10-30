#ifndef TESTS_TEST_H_
#define TESTS_TEST_H_

#include <ckdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __SIZEOF_INT128__
#ifndef INT128_MAX
#define INT128_MAX   ((__int128)(((unsigned __int128) 1 << ((__SIZEOF_INT128__ * __CHAR_BIT__) - 1)) - 1))
#endif
#ifndef INT128_MIN
#define INT128_MIN   (-INT128_MAX - 1)
#endif
#ifndef UINT128_MAX
#define UINT128_MAX  ((2 * (unsigned __int128) INT128_MAX) + 1)
#endif
#endif  // __SIZEOF_INT128__

#define TC(x)  ckd_##x##_t: "ckd_"#x"_t"
#ifdef HAVE_INT128
#define TC_INT128()  __int128_t: "int128", __uint128_t: "uint128", TC(int128), TC(uint128),
#else
#define TC_INT128()
#endif
#define typename(x) _Generic(x,                                                 \
            _Bool: "bool",                  unsigned char: "unsigned char",          \
             char: "char",                     signed char: "signed char",            \
        short int: "short int",         unsigned short int: "unsigned short int",     \
              int: "int",                     unsigned int: "unsigned int",           \
         long int: "long int",           unsigned long int: "unsigned long int",      \
    long long int: "long long int", unsigned long long int: "unsigned long long int", \
            float: "float",                         double: "double",                 \
      long double: "long double",                   char *: "pointer to char",        \
           void *: "pointer to void",                int *: "pointer to int",         \
		   TC(char), \
		   TC(schar), TC(uchar), \
		   TC(shrt), TC(ushrt), \
		   TC(int), TC(uint), \
		   TC(long), TC(ulong), \
		   TC(llong), TC(ullong), \
		   TC_INT128() \
		  default: "other")

bool test_failed = 0;

static const char RED[] = "\E[1m\E[31m";
static const char RESET[] = "\E(B\E[m";

#define FILENAME() (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG(...)  do { \
	fflush(0); \
	fprintf(stderr, "%s:%3d: ", FILENAME(), __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "%s\n", RESET); \
} while(0)

#define ERROR(...)  do { \
	fflush(0); \
	fprintf(stderr, "%s:%3d: %sERROR: ", FILENAME(), __LINE__, RED); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "%s\n", RESET); \
} while(0)


#define INTEST(expr, strexpr) do{ \
	if (!(expr)) { \
		ERROR("Expression: %s: failed", strexpr); \
		test_failed = 1; \
	} else { \
		LOG("%s is true", strexpr); \
	} \
}while(0)

#define TEST(expr)  INTEST(expr, #expr)

#define TEST_EQ_IN(expr1, expr1str, expr2, expr2str) do{ \
	uintmax_t _expr1 = (uintmax_t)(expr1); \
	uintmax_t _expr2 = (uintmax_t)(expr2); \
	if (_expr1 != _expr2) { \
		ERROR("Expression: %s == %s is false: (%s)%juu/%jdd != (%s)%juu/%jdd", \
				expr1str, expr2str, \
				typename(expr1), _expr1, (intmax_t)_expr1, \
				typename(expr2), _expr2, (intmax_t)_expr2); \
		test_failed = 1; \
	} else { \
		LOG("%s == %s", expr1str, expr2str); \
	} \
} while(0);

#define TEST_EQ(expr1, expr2)  TEST_EQ_IN(expr1, #expr1, expr2, #expr2)


#define CKDTEST(expr, value, overflow) do { \
		uintmax_t _value = (uintmax_t)ckd_value(expr); \
		uintmax_t _overflow = (uintmax_t)ckd_overflow(expr); \
		LOG("Testing expression %s -> %s", #expr, typename(ckd_value(expr))); \
		TEST_EQ_IN(_value, #expr ".value", value, #value); \
		TEST_EQ_IN(_overflow, #expr ".overflow", overflow, #overflow); \
} while(0)

#define TEST_OP3(RESTYPE, OP, a, b, val, o)  do { \
	LOG("TEST_OP3 ckd_%s(%s, (%s)%s, (%s)%s) =? {%s, %s}", \
		#OP, #RESTYPE, typename(a), #a, typename(b), #b, #val, #o); \
	RESTYPE _var = 0; \
	TEST_EQ(ckd_##OP(&_var, a, b), o); \
	TEST_EQ(_var, val); \
} while(0)

#define TEST_COP3(KEY, OP, a, b, val, o)  do { \
	LOG("TEST_OP3 ckd_%s(ckd_%s_t, (%s)%s, (%s)%s) =? {%s, %s}", \
		#OP, #KEY, typename(a), #a, typename(b), #b, #val, #o); \
	ckd_##KEY##_t _var = {0}; \
	TEST_EQ(ckd_##OP(&_var, a, b), o); \
	TEST_EQ(ckd_overflow(_var), o); \
	TEST_EQ(ckd_value(_var), val); \
} while(0)

#define FOREACH_TYPE(M, ...) \
	M(schar, signed char, ##__VA_ARGS__); \
	M(uchar, unsigned char, ##__VA_ARGS__); \
	M(shrt, short, ##__VA_ARGS__); \
	M(ushrt, unsigned short, ##__VA_ARGS__); \
	M(int, int, ##__VA_ARGS__); \
	M(uint, unsigned, ##__VA_ARGS__); \
	M(long, long, ##__VA_ARGS__); \
	M(ulong, unsigned long, ##__VA_ARGS__); \
	M(llong, long long, ##__VA_ARGS__); \
	M(ullong, unsigned long long, ##__VA_ARGS__);

#define FOREACH_PROMOTEDTYPE(M, ...) \
	M(int, int, ##__VA_ARGS__); \
	M(uint, unsigned, ##__VA_ARGS__); \
	M(long, long, ##__VA_ARGS__); \
	M(ulong, unsigned long, ##__VA_ARGS__); \
	M(llong, long long, ##__VA_ARGS__); \
	M(ullong, unsigned long long, ##__VA_ARGS__);

void test(void);

int main() {
	test();
	return !test_failed ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif  // TESTS_TEST_H_
