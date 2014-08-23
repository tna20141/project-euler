#include <stdio.h>
#include <string.h>

#define N 1000

int add(int *addend1, int *addend2, int *res)
{
	int i = 0;
	int carry = 0;
	int tmp;

	while(addend1[i] != -1 && addend2[i] != -1) {
		tmp = addend1[i]+addend2[i]+carry;
		res[i] = tmp%10;
		carry = tmp/10;
		i++;
	}

	while(addend1[i] != -1) {
		tmp = addend1[i]+carry;
		res[i] = tmp%10;
		carry = tmp/10;
		i++;
	}

	while(addend2[i] != -1) {
		tmp = addend2[i]+carry;
		res[i] = tmp%10;
		carry = tmp/10;
		i++;
	}

	if (carry) {
		res[i] = carry;
		i++;
	}

	res[i] = -1;

	return i;
}

int main()
{
	int n1[N+1];
	int n2[N+1];
	int tmp[N+1];
	int term = 3;
	int len;
	int old_len = 0;

	n1[0] = 1;
	n1[1] = -1;
	n2[0] = 1;
	n2[1] = -1;

	while ((len = add(n1, n2, tmp)) < 1000) {
		memcpy(n1, n2, (len+1)*sizeof(int));
		memcpy(n2, tmp, (len+1)*sizeof(int));
		term++;
	}

	printf("Result: %d\n", term);

	return 0;
}
