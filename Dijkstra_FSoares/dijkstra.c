#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "dijkstra.h"


int * Dijkstra(Tvtx ** graph, int origem, int qtdvtx)
{
	assert(graph);
	if(origem < 0) return NULL;
	if(origem < 0) return NULL;

	Heap * H = inicializaHeap();
	Tvtx * menor_vtx;
	Lista * vz;
	int idx;

	int *lista = (int *) malloc(sizeof(int)*qtdvtx);
	if(!lista) return NULL;

	lista[origem] = origem;
	graph[origem]->pai = origem;


	insereHeap(H, graph[origem], 0);
	menor_vtx = extraiMenorHeap(H);

	while(menor_vtx)
	{
		vz = menor_vtx->adj;

		while(vz)
		{
			idx = vz->idx;

			verificaSP(H, graph[idx], menor_vtx, vz);

			vz = vz->prox;

		}
		lista[menor_vtx->idx] = menor_vtx->pai;
printf("james \n" );
		menor_vtx = extraiMenorHeap(H);

	}

	return lista;
}



void verificaSP(Heap * H, Tvtx *vertice, Tvtx *pai, Lista * vz)
{
	assert(H);
	assert(vertice);
	assert(pai);
	assert(vz);


	if (vertice->no.n == INT_MAX)
	{
		insereHeap(H, vertice, pai->no.n + vz->custo);
		vertice->pai = pai->idx;
	}

	else
	{

		if (vertice->no.n > pai->no.n + vz->custo)
		{
			printf("			%d n %d nova %d \n", vertice->idx, vertice->no.n, pai->no.n + vz->custo);

			diminuiHeap(H, vertice, pai->no.n + vz->custo);
			vertice->pai = pai->idx;
		}
	}

}

Heap *inicializaHeap()
{
	return (Heap *) InitializeHeap();
}


void insereHeap(Heap * H, Tvtx * vtx, int custo)
{
	vtx->no.n=custo;
	Insert(H, (NoHeap *) vtx);
}


Tvtx * extraiMenorHeap(Heap * H)
{
	return (Tvtx *) Extract_Min(H);
}


void diminuiHeap(Heap * H, Tvtx *vertice, int custo)
{
	Decrease_key(H, (Heap *) vertice, custo);

}
