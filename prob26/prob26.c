#include <stdio.h>

#define N 1000
#define CHECK_DIGITS 3
#define BUF_SIZE (N+CHECK_DIGITS)

inline void fraction(int denominator, char *str);
int count_cycle_digits(char *str);

int main()
{
	int i;
	int max = 0;
	int res = 2;
	int tmp;
	char buf[BUF_SIZE];

	for (i = 2; i < N; i++) {
		fraction(i, buf);
		tmp = count_cycle_digits(buf);
		if (tmp > max) {
			max = tmp;
			res = i;
		}
	}

	printf("Result: %d, cycle = %d\n", res, max);

	return 0;
}

inline void fraction(int denominator, char *str)
{
	int dividend = 10;
	int quotient, remainder;
	int i;

	for (i = 0; i < BUF_SIZE; i++) {
		quotient = dividend/denominator;
		remainder = dividend%denominator;
		str[i] = quotient;
		dividend = remainder*10;
	}
}

int count_cycle_digits(char *str)
{
	int appeared[N];
	int i, j;
	int index, factor;

	for (i = 0; i < N; i++)
		appeared[i] = -1;
	
	for (i = 0; i < N+1; i++) {
		factor = 1;
		index = 0;
		for (j = i+CHECK_DIGITS-1; j > i-1; j--) {
			index += factor*str[j];
			factor *= 10;
		}

		if (appeared[index] != -1)
			return i-appeared[index];
		else
			appeared[index] = i;
	}
	return 0;
}
