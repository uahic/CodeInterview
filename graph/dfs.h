#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <functional>
#include <set>

Path dfs_recursive( Graph &graph, Node &source_node, Node &target_node );
std::pair<std::forward_list<Node>, std::vector<std::set<Node>>> dfs( Graph &g );

std::vector<std::set<Node>> dfs( Graph &g,
          std::forward_list<Node> &finish_time,
          std::function<Node( int )> node_accessor );
#endif /* ifndef DFS_H */
