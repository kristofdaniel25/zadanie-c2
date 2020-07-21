#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	unsigned int rows;
	unsigned int cols;
	float		*elem;
}MAT;

#define ELEM(A,r,c) (A->elem[(A->cols)*c+r])

MAT* mat_create_with_type(unsigned int r, unsigned int c)
{
	MAT* m = malloc(sizeof(MAT));
	if (m == NULL)
		return NULL;
	m->rows = r;
	m->cols = c;

	if ((m->elem = malloc(sizeof(float) * r * c)) == NULL)
	{
		free(m);
		return NULL;
	}
	return m;
}

void mat_random(MAT* mat) {
	int i, j;


	for (i = 0; i < mat->cols; i++) {
		for (j = 0; j < mat->rows; j++) {
			ELEM(mat, i, j) = -1 + (1 - (-1)) * ((float)rand() / (float)(RAND_MAX));
			printf(" %.3f ", ELEM(mat, i, j));
		}
		printf("\n");
	}
	
}



void mat_destroy(MAT* mat) {
	free(mat);
}

int main()
{
	MAT* a, * b;
	unsigned int n;
	srand(time(NULL));

	printf("Zadajte velkost matice a (nxn):");
	scanf_s("%d", &n);

	a = mat_create_with_type(n, n);
	b = mat_create_with_type(1, n);
	
	mat_random(a);
	mat_random(b);

	mat_destroy(a);
	mat_destroy(b);
	return 0;
}