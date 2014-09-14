#include <stdio.h>

#define SUM 1000

int is_triplet(int a, int b, int c)
{
	return a*a+b*b == c*c;
}

int main()
{
	int a, b;
	int prod;

	for (a = 1; a <= SUM/3; a++)
		for (b = a+1; b <= (SUM-a)/2; b++)
				if (is_triplet(a, b, SUM-a-b)) {
					prod = a*b*(SUM-a-b);
					goto result;
				}

result:
	printf("Result: %d\n", prod);

	return 0;
}
