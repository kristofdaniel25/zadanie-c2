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
			//ELEM(mat, i, j) = rand() % 15; ---> pre overenie spravnosti vysledku
		}
	}
	
}

void mat_unit(MAT* mat) {
	int i, j;
	for (i = 0; i < mat->rows; i++) {
		for (j = 0; j < mat->cols; j++) {
			if (i == j) ELEM(mat, i, j) = 1;
			else ELEM(mat, i, j) = 0;
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

char mat_solve_gauss(MAT* a, MAT* b, MAT* s)
{
	int i, j, k;
	float guide;
	unsigned int c = a->cols - 1;
	/*
	CYKLUS NA VYTVORENIE HORNEJ TROJUHOLNIKOVEJ MATICE Z MATICE a:
	1)predelenie riadku prvym nenulovym elementom riadku (cyklus predelenia)
	2)scitanie kazdeho elementu pod riadkom s nasobkom daneho riadku (cyklus scitania)
	Pozn. Oba cykly dodatocne pracuju aj s maticou b. Hodit cely algoritmus do jedneho cyklu by bolo menej narocnejsie na pamat, avsak aj menej prehladne.		
	*/
	
	for (k = 0; k < a->rows; k++)
	{
		guide = ELEM(a, k, k);
	
        for (i = k; i < a->cols; i++)	//cyklus predelenia
		{
			ELEM(a, k, i) = ELEM(a, k, i) / guide;
		}
		ELEM(b, k, 0) = ELEM(b, k, 0) / guide;
		
		for (i = k+1; i < a->rows; i++)	//cyklus scitania
		{
			guide = -1 * ELEM(a, i, k);
			for (j = k; j < a->cols; j++)
			{
				ELEM(a, i, j) += ELEM(a, k, j) * guide;
			}

			ELEM(b, i, 0) += ELEM(b, k, 0) * guide;
		}
	}
	
	for (k = a->rows -1; k > -1; k--)
	{
		
		for (i = k - 1; i > - 1; i--)	//cyklus scitania
		{
			guide = -1 * ELEM(a, i, k);
			for (j = k; j < a->cols; j++)
			{
				ELEM(a, i, j) += ELEM(a, k, j) * guide;
			}

			ELEM(b, i, 0) += ELEM(b, k, 0) * guide;
		}
	}
	
	for (i = 0; i < b->rows; i++)
	{
		ELEM(s, i, 0) = ELEM(b, i, 0);
	}

}


void mat_destroy(MAT* mat) {
	free(mat);
	free(mat->elem);
}

int main()
{
	MAT* a, * b, *s;
	unsigned int n;
	srand(time(NULL));

	printf("Zadajte velkost matice a (nxn):");
	scanf_s("%d", &n);

	a = mat_create_with_type(n, n);
	b = mat_create_with_type(n, 1);
	s = mat_create_with_type(n, 1);

	mat_random(a);
	mat_random(b);
	

	printf("\n"); printf("\n");
	
	mat_solve_gauss(a, b, s);

	mat_print(s);

	mat_destroy(a);
	mat_destroy(b);
	mat_destroy(s);
	return 0;
}