#include "rr.h"
#define SIZE_G 5


int main(void)
{
    // Testando as funções de grafo


    vertex * g = g_create_graph(SIZE_G);

    g_print_graph(g, SIZE_G);

    g_insert_edge(g, 0, 1, 1);
    g_insert_edge(g, 0, 4, 6);
    g_insert_edge(g, 1, 2, 3);
    g_insert_edge(g, 1, 3, 2);
    g_insert_edge(g, 2, 4, 1);
    g_insert_edge(g, 3, 4, 1);

    g_print_graph(g, SIZE_G);

    heap * q = heap_new();


    heap_insert((node *)&g[0], q);
    heap_insert((node *)&g[1], q);
    heap_insert((node *)&g[2], q);
    heap_insert((node *)&g[3], q);
    heap_insert((node *)&g[4], q);
    heap_print(q);
    heap_extract(q);
    // heap_checks_presence(node * heap_node, q);  // Retorna 0 se o nó não pertence ao heap e 1 caso contrário
    // heap_update(node * heap_node, int new_pi, int new_cost, q, int pos);
    heap_print(q);
    // heap_insert(node * node_to_insert, q);       // Retorna 0 se o nó foi inserido com sucesso no heap e 1 caso contrário





    g_free_graph(&g, SIZE_G);



    g_print_graph(g, SIZE_G);

    return 0;
}
