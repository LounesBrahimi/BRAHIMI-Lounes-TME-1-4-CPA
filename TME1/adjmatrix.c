#include "adjmatrix.h"

arclist* readarclistMat(char* nomFichier){
    unsigned long* listeNoeud;
    listeNoeud = (unsigned long*)malloc(MAX*sizeof(unsigned long));
    char c;
    unsigned long noeudMax = -9999999;
    adjmatrix *g=malloc(sizeof(adjmatrix));
    g->nombreNoeuds=0;
	g->nombreArcs=0;
	g->arcs=malloc(MAX*sizeof(arc));

    g->indices = malloc(MAX*sizeof(unsigned long));
    memset (g->indices, -1, sizeof (unsigned long)*MAX);

    FILE *file;
    file = fopen(nomFichier, "r");
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
    g->indices[g->arcs[g->nombreArcs].source]+=2;
    /* On traite le tout premier noeud de droite v :*/
    fscanf (file, "%lu", &(g->arcs[g->nombreArcs].cible));
    listeNoeud[(g->arcs[g->nombreArcs].cible)] = 1;
    noeudMax = ((g->arcs[g->nombreArcs].cible) < noeudMax)? noeudMax : (g->arcs[g->nombreArcs].cible);
    g->indices[g->arcs[g->nombreArcs].cible]+=2;
    g->nombreArcs++;
    while (fscanf(file,"%lu %lu", &g->arcs[g->nombreArcs].source, &g->arcs[g->nombreArcs].cible)==2) {
        listeNoeud[g->arcs[g->nombreArcs].source] = 1;
        listeNoeud[g->arcs[g->nombreArcs].cible] = 1;

        g->indices[g->arcs[g->nombreArcs].source]+=2;
        g->indices[g->arcs[g->nombreArcs].cible]+=2;

        noeudMax = (g->arcs[g->nombreArcs].source < noeudMax)? noeudMax : g->arcs[g->nombreArcs].source;
        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
        g->nombreArcs++;
    }
    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listeNoeud[i] == 1) g->nombreNoeuds++;
    }
    g->id_max = noeudMax;
    free(listeNoeud);
    fclose(file);
    /*g->arcs=realloc(g->arcs,g->nombreArcs*sizeof(arc));*/
	return g;
    }
    return NULL;
}

void indexation(adjmatrix* g){
    int i;
    int j=0;
	for (i=0;i<g->nombreNoeuds;i++) {
        j+=i;
        while ((g->indices[j] == -1)&&(j<g->id_max)){
            j++;
        }
        if (j<=g->id_max){
            g->indices[j] = i;
            j-=i;
        }
        else {
            break;
        }
	}
}

void mkmatrix(adjmatrix* g){
	unsigned long i,u,v;
	g->mat=calloc(g->nombreNoeuds*g->nombreNoeuds,sizeof(bool));
	for (i=0;i<g->nombreArcs;i++){
		u=g->indices[g->arcs[i].source];
		v=g->indices[g->arcs[i].cible];
		g->mat[(u*g->nombreNoeuds)+v]=1;
		g->mat[(v*g->nombreNoeuds)+u]=1;
	}
}

void free_adjmatrix(adjmatrix *g){
	free(g->arcs);
	free(g->mat);
	free(g);
}

void affichageMatrice(adjmatrix* g){
    int i;
        for(i=0; i<(g->nombreNoeuds*g->nombreNoeuds); i++)
        {
         printf("%lu     ", g->mat[i]);
         if (((i+1) % g->nombreNoeuds)==0) printf("\n");
        }
}

/*int main(int argc,char** argv){
	adjmatrix* g;

	printf("Reading edgelist from file com-amazon.ungraph.txt");
	g=readarclistMat("com-amazon.ungraph.txt");

	printf("\nNumber of nodes: %lu\n",g->nombreNoeuds);
	printf("Number of edges: %lu\n",g->nombreArcs);

	printf("Building the adjacency matrix\n");
	mkmatrix(g);
    affichageMatrice(g);
	free_adjmatrix(g);
	return 0;
}*/
