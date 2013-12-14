SET(IGRAPH_ROOT_DIR "" CACHE PATH "IGRAPH root directory")
FIND_PATH(IGRAPH_INCLUDE_DIR igraph/igraph.h
	HINTS ${IGRAPH_ROOT_DIR}/include
)
FIND_LIBRARY(IGRAPH_LIBRARY
	NAMES igraph libigraph
	HINTS ${IGRAPH_ROOT_DIR}/lib
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(IGRAPH DEFAULT_MSG
	IGRAPH_INCLUDE_DIR
	IGRAPH_LIBRARY
)

IF(IGRAPH_FOUND)
	SET(IGRAPH_INCLUDE_DIRS ${IGRAPH_INCLUDE_DIR})
	SET(IGRAPH_LIBRARIES ${IGRAPH_LIBRARY})
ENDIF(IGRAPH_FOUND)

MARK_AS_ADVANCED(
	IGRAPH_INCLUDE_DIR
	IGRAPH_LIBRARY
)
