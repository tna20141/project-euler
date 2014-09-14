#include <stdio.h>

#define BOUND 1000

int main()
{
	int sum = 0;
	int i;

	for (i = 1; i < BOUND; i++)
		if (i%3 == 0 || i%5 == 0)
			sum += i;

	printf("Result: %d\n", sum);

	return 0;
}
