#include <ckdint.h>
int main() {
	{
		int a;
		bool o = ckd_add(&a, INT_MIN, -1);
		if (!(o == 1 && a == INT_MAX)) return -__LINE__;
	}
	{
		signed char a;
		bool o = ckd_add(&a, INT_MIN, 0);
		if (!(o == 1 && a == (signed char)a)) return -__LINE__;
	}
	return 0;
}
