#include "fib.h"
#include "math.h"
//http://www.sanfoundry.com/cpp-program-implement-fibonacci-heap/
/*---------------------------------------------- INICIALIZAR ----------------------------------------------*/

HeapFib * makeHeapFib()
{
	HeapFib * heap = (HeapFib *) malloc(sizeof(HeapFib));
	if(!heap) return NULL;

	heap -> noMin = NULL;
	heap -> qtdNos = 0;

	return heap;

}


/*---------------------------------------------- CRIA NÓ ----------------------------------------------*/
NoHeapFib * criaNoFib(int custo)
{
	NoHeapFib * no = (NoHeapFib *) malloc(sizeof(NoHeapFib));
	if(!no) return NULL;

	no->pai = NULL;
	no->filho = NULL;
	no->custo = custo;
	no->grau = 0;
	no->marca = 0;
	no->esq = no->dir = no;

	return no;
}


/*---------------------------------------------- IMPRIMIR ----------------------------------------------*/

void imprimir( NoHeapFib* no){
	NoHeapFib * aux = no;

	do
	{
		printf("%d ", no->custo);

		if (no->aux)
		{
			printf("V ");
			imprimir(no->aux);
			printf("ˆ ");

		}

		no = no->dir;

		if(no != aux)
			printf("-> ");


	}while(no != aux);
}


void imprimirHeapFib(HeapFib* H){
	printf("\n");

	if(!H->noMin)
	{	
		printf("Heap vazio\n");
		return;
	}
	else 
	{
		printf("Itens do Heap\n");
		imprimir(H->noMin);
	}

	puts("\n");
}


/*---------------------------------------------- INSERIR ----------------------------------------------*/

NoHeapFib * insereFib(HeapFib* H, int custo){
	assert(H);

	NoHeapFib * no = criaNoFib(custo);
	if(!no) return NULL;
	no->filho = NULL;
	
	return insereFibNoPronto(H, no);
}

/*
 * Considera-se que os filhos do nó a ser inserido já estão devidamente corretos
 */
NoHeapFib * insereFibNoPronto(HeapFib* H, NoHeapFib* no){
	assert(H);
	assert(no);
	
	if (H->noMin == NULL){
		H->noMin = no;
		no->esq = no->dir = no;
	}

	else{
		no->esq = H->noMin->esq;
		H->noMin->esq = no;
		no->esq->dir = no;
		no->dir = H->noMin;
	}

	no->pai = NULL;
	no->marca = 0;
	H->qtdNos++;

	if (no->custo < H->noMin->custo)
		H->noMin = no;

	return no;

}




/*---------------------------------------------- EXTRAIR ----------------------------------------------*/

void heapFibLink(HeapFib * H, NoHeapFib * y, NoHeapFib * x)
{
	assert(H);

/*********************** Remove Y da lista de raizes ***********************/
	(y -> dir) -> esq = y -> esq;
	(y -> esq) -> dir = y -> dir;

	if(H -> noMin == y)
		H -> noMin = x;

/*********************** Y vira filho de X ***********************/

	if(x -> filho == NULL)
	{
	 	x -> filho = y;
	 	y -> esq = y -> dir = y;

	}

	else
	{
	 	y -> dir = x -> filho;
	 	((x -> filho) -> esq) -> dir = y;
	 	y -> esq = (x -> filho) -> esq;
	 	(x -> filho) -> esq = y;

	}


	(x -> grau)++;

	y -> marca = 0;
	y -> pai = x;
}


void consolidar(HeapFib * H){
	assert(H);
	
	int d = H->qtdNos; //(log(H->qtdNos))/(log(1.61803));

	//printf("qtdNos: %d\nd: %d", H->qtdNos, d );

	NoHeapFib **a = (NoHeapFib **) calloc(d, sizeof(NoHeapFib *));
	int i, grau;
	NoHeapFib * y, * troca, * x;

	y = troca = NULL;
 	x = H->noMin;



	do{

		grau = x->grau;

		while(a[grau])
		{
			y = a[grau];

			if (x->custo > y->custo)
			{

				troca = x;
				x = y;
				y = troca;

			}
			
			heapFibLink(H, y, x);
			
			if(x->dir == x || H->noMin == y)
				H->noMin = x;

			a[grau] = NULL;
			grau = x->grau;

		}

		a[grau] = x;


		//x = x->dir;

	}while(x != H -> noMin);


	H->noMin = NULL;

	for(i = 0; i < d; i++)
	{
		if(a[i])
		{
			if(!(H->noMin))
			{
				H->noMin = a[i];
				a[i]->esq = a[i];
				a[i]->dir = a[i];
			}
			else
			{
				a[i]->esq  = H->noMin->esq;		
				(H -> noMin) -> esq = a[i];
				a[i] -> dir = (H -> noMin);

				(a[i] -> esq) -> dir = a[i];


				if(a[i] -> custo < (H -> noMin) -> custo)
					H -> noMin = a[i];

			}
		}
	}

}


NoHeapFib * extractMin(HeapFib * H)
{
	assert(H);

	NoHeapFib * noExtraido = H->noMin;
	NoHeapFib * filho;
	NoHeapFib * aux = NULL;


	if(noExtraido != NULL)
	{

		filho = noExtraido->filho;

		if(filho)
		{
/*********************** Insere todos os filhos de noExtraido na lista de raizes ***********************/

			aux = filho;
			
			do
			{
				aux->pai= NULL;
				aux = aux->dir;


			}while(aux != filho);

			filho->esq->dir = noExtraido->dir;
			noExtraido->dir->esq = filho->esq;

			filho->esq = noExtraido;
			noExtraido->dir = filho;
			noExtraido -> filho = NULL;

		}
/*********************** Remove noExtraido da lista de raizes ***********************/

		if(noExtraido == noExtraido -> dir)
			H->noMin = NULL;
		
		else
		{
			
			noExtraido->esq->dir = noExtraido->dir;
			noExtraido->dir->esq = noExtraido->esq;

			H->noMin = noExtraido->dir;
	//imprimirHeapFib(H);
			consolidar(H);
	puts("\ndepoisi\n");
	imprimirHeapFib(H);
		}

		H->qtdNos--;


	}

	return noExtraido;
}


/*---------------------------------------------- ATUALIZAR ----------------------------------------------*/

void cut(HeapFib* H, NoHeapFib* x, NoHeapFib* y)
{
    assert(H);
    assert(x);
    assert(y);

    if(y -> filho == x)
    {
        if(x -> dir == x)
        {
            y -> filho = NULL;
        }
        else
        {
            y -> filho = x -> dir;
        }
    }

    (x -> esq) -> dir = x -> dir;
    (x -> dir) -> esq = x -> esq;
    y -> grau--;

    x -> pai = NULL;
    x -> marca = 0;

    insereFibNoPronto(H, x);
}

void cascadingCut(HeapFib* H, NoHeapFib* y)
{
    assert(H);
    assert(y);

    NoHeapFib* z = y -> pai;

    if(z != NULL)
    {
        if(!y->marca)
            y->marca = 1;
        else
        {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}


void decreaseKey(HeapFib* H, NoHeapFib* x , int k)
{
    assert(H);
    assert(x);

    if(k > x ->  custo) 
    {
        printf("Nova chave é maior que chave atual");
        return;
    }

    x -> custo = k;

    NoHeapFib * y = x->pai;

    if(y != NULL && x -> custo < y -> custo)
    {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if(H->noMin == NULL) H->noMin = x;
    else if(x->custo < (H->noMin)->custo) H->noMin = x;
}
