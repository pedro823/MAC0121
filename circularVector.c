#include "circularVector.h"
#include <stdlib.h>

cVector *cVector_create(int size) {
	cVector *res;
	res = malloc(sizeof(cVector));
	if(res == NULL) 
		return NULL;

	res->v = malloc(size * sizeof(int));
	if(res->v == NULL)
		return NULL;

	return res;
}

void cVector_destroy(cVector *vector) {
	free(vector->v);
	free(vector);
}

void cVector_swap(cVector *vector, int index) {
	int temp, size;
	size = vector->size;
	temp = vector->v[index % size];
	vector->v[index % size] = vector->v[(index + 2) % size];
	vector->v[(index + 2) % size] = temp;
}
