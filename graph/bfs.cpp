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
    void build_path( Path& path, Node& start_node, std::vector<Edge*>& parents )
    {
        Node i = start_node;
        while( parents[i] != nullptr )
        {
            path.push_front( parents[i] );
            i = parents[i]->first;
        }
        path.reverse();
    }
}

Path bfs( Graph& graph, Node& start_node, Node& target_node )
{
    //std::vector<bool> ist ein spezialisiertes Template und als bitset implementiert
    Path path;
    std::vector<bool> visited( graph.node_count, false );
    std::vector<Edge*> parents( graph.node_count, nullptr );
    std::queue<int> active;
    
    active.push( start_node );

    while( !active.empty() )
    {
        const int node = active.front(); 
        active.pop();
        visited[node] = true; 
        
        for( auto& edge : graph.adj_list[node] )
        {
            if( edge.second <= std::numeric_limits<double>::epsilon() )
            {
                continue;
            }
            if( !visited[edge.first] )
            {
                active.push( edge.first );
                visited[edge.first] = true;
                parents[node] = &edge;
            }
            if( edge.first == target_node )
            {
                build_path( path, start_node, parents );
                return path;
            }
        }

    }
    return path;
}


