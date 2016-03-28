#ifndef DFS_H
#define DFS_H

#include "graph.h"
Path dfs_recursive( Graph &graph, Node &source_node, Node &target_node );
std::pair<std::forward_list<Node>, std::vector<Node>> dfs( Graph &g );

#endif /* ifndef DFS_H */
