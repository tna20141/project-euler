#include <stdio.h>

#define P 1000

inline int is_right_angle(int a, int b, int c)
{
	return a*a+b*b == c*c;
}

int count_solutions(int p)
{
	int i, j;
	int count = 0;

	for (i = 1; i < p/3+1; i++)
		for (j = i; j < (p-i)/2+1; j++)
			if (is_right_angle(i, j, p-i-j))
				count++;

	return count;
}

int main()
{
	int max = 0;
	int max_p = 0;
	int count;
	int i;

	for (i = 1; i <= P; i++) {
		count = count_solutions(i);
		if (max < count) {
			max = count;
			max_p = i;
		}
	}

	printf("Result: %d\n", max_p);

	return 0;
}
