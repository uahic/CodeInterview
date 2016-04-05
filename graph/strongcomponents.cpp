
#include "strongcomponents.h"
#include "dfs.h"
#include <vector>
#include <algorithm>


std::vector<int> get_finish_times( int node_count, std::forward_list<int> &finish_order )
{
    std::vector<int> finish_times( node_count, 0 );
    int i = node_count;
    for( int finish_time : finish_order )
    {
        finish_times[finish_time] = i--;
    }
    return finish_times;
}


std::vector<std::set<Node>> strongly_connected_components_kosaraju( Graph &g )
{
    auto dfs_result_g = dfs( g );
    std::forward_list<Node> finish_time;
    std::vector<Node> finish_time_order( dfs_result_g.first.begin(), dfs_result_g.first.end() );
    Graph g_transposed = g.transpose();
    auto accessor = [&]( Node i ) { return finish_time_order[i]; };
    auto tree_list = dfs( g_transposed, finish_time, accessor);
    return tree_list;
}
