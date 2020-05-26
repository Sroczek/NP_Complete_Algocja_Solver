#include <iostream>
#include <string>
#include "InputReader.h"

int readInput(std::string filename){
    std::cout << filename << std::endl;
    return 0;
}

int main() {
    Exercise exercise = InputReader::read();
    std::cout << exercise << std::endl;
    Graph graph = Graph(exercise);


    return 0;
}