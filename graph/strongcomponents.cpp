
#include <vector>
#include "strongcomponents.h"
#include "dfs.h"

namespace
{
    struct FinishTimeComparator
    {
        std::vector<int>& _finish_times;
        FinishTimeComparator( std::vector<int>& finish_times)
            : _finish_times ( finish_times)
        {
        }

        bool operator()( const int a, const int b)
        {
            return _finish_times[a] < _finish_times[b];
        }
    };
}

std::vector<int> &&get_finish_times( int node_count, std::forward_list<int>& finish_order )
{
    std::vector<int> finish_times( node_count, 0); 
    int i = node_count;
    for( int finish_time : finish_order )
    {
        finish_times[finish_time] = i--;
    }
    return std::move( finish_times );
}

Graph &&build_transposed_graph( Graph &g, std::vector<int>& finish_times )
{
    std::vector<Edge&> sorted_edges;
    FinishTimeComparator comp ( finish_times );
    Graph transposed( g.node_count );

    for( int i = 0; i < g.node_count; ++i )
    {
        for( auto &edge : g.adj_list[i] )
        {
            sorted_edges.push_back( edge );
        }
        std::sort( sorted_edges.begin(), sorted_edges.end(), comp );

        for( Edge& edge : sorted_edges )
        {
            transposed.adj_list[edge.first].push_front( Edge{i, edge.second});
        }
    }

    return std::move( transposed );
}

std::vector<int> strongly_connected_components_kosaraju( Graph &g )
{
    auto dfs_result_g = dfs( g );
    auto& finish_times = get_finish_times( g.node_count, dfs_result_g.first );
    Graph& g_transposed = build_transposed_graph( g, finish_times );
    //std::pair<std::forward_list<Node>, std::vector<Node>> 
    auto dfs_result_g_transposed = dfs( g_transposed );
}
