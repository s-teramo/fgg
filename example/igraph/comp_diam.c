#include "fgg.h"
#include <igraph/igraph.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>


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

void dump_tri(flip_graph_generator& fgg, const size_t& v_id) 
{
	std::vector<std::pair<size_t, size_t> > te;
	fgg.get_triangulation_edges(v_id, te);

	igraph_t tg;
	build_flip_graph(fgg.get_polygon_vertex_count(), te, tg);
	std::ostringstream os;
	size_t digit = (size_t) log10(fgg.get_vertex_count());
	os << std::setfill('0') << std::setw(digit) << v_id;
	std::string fname = "triangulation-" + os.str() + ".gml";
	FILE* fp = fopen(fname.c_str(), "w");
	igraph_write_graph_gml(&tg, fp, 0, 0);
	fclose(fp);
	igraph_destroy(&tg);
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

	igraph_integer_t diameter;
	igraph_vector_t path;
	igraph_vector_init(&path, 0);

	igraph_diameter(&g, &diameter, 0, 0, &path, IGRAPH_UNDIRECTED, 0);

	std::cout << "diameter: " << (int) diameter << std::endl;
	for (long int i = 0; i < igraph_vector_size(&path); i++) {
		std::cout << (int) VECTOR(path)[i] << ", ";
		dump_tri(f, (size_t) VECTOR(path)[i]);
	}
	std::cout << std::endl;
	igraph_vector_destroy(&path);

	igraph_destroy(&g);

	return 0;
}
