#include "hierarchique.h"

void hiear_detect(graph* g, double decoupage){
    g->id_node = malloc(g->id_max*sizeof(unsigned long));
        memset (g->id_node, -1, sizeof (unsigned long)*g->id_max);

    g->marquage_noeuds = calloc(g->nombreNoeuds,sizeof(int));

    int i,j,k,cpt_sim, cpt_union, v_source, v_cible;
    double degr_sim = 0.0;
    int ind_arc = 0;
    arc_suppr a_suppr[10000];
    for(i=0; i<10000;i++){
        a_suppr[i].source=-1;
        a_suppr[i].cible=-1;
    }

    for(i=0; i<g->nombreArcs; i++){
        g->id_node[g->arcs[i].source] = g->arcs[i].source;
        g->id_node[g->arcs[i].cible] = g->arcs[i].cible;
        cpt_sim = 0;
        cpt_union = 0;
        cpt_union = g->cd[g->indices[g->arcs[i].source]+1] - g->cd[g->indices[g->arcs[i].source]];
        cpt_union += g->cd[g->indices[g->arcs[i].cible]+1] - g->cd[g->indices[g->arcs[i].cible]];
        for(j=g->cd[g->indices[g->arcs[i].source]];j<g->cd[g->indices[g->arcs[i].source]+1]; j++){
            v_source = g->adj[j];
            for(k=g->cd[g->indices[g->arcs[i].cible]];k<g->cd[g->indices[g->arcs[i].cible]+1]; k++){
                v_cible = g->adj[k];
                if (v_source == v_cible){
                    cpt_sim++;
                }
            }
        }
    cpt_union -= cpt_sim;
    degr_sim = (((double)cpt_sim)/((double)cpt_union));
    if (degr_sim <= decoupage){
        a_suppr[ind_arc].source = g->arcs[i].source;
        a_suppr[ind_arc].cible= g->arcs[i].cible;
        ind_arc++;
        a_suppr[ind_arc].cible = g->arcs[i].source;
        a_suppr[ind_arc].source= g->arcs[i].cible;
        ind_arc++;
    }

    }
    printf("====Arcs supprimes : ====\n");
    bfs(g,a_suppr,g->arcs[0].source,0, 1);
}

int new_community = 1;

void bfs(graph*g, arc_suppr a_suppr[], unsigned long node, int id_communaute, int id_augm){
    if(g->marquage_noeuds[g->indices[node]] ==0){
        g->marquage_noeuds[g->indices[node]]= 1;
        g->id_node[node] = id_communaute;
    }
    int i, voisin;
    int j =0;
    int continue_ = 1;
    for(i=g->cd[g->indices[node]];i<g->cd[g->indices[node]+1]; i++){
        continue_ =1;
        voisin = g->adj[i];
        while(a_suppr[j].source != -1){
            if((a_suppr[j].source == node)&&(a_suppr[j].cible == voisin)){
                continue_ = 0;
            }
            j++;
        }
        j=0;

        if(continue_){
            if(g->marquage_noeuds[g->indices[voisin]] ==0){
                g->marquage_noeuds[g->indices[voisin]]= 1;
                g->id_node[voisin] = id_communaute;
                bfs(g,a_suppr, voisin, id_communaute, id_augm);
            }
        }
        else{
            if(g->marquage_noeuds[g->indices[voisin]] ==0){
                    printf(" %ld ==> %d\n", node, voisin);
                g->marquage_noeuds[g->indices[voisin]]= 1;
                g->id_node[voisin] = new_community;
                new_community++;
                bfs(g,a_suppr, voisin, (new_community-1), id_augm+1);
            }
        }
    }
}
