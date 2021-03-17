#include "k_core_decomposition.h"

int main()
{
    printf("\n\n");
    printf("==== TME4 ====\n");
    printf("#1# : k-core decomposition\n");
    printf("#2# : Graph mining with k-core\n");
    int choix, choix_fichier;
    printf("Votre choix : ");
    scanf("%d", &choix);
    if (choix == 1){
        graph* g;
        printf("\n*1* : com-amazon.ungraph\n");
        printf("*2* : com-lj.ungraph\n");
        printf("*3* : com-orkut.ungraph\n");
        printf("*4* : com-friendster.ungraph\n");
        printf("Choix de fichier : ");
        scanf("%d", &choix_fichier);
        if (choix_fichier == 1){
            printf("Fichier : com-amazon.ungraph\n");
            g=liste_arcs("com-amazon.ungraph.txt");
        } else if (choix_fichier == 2){
            printf("Fichier : com-lj.ungraph\n");
            g=liste_arcs("com-lj.ungraph.txt");
        } else if (choix_fichier == 3){
            printf("Fichier : com-orkut.ungraph\n");
            g=liste_arcs("com-orkut.ungraph.txt");
        } else if (choix_fichier == 4){
            printf("Fichier : com-friendster.ungraph\n");
            g=liste_arcs("com-friendster.ungraph.txt");
        }
        printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
        printf("Nombre d'arcs : %lu\n\n",g->nombreArcs);
        mkadjlist(g);
        core_decomposition(g);
    } else if (choix == 2){
        graph* g;
        printf("Fichier : net\n");
        g=liste_arcs("net.txt");
        printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
        printf("Nombre d'arcs : %lu\n\n",g->nombreArcs);
        mkadjlist(g);
        min_heap* h = core_decomposition(g);
        make_a_plot(h, "google_scholar.txt", g);
        printf("Sauvegarder dans google_scholar.txt\n");
    }
    return 0;
}
