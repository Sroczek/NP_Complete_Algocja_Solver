//
// Created by Jakub Sroka on 01.05.2020.
//

#include "InputReader.h"
#include "Exercise.h"

Exercise InputReader::read(){
    int W, H, L, K;
    std::cin >> W >> H >> L >> K;

    std::string parkName;

    std::getline(std::cin, parkName, '\n');
    std::getline(std::cin, parkName, '\n');

    char** board = new char*[H];

    for(int i=0; i<H; i++){
        std::string line;
        std::getline(std::cin, line, '\n');

        board[i] = new char[W];
        for(int j=0; j<W; j++) board[i][j] = line[j];
    }

    return Exercise(W, H, L, K, board);
}