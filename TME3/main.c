#include "label_propagation.h"
#include "hierarchique.h"

int main(){
    printf("\n\n");
    printf("==== TME3 ====\n");
    printf("#1# : Simple bechmark\n");
    printf("#2# : Label propagation\n");
    printf("#3# : Regroupement hierarchique\n");
    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);
    if (choix == 1){
        float p, q;
        printf("\nSasie de : P = ");
        scanf("%f", &p);
        printf("Sasie de : q = ");
        scanf("%f", &q);
        simple_bechmark("4clusters.txt", p, q);
        printf("\nResultat sauvegarder dans 4clusters.txt\n");
    } else if (choix == 2){
        graph* g;
        printf("Fichier 4clusters\n");
        g=readedgelist("4clusters.txt");
        printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
        printf("Nombre d'arcs : %lu\n",g->nombreArcs);
        mkadjlist(g);
        indexation(g);
        label_propagation(g);
    /*  hiear_detect(g, 0.1);*/
        draw_community(g, "label_prop.txt");
        printf("\nResultat sauvegarder dans label_prop.txt\n");
    } else if (choix == 3){
        graph* g;
        printf("Fichier 4clusters\n");
        g=readedgelist("4clusters.txt");
        printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
        printf("Nombre d'arcs : %lu\n",g->nombreArcs);
        mkadjlist(g);
        indexation(g);
        hiear_detect(g, 0.1);
        draw_community(g, "hierarchique.txt");
        printf("\nResultat sauvegarder dans hierarchique.txt\n");
    }
    return 0;
}
