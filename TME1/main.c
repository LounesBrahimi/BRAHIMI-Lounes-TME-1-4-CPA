#include "exercice1.h"
#include "lower_bound.h"
#include "upper_bound.h"
#include "triangle.h"
#include <time.h>

int main(){
    printf("==== TME1 ====\n");
    printf("#1# : Compter le nombre de noeuds et d'arcs\n");
    printf("#2# : store the graph in memory\n");
    printf("#3# : BFS\n");
    printf("#4# : Nombre de triangles\n");
    int choix, choix_fichier, choix_methode, choix_bfs;
    time_t t_debut;
    printf("Votre choix : ");
    scanf("%d", &choix);
    printf("*1* : com-amazon.ungraph\n");
    printf("*2* : com-lj.ungraph\n");
    printf("*3* : com-orkut.ungraph\n");
    printf("*4* : com-friendster.ungraph\n");
    printf("Choix de fichier : ");
    scanf("%d", &choix_fichier);
    if (choix == 1){
        t_debut = time(NULL);
        printf("\n");
        if (choix_fichier == 1){
            compteur("com-amazon.ungraph.txt");
        } else if (choix_fichier == 2){
            compteur("com-lj.ungraph.txt");
        } else if (choix_fichier == 3){
            compteur("com-orkut.ungraph.txt");
        } else if (choix_fichier == 4){
            compteur("com-friendster.ungraph.txt");
        }
    } else if (choix == 2){
        printf("\n");
        printf("#1# : list of edges\n");
        printf("#2# : adjacency matrix\n");
        printf("#3# : adjacency array\n");
        printf("Choix de methode : ");
        scanf("%d", &choix_methode);
        t_debut = time(NULL);
        if (choix_methode == 1){
            printf("\n");
            arclist* g;
            if (choix_fichier == 1){
                printf("Fichier : com-amazon.ungraph\n");
                g=readarclist("com-amazon.ungraph.txt");
            } else if (choix_fichier == 2){
                printf("Fichier : com-lj.ungraph\n");
                g=readarclist("com-lj.ungraph.txt");
            } else if (choix_fichier == 3){
                printf("Fichier : com-orkut.ungraph\n");
                g=readarclist("com-orkut.ungraph.txt");
            } else if (choix_fichier == 4){
                printf("Fichier : com-friendster.ungraph\n");
                g=readarclist("com-friendster.ungraph.txt");
            }
            printf("Nombre de noeuds: %lu\n",g->nombreNoeuds);
            printf("Nombre d'arcs : %lu\n",g->nombreArcs);
            printf("Exemple arc 10 : %lu ==> %lu\n", g->arcs[10].source, g->arcs[10].cible);
            free_arclist(g);
        } else if (choix_methode == 2){
            printf("\n");
            adjmatrix* g;
            printf("Fichier : matrice");
            g=readarclistMat("matrice.txt");
            printf("\nNombre de noeuds : %lu\n",g->nombreNoeuds);
            printf("Nombre d'arcs : %lu\n",g->nombreArcs);
            indexation(g);
            mkmatrix(g);
            printf("Construction Finit.\n");
            affichageMatrice(g);
       -     free_adjmatrix(g);
        } else if (choix_methode == 3){
            printf("\n");
            adjlist* g;
            if (choix_fichier == 1){
                printf("Fichier : com-amazon.ungraph\n");
                g=readedgelist("com-amazon.ungraph.txt");
            } else if (choix_fichier == 2){
                printf("Fichier : com-lj.ungraph\n");
                g=readedgelist("com-lj.ungraph.txt");
            } else if (choix_fichier == 3){
                printf("Fichier : com-orkut.ungraph\n");
                g=readedgelist("com-orkut.ungraph.txt");
            } else if (choix_fichier == 4){
                printf("Fichier : com-friendster.ungraph\n");
                g=readedgelist("com-friendster.ungraph.txt");
            }
            printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
            printf("Nombre d'arcs : %lu\n",g->nombreArcs);
            printf("Construction de la liste d'adjacence\n");
            mkadjlist(g);
            /*free_adjlist(g);*/
        }
    } else if (choix == 3){
                printf("*1* : Lower bound\n");
                printf("*2* : Upper bound\n");
                printf("Votre choix : ");
                scanf("%d", &choix_bfs);
                t_debut = time(NULL);
                if (choix_bfs == 1){
                    printf("\n");
                    adjlist* g;
                    if (choix_fichier == 1){
                        printf("Fichier : com-amazon.ungraph\n");
                        g=readedgelist("com-amazon.ungraph.txt");
                    } else if (choix_fichier == 2){
                        printf("Fichier : com-lj.ungraph\n");
                        g=readedgelist("com-lj.ungraph.txt");
                    } else if (choix_fichier == 3){
                        printf("Fichier : com-orkut.ungraph\n");
                        g=readedgelist("com-orkut.ungraph.txt");
                    } else if (choix_fichier == 4){
                        printf("Fichier : com-friendster.ungraph\n");
                        g=readedgelist("com-friendster.ungraph.txt");
                    }
                    printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
                    printf("Nombre d'arcs : %lu\n",g->nombreArcs);
                    mkadjlist(g);
                    resultat_bfs b;
                    unsigned long u = 20;
                    int i;
                    for(i=0;i<10;i++){
                        b = lower_bfs(g,u);
                        u = b.noeud;
                    }
                    printf("\ndistance ==> %d\n", b.dis);
                   /* free_adjlist(g);*/
                } else if (choix_bfs == 2){
                    printf("\n");
                    adjlist* g;
                    if (choix_fichier == 1){
                        printf("Fichier : com-amazon.ungraph\n");
                        g=readedgelist("com-amazon.ungraph.txt");
                    } else if (choix_fichier == 2){
                        printf("Fichier : com-lj.ungraph\n");
                        g=readedgelist("com-lj.ungraph.txt");
                    } else if (choix_fichier == 3){
                        printf("Fichier : com-orkut.ungraph\n");
                        g=readedgelist("com-orkut.ungraph.txt");
                    } else if (choix_fichier == 4){
                        printf("Fichier : com-friendster.ungraph\n");
                        g=readedgelist("com-friendster.ungraph.txt");
                    }
                    printf("Nombre de noeuds : %lu\n",g->nombreNoeuds);
                    printf("Nombre d'arcs : %lu\n",g->nombreArcs);
                    mkadjlist(g);
                    resultat_bfs b;
                    unsigned long u = 1;
                    int i;
                    b = upper_bfs(g,u);
                    printf("\nDistance ==> %d\n", b.dis);
                    /*free_adjlist(g);*/
                }
    } else if (choix == 4){
                t_debut = time(NULL);
                printf("\n");
                adjlist* g;
                if (choix_fichier == 1){
                    printf("Fichier : com-amazon.ungraph\n");
                    g=liste_des_arcs("com-amazon.ungraph.txt");
                } else if (choix_fichier == 2){
                    printf("Fichier : com-lj.ungraph\n");
                    g=liste_des_arcs("com-lj.ungraph.txt");
                } else if (choix_fichier == 3){
                    printf("Fichier : com-orkut.ungraph\n");
                    g=liste_des_arcs("com-orkut.ungraph.txt");
                } else if (choix_fichier == 4){
                    printf("Fichier : com-friendster.ungraph\n");
                    g=liste_des_arcs("com-friendster.ungraph.txt");
                }
                printf("Nombre de noeud : %lu\n",g->nombreNoeuds);
                printf("Nombre d'arcs : %lu\n",g->nombreArcs);
                adjlist_dag(g);
                printf("\nnombre de triangles ==> %d\n", nombre_triangle(g));
                /*free_adjlist(g);*/
    }
    printf("\nTempsd'execution ==> %.2fs\n", (double)(time(NULL) - t_debut));
    return 0;
}
