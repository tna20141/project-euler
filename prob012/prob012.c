#include <stdio.h>

#define DIVISORS 500

int count_divisors(int n)
{
	int i;
	int count = 2;

	for (i = 2; i < n; i++)
		if (n%i == 0)
			count++;

	return count;
}

int count_divisors_half(int n)
{
	int i;
	int count = 1;

	for (i = 2; i < n; i += 2)
		if (n%i == 0)
			count++;

	return count;
}

int main()
{
	int i = 1;
	int last_count = 1;
	int new_count;
	int count;

	while (1) {
		if (i%2 == 1)
			new_count = count_divisors_half(i+1);
		else
			new_count = count_divisors(i+1);

		count = last_count*new_count;
		if (count > DIVISORS)
			break;

		last_count = new_count;
		i++;
	}

	printf("Result: %d\n", i*(i+1)/2);

	return 0;
}
