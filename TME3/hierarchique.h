#ifndef HIERARCHIQUE_H_INCLUDED
#define HIERARCHIQUE_H_INCLUDED

#include "label_propagation.h"

typedef struct {
	unsigned long source;
	unsigned long cible;
} arc_suppr;

void hiear_detect(graph* g, double decoupage);
void bfs(graph*g, arc_suppr a_suppr[], unsigned long node, int id_communaute, int id_augm);

#endif // HIERARCHIQUE_H_INCLUDED
