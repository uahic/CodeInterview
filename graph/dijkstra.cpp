#include <vector>
#include <queue>
#include <forward_list>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <memory>
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
                break;
        }
    }
}

Path dijkstra( Graph &graph, Node &start_node, Node &target_node )
{
    Path path;
    std::priority_queue<Edge> pq;
    std::vector<bool> visited( graph.node_count, false );
    std::vector<double> dists( graph.node_count, std::numeric_limits<double>::infinity() );
    Parentlist parents( graph.node_count );

    dists[start_node] = 0.0;
    pq.push( {start_node, 0.0} );

    while( !pq.empty() )
    {
        const Edge top_edge = pq.top();
        const Node node = top_edge.first;
        pq.pop();
        visited[node] = true;
        if( node == target_node )
        {
            build_path( path, start_node, target_node, parents, visited );
            return path;
        }
        // std::cout << "Node " << node << std::endl;
        for( Edge &edge : graph.adj_list[node] )
        {
            const Node &neigh_node = edge.first;
            const auto &neigh_weight = edge.second;
            const auto new_dist = dists[node] + neigh_weight;
            if( neigh_weight <= std::numeric_limits<double>::epsilon() )
            {
                continue;
            }
            if( new_dist < dists[neigh_node] )
            {
                dists[neigh_node] = new_dist;
                parents[edge.first] = {node, &edge};
            }
            if( !visited[neigh_node] )
            {
                pq.push( {neigh_node, dists[neigh_node]} );
            }
        }
    }
    return path;
}
