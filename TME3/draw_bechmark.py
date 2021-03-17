import networkx as nx
import matplotlib.pyplot as plt

g=nx.read_edgelist('4clusters.txt', create_using=nx.Graph(), nodetype=int)

color_map = []
for node in g:
    if node < 100:
        color_map.append('blue')
    elif node < 200: 
        color_map.append('green') 
    elif node < 300: 
        color_map.append('orange') 
    elif node < 400: 
        color_map.append('red') 

nx.draw(g, node_color=color_map)

plt.show()