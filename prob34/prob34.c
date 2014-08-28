#include <stdio.h>

#define BOUND 2200000

int factorial[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int is_curious(int n)
{
	int sum = 0;
	int _n = n;
	int digit;

	while (_n > 0) {
		digit = _n%10;
		_n /= 10;

		sum += factorial[digit];
	}

	if (sum == n)
		return 1;
	else
		return 0;
}

int main()
{
	int sum = 0;
	int i;

	for (i = 10; i < BOUND; i++)
		if (is_curious(i))
			sum += i;

	printf("Result: %d\n", sum);

	return 0;
}
