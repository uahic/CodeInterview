#ifndef MST_H
#define MST_H 

#include "graph.h"
#include <cstddef>
#include <utility>

typedef std::pair<Node, Edge> SourceEdge;

struct MST
{
    MST( size_t N )
        : g( N ),
        weight( 0.0 )
    {}
    Graph g;
    double weight;
};

MST prim( Graph& );
MST kruskal( Graph& );

#endif /* MST_H */
