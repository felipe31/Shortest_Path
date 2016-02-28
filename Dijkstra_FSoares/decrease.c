#include "fib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void decreaseKey(HeapFib* H, NoHeapFib* x ,int k)
{
    assert(H);
    assert(x);

    if(k > x->chave)
    {
        printf("Nova chave é maior que chave atual");
        return;
    }

    x->chave = k;
    NoHeapFib* y = x->pai;

    if(y != NULL && x->chave < y->chave)
    {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if(x->chave < (H->noMin) -> chave)
        H->noMin = x;
}

void cut(HeapFib* H, NoHeapFib* x, NoHeapFib* y)
{
    assert(H);
    assert(x);
    assert(y);

    if(y->filho == x)
    {
        if(x->esq == x)
        {
            y->filho = NULL;
            y->grau--;
        }
        else
        {
            y->filho = x->esq;
            y->grau--;
        }
    }
    else
    {
        (x->esq)->dir = x->dir;
        (x->dir)->esq = x->esq;
        y->grau--;
    }

    reinsereFibNo(H, x);
    x->pai = NULL;
    x->marca = 0;
}

void cascadingCut(HeapFib* H, NoHeapFib* y)
{
    assert(H);
    assert(y);

    NoHeapFib* z = y->pai;

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
