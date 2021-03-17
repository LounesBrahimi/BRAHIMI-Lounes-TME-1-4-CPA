#include "k_core_decomposition.h"

graph* liste_arcs(char* nomFichier){
	char c = '\0';
	unsigned long max=MAX;
	unsigned long source = -1;
	unsigned long cible = -1;
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
    int format = 0;
    /*while(c!='\t'){*/
    while((c!='\t')&&(c!=' ')){
        source*=format;
        source += c-'0';
        if(!format) format = 10;
        else format*= 10;
        c = getc(file);
    }
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

            g->arcs[g->nombreArcs].source = source;
            g->arcs[g->nombreArcs].cible = cible;

        noeudMax = (g->arcs[g->nombreArcs].cible < noeudMax)? noeudMax : g->arcs[g->nombreArcs].cible;
        noeudMax = (g->arcs[g->nombreArcs].source < noeudMax)? noeudMax : g->arcs[g->nombreArcs].source;

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
}else
return NULL;
}

void mkadjlist(graph* g){
	unsigned long i,u,v;
    g->d=calloc(g->nombreNoeuds,sizeof(unsigned long));
    g->cd=malloc((g->nombreNoeuds+1)*sizeof(unsigned long));
    g->indices = calloc(g->id_max,sizeof(unsigned long));
	for (i=0;i<g->nombreArcs;i++) {
		g->indices[g->arcs[i].source]++;
		g->indices[g->arcs[i].cible]++;
	}
	int j=0;
	for (i=0;i<g->nombreNoeuds;i++) {
        j+=i;
        while (g->indices[j] == 0){
            j++;
        }
        g->d[i] = g->indices[j];
        g->indices[j] = i;
        j-=i;
	}

	g->cd[0]=0;
	for (i=1;i<g->nombreNoeuds+1;i++) {
		g->cd[i]=g->cd[i-1]+g->d[i-1];
		g->d[i-1]=0;
	}

    g->adj=malloc(2*g->nombreArcs*sizeof(unsigned long));

    unsigned long u_0;
    unsigned long v_0;
	for (i=0;i<g->nombreArcs;i++) {
		u=g->arcs[i].source;
		v=g->arcs[i].cible;
		u_0 = g->indices[u];
		v_0 = g->indices[v];
		g->adj[ g->cd[u_0] + g->d[u_0]++ ]=v;
		g->adj[ g->cd[v_0] + g->d[v_0]++ ]=u;
	}
}

min_heap* core_decomposition(graph* g){
    min_heap* h = (min_heap*)malloc(sizeof(min_heap));
    min_heap* h_f = (min_heap*)malloc(sizeof(min_heap));

    h->count_=0;
    h->capacity = g->nombreNoeuds;
    h->arr = (id_degree*)malloc(h->capacity*sizeof(id_degree));
    h->indexation = (int*)malloc(h->capacity*sizeof(int));

    h_f->count_=0;
    h_f->capacity = g->nombreNoeuds;
    h_f->arr = (id_degree*)malloc(h->capacity*sizeof(id_degree));
    h_f->indexation = (int*)malloc(h->capacity*sizeof(int));

    int i;
    for(i=0; i<g->nombreNoeuds; i++){
        insert(h,g->d[i], i, 0, -1);
    }

    int j=0;
    id_degree n_min_d;
    int id = g->nombreNoeuds;
    int c=0;
    while(j<g->nombreNoeuds){
        n_min_d = PopMin(h);
        c = (n_min_d.d > c) ? n_min_d.d : c;
        n_min_d.c = c;
        for(i=g->cd[n_min_d.indice]; i<g->cd[n_min_d.indice+1]; i++){
            if (h->indexation[g->indices[g->adj[i]]] != -1){
                decrementer(h,h->indexation[g->indices[g->adj[i]]]);
            }
        }
        n_min_d.id_node = id;
        insert(h_f,n_min_d.d, n_min_d.indice, n_min_d.c, n_min_d.id_node);
        id--;
        j++;
    }

    int* e_n = (int*)calloc((g->nombreNoeuds+1), sizeof(int));
    unsigned long source = -1;
    unsigned long source_id = -1;
    unsigned long cible = -1;
    unsigned long cible_id = -1;
    for(i=0; i<g->nombreArcs; i++){
        source = g->arcs[i].source;
        source_id = h_f->arr[g->indices[source]].id_node;
        cible = g->arcs[i].cible;
        cible_id = h_f->arr[g->indices[cible]].id_node;
        if (source_id > cible_id){
            e_n[source_id]++;
        } else {
            e_n[cible_id]++;
        }
    }

    int* e_sg = (int*)calloc((g->nombreNoeuds+1), sizeof(int));
    int dansest_core = 0;
    e_sg[0] = 0;
    e_sg[1] = 0;
    if (h_f->arr[0].c == c) dansest_core++;
    double max_d_sg = -1;
    double densite;
    int max_edges = 0;
    int max_nodes = 0;
    for(i=2; i<=g->nombreNoeuds; i++){
        e_sg[i]= e_n[i]+e_sg[i-1];
        densite = ((double)(((double)e_sg[i])/((double)i)));
        if ( densite > max_d_sg){
            max_d_sg = densite;
            max_edges = e_sg[i];
            max_nodes = i;
        }
        if (h_f->arr[i-1].c == c) dansest_core++;

    }
    long long int calcul = ((long long int)((long long int)max_nodes)*((long long int )(max_nodes-1)));
    calcul /= 2;
    double edge_d = ((double)max_edges)/ (double)calcul;
    printf("Core value of the graph : %d\n", c);
    printf("The average degree density : %f\n", max_d_sg);
    printf("The edge density : %e\n", edge_d);
    printf("the size of a densest core ordering prefix : %d\n", dansest_core);
    /*make_a_plot(h_f, "",g);*/
        free(h->indexation);
    free(h->arr);
    free(h);
    return h_f;
    /*free(h_f->arr);
    free(h_f->indexation);
    free(h_f);*/

}

void make_a_plot(min_heap* h, char* nom_fichier, graph* g){
FILE *f = fopen(nom_fichier, "w");
printf("\n\n===Generation d'un graph===\n");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char* str = "";
    int i, cpt = 0;
    long int max=-1, max_2=-1, max_3=-1, max_4=-1;
    int min_d2=100000, min_d3=100000, min_d4=100000, tmp = 0, tmp2 =0;
    int tmp_d, tmp2_d;
    long int d_min = 1000000;
    for(i=0; i<g->nombreNoeuds; i++){
            if (h->arr[h->indexation[i]].c > 13){
                if (g->d[i] < d_min){
                        tmp = max;
                        tmp_d = d_min;
                        max = i;
                        d_min = g->d[i];
                        tmp2 = max_2;
                        tmp2_d = min_d2;
                        max_2 = tmp;
                        min_d2 = tmp_d;
                        tmp = max_3;
                        tmp_d = min_d3;
                        max_3 = tmp2;
                        min_d3 = tmp2_d;
                        max_4 = tmp;
                        min_d4 = tmp_d;
                }else if (g->d[i] < min_d2){
                        tmp = max_2;
                        tmp_d = min_d2;
                        max_2 = i;
                        min_d2 = g->d[i];
                        tmp2 = max_3;
                        tmp2_d = min_d3;
                        max_3 = tmp;
                        min_d3 = tmp_d;
                        max_4 = tmp2;
                        min_d4 = tmp2_d;
                }else if (g->d[i] < min_d3){
                        max_4 = max_3;
                        min_d4 = min_d3;
                        max_3 = i;
                        min_d3 = g->d[i];
                }else if (g->d[i] < min_d4){
                        max_4 = i;
                        min_d4 = g->d[i];
                }
            }
        fprintf(f, "%d  ", g->d[i]);
        fprintf(f, "%d\n", h->arr[h->indexation[i]].c);

        if (i == (g->nombreNoeuds-1))
        printf("\n");
    }
    fclose(f);

    FILE *file=fopen("ID.txt","r");
    int id;
    char nom[10000];
    for(i=0; i<g->nombreArcs; i++){
	fscanf(file,"%lu %[^\n]", &id, nom);
        if(id == max){
            printf("Anomalous : %s\n", nom);
        }else
        if(id == max_2){
            printf("Anomalous : %s\n", nom);
        }else
        if(id == max_3){
            printf("Anomalous : %s\n", nom);
        }else
        if(id == max_4){
            printf("Anomalous : %s\n", nom);
        }
    }
    fclose(file);
}
