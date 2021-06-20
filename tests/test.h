#include <ckdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INTEST(expr, strexpr) do{ \
	printf("%s:%3d: Testing: %s\n", __FILE__, __LINE__, strexpr); \
	fflush(stdout); \
	if (!(expr)) { \
		fprintf(stderr, "%s:%3d: Expression: %s: failed\n", __FILE__, __LINE__, strexpr); \
		exit(-1); \
	} \
}while(0)

#define TEST(expr)  INTEST(expr, #expr)

#define CKDTEST(expr, value, inexact) do{ \
	printf("%s = %d\n", #expr, ckd_value(expr)); \
	INTEST((value) == ckd_value(expr),     "value(   "#expr" ) == "#value""); \
	INTEST((inexact) == ckd_inexact(expr), "inexact( "#expr" ) == "#inexact""); \
} while(0)


