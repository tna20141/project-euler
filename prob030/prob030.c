#include <stdio.h>

#define BOUND 3000000

int power(int base, int exponent)
{
	int i;
	int pow = 1;

	for (i = 0; i < exponent; i++)
		pow *= base;

	return pow;
}

int main()
{
	int res = 0;
	int sum;
	int i, tmp, digit;

	for (i = 2; i < BOUND; i++) {
		tmp = i;
		sum = 0;
		while (tmp > 0) {
			digit = tmp%10;
			sum += power(digit, 5);
			tmp = tmp/10;
		}
		if (i == sum)
			res += i;
	}

	printf("Result: %d\n", res);

	return 0;
}

