#include <stdio.h>

#define BOUND 10000

int max_pandigital = 0;

int concatenate(int a, int b)
{
	int factor = 1;

	while (b >= factor)
		factor *= 10;
	return factor*a+b;
}

int is_pandigital(int n)
{
	int digits[10];
	int digit;
	int i;

	for (i = 1; i < 10; i++)
		digits[i] = 0;

	while (n > 0) {
		digit = n%10;
		if (digits[digit])
			return 0;
		digits[digit] = 1;
		n /= 10;
	}

	for (i = 1; i < 10; i++)
		if (!digits[i])
			return 0;

	return 1;
}
		
int check(int num)
{
	int n = 1;
	int concatenated = num;
	int new_concat;
	int prod;

	while (1) {
		n++;
		prod = n*num;
		new_concat = concatenate(concatenated, prod);
		if (new_concat > 987654321)
			break;

		concatenated = new_concat;
		if (concatenated > 99999999) {
			if (is_pandigital(concatenated))
				if (max_pandigital < concatenated)
					max_pandigital = concatenated;
			break;
		}
	}
}

int main()
{
	int i;

	for (i = 1; i < BOUND; i++)
		check(i);

	printf("Result: %d\n", max_pandigital);

	return 0;
}
