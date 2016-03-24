#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <memory>
#include "graph.h"


std::vector<Node> dijkstra ( Graph &graph, Node start_node )
{
    std::priority_queue<Pair, std::vector<Pair>, PairComperator> pq;
    std::vector<bool> visited ( graph.node_count, false );
    std::vector<double> dists ( graph.node_count, std::numeric_limits<double>::infinity () );
    std::vector<Node> parents ( graph.node_count, -1 );

    dists[start_node] = 0.0;
    pq.push ( {start_node, 0.0} );
    parents[start_node] = start_node;

    while ( !pq.empty () )
    {
        const Edge top_edge = pq.top ();
        const Node node = top_edge.first;
        pq.pop ();
        visited[node] = true;
        // std::cout << "Node " << node << std::endl;
        for ( const Edge &edge : graph.adj_list[node] )
        {
            const Node neigh_node = edge.first;
            const auto neigh_weight = edge.second;
            const auto new_dist = dists[node] + neigh_weight;
            // std::cout << "In Node " << node << " edge (" << neigh_node << ",
            // " << neigh_weight << "), new_dist: " << new_dist << ",
            // dists[neigh_node] " << dists[neigh_node] << std::endl;
            if ( new_dist < dists[neigh_node] )
            {
                dists[neigh_node] = new_dist;
                parents[neigh_node] = node;
            }
            if ( !visited[neigh_node] )
                pq.push ( {neigh_node, dists[neigh_node]} );
        }
    }
    return parents;
}



int main ()
{
    Node start_node;
    auto graph = read_adj_list ( start_node , std::string("dijkstra.in") );
    print_graph ( *graph );
    std::vector<Node> parents = dijkstra ( *graph, start_node);

    size_t i = 0;
    for ( const auto &node : parents )
    {
        std::cout << "Parent of " << i << " is " << node << std::endl;
        i++;
    }
}
