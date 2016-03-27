#include <vector>
#include <limits>
#include <memory>
#include <utility>
#include "graph.h"
#include <exception>

namespace
{
    typedef std::vector<std::pair<Node, Edge*>> Parentlist;
    void build_path( Path& path, Node& start_node, Node& target_node, Parentlist& parents, std::vector<bool>& visited )
    {
        Node i = target_node;
        while( visited[i] )
        {
            path.push_front( parents[i].second );
            i = parents[i].first;
            if( i == start_node )
                break;
        }
    }
}

inline bool relax_edges ( Graph &g, Parentlist &parents, std::vector<double> &distances )
{
    bool has_relaxed = false;
    for ( Node i = 0; i < g.node_count; i++ )
    {
        for ( const auto &edge : g.adj_list[i] )
        {
            const double new_weight = distances[i] + edge.second;
            if ( new_weight < distances[edge.first] )
            {
                distances[edge.first] = new_weight;
                parents[edge.first] = {i, &edge};
                has_relaxed = true;
            }
        }
    }
    return has_relaxed;
}

Path bellman_ford ( Graph &g, Node& start_node, Node& target_node )
{
    Path path;
    Parentlist parents ( g.node_count );
    std::vector<double> distances ( g.node_count, std::numeric_limits<double>::infinity () );
    distances[start_node] = 0.0;

    for ( int i = 0; i < g.node_count; i++ )
    {
        relax_edges ( g, parents, distances );
    }

    if ( relax_edges ( g, parents, distances ) )
    {
        throw std::logic_error ( "Graph has negative cycle" );
    }

    return path;
}

