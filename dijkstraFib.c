#include "dijkstra.h"
#include "fib.h"

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
verticeDjk * dijkstra (int * v1, int o, int n)
{
    assert(v1);
    if(n < 1)
        return NULL;


    int v[n][n];

    int j = 0;
    int k = 0;
    int i;


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

    HeapFib * heap = makeHeapFib();
    if(!heap) return NULL;


    // Vetor que será retornado e contém o anterior do caminho
    // mínimo para cada elemento
    verticeDjk * caminhoMin = (verticeDjk *) calloc(n, sizeof(verticeDjk));

    NoHeapFib ** ptrFib = (NoHeapFib **) calloc(n, sizeof(NoHeapFib *));

    NoHeapFib * no;

    int ex;

    // O caminho mínimo pra origem partindo do próprio
    // vem dele mesmo, então o vetor caminhoMin na posição
    // 'origem' recebe a própria origem
    caminhoMin[o].predec = &caminhoMin[o];
    caminhoMin[o].verticeId = o;
    caminhoMin[o].custo = 0;

    ptrFib[o] = insereFib(heap, &caminhoMin[o]);
    if (!ptrFib[o]) return NULL;

    // ex é o vértice que será explorado, usado dentro do laço
    ex = o;
    no = extractMin(heap);

    
    while(no)
    {

        ex = no -> chave -> verticeId;


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



                if(ptrFib[i])
                {
                    /*
                     * if para verificar se o caminho encontrado para o vértice i
                     * é o menor já encontrado
                     * Se for então o caminhoMin é atualizado
                     * e visitado guarda o novo valor mínimo para o vértice
                     */
                    if((v[ex][i] + caminhoMin[ex].custo) < caminhoMin[i].custo)
                        decreaseKey(heap , ptrFib[i] ,  (v[ex][i] + caminhoMin[ex].custo), &caminhoMin[ex]);
                }

                else
                {
                    caminhoMin[i].predec = &caminhoMin[ex];
                    caminhoMin[i].verticeId = i;
                    caminhoMin[i].custo = v[ex][i] + caminhoMin[ex].custo;

                    ptrFib[i] = insereFib(heap, &caminhoMin[i]);
                        if (!ptrFib[i]) return NULL;

                }
            }

        }


        // ex recebe o índice do vértice a ser explorado

        no = extractMin(heap);

    };


    printf("Os calculos de menor caminho para a origem %d foram feitos\n", o);



    /*
     * for para imprimir a lista de camínhos mínimos para a dada origem
     */
    puts("A sua lista de caminhos mínimos é a seguinte:");

    for(i = 0; i < n; i++)
    {
        printf("%d = %d\n", i, caminhoMin[i].custo);
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
void imprimeCm(verticeDjk * Cm, int destino)
{

    assert(Cm);
    if(Cm[destino].predec -> verticeId == destino)
    {
        printf("%d", destino);
        return;
    }

    imprimeCm(Cm, Cm[destino].predec -> verticeId);

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
void shortestPath(int * v1, int origem, int destino, int n, verticeDjk ** listCm)
{
    assert(v1);
    assert(listCm);

    if(n < 1) return;

    // if confere se já existem os cálculos para essa origem
    // e apenas chama Dijkstra caso não hajam tais dados
    if(!listCm[origem])
        listCm[origem] = dijkstra(v1, origem, n);

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

 /*
int **v
v = (int**)calloc(n, sizeof(int*));
for (size_t i = 0;  < count; ++) {
    v[i] = (int*)calloc(n, sizeof(int));
}
 */

    int n = 6;
    int v[n][n];
    verticeDjk ** listCm = (verticeDjk **)malloc(sizeof(verticeDjk *)*n);
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
// floyd warsha
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
