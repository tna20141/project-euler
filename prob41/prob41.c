#include <stdio.h>

int max_pandigital_prime = 2;

int is_prime(int num)
{
	int i = 2;

	if (num < 2)
		return 0;

	while (i*i < num) {
		if (num%i == 0)
			return 0;
		i++;
	}
	return 1;
}

void check(int *digits, int count)
{
	int i;
	int num = digits[count-1];
	int factor = 1;

	for (i = count-2; i > -1; i--) {
		factor *= 10;
		num += factor*digits[i];
	}

	if (is_prime(num))
		if (max_pandigital_prime < num)
			max_pandigital_prime = num;
}

void __permute_and_check(int *digits, int start, int end)
{
	int i, tmp;

	if (start == end-1) {
		check(digits, end);
		return;
	}

	__permute_and_check(digits, start+1, end);
	for (i = start+1; i < end; i++) {
		tmp = digits[start];
		digits[start] = digits[i];
		digits[i] = tmp;
		__permute_and_check(digits, start+1, end);
	}

	tmp = digits[start];
	for (i = start; i < end-1; i++)
		digits[i] = digits[i+1];
	digits[i] = tmp;
}

void permute_and_check(int *digits, int size)
{
	__permute_and_check(digits, 0, size);
}

int main()
{
	int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;

	for (i = 1; i < 10; i++)
		permute_and_check(digits, i);

	printf("Result: %d\n", max_pandigital_prime);

	return 0;
}
