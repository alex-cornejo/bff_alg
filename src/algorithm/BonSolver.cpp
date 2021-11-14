//
// Created by ale_j on 11/1/2021.
//

#include <cstdlib>
#include <numeric>
#include "BonSolver.h"

using namespace std;

std::vector<int> BonSolver::burning_sequence(int k, vector<int> &V) {
    int n = V.size();
    std::vector<int> f;
    std::vector<bool> f_aux(n);
    std::vector<bool> C(n);

    // 1. Construct a sequence f
    int covered_count = 0;
    while (covered_count < n) {
        int f_i = rand() % n;
        while (C[f_i]) {
            f_i = rand() % n;
        }
        f.push_back(V[f_i]);
        f_aux[f_i] = true;
        int iv = 0;
        for (int v: V) {
            if (D[V[f_i]][v] <= 2 * (k - 1)) {
                if (!C[iv]) {
                    C[iv] = true;
                    if (++covered_count == n) break;
                }
            }
            iv++;
        }
    }

    // 2. Add extra vertices to f until all vertices in V are covered
    std::fill(C.begin(), C.end(), false);
    covered_count = 0;
    int S = f.size();
    int i = 1;
    for (auto u: f) {
        int iv = 0;
        for (int v: V) {
            if (D[u][v] <= S - i && !C[iv]) {
                C[iv] = true;
                if(++covered_count==n) goto allCoveredByF;
            }
            iv++;
        }
        i++;
    }
    // i = S + 1;
    // second part
    while (covered_count < n) {
        int f_i = rand() % n;
        while (C[f_i]) {
            f_i = rand() % n;
        }
        f.push_back(V[f_i]);
        f_aux[f_i] = true;
        S = f.size();
        i = 1;
        for (auto u: f) {
            int iv = 0;
            for (int v: V) {
                if (D[u][v] <= S - i && !C[iv]) {
                    C[iv] = true;
                    if (++covered_count == n) {
                        goto allCoveredByF;
                    }
                }
                iv++;
            }
            i++;
        }
    }
    allCoveredByF:
    return f;
}

BonSolver::BonSolver(const int n, int **D) : n(n), D(D) {}

std::vector<int> BonSolver::run() {

    vector<int> V(n);
    std::iota(V.begin(), V.end(), 0);

    int low = 0;
    int high = n - 1;
    vector<int> f;
    while (low <= high) {
        int k = (low + high) / 2;
        srand(seed);
        vector<int> f_tmp = burning_sequence(k, V);
        if (f_tmp.size() > 3 * k - 2) {
            low = k + 1;
        } else {
            high = k - 1;
            f = f_tmp;
        }
    }
    return f;
}
