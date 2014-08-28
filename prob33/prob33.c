#include <stdio.h>

int numerator = 1;
int denominator = 1;

void check(int n1, int d1, int n2, int d2)
{
	if (n1 >= d1)
		return;

	if (n1*d2 == n2*d1) {
		numerator *= n2;
		denominator *= d2;
	}
}

void shrink_prod()
{
	int n = numerator;
	int d = denominator;
	int tmp;

	while (n > 0) {
		tmp = n;
		n = d%n;
		d = tmp;
	}

	denominator /= d;
}

int main()
{
	int i, j;
	int tens, units;

	for (i = 11; i < 99; i++) {
		if (i%10 == 0)
			continue;

		tens = i/10;
		units = i%10;

		for (j = i+1; j < (tens+1)*10; j++)
			check(i, j, units, j%10);

		for (j = i+10; j < 100; j += 10)
			check(i, j, tens, j/10);

		for (j = tens*11; j < 100; j+= 10)
			check(i, j, units, j/10);

		if (units < tens)
			continue;

		for (j = units*10+1; j < (units+1)*10; j++)
			check(i, j, tens, j%10);
	}

	shrink_prod();
	printf("Result: %d\n", denominator);

	return 0;
}
