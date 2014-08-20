#include <stdio.h>
#include <malloc.h>

struct result {
	int max_sum;
	int pos;
};

int main()
{
	int line1[1] = {75};
	int line2[2] = {95, 64};
	int line3[3] = {17, 47, 82};
	int line4[4] = {18, 35, 87, 10};
	int line5[5] = {20, 4, 82, 47, 65};
	int line6[6] = {19, 1, 23, 75, 3, 34};
	int line7[7] = {88, 2, 77, 73, 7, 63, 67};
	int line8[8] = {99, 65, 4, 28, 6, 16, 70, 92};
	int line9[9] = {41, 41, 26, 56, 83, 40, 80, 70, 33};
	int line10[10] = {41, 48, 72, 33, 47, 32, 37, 16, 94, 29};
	int line11[11] = {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14};
	int line12[12] = {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57};
	int line13[13] = {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48};
	int line14[14] = {63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31};
	int line15[15] = {4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23};
	int *lines[15] = {line1, line2, line3, line4, line5, line6, line7, line8,
			line9, line10, line11, line12, line13, line14, line15};
	struct result **results = NULL;
	int i, j;

	results = (struct result **)malloc(15*sizeof(struct result *));
	for (i = 0; i < 15; i++)
		results[i] = (struct result *)calloc(i+15, sizeof(struct result));

	for (i = 0; i < 15; i++) {
		results[14][i].max_sum = line15[i];
		results[14][i].pos = -1;
	}

	for (i = 13; i > -1; i--)
		for (j = 0; j < i+1; j++) {
			if (results[i+1][j].max_sum > results[i+1][j+1].max_sum) {
				results[i][j].max_sum = lines[i][j]+
						results[i+1][j].max_sum;
				results[i][j].pos = j;
			} else {
				results[i][j].max_sum = lines[i][j]+
						results[i+1][j+1].max_sum;
				results[i][j].pos = j+1;
			}
		}

	printf("Max sum: %d\n", results[0][0].max_sum);
	printf("Path:");
	for (i = 0, j = 0; i < 15; i++) {
		printf(" %d", j+1);
		j = results[i][j].pos;
	}
	printf("\n");

	for (i = 0; i < 15; i++)
		free(results[i]);

	free(results);

	return 0;
}
