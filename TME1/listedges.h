#ifndef LISTEDGES_H_INCLUDED
#define LISTEDGES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000000

/*structure representant un arc avec un noeud source et un noeud cible*/
typedef struct {
	unsigned long source;
	unsigned long cible;
} arc;

/*Structure representant la liste de tous les arcs*/
typedef struct {
	unsigned long nombreNoeuds;
	unsigned long nombreArcs;
	arc *arcs;/*vercteur qui va contenir tous les arcs*/
} arclist;

arclist* readarclist(char* nomFichier);
void free_arclist(arclist *g);


#endif // LISTEDGES_H_INCLUDED
