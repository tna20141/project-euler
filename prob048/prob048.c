#include <stdio.h>

#define N 1000
#define DIGITS_MOD 10000000000

long long last_digits(int base, int power)
{
	int i;
	long long prod = 1;

	for (i = 0; i < power; i++) {
		prod *= base;
		if (prod > DIGITS_MOD)
			prod %= DIGITS_MOD;
	}

	return prod;
}

int main()
{
	int i;
	long long sum = 0;

	for (i = 1; i < N+1; i++) {
		sum += last_digits(i, i);
		if (sum > DIGITS_MOD)
			sum %= DIGITS_MOD;
	}

	printf("Result: %lld\n", sum);

	return 0;
}
