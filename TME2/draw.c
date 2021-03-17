#include "draw.h"

void indicage_de_d(graph* g){
    int i;
    for(i=0; i<=g->id_max; i++){
        if (g->indices[i] != -1){
        if(g->d_out[i]>0){
            g->d_out[g->indices[i]]=g->d_out[i];
        } else{
            g->d_out[g->indices[i]]=0;
        }

        if(g->d_in[i]>0){
            g->d_in[g->indices[i]]=g->d_in[i];
        }else{
            g->d_in[g->indices[i]]=0;
        }
        }
    }
}

void drawPRWOutD(graph* g, char* nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char* str = "";
    int i, cpt = 0;
    for(i=0; i<g->nombreNoeuds; i++){
        fprintf(f, "%.15lf  ", g->P[i]);
        fprintf(f, "%ld\n", g->d_out[i]);
        if (i == (g->nombreNoeuds-1))
        printf("fin draw\n");
    }
    fclose(f);
}

void drawPRWInD(graph* g, char* nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char* str = "";
    int i;
    for(i=0; i<g->nombreNoeuds; i++){
        fprintf(f, "%.15lf  ", g->P[i]);
        fprintf(f, "%d\n", g->d_in[i]);
        if (i == (g->nombreNoeuds-1))
        printf("fin drawin\n");
    }
    fclose(f);
}

void draw_p_r(double* P_x, graph* g, double a, char* nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    power_iteration(g,a,5);

    char* str = "";
    int i;
    for(i=0; i<g->nombreNoeuds; i++){
        fprintf(f, "%.15lf  ", P_x[i]);
        fprintf(f, "%.15lf\n", g->P[i]);
        if (i == (g->nombreNoeuds-1))
        printf("fin drawin\n");
    }
    fclose(f);
}

void draw_nodes_p_r(graph* g, char* nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char* str = "";
    int i;
    for(i=0; i<g->nombreNoeuds; i++){
        fprintf(f, "%lu  ", i);
        fprintf(f, "%.30lf\n", g->P[i]);
        if (i == (g->nombreNoeuds-1))
        printf("fin drawin\n");
    }
    fclose(f);
}

/*int main(){
    graph* g;
	printf("Fichier : alr21--dirLinks--enwiki-20071018\n");
    g=liste_arcs("alr21--dirLinks--enwiki-20071018.txt");
	printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
	printf("Nombre d'arcs : %lu\n",g->nombreArcs);
    indexation(g);
    power_iteration(g,0.15,5);
   /* printf("fin premiere power");
    drawPRWInD(g,"correlation1.txt");
    drawPRWOutD(g,"correlation2.txt");
    /*-----------------------------------------*/
  /*  graph* g_2 = malloc(sizeof(graph));
	g_2->nombreNoeuds=g->nombreNoeuds;
	g_2->nombreArcs=g->nombreArcs;
	g_2->arcs= g->arcs;
	g_2->adj = g->adj;
	g_2->cd = g->cd;
	g_2->d_in = g->d_in;
	g_2 ->d_out = g->d_out;
	g_2->indices = g->indices;
	g_2->id_max = g->id_max;
    draw_p_r(g->P, g_2, 0.1, "correlation3.txt");
    draw_p_r(g->P, g_2, 0.2, "correlation4.txt");
    draw_p_r(g->P, g_2, 0.5, "correlation5.txt");
    draw_p_r(g->P, g_2, 0.9, "correlation6.txt");
    /*-----------------------------------------*/
    /*return 0;
}*/
