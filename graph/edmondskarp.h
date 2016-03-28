#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H
#include "graph.h"

std::pair<double, Graph> edmonds_karp_unit_weights( Graph &graph, Node &source, Node &sink );
std::pair<double, Graph> edmonds_karp( Graph &graph, Node &source, Node &sink );
#endif /* ifndef EDMONDS_KARP_H */
