#ifndef K_CORE_DECOMPOSITION_H_INCLUDED
#define K_CORE_DECOMPOSITION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "tas_binaire.h"

#define MAX 10000000

typedef struct {
	unsigned long source;
	unsigned long cible;
} arc;

typedef struct {
	unsigned long nombreNoeuds;
	unsigned long nombreArcs;
	arc *arcs;
	unsigned long id_max;
	unsigned long *indices;
	unsigned long *cd;
	unsigned long *adj;
	int *d;
} graph;

graph* liste_arcs(char* nomFichier);
void mkadjlist(graph* g);
min_heap* core_decomposition(graph* g);
void make_a_plot(min_heap* h, char* nom_fichier, graph* g);

#endif // K_CORE_DECOMPOSITION_H_INCLUDED
