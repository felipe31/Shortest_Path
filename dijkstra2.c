#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*
 * v = grafo em forma de matriz
 * n = qtd de vértices
 * o = origem
 */
int * Dijkstra (int v[][], int n, int o)
{

    // Vetor que será retornado e contém o anterior do caminho
    // mínimo para cada elemento
    int caminhoMin = (int *) malloc (sizeof(int) * n);

    // Lista de vértices visitados(desconhecido) e explorados
    int visitado[n];
    int explorado[n];
    int verifEx;


    int i = 0;

    while(i < n)
    {
        if(i == o)
            continue;

        visitado[i] = UINT_MAX;
        explorado[i] = -1;

        i++;
    }


    visitado[o] = 0;
    explorado[o] = o;

    caminhoMin[o] = o;

    // ex é o vértice que será explorado
    int ex = o;
    int menor = UINT_MAX;
    for(;;)
    {
        // explora os vértices que tem ligação com ex
        for(i = 0; i < n; i++)
        {
            if (v[ex][i])
            {
                if((v[ex][i] + visitado[ex]) < visitado[i])
                {
                    visitado[i] = v[ex][i] + visitado[ex];
                    caminhoMin[i] = ex;
                }
            }

        }
        explorado[ex] = ex;

        // encontra o próximo a ser explorado
        for(i = 0, menor = UINT_MAX, verifEx = 0 ; i < n; i++)
        {
            if(explorado[i] == -1)
            {
                verifEx++;
                if( visitado[i] < menor)
                    menor = i;
            }
        }


        //Condição de parada
        if( verifEx == 0)
            return caminhoMin;

        ex = menor;

    }



}
