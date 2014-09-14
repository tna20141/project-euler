#include <stdio.h>
#include <malloc.h>

int multiply(char *num, int factor, int len)
{
	int i, j;
	int temp;
	int new_len = len;
	char *res = NULL;
	int carry = 0;

	res = (char *)calloc(200, sizeof(char));

	for (i = 0; i < len; i++) {
		j = i;
		temp = num[i]*factor;
		while (temp > 0) {
			res[j] += temp%10+carry;
			carry = res[j]/10;
			res[j] %= 10;
			temp /= 10;
			j++;
		}
		if (carry > 0) {
			res[j] = carry;
			carry = 0;
			j++;
		}
	}

	new_len = j;

	for (i = 0; i < new_len; i++)
		num[i] = res[i];

	free(res);

	return new_len;
}

int main()
{
	char digits[200];
	int i;
	int len;
	int sum = 0;

	digits[0] = 1;
	len = 1;

	for (i = 2; i < 101; i++) {
		len = multiply(digits, i, len);
		if (len < 0)
			return 1;
	}

	for (i = 0; i < len; i++)
		sum += digits[i];

	printf("Result: %d\n", sum);

	return 0;
}
