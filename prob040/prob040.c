#include <stdio.h>

#define LAST 1000000

int get_digit(int num, int pos)
{
	int i;
	int limit = 1;

	for (i = 0; i < pos; i++)
		limit *= 10;

	return (num/limit)%10;
}

int main()
{
	int num;
	int power = 1;
	int n = 1;
	int prod = 1;
	int advance = 0;
	int pos = 0;

	for (num = 1; n <= LAST; num++) {
		if (num >= power) {
			power *= 10;
			advance++;
		}

		pos += advance;
		if (pos >= n) {
			prod *= get_digit(num, pos-n);
			n *= 10;
		}
	}

	printf("Result: %d\n", prod);

	return 0;
}
