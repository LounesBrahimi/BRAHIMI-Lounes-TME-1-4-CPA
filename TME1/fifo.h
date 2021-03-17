#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {
    unsigned long nombre_elements;
    unsigned long tete;
    unsigned long queue;
    unsigned long taille;
    unsigned long* u;
} fifo;

unsigned long defiler(fifo *f);
int enfiler(fifo *f, unsigned long noeud);
