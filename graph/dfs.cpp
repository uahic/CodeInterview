#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include "dfs.h"

namespace
{
    enum class MarkColor
    {
        White,
        Grey,
        Black
    };
}

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

// Alternative implementation (see Corman - Introduction to algorithms )

void dfs_visit( Graph &g,
                Node& n,
                std::vector<MarkColor> &visited,
                std::forward_list<Node> &finish_time,
                std::vector<Node> &parents )
{
    visited[n] = MarkColor::Grey;
    for( auto& edge : g.adj_list[n] )
    {
        if( visited[edge.first] == MarkColor::White )
        {
            parents[edge.first] = n;
            dfs_visit( g, edge.first, visited, finish_time, parents );
            visited[edge.first] = MarkColor::Black;

        }
    }
    finish_time.push_front( n );
}

std::pair<std::forward_list<Node>, std::vector<Node>> dfs( Graph &g )
{
    std::vector<MarkColor> visited( g.node_count, MarkColor::White );
    std::forward_list<Node> finish_time;
    std::vector<Node> parents( g.node_count, -1 );

    for( Node n = 0; n < g.node_count; ++n )
    {
        if( visited[n] == MarkColor::White )
        {
            dfs_visit( g, n, visited, finish_time, parents );
        }
    }

    return std::make_pair( finish_time, parents );
}
