#ifndef PAGE_RANK_H_INCLUDED
#define PAGE_RANK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20071018

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
	int *d_out;
	int *d_in;
	double* P;
} graph;

void power_iteration(graph* g, double a, int t);
void power_iteration_rooted(graph* g, double a, int t, double* P_0);
graph* liste_arcs(char* nomFichier);
void initialisation_P(double* P, double* P2, unsigned long nombreNoeuds);
void indexation(graph* g);
double* permutationVecteurs(graph* g, double* d);
#endif // PAGE_RANK_H_INCLUDED
