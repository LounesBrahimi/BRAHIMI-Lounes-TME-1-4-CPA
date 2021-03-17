#include "tas_binaire.h"

void insert(min_heap *h, int d, int indice, int c, int id){
    if( h->count_ < h->capacity){
        h->arr[h->count_].d = d;
        h->arr[h->count_].indice = indice;
        h->arr[h->count_].c = c;
        h->arr[h->count_].id_node = id;
        h->indexation[indice]= h->count_;
        heapify(h, h->count_);
        h->count_++;
    }
}

void heapify(min_heap *h,int index){
    int temp_d;
    int temp_indice;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node].d > h->arr[index].d){

        h->indexation[h->arr[parent_node].indice]= index;
        h->indexation[h->arr[index].indice]= parent_node;

        temp_d = h->arr[parent_node].d;
        temp_indice = h->arr[parent_node].indice;
        h->arr[parent_node].d = h->arr[index].d;
        h->arr[parent_node].indice = h->arr[index].indice;
        h->arr[index].d = temp_d;
        h->arr[index].indice = temp_indice;
        heapify(h,parent_node);
    }
}

id_degree PopMin(min_heap *h){
    id_degree pop;
    if(h->count_==0){
        printf("Empty ERROR\n");
        return ;
    }
    pop = h->arr[0];
    h->indexation[h->arr[0].indice] = -1;
    h->arr[0] = h->arr[h->count_-1];
    h->indexation[h->arr[h->count_-1].indice] = 0;
    h->count_--;
    heapify_to_bottom(h, 0);
    return pop;
}

void heapify_to_bottom(min_heap *h, int parent){
    int left = parent*2+1;
    int right = parent*2+2;
    int min;
    int temp_d;
    int temp_indice;
    if(left >= h->count_ || left <0)
        left = -1;
    if(right >= h->count_ || right <0)
        right = -1;

    if(left != -1 && h->arr[left].d < h->arr[parent].d)
        min=left;
    else
        min =parent;
    if(right != -1 && h->arr[right].d < h->arr[min].d)
        min = right;
    if(min != parent){
        h->indexation[h->arr[parent].indice] = min;
        h->indexation[h->arr[min].indice] = parent;
        temp_d = h->arr[min].d;
        temp_indice = h->arr[min].indice;
        h->arr[min].d = h->arr[parent].d;
        h->arr[min].indice= h->arr[parent].indice;
        h->arr[parent].d = temp_d;
        h->arr[parent].indice = temp_indice;
        heapify_to_bottom(h, min);
    }
}

void decrementer(min_heap* h, int index)
{
    h->arr[index].d--;
    if ((index != 0)&&(h->arr[(index-1)/2].d > h->arr[index].d)){
        heapify(h, index);
    }
}
