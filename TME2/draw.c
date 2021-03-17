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
        fprintf(f, "%d\n", g->d_out[i]);
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
        fprintf(f, "%u  ", i);
        fprintf(f, "%.30lf\n", g->P[i]);
        if (i == (g->nombreNoeuds-1))
        printf("fin drawin\n");
    }
    fclose(f);
}
