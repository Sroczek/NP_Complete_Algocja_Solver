//
// Created by Jakub Sroka on 25.05.2020.
//

#include <iostream>
#include "Algorythm.h"

int Algorythm::L;

bool Algorythm::solve(Graph &graph, int k) {

    if(k == 0)
        counter++;
        for(auto node: graph.nodes){
            if(node->inSolution){
                std::cout << node->y << " " << node->x << std::endl;
            }
        }
        return true;
    }

    graph.findConnectedComponents();

    if(graph.connectedComponents.empty())
        return false;

    auto first = graph.connectedComponents.begin();
    Node* firstNode = (*first).second;
    std::list<Node*> crawlSpace = firstNode->getNodesInRadius(Algorythm::L);

    for(auto node : crawlSpace){
        if(node->marker != 0) continue;

        node->inSolution = true;
        // k+2 becouse of 0 1 reserved and k+2 is still unique
        node->markInRadius(k+2, Algorythm::L);
        if(Algorythm::solve(graph, k-1)) return true;

        node->unmarkInRadius(k+2, Algorythm::L);
        node->inSolution = false;
    }
}
