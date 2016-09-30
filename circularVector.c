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

int cVector_swap(cVector *vector, int index) {
	int temp, size;
	size = vector->size;
	temp = vector->v[index % size];
	vector->v[index % size] = vector->v[(index + 2) % size];
	vector->v[(index + 2) % size] = temp;
	return(index % size);
}

void cVector_debug(cVector *vector, int mode) {
	int i;
	if(mode && mode < vector->size) {
		printf("cVector::debug -> index %d: %d", mode, vector->v[mode]);
	}
	else if (!mode) {
		printf("cVector::debug -> vector\n    ");
		for(i = 0; i < vector->size; i++) {
			printf("%d ", vector->v[i]);
		}
		printf("\n");
	}
}