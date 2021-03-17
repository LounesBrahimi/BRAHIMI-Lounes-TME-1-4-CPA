#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "adjarray.h"

adjlist* liste_des_arcs(char* nomFichier);
void adjlist_dag(adjlist* g);
int nombre_triangle(adjlist* g);

#endif // TRIANGLE_H_INCLUDED
