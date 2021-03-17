#ifndef LABEL_PROPAGATION_H_INCLUDED
#define LABEL_PROPAGATION_H_INCLUDED

#include "bechmark.h"
#include <string.h>

#define MAX 1000000

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
	unsigned long *id_node;
	unsigned long *nodes;
	unsigned long *cd;
	unsigned long *adj;
	unsigned long *voisins;
	int *marquage_noeuds;
} graph;

graph* readedgelist(char* nomFichier);
void mkadjlist(graph* g);
void label_propagation(graph* g);
void swap_nodes(graph* g, int x, int y);
void shuffle_nodes(graph* g);
void indexation(graph* g);
void draw_community(graph* g, char* nom_fichier);

#endif // LABEL_PROPAGATION_H_INCLUDED
