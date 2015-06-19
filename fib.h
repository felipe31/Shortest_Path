#ifndef FIB_H
#define FIB_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

typedef struct NoHeapFib{

	struct NoHeapFib* pai; //ponteiro para o nó pai
	struct NoHeapFib* filho; //ponteiro para um nó filho
	struct NoHeapFib* esq; //ponteiro para o nó irmão esquerdo
	struct NoHeapFib* dir; //ponteiro para o nó irmão direito


	int custo;
	int grau; //quantidade de filhos do nó
	char marca; //campo booleano que determina se o nó já perdeu o filho

} NoHeapFib;


typedef struct HeapFib
{
	NoHeapFib * noMin;
	int qtdNos;
} HeapFib;


typedef struct verticeDjk
{
	
	NoHeapFib * noFib;
	int verticeId;
	struct verticeDjk * predec;

} verticeDjk;



HeapFib * makeHeapFib();

NoHeapFib * insereFib( HeapFib * H, int custo);

NoHeapFib * insereFibNoPronto( HeapFib * H, NoHeapFib * No);

void heapFibLink(HeapFib * H, NoHeapFib * y, NoHeapFib * x);

void consolidar(HeapFib * H);

NoHeapFib * extractMin(HeapFib * H);

void decreaseKey(HeapFib* H, NoHeapFib* x , int k, verticeDjk * predec);

void cut(HeapFib* H, NoHeapFib* x, NoHeapFib* y);

void cascadingCut(HeapFib* H, NoHeapFib* y);

void imprimirHeapFib(HeapFib* H);

void imprimir( NoHeapFib* No, NoHeapFib * pai);


#endif
