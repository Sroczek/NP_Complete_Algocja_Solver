//
// Created by Jakub Sroka on 30.04.2020.
//

#ifndef SEMESTERPROJECT_NODE_H
#define SEMESTERPROJECT_NODE_H

#include <list>

enum NodeMarker{
    NONE = 0,
    VISITED = 1,
    DELETED = 2,
    ADDED = 3
};

class Node {
    public:
        const int x;
        const int y;
    public:
        // 0 means unvisited
        int marker;
        int tmpMarker = 0;
        bool inSolution = false;
        std::list<Node*> neighbors;

        Node(int _x, int _y): x(_x), y(_y), marker(0), neighbors(){};
        Node(int _x, int _y, std::list<Node*> &_neighbors): x(_x), y(_y), marker(0), neighbors(_neighbors){};
        void addNeighbour(Node* &neighbor){ this->neighbors.push_front(neighbor); };
        void markInRadius(int marker, int radius);
        void unmarkInRadius(int marker, int radius);
        void removeNeighbour(Node* &neighbor){ this->neighbors.remove(neighbor); };
        std::list<Node*> getNodesInRadius(int radius);
};

#endif //SEMESTERPROJECT_NODE_H
