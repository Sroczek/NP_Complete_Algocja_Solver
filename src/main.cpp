#include <iostream>
#include <string>
#include "InputReader.h"
#include "Algorythm.h"
#include <ctime>

int readInput(std::string filename){
    std::cout << filename << std::endl;
    return 0;
}

int main() {

    Exercise exercise = InputReader::read();

//    clock_t start = clock();
    Graph graph = Graph(exercise);
    Algorythm::findSolution(graph, exercise.L, exercise.K);

//    clock_t stop = clock();

//    std::cout<< "Liczba cykli trwania = " << stop - start << std::endl;
//    std::cout<< "CLOCKS_PER_SEC = " << CLOCKS_PER_SEC << std::endl;
//    std::cout<< "W przeliczeniu na ms = " << 1000 * float(stop - start) / (CLOCKS_PER_SEC) << std::endl;

    return 0;
}