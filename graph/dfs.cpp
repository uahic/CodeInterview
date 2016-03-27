#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include "graph.h"
#include "dfs.h"


std::forward_list<Edge> dfs( Graph& graph, Node& source_node, Node& target_node )
{
    std::vector<bool> visited( graph.node_count, false );
    std::vector<Edge> back_track( graph.node_count, {-1, 0.0});
    std::forward_list<Edge> path;
    std::forward_list<int> active;

    active.push_front( source_node );

    while( !active.empty() )
    {
       const Node node = active.front(); 
       visited[node] = true;
       active.pop_front();
       if( node == target_node )
           break;
       for( const auto& edge : graph.adj_list[node])
       {
           if( !visited[edge.first] )
           {
               active.push_front(edge.first);
               back_track[edge.first] = Edge( node, edge.second );
           }
       }
    
    }
    Node i = target_node;
    while( back_track[i].first > 0 )
    {
        path.push_front( back_track[i] );
    }
    return path;
}
    

int main()
{
    Node start_node;
    Node target_node = 3;
    Graph graph = read_adj_list( start_node, std::string("dfs.in"));
    print_graph(graph);
    std::forward_list<Edge> path = dfs( graph, start_node, target_node );
    
    for( const auto& edge : path )
        std::cout << "-->[ " << edge.first << ", " << edge.second << " ] ";
}
