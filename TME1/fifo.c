#include "fifo.h"
unsigned long defiler(fifo *f) {
    if (f->queue == f->tete) {
        perror("Pile vide");
        exit(EXIT_FAILURE);
    }
    unsigned long noeud = f->u[f->queue];
    f->queue++;
    f->nombre_elements--;
    return noeud;
}

int enfiler(fifo *f, unsigned long noeud) {
    if (f->tete == f->taille) {
        return -1;
    }
    f->u[f->tete] = noeud;
    f->tete++;
    f->nombre_elements++;
    return 0;
}
