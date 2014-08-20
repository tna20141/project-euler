#include <stdio.h>

typedef enum {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
} day_of_week;

int main()
{
	day_of_week cur = (MONDAY+365)%7;
	int year = 1901;
	int month = 1;
	int sundays = 0;

	while (year < 2001) {
		if (cur == SUNDAY)
			sundays++;

		switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
			cur = (cur+31)%7;
			month++;
			break;
		case 2:
			if (year%4 == 0 && (year%100 != 0 || year%400 == 0))
				cur = (cur+29)%7;
			else
				cur = (cur+28)%7;
			month++;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			cur = (cur+30)%7;
			month++;
			break;
		case 12:
			cur = (cur+31)%7;
			month = 1;
			year++;
			break;
		}
	}

	printf("Results: %d\n", sundays);

	return 0;
}
