#include <ckdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned error = 0;

// Single test case - do operation on a and b using the function defined in TIN
#define t(a, b)  \
    do{ \
        t2(#a, a, #b, b); \
        if ((unsigned long long)a != (unsigned long long)b) t2(#b, b, #a, a); \
    } while(0)

// Define supet testing function that defines a function that calls two functions that calculate overflow.
#define TIN(FUNC1, FUNC2, OP, X, Y, Z) \
void super_test() { \
    const char *func1str = #FUNC1"("#X", "#Y", "#Z")"; \
    const char *func2str = #FUNC2; \
    const char *opstr = #OP; \
    fprintf(stderr, "%s vs %s\n", func1str, func2str); \
    void t2(const char *astr, unsigned long long int a, const char *bstr, unsigned long long b) { \
        bool func1(X a, Y b, Z *c) { \
            return FUNC1(a, b, c); \
        } \
        bool func2(X a, Y b, Z *c) { \
            return FUNC2(a, b, (void*)c); \
        } \
        unsigned long long c, c2; \
        const bool o = func1(a, b, (void*)&c); \
        const bool o2 = func2(a, b, (void*)&c2); \
        const bool ok = c == c2 && o == o2; \
        if (!ok) { \
			fprintf(stderr, "%s %s %s ->\t%llu/%lld %s %llu/%lld \t|| %d %s %d\n", \
				astr, opstr, bstr, \
				c, c, c == c2 ? "OK" : "ERROR", c2, c2, \
				o, o == o2 ? "OK" : "ERROR", o2); \
			error++; \
		} \
    } \
    t(-2, 1); \
    t(0, -2); \
    t(-2, 2); \
    t(-1, 1); \
    t(1, 1); \
    t(LLONG_MAX, 1); \
    t(LLONG_MIN, 1); \
    t(LLONG_MIN, LLONG_MIN); \
    t(LLONG_MIN, LLONG_MAX); \
    t(LLONG_MAX, LLONG_MIN); \
    t(LLONG_MAX, LLONG_MAX); \
    t(ULLONG_MAX, 0); \
    t(ULLONG_MAX, 1); \
    t(ULLONG_MAX, LLONG_MAX); \
    t(ULLONG_MAX, LLONG_MIN); \
    t(ULLONG_MAX, ULLONG_MAX); \
    t(0, ULLONG_MAX); \
    t(-1, -1); \
    t(-1, -2); \
    t(-1, -3); \
    t(-1, LLONG_MIN); \
}

// Run tests for specific type cases
#define T(TYPE, OP, X,x, Y,y, Z,z) \
    do{ \
		TIN(__builtin_##OP##_overflow, _ckd_##OP##_##x##y##z##_##TYPE, OP, X, Y, Z); \
		super_test(); \
	} while(0)

// Run tests for each operation
#define CASE1(TYPE, X,x, Y,y, Z,z) \
    T(TYPE, add, X,x, Y,y, Z,z); \
    T(TYPE, sub, X,x, Y,y, Z,z); \
    T(TYPE, mul, X,x, Y,y, Z,z);

// The main entrypoin
#define CASE(X,x, Y,y, Z,z) \
    CASE1(llong, X,x, Y,y, Z,z);

int main() {
#if !CKD_NOGNU_SOURCE || !__GNUC__ || __clang__ || __INTEL_COMPILER
	// This test is only meaningfull when using non-gnu.
#else
#define S long long
#define U unsigned long long
    CASE(S,s, S,s, S,s);
    CASE(S,s, S,s, U,u);
    CASE(S,s, U,u, S,s);
    CASE(S,s, U,u, U,u);
    CASE(U,u, S,s, S,s);
    CASE(U,u, S,s, U,u);
    CASE(U,u, U,u, S,s);
    CASE(U,u, U,u, U,u);
#endif
	if (error) {
		fprintf(stderr, "Got %u errors\n", error);
	}
	return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
