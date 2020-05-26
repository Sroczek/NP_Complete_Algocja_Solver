//
// Created by Jakub Sroka on 24.05.2020.
//

#include "Exercise.h"

Exercise::Exercise(int w, int h, int l, int k, char** board) : W(w), H(h), L(l), K(k), board(board) {}

std::ostream &operator<<(std::ostream &os, const Exercise &exercise) {
    os << "Width: " << exercise.W
       << "  Height: " << exercise.H
       << "  Social Distance: " << exercise.L
       << "  People number: " << exercise.K << std::endl;
    for(int i=0; i<exercise.H; i++){
        for(int j=0; j<exercise.W; j++){
            os << exercise.board[i][j];
        }
        os << std::endl;
    }
    return os;
}
