CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJECT_NAME "FGG")
PROJECT(${PROJECT_NAME} CXX)
SET(serial "0.0.1")
SET(soserial "1")

SET(CMAKE_C_FLAGS_RELEASE "-Wall -O2")
SET(CMAKE_C_FLAGS_DEBUG "-g")
SET(CMAKE_BUILD_TYPE Release)

#SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#FIND_PACKAGE(IGRAPH)

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${IGRAPH_INCLUDE_DIR})
#LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/${IGRAPH_LIBRARY_DIR}")

ADD_LIBRARY(fgg SHARED fgg.cpp)
#TARGET_LINK_LIBRARIES(fgg igraph)
SET_TARGET_PROPERTIES(fgg PROPERTIES VERSION ${serial} SOVERSION ${soserial})

INSTALL(TARGETS fgg LIBRARY DESTINATION lib)
INSTALL(FILES fgg.h DESTINATION include)

