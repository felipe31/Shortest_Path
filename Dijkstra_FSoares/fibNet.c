#include "fibNet.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int nH = 0;
node* InitializeHeap()
{
    node* np;
    np = NULL;
    return np;
}
/*
 * Create Node
 */
node* Create_node(int value)
{
    node* x = (node *) malloc(sizeof(node));
    x->n = value;
    return x;
}
/*
 * Insert Node
 */
node* Insert(node* H, node* x)
{
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    x->mark = 'F';
    x->C = 'N';
    if (H != NULL)
    {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->n < H->n)
            H = x;
    }
    else
    {
        H = x;
    }
    nH = nH + 1;
    return H;
}
/*
 * Link Nodes in Fibonnaci Heap
 */
int Fibonnaci_link(node* H1, node* y, node* z)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (z->right == z)
        H1 = z;
    y->left = y;
    y->right = y;
    y->parent = z;
    if (z->child == NULL)
        z->child = y;
    y->right = z->child;
    y->left = (z->child)->left;
    ((z->child)->left)->right = y;
    (z->child)->left = y;
    if (y->n < (z->child)->n)
        z->child = y;
    z->degree++;
}
/*
 * Union Nodes in Fibonnaci Heap
 */
node* Union(node* H1, node* H2)
{
    node* np;
    node* H = InitializeHeap();
    H = H1;
    (H->left)->right = H2;
    (H2->left)->right = H;
    np = H->left;
    H->left = H2->left;
    H2->left = np;
    return H;
}
/*
 * Display Fibonnaci Heap
 */

/*
 * Extract Min Node in Fibonnaci Heap
 */
node* Extract_Min(node* H)
{
    node* p;
    node* ptr;
    node* z = H;
    p = z;
    ptr = z;
    if (z == NULL)
        return z;
    node* x;
    node* np;
    x = NULL;
    if (z->child != NULL)
        x = z->child;
    if (x != NULL)
    {
        ptr = x;
        do
        {
            np = x->right;
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;
            if (x->n < H->n)
                H = x;
            x->parent = NULL;
            x = np;
        }
        while (np != ptr);
    }
    (z->left)->right = z->right;
    (z->right)->left = z->left;
    H = z->right;
    if (z == z->right && z->child == NULL)
        H = NULL;
    else
    {
        H = z->right;
        Consolidate(H);
    }
    nH = nH - 1;
    return p;
}
/*
 * Consolidate Node in Fibonnaci Heap
 */
int Consolidate(node* H)
{
    int d, i;
    float f = (log(nH)) / (log(2));
    int D = f;
    node* A[D];
    for (i = 0; i <= D; i++)
        A[i] = NULL;
    node* x = H;
    node* y;
    node* np;
    node* pt = x;
    do
    {
        pt = pt->right;
        d = x->degree;
        while (A[d] != NULL)
        {
            y = A[d];
            if (x->n > y->n)
            {
                np = x;
                x = y;
                y = np;
            }
            if (y == H)
                H = x;
            Fibonnaci_link(H, y, x);
            if (x->right == x)
                H = x;
                A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x->right;
    }
    while (x != H);
    H = NULL;
    int j;
    for ( j = 0; j <= D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->left = A[j];
            A[j]->right =A[j];
            if (H != NULL)
            {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->n < H->n)
                H = A[j];
            }
            else
            {
                H = A[j];
            }
            if(H == NULL)
                H = A[j];
            else if (A[j]->n < H->n)
                H = A[j];
        }
    }
}

/*
 * Decrease key of Nodes in Fibonnaci Heap
 */
int Decrease_key(node*H, node *ptr, int k)
{
    node* y;
    if (H == NULL)
    {
        puts("The Heap is Empty");
        return 0;
    }
    //node* ptr = Find(H, x);
    if (ptr == NULL)
    {
        puts("Node not found in the Heap");
        return 1;
    }
    if (ptr->n < k)
    {
        puts("Entered key greater than current key");
        return 0;
    }
    ptr->n = k;
    y = ptr->parent;
    if (y != NULL && ptr->n < y->n)
    {
        Cut(H, ptr, y);
        Cascase_cut(H, y);
    }
    if (ptr->n < H->n)
        H = ptr;
    return 0;
}
/*
 * Cut Nodes in Fibonnaci Heap
 */
int Cut(node* H1, node* x, node* y)
{
    if (x == x->right)
        y->child = NULL;
    (x->left)->right = x->right;
    (x->right)->left = x->left;
    if (x == y->child)
        y->child = x->right;
    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;
    (H1->left)->right = x;
    x->right = H1;
    x->left = H1->left;
    H1->left = x;
    x->parent = NULL;
    x->mark = 'F';
}

/*
 * Cascade Cutting in Fibonnaci Heap
 */
int Cascase_cut(node* H1, node* y)
{
    node* z = y->parent;
    if (z != NULL)
    {
        if (y->mark == 'F')
        {
            y->mark = 'T';
	}
        else
        {
            Cut(H1, y, z);
            Cascase_cut(H1, z);
        }
    }
}

/*
 * Find Nodes in Fibonnaci Heap
 */
node* Find(node* H, int k)
{
    node* x = H;
    x->C = 'Y';
    node* p = NULL;
    if (x->n == k)
    {
        p = x;
        x->C = 'N';
        return p;
    }
    if (p == NULL)
    {
        if (x->child != NULL )
            p = Find(x->child, k);
        if ((x->right)->C != 'Y' )
            p = Find(x->right, k);
    }
    x->C = 'N';
    return p;
}
/*
 * Delete Nodes in Fibonnaci Heap
 */
// int Delete_key(node* H, int k)
// {
//     node* np = NULL;
//     int t;
//     t = Decrease_key(H, k, -5000);
//     if (!t)
//         np = Extract_Min(H);
//     if (np != NULL)
//         printf("Key Deleted");
//     else
//         printf("Key not Deleted");
//     return 0;
//}
