#include <stdio.h>

#define NTH 10001

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

int main()
{
	int count = 1;
	int n = 3;

	while (count < NTH) {
		if (is_prime(n))
			count++;
		n += 2;
	}

	printf("Result: %d\n", n-2);

	return 0;
}
