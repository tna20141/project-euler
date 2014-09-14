#include <stdio.h>

#define MAX_DIGITS 6

#define BINARY_SIZE 20

char binary[BINARY_SIZE];
int sum = 0;

int to_binary(int num)
{
	int i = 0;

	while (num > 0) {
		binary[i] = num%2;
		num >>= 1;
		i++;
	}
	binary[i] = -1;
	return i;
}

int is_binary_palindromic(int num)
{
	int len = to_binary(num);
	int i;

	for (i = 0; i < len >> 1; i++)
		if (binary[i] != binary[len-1-i])
			return 0;
	return 1;
}

int reverse(int num, int num_digits)
{
	int res = 0;
	int digit;

	while (num > 0) {
		digit = num%10;
		res *= 10;
		res += digit;
		num /= 10;
		num_digits--;
	}

	for (digit = 0; digit < num_digits; digit++)
		res *= 10;

	return res;
}

void __find_palindromic_odd(int num_digits)
{
	int bound = 1;
	int i, j;
	int revs;
	int palin;
	int tmp;

	for (i = 0; i < num_digits; i++)
		bound *= 10;

	for (i = 1; i < bound; i++) {
		if (i%10 == 0)
			continue;
		palin = i+reverse(i, num_digits)*(bound*10);
		for (j = 0; j < 10; j++) {
			tmp = palin + j*bound;
			if (is_binary_palindromic(tmp))
				sum += tmp;
		}
	}
}

void __find_palindromic_even(int num_digits)
{
	int bound = 1;
	int i;
	int palin;

	for (i = 0; i < num_digits; i++)
		bound *= 10;

	for (i = 1; i < bound; i++) {
		if (i%10 == 0)
			continue;
		palin = i+reverse(i, num_digits)*bound;
		if (is_binary_palindromic(palin))
			sum += palin;
	}
}

void find_palindromic(int num_digits)
{
	if (num_digits == 1) {
		sum += 1+3+5+7+9;
		return;
	}
	if (num_digits%2 == 0)
		__find_palindromic_even(num_digits >> 1);
	else
		__find_palindromic_odd(num_digits >> 1);
}

int main()
{
	int i;

	for (i = 1; i < MAX_DIGITS+1; i++)
		find_palindromic(i);

	printf("Result: %d\n", sum);

	return 0;
}
