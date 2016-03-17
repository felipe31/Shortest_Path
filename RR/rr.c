/* Alone*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rr.h"

/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE RAMALINGAM E REPS *******************************
*************************************************************************************************
************************************************************************************************/


void rr_recalculate_shortest_path(vertex *graph, heap *queue)
{
	if(!graph)
		return;

	node * min = NULL;
	edge * edge_aux, * edge_p;
	int pos;

	while(queue->control)
	{
		min = heap_extract(queue);
		if(!min) return;
		if(((vertex *) min)->pi != -2)												// -2 indica que o nó é a origem
		{
			edge_aux = find_edge_pred((vertex *) min, ((vertex *) min)->pi);
			if(!edge_aux) return;
			edge_aux->hot_line = 1;
		}
		edge_aux = ((vertex *) min)->adjacent;

		while(edge_aux)
		{
			if(((node *)(graph + edge_aux->head_vertex))->mark == 1)
			{
				if(graph[edge_aux->head_vertex].heap_node.cost > min->cost + edge_aux->cost )									//relax();
					heap_update((graph + edge_aux->head_vertex), min->key, min->cost + edge_aux->cost, queue);
			}
			else
			{
				if(graph[edge_aux->head_vertex].heap_node.cost > min->cost + edge_aux->cost)
				{
					edge_p = find_edge_pred(graph+edge_aux->head_vertex, graph[edge_aux->head_vertex].pi);
					if(edge_p) edge_p->hot_line = 0;

					graph[edge_aux->head_vertex].heap_node.cost = min->cost + edge_aux->cost;
					graph[edge_aux->head_vertex].pi = min->key;
					if(heap_insert((node *) &graph[edge_aux->head_vertex], queue))
						printf("No %d nao inserido\n", edge_aux->head_vertex);
				}
			}
			edge_aux = edge_aux->next_adj;
		}
	}
}


void rr_add_edge(vertex *graph, int tail, int head, int cost){

	if(!graph) return;

	edge * edge_added = g_insert_edge(graph, tail, head, cost);

	int new_cost = graph[tail].heap_node.cost + edge_added->cost;

	if (graph[head].heap_node.cost <= new_cost)
		return;

	heap * queue = heap_new();
	if(!queue) return;

	edge_added->hot_line = 1;
	edge_added = find_edge_pred(graph+head, graph[head].pi);
	if(edge_added)
		edge_added->hot_line = 0;
	graph[head].heap_node.cost = new_cost;
	graph[head].pi = tail;

	if(heap_insert((node *)(graph + head), queue))
		printf("No %d nao inserido\n", graph[head].heap_node.key);

	rr_recalculate_shortest_path(graph, queue);

    return;
}



void rr_remove_edge(vertex *graph, int tail, int head)
{
 	heap *queue = heap_new();
	if(!queue) return;

	edge * edge_removed = find_edge_adj(graph+tail, head);
	edge ** edge_adj = find_pointer_edge_adj(graph+tail, edge_removed );
	edge ** edge_pred = find_pointer_edge_pred(graph+head, edge_removed );
	if(!edge_adj || !edge_pred)	return;

	*edge_adj = edge_removed->next_adj;
	*edge_pred = edge_removed->next_pred;

	if(edge_removed->hot_line == 0)
	{
		free(edge_removed);
		return;
	}

	edge_removed->hot_line == 0;
	head_list *affected_list = rr_mark_affected(graph, edge_removed);

    rr_estimate_new_pi(graph, affected_list, queue);
    rr_recalculate_shortest_path(graph, queue);

    free(edge_removed);
	return;
}

head_list *rr_mark_affected(vertex *graph, edge *edge_marked)
{
	if(!graph || !edge_marked) return NULL;

	head_list * aux_list = list_new();
	head_list * affected_list = list_new();

	graph[edge_marked->head_vertex].heap_node.cost = INT_MAX;
	graph[edge_marked->head_vertex].pi = -3;
	list_insert(aux_list, graph+edge_marked->head_vertex);

	vertex * vtx;
	edge * edge_aux;
	while (aux_list->first)
	{
		vtx = list_remove(aux_list);

		list_insert(affected_list, vtx);

		edge_aux = vtx->adjacent;
		while(edge_aux)
		{
			if(edge_aux->hot_line)
			{
				edge_aux->hot_line = 0;
				graph[edge_aux->head_vertex].heap_node.cost = INT_MAX;
				graph[edge_aux->head_vertex].pi = -3;					// -3 indica que o nó foi afetado e está na lista

				list_insert(aux_list, graph+edge_aux->head_vertex);
//				break;
			}

			edge_aux = edge_aux->next_adj;
		}

	}
	return affected_list;

}
void rr_estimate_new_pi(vertex *graph, head_list *affected_list, heap *queue)
{
	if(!graph || !affected_list || !queue) return;

	vertex * vtx;
	edge * edge_aux;
	while(affected_list->first)
	{
		vtx = list_remove(affected_list);
		edge_aux = vtx -> predecessor;
		while (edge_aux)
		{
			if((graph+edge_aux->tail_vertex)->pi != -3)							// -3 indica que o nó foi afetado e está na lista
			{
				if(vtx->heap_node.cost > graph[edge_aux->tail_vertex].heap_node.cost + edge_aux->cost )
				{
					vtx->heap_node.cost = graph[edge_aux->tail_vertex].heap_node.cost + edge_aux->cost;
					vtx->pi = edge_aux->tail_vertex;
				}
			}
			edge_aux = edge_aux->next_pred;
		}
		if(vtx->heap_node.cost < INT_MAX)
			heap_insert((node *)vtx, queue);
	}

	return;
}


void rr_print_sssp(vertex * graph)
{

}

edge ** find_pointer_edge_adj(vertex *tail, edge *edge_ref)
{
	edge * edge_p = tail->adjacent;

	if(edge_p == edge_ref)
		return &tail->adjacent;

	while(1)
	{
		if (edge_p->next_adj == edge_ref)
		{
			break;
		}
		else if(edge_p->next_adj == NULL)
		{
			return NULL;
		}

		edge_p = edge_p->next_adj;
	}

	return &edge_p->next_adj;
}

edge ** find_pointer_edge_pred(vertex *head, edge *edge_ref)
{
	edge * edge_p = head->predecessor;

	if(edge_p == NULL)
		return NULL;

	if(edge_p == edge_ref)
		return &head->predecessor;

	while(1)
	{
		if (edge_p->next_pred == edge_ref)
		{
			break;
		}
		else if(edge_p->next_pred == NULL)
		{
			return NULL;
		}

		edge_p = edge_p->next_pred;
	}

	return &edge_p->next_pred;
}


edge * find_edge_adj(vertex * tail, int key)
{
	edge * edge_adj = tail->adjacent;

	if(edge_adj == NULL)
		return NULL;

	while(edge_adj->head_vertex != key)
	{
		edge_adj = edge_adj->next_adj;

		if(edge_adj == NULL)
			return NULL;
	}

	return edge_adj;
}

edge * find_edge_pred(vertex * head, int key)
{
	edge * edge_pred = head->predecessor;

	if(edge_pred == NULL || key == -1)
		return NULL;

	while(edge_pred->tail_vertex != key)
	{
		edge_pred = edge_pred->next_pred;

		if(edge_pred == NULL)
			return NULL;
	}

	return edge_pred;
}


/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DO GRAFO *******************************
*************************************************************************************************
************************************************************************************************/

void g_free_graph(vertex **graph, int size)
{
	if(!(*graph) || size < 1) return;
	int i;
	edge * edge_aux;

	for (i = 0; i < size; i++)
	{
		edge_aux = (*graph)[i].adjacent;
		while(edge_aux)
		{
			(*graph)[i].adjacent = (*graph)[i].adjacent->next_adj;
			free(edge_aux);
			edge_aux = (*graph)[i].adjacent;
		}
	}
	free(*graph);
	*graph = NULL;
}

vertex *g_create_graph(int size)
{
	if(size < 1) return NULL;

	vertex * graph = (vertex *) calloc(size, sizeof(vertex));
	if(!graph) return NULL;

	for (; size > 0; --size)
	{
		graph[size-1].heap_node.key = size-1;
		graph[size-1].heap_node.cost = INT_MAX;
		graph[size-1].pi = -1;

	}

	return graph;
}

void g_print_graph(vertex *graph, int size)
{

	if(!graph || size < 1)
	{
		puts("Grafo invalido ou vazio!");
		return;
	}
	int i;
	edge * edge_aux;

	for(i = 0; i < size; ++i)
	{
		edge_aux = graph[i].adjacent;
		printf("Vertice\t\t%d\npi:\t\t%d\ncost:\t\t%d\narestas:\t", i, graph[i].pi, graph[i].heap_node.cost);

		while(edge_aux)
		{
			printf("%d {cost %d, sp %d} - ", edge_aux->head_vertex, edge_aux->cost, edge_aux->hot_line );
			edge_aux = edge_aux->next_adj;
		}

		printf("NULL\n---------------------------------------------------------------\n");
	}

	puts("\n");
}


edge * g_insert_edge(vertex *graph, int tail, int head, int cost)
{
	if(!graph) return NULL;

	edge * edge_added = (edge *) calloc(1, sizeof(edge));

	if(edge_added)
	{
		edge_added->head_vertex = head;
		edge_added->tail_vertex = tail;
		edge_added->cost = cost;
		edge_added->hot_line = 0;

		edge_added->next_adj = graph[tail].adjacent;
		graph[tail].adjacent = edge_added;

		edge_added->next_pred = graph[head].predecessor;
		graph[head].predecessor = edge_added;
	}

	return edge_added;

}


/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DO HEAP *******************************
*************************************************************************************************
************************************************************************************************/

heap * heap_new()
{
	heap * new_heap = (heap *) calloc(1, sizeof(heap));
	if(new_heap)
	{
		new_heap->node_vector = (node **) calloc(HEAP_SIZE, sizeof(node *));
		new_heap->control = 0;
	}

	return new_heap;

}

node * heap_extract(heap * queue)
{
	if(!queue) return NULL;

	node * extracted = queue->node_vector[0];
	queue->control--;
	if(queue->control > 0)
	{
		queue->node_vector[0] = queue->node_vector[queue->control];
		heapfy(queue, 0);
	}

	extracted->mark = 0;
	return extracted;
}

int heap_checks_presence(node * heap_node, heap * queue)  	// Retorna 0 se o nó não pertence ao heap,
{															// -1 caso haja erros e retorna a posição caso o nó pertença ao heap
	if(!queue || !heap_node) return -1;

	node ** vector = queue->node_vector;
	int i;

	for (i = 0; i < queue->control; ++i)
	{
		if(vector[i] == heap_node)
			return i;
	}
	return 0;
}

void heap_update(vertex * vtx, int new_pi, int new_cost, heap * queue)
{
	vtx->pi = new_pi;
	vtx->heap_node.cost = new_cost;
	heap_build(queue);
}

int heap_insert(node * node_to_insert, heap * queue)       // Retorna 0 se o nó foi inserido com sucesso no heap e -1 caso contrário
{
	if(!queue || !node_to_insert) return -1;
	if(queue->control == HEAP_SIZE) return -1;

	node_to_insert->mark = 1;
	queue->node_vector[queue->control] = node_to_insert;
	queue->control++;
	heap_build(queue);
	return 0;
}

void heapfy(heap * queue, int idx)
{
	int l_child, r_child, smallest;
	node * aux;

	l_child = 2 * idx + 1;
	r_child = 2 * idx + 2;
	if ((l_child < queue->control)  && ((queue->node_vector[l_child])->cost < (queue->node_vector[idx])->cost))
		smallest = l_child;
	else
		smallest = idx;
	if ((r_child < queue->control)  && ((queue->node_vector[r_child])->cost < (queue->node_vector[smallest])->cost))
		smallest = r_child;
	if (smallest != idx)
	{
		aux = queue->node_vector[smallest];
		queue->node_vector[smallest] = queue->node_vector[idx];
		queue->node_vector[idx] = aux;

		heapfy(queue, smallest);
	}
	return;
}

void heap_build(heap * queue)
{
	int i;
	for (i = (queue->control-2)/2; i > -1 ; i--)
		heapfy(queue, i);

	return;
}
/*
void heap_build(queue)
{
	int pos = queue->control;
	int pos_parent = (queue->control-1)/2;
	node * swap;


	while(pos_parent > -1)
	{
		if(queue->node_vector[pos]->cost < queue->node_vector[pos_parent]->cost)
		{
			swap = queue->node_vector[pos];
			queue->node_vector[pos] = queue->node_vector[pos_parent];
			queue->node_vector[pos_parent] = swap;

			pos = pos_parent;
			pos_parent = (pos-1)/2;
			continue;
		}
		break;
	}

}
*/

void heap_print(heap * queue)
{
	int i;
	if(!queue)
		printf("Heap invalido\n");
	else if(queue->control)
	{
		for ( i = 0; i < queue->control; i++)
		{
			printf("Elemento %d:\ncost:\t%d\npi:\t%d\nkey:\t%d\n\n", i, (queue->node_vector[i])->cost, ((vertex *)(queue->node_vector[i]))->pi, (queue->node_vector[i])->key);
		}
	}
	else
		printf("Heap vazio!\n\n");

		puts("\n");
	return;
}


/************************************************************************************************
*************************************************************************************************
****************************** ALGORITMOS DE MANIPULAÇÃO DE LISTA *******************************
*************************************************************************************************
************************************************************************************************/

head_list * list_new()
{
	return (head_list *) calloc(1, sizeof(head_list));
}

list * list_insert(head_list * h_list, vertex * v_list)
{
	if(!h_list || !v_list) return NULL;

	list * l = (list *) calloc(1, sizeof(list));
	if(l)
	{
		l->vtx = v_list;
		if(h_list -> last)
			h_list -> last -> next = l;
		else
			h_list->first = l;
		h_list -> last = l;
	}
	return l;
}

vertex * list_remove(head_list * h_list)
{
	if(!h_list) return NULL;
	if(!h_list->first) return NULL;

	vertex * vtx = h_list->first->vtx;
	list * aux = h_list->first;

	h_list->first = h_list->first->next;

	if(!h_list->first)
		h_list->last = NULL;

	free(aux);
	return vtx;
}
