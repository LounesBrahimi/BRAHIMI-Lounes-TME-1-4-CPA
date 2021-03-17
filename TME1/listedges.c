#include "listedges.h"

arclist* readarclist(char* nomFichier){
	char c = '\0';
	FILE *file=fopen(nomFichier,"r");
	arclist *g=malloc(sizeof(arclist));
	g->nombreNoeuds=0;
	g->nombreArcs=0;
	g->arcs=malloc(MAX*sizeof(arc));
	unsigned long* listeNoeud;
	unsigned long noeudMax = -9999999;
    listeNoeud = (unsigned long*)calloc(MAX,sizeof(unsigned long));

	if (file) {
        /*On ignore toutes les lignes qui commence par #*/
        while (((c = getc(file)) != EOF)){
            if (c != '#') break;
            while ((c = getc(file)) != '\n'){
            }
        }
    /* On traite le tout premier noeud gauche u :*/
    g->arcs[g->nombreArcs].source = c-'0';
    listeNoeud[g->arcs[g->nombreArcs].source] = 1;
    noeudMax = g->arcs[g->nombreArcs].source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf (file, "%lu", &(g->arcs[g->nombreArcs].cible));
    listeNoeud[g->arcs[g->nombreArcs].cible] = 1;
    noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
    g->nombreArcs++;

	while (fscanf(file,"%lu %lu", &(g->arcs[g->nombreArcs].source), &(g->arcs[g->nombreArcs].cible))==2) {
		listeNoeud[g->arcs[g->nombreArcs].cible] = 1;
		listeNoeud[g->arcs[g->nombreArcs].source] = 1;

		noeudMax = (g->arcs[g->nombreArcs].source < noeudMax)? noeudMax : g->arcs[g->nombreArcs].source;
        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;

        g->nombreArcs++;
		/*if (++(g->nombreArcs)==MAX) {
			max+=MAX;
			g->arcs=realloc(g->arcs,max*sizeof(arc));
		}*/
	}
	fclose(file);

    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listeNoeud[i] == 1) g->nombreNoeuds++;
    }
    free(listeNoeud);
	/*g->arcs=realloc(g->arcs,g->nombreArcs*sizeof(arc));*/
	return g;
}
return NULL;
}

void free_arclist(arclist *g){
	free(g->arcs);
	free(g);
}

/*
int main(int argc,char** argv){
    arclist* g;
	printf("Reading edgelist from file com-amazon.ungraph.txt \n");
	g=readarclist("com-amazon.ungraph.txt");
	printf("Number of nodes: %lu\n",g->nombreNoeuds);
	printf("Number of edges: %lu\n",g->nombreArcs);
    printf("arc10 : %lu\n", g->arcs[10].cible);
	free_arclist(g);
	return 0;
}*/
