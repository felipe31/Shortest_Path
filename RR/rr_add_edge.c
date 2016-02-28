	#include "rr.h"

void rr_add_edge(vertex *graph, edge *edge_added){

	if(!graph || !edge_added)
		return;

	int tail = edge_added->tail_vertex;
	int head = edge_added->head_vertex;

	int new_cost = graph[tail]->min_cost + edge_added->cost;

	edge_added->next_adj = graph[tail].adjacent;
	graph[tail].adjacent = edge_added;

	edge_added->next_pred = graph[head].predecessor;
	graph[head].predecessor = edge_added;

	if (graph[head]->min_cost <= new_cost)
		return;

	heap * queue = heap_new();

	heap_insert(head, tail, queue, new_cost)
	rr_recalculate_shortest_path(graph, queue);

    return;
}
