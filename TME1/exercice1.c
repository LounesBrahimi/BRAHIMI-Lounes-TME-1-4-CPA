#include "exercice1.h"

void compteur(char* nomFichier){
    unsigned long* listeNoeud;
    listeNoeud = (unsigned long*)calloc(MAX,sizeof(unsigned long));
    char c;
    unsigned long nombreNoeud = 0;
    unsigned long nombreArcs = 0;
    unsigned long source = -999999;
    unsigned long cible = -999999;
    unsigned long noeudMax = -9999999;
    FILE *file;
    file = fopen(nomFichier, "r");
    if (file) {
    /*On ignore toutes les lignes qui commence par #*/
    while (((c = getc(file)) != EOF)){
        if (c != '#') break;
        while ((c = getc(file)) != '\n'){
        }
    }
     /* On traite le tout premier noeud gauche u :*/
    source = c-'0';
    listeNoeud[source] = 1;
    noeudMax = source;
    /* On traite le tout premier noeud de droite v :*/
    fscanf (file, "%lu", &source);
    listeNoeud[source] = 1;
    noeudMax = (source < noeudMax)? noeudMax : source;
    nombreArcs++;
    while (fscanf(file,"%lu %lu", &source, &cible)==2) {
        listeNoeud[source] = 1;
        listeNoeud[cible] = 1;
        noeudMax = (source < noeudMax)? noeudMax : source;
        noeudMax = (cible < noeudMax)? noeudMax : cible;
        nombreArcs++;
    }
    int i;
    for (i = 0; i <= noeudMax; i++){
        if (listeNoeud[i] == 1) nombreNoeud++;
    }
    free(listeNoeud);
    fclose(file);
    }
    else printf("Erreur à l'ouverture du fichier!");
    printf("Nombre de noeud : %ld\nNombre d'arcs : %ld\n", nombreNoeud, nombreArcs);
}
