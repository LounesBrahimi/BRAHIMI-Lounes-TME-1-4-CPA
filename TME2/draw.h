#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "page_rank.h"

void drawPRWInD(graph* g, char* nom_fichier);
void indicage_de_d(graph* g);
void drawPRWOutD(graph* g, char* nom_fichier);
void draw_p_r(double* P_x, graph* g, double a, char* nom_fichier);
void draw_nodes_p_r(graph* g, char* nom_fichier);

#endif // DRAW_H_INCLUDED
