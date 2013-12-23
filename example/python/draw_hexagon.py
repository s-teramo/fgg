#! /usr/bin/env python2.7

import fgg
import networkx as nx
import matplotlib.pyplot as plt
try:
	from networkx import graphviz_layout
except ImportError:
	raise ImportError("This example needs Graphviz and either PyGraphviz or pydot")


if __name__ == '__main__':
	f = fgg.flip_graph_generator(6)
	f.gen()

	edges = fgg.edge_vector()
	f.get_edges(edges)

	G = nx.Graph()
	for e in edges:
		G.add_edge(e[0], e[1])

	pos = nx.graphviz_layout(G, prog = 'neato', args = '')
	plt.figure(figsize = (8, 8))
	nx.draw(G, pos, node_size = 250, alpha = 0.75,
			node_color = "yellow", with_labels = True)
	plt.axis('equal')
	plt.savefig('hexagon_flip_graph.png')
	plt.show()
