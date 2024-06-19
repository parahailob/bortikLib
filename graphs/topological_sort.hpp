#pragma once

#include <vector>
#include <queue>

/// @brief Finds a topological order of a given DAG
/// @param G DAG
/// @return list of vertices in topological order
std::vector<int> topological_sort(const std::vector<std::vector<int>> &G){
    int n = G.size();
    std::vector<int> in_degree(n, 0);
    for(const auto &g: G)
        for(const auto &i: g) in_degree[i]++;

    std::queue<int> que;
    for(int i = 0; i < n; i++)
        if(in_degree[i]==0) que.push(i);
    std::vector<int> order;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        order.push_back(u);
        for(int v: G[u]){
            in_degree[v]--;
            if(in_degree[v]==0){
                que.push(v);
            }
        }
    }
    return order;
}