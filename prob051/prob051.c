#include <stdio.h>

#define SQUARES_SIZE 10000
#define SAME_DIGIT_SIZE 40
#define TENS_SIZE 40
#define INCREMENTS_SIZE 100

int squares[SQUARES_SIZE];

int digit_pos[SAME_DIGIT_SIZE];
int digit_count;

int tens[TENS_SIZE];

int increments[INCREMENTS_SIZE];
int increments_size;

inline int square(int n)
{
	if (squares[n] == 0)
		squares[n] = n*n;

	return squares[n];
}

inline int __is_prime(int n)
{
	int i = 2;

	while (square(i) <= n) {
		if (n%i == 0)
			return 0;
		i++;
	}

	return 1;
}

inline int is_prime(int n)
{
	if (n < 2)
		return 0;

	return __is_prime(n);
}

void count_digits(int n, int d)
{
	int i = 0;
	int pos = 1;
	int digit;

	n /= 10;
	while (n > 0) {
		digit = n%10;
		if (digit == d) {
			digit_pos[i] = pos;
			i++;
		}

		n /= 10;
		pos++;
	}

	digit_count = i;
}

void __get_increments(int count, int sum, int start)
{
	int i;

	if (count == 0) {
		increments[increments_size] = sum;
		increments_size++;
		return;
	}

	for (i = start; i < digit_count-count+1; i++)
		__get_increments(count-1, sum+tens[digit_pos[i]], i+1);
}

void get_increments(int count)
{
	increments_size = 0;

	__get_increments(count, 0, 0);
}

int __check(int base, int increment, int count, int inval_bound)
{
	int i;
	int inval_count = 0;

	for (i = 1; i < count+1; i++) {
		if (!is_prime(base+i*increment))
			inval_count++;

		if (inval_count == inval_bound)
			return 0;
	}

	return 1;
}

int check(int base, int start_digit, int inc_digit_count)
{
	int count = 9-start_digit;
	int inval_bound = 3-start_digit;
	int increment = 0;
	int i;

	get_increments(inc_digit_count);

	for (i = 0; i < increments_size; i++)
		if (__check(base, increments[i], count, inval_bound))
			return 1;

	return 0;
}

int check_prime(int n)
{
	int i;

	count_digits(n, 0);
	for (i = 3; i < digit_count+1; i += 3)
		if (check(n, 0, i))
			return 1;

	count_digits(n, 1);
	for (i = 3; i < digit_count+1; i += 3)
		if (check(n, 1, i))
			return 1;

	return 0;
}

void init_tens()
{
	int i;

	tens[0] = 1;
	for (i = 1; i < TENS_SIZE; i++)
		tens[i] = 10*tens[i-1];
}

int main()
{
	int i = 111;

	init_tens();

	while (1) {
		if (check_prime(i))
			break;
		i += 2;
	}

	printf("Result: %d\n", i);

	return 0;
}
