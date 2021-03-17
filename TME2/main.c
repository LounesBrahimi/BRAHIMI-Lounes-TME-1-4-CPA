#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "draw.h"

int main(){
    printf("\n\n");
    printf("==== TME2 ====\n");
    printf("#1# : PageRank\n");
    printf("#2# : Personalized PageRank\n");
    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);
    if ((choix == 1)||(choix == 2)){
        graph* g;
        printf("Fichier : alr21--dirLinks--enwiki-20071018\n");
        g=liste_arcs("alr21--dirLinks--enwiki-20071018.txt");
        printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
        printf("Nombre d'arcs : %lu\n",g->nombreArcs);
        indexation(g);
        if (choix == 1){
            power_iteration(g,0.15,1);
        } else if (choix == 2){
            double* P_0 = calloc(g->nombreNoeuds,sizeof(double));
            P_0[g->indices[442682]] = 1;
            power_iteration_rooted(g,0.15,5, P_0);
        }
        int i;
        double maxP[5], tmp1, tmp2, minP[5];
        int tmpN1, tmpN2, maxN[5], minN[5];
        /* initialisation max*/
        maxP[0] = -1;maxP[1] = -1;maxP[2] = -1;maxP[3] = -1;maxP[4] = -1;
        maxN[0] = -1;maxN[1] = -1;maxN[2] = -1;maxN[3] = -1;maxN[4] = -1;
        /* initialisation min*/
        minP[0] = 100000;minP[1] = 100000;minP[2] = 100000;minP[3] = 100000;minP[4] = 100000;
        minN[0] = 100000;minN[1] = 100000;minN[2] = 100000;minN[3] = 100000;minN[4] = 100000;
        /*max--------------------------------max*/
        for(i=0; i<g->nombreNoeuds;i++){
            if(g->P[i] > maxP[4]){
                if (maxP[4] == -1){
                    maxP[4] = g->P[i];
                    maxN[4] = i;
                }
                else {
                    tmp1 = maxP[4];
                    tmpN1 = maxN[4];
                    tmp2 = maxP[3];
                    tmpN2 = maxN[3];
                    maxP[4] = g->P[i];
                    maxN[4] = i;
                    maxP[3] = tmp1;
                    maxN[3] = tmpN1;
                    tmp1 = maxP[2];
                    tmpN1 = maxN[2];
                    maxP[2] = tmp2;
                    maxN[2] = tmpN2;
                    tmp2 = maxP[1];
                    tmpN2 = maxN[1];
                    maxP[1] = tmp1;
                    maxN[1] = tmpN1;
                    maxP[0] = tmp2;
                    maxN[0] = tmpN2;
                }
            }
            else if(g->P[i] > maxP[3]){
                if (maxP[3] == -1){
                    maxP[3] = g->P[i];
                    maxN[3] = i;
                }
                else {
                    tmp1 = maxP[3];
                    tmpN1 = maxN[3];
                    tmp2 = maxP[2];
                    tmpN2 = maxN[2];
                    maxP[3] = g->P[i];
                    maxN[3] = i;
                    maxP[2] = tmp1;
                    maxN[2] = tmpN1;
                    tmp1 = maxP[1];
                    tmpN1 = maxN[1];
                    maxP[1] = tmp2;
                    maxN[1] = tmpN2;
                    maxP[0] = tmp1;
                    maxN[0] = tmpN1;
                }
            }
            else if(g->P[i] > maxP[2]){
                if (maxP[2] == -1){
                    maxP[2] = g->P[i];
                    maxN[2] = i;
                }
                else {
                    tmp1 = maxP[2];
                    tmpN1 = maxN[2];
                    tmp2 = maxP[1];
                    tmpN2 = maxN[1];
                    maxP[2] = g->P[i];
                    maxN[2] = i;
                    maxP[1] = tmp1;
                    maxN[1] = tmpN1;
                    maxP[0] = tmp2;
                    maxN[0] = tmpN2;
                }
            }
            else if(g->P[i] > maxP[1]){
                if (maxP[1] == -1){
                    maxP[1] = g->P[i];
                    maxN[1] = i;
                }
                else{
                    tmp1 = maxP[1];
                    tmpN1 = maxN[1];
                    maxP[1] = g->P[i];
                    maxN[1] = i;
                    maxP[0] = tmp1;
                    maxN[0] = tmpN1;
                }
            }
            else if(g->P[i] > maxP[0]){
                maxP[0] = g->P[i];
                maxN[0] = i;
            }
            if(g->P[i] < minP[4]){
                if (minP[4] == -1){
                    minP[4] = g->P[i];
                    minN[4] = i;
                }
                else {
                    tmp1 = minP[4];
                    tmpN1 = minN[4];
                    tmp2 = minP[3];
                    tmpN2 = minN[3];
                    minP[4] = g->P[i];
                    minN[4] = i;
                    minP[3] = tmp1;
                    minN[3] = tmpN1;
                    tmp1 = minP[2];
                    tmpN1 = minN[2];
                    minP[2] = tmp2;
                    minN[2] = tmpN2;
                    tmp2 = minP[1];
                    tmpN2 = minN[1];
                    minP[1] = tmp1;
                    minN[1] = tmpN1;
                    minP[0] = tmp2;
                    minN[0] = tmpN2;
                }
            }
            else if(g->P[i] < minP[3]){
                if (minP[3] == -1){
                    minP[3] = g->P[i];
                    minN[3] = i;
                }
                else {
                    tmp1 = minP[3];
                    tmpN1 = minN[3];
                    tmp2 = minP[2];
                    tmpN2 = minN[2];
                    minP[3] = g->P[i];
                    minN[3] = i;
                    minP[2] = tmp1;
                    minN[2] = tmpN1;
                    tmp1 = minP[1];
                    tmpN1 = minN[1];
                    minP[1] = tmp2;
                    minN[1] = tmpN2;
                    minP[0] = tmp1;
                    minN[0] = tmpN1;
                }
            }
            else if(g->P[i] < minP[2]){
                if (minP[2] == -1){
                    minP[2] = g->P[i];
                    minN[2] = i;
                }
                else {
                    tmp1 = minP[2];
                    tmpN1 = minN[2];
                    tmp2 = minP[1];
                    tmpN2 = minN[1];
                    minP[2] = g->P[i];
                    minN[2] = i;
                    minP[1] = tmp1;
                    minN[1] = tmpN1;
                    minP[0] = tmp2;
                    minN[0] = tmpN2;
                }
            }
            else if(g->P[i] < minP[1]){
                if (minP[1] == -1){
                    minP[1] = g->P[i];
                    minN[1] = i;
                }
                else{
                    tmp1 = minP[1];
                    tmpN1 = minN[1];
                    minP[1] = g->P[i];
                    minN[1] = i;
                    minP[0] = tmp1;
                    minN[0] = tmpN1;
                }
            }
            else if(g->P[i] < minP[0]){
                minP[0] = g->P[i];
                minN[0] = i;
            }
        }
 /*-------------------------------------*/
        int cpt_0 = 0, cpt_1 = 0, cpt_2 = 0, cpt_3 = 0, cpt_4 = 0, cpt = 0;
        int cpt_5 = 0, cpt_6 = 0, cpt_7 = 0, cpt_8 = 0, cpt_9 = 0;
        for(i=0; i<g->id_max; i++){
            if((g->indices[i] == maxN[0])||(g->indices[i] == maxN[1])||
            (g->indices[i] == maxN[2])||(g->indices[i] == maxN[3])||
            (g->indices[i] == maxN[4])||(g->indices[i] == minN[0])||
            (g->indices[i] == minN[1])||(g->indices[i] == minN[2])||
            (g->indices[i] == minN[3])||(g->indices[i] == minN[4])){
                    cpt++;
                    if (!cpt_0)
                    if (g->indices[i] == maxN[0]){
                        maxN[0]=i;
                        cpt_0++;
                    }
                    if (!cpt_1)
                    if (g->indices[i] == maxN[1]){
                        maxN[1]=i;
                        cpt_1;
                    }
                    if (!cpt_2)
                    if (g->indices[i] == maxN[2]){
                        maxN[2]=i;
                        cpt_2++;
                    }
                    if (!cpt_3)
                    if (g->indices[i] == maxN[3]){
                        maxN[3]=i;
                        cpt_3++;
                    }
                    if (!cpt_4){
                    if (g->indices[i] == maxN[4]){
                        maxN[4]=i;
                        cpt_4++;
                    }
                    }
                    if (!cpt_5)
                    if (g->indices[i] == minN[0]){
                        minN[0]=i;
                        cpt_5++;
                    }
                    if (!cpt_6)
                    if (g->indices[i] == minN[1]){
                        minN[1]=i;
                        cpt_6;
                    }
                    if (!cpt_7)
                    if (g->indices[i] == minN[2]){
                        minN[2]=i;
                        cpt_7++;
                    }
                    if (!cpt_8)
                    if (g->indices[i] == minN[3]){
                        minN[3]=i;
                        cpt_8++;
                    }
                    if (!cpt_9){
                    if (g->indices[i] == minN[4]){
                        minN[4]=i;
                        cpt_9++;
                    }
                    }
                }
        }
        char s_max_1[10000],s_max_2[10000],s_max_3[10000],s_max_4[10000],s_max_5[10000];
        char s_min_1[10000],s_min_2[10000],s_min_3[10000],s_min_4[10000],s_min_5[10000];
        FILE *file=fopen("alr21--pageNum2Name--enwiki-20071018.txt","r");
        long long int id;
        char nom[10000];
        int c=0;
        for(i=0; i<g->nombreArcs; i++){
            fscanf(file,"%llu %[^\n]", &id, nom);
            if(id == maxN[0]){
                c++;
                strcpy(s_max_1, nom);
            }else if(id == maxN[1]){
                c++;
                strcpy(s_max_2, nom);
            }else if(id == maxN[2]){
                c++;
                strcpy(s_max_3, nom);
            }else if(id == maxN[3]){
                c++;
                strcpy(s_max_4, nom);
            }else if(id == maxN[4]){
                c++;
                strcpy(s_max_5, nom);
            }
            if(id == minN[0]){
                c++;
                strcpy(s_min_1, nom);
            }else if(id == minN[1]){
                c++;
                strcpy(s_min_2, nom);
            }else if(id == minN[2]){
                c++;
                strcpy(s_min_3, nom);
            }else if(id == minN[3]){
                c++;
                strcpy(s_min_4, nom);
            }else
            if(id == minN[4]){
                c++;
                strcpy(s_min_5, nom);
            }
            if(c==10) break;
        }
        fclose(file);
        printf("====Highest PageRank====\n\n");
        printf("%s\n", s_max_5);
        printf("PR : %f\n", maxP[4]);
        printf("%s\n", s_max_4);
        printf("PR : %f\n", maxP[3]);
        printf("%s\n", s_max_3);
        printf("PR : %f\n", maxP[2]);
        printf("%s\n", s_max_2);
        printf("PR : %f\n", maxP[1]);
        printf("%s\n", s_max_1);
        printf("PR : %f\n", maxP[0]);
        printf("\n====Lowest PageRank====\n\n");
        printf("%s\n", s_min_5);
        printf("PR : %e\n", minP[4]);
        printf("%s\n", s_min_4);
        printf("PR : %e\n", minP[3]);
        printf("%s\n", s_min_3);
        printf("PR : %e\n", minP[2]);
        printf("%s\n", s_min_2);
        printf("PR : %e\n", minP[1]);
        printf("%s\n", s_min_1);
        printf("PR : %e\n", minP[0]);
        }
    return 0;
}
