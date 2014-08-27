#include <stdio.h>

#define AMOUNT 200

int num_coins = 7;
int coins[7] = {200, 100, 50, 20, 10, 5, 2};

int num_ways(int amount, int start)
{
	int i;
	int ways = 0;
	int acc = 0;

	if (amount == 0)
		return 1;

	if (start == num_coins)
		return 1;

	while (acc <= amount) {
		ways += num_ways(amount-acc, start+1);
		acc += coins[start];
	}

	return ways;
}

int main()
{
	printf("Result: %d\n", num_ways(AMOUNT, 0));

	return 0;
}
