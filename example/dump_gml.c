#include "fgg.h"

int main(int argc, char* argv[])
{
	flip_graph_generator f(6);
	f.gen();
	f.save("hexagon-flip-graph.gml");

	return 0;
}
