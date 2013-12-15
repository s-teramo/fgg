#include "fgg.h"
#include <igraph/igraph.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <stack>


/** Constructor of flip_graph_generator. Initializing the number of
 * polygon_vertex_count and vertex_count.
 * @param n the number of vertices of a target convex polygon
 */
flip_graph_generator::flip_graph_generator(size_t n) :
		polygon_vertex_count(n), vertex_count(0)
{
	assert(n > 2);
}

/** Destructor of flip_graph_generator. Just destroying igraph_t.
 */
flip_graph_generator::~flip_graph_generator()
{
	igraph_destroy(&flip_graph);
}

/** Generating a Davenport-Schinzel sequence which is used as 
 * a seed of vertex-enumeration. Generated sequence is one of the
 * simplest sequences, we think.
 * @return string data of Davenport-Schinzel sequence
 */
std::string
flip_graph_generator::get_init_dss()
{
	std::string s;
	char separator = 0;
	s += separator;
	for (size_t i = 1; i < polygon_vertex_count - 1; i++) {
		s += i;
		s += separator;
	}
	assert(s.size() == 2 * polygon_vertex_count - 3);
	return s;
}

/** Write given Davenport-Schinzel sequence to standard output.
 * Since this method is just debug usage only, we define as private.
 * @param dss string data storing Davenport-Schinzel sequence.
 */
void
flip_graph_generator::print_dss(const std::string& dss) const
{
	for (std::string::const_iterator i = dss.begin(); i != dss.end(); i++) {
		std::cout << (int) *i;
	}
	std::cout << std::endl;
}

/** Split given Davenport-Schinzel sequence into polygon_vertex_count
 * - 1 subsequences. Each subsequence is in decreasing order of
 * alphabet.
 * @param dss as an input Davenport-Schinzel sequence
 * @param split_strings stored vector of strings of subsequences.
 */
void
flip_graph_generator::split(const std::string& dss,
		std::vector<std::string>& split_strings)
{
	split_strings.clear();
	int head = 0; 
	for (size_t i = 1; i < polygon_vertex_count - 1; i++) {
		int tail;
		for (tail = head; (unsigned) dss[tail] != i; tail++) ;
		split_strings.push_back(dss.substr(head, tail - head));
		head = tail;
	}
	split_strings.push_back(dss.substr(head));
}

/** Concatenate subsequences in order to generate a new
 * Davenport-Schinzel sequence.
 * @param splits is vector of splited Davenport-Schinzel sequence.
 * @param swap_string1
 * @param swap_pos1
 * @param swap_string2
 * @param swap_pos2
 */
std::string
flip_graph_generator::concatenate(const std::vector<std::string>& splits,
		const std::string& swap_string1, const size_t swap_pos1,
		const std::string& swap_string2, const size_t swap_pos2) const
{
	std::string concat_string;
	for (size_t i = 0; i < swap_pos1; i++) {
		concat_string += splits[i];
	}
	concat_string += swap_string1;
	for (size_t i = swap_pos1 + 1; i < swap_pos2; i++) {
		concat_string += splits[i];
	}
	concat_string += swap_string2;
	for (size_t i = swap_pos2 + 1; i < splits.size(); i++) {
		concat_string += splits[i];
	}
	return concat_string;
}

/**
 *
 */
void
flip_graph_generator::neighbor_dss_from_last_word(
		std::vector<std::string>& neighbor_vec,
		const std::vector<std::string>& split_strings, 
		const size_t ith_dec_seq, const size_t jth_word)
{
	std::string s1 = split_strings[ith_dec_seq];
	s1.erase((char) jth_word, 1); 

	char c = split_strings[ith_dec_seq][jth_word - 1];
	std::string s2;
	size_t swap_pos2;
	for (swap_pos2 = ith_dec_seq + 1; swap_pos2 < split_strings.size();
				swap_pos2++) {
		char find_target_char = split_strings[ith_dec_seq][jth_word];
		size_t pos = split_strings[swap_pos2].find(find_target_char, 0);
		if (pos == std::string::npos) {
			continue;
		} else {
			s2 = split_strings[swap_pos2];
			s2 = s2.insert(pos, 1, c);
			break;
		}
	}
	neighbor_vec.push_back(concatenate(split_strings,
			s1, ith_dec_seq, s2, swap_pos2));
}

/**
 *
 */
void
flip_graph_generator::neighbor_dss_from_not_last_word(
		std::vector<std::string>& neighbor_vec,
		const std::vector<std::string>& split_strings, 
		const size_t ith_dec_seq, const size_t jth_word)
{
	if (ith_dec_seq == split_strings.size() - 1
			&& jth_word == split_strings[ith_dec_seq].size() - 1) {
		return;
	}
	std::string s1 = split_strings[ith_dec_seq];
	s1.erase((char) jth_word, 1); 

	char pred = split_strings[ith_dec_seq][jth_word - 1];
	char succ = split_strings[ith_dec_seq][jth_word + 1];
	std::string s2 = split_strings[(unsigned) pred - 1];
	for (size_t pos = 0; pos < s2.size(); pos++) {
		if ((unsigned) s2[pos] < (unsigned) succ) {
			s2 = s2.insert(pos, succ, 1);
			break;
		}
		if (pos == s2.size() - 1) {
			s2 += succ;
			break;
		}
	}
	neighbor_vec.push_back(concatenate(split_strings,
			s2, (unsigned) pred - 1, s1, ith_dec_seq));
}

/**
 *
 */
void
flip_graph_generator::get_neighbors(const std::string& dss, 
		std::vector<std::string>& S) 
{
	S.clear();
	std::vector<std::string> splits;
	split(dss, splits);

	for (size_t i = 1; i < splits.size(); i++) {
		if (splits[i].size() == 1) {
			continue;
		}
		for (size_t j = 1; j < splits[i].size(); j++) {
			if (i == splits.size() - 1 && j == splits[i].size() - 1) {
				break;
			}
			if (j == splits[i].size() - 1) {
				neighbor_dss_from_last_word(S, splits, i, j);
			} else {
				neighbor_dss_from_not_last_word(S, splits, i, j);
			}
		}
	}
}

/**
 *
 */
void
flip_graph_generator::build_flip_graph()
{
	igraph_vector_t E;
	igraph_vector_init(&E, edges.size() * 2);
	long int edge_count = 0;
	std::vector<std::pair<size_t, size_t> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++) {
		VECTOR(E)[edge_count] = (*it).first;
		VECTOR(E)[edge_count + 1] = (*it).second;
		edge_count += 2;
	}
	igraph_empty(&flip_graph, vertices.size(), IGRAPH_UNDIRECTED);
	igraph_add_edges(&flip_graph, &E, 0);
	igraph_vector_destroy(&E);
}

/**
 *
 */
void
flip_graph_generator::gen()
{
	std::string init_dss = get_init_dss();
	vertices.push_back(init_dss);

	dss_id_ref_tab[init_dss] = vertex_count;
	vertex_count = 1;

	std::map<std::pair<size_t, size_t>, bool> added_edges;

	std::stack<std::string> task_stack;
	task_stack.push(init_dss);
	while (! task_stack.empty()) {
		std::string dss = task_stack.top();
		task_stack.pop();

		std::vector<std::string> neighbors;
		get_neighbors(dss, neighbors);
		assert(neighbors.size() == polygon_vertex_count - 3);

		for (std::vector<std::string>::iterator it = neighbors.begin();
				it != neighbors.end(); it++) {
			if (dss_id_ref_tab.find(*it) == dss_id_ref_tab.end()) {
				vertices.push_back(*it);
				dss_id_ref_tab[*it] = vertex_count;
				vertex_count++;
				task_stack.push(*it);
			}
			std::pair<size_t, size_t> e;
			if (dss_id_ref_tab[dss] < dss_id_ref_tab[*it]) {
				e.first = dss_id_ref_tab[dss];
				e.second = dss_id_ref_tab[*it];
			} else {
				e.first = dss_id_ref_tab[*it];
				e.second = dss_id_ref_tab[dss];
			}
			if (added_edges.find(e) == added_edges.end()) {
				edges.push_back(e);
				added_edges[e] = true;
			}
		}
	}
	build_flip_graph();
}

/**
 *
 */
void
flip_graph_generator::write_triangulation_graph(size_t vertex_id) const
{
	igraph_t g;
	igraph_empty(&g, vertex_count, IGRAPH_UNDIRECTED);
	assert(vertex_id < vertices.size());
	std::string s = vertices[vertex_id];

	for (size_t i = 1, si = 0; i < vertex_count; i++) {
		for (; si < s.size(); si++) {
			if ((unsigned) s[si] == i) break;
			igraph_add_edge(&g, i, (unsigned) s[si]);
		}
	}
	std::ostringstream os;
	size_t digit = (size_t) log10(vertex_count);
	os << std::setfill('0') << std::setw(digit) << vertex_id;
	std::string fname = "triangulation-" + os.str() + ".gml";
	FILE* fp = fopen(fname.c_str(), "w");
	igraph_write_graph_gml(&g, fp, 0, 0);
	fclose(fp);
	igraph_destroy(&g);
}

/**
 *
 */
void
flip_graph_generator::save(const std::string& filename) const
{
	FILE *fp  = fopen(filename.c_str(), "w");
	igraph_write_graph_gml(&flip_graph, fp, 0, 0);
	fclose(fp);
}

/**
 *
 */
void flip_graph_generator::get_flip_graph(igraph_t& g)
{
	g = flip_graph;
}

/** Get the vertex set of caliculated flip graph. The vertex set is
 * represented as a vector of strings. Each index of vector is a id of
 * vertex, and stored string is a Davenport-Schinzel sequence, which
 * is able to decode to triangulation of convex polygons.
 * @param v stored the vertex set.
 */
void flip_graph_generator::get_vertices(std::vector<std::string>& v)
{
	v = vertices;
}
