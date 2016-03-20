#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>

struct Graph
{
    std::forward_list<int> * adj_list;
    int node_count;

    Graph( int node_count )
        : adj_list( new std::forward_list<int>[node_count] )
        , node_count( node_count )
    {}

    Graph()
        : adj_list( new std::forward_list<int>[1] )
        , node_count( 0 )
    {}
};

Graph* read_adj_list( int& start_node )
{
    std::ifstream is ( "bfs.in" );
    int m;
    int n;

    // Header
    is >> n >> m >> start_node;
    start_node--;

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
        graph->adj_list[ from_node ].push_front( to_node );
    }
    return graph;
}

std::vector<int> bfs( Graph* graph, int start_node, int target_node )
{
    //std::vector<bool> ist ein spezialisiertes Template und als bitset implementiert
    std::vector<bool> visited( graph->node_count, false );
    std::vector<int> parents( graph->node_count, -1 );
    std::queue<int> active;
    
    active.push( start_node );

    while( !active.empty() )
    {
        const int node = active.front(); 
        active.pop();
        visited[node] = true; 
        
        for( std::forward_list<int>::iterator it = graph->adj_list[node].begin();
                it != graph->adj_list[node].end(); it++ )
        {
            if( !visited[*it] )
            {
                active.push( *it );
                visited[*it] = true;
                parents[*it] = node;
            }
            //if( *it == target_node )
            //    return parents;
        }

    }
    return parents;
}



int main()
{
    int start_node;
    int target_node = -200;
    Graph * graph = read_adj_list( start_node );
    std::vector<int> parents = bfs( graph, start_node, target_node );
    
    size_t i = 0;
    for( std::vector<int>::iterator it = parents.begin(); 
            it != parents.end(); i++, it++ )
        std::cout << "\n" << i+1 << "Node " << *it +1;
}
