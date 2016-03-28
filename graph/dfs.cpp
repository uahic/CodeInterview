#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include "dfs.h"

bool dfs_recursive_loop( Graph &g, Node &n, Node &t, std::vector<bool> &visited, std::forward_list<Edge *> &path )
{
    visited[n] = true;
    for( auto it = g.adj_list[n].begin(); it != g.adj_list[n].end(); ++it )
    {
        auto &edge = *it;
        if( visited[edge.first] || edge.second <= std::numeric_limits<double>::epsilon() )
        {
            return false;
        }
        if( edge.first == t || dfs_recursive_loop( g, edge.first, t, visited, path ) )
        {
            path.push_front( &edge );
            return true;
        }
    }
    return false;
}

Path dfs_recursive( Graph &graph, Node &source_node, Node &target_node )
{
    std::vector<bool> visited( graph.node_count, false );
    Path path;
    dfs_recursive_loop( graph, source_node, target_node, visited, path );
    return std::move( path );
}

