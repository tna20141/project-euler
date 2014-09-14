#include <stdio.h>

#define MAX 28124
#define MIN 12

int inline __is_abundant(int n)
{
	int sum = 0;
	int i;

	for (i = 1; i < n; i++)
		if (n%i == 0)
			sum += i;

	if (sum > n)
		return 1;
	else
		return 0;
}

void find_abundants(int *num, int min, int max)
{
	int i;
	int prev = 0;

	for (i = min; i < max; i++)
		if (__is_abundant(i)) {
			num[prev] = i;
			prev = i;
		}

	num[prev] = max+1;
}

void find_sum_two_abundants(int *sum_abs, int *num, int min, int max_search)
{
	int max = min+max_search;
	int i, j;

	for (i = num[0]; i < max_search; ) {
		for (j = i; j < max-i; ) {
			sum_abs[j+i] = 1;
			j = num[j];
		}
		i = num[i];
	}
}

unsigned int cal_sum(int *sum_abs, int max)
{
	int i;
	unsigned int sum = 0;

	for (i = 1; i < max; i++)
		if (!sum_abs[i])
			sum += i;

	return sum;
}

int main()
{
	int num[MAX-MIN];
	int sum_abundants[MAX];
	unsigned int sum = 0;
	int i;

	for (i = 0; i < MAX; i++)
		sum_abundants[i] = 0;

	find_abundants(num, MIN, MAX-MIN);

	find_sum_two_abundants(sum_abundants, num, MIN, MAX-MIN);

	sum = cal_sum(sum_abundants, MAX);

	printf("Result: %u\n", sum);

	return 0;
}
