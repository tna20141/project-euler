#include <stdio.h>
#include <string.h>

#define NTH 1000000
#define N 10

int count = 0;
char res[N+1];

inline void swap(char *a, char *b)
{
	char c;

	c = *a;
	*a = *b;
	*b = c;
}

int permute(char *num, int start, int end)
{
	int i;
	char c;

	if (end-start == 1) {
		count++;
		if (count == NTH) {
			strncpy(res, num, N);
			/* stop permuting */
			return 1;
		}
		return 0;
	}

	if (permute(num, start+1, end))
		return 1;

	for (i = start+1; i < end; i++) {
		swap(&num[start], &num[i]);
		if (permute(num, start+1, end))
			return 1;
	}

	c = num[start];
	for (i = start; i < end-1; i++)
		num[i] = num[i+1];
	num[end-1] = c;

	return 0;
}

int main()
{
	char num[N+1];
	int i;

	for (i = 0; i < N; i++)
		num[i] = '0'+i;
	num[N] = '\0';

	i = permute(num, 0, N);

	if (i)
		printf("Result: %s\n", res);
	else
		printf("Problem not solved. Check the data again.\n");

	return 0;
}
