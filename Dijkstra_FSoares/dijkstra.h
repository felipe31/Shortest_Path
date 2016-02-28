#ifndef _DIJKSTRA_
#define _DIJKSTRA_
#include "fibNet.h"
#define NoHeap node
#define Heap node

typedef char Tid[10];

typedef struct Lista{
	int custo, idx;
	Tid id;
	struct Lista * prox;
} Lista;

//terminar de implementar a FLAG
typedef struct Tvtx{
	NoHeap no;
	char flag;
	Tid id;
	int pai, idx;
	Lista * adj;
}Tvtx;


int * Dijkstra(Tvtx ** graph, int origem, int qtdvtx);

void verificaSP(Heap * H, Tvtx *vertice, Tvtx *pai, Lista * vz);

Heap * inicializaHeap();

void insereHeap(Heap * H, Tvtx * vtx, int custo);

Tvtx * extraiMenorHeap(Heap * H);

void diminuiHeap(Heap * H, Tvtx *vertice, int custo);



#endif
