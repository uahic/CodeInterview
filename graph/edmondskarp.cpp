#include <vector>
#include "edmondskarp.h"
#include "fordfulkerson.h"
#include "dijkstra.h"
#include "bfs.h"

std::pair<double, Graph> edmonds_karp( Graph &g, Node &s, Node &t )
{
    return ford_fulkerson_core( g, s, t, dijkstra );
}

std::pair<double, Graph> edmonds_karp_unit_weights( Graph &g, Node &s, Node &t )
{
    return ford_fulkerson_core( g, s, t, bfs );
}
