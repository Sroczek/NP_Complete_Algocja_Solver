//
// Created by Jakub Sroka on 01.05.2020.
//

#ifndef SEMESTERPROJECT_GRAPH_H
#define SEMESTERPROJECT_GRAPH_H


#include <list>
#include "Exercise.h"
#include "Node.h"

class Graph {

public:
    std::list<Node*> nodes;
    std::list<std::pair<int, Node*>> connectedComponents;
    void findConnectedComponents();
    Graph(const Exercise& exercise);
};


#endif //SEMESTERPROJECT_GRAPH_H
