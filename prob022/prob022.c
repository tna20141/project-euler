#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

#define ALLOC_BATCH 100

char **read_names(const char *filename, int *num);
void free_names(char **names, int num);
inline void sort_names(char **names, int num);
unsigned long long cal_score(char **names, int num);

char **read_names(const char *filename, int *num)
{
	FILE *f = NULL;
	int _num = 0;
	int i;
	char **names = NULL, **tmp = NULL;
	char *name = NULL;
	size_t len = 0;
	int batches = 1;
	ssize_t read;

	f = fopen(filename, "rb");
	if (f == NULL)
		return NULL;

	names = (char **)malloc(ALLOC_BATCH*sizeof(char *));
	if (names == NULL)
		goto out_close_null;

	while ((read = getdelim(&name, &len, ',', f)) != -1) {
		_num++;
		if (_num > ALLOC_BATCH*batches) {
			batches++;
			tmp = names;
			names = (char **)realloc(names, ALLOC_BATCH*batches*sizeof(char *));
			if (names == NULL) {
				free_names(tmp, _num-1);
				free(name);
				goto out_close_null;
			}
		}
		if (name[read-1] == ',')
			read--;
		name[read-1] = '\0';
		names[_num-1] = name;
		name = NULL;
		len = 0;
	}

	if (errno != 0) {
		free_names(names, _num);
		goto out_close_null;
	}

	*num = _num;
	fclose(f);
	return names;

out_close_null:
	fclose(f);
	return NULL;
}

void free_names(char **names, int num)
{
	int i;
	
	for (i = 0; i < num; i++)
		free(names[i]);
	free(names);
}

void __sort_names(char **names, int start, int end)
{
	int i, j;
	char *tmp;
	char mid[100];

	if (start >= end)
		return;

	strcpy(mid, names[(start+end)/2]);
	i = start;
	j = end;
	while (i <= j) {
		while (strcmp(names[i], mid) < 0)
			i++;

		while (strcmp(mid, names[j]) < 0)
			j--;

		if (i <= j) {
			tmp = names[i];
			names[i] = names[j];
			names[j] = tmp;
			i++;
			j--;
		}
	}

	__sort_names(names, start, j);
	__sort_names(names, i, end);
}

inline void sort_names(char **names, int num)
{
	__sort_names(names, 0, num-1);
}

unsigned int name_sum(const char *name)
{
	unsigned int sum = 0;
	int i = 1;

	while (name[i] != '\0') {
		sum += name[i]-'A'+1;
		i++;
	}

	return sum;
}

unsigned long long cal_score(char **names, int num)
{
	int i;
	unsigned long long sum = 0;

	for (i = 0; i < num; i++)
		sum += (i+1)*name_sum(names[i]);

	return sum;
}

int main()
{
	char **names;
	int num;
	unsigned long long sum;

	names = read_names("./p022_names.txt", &num);

	if (names == NULL) {
		perror("Can't read names!\n");
		return 1;
	}

	sort_names(names, num);

	sum = cal_score(names, num);

	printf("Result: %llu\n", sum);

	free_names(names, num);

	return 0;
}
