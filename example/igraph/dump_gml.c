#include "fgg.h"
#include <igraph/igraph.h>
#include <cstdio>
#include <string>
#include <vector>

void
build_flip_graph(const size_t& v_count,
		const std::vector<std::pair<size_t, size_t> >& edges,
		igraph_t& flip_graph)
{
	igraph_vector_t E;
	igraph_vector_init(&E, edges.size() * 2);
	long int edge_count = 0;
	std::vector<std::pair<size_t, size_t> >::const_iterator it;
	for (it = edges.begin(); it != edges.end(); it++) {
		VECTOR(E)[edge_count] = (*it).first;
		VECTOR(E)[edge_count + 1] = (*it).second;
		edge_count += 2;
	}
	igraph_empty(&flip_graph, v_count, IGRAPH_UNDIRECTED);
	igraph_add_edges(&flip_graph, &E, 0);
	igraph_vector_destroy(&E);
}

void
save(igraph_t& flip_graph, const std::string& filename) 
{
	FILE *fp  = fopen(filename.c_str(), "w");
	igraph_write_graph_gml(&flip_graph, fp, 0, 0);
	fclose(fp);
}

int
main()
{
	flip_graph_generator f(6);
	f.gen(); 

	std::vector<std::pair<size_t, size_t> > edges;
	f.get_edges(edges);
	igraph_t g;

	build_flip_graph(f.get_vertex_count(), edges, g);
	save(g, "hexagon_flip_graph.gml");

	igraph_destroy(&g);

	return 0;
}
