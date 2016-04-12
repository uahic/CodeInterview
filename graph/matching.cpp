
#include "matching.h"
#include "fordfulkerson.h"

Match matching_by_flow( Graph &g )
{
    Graph m( g );
    Node s( g.node_count );
    Node t( g.node_count + 1 );
    m.node_count += 2;
    m.adj_list.push_back( std::forward_list<Edge>() );
    m.adj_list.push_back( std::forward_list<Edge>() );

    // Connect start node to all other nodes
    for( int i = 0; i < g.node_count; i++ )
    {
        m.adj_list[s].push_front( {i, 1.0} );
        m.adj_list[i].push_front( {t, 1.0} );
    }
    auto matching_graph = ford_fulkerson( m, s, t );
    Match result( matching_graph.second, matching_graph.first );
    return result;
}
