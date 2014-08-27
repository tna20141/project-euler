#include <stdio.h>

struct found_prods {
	int prods[1000];
	int num;
};

struct found_prods fp;
int digits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int sum = 0;

void init_found_prods()
{
	fp.prods[0] = -1;
	fp.num = 0;
}

void insert_prod(int prod)
{
	fp.prods[fp.num] = prod;
	fp.num++;
}

int lookup_prod(int prod)
{
	int i;

	for (i = 0; i < fp.num; i++)
		if (fp.prods[i] == prod)
			return 1;

	return 0;
}

int to_num(int start, int end)
{
	int i;
	int num = 0;
	int factor = 1;

	for (i = start; i < end; i++) {
		num += factor*digits[i];
		factor *= 10;
	}

	return num;
}

int prod_valid(int prod)
{
	int digit;
	int i;
	int prod_digits[4];

	for (i = 5; i < 9; i++)
		prod_digits[i] = digits[i];

	while (prod > 0) {
		digit = prod%10;
		prod /= 10;
		for (i = 5; i < 9; i++)
			if (digit == digits[i])
				break;
void calculate_prod()
{
	int i;

	for (i = 1; i < 5; i++) {
		prod = to_num(0, i)*to_num(i, 5);
		if (prod_valid(prod))
			if (!lookup_prod(prod)) {
				insert_prod(prod);
				sum += prod;
			}
	}
}

void permute(int start)
{
	int i;

	if (start == 5) {
		calculate_prod();
		return;
	}

	for (i = start; i < 9; i++) {
		tmp = digits[start];
		digits[start] = digits[i];
		digits[i] = tmp;
		permute(start+1);
	}

	tmp = digits[start];
	for (i = start; i < 8; i++)
		digits[i] = digits[i+1];
	digits[i] = tmp;
}
