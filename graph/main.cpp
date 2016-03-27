#include <functional>
#include "bfs.h"
#include "dijkstra.h"
#include "dfs.h"
#include "edmondskarp.h"
#include "fordfulkerson.h"

void run_print_graph_path( Node target_node, std::string graph_file, std::string func_name, std::function<Path( Graph&, Node&, Node& )> func)
{
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file);
    auto algo_result = func( graph, start_node, target_node );
    std::cout << std::endl << func_name << " back track path" << std::endl;
    print_path( algo_result);
}

void run_flow_graph( Node target_node, std::string graph_file, std::string func_name, std::function<std::pair<double, Graph>( Graph&, Node&, Node& )> func)
{
    std::cout << std::endl << func_name << " result" << std::endl;
    Node start_node;
    Graph graph = read_adj_list( start_node, graph_file);
    std::cout << std::endl << "Input Graph" << std::endl; 
    print_graph( graph );
    auto algo_result = func( graph, start_node, target_node );
    std::cout << std::endl << "Output Graph" << std::endl;
    print_graph( algo_result.second );
    std::cout << "\nMaxFlow is " << algo_result.first << std::endl;
}

int main()
{
    run_print_graph_path( Node(5), std::string("dfs.in"), std::string("DFS"), dfs_recursive);
    run_print_graph_path( Node(4), std::string("bfs.in"), std::string("BFS"), bfs);
    run_print_graph_path( Node(4), std::string("bfs.in"), std::string("DIJKSTRA"), dijkstra);
    run_flow_graph( Node(5), std::string("dfs.in"), std::string("Ford-Fulkerson"), ford_fulkerson);
    run_flow_graph( Node(4), std::string("bfs.in"), std::string("Edmonds-Karp (Unit-Weights)"), edmonds_karp_unit_weights);
    run_flow_graph( Node(5), std::string("dfs.in"), std::string("Edmonds-Karp"), edmonds_karp);
    return 0;
}
