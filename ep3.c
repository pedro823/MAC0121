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
	while(i <= mid && j <= fim) {
		if(aux[i] < aux[j]) {
			res[k] = aux[i];
			resParity[k++] = parity[i++];
		}
		else{
			res[k] = aux[j];
			resParity[k++] = parity[j++];
		}

	}
	while(i <= mid) {
		res[k] = aux[i];
		resParity[k++] = parity[i++];
	}
	while(j <= fim) {
		res[k] = aux[j];
		resParity[k++] = parity[j++];
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
	printf("specialMergeSort:\n");
	int mid;
	if(ini >= fim) return;
	mid = (ini + fim) / 2;
	printf("\tini = %d\n\tfim = %d", ini, fim);
	printf("\tmid = %d\n", mid);
	specialMergeSort(aux, parity, ini, mid);
	specialMergeSort(aux, parity, mid + 1, fim);
	specialMerge(aux, parity, ini, mid, fim);
}

/* Acha o próximo índice do modulo. */
int nextIndex(int size, int current) {
	int step;
	if(!(size % 2)) {

	}
	step = (size + 1) / 2;
	current = (current + step) % size;
	return current;
}

/* Função módulo para fazer o % funcionar que nem a implementação de python. */
int modulo(int n, int m) {
	if(n < 0)
		return m + n;
	return n % m;
}

/* Resolve um vetor de tamanho 3 */
/*
void trivialSolve(cVector *v) {
	int *solve = v->v;
	if(solve[0] <= solve[1] && solve[0] <= solve[2]) {
		/* O primeiro está no seu devido lugar
		if(solve[1] <= solve[2])
			/* Já está ordenado
			return;
		else {
			printf("2\n");
			return;
		}
	}
	else if(solve[0] <= solve[1]) {

	}
}
*/
/* Troca um índice e imprime o lado do vetor */
void swapNprint(cVector *v, int index) {
	cVector_swap(v, index);
	printf("%d\n", index);
}

/* Verifica se o vetor é possível de ser ordenado, antes de começar */
int isPossible(cVector *v, int *finalAux) {
	int i;
	char *parity;
	if(v->size % 2) {
		return true;
	}
	printf("isPossible:\n");
	parity = (char*) malloc(v->size * sizeof(char));
	finalAux = (int*) malloc(v->size * sizeof(int));
	for(i = 0; i < v->size; i++) {
		finalAux[i] = v->v[i];
		parity[i] = i % 2;
	}
	printf("\tallocated parity and assigned values\n");
	/* MergeSort com os dois vetores: Tudo que se fizer no vetor aux,
	   se faz no vetor paridade. Caso o vetor paridade, no final, não
	   se apresente da forma 0 1 0 1 0 1..., o vetor é impossível de se
	   ordenar e o EP acaba por aí. */
	specialMergeSort(finalAux, parity, 0, v->size-1);
	printf("isPossible:\n\tback from MergeSort");
	printf("\tvector:\n\t");
	for(i = 0; i < v->size; i++)
		printf("%d ", finalAux[i]);
	for(i = 0; i < v->size; i++) {
		if(parity[i] != (i % 2))
			return false;
	}
	return true;
}

/* Circular selection sort. */
void selectCircular(cVector *v, int *aux) {
	int i, j, next;
	int *indexation;
	printf("selectCircular\n");
	if(v->size % 2) {
		indexation = (int*) malloc(v->size * sizeof(int));
		indexation[0] = 0;
		/* Acha o índice correto do vetor circular */
		for(i = 1; i < v->size; i++) {
			indexation[i] = nextIndex(v->size, indexation[i - 1]);
		}
		/* Bubble sort explicado no relatório. */
		for(i = v->size - 2; i > 0; i = modulo(i - 2, v->size)) {
			for(j = 0; j == i ; j = modulo(j + 2, v->size)) {
				next = modulo(j + 2, v->size);
				if(v->v[j] > v->v[next])
					swapNprint(v, j);
			}
		}
	}
	else {
		/* BUBBLE PRIMEIRO PARA OS IMPARES DEPOIS PARA OS PARES. */
		for(i = v->size - 1; i > 0; i -= 2)
			for(j = 1; j < i; j += 2)
				if(v->v[j] > v->v[j + 2])
					swapNprint(v, j);
		/* BUBBLE PARA A SEGUNDA PARTE */
		for(i = v->size - 2; i > 0; i -= 2)
			for(j = 0; j < i; j += 2)
				if(v->v[j] > v->v[j + 2])
					swapNprint(v, j);
	}
	/* Debug */
	cVector_debug(v, 0);
}

int main() {
	int size, i, *aux = NULL;
	cVector *v;

	scanf("%d", &size);
	v = cVector_create(size);
	if(v == NULL)
		return -1;
	for(i = 0; i < size; i++) {
		scanf("%d", &(v->v[i]));
	}
	/* Para v <= 2 não definido */
	if(v->size <= 2) {
		printf("v->size < 3: %d\n", v->size);
		return 0;
	}
	if(isPossible(v, aux)) {
		selectCircular(v, aux);
	}
	else
		printf("Impossivel\n");
	cVector_destroy(v);
	return 0;
}
