//
// Created by Jakub Sroka on 24.05.2020.
//

#ifndef SEMESTERPROJECT_EXERCISE_H
#define SEMESTERPROJECT_EXERCISE_H


#include <vector>
#include <sstream>

class Exercise {
    public:
        int W;
        int H;
        int L;
        int K;
        char** board;

    Exercise(int w, int h, int l, int k, char** board);
    friend std::ostream& operator<<(std::ostream& os, const Exercise& exercise);
};


#endif //SEMESTERPROJECT_EXERCISE_H
