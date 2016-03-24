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

struct PairComperator
{
    bool operator()( const Pair &p1, const Pair &p2 ) const
    {
        return p1.second > p2.second;
    }
};


struct Graph
{
    public:
    std::vector<std::forward_list<Edge>> adj_list;
    Node node_count;

    Graph ( Node node_count ) : adj_list ( node_count ), node_count ( node_count )
    {
    }

    Graph () : adj_list ( 0 ), node_count ( 0 )
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

std::shared_ptr<Graph> read_adj_list ( Node &start_node, std::string file_name )
{
    std::ifstream is ( file_name );
    size_t m;
    size_t n;

    // Header
    is >> n >> m >> start_node;

    Graph *graph = new Graph ( n );

    // Rest
    Node from_node;
    Node to_node;
    double weight;
    while ( true )
    {
        is >> from_node >> to_node >> weight;
        if ( is.eof () )
            break;
        graph->adj_list[from_node].push_front ( Edge{to_node, weight} );
    }
    return std::shared_ptr<Graph> ( graph );
}
#endif /* ifndef GRAPH_H */
