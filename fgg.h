#pragma once

#include <string>
#include <vector>
#include <map>

#include <igraph/igraph.h>

class flip_graph_generator {
private:
	size_t polygon_vertex_count;
	size_t vertex_count;
	igraph_t flip_graph;
	std::vector<std::string> vertices;
	std::map<std::string, size_t> dss_id_ref_tab;
	std::vector<std::pair<size_t, size_t> > edges;

	std::string get_init_dss();
	void print_dss(const std::string&) const;
	void get_neighbors(const std::string&, std::vector<std::string>&); 
	void split(const std::string&, std::vector<std::string>&);
	std::string concatenate(const std::vector<std::string>&,
			const std::string&, const size_t,
			const std::string&, const size_t) const;
	void neighbor_dss_from_last_word(std::vector<std::string>&,
			const std::vector<std::string>&, const size_t, const size_t);
	void neighbor_dss_from_not_last_word(std::vector<std::string>&,
			const std::vector<std::string>&, const size_t, const size_t);
	void build_flip_graph();

public:
	flip_graph_generator(size_t);
	~flip_graph_generator();
	void gen();
	void save(const std::string&) const;
	void write_triangulation_graph(size_t) const;
	void get_flip_graph(igraph_t& g);
	void get_vertices(std::vector<std::string>&);
};
