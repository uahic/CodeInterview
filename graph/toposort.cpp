#include "toposort.h"
#include "dfs.h"

std::forward_list<Node> topo_sort( Graph & g )
{
    const auto& finish_parent_pair = dfs( g );
    return finish_parent_pair.first;
}
