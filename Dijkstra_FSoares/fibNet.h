#ifndef _FIB_NET_
#define _FIB_NET_
#include <stdlib.h>

typedef struct node
{
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* left;
    struct node* right;
    char mark;
    char C;
}node;

    node* InitializeHeap();
    int Fibonnaci_link(node* H1, node* y, node* z);
    node *Create_node(int value);
    node *Insert(node * H, node * x);
    node *Union(node * H1, node *H2);
    node *Extract_Min(node * H);
    int Consolidate(node * H);
    //int Display(node *);
    node *Find(node *, int k);
    int Decrease_key(node * H, node *ptr, int k);
    int Delete_key(node * H,int k);
    int Cut(node * H1, node * x, node * y);
    int Cascase_cut(node * H1, node * y);

#endif