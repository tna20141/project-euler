#include <stdio.h>

#define DIGITS_SIZE 20

int is_palindromic(int num)
{
	int digits[DIGITS_SIZE];
	int size = 0;
	int i;

	while (num > 0) {
		digits[size] = num%10;
		num /= 10;
		size++;
	}

	for (i = 0; i < size; i++)
		if (digits[i] != digits[size-i-1])
			return 0;

	return 1;
}

int main()
{
	int a, b, product;
	int max = 9009;

	for (a = 100; a < 1000; a++)
		for (b = 100; b < 1000; b++) {
			product = a*b;
			if (is_palindromic(product) && max < product)
				max = product;
		}

	printf("Result: %d\n", max);

	return 0;
}
