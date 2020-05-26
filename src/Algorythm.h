//
// Created by Jakub Sroka on 25.05.2020.
//

#ifndef SEMESTERPROJECT_ALGORYTHM_H
#define SEMESTERPROJECT_ALGORYTHM_H


#include "Graph.h"

class Algorythm {
public:
    static int L;
    static void findSolution(Graph &graph, int _L, int K){
        Algorythm::L = _L;
        Algorythm::solve(graph, K);
    }
    static void solve(Graph &graph, int k);
};


#endif //SEMESTERPROJECT_ALGORYTHM_H
