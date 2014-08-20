#include <stdio.h>

inline int count_one_digit()
{
	return 36;
}

inline int count_tens()
{
	return 70;
}

int count_two_digits()
{
	int char_num[8] = {6, 6, 5, 5, 5, 7, 6, 6};
	int i, sum = 0;

	for (i = 0; i < 8; i++)
		sum += char_num[i]*10 + count_one_digit();

	return sum+count_tens();
}

int count_three_digits()
{
	int i, sum = 0;

	sum += (count_one_digit()+count_two_digits())*9;
	sum += (count_one_digit()+7*9)+(count_one_digit()+90)*99;

	return sum;
}

int main()
{
	printf("Result: %d\n", count_one_digit()+
			count_two_digits()+count_three_digits()+11);

	return 0;
}
