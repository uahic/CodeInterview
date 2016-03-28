#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <limits>
#include "graph.h"

namespace
{

    typedef std::vector<std::pair<Node, Edge *>> Parentlist;
    void build_path( Path &path, Node &start_node, Node &target_node, Parentlist &parents, std::vector<bool> &visited )
    {
        Node i = target_node;
        while( visited[i] )
        {
            path.push_front( parents[i].second );
            i = parents[i].first;
            if( i == start_node )
            {
                break;
            }
        }
    }
}

Path bfs( Graph &graph, Node &start_node, Node &target_node )
{
    // std::vector<bool> ist ein spezialisiertes Template und als bitset implementiert
    Path path;
    std::vector<bool> visited( graph.node_count, false );
    Parentlist parents( graph.node_count );
    std::queue<int> active;

    active.push( start_node );

    while( !active.empty() )
    {
        const int node = active.front();
        active.pop();
        visited[node] = true;
        if( node == target_node )
        {
            build_path( path, start_node, target_node, parents, visited );
            return path;
        }

        for( auto &edge : graph.adj_list[node] )
        {
            if( edge.second <= std::numeric_limits<double>::epsilon() )
            {
                continue;
            }
            if( !visited[edge.first] )
            {
                active.push( edge.first );
                // visited[edge.first] = true;
                parents[edge.first] = {node, &edge};
            }
        }
    }
    return path;
}
