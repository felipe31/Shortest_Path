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


verticeDjk * dijkstra (int ** v, int o, int n)
{
    assert(v);
    if(n < 1)
        return NULL;

    int i;

    HeapFib * heap = makeHeapFib();
    if(!heap) return NULL;




    // Vetor que será retornado e contém o anterior do caminho
    // mínimo para cada elemento
    verticeDjk * caminhoMin = (verticeDjk *) calloc(n, sizeof(verticeDjk));

    //NoHeapFib ** ptrFib = (NoHeapFib **) calloc(n, sizeof(NoHeapFib *));

    NoHeapFib * no;

    int ex;

    // O caminho mínimo pra origem partindo do próprio
    // vem dele mesmo, então o vetor caminhoMin na posição
    // 'origem' recebe a própria origem
    caminhoMin[o].predec = &caminhoMin[o];

    caminhoMin[o].verticeId = o;

    caminhoMin[o].noFib = (NoHeapFib *) malloc(sizeof(NoHeapFib));
    if(!caminhoMin[o].noFib) return NULL;

    caminhoMin[o].noFib -> custo = 0;

    insereFibNoPronto(heap, caminhoMin[o].noFib);
    
    no = extractMin(heap);

    while(no)
    {

        ex = no->custo;

        // for que explora os vértices que tem ligação com ex
        for(i = 0; i < n; i++)
        {

            if (v[ex][i] != -1)
            {

                /*
                 * if para verificar se o caminho encontrado para o vértice i
                 * é o menor já encontrado
                 * Se for então o caminhoMin é atualizado
                 * e visitado guarda o novo valor mínimo para o vértice
                 */
                if(caminhoMin[i].noFib){

                    if((v[ex][i] + caminhoMin[ex].noFib -> custo) < caminhoMin[i].noFib -> custo){
                        
                        decreaseKey(heap , caminhoMin[i].noFib,  (v[ex][i] + caminhoMin[ex].noFib -> custo), &caminhoMin[ex]);
                    }
                }

                else
                {

                        caminhoMin[i].predec = &caminhoMin[ex];
                        caminhoMin[i].verticeId = i;
                       
                        caminhoMin[i].noFib = (NoHeapFib *) malloc(sizeof(NoHeapFib));
                        if(!caminhoMin[i].noFib) return NULL;
    
                        caminhoMin[i].noFib -> custo = v[ex][i] + caminhoMin[ex].noFib -> custo;

                        insereFibNoPronto(heap, caminhoMin[i].noFib);
                }

            }

        }


        // ex recebe o índice do vértice a ser explorado
  
        no = extractMin(heap);
    }

    printf("Os calculos de menor caminho para a origem %d foram feitos\n", o);



    /*
     * for para imprimir a lista de camínhos mínimos para a dada origem
     */
    puts("A sua lista de caminhos mínimos é a seguinte:");

    for(i = 0; i < n; i++)
    {
        printf("%d = %d\n", i, caminhoMin[i].noFib -> custo);
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
void shortestPath(int ** v, int origem, int destino, int n, verticeDjk ** listCm)
{
    assert(v);
    assert(listCm);

    if(n < 1) return;


    // if confere se já existem os cálculos para essa origem
    // e apenas chama Dijkstra caso não hajam tais dados
    //if(!listCm[origem])
        listCm[origem] = dijkstra(v, origem, n);

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

 
    int **v;
    int n = 10 ;

    int i;
    int j;


    v = (int**)calloc(n, sizeof(int*));

    for (i = 0; i < n; i++) {

        v[i] = (int*)calloc(n, sizeof(int));
    }


    verticeDjk ** listCm = (verticeDjk **)calloc(n, sizeof(verticeDjk *));
    if(!listCm) return 0;


    for(i = 0; i < n; i++)
    {
        listCm[i] = NULL;
    }

    //memset(v, -1, sizeof(v));
/*
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
*/

    // Inserção dos valores das arestas
    // do grafo na matriz

    int i2 = 0;

    for (i = 0; i < n; ++i)
    {
        for (j = 0 + i2++ ; j < n; ++j)
        {
            if(i == j)
            v[i][j] = v[j][i] = 0;

            else
            v[i][j] = v[j][i] = 1+ (int)(rand() % 9) ;

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

// floyd warshall

    shortestPath(v, 0, 1, n, listCm);   



    //puts("\nA segunda vez que cada vértice é a origem (valores já foram calculados)\n");

    //Repetição das origens com outras saídas

    //shortestPath((int *) v, A, F, n, listCm);
    
    return 0;
}
