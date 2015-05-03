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
int * Dijkstra (int * v1, int o, int n)
{


    assert(v1);
    if(n < 1)
        return NULL;


    int v[n][n];

    int j = 0;
    int k = 0;
    int i;
    int idx;

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


    int verifEx = 0;


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
            if (v[ex][i] != -1)
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
                {
                    menor = visitado[i];
                    idx = i;
                }
            }
        }


        //Condição de parada
        if( verifEx == 0)
            break;


        ex = idx;

        verifEx = 0;
    }


    printf("Os calculos de menor caminho para a origem %d foram feitos\n", o);

/*
    for(i = 0; i < n; i++)
    {
        printf("%d = %d\n", i, caminhoMin[i] );
    }    
*/

    return caminhoMin;
}


/* Algoritmo que imprime recursivamente o
 * caminho pro destino
 * ele para de imprimir quando encontrar índice igual ao valor
 */
void imprimeCm(int * Cm, int destino)
{

    assert(Cm);
    if(Cm[destino] == destino)
    {
        printf("%d", destino);
        return;
    }

    imprimeCm(Cm, Cm[destino]);

    printf(" -> %d", destino );

    return;

}



/*
 * shortestPath imprime mínimo para dada origem 
 * e dado destino, sendo que:
 *
 * n = numero total de elementos
 * listCm = lista de caminhos mínimos
 *
 *
 * Recebe as informações necessárias e guarda
 * os cálculos pra eles não precisarem ser 
 * refeitos.
 *
 * Se já existirem, apenas consulta.
 *
 */
void shortestPath(int * v1, int origem, int destino, int n, int ** listCm)
{


    assert(v1);
    assert(listCm);


    if(n < 1) return;

    if(!listCm[origem])
        listCm[origem] = Dijkstra(v1, origem, n);

    imprimeCm(listCm[origem], destino);
    puts("");

    return;
}


int main(void)
{

/* n = numero total de elementos
 * o = origem 
 * v = matriz representando o grafo
 * listCm = veotor de caminhos mínimos 
 */

    int n = 6;
    int o = 0;
    int v[n][n];
    int ** listCm = (int **)malloc(sizeof(int *)*n);
    if(!listCm) return 0;


    int i;
    int j;


    for(i = 0; i < n; i++)
    {
        listCm[i] = NULL;
    }

    memset(v, -1, sizeof(v));
    
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

    shortestPath((int *) v, A, F, n, listCm);
    shortestPath((int *) v, B, A, n, listCm);
    shortestPath((int *) v, C, E, n, listCm);
    shortestPath((int *) v, D, A, n, listCm);
    shortestPath((int *) v, E, A, n, listCm);
    shortestPath((int *) v, F, A, n, listCm);

    puts("\nA segunda vez que cada vértice é a origem (valores já foram calculados)\n");

    //Repetição das origens com outras saídas

    shortestPath((int *) v, A, F, n, listCm);
    shortestPath((int *) v, B, E, n, listCm);
    shortestPath((int *) v, C, D, n, listCm);
    shortestPath((int *) v, D, C, n, listCm);
    shortestPath((int *) v, E, B, n, listCm);
    shortestPath((int *) v, F, A, n, listCm);
    
    return 0;
}
