#ifndef TESTS_TEST_H_
#define TESTS_TEST_H_

#include <ckdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define typename(x) _Generic(_ckd_value(x),                                                 \
            _Bool: "_Bool",                  unsigned char: "unsigned char",          \
             char: "char",                     signed char: "signed char",            \
        short int: "short int",         unsigned short int: "unsigned short int",     \
              int: "int",                     unsigned int: "unsigned int",           \
         long int: "long int",           unsigned long int: "unsigned long int",      \
    long long int: "long long int", unsigned long long int: "unsigned long long int", \
            float: "float",                         double: "double",                 \
      long double: "long double",                   char *: "pointer to char",        \
           void *: "pointer to void",                int *: "pointer to int",         \
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
	uintmax_t _expr1 = (expr1); \
	uintmax_t _expr2 = (expr2); \
	if (_expr1 != _expr2) { \
		ERROR("Expression: %s == %s is false: %juu/%jdd != %juu/%jdd", \
				expr1str, expr2str, _expr1, (intmax_t)_expr1, _expr2, (intmax_t)_expr2); \
		test_failed = 1; \
	} else { \
		LOG("%s == %s", expr1str, expr2str); \
	} \
} while(0);

#define TEST_EQ(expr1, expr2)  TEST_EQ_IN(expr1, #expr1, expr2, #expr2)


#define CKDTEST(expr, value, overflow) do { \
		uintmax_t _value = ckd_value(expr); \
		uintmax_t _overflow = ckd_overflow(expr); \
		LOG("Testing expression %s -> %s", #expr, typename(ckd_value(expr))); \
		TEST_EQ_IN(_value, #expr ".value", value, #value); \
		TEST_EQ_IN(_overflow, #expr ".overflow", overflow, #overflow); \
} while(0)

#define CKDEND() exit(!test_failed ? EXIT_SUCCESS : EXIT_FAILURE)

#endif
