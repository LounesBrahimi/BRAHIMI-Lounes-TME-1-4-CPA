#include "lower_bound.h"

resultat_bfs lower_bfs(adjlist* g, unsigned long s_dep){
    unsigned long u = g->indices[s_dep];

    unsigned long *dis=calloc(g->nombreNoeuds,sizeof(unsigned long));
    memset (dis, -1, sizeof (unsigned long) * g->nombreNoeuds);
    resultat_bfs* res = malloc(sizeof(resultat_bfs));
    res->dis = -1;
    res->noeud = -1;

    fifo* f = malloc(sizeof(fifo));
    f->nombre_elements = 0;
    f->queue = 0;
    f->tete = 0;
    f->taille = g->nombreNoeuds;
    f->u = (unsigned long*) malloc(g->nombreNoeuds*sizeof(unsigned long));
    enfiler(f, u);
    dis[u] = 0;

    unsigned long v = -1;

    while(f->nombre_elements > 0){
        u = defiler(f);
        int i;
         for(i=g->cd[u]; i<g->cd[u+1]; i++){

            v = g->indices[g->adj[i]];
            if (dis[v] == -1)
            {

                enfiler(f, v);
                dis[v]= dis[u] + 1;
            }
        }
    }
    int maxDis = 0;
    int ind = -1;

    int i;
    for (i = 0; i < g->nombreNoeuds; i++)
    {
        if (dis[i] > maxDis)
        {
            maxDis = dis[i];
            ind = i;
        }
    }

    for(i=0; i<g->id_max; i++)
        if (ind == g->indices[i]) {ind = i;break;}

    free(f->u);
    free (f);
    free(dis);

    res->dis = maxDis;
    res->noeud = ind;

    return *res;
}
