#include <stdio.h>

#define EXP 1000

int main()
{
	char digits[EXP];
	int i, j;
	int carry = 0;
	int len = 1;
	int sum = 0;

	digits[0] = 1;
	for (i = 1; i < EXP; i++)
	       digits[EXP] = 0;	

	for (i = 0; i < EXP; i++) {
		for (j = 0; j < len; j++) {
			digits[j] <<= 1;
			digits[j] += carry;
			carry = 0;
			if (digits[j] > 9) {
				carry = digits[j]/10;
				digits[j] %= 10;
			}
		}
		if (carry > 0) {
			digits[j] = carry;
			carry = 0;
			len++;
		}
	}

	for (i = 0; i < len; i++)
		sum += digits[i];

	printf("Results: %d\n", sum);

	return 0;
}

