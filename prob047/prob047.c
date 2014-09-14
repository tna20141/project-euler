#include <stdio.h>

#define PRIMES_SIZE 20000

int primes[PRIMES_SIZE];

int is_prime(int n)
{
	int i = 2;

	while (i*i <= n) {
		if (n%i == 0)
			return 0;
		i++;
	}

	return 1;
}

void fill_primes()
{
	int i = 3;
	int count = 1;

	primes[0] = 2;
	while (count < PRIMES_SIZE) {
		if (is_prime(i)) {
			primes[count] = i;
			count++;
		}
		i += 2;
	}
}

int has_four_prime_factors(int num)
{
	int i = 0;
	int count = 0;

	while (num > 1) {
		if (num%primes[i] == 0) {
			count++;
			if (count == 4)
				return 1;
			do
				num /= primes[i];
			while (num%primes[i] == 0);
		}
		i++;
	}

	return 0;
}

int find_first_four()
{
	int i = 4;
	int count = 0;

	while (1) {
		if (has_four_prime_factors(i)) {
			count++;
			if (count == 4)
				return i-3;
		} else
			count = 0;
		i++;
	}

	return -1;
}

int main()
{
	int res;

	fill_primes();

	res = find_first_four();

	printf("Result: %d\n", res);

	return 0;
}
