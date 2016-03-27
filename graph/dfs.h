#ifndef DFS_H
#define DFS_H

#include "graph.h"
std::forward_list<Edge> dfs( Graph& graph, Node& source_node, Node& target_node );

#endif /* ifndef DFS_H */

