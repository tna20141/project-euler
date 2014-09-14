#include <stdio.h>

#define NUM 600851475143
int main()
{
	long long i = 3;
	long long n = NUM;

	while (i < n) {
		while (n%i == 0)
			n /= i;
		i += 2;
	}

	printf("Result: %lld\n", n);

	return 0;
}
