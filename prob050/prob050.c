#include <stdio.h>

#define BOUND 1000000
#define SQUARES_CACHE_SIZE 1000
#define PRIMES_SIZE 1000000

int primes[PRIMES_SIZE];
int num_primes = 0;
int squares_cache[SQUARES_CACHE_SIZE];
int sum_cache[PRIMES_SIZE];
int max_sequence = 6;
int max_prime = 41;

int squares(int n)
{
	if (squares_cache[n] == 0)
		squares_cache[n] = n*n;

	return squares_cache[n];
}

int is_prime(int n)
{
	int i = 2;

	while (squares(i) <= n) {
		if (n%i == 0)
			return 0;
		i++;
	}

	return 1;
}

void find_primes()
{
	int n = 3;
	int i = 1;

	primes[0] = 2;
	while (n < BOUND) {
		if (is_prime(n)) {
			primes[i] = n;
			i++;
		}

		n += 2;
	}

	num_primes = i;
}

void add_primes()
{
	int i;

	sum_cache[0] = 2;
	for (i = 0; i < PRIMES_SIZE-1; i++)
		sum_cache[i+1] = sum_cache[i]+primes[i+1];
}

inline int get_sum(int start, int end)
{
	int *p;

	if (start == 0)
		return sum_cache[end];
	return sum_cache[end]-sum_cache[start-1];
}

int find_longest_sequence(int n, int bound)
{
	int i, j;
	int sum;
	int max = 0;

	for (i = 0; primes[i] < bound; i++) {
		sum = 0;
		j = 1;
		while (sum < n) {
			sum = get_sum(i, j);
			j++;
		}

		if (sum == n)
			if (max < j-i)
				max = j-i;
	}

	return max;
}

void init()
{
	int i, j;

	for (i = 0; i < SQUARES_CACHE_SIZE; i++)
		squares_cache[i] = 0;

	find_primes();
	add_primes();
}

int main()
{
	int i;
	int sequence;

	init();

	for (i = 0; i < num_primes; i++) {
		sequence = find_longest_sequence(primes[i], primes[i]/max_sequence);
		if (max_sequence < sequence) {
			max_sequence = sequence;
			max_prime = primes[i];
		}
	}

	printf("Result: %d\n", max_prime);

	return 0;
}
