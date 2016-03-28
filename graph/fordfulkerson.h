#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H
#include <functional>
#include "graph.h"

std::pair<double, Graph>
ford_fulkerson_core( Graph &g, Node &s, Node &t, std::function<Path(Graph &, Node &, Node &)> );
std::pair<double, Graph> ford_fulkerson( Graph &, Node &, Node & );
#endif /* ifndef FORDFULKERSON_H */
