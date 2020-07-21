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
		}
	}
	
}

void mat_print(MAT* mat) {
	int i, j;

	for (i = 0; i < mat->rows; i++) {
		for (j = 0; j < mat->cols; j++) {
			if (ELEM(mat, i, j) < 0) printf(" %.3f", ELEM(mat, i, j));
			else printf("  %.3f", ELEM(mat, i, j));
		}
		printf("\n");
	}
}

char mat_solve_gauss(MAT* a, MAT* b)
{
	int i, j;
	float guide;
	for (i = 0; i < a->cols; i++)
	{
		ELEM(a, 0, i) = ELEM(a, 0, 0) / ELEM(a, 0, i);
	}
	ELEM(b, 0, 0) = ELEM(a, 0, 0) / ELEM(b, 0, 0);

	mat_print(a);
	printf("\n");
	mat_print(b);
	printf("\n"); printf("\n");

	for (i = 1; i < a->rows; i++)
	{
		guide = -1 * ELEM(a, i, 0);
		for (j = 0; j < a->cols; j++)
		{
			ELEM(a, i, j) += ELEM(a, 0, j) * guide;
		}
		ELEM(b, i, 1) += ELEM(a, 0, j) * guide;
	    printf("b_%d: %.3f\n",i, ELEM(b, i, 1));
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
	b = mat_create_with_type(n, 1);
	
	mat_random(a);
	mat_random(b);
	
	mat_print(a);
	printf("\n");
	mat_print(b);
	printf("\n"); printf("\n");
	mat_solve_gauss(a, b);
	mat_print(a);
	mat_print(b);
	mat_destroy(a);
	mat_destroy(b);
	return 0;
}