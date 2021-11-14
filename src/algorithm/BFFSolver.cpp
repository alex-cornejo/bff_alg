//
// Created by ale_j on 11/1/2021.
//

#include <cstdlib>
#include <climits>
#include "BFFSolver.h"

using namespace std;

BFFSolver::BFFSolver(const int n, int **D, vector<pair<int, int>> &edges) : n(n), D(D) {
    plus = false;
    D2S.resize(n);
    burned.resize(n);
    adj = AlgUtils::createAdjList(edges, n);
}

void BFFSolver::init() {
    fill(D2S.begin(), D2S.end(), INT_MAX);
    fill(burned.begin(), burned.end(), false);
}

int BFFSolver::getFarthest() {
    int maxDist = -1;
    int v = -1;
    for (int i = 0; i < n; ++i) {
        if (!burned[i] && maxDist < D2S[i]) {
            maxDist = D2S[i];
            v = i;
        }
    }
    return v;
}

void BFFSolver::updateDistances(int v) {
    for (int i = 0; i < n; ++i) {
        D2S[i] = min(D2S[i], D[v][i]);
    }
}

void BFFSolver::setPlus(bool plus) {
    BFFSolver::plus = plus;
}

vector<int> BFFSolver::run() {

    int rep = plus ? n : 1;
    vector<int> bestF;
    for (int iRep = 0; iRep < rep; ++iRep) {
        init();
        vector<int> f;
        f.reserve(n);

        // select initial vertex to be burned
        int v = plus ? iRep : rand() % n;
        f.push_back(v);
        updateDistances(v);
        burned[v] = true;

        // contains burned vertices
        vector<int> B;
        B.reserve(n);
        B.push_back(v);
        int iB = 0;
        while (B.size() != n) {
            // Select the farthest vertex from the already selected vertices
            v = getFarthest();

            // update distances from S
            updateDistances(v);

            // add to solution
            f.push_back(v);

            // burn neighbors of already burned vertices
            int tmpBsize = B.size();
            for (int i = iB; i < tmpBsize; ++i) {
                int u = B[i];
                for (auto w: adj[u]) {
                    if (!burned[w] && w != v) {
                        burned[w] = true;
                        B.push_back(w);
                    }
                }
            }
            // burn vertex of current iteration
            burned[v] = true;
            B.push_back(v);
            iB = tmpBsize;
        }
        if (iRep == 0 || bestF.size() > f.size()) {
            bestF = f;
        }
    }

    return bestF;
}



