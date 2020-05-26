//
// Created by Jakub Sroka on 01.05.2020.
//

#include <iostream>
#include "Graph.h"
#include "Exercise.h"

bool isOnBoard(int H, int W, int i, int j){
    return i >= 0 && i < H && j >= 0 && j < W;
}

Graph::Graph(const Exercise &exercise){
    Node*** nodesTab = new Node**[exercise.H];
    for(int i=0; i<exercise.H;i++){
        nodesTab[i] = new Node*[exercise.W];
        for(int j=0; j<exercise.W; j++) nodesTab[i][j] = nullptr;
    }
    for(int i=0; i<exercise.H; i++){
        for(int j=0; j<exercise.W; j++){
            //łączenie dodawane są dwustronnie, a budowanie odbywa się przez dołączanie z lewej i u góry
//            std::cout << "i=" << i << " j="<<j << " :" << exercise.board[i][j]<<std::endl;
            switch(exercise.board[i][j]) {
                case '+':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i-1, j)){
                        if(nodesTab[i-1][j] != nullptr && (exercise.board[i-1][j] == '+' ||  exercise.board[i-1][j] == '|' )){
//                            std::cout<< "up association" <<std::endl;
                            nodesTab[i-1][j]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i-1][j]);
//                            std::cout << "curr neighbor len = " << nodesTab[i][j] -> neighbors.size() << "added neighbor len = " << nodesTab[i-1][j] -> neighbors.size() << std::endl;
                        }
                    }
                    if(isOnBoard(exercise.H, exercise.W, i, j-1)){
                        if(nodesTab[i][j-1] != nullptr && (exercise.board[i][j-1] == '+' ||  exercise.board[i][j-1] == '-' )){
//                            std::cout<< "left association" <<std::endl;
                            nodesTab[i][j-1]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i][j-1]);
                        }
                    }
                    break;
                case '-':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i, j-1)){
                        if(nodesTab[i][j-1] != nullptr && (exercise.board[i][j-1] == '+' ||  exercise.board[i][j-1] == '-' )){
//                            std::cout<< "left association" <<std::endl;
                            nodesTab[i][j-1]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i][j-1]);
                        }
                    }
                    break;
                case '|':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i-1, j)){
                        if(nodesTab[i-1][j] != nullptr && (exercise.board[i-1][j] == '+' ||  exercise.board[i-1][j] == '|' )){
//                            std::cout<< "up association" <<std::endl;
                            nodesTab[i-1][j]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i-1][j]);
//                            std::cout << "curr neighbor len = " << nodesTab[i][j] -> neighbors.size() << "added neighbor len = " << nodesTab[i-1][j] -> neighbors.size() << std::endl;

                        }
                    }
                    break;
                case '.':
                    break;
            }
            if(nodesTab[i][j] != nullptr) this->nodes.push_back(nodesTab[i][j]);
        }
    }
//    for(int i=0; i<exercise.H; i++) {
//        for (int j = 0; j < exercise.W; j++) {
//            if(nodesTab[i][j] != nullptr) this->nodes.push_back(nodesTab[i][j]);
//        }
//    }

    this->findConnectedComponents();
}

int countVertexInConnectedComponent(Node* &node){

    int count = 0;
    node->marker = 1;
    for(Node* neighbour: node->neighbors){
        if(neighbour -> marker == 0){
            count += countVertexInConnectedComponent(neighbour);
        }
    }
    return count + 1;
}

void Graph::findConnectedComponents() {
    for(Node* node : this->nodes){
        if(node -> marker == 0){
            int count = countVertexInConnectedComponent(node);
            this->connectedComponents.emplace_back(std::pair<int, Node*>(count, node));
        }
    }
    for(Node* node : this->nodes)
        if(node -> marker == 1) node -> marker = 0;

    std::cout<< "Connected components counts: ";
    this->connectedComponents.sort();
    for(std::pair<int, Node*> p : this->connectedComponents) std::cout<< p.first << " ";
    std::cout<< std::endl;
}
