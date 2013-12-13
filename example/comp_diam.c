#include "fgg.h"
#include <igraph/igraph.h>
#include <iostream>
#include <string>
#include <cstdio>

int
main() {
	flip_graph_generator f(6);
	f.gen();

	igraph_t g;
	f.get_flip_graph(g);

	igraph_integer_t diameter;
	igraph_vector_t path;
	igraph_vector_init(&path, 0);

	igraph_diameter(&g, &diameter, 0, 0, &path, IGRAPH_UNDIRECTED, 0);

	std::cout << "diameter: " << (int) diameter << std::endl;
	for (long int i = 0; i < igraph_vector_size(&path); i++) {
		std::cout << (int) VECTOR(path)[i] << ", ";
	}
	std::cout << std::endl;
	igraph_vector_destroy(&path);

	return 0;
}

