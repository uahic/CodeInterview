#include <functional>
#include "bfs.h"
#include "dijkstra.h"
#include "dfs.h"
#include "edmondskarp.h"
#include "fordfulkerson.h"
#include "bellmanford.h"
#include "toposort.h"
#include "strongcomponents.h"
#include "mst.h"
#include "kruskal.h"

void print_limiter()
{
    std::cout << std::endl
              << " --------------------------------------------- " << std::endl;
}

void run_print_graph_path( Node target_node,
                           std::string graph_file,
                           std::string func_name,
                           std::function<Path(Graph &, Node &, Node &)> func )
{
    print_limiter();
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file );
    print_graph( graph );
    auto algo_result = func( graph, start_node, target_node );
    std::cout << std::endl
              << func_name << " back track path" << std::endl;
    print_path( algo_result );
}

void run_flow_graph( Node target_node,
                     std::string graph_file,
                     std::string func_name,
                     std::function<std::pair<double, Graph>(Graph &, Node &, Node &)> func )
{
    print_limiter();
    std::cout << std::endl
              << func_name << " result" << std::endl;
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file );
    std::cout << std::endl
              << "Input Graph" << std::endl;
    print_graph( graph );
    auto algo_result = func( graph, start_node, target_node );
    std::cout << std::endl
              << "Output Graph" << std::endl;
    print_graph( algo_result.second );
    std::cout << "\nMaxFlow is " << algo_result.first << std::endl;
}

void run_graph_only_input( std::string graph_file, std::string func_name, std::function<std::forward_list<Node>(Graph &)> func)
{

    print_limiter();
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file );
    std::cout << std::endl
              << func_name << " result" << std::endl;
    for (auto node : func(graph)) {
        std::cout << " -- " << node;  
    }
    std::cout << std::endl;
}

void print_tree_list( std::vector<std::set<Node>> & tree_list )
{
    for( auto& tree: tree_list )
    {
        std::cout << std::endl;
        for( auto& node : tree ) 
        {
            std::cout << " -- " << node;
        }
    }
    std::cout << std::endl;
}

void run_mst( std::string graph_file, std::string func_name, std::function<MST(Graph&)> func)
{
    print_limiter();
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file );
    std::cout << std::endl
              << func_name << " result" << std::endl;
    MST mst = func( graph );
    print_graph( mst.g );
    std::cout << std::endl << "Weight " << mst.weight << std::endl;
}


int main()
{
    std::string dfs_file ("dfs.in");
    run_print_graph_path( Node( 5 ), std::string( "dfs.in" ), std::string( "DFS" ), dfs_recursive );
    run_print_graph_path( Node( 4 ), std::string( "bfs.in" ), std::string( "BFS" ), bfs );
    run_print_graph_path( Node( 4 ), std::string( "bfs.in" ), std::string( "DIJKSTRA" ), dijkstra );
    run_print_graph_path( Node( 5 ), std::string( "dfs.in" ), std::string( "Bellman-Ford" ), bellman_ford );
    run_flow_graph( Node( 5 ), std::string( "dfs.in" ), std::string( "Ford-Fulkerson" ), ford_fulkerson );
    run_flow_graph( Node( 4 ), std::string( "bfs.in" ),
                    std::string( "Edmonds-Karp (Unit-Weights)" ), edmonds_karp_unit_weights );
    run_flow_graph( Node( 5 ), std::string( "dfs.in" ), std::string( "Edmonds-Karp" ), edmonds_karp );
    run_graph_only_input( std::string("dfs.in"), std::string("Topological Sort"), topo_sort);
    run_mst( std::string("dfs.in"), std::string("Kruskals algorithm"), kruskal);



    
    return 0;
}
