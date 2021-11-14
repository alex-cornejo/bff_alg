//
// Created by ale_j on 11/1/2021.
//

#ifndef BONUS_BONSOLVER_H
#define BONUS_BONSOLVER_H


#include <vector>

class BonSolver {
protected:
    int seed = 0;
    const int n;
    int **D;

    std::vector<int> burning_sequence(int k, std::vector<int> &V);

public:
    BonSolver(int n, int **D);

    virtual std::vector<int> run();
};


#endif //BONUS_BONSOLVER_H
