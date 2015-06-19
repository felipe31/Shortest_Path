#include <stdio.h>
#include <stdlib.h>


int main(void)
{

/* n = numero total de elementos
 * o = origem
 * v = matriz representando o grafo
 * listCm = vetor de vetores de caminhos mínimos
 */

 
    int **v;
    int n = 2000;

    int i;
    int j;


    v = (int**)calloc(n, sizeof(int*));

    for (i = 0; i < n; i++) {

        v[i] = (int*)calloc(n, sizeof(int));
    }


    //verticeDjk ** listCm = (verticeDjk **)malloc(sizeof(verticeDjk *)*n);
    //if(!listCm) return 0;


    for(i = 0; i < n; i++)
    {
      //  listCm[i] = NULL;
    }

    //memset(v, -1, sizeof(v));

    puts("Matriz sem os valores do grafo");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", v[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");


    // Inserção dos valores das arestas
    // do grafo na matriz
    

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            v[i][j] = rand() % 2000;
        }
    }



    puts("Matriz com os valores do grafo");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", v[i][j]);

        }
        printf("\n");
    }
    puts("\nA primeira vez que cada vértice é a origem (Dijkstra é usado)\n");
}