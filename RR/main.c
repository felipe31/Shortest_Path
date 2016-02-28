#include "rr.h"
#define SIZE_G 5

int main(void)
{
    // Testando as funções de grafo


    vertex * g = g_create_graph(SIZE_G);

    g_print_graph(g, SIZE_G);

    g_insert_edge(g, 1, 2, 5);
    g_insert_edge(g, 1, 5, 8);
    g_print_graph(g, SIZE_G);

    g_insert_edge(g, 1, 3, 8);

    //g_insert_edge(g, 2, 3, 5);
    //g_insert_edge(g, 4, 3, 2);
    //g_insert_edge(g, 5, 4, 1);

    g_print_graph(g, SIZE_G);

    g_free_graph(g, SIZE_G);

    g_print_graph(g, SIZE_G);

    return 0;
}
