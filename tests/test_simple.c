#include <ckdint.h>
#include <stdlib.h>
int main() {
	int a;
	if (ckd_add(&a, 1, 1) != 0) return EXIT_FAILURE;
	if (a != 2) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
