#include <stdio.h>

#define TWICE_SQUARES_SIZE 10000
#define PRIMES_SIZE 10000

int twice_squares[TWICE_SQUARES_SIZE];
int primes[PRIMES_SIZE];
int num_primes;

int twice_square(int n)
{
	if (twice_squares[n] == 0)
		twice_squares[n] = (n*n)<<1;

	return twice_squares[n];
}

int check_cg(int n)
{
	int i, j;
	int sum;

	for (i = 0; i < num_primes; i++) {
		j = 1;
		do {
			sum = primes[i]+twice_square(j);
			if (sum == n)
				return 1;
			j++;
		} while (sum < n);
	}

	return 0;
}

int check_prime(int n)
{
	int i = 2;

	while (i*i <= n) {
		if (n%i == 0)
			return 0;
		i++;
	}

	primes[num_primes] = n;
	num_primes++;
	return 1;
}

void init_twice_squares()
{
	int i;

	for (i = 0; i < TWICE_SQUARES_SIZE; i++)
		twice_squares[i] = 0;
}

void init_primes()
{
	primes[0] = 2;
	primes[1] = 3;
	num_primes = 2;
}

int main()
{
	int i;

	i = 5;
	while (1) {
		if (!check_prime(i))
			if (!check_cg(i))
				break;
		i += 2;
	}

	printf("Result: %d\n", i);

	return 0;
}
