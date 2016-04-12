
#include <vector>
#include <algorithm>
#include <functional>
#include "kruskal.h"
#include "../datastructures/disjoint_sets.h"


MST kruskal( Graph& g )
{
    std::vector<SourceEdge> edges; 
    UnionFind sets( g.node_count );
    MST mst( g.node_count );
    for( int i=0; i < g.node_count; i++ )
    {
        for( Edge& e: g.adj_list[i] )
        {
            edges.push_back( { Node(i), e });
        }
    }

    std::sort( edges.begin(), edges.end(), []( const SourceEdge& a, const SourceEdge& b) { return a.second.second < b.second.second; } );
    
    for( SourceEdge& e : edges )
    {
       if( !sets.is_connected( e.first, e.second.first ) )
       {
           sets.unite( e.first, e.second.first );
           mst.g.adj_list[e.first].push_front(e.second);
       }
    }
    return mst;
}
