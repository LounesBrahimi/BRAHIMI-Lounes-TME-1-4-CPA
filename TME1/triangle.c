#include "triangle.h"

adjlist* liste_des_arcs(char* nomFichier){
	char c = '\0';
	unsigned long max=MAX;
	unsigned long source = -1;
	unsigned long cible = -1;
	FILE *file=fopen(nomFichier,"r");
	adjlist *g=malloc(sizeof(adjlist));
	g->nombreNoeuds=0;
	g->nombreArcs=0;
	g->arcs=malloc(max*sizeof(arc));
	unsigned long* listeNoeuds;

	unsigned long noeudMax = -9999999;
    listeNoeuds = (unsigned long*)malloc(max*sizeof(unsigned long));

	if (file) {
        /*On ignore toutes les lignes qui commence par #*/
        while (((c = getc(file)) != EOF)){
            if (c != '#') break;
            while ((c = getc(file)) != '\n'){
            }
        }
    /* On traite le tout premier noeud gauche u :*/
    source = c-'0';
    listeNoeuds[source] = 1;
    noeudMax = source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf(file, "%lu", &cible);
    listeNoeuds[cible] = 1;
    noeudMax = (cible < noeudMax)? noeudMax : cible;
    if(cible < noeudMax){
        g->arcs[g->nombreArcs].source = cible;
        g->arcs[g->nombreArcs].cible = source;
    }
    else {
        noeudMax = cible;
        g->arcs[g->nombreArcs].source = source;
        g->arcs[g->nombreArcs].cible = cible;
    }
    g->nombreArcs++;

	while (fscanf(file,"%lu %lu", &source, &cible)==2) {
		listeNoeuds[source] = 1;
		listeNoeuds[cible] = 1;

		if(source < cible){
            g->arcs[g->nombreArcs].source = source;
            g->arcs[g->nombreArcs].cible = cible;
        }
        else {
            g->arcs[g->nombreArcs].source = cible;
            g->arcs[g->nombreArcs].cible = source;
        }
        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
		g->nombreArcs++;
	}
	fclose(file);

    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listeNoeuds[i] == 1) g->nombreNoeuds++;
    }
    free(listeNoeuds);
    g->id_max = noeudMax;
	return g;
}
return NULL;
}

void adjlist_dag(adjlist* g){
	unsigned long i,u,v;

    g->indices = malloc(g->id_max*sizeof(unsigned long));
    memset (g->indices, -1, sizeof (unsigned long) * g->id_max);

	for (i=0;i<g->nombreArcs;i++) {
        if(g->indices[g->arcs[i].source] == -1)
            g->indices[g->arcs[i].source] = 0;
		g->indices[g->arcs[i].source]++;
		if(g->indices[g->arcs[i].cible] == -1)
            g->indices[g->arcs[i].cible] = 0;
	}


	unsigned long *d=calloc(g->nombreNoeuds,sizeof(unsigned long));

	int j=0;
	for (i=0;i<g->nombreNoeuds;i++) {
        j+=i;
        while (g->indices[j] == -1){
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

    g->adj=malloc(g->nombreArcs*2*sizeof(unsigned long));

    unsigned long u_0;
    unsigned long v_0;
    unsigned long cpt = 0;
	for (i=0;i<g->nombreArcs;i++) {
		u=g->arcs[i].source;
		v=g->arcs[i].cible;
		u_0 = g->indices[u];
		v_0 = g->indices[v];

		cpt = g->cd[u_0] + d[u_0]+1;
		g->adj[ g->cd[u_0] + d[u_0]++ ]=v;
	}
}

int nombre_triangle(adjlist* g){
    int i, j, k;
    int nombreTriangle = 0;
    for(i=0; i<g->nombreArcs; i++){
        for(j=g->cd[g->indices[g->arcs[i].source]+1]-1;
            j>=g->cd[g->indices[g->arcs[i].source]];j--){
            if (g->arcs[i].cible > g->adj[j]) break;
                for(k=g->cd[g->indices[g->arcs[i].cible]+1]-1;
                        ((k>= g->cd[g->indices[g->arcs[i].cible]])
                            );k--){
                    if (g->adj[k] < g->adj[j]) break;
                    if (g->adj[j] == g->adj[k]){
                            nombreTriangle++;
                    }
                }

        }
    }
    return nombreTriangle;
}

void free_triangle(adjlist *g){
	free(g->arcs);
	free(g->cd);
	free(g->adj);
	free(g);
}
