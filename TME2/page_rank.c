#include "page_rank.h"

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

    g->d_out = malloc(max*sizeof(int));
    memset (g->d_out, 0, sizeof (int)*max);

    g->d_in = malloc(max*sizeof(int));
    memset (g->d_in, 0, sizeof (int)*max);

    g->indices = malloc(max*sizeof(unsigned long));
    memset (g->indices, -1, sizeof (unsigned long)*max);

	if (file) {
        /*On ignore toutes les lignes qui commence par #*/
        while (((c = getc(file)) != EOF)){
            if (c != '#') break;
            while ((c = getc(file)) != '\n'){
            }
        }
    /* On traite le tout premier noeud gauche u :*/
    int format = 0;
    while(c!='\t'){
        source*=format;
        source += c-'0';
        if(!format) format = 10;
        else format*= 10;
        c = getc(file);
    }
    listeNoeuds[source] = 1;
    g->d_out[source]++;
    g->indices[source]+=2;
    noeudMax = source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf(file, "%lu", &cible);
    listeNoeuds[cible] = 1;
    g->d_in[cible]++;
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
    g->indices[cible]+=2;
    g->nombreArcs++;

	while (fscanf(file,"%lu %lu", &source, &cible)==2) {
		listeNoeuds[source] = 1;
		listeNoeuds[cible] = 1;

		g->indices[source]+=2;
		g->indices[cible]+=2;

		g->d_out[source]++;
        g->d_in[cible]++;

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

void initialisation_P(double* P, double* P2, unsigned long nombreNoeuds){

    double d= 1.0/nombreNoeuds;
    int i;
    for(i=0; i<nombreNoeuds; i++)
        P[i]=d;
        P2[i]=0;
}

void indexation(graph* g){
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

double* permutationVecteurs(graph* g, double* d){
    memset (d, 0, sizeof(double)*g->nombreNoeuds);
    double* mid = d;
    d = g->P;
    g->P = mid;
    return d;
}

void power_iteration_rooted(graph* g, double a, int t, double* P_0){
     double* P1 = (double*)malloc(g->nombreNoeuds*sizeof(double));
     g->P = calloc(g->nombreNoeuds,sizeof(double));
     initialisation_P(P1, g->P, g->nombreNoeuds);
     int i, j;
    for(j=0; j<t; j++){
      if (j){
        P1 = permutationVecteurs(g, P1);
      }
     for(i=0; i<g->nombreArcs; i++){
        g->P[g->indices[g->arcs[i].cible]]+=
            ((double)P_0[g->indices[g->arcs[i].source]])* (1.0/((double)g->d_out[g->arcs[i].source]));
     }
     double s = 0;
     for(i=0; i<g->nombreNoeuds; i++){
        P_0[i] = a * P_0[i];
        g->P[i]= (1.0-a)*((double)g->P[i]);
        g->P[i]+= P_0[i];
        s+=g->P[i];
    }

    for(i=0; i<g->nombreNoeuds; i++){
        g->P[i]+= P_0[i]*((1.0-s)/((double)g->nombreNoeuds));
    }
    }
}

void power_iteration(graph* g, double a, int t){
     double* P1 = (double*)malloc(g->nombreNoeuds*sizeof(double));
     g->P = calloc(g->nombreNoeuds,sizeof(double));
     initialisation_P(P1, g->P, g->nombreNoeuds);
     int i, j;
    for(j=0; j<t; j++){
      if (j){
        P1 = permutationVecteurs(g, P1);
      }
     for(i=0; i<g->nombreArcs; i++){
        g->P[g->indices[g->arcs[i].cible]]+=
            ((double)P1[g->indices[g->arcs[i].source]])* ((double)(1.0/((double)g->d_out[g->arcs[i].source])));
     }
    double s = 0;
    double aI = a*(1.0/((double)g->nombreNoeuds));
    for(i=0; i<g->nombreNoeuds; i++){
        g->P[i]= (1.0-a)*g->P[i];
        g->P[i]+= aI;
        s+=g->P[i];
    }

    for(i=0; i<g->nombreNoeuds; i++){
        g->P[i]+= ((1.0-s)/g->nombreNoeuds);
    }
    }
}
