#ifndef __CIRCULARVECTOR_H__
#define __CIRCULARVECTOR_H__

/*		CircularVector header
		por Pedro Pereira, IME-USP */

typedef struct {
	int *v;
	int size;
} cVector;

/* Cria e retorna um ponteiro de um
   vetor circular de tamanho size */
cVector *cVector_create(int size);

/* Desaloca a memória disponível de um
   vetor circular. Este se torna
   inutilizável. 					*/
void cVector_destroy(cVector *vector);

/* Faz uma 3-reversão no vetor circular
   vector no índice index.
   Retorna o indice do vetor mexido,
   logo não falha caso o índice é maior que
   o tamanho do vetor.			*/

int cVector_swap(cVector *vector, int index);


#endif