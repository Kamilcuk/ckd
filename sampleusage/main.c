#include <ckdint.h>
#include <stdio.h>
#include <stdbool.h>
int main() {
	unsigned u;
	bool o = ckd_add(&u, 1, 1);
	printf("%d %u\n", o, u);
}
