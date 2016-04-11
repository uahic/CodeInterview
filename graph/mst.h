#ifndef MST_H
#define MST_H 

#include <cstddef>
#include "graph.h"

struct MST
{
    MST( size_t N )
        : g( N ),
        weight( 0.0 )
    {}
    Graph g;
    double weight;
};


#endif /* MST_H */
