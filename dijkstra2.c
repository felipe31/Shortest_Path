#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

/*
 * v = grafo em forma de matriz
 * n = qtd de vértices
 * o = origem
 */
int * Dijkstra (int * v1, int n, int o )
{

    assert(v1);
    if(n < 1)
        return NULL;

    int v[n][n];

    int j = 0;
    int k = 0;
    int i;

    for (i = 0; i < n * n; i++)
    {
    //    printf("%d %d = %d\n" ,j , k, *((v1 + (i % n) * n) + (i / n)));
        v[j][k] = *((v1 + (i % n) * n) + (i / n));
        k++;
        if(k == n)
        {
            k = 0;
            j++;
        }
    }



    // Vetor que será retornado e contém o anterior do caminho
    // mínimo para cada elemento
    int * caminhoMin = (int *) calloc (n, sizeof(int));

    // Lista de vértices visitados(desconhecido) e explorados
    int visitado[n];
    int explorado[n];
    int verifEx;


     i = 0;

    while(i < n)
    {
        if(i == o)
        {
            i++;
            continue;
        }

        visitado[i] = INT_MAX;
        explorado[i] = -1;

        i++;
    }

    visitado[o] = 0;
    explorado[o] = o;

    caminhoMin[o] = o;

    // ex é o vértice que será explorado
    int ex = o;
    int menor = INT_MAX;

    for(;;)
    {

        if(ex > n)
            break;
        // explora os vértices que tem ligação com ex
        for(i = 0; i < n; i++)
        {
//            puts("teste");
//            printf("ex %d   i %d    n %d\n", ex, i, n);
//            printf(" %d, %d, %d\n", v[ex][i], i, visitado[i]);
            if (v[ex][i])
            {

//                printf(" %d, %d, %d\n", v[ex][i], visitado[ex], visitado[i]);

                if((v[ex][i] + visitado[ex]) < visitado[i])
                {
                    visitado[i] = v[ex][i] + visitado[ex];
                    caminhoMin[i] = ex;


                }
            }

        }
        explorado[ex] = ex;
//        printf("%d \n", ex);

        // encontra o próximo a ser explorado
        for(i = 0, menor = INT_MAX, verifEx = 0 ; i < n; i++)
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
            break;

        ex = menor;

    }

    return caminhoMin;
}
int main(void)
{
    int n = 6;
    int o = 0;
    int v[n][n];
    int * cm;

    int i = 0;
    int j;

    memset(v, 0, sizeof(v));

    v[A][B] = 4;
    v[A][C] = 2;

    v[B][A] = 4;
    v[B][C] = 1;
    v[B][D] = 5;

    v[C][A] = 2;
    v[C][B] = 1;
    v[C][D] = 8;
    v[C][E] = 10;

    v[D][B] = 5;
    v[D][C] = 8;
    v[D][E] = 2;
    v[D][F] = 6;

    v[E][C] = 10;
    v[E][D] = 2;
    v[E][F] = 2;

    v[F][D] = 6;
    v[F][E] = 2;





    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", v[i][j]);
        }
        printf("\n");
    }



    cm = Dijkstra((int *) v, n, o);


    for(j = 0 ; j < n; j++)
    {
        printf("%d = %d\n", j, *(cm+j));
    }
    return 0;
}
