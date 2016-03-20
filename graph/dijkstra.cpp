#include <vector>
#include <forward_list>
#include <queue>
#include <iostream>
#include <fstream>
#include <limits>
#include <tuple>

typedef std::tuple<int, double> Edge;
 

struct Compare
{
    bool operator()( const Edge a, const Edge b ) const 
    {
        if( std::get<1>(a) > std::get<1>(b) )
            return true;
        return false;
    }
};

struct Graph
{
    std::vector< std::forward_list< Edge > > adj_list;
    int node_count;
    

    Graph( int node_count )
        : adj_list( node_count )
        , node_count( node_count )
    {}

    Graph()
        : adj_list( 0 )
        , node_count( 0 )
    {}
};

std::vector<int> dijkstra( Graph & graph, int start_node )
{
    std::priority_queue< Edge, std::vector<Edge>, Compare> pq; 
    std::vector<bool> visited( graph.node_count, false );
    std::vector<unsigned int> dists( graph.node_count, std::numeric_limits<double>::max() );
    std::vector<int> parents( graph.node_count, -1 );

    pq.push( Edge (start_node, 0.0) );
    dists[start_node] = 0.0;
    visited[start_node] = true;

    while( !pq.empty() )
    {
        const Edge top_edge  = pq.top();
        pq.pop();
        const int node = std::get<0>(top_edge);
        visited[node] = true;
        for( const Edge &edge : graph.adj_list[node] )
        {
            const int neigh_node = std::get<0>(edge);
            const double weight = std::get<1>(edge);
            const double new_dist = dists[node] + weight;
            if( new_dist < dists[neigh_node] )
            {
                dists[neigh_node] = new_dist;
                parents[neigh_node] = node;
            }
            if( !visited[neigh_node] )
                pq.push( edge );
        }
            
    }
    return parents;

}

Graph* read_adj_list( int& start_node )
{
    std::ifstream is ( "dijkstra.in" );
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
    double weight; 
    while( is )
    {
        is >> from_node >> to_node >> weight;
        from_node--;
        to_node--;
        graph->adj_list[ from_node ].push_front( Edge { to_node, weight } );
    }
    return graph;
}


int main()
{
    int start_node;
    Graph * graph = read_adj_list( start_node );
    std::vector<int> parents = dijkstra( *graph, start_node );
    
    size_t i = 0;
    for( std::vector<int>::iterator it = parents.begin(); 
            it != parents.end(); i++, it++ )
        std::cout << "\n" << i+1 << "Node " << *it +1;
}
