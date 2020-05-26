//
// Created by Jakub Sroka on 30.04.2020.
//

#ifndef SEMESTERPROJECT_NODE_H
#define SEMESTERPROJECT_NODE_H

#include <list>

class Node {
    public:
        const int x;
        const int y;
    public:
        int marker;
        std::list<Node*> neighbors;

        Node(int _x, int _y): x(_x), y(_y), marker(0), neighbors(){};
        Node(int _x, int _y, std::list<Node*> &_neighbors): x(_x), y(_y), marker(0), neighbors(_neighbors){};
//        Node(const Node& node): x(node.x), y(node.y), marker(node.marker){};
        void addNeighbour(Node* &neighbor){ this->neighbors.push_front(neighbor); };
        void removeNeighbour(Node* &neighbor){ this->neighbors.remove(neighbor); };
//        int getMarker(){ return this->marker; };
//        std::list<Node*> getNeighbors(){ return this->neighbors; };
};

#endif //SEMESTERPROJECT_NODE_H
