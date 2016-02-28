#include <stdio.h>
#include <stdlib.h>

typedef struct numeros
{
    int i;
    struct numeros* prox;
}num;



int main() {

     num *i =  (num *) calloc(10, sizeof(num));

     
    // num *j =  (num *) calloc(1, sizeof(num));
    // num *k =  (num *) calloc(1, sizeof(num));
    //
    // printf("i = %p\n", i);
    // printf("i->prox = %p\n\n", i->prox);
    //
    // j->prox = i->prox;
    // i->prox = j;
    //
    // printf("j = %p\n", j);
    // printf("i = %p\n", i);
    // printf("i->prox = %p\n", i->prox);
    // printf("i->prox->prox = %p\n\n", i->prox->prox);
    //
    //
    // k->prox = i->prox;
    // i->prox = k;
    //
    // printf("k = %p\n", k);
    // printf("j = %p\n", j);
    // printf("i = %p\n", i);
    // printf("i->prox = %p\n", i->prox);
    // printf("i->prox->prox = %p\n", i->prox->prox);
    // printf("i->prox->prox->prox = %p\n", i->prox->prox->prox);

    return 0;
}
