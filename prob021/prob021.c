#include <stdio.h>

#define N 10000

int main()
{
	int num[N];
	int i, j;
	int sum = 0;

	num[0] = -1;
	for (i = 1; i < N; i++) {
		num[i] = 0;
		for (j = 1; j < i; j++)
			if (i%j == 0)
				num[i] += j;
	}

	for (i = 1; i < N; i++)
		if (num[i] < N && i == num[num[i]] && i != num[i])
			sum += i;

	printf("Result: %d\n", sum);

	return 0;
}
