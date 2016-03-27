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

Path dijkstra ( Graph &graph, Node& start_node, Node& target_node )
{
    Path path;
    std::priority_queue<Edge> pq;
    std::vector<bool> visited ( graph.node_count, false );
    std::vector<double> dists ( graph.node_count, std::numeric_limits<double>::infinity () );
    std::vector<Edge*> parents (graph.node_count, nullptr );

    dists[start_node] = 0.0;
    pq.push ( {start_node, 0.0} );

    while ( !pq.empty () )
    {
        const Edge top_edge = pq.top ();
        const Node node = top_edge.first;
        pq.pop ();
        visited[node] = true;
        // std::cout << "Node " << node << std::endl;
        for ( Edge &edge : graph.adj_list[node] )
        {
            const Node& neigh_node = edge.first;
            const auto& neigh_weight = edge.second;
            const auto new_dist = dists[node] + neigh_weight;
            if ( new_dist < dists[neigh_node] )
            {
                dists[neigh_node] = new_dist;
                parents[node] = &edge;
            }
            if ( !visited[neigh_node] )
            {
                pq.push ( {neigh_node, dists[neigh_node]} );
            }
            if ( neigh_node == target_node )
            {
                build_path( path, start_node, parents );
                return path;
            }

        }
    }
    return path;
}

