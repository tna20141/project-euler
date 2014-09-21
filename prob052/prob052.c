#include <stdio.h>

#define POWERS_OF_TEN_SIZE 40

long long pot[POWERS_OF_TEN_SIZE];

int init()
{
	int i;

	pot[0] = 1;
	for (i = 1; i < POWERS_OF_TEN_SIZE; i++)
		pot[i] = pot[i-1]*10;
}

int compare_digits(long long num, int *base_digits)
{
	int digits[10];
	int i;

	for (i = 0; i < 10; i++)
		digits[i] = 0;

	while (num > 0) {
		digits[num%10]++;
		num /= 10;
	}

	for (i = 0; i < 10; i++)
		if (digits[i] != base_digits[i])
			return 0;

	return 1;
}

int check(long long num)
{
	int base_digits[10];
	int i;
	int tmp = num;

	for (i = 0; i < 10; i++)
		base_digits[i] = 0;

	while (tmp > 0) {
		base_digits[tmp%10]++;
		tmp /= 10;
	}

	for (i = 2; i < 7; i++)
		if (!compare_digits(i*num, base_digits))
			return 0;

	return 1;
}

int main()
{
	int num_digits = 1;
	long long num, bound;
	int not_found = 1;
	int i;

	init();

	while (not_found) {
		num = pot[num_digits+1];
		bound = num<<1;
		for ( ; num < bound; num++)
			if (check(num)) {
				not_found = 0;
				break;
			}

		num_digits++;
	}

	printf("Result: %lld\n", num);

	return 0;
}
