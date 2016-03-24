#include <vector>
#include <limits>
#include "graph.h"
#include <exception>

inline bool relax_edges ( Graph &g, std::vector<Node> &parents, std::vector<double> &distances )
{
    bool has_relaxed = false;
    for ( size_t i = 0; i < g.node_count; i++ )
    {
        for ( const auto &edge : g.adj_list[i] )
        {
            const double new_weight = distances[i] + edge.second;
            if ( new_weight < distances[edge.first] )
            {
                distances[edge.first] = new_weight;
                parents[edge.first] = i;
                has_relaxed = true;
            }
        }
    }
    return has_relaxed;
}

std::vector<Node> bellman_ford ( Graph &g, Node start_node )
{
    std::vector<Node> parents ( g.node_count, -1.0 );
    std::vector<double> distances ( g.node_count, std::numeric_limits<double>::infinity () );
    distances[start_node] = 0.0;

    for ( size_t i = 0; i < g.node_count; i++ )
    {
        relax_edges ( g, parents, distances );
    }

    if ( relax_edges ( g, parents, distances ) )
    {
        throw std::logic_error ( "Graph has negative cycle" );
    }

    return parents;
}

int main ()
{
    Node start_node;
    std::string file_name = "bellmanford.in";
    auto graph = read_adj_list ( start_node , file_name );
    print_graph ( *graph );
    std::vector<Node> parents = bellman_ford( *graph, start_node);

    size_t i = 0;
    for ( const auto &node : parents )
    {
        std::cout << "Parent of " << i << " is " << node << std::endl;
        i++;
    }
}
