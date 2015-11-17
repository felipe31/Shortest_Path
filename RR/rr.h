#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct edge {
    int head_vertex, cost, tail_vertex, hot_line; // tail -> head
    // hot_line = aresta faz parte do caminho mínimo
    struct edge *next;
} edge;

typedef struct vertex {
    node heap_node;
	int father, min_cost;
    int next_sp, key;
    edge *adjacent;
    edge *predecessor;
} vertex;

/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE RAMALINGAM E REPS *******************************
*************************************************************************************************
************************************************************************************************/
void rr_recalculate_shortest_path(vertex *graph, heap *queue);
void rr_add_edge(vertex *graph, edge *edge_added);
void rr_remove_edge(vertex *graph, edge *edge_removed);
vertex *rr_mark_affected(vertex *graph, edge *edge_marked);
rr_estimate_new_parents(vertex *graph, vertex *affected_list, heap *queue, vertex vertex);


/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DO GRAFO *******************************
*************************************************************************************************
************************************************************************************************/
void g_free_graph(vertex *vertices, int size);

vertex *g_create_graph(vertex *vertices, int size);

void g_show_edges(vertex *vertices, int size);

void g_print_graph(vertex *vertices, int size);

void g_insert_edge(vertex *vertices, int tail, int head, int cost);

edge *g_create_edge(int tail, int head, int cost);
