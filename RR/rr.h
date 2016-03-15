#ifndef _RR_
#define _RR_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define HEAP_SIZE 1000


typedef struct node{
    int cost, key;                      // cost = custo mínimo no caminho mínimo | key = nome do vértice
    char mark;
} node;                                 // primeiramente usar um vetor

typedef struct heap{
    node ** node_vector;
    int control;
} heap;

typedef struct edge {
    int head_vertex, cost, tail_vertex; // tail -> head
    char hot_line;                      // hot_line = aresta faz parte do caminho mínimo
    struct edge *next_pred;             // prox na lista de predecessores
    struct edge *next_adj;              // prox na lista de adjacentes
} edge;

typedef struct vertex {
    node heap_node;
    int pi;
    edge *adjacent;                     // lista de adjacentes
    edge *predecessor;                  // lista de predecessores
} vertex;

typedef struct list{
    vertex * vtx;
    struct list * next;
} list;

typedef struct head_list
{
    list * first;
    list * last;
} head_list;

/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE RAMALINGAM E REPS *******************************
*************************************************************************************************
************************************************************************************************/
void rr_recalculate_shortest_path(vertex *graph, heap *queue);
void rr_add_edge(vertex *graph, int tail, int head, int cost);
void rr_remove_edge(vertex *graph,  int tail, int head);
head_list *rr_mark_affected(vertex *graph, edge *edge_marked);
void rr_estimate_new_pi(vertex *graph, head_list *affected_list, heap *queue);
edge * find_edge_pred(vertex * head, int key);
edge * find_edge_adj(vertex * tail, int key);
edge ** find_pointer_edge_pred(vertex *head, edge *edge_ref);
edge ** find_pointer_edge_adj(vertex *tail, edge *edge_ref);

void rr_print_sssp(vertex * graph);

/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DO GRAFO *******************************
*************************************************************************************************
************************************************************************************************/
void g_free_graph(vertex **graph, int size);

vertex *g_create_graph(int size);

void g_print_graph(vertex *graph, int size);

edge * g_insert_edge(vertex *graph, int tail, int head, int cost);


/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DO HEAP *******************************
*************************************************************************************************
************************************************************************************************/


heap * heap_new();

node * heap_extract(heap * queue);

int heap_checks_presence(node * heap_node, heap * queue);  // Retorna 0 se o nó não pertence ao heap, -1 caso haja erros e retorna a posição caso o nó pertença ao heap

void heap_update(vertex * vtx, int new_pi, int new_cost, heap * queue);

int heap_insert(node * node_to_insert, heap * queue);       // Retorna 0 se o nó foi inserido com sucesso no heap e 1 caso contrário

void heapfy(heap * queue, int i);

void heap_build(heap * queue);

void heap_print(heap * queue);

/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DE LISTA *******************************
*************************************************************************************************
************************************************************************************************/

head_list * list_new();

list * list_insert(head_list * h_list, vertex * v_list);

vertex * list_remove(head_list * h_list);


#endif
