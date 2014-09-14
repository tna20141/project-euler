#include <stdio.h>

#define N 20

int gcd(long long a, long long b)
{
	int tmp;

	while (b) {
		tmp = b;
		b = a%b;
		a = tmp;
	}

	return a;
}

int lcm(long long a, long long b)
{
	return a*b/gcd(a, b);
}

int main()
{
	long long res = 1;
	int i;

	for (i = 1; i < N+1; i++)
		res = lcm(res, (long long)i);

	printf("Result: %lld\n", res);

	return 0;
}
