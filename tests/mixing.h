#include "test.h"

#define T(A, B) do { \
	TEST_COP3(ullong, add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(llong,  add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(ulong,  add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(long,   add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(uint,   add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(int,    add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(ushrt,  add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(shrt,   add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(uchar,  add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(schar,  add,     (A)2, (B)3, 5, 0); \
	TEST_COP3(char,   add,     (A)2, (B)3, 5, 0); \
	\
	TEST_COP3(ullong, sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(llong,  sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(ulong,  sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(long,   sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(uint,   sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(int,    sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(ushrt,  sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(shrt,   sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(uchar,  sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(schar,  sub,     (A)6, (B)4, 2, 0); \
	TEST_COP3(char,   sub,     (A)6, (B)4, 2, 0); \
	\
	TEST_COP3(ullong, mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(llong,  mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(ulong,  mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(long,   mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(uint,   mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(int,    mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(ushrt,  mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(shrt,   mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(uchar,  mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(schar,  mul,     (A)2, (B)3, 6, 0); \
	TEST_COP3(char,   mul,     (A)2, (B)3, 6, 0); \
} while(0)
