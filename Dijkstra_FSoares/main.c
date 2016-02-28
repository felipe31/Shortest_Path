#include <stdio.h>
#include "fib.h"
#include "dijkstra.h"
#include <stdlib.h>
#include <limits.h>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5


void insereAdj(Tvtx * vtx, int i, int custo)
{
	Lista * no = (Lista *) malloc(sizeof(Lista));
	if(!no) return;

	no->idx	 =  i;
	no->custo= custo;
	no->prox = vtx->adj;
	vtx->adj = no;

}


int main(void)
{

	Tvtx * graph[6];
	int i;

	for ( i = 0; i < 6; ++i)
	{
		graph[i] = (Tvtx *) malloc(sizeof(Tvtx));
		if (!graph[i])
		{
			puts("ERROR MAIN 1");
			return 0;
		}

		graph[i]->no.parent = NULL;
		graph[i]->no.child = NULL;
		graph[i]->no.n = INT_MAX;
		graph[i]->no.degree = 0;
		graph[i]->no.mark = 'F';
		graph[i]->flag = 0;

		graph[i]->pai=-1;
		graph[i]->idx=i;
		graph[i]->adj=NULL;
	}


	// for ( i = 0; i < 6; ++i)
	// {
	// 	printf("%d chave %d\n",i, graph[i]->no.chave );
	// }


	insereAdj(graph[A], B, 4);
    insereAdj(graph[A], C, 2);

    insereAdj(graph[B], A, 4);
    insereAdj(graph[B], C, 1);
    insereAdj(graph[B], D, 5);

    insereAdj(graph[C], A, 2);
    insereAdj(graph[C], B, 1);
    insereAdj(graph[C], D, 8);
    insereAdj(graph[C], E, 10);

    insereAdj(graph[D], B, 5);
    insereAdj(graph[D], C, 8);
    insereAdj(graph[D], E, 2);
    insereAdj(graph[D], F, 6);

    insereAdj(graph[E], C, 10);
    insereAdj(graph[E], D, 2);
    insereAdj(graph[E], F, 2);

    insereAdj(graph[F], D, 6);
    insereAdj(graph[F], E, 2);

	int * l;
	l = Dijkstra(graph, A, 6);

	if(!l) return 0;

	i=0;
	while(i<6)
	{
		printf("%d -> %d \n", i, l[i]);
		i++;
	}


	return 0;
}
