#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H
#include "graph.h"

std::pair<double, Graph> ford_fulkerson( Graph &g, Node& s, Node& t );
#endif /* ifndef FORDFULKERSON_H */
