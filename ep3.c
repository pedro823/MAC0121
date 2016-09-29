#include <stdio.h>
#include <stdlib.h>
#include "circularVector.h"
#define true 1
#define false 0

/* Merge especial do mergeSort, que faz todas as operações no vetor de
	paridade também. */
void specialMerge(int *aux, char *parity, int ini, int mid, int fim) {
	int i = ini, j = mid + 1, k = 0, *res;
	char *resParity;
	res = (int*) malloc((fim - ini + 1) * sizeof(int));
	resParity = (char*) malloc((fim - ini + 1) * sizeof(int));
	while(i <= mid && j <= end) {
		if(aux[i] > aux[j]) {
			res[k] = aux[i];
			resParity[k++] = parity[i++];
		}
		else{
			res[k] = aux[j];
			resParity[k++] = parity[j++]
		}
	
	}
	while(i <= mid) {
		res[k] = aux[i];
		resParity[k++] = parity[i++];	
	}
	while(j <= fim) {
		res[k] = aux[j];
		resParity[k++] = parity[j++]
	}
	for(i = 0; i < k; i++) {
		aux[ini + i] = res[i];
		parity[ini + i] = resParity[i];
	}
	free(res);
	free(resParity);
}


/* Esse mergeSort também faz todas as operações 
	que deve fazer no aux, no parity também. Para auxiliar na checagem
	de paridade do vetor. */
void specialMergeSort(int *aux, char *parity, int ini, int fim) {
	int mid;
	if(ini >= fim) return;
	mid = ini + fim / 2;
	specialMergeSort(aux, parity, ini, mid);
	specialMergeSort(aux, parity, mid + 1, fim);
	specialMerge(aux, parity, ini, mid, fim);
}


/* Verifica se o vetor é possível de ser ordenado, antes de começar */
int isPossible(static cVector *v, int size) {
	int *aux, i;
	char *parity;
	
	if(size % 2) {
		return true;
	}
	parity = (char*) malloc(size * sizeof(char));
	aux = (int*) malloc(size * sizeof(int));
	for(i = 0; i < size; i++) {
		aux[i] = v[i];
		parity[i] = i % 2;
	}
	/* MergeSort com os dois vetores: Tudo que se fizer no vetor aux,
	   se faz no vetor paridade. Caso o vetor paridade, no final, não
	   se apresente da forma 0 1 0 1 0 1..., o vetor é impossível de se
	   ordenar e o EP acaba por aí. */
	specialMergeSort(aux, parity, 0, size - 1);
	for(i = 0; i < size; i++) {
		if(parity[i] != (i % 2))
			return false;
	}
	return true;
}


int main() {
	int size, i;
	cVector *v;
	scanf("%d", &size);
	v = cVector_create(size);
	if(v == NULL) 
		return -1;
	for(i = 0; i < size; i++)
		scanf("%d", &v[i]);
	if(isPossible(v, size)) {
		
	}
	else
		printf("Impossivel\n");
	cVector_destroy(v);
	return 0;
}
