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

void mat_destroy(MAT* mat) {
	free(mat);
	free(mat->elem);
}

int main()
{
	MAT* a, * b;
	srand(time(NULL));

	printf("Zadajte velkost matice nxn:");
	scanf("%d", &n);

	a = mat_create_with_type(n, n);
	b = mat_create_with_type(1, n);

	mat_destroy(a);
	mat_destroy(b);
	return 0;
}