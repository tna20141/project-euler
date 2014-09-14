#include <stdio.h>

#define SIZE 1001

int main()
{
	int sum = 1;
	int progress = 1;
	int i, j;
	int inc = 2;

	for (i = 0; i < SIZE/2; i++) {
		for (j = 0; j < 4; j++) {
			progress += inc;
			sum += progress;
		}
		inc += 2;
	}

	printf("Result: %d\n", sum);

	return 0;
}
