
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

void pack_parents_into_set( Node& n, std::vector<Node>& parents, std::shared_ptr<std::set<Node>>& s, std::vector<std::shared_ptr<std::set<Node>>> & bins )
{

    const Node parent = parents[n];
    if( bins[parent] != nullptr)
    {
        std::set<Node>& parent_set = *bins[parent];
        std::merge(s->begin(), s->end(), parent_set.begin(), parent_set.end(), std::back_inserter(parent_set));
        bins[n] = bins[parent];
    }

    if( parents[n] > 0) 
    {
        pack_parents_into_set(parents[n], parents, bins[n], bins);


    }
    parents[n] = -1;
}

std::vector<std::set<Node>> parents_to_set( std::vector<Node> parents)
{
    std::vector<std::shared_ptr<std::set<Node>>> bins(parents.size(), nullptr);
    for( Node& k : parents)
    {
        if( k < 0 )
        {
            continue;
        }
        
        bins[k] = std::make_shared<std::set<Node>> (new std::set<Node>());
        pack_parents_into_set( k, parents, bins[k], bins);
    }
}

std::vector<std::set<Node>> strongly_connected_components_kosaraju( Graph &g )
{
    auto dfs_result_g = dfs( g );
    std::forward_list<Node> finish_time;
    std::vector<Node> parents;
    std::vector<Node> finish_time_order( dfs_result_g.first.begin(), dfs_result_g.first.end() );
    Graph g_transposed = g.transpose();
    auto accessor = [&]( Node i ) { return finish_time_order[i]; };
    dfs( g_transposed, finish_time, parents, accessor);

}
