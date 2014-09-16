#include <stdio.h>

int is_permutation(int n, int base, int num_digits)
{
	int i;
	int digit_count_n[10];
	int digit_count_base[10];

	for (i = 0; i < 10; i++) {
		digit_count_n[i] = 0;
		digit_count_base[i] = 0;
	}

	while (num_digits > 0) {
		digit_count_n[n%10]++;
		n /= 10;

		digit_count_base[base%10]++;
		base /= 10;

		num_digits--;
	}

	for (i = 0; i < 10; i++)
		if (digit_count_n[i] != digit_count_base[i])
			return 0;

	return 1;
}

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

int check(int n)
{
	int nn;

	if (!is_prime(n))
		return 0;

	nn = n+3330;

	if (!is_permutation(n, nn, 4) || !is_prime(nn))
		return 0;

	nn += 3330;

	if (!is_permutation(n, nn, 4) || !is_prime(nn))
		return 0;

	return 1;
}

int main()
{
	int i;

	for (i = 1001; i < 10000-3330-3330; i += 2)
		if (check(i) && i != 1487)
			break;

	printf("Result: %d%d%d\n", i, i+3330, i+6660);

	return 0;
}
