#include "rr.h"
#include <limits.h>
#define infinity INT_MAX

typedef struct node {
  vertex *v;
  struct node *next;
}list_node;


vertex *remove_last_list(list_node **r){
	if(*r) return NULL;
	while(*r->next){
		r = *r;
	}
	list_node *aux = *r->next;
	free(*r->next);
	*r->next = null;
	return aux;
}

void rr_recalculate_shortest_path(vertex *graph, heap *queue){
	node *x;
	while(queue){
		x = heap_extract_min(queue);
		(graph+x->key)->pi = x->pi;
		(graph+x->key)->min_cost = x->cost;
		 edge *aux;// = (graph+x->key)->predecessor;
		// while(aux){
		// 	aux->hot_line = 0;
		// 	aux = aux->next_pred;
		// }
		aux = (graph+x->pi)->adjacent;
		while(aux){
			if(aux->head_vertex == x->key){
				aux->hot_line = 1;

				break;
			}
			aux = aux->next_adj;
		}
		aux = (graph+x->key)->adjacent;
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
			aux = aux->next_adj;
		}
	}
}

vertex *rr_mark_affected(vertex *graph, edge *edge_marked, vertex *auxiliary_list, vertex *affected_list){
	auxiliary_list = graph[edge_marked->head_vertex];

	vertex *aux = auxiliary_list;
	while(auxiliary_list){
		while(aux->){}
	}

}
void insert_list(auxiliary_list, graph[edge_marked->head_vertex]); // INSERE O VERTICE v, DA ARESTA u->v NA LISTA AUXILIAR
	vertex *v;		//	VARIAVEIS AUXILIARES{
	edge *e1;		//
	edge *e2;		//
	int flag = 0;	//	}
	while(auxiliary_list){	//	ENQUANTO EXISTIR ELEMENTOS NA LISTA AUXILIAR, FAÇA...
		v = remove_last_list(auxiliary_list);	//	REMOVE O ULTIMO DA LISTA AUXILIAR
		insert_list(affected_list, v);	//	INSERE O VERTICE, REMOVIDO ANTERIORMENTE, NA LISTA AFETADOS
		e1 = v->adjacent;
		while(e1){	//	PARA CADA VERTICE w SUCESSOR DE v (PERTENCENTE AO SUBGRAFO DE CAMINHOS MINIMOS, GARANTIDO NA PROXIMA LINHA), FAÇA...
			if(e1->hot_line){	//	VERIFICA SE A ARESTA v->w PERTENCE AO SUBGRAFO DE CAMINHOS MINIMOS
				e1->hot_line = 0;	//	SE FOR CAMINHO MINIMO, TIRA DOS CAMINHOS MINIMOS
				e2 = graph[e1->head_vertex]->predecessor;
				while(e2){	//	PASSA POR TODOS OS PREDECESSORES DE w
					if(e2->hot_line){	//	SE EXISTIR PELO MENOS UM PREDECESSOR DE w, QUE PERTENCE AO CONJUNTO DE CAMINHO MINIMOS, FAÇA...
						flag = 1;	// SINALIZA QUE EXISTE UM PREDECESSOR DE w PERTENCENTE AO CONJUNTO DE CAMINHOS MINMOS
						break;		// ACABA A PROCURA
					}
					e2 = e2->next_pred;	//	SE NÃO FOR CAMINHO MINIMO,
					continue;			//	VERIFICA A PROXIMA ARESTA
				}
				if(!flag){	//	SE NÃO FOI ENCONTRADO UM PREDECESSOR DE w QUE PERTENCE AO CONJUNTO DE CAMINHOS MINIMOS
					insert_list(auxiliary_list, graph[e1->head_vertex]);
				}
			}
			e1 = e1->next_adj;	// SE NÃO É CAMINHO MINIMO,
		}
	}
	return affected_list;
}
