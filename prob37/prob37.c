#include <stdio.h>

int sum = 23+53+73+37+313+373;
int count = 6;

int is_prime(unsigned long long num)
{
	int i = 2;

	if (num == 0 || num == 1)
		return 0;

	while (i*i < num) {
		if (num%i == 0)
			return 0;
		i++;
	}
	return 1;
}

void check_prefix_suffix(int prefix, int p_cnt, int suffix, int s_cnt,
		int mid, int m_cnt)
{
	unsigned long long num;
	unsigned long long tmp;
	int factor = 1;
	int i;

	for (i = 0; i < s_cnt; i++)
		factor *= 10;
	num = suffix + factor*mid;

	for (i = 0; i < m_cnt; i++)
		factor *= 10;
	num += factor*prefix;

	tmp = num;
	while (tmp > 0) {
		if (!is_prime(tmp))
			return;
		tmp /= 10;
	}

	for (i = 0; i < p_cnt-1; i++)
		factor *= 10;

	while (factor > 1) {
		tmp = num%factor;
		if (!is_prime(tmp))
			return;
		factor /= 10;
	}

	sum += num;
	count++;
}

void __check_middle(int prefix, int p_cnt, int suffix, int s_cnt,
		int mid, int m_cnt, int m)
{
	if (m_cnt == m) {
		check_prefix_suffix(prefix, p_cnt, suffix, s_cnt, mid, m_cnt);
		return;
	}

	__check_middle(prefix, p_cnt, suffix, s_cnt, mid*10+3, m_cnt, m+1);
	__check_middle(prefix, p_cnt, suffix, s_cnt, mid*10+9, m_cnt, m+1);
}

void check_middle(int prefix, int p_cnt, int suffix, int s_cnt, int m_cnt)
{
	__check_middle(prefix, p_cnt, suffix, s_cnt, 0, m_cnt, 0);
}

int main()
{
	int cnt = 0;

	while (1) {
		check_middle(7, 1, 73, 2, cnt);
		if (count >= 11)
			break;
		check_middle(7, 1, 13, 2, cnt);
		if (count >= 11)
			break;
		check_middle(7, 1, 7, 1, cnt);
		if (count >= 11)
			break;
		check_middle(37, 2, 13, 2, cnt);
		if (count >= 11)
			break;
		check_middle(31, 2, 13, 2, cnt);
		if (count >= 11)
			break;
		check_middle(37, 2, 7, 1, cnt);
		if (count >= 11)
			break;
		check_middle(31, 2, 7, 1, cnt);
		if (count >= 11)
			break;
		check_middle(31, 2, 73, 2, cnt);
		if (count >= 11)
			break;
		check_middle(37, 2, 73, 2, cnt);
		if (count >= 11)
			break;
		cnt++;
	}

	printf("Result: %d\n", sum);

	return 0;
}
