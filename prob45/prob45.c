#include <stdio.h>
#include <math.h>

#define START 286

int is_hexagonal(long long num)
{
	double test;

	test = (sqrt((double)(num<<3)+1)+1)/4;

	return test == floor(test);
}

int is_pentagonal(long long num)
{
	double test;

	test = (sqrt(24*(double)num+1)+1)/6;

	return test == floor(test);
}

inline long long to_triangle(int n)
{
	return ((long long)n*((long long)n+1))>>1;
}

int main()
{
	int i = START;
	long long triangle;

	while (1) {
		triangle = to_triangle(i);
		if (is_pentagonal(triangle) && is_hexagonal(triangle))
			break;
		i++;
	}

	printf("Result: %lld\n", triangle);

	return 0;
}
