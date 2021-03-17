#ifndef TAS_BINAIRE_H_INCLUDED
#define TAS_BINAIRE_H_INCLUDED

#include <stdio.h>

typedef struct{
    int d;
    int c;
    int indice;
    int id_node;
}id_degree;

typedef struct{
    id_degree *arr;
    int count_;
    int capacity;
    int* indexation;
}min_heap;

void insert(min_heap *h, int d, int indice, int c, int id);
void heapify(min_heap *h,int index);
id_degree PopMin(min_heap *h);
void heapify_to_bottom(min_heap *h, int parent);
void decrementer(min_heap* h, int index);

#endif // TAS_BINAIRE_H_INCLUDED
