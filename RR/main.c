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

    g_free_graph(&g, SIZE_G);



    g_print_graph(g, SIZE_G);

    return 0;
}
