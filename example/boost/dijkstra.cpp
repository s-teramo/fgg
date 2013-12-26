#include "fgg.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>
#include <iostream>

int
main()
{
	flip_graph_generator f(6);
	f.gen();

	typedef boost::adjacency_list<boost::vecS, boost::vecS,
			boost::undirectedS, boost::no_property,
			boost::property<boost::edge_weight_t, int> > graph_t;
	typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

	const size_t v_count = f.get_vertex_count();
	std::cout << "v: " << v_count << std::endl;

	std::vector<std::pair<size_t, size_t> > edges;
	f.get_edges(edges);

	std::vector<size_t> weights(edges.size(), 1);
	graph_t g(edges.begin(), edges.end(), weights.begin(), v_count);

	const std::string names ="abcdefghijklmnopqrstuvwxyz";  

	std::vector<vertex_descriptor> p(v_count);
	std::vector<int> d(v_count);
	vertex_descriptor s = boost::vertex(0, g);

	boost::dijkstra_shortest_paths(g, s,
			boost::predecessor_map(boost::make_iterator_property_map(p.begin(),
					get(boost::vertex_index, g)))
			.distance_map(boost::make_iterator_property_map(d.begin(),
					get(boost::vertex_index, g))));

	std::cout << "distances and parents:" << std::endl;
	boost::graph_traits<graph_t>::vertex_iterator vi, vend;

	for (boost::tie(vi, vend) = boost::vertices(g); vi != vend; ++vi) {
		std::cout << "distance(" << names[*vi] << ") = " << d[*vi] << ", ";
		std::cout << "parent(" << names[*vi] << ") = " << names[p[*vi]]
				<< std::endl;
	}
	std::cout << std::endl;

	return 0;
}
