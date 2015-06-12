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
	printf("Elemento %d: %d   ", G++,  No == NULL ? INT_MIN : No -> chave -> custo);

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

NoHeapFib * insereFib(HeapFib* H, verticeDjk * chave){
	assert(H);

	NoHeapFib* novoNo = (NoHeapFib*) malloc( sizeof( NoHeapFib));
	if(novoNo == NULL) return novoNo;

	novoNo->pai = NULL;
	novoNo->filho = NULL;
	novoNo->chave = chave;
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

		if ( chave -> custo < (H -> noMin) -> chave -> custo){
			(H -> noMin) = novoNo;
		}
	}

	(H -> qtdNos)++;
	return novoNo;
}

void insereFibNoPronto( HeapFib* H, NoHeapFib* No){
	assert( H);

	if ( H->noMin == NULL)
		return;

	No->esq = (H -> noMin)->esq;
	(H -> noMin) -> esq = No;
	No -> dir = (H -> noMin);
	(No -> esq) -> dir = No;

	if (No -> chave -> custo < (H -> noMin) -> chave -> custo)
			(H -> noMin) = No;	

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


void consolidar(HeapFib * H)
{	
	NoHeapFib * a[H->qtdNos];
	int i, grau;
	NoHeapFib * y, * troca, * x = H -> noMin;


	for(i = 0; i < H -> qtdNos; i++)
	{
		a[i] = NULL;
	}
	

	do{

		grau = x -> grau;

		while(a[grau])
		{
			y = a[grau];
			if (x -> chave -> custo > y -> chave -> custo)
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
		x = x -> dir;

	}while(x != H -> noMin);


	H -> noMin = NULL;

	for(i = 0; i < H -> qtdNos; i++)
	{
		if( a[i] )
		{
			if(!(H -> noMin))
			{
				H -> noMin = a[i];
				a[i] -> esq = a[i];
				a[i] -> dir = a[i];
			}
			else
			{
				a[i] -> esq  = (H -> noMin) -> esq;		
				(H -> noMin) -> esq = a[i];
				a[i] -> dir = (H -> noMin);

				(a[i] -> esq) -> dir = a[i];


				if(a[i] -> chave -> custo < (H -> noMin) -> chave -> custo)
					H -> noMin = a[i];

			}
		}
	}

}


NoHeapFib * extractMin(HeapFib * H)
{
	assert(H);

	NoHeapFib * ext = H -> noMin;
	NoHeapFib * filho;
	NoHeapFib * aux = NULL;


	if(ext != NULL)
	{

		filho = ext -> filho;

		if(filho)
		{
/*********************** Insere todos os filhos de ext na lista de raizes ***********************/

			(filho -> esq) -> dir = (ext -> dir);
			(ext -> dir) -> esq = filho -> esq;

			filho -> esq = ext;
			ext -> dir = filho;

			aux = filho;
			
			do
			{
				aux -> pai	= NULL;
				aux = aux -> esq;

			}while(aux != filho);

		}
/*********************** Remove ext da lista de raizes ***********************/

		(ext -> esq) -> dir = ext -> dir;
		(ext -> dir) -> esq = ext -> esq;


		if(ext == ext -> dir)
		{

			H -> noMin = NULL;
		}
		else
		{
			H -> noMin = ext -> dir;

			consolidar(H);
		}

		H -> qtdNos--;


	}

	return ext;
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
            y -> grau--;
        }
        else
        {
            y -> filho = x -> esq;
            y -> grau--;
        }
    }
    else
    {
        (x -> esq) -> dir = x -> dir;
        (x -> dir) -> esq = x -> esq;
        y -> grau--;
    }

    insereFibNoPronto(H, x);
    x -> pai = NULL;
    x -> marca = 0;
}

void cascadingCut(HeapFib* H, NoHeapFib* y)
{
    assert(H);
    assert(y);

    NoHeapFib* z = y -> pai;

    if(z != NULL)
    {
        if(!y -> marca)
            y -> marca = 1;
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

    if(k > x -> chave ->  custo) 
    {
        printf("Nova chave é maior que chave atual");
        return;
    }

    x -> chave -> custo = k;
    x -> chave -> predec = predec;

    NoHeapFib* y = x->pai;

    if(y != NULL && x -> chave -> custo < y -> chave -> custo)
    {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if(x -> chave -> custo < (H->noMin) -> chave -> custo)
        H->noMin = x;
}
