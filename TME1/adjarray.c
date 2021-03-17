#include "adjarray.h"

adjlist* readedgelist(char* nomFichier){
	char c = '\0';
	FILE *file=fopen(nomFichier,"r");
	adjlist *g=malloc(sizeof(adjlist));
	g->nombreNoeuds=0;
	g->nombreArcs=0;
	g->arcs=malloc(MAX*sizeof(arc));
	unsigned long* listNoeuds;

	unsigned long noeudMax = -9999999;
    listNoeuds = (unsigned long*)malloc(MAX*sizeof(unsigned long));

	if (file) {
        /*On ignore toutes les lignes qui commence par #*/
        while (((c = getc(file)) != EOF)){
            if (c != '#') break;
            while ((c = getc(file)) != '\n'){
            }
        }
    /* On traite le tout premier noeud gauche u :*/
    g->arcs[g->nombreArcs].source = c-'0';
    listNoeuds[g->arcs[g->nombreArcs].source] = 1;
    noeudMax = g->arcs[g->nombreArcs].source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf (file, "%lu", &(g->arcs[g->nombreArcs].cible));
    listNoeuds[g->arcs[g->nombreArcs].cible] = 1;
    noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
    g->nombreArcs++;

	while (fscanf(file,"%lu %lu", &(g->arcs[g->nombreArcs].source), &(g->arcs[g->nombreArcs].cible))==2) {
		listNoeuds[g->arcs[g->nombreArcs].cible] = 1;
		listNoeuds[g->arcs[g->nombreArcs].source] = 1;

		noeudMax = (g->arcs[g->nombreArcs].source < noeudMax)? noeudMax : g->arcs[g->nombreArcs].source;
        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;

        g->nombreArcs++;
	}
	fclose(file);

    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listNoeuds[i] == 1) g->nombreNoeuds++;
    }
    free(listNoeuds);
    g->id_max = noeudMax;
	return g;
}
return NULL;
}

void mkadjlist(adjlist* g){
	unsigned long i,u,v;
    g->indices = calloc(g->id_max,sizeof(unsigned long));
	for (i=0;i<g->nombreArcs;i++) {
		g->indices[g->arcs[i].source]++;
		g->indices[g->arcs[i].cible]++;
	}
	unsigned long *d=calloc(g->nombreNoeuds,sizeof(unsigned long));
	int j=0;
	for (i=0;i<g->nombreNoeuds;i++) {
        j+=i;
        while (g->indices[j] == 0){
            j++;
        }
        d[i] = g->indices[j];
        g->indices[j] = i;
        j-=i;
	}
	g->cd=malloc((g->nombreNoeuds+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->nombreNoeuds+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}
    g->adj=malloc(2*g->nombreArcs*sizeof(unsigned long));
    unsigned long u_0;
    unsigned long v_0;
	for (i=0;i<g->nombreArcs;i++) {
		u=g->arcs[i].source;
		v=g->arcs[i].cible;
		u_0 = g->indices[u];
		v_0 = g->indices[v];
		g->adj[ g->cd[u_0] + d[u_0]++ ]=v;
		g->adj[ g->cd[v_0] + d[v_0]++ ]=u;
	}
	free(d);
}

void free_adjlist(adjlist *g){
	free(g->arcs);
	free(g->cd);
	free(g->adj);
	free(g);
}
