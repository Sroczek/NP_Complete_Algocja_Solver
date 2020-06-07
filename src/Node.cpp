//
// Created by Jakub Sroka on 30.04.2020.
//

#include <iostream>
#include "Node.h"

void Node::markInRadius(int marker, int radius) {

    if(this->marker == 0) this->marker = marker;

    if(radius == 1){
        for(auto neighbor: this->neighbors) {
            if(neighbor->marker == 0){
                neighbor->marker = marker;
            }
        }
        return;
    }

    for(auto neighbor: this->neighbors) {
        neighbor->markInRadius(marker, radius -1);
    }
}

void Node::unmarkInRadius(int marker, int radius) {
//    std::cout<<"Stating unmarging" << std::endl;

    if(this->marker == marker) this->marker = 0;

    if(radius == 1){
        for(auto neighbor: this->neighbors) {
            if(neighbor->marker == marker){
//                std::cout << "Unmarking" << std::endl;
                neighbor->marker = 0;
            }
        }
        return;
    }

    for(auto neighbor: this->neighbors){
        neighbor->unmarkInRadius(marker, radius - 1);
    }
}

std::list<Node *> Node::getNodesInRadius(int radius) {
    std::list<Node *> res = std::list<Node *>();
    if(this->tmpMarker == 0) {
        res.push_back(this);
        this->tmpMarker = 1;
    }

    if(radius == 0){
        this->tmpMarker = 0;
        return res;
    }

    for(auto neighbor: this->neighbors){
        if(neighbor->tmpMarker == 0) res.splice(res.end(), neighbor->getNodesInRadius(radius - 1));
    }

    this->tmpMarker = 0;
    return res;
}
