#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>


typedef struct verticeDjk
{
	int custo;
	int verticeId;
	struct verticeDjk * predec;

} verticeDjk;



#endif