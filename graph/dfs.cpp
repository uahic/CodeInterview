#include "dfs.h"
#include <forward_list>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <vector>
#include <set>

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
    return path;
}

// Alternative implementation (see Corman - Introduction to algorithms )

void dfs_visit( Graph &g,
                Node &n,
                std::vector<MarkColor> &visited,
                std::forward_list<Node> &finish_time,
                std::set<Node> &tree)
{
    visited[n] = MarkColor::Grey;
    for( auto &edge : g.adj_list[n] )
    {
        if( visited[edge.first] == MarkColor::White )
        {
            tree.insert(edge.first);
            dfs_visit( g, edge.first, visited, finish_time, tree);
            visited[edge.first] = MarkColor::Black;
        }
    }
    finish_time.push_front( n );
}


std::vector<std::set<Node>> dfs( Graph &g, std::forward_list<Node> &finish_time, std::function<Node( Node )> node_accessor )
{
    std::vector<MarkColor> visited( g.node_count, MarkColor::White );
    std::vector<std::set<Node>> tree_list;
    for( Node n = 0; n < g.node_count; ++n )
    {
        if( visited[n] == MarkColor::White )
        {
            std::set<Node> tree;
            Node k = node_accessor( n );
            dfs_visit( g, k, visited, finish_time, tree);
            tree_list.push_back( tree);
        }
    }
    return tree_list;
}

std::pair<std::forward_list<Node>, std::vector<std::set<Node>>> dfs( Graph &g )
{
    std::forward_list<Node> finish_time;
    std::set<Node> tree;

    auto accessor = []( Node i ) { return i; };
    auto tree_list = dfs( g, finish_time, accessor );

    return std::make_pair( finish_time, tree_list);
}
