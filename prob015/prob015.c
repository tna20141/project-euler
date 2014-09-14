#include <stdio.h>

#define SIZE 20

int main()
{
	unsigned int i;
	unsigned long long divisor = 1;
	unsigned long long result = 1;

	for (i = 1; i < SIZE+1; i++) {
		result *= SIZE+i;
		if (result%i == 0)
			result /= i;
		else
			divisor *= i;
	}

	result /= divisor;

	printf("Result: %llu\n", result);

	return 0;
}
