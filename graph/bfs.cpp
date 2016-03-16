#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "linkedList.h"


struct searchGraph
{
    std::vector<LinkedList> adj_list;
    int start_node;

    searchGraph( size_t nodes, int start_node )
        : adj_list( nodes )
        , start_node( start_node )
    {}

    searchGraph()
        : adj_list( )
        , start_node( -1 )
    {}

};

std::ostream& operator<<( std::ostream& os, const searchGraph& graph )
{
    for( size_t i = 0; i < graph.adj_list.size(); i++ )
        os << graph.adj_list[i] << "\n";
    return os;
}

searchGraph* read_adj_list( )
{
    std::ifstream is ( "bfs.in" );
    int m;
    int n;
    int start_node;

    // Header
    is >> n >> m >> start_node;

    searchGraph * graph = new searchGraph( n, start_node );

    // Rest
    std::string buf;
    int from_node;
    int to_node;
    while( is )
    {
        is >> from_node >> to_node; 
        from_node--;
        to_node--;
        graph->adj_list[ from_node ].append( new linkedListItem( to_node, NULL) );
    }
    return graph;
}

int main()
{
    searchGraph * graph = read_adj_list();
    std::cout << graph << std::endl;



}
