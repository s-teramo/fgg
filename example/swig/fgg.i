%module fgg

%{
#include "../../fgg.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_pair.i"

%template(vertex_vector) std::vector<std::string>;
%template(edge) std::pair<size_t, size_t>;
%template(edge_vector) std::vector<std::pair<size_t, size_t> >;

%include "../../fgg.h"
