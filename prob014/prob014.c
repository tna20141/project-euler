#include <stdio.h>
#include <stdlib.h>

#define END 1000000

int main()
{
	unsigned int *table;
	unsigned int i, max_num, max_len, len;
	unsigned long long n;

	table = (unsigned int *)calloc(END+1, sizeof(unsigned int));
	if (table == NULL)
		return 1;

	table[1] = 1;
	max_len = 1;
	max_num = 1;

	for (i = 2; i < END+1; i++) {
		n = i;
		len = 1;
		while (n > 1) {
			len++;
			n = (n%2 == 1) ? 3*n+1 : n/2;
			if (n < END)
				if (table[n] != 0) {
					len += table[n];
					break;
				}
		}
		table[i] = len;
		if (len > max_len) {
			max_len = len;
			max_num = i;
		}
	}

	printf("The number with the longest chain is %u, with length %u\n",
			max_num, max_len);

	free(table);
	return 0;
}
