#include <vector>
#include <queue>
#include <functional>
#include <set>

#include "mst.h"


MST kruskal( Graph& g )
{
    MST mst( g.node_count );
    std::vector<bool> visited( g.node_count, false);
    auto comp = [](SourceEdge& a, SourceEdge& b){ return a.second.second < b.second.second; };
   
    std::set<Node>
    

    return mst;
}


MST prim( Graph& g )
{
    MST mst( g.node_count );
    std::vector<bool> visited( g.node_count, false);
    auto comp = [](SourceEdge& a, SourceEdge& b){ return a.second.second < b.second.second; };
    std::priority_queue< SourceEdge, std::vector<SourceEdge>, decltype(comp)> pq( comp ); 
    
    for( Edge& e: g.adj_list[0])
    {
        pq.push( { Node(0), e } );
    }
    visited[0] = true;

    while( !pq.empty() )
    {
        SourceEdge k = pq.top();
        pq.pop();
        if( !visited[k.second.first])
        {
            mst.g.adj_list[k.first].push_front(k.second);
            visited[k.second.first] = true;

            for( Edge& e: g.adj_list[k.second.first])
            {
                pq.push( {Node(k.second.first), e} );
            }

        }
    
    }
    return mst;
}

