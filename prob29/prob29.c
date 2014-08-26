#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define HASH_TABLE_SIZE 997

struct hash_elem {
	unsigned long long num;
	struct hash_elem *next;
};

struct hash_elem *hash_table[HASH_TABLE_SIZE];

int hash(unsigned long long num)
{
	return num%HASH_TABLE_SIZE;
}

inline void init_hash_elem(struct hash_elem *e)
{
	e->num = 0;
	e->next = NULL;
}

void init_hash_table(struct hash_elem **table, int size)
{
	int i;

	for (i = 0; i < size; i++)
		table[i] = NULL;
}

void insert(unsigned long long num, struct hash_elem **table)
{
	int index;
	struct hash_elem *p, **tmp;

	p = (struct hash_elem *)malloc(sizeof(struct hash_elem));
	if (p == NULL)
		return;
	init_hash_elem(p);
	p->num = num;

	index = hash(num);
	tmp = &table[index];

	while (*tmp != NULL)
		tmp = &((*tmp)->next);

	*tmp = p;
}

struct hash_elem *lookup(unsigned long long num, struct hash_elem **table)
{
	int index;
	struct hash_elem *p;

	index = hash(num);
	p = table[index];

	while (p != NULL) {
		if (p->num == num)
			return p;
		p = p->next;
	}
	return NULL;
}

void __free_chain(struct hash_elem *e)
{
	if (e == NULL)
		return;

	__free_chain(e->next);
	free(e);
}

void free_hash_table(struct hash_elem **table, int size)
{
	int i;

	for (i = 0; i < size; i++)
		__free_chain(table[i]);
}

int main()
{
	int i, j, k, l, m;
	unsigned short powers[4];
	unsigned long long p;
	int prod = 1;
	int dec = 0;
	int tmp1, tmp2, tmp3, tmp4;

	for (i = 0; prod < 101; i++) {
		tmp1 = prod;
		for (j = 0; prod < 101; j++) {
			tmp2 = prod;
			for (k = 0; prod < 101; k++) {
				tmp3 = prod;
				for (l = 0; prod < 101; l++) {
					if (prod < 2) {
						prod <<= 1;
						continue;
					}
					for (m = 2; m < 101; m++) {
						powers[0] = i*m;
						powers[1] = j*m;
						powers[2] = k*m;
						powers[3] = l*m;
						p = *((unsigned long long *)powers);
						if (lookup(p, hash_table) == NULL)
							insert(p, hash_table);
						else
							dec++;
					}
					prod <<= 1;
				}
				prod = tmp3;
				prod *= 3;
			}
			prod = tmp2;
			prod *= 5;
		}
		prod = tmp1;
		prod *= 7;
	}

	printf("Result: %d\n", 99*99-dec);

	free_hash_table(hash_table, HASH_TABLE_SIZE);
	return 0;
}


