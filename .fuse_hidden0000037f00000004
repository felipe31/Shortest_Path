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

    //For para organizar a matriz
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


    // Usado como condição de parada quando verifEx = 0
    int verifEx = 0;


    //Laço para inicializar visitados com o maior valor representado por int
    // e explorado com -1 em todas as posições
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


    // O peso para ir da origem até a própria origem é zero
    // então na posição 'origem' de visitado é inserido 0
    visitado[o] = 0;


    //Começamos explorando o nó origem, então colocamos 
    //o mesmo no vetor explorado na posição origem
    explorado[o] = o;

    // O caminho mínimo pra origem partindo do próprio
    // vem dele mesmo, então o vetor caminhoMin na posição
    // 'origem' recebe a própria origem
    caminhoMin[o] = o;

    // ex é o vértice que será explorado, usado dentro do laço
    int ex = o;

    // menor é usado para encontrar o próximo a ser explorado
    int menor = INT_MAX;

    for(;;)
    {

        // Esse if nunca deverá ser verdadeiro,
        // Apenas foi colocado aqui por segurança
        if(ex > n)
            break;



        // for que explora os vértices que tem ligação com ex
        for(i = 0; i < n; i++)
        {

//            printf("teste\nex %d   i %d    n %d\n", ex, i, n);
//            printf(" %d, %d, %d\n", v[ex][i], i, visitado[i]);

            /*
             * Vértices que não tem ligação tem seu campo em comum
             * o valor de -1, portanto o if filtra para que apenas sejam
             * avaliados campos válidos (vértices que tem ligação)
             */
            if (v[ex][i] != -1)
            {

//                printf(" %d, %d, %d\n", v[ex][i], visitado[ex], visitado[i]);

  
                /* 
                 * if para verificar se o caminho encontrado para o vértice i
                 * é o menor já encontrado
                 * Se for então o caminhoMin é atualizado
                 * e visitado guarda o novo valor mínimo para o vértice 
                 */
                if((v[ex][i] + visitado[ex]) < visitado[i])
                {
                    visitado[i] = v[ex][i] + visitado[ex];
                    caminhoMin[i] = ex;

                }
            }

        }

        /* 
         * Após visitar todos os vértices com os quais ex tem ligação,
         * então colocamos ele no grupo dos vértices explorados
         */
        explorado[ex] = ex;
//        printf("%d \n", ex);


        // for que encontra o próximo a ser explorado (menor dos visitados)
        for(i = 0, menor = INT_MAX, verifEx = 0 ; i < n; i++)
        {
            /*
             * Como as posições de explorado foram iniciadas com -1
             * e a cada novo explorado o valor na posição ex muda para != -1
             * Então pode-se fazer um filtro para encontrar todos os que foram apenas visitados,
             * ou seja explorado[i] == -1, destes encontramos o menor, que será o próximo a ser explorado
             */
            if(explorado[i] == -1)
            {

                /*
                 * Caso todos já tenham sido explorados, então este if nunca será verdadeiro
                 * logo verifEx não será incrementado e será usado como condição de parada
                 */
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

        // ex recebe o índice do vértice a ser explorado
        ex = idx;

        verifEx = 0;
    }


    printf("Os calculos de menor caminho para a origem %d foram feitos\n", o);



    /* 
     * for para imprimir a lista de camínhos mínimos para a dada origem 
     */
    puts("A sua lista de caminhos mínimos é a seguinte:");

    for(i = 0; i < n; i++)
    {
        printf("%d = %d\n", i, caminhoMin[i] );
    }    
    puts("");


    return caminhoMin;
}


/*
 * Algoritmo que imprime recursivamente o
 * caminho pro destino
 *
 * Ele é chamado recusivamente até chegar na origem,
 * Onde Cm[destino] == destino, então ele retorna para a próxima chamada
 * na pilha e a cada chamada imprime o caminho.
 *
 * Sendo assim, cumprimos o objetivo
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
 * shortestPath imprime caminho mínimo para dada origem 
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

    // if confere se já existem os cálculos para essa origem
    // e apenas chama Dijkstra caso não hajam tais dados
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
 * listCm = vetor de vetores de caminhos mínimos 
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


    // Inserção dos valores das arestas
    // do grafo na matriz
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
    shortestPath((int *) v, B, E, n, listCm);
    shortestPath((int *) v, C, D, n, listCm);
    shortestPath((int *) v, D, C, n, listCm);
    shortestPath((int *) v, E, B, n, listCm);
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
