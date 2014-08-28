#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define DIGITS 6

#define PRIME_DIGIT_NUM 4

int prime_digits[PRIME_DIGIT_NUM] = {1, 3, 7, 9};
int count = 0;
int check_buf[100];

int __is_prime(int n)
{
	int i;
	int s;

	if (n < 2)
		return 0;

	s = (int)(floor(sqrt((double)n)));
	for (i = 2; i < s; i++)
		if (n%i == 0)
			return 0;

	return 1;
}

int str2int(int *a, int size)
{
	int i;
	int factor = 1;
	int num = 0;

	for (i = 0; i < size; i++) {
		num += a[i]*factor;
		factor *= 10;
	}

	return num;
}

void check_circular_prime(int *a, int size)
{
	int i, j, tmp;
	int num;

	for (i = 0; i < size; i++) {
		num = str2int(a, size);
		if (!__is_prime(num))
			return;

		tmp = a[0];
		for (j = 0; j < size-1; j++)
			a[j] = a[j+1];
		a[j] = tmp;
	}
	count++;
}

void permute_and_check(int *a, int start, int end)
{
	int i, tmp;
	int old_end = a[end-1];

	if (end-start == 1) {
		for (i = 0; i < end; i++)
			check_buf[i] = a[i];
		check_circular_prime(check_buf, end);
		return;
	}

	permute_and_check(a, start+1, end);
	for (i = start+1; i < end; i++) {
		if (a[start] == a[i])
			continue;
		tmp = a[start];
		a[start] = a[i];
		a[i] = tmp;
		permute_and_check(a, start+1, end);
	}

	for (i = start; i < end-1; i++)
		a[i] = a[i+1];
	a[i] = old_end;
}

void get_and_check(int *a, int start_prime, int start_buf, int num)
{
	int i;

	if (num == start_buf) {
		permute_and_check(a, 0, num);
		return;
	}

	for (i = start_prime; i < PRIME_DIGIT_NUM; i++) {
		a[start_buf] = prime_digits[i];
		get_and_check(a, i, start_buf+1, num);
	}
}

void find_circular_primes(int num)
{
	int *digits;
	int res;

	if (num == 1) {
		count += 4;
		return;
	}

	digits = (int *)malloc(num*sizeof(int));

	get_and_check(digits, 0, 0, num);

	free(digits);
}

int main()
{
	int i;

	for (i = 1; i < DIGITS+1; i++)
		find_circular_primes(i);

	printf("Result: %d\n", count);

	return 0;
}
