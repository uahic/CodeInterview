#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "linkedList.h"

struct Vertex
{
    int id;
    Vertex * parent;

    Vertex()
        : id(-1)
        , parent( NULL )
    {}

    Vertex( int id )
        : id( id )
        , parent( NULL )
    {}

};

struct Graph 
{
    LinkedList<Vertex*> ** adj_list;    
    Vertex * vertices;
    int num_nodes;
    int node_count;

    Graph( size_t nodes )
        : adj_list( new LinkedList<Vertex*>*[nodes] )
        , vertices( new Vertex[nodes] )
        , num_nodes( nodes )
    {
        for( size_t i=0; i < num_nodes; i++ )
        {
            adj_list[i] = new LinkedList<Vertex*>();
            vertices[i].id = i;
        }

    }

    void add_edge( int from_node, int to_node )
    {
        adj_list[from_node]->push_back( &vertices[to_node] );
    }

};


Graph* read_adj_list( int &start_node )
{
    std::ifstream is ( "bfs.in" );
    int m;
    int n;

    // Header
    is >> n >> m >> start_node;

    Graph * graph = new Graph( n );


    // Rest
    std::string buf;
    int from_node;
    int to_node;
    while( is )
    {
        is >> from_node >> to_node; 
        from_node--;
        to_node--;
        graph->add_edge( from_node, to_node );
        // TODO einfuegen
    }
    return graph;
}


void bfs( Graph * graph, int start_node, int target_node )
{
    LinkedList<Vertex*> * active_nodes = new LinkedList<Vertex*>();
    active_nodes->push_back( &graph->vertices[start_node] );

    while( !active_nodes->is_empty() )
    {
        Vertex * node = active_nodes->pop_front();
        SLLItem<Vertex*> * k = graph->adj_list[node->id]->first;
        while( k != NULL )
        {
            if( node->id == target_node )
            {
                k->data->parent = node;
                return;
            }
            if( k->data->parent == NULL )
            {
                active_nodes->push_back( k->data );
                k->data->parent = node;
            }
            k = k->next;
        }
        
    }


}

int main()
{
    int start_node = 0;
    int target_node = 3;
    Graph * graph = read_adj_list(start_node);
    bfs( graph, start_node, target_node );
}
