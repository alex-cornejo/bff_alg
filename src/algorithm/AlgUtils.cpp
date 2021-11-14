//
// Created by ale_j on 11/3/2021.
//

#include "AlgUtils.h"

#include <vector>

using namespace std;

vector<vector<int>> AlgUtils::createAdjList(vector<pair<int, int>> &edges, int n) {
    vector<vector<int>> adj(n);
    for (auto e: edges) {
        int i = e.first;
        int j = e.second;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    return adj;
}
