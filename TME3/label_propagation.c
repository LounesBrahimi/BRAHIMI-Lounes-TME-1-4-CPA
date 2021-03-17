#include "label_propagation.h"


graph* readedgelist(char* nomFichier){
	char c = '\0';
	unsigned long max=MAX;
	FILE *file=fopen(nomFichier,"r");
	graph *g=malloc(sizeof(graph));
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
    g->arcs[g->nombreArcs].source = c-'0';
    listeNoeuds[g->arcs[g->nombreArcs].source] = 1;
    noeudMax = g->arcs[g->nombreArcs].source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf (file, "%lu", &(g->arcs[g->nombreArcs].cible));
    listeNoeuds[g->arcs[g->nombreArcs].cible] = 1;
    noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
    g->nombreArcs++;

	while (fscanf(file,"%lu %lu", &(g->arcs[g->nombreArcs].source), &(g->arcs[g->nombreArcs].cible))==2) {
		listeNoeuds[g->arcs[g->nombreArcs].cible] = 1;
		listeNoeuds[g->arcs[g->nombreArcs].source] = 1;

		noeudMax = (g->arcs[g->nombreArcs].source < noeudMax)? noeudMax : g->arcs[g->nombreArcs].source;
        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;

		if (++(g->nombreArcs)==max) {
			max+=MAX;
			g->arcs=realloc(g->arcs,max*sizeof(arc));
		}
	}
	fclose(file);

    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listeNoeuds[i] == 1) g->nombreNoeuds++;
    }
    free(listeNoeuds);
	g->arcs=realloc(g->arcs,g->nombreArcs*sizeof(arc));
    g->id_max = noeudMax;
	return g;
}
return NULL;
}

void mkadjlist(graph* g){
	unsigned long i,u,v;
    unsigned long *d=calloc(g->nombreNoeuds,sizeof(unsigned long));

    g->cd=malloc((g->nombreNoeuds+1)*sizeof(unsigned long));

    g->indices = calloc(g->id_max,sizeof(unsigned long));

    g->id_node = malloc(g->id_max*sizeof(unsigned long));
    memset (g->id_node, -1, sizeof (unsigned long)*g->id_max);

    g->nodes = malloc(g->id_max*sizeof(unsigned long));
    memset (g->nodes, -1, sizeof (unsigned long)*g->id_max);

	g->adj=(unsigned long*) malloc(2*g->nombreArcs*sizeof(unsigned long));

	for (i=0;i<g->nombreArcs;i++) {
		g->indices[g->arcs[i].source]++;
		g->indices[g->arcs[i].cible]++;
		g->id_node[g->arcs[i].source]=g->arcs[i].source;
		g->id_node[g->arcs[i].cible]=g->arcs[i].cible;
        g->nodes[g->arcs[i].source]=g->arcs[i].source;
		g->nodes[g->arcs[i].cible]=g->arcs[i].cible;
	}
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

	g->cd[0]=0;
	for (i=1;i<g->nombreNoeuds+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}
    
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

void indexation(graph* g){
    int i;
    int j=0;
	for (i=0;i<g->nombreNoeuds;i++) {
        j+=i;
        while ((g->nodes[j] == -1)&&(j<g->id_max)){
            j++;
        }
        if (j<=g->id_max){
            g->nodes[i] = g->nodes[j];
            j-=i;
        }
        else {
            break;
        }
	}
}

void swap_nodes(graph* g, int x, int y){
    unsigned long tmp = g->nodes[x];
    g->nodes[x] = g->nodes[y];
    g->nodes[y] = tmp;
}

void shuffle_nodes(graph* g)
{
    int i, j;
    srand(time(NULL));
    for (i = g->nombreNoeuds-1; i > 0; i--){
        j = rand() % (i+1);
        swap_nodes(g, i,j);
    }
}

void label_propagation(graph* g){
    g->voisins = calloc(g->id_max+1, sizeof(unsigned long));
    unsigned long nv_id_node;
    int nb_voisins;
    int nb_d =0;
    int alea = 0;
    int cpt = 0;
    int continue_ = 1;
    int i, j;
    srand(time(NULL));
    while(continue_){
    continue_=0;
    shuffle_nodes(g);
    for(i=0; i<g->nombreNoeuds; i++){
            g->voisins[g->id_node[g->nodes[i]]]++;
            nb_voisins = 0;
            nv_id_node = 0;
            cpt =0;
            alea = 0;

        if (g->nodes[i] != g->id_max){
            nb_d = g->cd[g->indices[g->nodes[i]]+1] - g->cd[g->indices[g->nodes[i]]];
        }
        alea = rand()%nb_d;
        for(j=g->cd[g->indices[g->nodes[i]]];((j<g->cd[g->indices[g->nodes[i]]+1])&&(j< (g->nombreArcs*2))); j++){
            g->voisins[g->id_node[g->adj[j]]]++;
                nv_id_node = g->id_node[g->adj[j]];
        }

            if (g->voisins[g->id_node[g->nodes[i]]] > nb_voisins){
                nb_voisins = g->voisins[g->id_node[g->nodes[i]]];
                nv_id_node = g->id_node[g->nodes[i]];
            }

        for(j=g->cd[g->indices[g->nodes[i]]];((j<g->cd[g->indices[g->nodes[i]]+1])&&(j< (g->nombreArcs*2))); j++){
            if ((g->voisins[g->id_node[g->adj[j]]] > nb_voisins)&&(g->id_node[g->adj[j]]!=g->id_node[g->nodes[i]])) {
                nb_voisins = g->voisins[g->id_node[g->adj[j]]];
                nv_id_node = g->id_node[g->adj[j]];
                continue_=1;
                cpt++;
            }
            else if ((g->voisins[g->id_node[g->adj[j]]] == nb_voisins)&&(cpt == alea)){
                nb_voisins = g->voisins[g->id_node[g->adj[j]]];
                nv_id_node = g->id_node[g->adj[j]];
                cpt++;
                continue_=1;
            }
            else {
                cpt++;
            }
            g->voisins[g->id_node[g->adj[j]]] = 0;
        }
            g->voisins[g->id_node[g->nodes[i]]] =0;
            g->id_node[g->nodes[i]] = nv_id_node;
    }
    }
}

void draw_community(graph* g, char* nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char* str = "";
    int i;
    for(i=0; i<g->nombreArcs; i++){
            fprintf(f, "%ld ", g->id_node[g->indices[g->arcs[i].source]]);
            fprintf(f, "%ld\n", g->id_node[g->indices[g->arcs[i].cible]]);
    }
    fclose(f);
}

void free_adjlist(graph *g){
	free(g->arcs);
	free(g->cd);
	free(g->adj);
	free(g->id_node);
	free(g->indices);
	free(g->nodes);
	free(g->voisins);
	free(g);
}
