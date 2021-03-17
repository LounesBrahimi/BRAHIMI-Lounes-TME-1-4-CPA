#ifndef LOWER_BOUND_H_INCLUDED
#define LOWER_BOUND_H_INCLUDED

#include "adjarray.h"
#include "fifo.h"

typedef struct {
    unsigned long noeud;
    int dis;
} resultat_bfs;

resultat_bfs lower_bfs(adjlist* g, unsigned long s_dep);

#endif // LOWER_BOUND_H_INCLUDED
