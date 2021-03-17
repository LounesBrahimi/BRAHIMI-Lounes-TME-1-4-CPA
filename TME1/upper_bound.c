#include "upper_bound.h"

resultat_bfs upper_bfs(adjlist* g, unsigned long s_dep){
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
        if (dis[i]== maxDis/2) {ind = i;break;}

    for(i=0; i<g->id_max; i++)
        if (ind == g->indices[i]) {ind = i;break;}

    printf("\nDistance milieu: %d\n", maxDis/2);
    resultat_bfs b;
    b = lower_bfs(g,ind);
    b = lower_bfs(g,b.noeud);
    free(f->u);
    free (f);
    free(dis);
    return b;
}

/*
int main(int argc,char** argv){
	adjlist* g;

	printf("Reading edgelist from file com-amazon.ungraph.txt\n");
	g=readedgelist("com-amazon.ungraph.txt");

	printf("Number of nodes: %lu\n",g->nombreNoeuds);
	printf("Number of edges: %lu\n",g->nombreArcs);

	printf("Building the adjacency list\n");
    mkadjlist(g);

    resultat_bfs b;
    unsigned long u = 1;
    int i;
        b = upper_bfs(g,u);
    printf("\n_________ distance : %d _________\n", b.dis);

            b = bfs(g,b.noeud);
    printf("\n_________ distance : %d _________\n", b.dis);

                b = bfs(g,b.noeud);
    printf("\n_________ distance : %d _________\n", b.dis);

	free_adjlist(g);
	return 0;
}
*/
