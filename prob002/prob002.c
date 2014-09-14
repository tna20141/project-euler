#include <stdio.h>

#define BOUND 4000000

int main()
{
	int f1 = 1, f2 = 2;
	int tmp;
	int sum = 2;

	while (1) {
		tmp = f2;
		f2 = f2+f1;
		f1 = tmp;

		if (f2 > BOUND)
			break;

		if (f2%2 == 0)
			sum += f2;
	}

	printf("Result: %d\n", sum);

	return 0;
}
