#include <stdio.h>

#define PENTAGONAL_SERIES_SIZE 4000000

long long pentagonal_series[PENTAGONAL_SERIES_SIZE];

inline long long __pentagonal(int n)
{
	return (long long)n*(3*(long long)n-1)/2;
}

inline long long pentagonal(int n)
{
	if (!pentagonal_series[n])
		pentagonal_series[n] = __pentagonal(n);

	return pentagonal_series[n];
}

int is_pentagonal(long long num)
{
	int i = 1;

	while (1) {
		if (pentagonal(i) >= num)
			break;
		i++;
	}

	if (pentagonal(i) == num)
		return 1;

	return 0;
}

long long find_first_pair(int *a, int *b)
{
	int i = 1, j;

	while (1) {
		for (j = 1; j < i; j++)
			if (is_pentagonal(pentagonal(i)+pentagonal(j)) &&
					is_pentagonal(pentagonal(i)-pentagonal(j))) {
				*a = j;
				*b = i;
				return pentagonal(i)-pentagonal(j);
			}
		i++;
	}
	return -1;
}

int find_minimized_pair(int start, long long diff)
{
	int i = start;
	int j;
	long long tmp_diff;

	while(pentagonal(i)-pentagonal(i-1) <= diff) {
		for (j = i-1; j > 0; j--) {
			tmp_diff = pentagonal(i)-pentagonal(j);
			if (tmp_diff > diff)
				break;
			if (is_pentagonal(pentagonal(i)+pentagonal(j)) &&
					is_pentagonal(tmp_diff)) {
				if (diff > tmp_diff)
					diff = tmp_diff;
			}
		}
		i++;
	}
	return diff;
}

void init_pentagonal_series()
{
	int i;

	for (i = 0; i < PENTAGONAL_SERIES_SIZE; i++)
		pentagonal_series[i] = 0;
}

int main()
{
	int a, b;
	long long first_diff;

	init_pentagonal_series();

	first_diff = find_first_pair(&a, &b);

	first_diff = find_minimized_pair(b, first_diff);

	printf("Result: %lld\n", first_diff);

	return 0;
}
