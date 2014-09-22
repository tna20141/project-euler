#include <stdio.h>

int num_exceeds(int n, int *k, long long *last_factorial,
		long long *last_product)
{
	int i;
	long long val;

	*last_product *= (long long)n;
	*last_product /= (long long)(n-*k);
	val = *last_product / *last_factorial;

	while (val > 1000000) {
		*last_factorial /= (long long)*k;
		*last_product /= (long long)(n-*k+1);
		val = *last_product / *last_factorial;
		(*k)--;
	}

	return n-((*k)<<1)-1;
}

int main()
{
	int n;
	long long last_factorial, last_product;
	int k;
	int count;
	int this;

	k = 9;
	last_factorial = 1;
	for (n = 2; n < 10; n++)
		last_factorial *= n;

	last_product = 1;
	for (n = 15; n < 24; n++)
		last_product *= n;

	count = 4;

	for (n = 24; n < 101; n++)
		count += num_exceeds(n, &k, &last_factorial, &last_product);

	printf("Result: %d\n", count);

	return 0;
}
