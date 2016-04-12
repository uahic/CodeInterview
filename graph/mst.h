#ifndef MST_H
#define MST_H 

#include "graph.h"
#include <utility>


typedef std::pair<Node, Edge> SourceEdge;

struct MST
{
    MST( size_t size )
        : g(size),
        weight( 0.0 )
    {}

    Graph g;
    double weight;
};

MST prim( Graph& );
MST kruskal( Graph& );

#endif /* MST_H */
