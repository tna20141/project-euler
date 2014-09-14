#include <stdio.h>

#define BOUND 2000000
#define SQUARES_SIZE 2000

int squares[SQUARES_SIZE];

static int square(int n)
{
	if (squares[n] == 0)
		squares[n] = n*n;

	return squares[n];
}

void init_squares()
{
	int i;

	for (i = 0; i < SQUARES_SIZE; i++)
		squares[i] = 0;
}

int is_prime(int n)
{
	int i = 2;

	while (square(i) <= n) {
		if (n%i == 0)
			return 0;
		i++;
	}

	return 1;
}

int main()
{
	int i;
	long long sum = 2;

	init_squares();

	for (i = 3; i < BOUND; i += 2)
		if (is_prime(i))
			sum += (long long)i;

	printf("Result: %lld\n", sum);

	return 0;
}
