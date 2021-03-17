#ifndef ADJARRAY_H_INCLUDED
#define ADJARRAY_H_INCLUDED

#include "adjmatrix.h"

typedef struct {
	unsigned long nombreNoeuds;
	unsigned long nombreArcs;
	arc *arcs;
	unsigned long id_max;
	unsigned long *indices;
	unsigned long *cd;
	unsigned long *adj;
} adjlist;

adjlist* readedgelist(char* nomFichier);
void mkadjlist(adjlist* g);

#endif // ADJARRAY_H_INCLUDED
