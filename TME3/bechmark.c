#include "bechmark.h"

void simple_bechmark(char* nom_fichier, double p_, double q_){
    int* graph = (int*) malloc(400*sizeof(int));
    int i, p, q;
    p = (int)(p_*100);
    q= (int)(q_*100);

    for(i=0; i<400; i++){
        graph[i] = i;
    }
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int j;
    for(i=0; i<400; i++){
        if(i<100){
            for(j=(i+1); j<100; j++){
                if((rand()%100)<= p){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
            for(j=(i+1); j<400; j++){
                if((rand()%100)<= q){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
        }
        else if(i<200){
            for(j=(i+1); j<200; j++){
                if((rand()%100)<= p){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
            for(j=(i+1); j<400; j++){
                if((rand()%100)<= q){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
        }
        else if(i<300){
            for(j=(i+1); j<300; j++){
                if((rand()%100)<= p){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
            for(j=(i+1); j<400; j++){
                if((rand()%100)<= q){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
        }
        else if(i<400){
            for(j=(i+1); j<400; j++){
                if((rand()%100)<= p){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
            for(j=(i+1); j<400; j++){
                if((rand()%100)<= q){
                    fprintf(f, "%d  %d\n", i, j);
                }
            }
        }
    }
    fclose(f);
}
