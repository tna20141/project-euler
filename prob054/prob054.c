#include <stdio.h>

#define HANDS 1000
#define LINE_LEN 30

#define S 1
#define C 2
#define D 3
#define H 4

#define STRAIGHT_FLUSH_BASE_SCORE 9000000
#define FOUR_OF_A_KIND_BASE_SCORE 8000000
#define FULL_HOUSE_BASE_SCORE 7000000
#define FLUSH_BASE_SCORE 6000000
#define STRAIGHT_BASE_SCORE 5000000
#define THREE_OF_A_KIND_BASE_SCORE 4000000
#define TWO_PAIRS_BASE_SCORE 3000000
#define ONE_PAIR_BASE_SCORE 2000000

#define CARD_FACTOR_4 50625
#define CARD_FACTOR_3 3375
#define CARD_FACTOR_2 225
#define CARD_FACTOR 15

struct card {
	int value;
	int suit;
};

char *buf;

void read_card(struct card *p, char *buf)
{
	if ('0' <= buf[0] && buf[0] <= '9')
		p->value = buf[0]-'0';
	else if (buf[0] == 'T')
		p->value = 10;
	else if (buf[0] == 'J')
		p->value = 11;
	else if (buf[0] == 'Q')
		p->value = 12;
	else if (buf[0] == 'K')
		p->value = 13;
	else
		p->value = 14;

	switch (buf[1]) {
	case 'S':
		p->suit = S;
		break;
	case 'C':
		p->suit = C;
		break;
	case 'D':
		p->suit = D;
		break;
	case 'H':
		p->suit = H;
		break;
	}
}

void read_hands(FILE *f, struct card *p1, struct card *p2)
{
	int i;
	size_t n = 0;

	getline(&buf, &n, f);

	for (i = 0; i < 5; i++)
		read_card(&p1[i], &buf[i*3]);

	for (i = 0 ; i < 5; i++)
		read_card(&p2[i], &buf[(i+5)*3]);
}

void sort(struct card *p)
{
	int i, j;
	struct card tmp;

	for (i = 0; i < 5; i++)
		for (j = 4; j > i; j--)
			if (p[j].value > p[j-1].value) {
				tmp = p[j];
				p[j] = p[j-1];
				p[j-1] = tmp;
			}
}

int all_cards_score(struct card *p)
{
	return p[0].value*CARD_FACTOR_4+p[1].value*CARD_FACTOR_3+p[2].value*CARD_FACTOR_2+
			p[3].value*CARD_FACTOR+p[4].value;
}

int royal_or_straight_flush(struct card *p)
{
	int i;
	int suit = p[0].suit;
	int last_value = p[0].value-1;

	for (i = 1; i < 5; i++, last_value--)
		if (p[i].value != last_value)
			return 0;

	for (i = 1; i < 5; i++)
		if (p[i].suit != suit)
			break;

	if (i == 5)
		return STRAIGHT_BASE_SCORE+last_value;
	else
		return STRAIGHT_FLUSH_BASE_SCORE+last_value;
}

int four_of_a_kind(struct card *p)
{
	int i;

	if (p[0].value == p[1].value) {
		for (i = 1; i < 3; i++)
			if (p[i].value != p[i+1].value)
				return 0;

		return FOUR_OF_A_KIND_BASE_SCORE+p[0].value*CARD_FACTOR+p[4].value;
	} else {
		for (i = 1; i < 4; i++)
			if (p[i].value != p[i+1].value)
				return 0;

		return FOUR_OF_A_KIND_BASE_SCORE+p[1].value*CARD_FACTOR+p[0].value;
	}
}

int straight(struct card *p)
{
	int i;
	int last_value = p[0].value-1;

	for (i = 1; i < 5; i++, last_value--)
		if (p[i].value != last_value)
			return 0;

	return STRAIGHT_BASE_SCORE+last_value;
}

int flush(struct card *p)
{
	int i;
	int suit = p[0].suit;

	for (i = 1; i < 5; i++)
		if (p[i].suit != suit)
			return 0;

	return FLUSH_BASE_SCORE+all_cards_score(p);
}

int three_of_a_kind(struct card *p)
{
	if (p[2].value == p[1].value) {
		if (p[1].value == p[0].value)
			return THREE_OF_A_KIND_BASE_SCORE+p[0].value*CARD_FACTOR_2+
					p[3].value*CARD_FACTOR+p[4].value;
		else if (p[2].value == p[3].value)
			return THREE_OF_A_KIND_BASE_SCORE+p[2].value*CARD_FACTOR_2+
					p[0].value*CARD_FACTOR+p[4].value;
		else
			return 0;
	}

	if (p[2].value == p[3].value && p[3].value == p[4].value)
		return THREE_OF_A_KIND_BASE_SCORE+p[2].value*CARD_FACTOR_2+
				p[0].value*CARD_FACTOR+p[1].value;
	else
		return 0;
}

int full_house(struct card *p)
{
	if (p[0].value != p[1].value || p[3].value != p[4].value)
		return 0;

	if (p[1].value == p[2].value)
		return FULL_HOUSE_BASE_SCORE+p[2].value*CARD_FACTOR+p[3].value;
	else if (p[2].value == p[3].value)
		return FULL_HOUSE_BASE_SCORE+p[2].value*CARD_FACTOR+p[1].value;
	else
		return TWO_PAIRS_BASE_SCORE+
				p[0].value*CARD_FACTOR_2+p[4].value*CARD_FACTOR+p[2].value;
}

int two_pairs(struct card *p)
{
	if (p[0].value == p[1].value) {
		if (p[2].value == p[3].value)
			return TWO_PAIRS_BASE_SCORE+p[0].value*CARD_FACTOR_2+
					p[2].value*CARD_FACTOR+p[4].value;
		else if (p[3].value == p[4].value)
			return TWO_PAIRS_BASE_SCORE+p[0].value*CARD_FACTOR_2+
					p[3].value*CARD_FACTOR+p[2].value;
		else
			return ONE_PAIR_BASE_SCORE+p[0].value*CARD_FACTOR_3+
					p[2].value*CARD_FACTOR_2+p[3].value*CARD_FACTOR+p[4].value;
	} else if (p[1].value == p[2].value) {
		if (p[3].value == p[4].value)
			return TWO_PAIRS_BASE_SCORE+p[1].value*CARD_FACTOR_2+
					p[3].value*CARD_FACTOR+p[0].value;
		else
			return ONE_PAIR_BASE_SCORE+p[1].value*CARD_FACTOR_3+
					p[0].value*CARD_FACTOR_2+p[3].value*CARD_FACTOR+p[4].value;
	} else
		return 0;
}

int high_card(struct card *p)
{
	return all_cards_score(p);
}

int one_pair(struct card *p)
{
	int i;
	int s = 0;
	int factor = CARD_FACTOR_2;

	for (i = 0; i < 4; i++)
		if (p[i].value == p[i+1].value) {
			s += ONE_PAIR_BASE_SCORE;
			s += p[i].value*CARD_FACTOR_3;
			i++;
		} else {
			s = p[i].value*factor;
			factor /= CARD_FACTOR;
		}

	if (s > ONE_PAIR_BASE_SCORE)
		return s;
	else
		return high_card(p);
}

int score(struct card *p)
{
	int s;

	sort(p);

	if (s = royal_or_straight_flush(p))
		return s;

	if (s = four_of_a_kind(p))
		return s;

	if (s = full_house(p))
		return s;

	if (s = flush(p))
		return s;

	if (s = straight(p))
		return s;

	if (s = three_of_a_kind(p))
		return s;

	if (s = two_pairs(p))
		return s;

	if (s = one_pair(p))
		return s;

	return high_card(p);
}

int compare(struct card *p1, struct card *p2)
{
	return score(p1)-score(p2);
}

int main()
{
	int i;
	struct card p1[5], p2[5];
	int p1_wins = 0;
	FILE *f;
	int cmp;

	f = fopen("./p054_poker.txt", "rb");
	if (f == NULL)
		return 1;

	for (i = 0; i < HANDS; i++) {
		read_hands(f, p1, p2);
		if (compare(p1, p2) > 0)
			p1_wins++;
	}

	printf("Result: %d\n", p1_wins);

	fclose(f);

	return 0;
}
