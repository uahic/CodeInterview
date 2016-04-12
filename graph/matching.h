#ifndef MATCHING_H
#define MATCHING_H 

#include "graph.h"

struct Match 
{
    Match( size_t N ): g( N ), weight( 0.0 )
    {}

    Match( const Graph& other, double weight): g( other ), weight( weight)  
    {}

    Graph g;
    double weight;
};

Match matching_by_flow( Graph& );

#endif /* MATCHING_H */
