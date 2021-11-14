//
// Created by ale_j on 11/1/2021.
//

#ifndef BONUS_BFFSOLVER_H
#define BONUS_BFFSOLVER_H


#include <vector>
#include "AlgUtils.h"

class BFFSolver {

private:
    const int n;
    std::vector<std::vector<int>> adj;
    bool plus;
    std::vector<int> D2S;
    std::vector<bool> burned;
    int **D;

    void init();

    int getFarthest();

    void updateDistances(int v);

public:

    BFFSolver(int n, int **D, std::vector<std::pair<int, int>>& edges);

    std::vector<int> run();

    void setPlus(bool plus);

};


#endif //BONUS_BFFSOLVER_H
