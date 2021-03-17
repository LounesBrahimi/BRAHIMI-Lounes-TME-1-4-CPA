#ifndef ADJMATRIX_H_INCLUDED
#define ADJMATRIX_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listedges.h"

typedef struct {
	unsigned long nombreNoeuds;
	unsigned long nombreArcs;
	unsigned long id_max;
	unsigned long *indices;
	arc *arcs;
	bool *mat;
} adjmatrix;

arclist* readarclistMat(char* nomFichier);
void mkmatrix(adjmatrix* g);
void free_adjmatrix(adjmatrix *g);
void affichageMatrice(adjmatrix* g);
void indexation(adjmatrix* g);


#endif // ADJMATRIX_H_INCLUDED
