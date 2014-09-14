#include <stdio.h>

int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
long long sum = 0;

long long to_number(int start, int end)
{
	int i;
	long long num = 0;
	int factor = 1;

	for (i = end; i > start-1; i--) {
		num += (long long)factor*(long long)digits[i];
		factor *= 10;
	}

	return num;
}

int check_prop()
{
	if (digits[0] == 0)
		return 0;

	if (to_number(1, 3)%2 != 0)
		return 0;

	if (to_number(2, 4)%3 != 0)
		return 0;

	if (to_number(3, 5)%5 != 0)
		return 0;

	if (to_number(4, 6)%7 != 0)
		return 0;

	if (to_number(5, 7)%11 != 0)
		return 0;

	if (to_number(6, 8)%13 != 0)
		return 0;

	if (to_number(7, 9)%17 != 0)
		return 0;

	return 1;
}

void permute_and_check(int start, int end)
{
	int i, tmp;

	if (start == end-1) {
		if (check_prop())
			sum += to_number(0, 9);
		return;
	}

	permute_and_check(start+1, end);
	for (i = start+1; i < end; i++) {
		tmp = digits[start];
		digits[start] = digits[i];
		digits[i] = tmp;
		permute_and_check(start+1, end);
	}

	tmp = digits[start];
	for (i = start; i < end-1; i++)
		digits[i] = digits[i+1];
	digits[end-1] = tmp;
}

int main()
{
	permute_and_check(0, 10);

	printf("Result: %lld\n", sum);

	return 0;
}
