import networkx as nx
import matplotlib.pyplot as plt

g=nx.read_edgelist('hierarchique.txt', create_using=nx.Graph(), nodetype=int)

color_map = []
for node in g:
    if node < 1:
        color_map.append('blue')
    elif node < 2: 
        color_map.append('green') 
    elif node < 3: 
        color_map.append('orange') 
    elif node < 4: 
        color_map.append('red') 

nx.draw(g, node_color=color_map, with_labels=True)

plt.show()