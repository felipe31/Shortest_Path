#include "rr.h"
#define SIZE_G 5


int main(void)
{
    // Testando as funções de grafo


    vertex * g = g_create_graph(SIZE_G);

/*  ***TESTE GRAFO***
    g_print_graph(g, SIZE_G);
    g_insert_edge(g, 0, 1, 1);
    g_insert_edge(g, 0, 4, 6);
    g_insert_edge(g, 1, 2, 3);
    g_insert_edge(g, 1, 3, 2);
    g_insert_edge(g, 2, 4, 1);
    g_insert_edge(g, 3, 4, 1);
    edge * g_insert_edge(vertex *graph, int tail, int head, int cost);

*/
    g[0].heap_node.cost = 0;                                                     // Define origem
    g[0].heap_node.pi = -2;                                                     // Define origem
    g[0].pi = -2;                                                     // Define origem
    rr_add_edge(g, 0, 1, 1);
    rr_add_edge(g, 0, 4, 6);
    rr_add_edge(g, 1, 2, 3);
    rr_add_edge(g, 1, 3, 2);
    rr_add_edge(g, 2, 4, 1);
    rr_add_edge(g, 3, 4, 1);
    rr_add_edge(g, 0, 2, 1);
    g_print_graph(g, SIZE_G);
    // void rr_add_edge(vertex *graph, int tail, int head, int cost);

    // void rr_recalculate_shortest_path(vertex *graph, heap *queue);
    // void rr_remove_edge(vertex *graph, edge *edge_removed);
    // vertex *rr_mark_affected(vertex *graph, edge *edge_marked);
    // void rr_estimate_new_pi(vertex *graph, vertex *affected_list, heap *queue, edge vertex);
    // edge * find_edge_pred(vertex * head, int key);
    // edge * find_edge_adj(vertex * tail, int key);
    // edge ** find_pointer_edge_pred(vertex *head, edge *edge_ref);
    // edge ** find_pointer_edge_adj(vertex *tail, edge *edge_ref);
    // void rr_print_sssp(vertex * graph);


/*  ***TESTE HEAP***
    heap * q = heap_new();
    heap_insert((node *)&g[0], q);
    heap_insert((node *)&g[1], q);
    heap_insert((node *)&g[2], q);
    heap_insert((node *)&g[3], q);
    heap_insert((node *)&g[4], q);
    heap_print(q);

    int
    i = heap_checks_presence((node *)&g[0], q);
    printf("Posicao do node %d: %d e seu key e: %d\n", 0, i, q->node_vector[i]->key );  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    heap_update(-1, 0, q, i);

    i = heap_checks_presence((node *)&g[1], q);
    printf("Posicao do node %d: %d e seu key e: %d\n", 1, i, q->node_vector[i]->key );  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    heap_update(0,  1,q, i);

    i = heap_checks_presence((node *)&g[2], q);
    printf("Posicao do node %d: %d e seu key e: %d\n", 2, i, q->node_vector[i]->key );  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    heap_update(1,  4,q, i);

    i = heap_checks_presence((node *)&g[3], q);
    printf("Posicao do node %d: %d e seu key e: %d\n", 3, i, q->node_vector[i]->key );  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    heap_update(1,  3,q, i);

    i = heap_checks_presence((node *)&g[4], q);
    printf("Posicao do node %d: %d e seu key e: %d\n\n\n", 4, i, q->node_vector[i]->key );  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    heap_update(3,  4,q, i);

    heap_print(q);
    heap_extract(q);
    heap_print(q);

*/


    g_free_graph(&g, SIZE_G);
    g_print_graph(g, SIZE_G);

    return 0;
}
