#include <stdio.h>
#include <malloc.h>

#define FILENAME "./p042_words.txt"
#define BOUND 400
#define INIT_BUF_SIZE 20

void fill_is_trangle_array(int *a, int len)
{
	int i;
	int sum = 1;

	for (i = 0; i < len; i++)
		a[i] = 0;

	i = 2;
	while (sum < len) {
		a[sum] = 1;
		sum += i;
		i++;
	}
}

int cal(char *buf, int len)
{
	int i;
	int res = 0;

	if (buf[0] != '\"')
		res += buf[0]-'A'+1;

	for (i = 1; i < len; i++)
		res += buf[i]-'A'+1;

	return res;
}

int main()
{
	char *buf;
	size_t buf_size = INIT_BUF_SIZE;
	int is_triangle[BOUND];
	int count = 0;
	FILE *f;
	int len;
	int i, sum;

	buf = (char *)malloc(buf_size);
	if (buf == NULL)
		return 1;

	f = fopen(FILENAME, "rb");
	if (f == NULL)
		goto out_free;

	fill_is_trangle_array(is_triangle, BOUND);

	while ((len = getdelim(&buf, &buf_size, ',', f)) != -1) {
		if (buf[len-1] == ',') {
			len--;
			buf[len] = '\0';
		}
		if (buf[len-1] == '\"') {
			len--;
			buf[len] = '\0';
		}
		sum = cal(buf, len);
		if (is_triangle[sum])
			count++;
	}

	printf("Result: %d\n", count);

	fclose(f);
out_free:
	free(buf);

	return 0;
}
