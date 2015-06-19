#include "fib.h"

/*---------------------------------------------- INICIALIZAR ----------------------------------------------*/

HeapFib * makeHeapFib()
{
	HeapFib * heap = (HeapFib *) malloc(sizeof(HeapFib));
	if(!heap) return NULL;

	heap -> noMin = NULL;
	heap -> qtdNos = 0;

	return heap;

}


/*---------------------------------------------- IMPRIMIR ----------------------------------------------*/

int G = 0;
void imprimir( NoHeapFib* No, NoHeapFib * pai){
	printf("Elemento %d: %d   ", G++,  No == NULL ? INT_MIN : No -> custo);

/*	if( No->filho != NULL){
		imprimir( No->filho, No->filho);
	}
*/
	if( No->dir != pai){
		imprimir( No->dir, pai);
	}
}


void imprimirHeapFib(HeapFib* H){
	G = 1;
	if(H -> noMin)
		imprimir(H->noMin, H->noMin);
	else 
		printf("Heap vazio!");

	puts("");
}	



/*---------------------------------------------- INSERIR ----------------------------------------------*/

NoHeapFib * insereFib(HeapFib* H, int custo){
	assert(H);

	NoHeapFib* novoNo = (NoHeapFib*) malloc( sizeof( NoHeapFib));
	if(novoNo == NULL) return novoNo;

	novoNo->pai = NULL;
	novoNo->filho = NULL;
	novoNo->custo = custo;
	novoNo->grau = 0;
	novoNo->marca = 0; 


	if ( H->noMin == NULL){
		novoNo->esq = novoNo;
		novoNo->dir = novoNo;
		H->noMin = novoNo;
	}
	else{
		novoNo->esq = (H -> noMin)->esq;
		(H -> noMin)->esq = novoNo;
		novoNo->dir = (H -> noMin);
		(novoNo->esq)->dir = novoNo;

		if ( custo < (H -> noMin) -> custo){
			(H -> noMin) = novoNo;
		}
	}

	(H -> qtdNos)++;
	return novoNo;
}
//int dragonball = 0;

NoHeapFib * insereFibNoPronto(HeapFib* H, NoHeapFib* No){
	assert(H);
	assert(No);
    
//    printf("%d insere ", dragonball++);

	if (H->noMin == NULL){
		H->noMin = No;
		No->esq = No->dir = No;
	}

	else{
		No->esq = H->noMin->esq;
		H->noMin->esq = No;
		No->esq->dir = No;
		No->dir = H->noMin;
	}

	No->pai = NULL;
	No->filho = NULL;
	No->marca = 0;
	H->qtdNos++;

	if (No->custo < H->noMin->custo)
		H->noMin = No;

	return No;

}




/*---------------------------------------------- EXTRAIR ----------------------------------------------*/

void heapFibLink(HeapFib * H, NoHeapFib * y, NoHeapFib * x)
{
	assert(H);

/*********************** Remove Y da lista de raizes ***********************/
	if (H -> noMin == y)
		H -> noMin = y -> dir;

	(y -> dir) -> esq = y -> esq;
	(y -> esq) -> dir = y -> dir;


/*********************** Y vira filho de X ***********************/

	if(x -> filho == NULL)
	{
	 	x -> filho = y;
	 	y -> esq = y;
	 	y -> dir = y;

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
	
	NoHeapFib **a = (NoHeapFib **) calloc(H->qtdNos, sizeof(NoHeapFib *));
	int i, grau;
	NoHeapFib * y, * troca, * x = H->noMin;

	do{

		grau = x->grau;

		while(a[grau]){
			y = a[grau];
			if (x->custo > y->custo)
			{
				troca = x;
				x = y;
				y = troca;
			}

			heapFibLink(H, y, x);
			a[grau] = NULL;
			grau++;

		}
	
		a[grau] = x;
		x = x->dir;

	}while(x != H -> noMin);


	H->noMin = NULL;

	for(i = 0; i < H -> qtdNos; i++)
	{
		if( a[i] )
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

			filho->esq->dir = noExtraido->dir;
			noExtraido->dir->esq = filho->esq;

			filho->esq = noExtraido;
			noExtraido->dir = filho;

			aux = filho;
			
			do
			{
				aux->pai= NULL;
				aux = aux->esq;

			}while(aux != filho);

		}
/*********************** Remove noExtraido da lista de raizes ***********************/

		if(noExtraido == noExtraido -> dir)
			H->noMin = NULL;
		
		else
		{
			
			noExtraido->esq->dir = noExtraido->dir;
			noExtraido->dir->esq = noExtraido->esq;

			H->noMin = noExtraido->dir;

			consolidar(H);
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
        if(x -> esq == x)
        {
            y -> filho = NULL;
        }
        else
        {
            y -> filho = x -> esq;
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


void decreaseKey(HeapFib* H, NoHeapFib* x , int k, verticeDjk * predec)
{
    assert(H);
    assert(x);
    assert(predec);

    if(k > x ->  custo) 
    {
        printf("Nova chave é maior que chave atual");
        return;
    }

    x -> custo = k;

    verticeDjk * x2 = (verticeDjk *) x;

    x2 -> predec = predec;

    NoHeapFib* y = x->pai;

    if(y != NULL && x -> custo < y -> custo)
    {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if(x -> custo < (H->noMin) -> custo)
        H->noMin = x;
}
