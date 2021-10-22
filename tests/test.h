#ifndef TESTS_TEST_H_
#define TESTS_TEST_H_

#include <ckdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static bool test_failed = 0;

static const char RED[] = "\E[1m\E[31m";
static const char RESET[] = "\E(B\E[m";

#define FILENAME() (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define INTEST(expr, strexpr) do{ \
	printf("%s:%3d: Testing: %s\n", FILENAME(), __LINE__, strexpr); \
	fflush(stdout); \
	if (!(expr)) { \
		fprintf(stderr, "%s:%3d: %sExpression: %s: failed%s\n", FILENAME(), __LINE__, \
				RED, strexpr, RESET); \
		test_failed = 1; \
	} \
}while(0)

#define TEST(expr)  INTEST(expr, #expr)

#define CKDTEST(expr, value, overflow) do{ \
	printf("%s:%3d: %s = %zuu%zdd ?= %zuu%zdd\n", FILENAME(), __LINE__, #expr, \
			(uintmax_t)ckd_value(expr), (intmax_t)ckd_value(expr), \
			(uintmax_t)value, (intmax_t)value); \
	INTEST((value) == ckd_value(expr),     "value(   "#expr" ) == "#value""); \
	INTEST((overflow) == ckd_overflow(expr), "overflow( "#expr" ) == "#overflow""); \
} while(0)

#define CKDEND() exit(!test_failed ? EXIT_SUCCESS : EXIT_FAILURE)

#endif
