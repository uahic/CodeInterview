#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <forward_list>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

typedef int Node;
typedef std::pair<Node, double> Pair;
typedef std::pair<Node, double> Edge;

struct EdgeComperator
{
    bool operator()( const Edge& a, const Edge& b )
    {
        return a.second < b.second;
    }

};

struct Graph
{
    public:
    std::vector<std::forward_list<Edge>> adj_list;
    int node_count;

    Graph ( Node node_count ) 
        : adj_list ( node_count )
        , node_count ( node_count )
    {
    }

    Graph( const Graph& other )
        : adj_list( other.adj_list )
        , node_count( other.node_count )
    {
    }
    
    Graph( Graph&& other ) noexcept 
        : adj_list( std::move( other.adj_list ))
        , node_count( other.node_count )
    {
    }

    Graph () 
        : adj_list ( 0 )
        , node_count ( 0 )
    {
    }
};

void print_graph ( Graph &graph )
{
    size_t i = 0;
    for ( const auto &edges : graph.adj_list )
    {
        std::cout << i << " : [ ";
        for ( const auto &edge : edges )
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        std::cout << " ]" << std::endl;
        i++;
    }
}

Graph read_adj_list ( Node &start_node, std::string file_name )
{
    std::ifstream is ( file_name );
    size_t m;
    size_t n;

    // Header
    is >> n >> m >> start_node;

    Graph graph( n );

    // Rest
    Node from_node;
    Node to_node;
    double weight;
    while ( true )
    {
        is >> from_node >> to_node >> weight;
        if ( is.eof () )
        {
            break;
        }
        graph.adj_list.at(from_node).push_front ( Edge{to_node, weight} );
    }
    return graph;
}
#endif /* ifndef GRAPH_H */
