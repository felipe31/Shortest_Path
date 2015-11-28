#include "rr.h"
#include <limits.h>
#define infinity INT_MAX

void rr_recalculate_shortest_path(vertex *graph, heap *queue){
	node *x;
	while(queue){
		x = heap_extract_min(queue);
		(graph+x->key)->pi = x->pi;
		(graph+x->key)->min_cost = x->cost;
		edge *aux = (graph+x->key)->predecessor;
		while(aux){
			aux->hot_line = 0;
			aux = aux->next;
		}
		aux = (graph+x->pi)->adjacent;
		while(aux){
			if(aux->head_vertex == (graph+x->key)){
				aux->hot_line = 1;
				break;
			}
			aux = aux->next;
		}
		aux = x->adjacent;
		while(aux){
			if((graph+aux->head_vertex)->mark)
				relax(aux, queue);
			else{
				if((graph+aux->head_vertex)->min_cost > x->cost + aux->cost){
					(graph+aux->head_vertex)->pi = x->key;
					(graph+aux->head_vertex)->min_cost = x->cost + aux->cost;
					heap_insert((graph+aux->head_vertex)->key, (graph+aux->head_vertex)->pi, queue, (graph+aux->head_vertex)->min_cost);
				}
			}
			aux = aux->next;
		}
	}
}

vertex *rr_mark_affected(vertex *graph, edge *edge_marked, vertex *auxiliary_list, vertex *affected_list){
	
}