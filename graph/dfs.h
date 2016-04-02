#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <functional>

Path dfs_recursive( Graph &graph, Node &source_node, Node &target_node );
std::pair<std::forward_list<Node>, std::vector<Node>> dfs( Graph &g );

void dfs( Graph &g,
          std::forward_list<Node> &finish_time,
          std::vector<Node> &parents,
          std::function<Node( int )> node_accessor );
#endif /* ifndef DFS_H */
