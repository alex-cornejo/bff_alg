#include <iostream>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>

#include "utils/FileUtil.h"
#include "algorithm/BFFSolver.h"
#include "algorithm/BonSolver.h"

using namespace boost;
using namespace std;


int **computeAllShortestPaths2(vector<pair<int, int>> &edges_vec, int n) {
    const int m = edges_vec.size();

    typedef adjacency_list<vecS, vecS, undirectedS, no_property,
            property<edge_weight_t, int, property<edge_weight2_t, int>>>
            Graph;

    typedef std::pair<int, int> Edge;
    Edge edges_array[m];
    for (int i = 0; i < m; ++i)
        edges_array[i] = Edge(edges_vec[i].first, edges_vec[i].second);

    Graph G(edges_array, edges_array + m, n);

    property_map<Graph, edge_weight_t>::type w = get(edge_weight, G);
    int weights[m];
    std::fill(weights, weights + m, 1);
    int *wp = weights;

    graph_traits<Graph>::edge_iterator e, e_end;
    for (boost::tie(e, e_end) = edges(G); e != e_end; ++e)
        w[*e] = *wp++;

    int **D = new int *[n];
    for (int i = 0; i < n; ++i) {
        D[i] = new int[n];
    }
    johnson_all_pairs_shortest_paths(G, D);
    return D;
}

int **computeAllShortestPaths(vector<vector<int>> &adj, int n) {

    int **D = new int *[n];
    for (int i = 0; i < n; ++i) {
        D[i] = new int[n];
        fill(D[i], D[i] + n, std::numeric_limits<int>::max());
        D[i][i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        queue<int> q;
        vector<bool> visited(n);
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            for (auto u: adj[s]) {
                if (!visited[u]) {
                    D[i][u] = D[i][s] + 1;
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
    }

    return D;
}

int main(int argc, char **argv) {

    string input_file = argv[1];
    string alg = argv[2];

    // read instance
    vector<pair<int, int>> edges_vec;
    int n;
    tie(edges_vec, n) = FileUtil::load_graph(input_file);
    vector<vector<int>> adj = AlgUtils::createAdjList(edges_vec, n);

    // time of compute all shortest paths
    clock_t begin = clock();
    int **D = computeAllShortestPaths(adj, n);
//    int **D2 = computeAllShortestPaths2(edges_vec, n);
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if(D[i][j]!=D2[i][j]){
//                cout<<D[i][j]<<endl;
//                cout<<D2[i][j]<<endl;
//                int a = 1;
//            }
//
//        }
//    }
    clock_t end = clock();
    double time_casp = (double) (end - begin) / CLOCKS_PER_SEC;
    // end computations of all shortest paths
    cout << "Compute all shortest paths running time: " << time_casp << " seconds" << endl;

    // time of algorithm
    vector<int> f;
    begin = clock();

    if (alg == "bon") {
        BonSolver solver(n, D);
        f = solver.run();
    } else if (alg == "bff") {
        BFFSolver solver(n, D, edges_vec);
        f = solver.run();
    } else if (alg == "bff+") {
        BFFSolver solver(n, D, edges_vec);
        solver.setPlus(true);
        f = solver.run();
    } else {
        cerr << "Invalid algorithm!" << endl;
    }
    end = clock();
    double time_alg = (double) (end - begin) / CLOCKS_PER_SEC;

    // print computations times and solution
    cout << "Algorithm running time: " << time_alg << " seconds" << endl;

    cout << "[";
    for (int i = 0; i < f.size() - 1; ++i) {
        cout << f[i] << ", ";
    }
    cout << f.back() << "]" << endl;
    cout << f.size() << endl;

    // clear memory
    for (int i = 0; i < n; ++i) {
        delete[] D[i];
    }
    return 0;
}
