#include <stdio.h>

#define BOUND 100

int main()
{
	int i;
	int sum_of_squares = 0;
	int square_of_sum = 0;
	int diff;

	for (i = 1; i < BOUND+1; i++) {
		sum_of_squares += i*i;
		square_of_sum += i;
	}
	square_of_sum *= square_of_sum;

	diff = square_of_sum-sum_of_squares;

	printf("Result: %d\n", diff);

	return 0;
}
