#include <algorithm>
#include "graph.h"
#include "fordfulkerson.h"
#include "dfs.h"

std::pair<double, Graph> ford_fulkerson( Graph &g, Node& s, Node& t )
{
    Graph residual( g );
    double max_flow = 0.0;
    
    std::vector<int> parents;
    std::forward_list<Edge> path;
    while( !(path = dfs( residual, s, t )).empty() )
    {
        const auto& it = std::min_element( path.begin(), path.end(), EdgeComperator() );
        const double min_weight = (*it).second;
        for( Edge& edge : path )
        {
           max_flow += min_weight;
           edge.second -= min_weight;
        }
    }
    return std::pair<double, Graph>( max_flow, residual );
}

int main()
{
    int start_node;
    int target_node = 3;
    Graph graph = read_adj_list( start_node, std::string("bfs.in"));
    std::forward_list<Edge> path = dfs( graph, start_node, target_node );
    
    for( const auto& edge : path )
        std::cout << "-->[ " << edge.first << ", " << edge.second << " ] ";
}
