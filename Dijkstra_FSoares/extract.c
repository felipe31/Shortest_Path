#include "fib.h"
#include <stdio.h>
#include <assert.h>

HeapFib * makeHeapFib()
{
	HeapFib * heap = (HeapFib *) malloc(sizeof(HeapFib));
	if(!heap) return NULL;

	heap -> noMin = NULL;
	heap -> qtdNos = 0;

	return heap;

}

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


	//NoHeapFib * no = H -> noMin;
	

	do{

		grau = x -> grau;

		while(a[grau])
		{
			y = a[grau];
			if (x -> chave > y -> chave)
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


				if(a[i] -> chave < (H -> noMin) -> chave)
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