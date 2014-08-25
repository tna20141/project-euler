#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define HASH_TABLE_SIZE 997

struct hash_elem {
	int num;
	int is_prime;
	struct hash_elem *next;
};

struct hash_elem *hash_table[HASH_TABLE_SIZE];

int hash(int num)
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

void insert(int num, int is_prime, struct hash_elem **table)
{
	int index;
	struct hash_elem *p, **tmp;

	p = (struct hash_elem *)malloc(sizeof(struct hash_elem));
	if (p == NULL)
		return;
	init_hash_elem(p);
	p->num = num;
	p->is_prime = is_prime;

	index = hash(num);
	tmp = &table[index];

	while (*tmp != NULL)
		tmp = &((*tmp)->next);

	*tmp = p;
}

struct hash_elem *lookup(int num, struct hash_elem **table)
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

int is_prime(int num)
{
	int n, i;

	if (num < 2)
		return 0;

	n = (int)floor(sqrt((double)num));

	for (i = 2; i < n+1; i++)
		if (num%i == 0)
			return 0;
	return 1;
}

int is_prime_lookup(int num)
{
	struct hash_elem *p;
	int _is_prime;

	p = lookup(num, hash_table);
	if (p == NULL) {
		_is_prime = is_prime(num);
		insert(num, _is_prime, hash_table);
		return _is_prime;
	}

	return p->is_prime;
}

int num_consecutive_primes(int a, int b)
{
	int val;
	int i = -1;

	do {
		i++;
		val = i*i + a*i + b;
		if (val < 2)
			return i;
	} while (is_prime_lookup(val));

	return i;
}

int main()
{
	int max_count = 0;
	int count;
	int max = 0;
	int a, b;
	int max_a, max_b;

	init_hash_table(hash_table, HASH_TABLE_SIZE);

	for (a = -999; a < 1000; a++)
		for (b = -999; b < 1000; b++) {
			count = num_consecutive_primes(a, b);
			if (max_count < count) {
				max_count = count;
				max_a = a;
				max_b = b;
			}
		}

	printf("Result: %d, count = %d\n", max_a*max_b, max_count);

	free_hash_table(hash_table, HASH_TABLE_SIZE);
	return 0;
}
