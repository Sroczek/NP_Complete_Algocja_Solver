#include <string>
#include <list>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

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

class Graph {

public:
    std::list<Node*> nodes;
    std::list<std::pair<int, Node*>> connectedComponents;
    void findConnectedComponents();
    Graph(const Exercise& exercise);
};

class Algorythm {
public:
    static int L;
    static void findSolution(Graph &graph, int _L, int K){
        Algorythm::L = _L;
        Algorythm::solve(graph, K);
    };
    static bool solve(Graph &graph, int k);
};

class InputReader {
    public:
        static Exercise read();
};

int Algorythm::L;

int counter=0;

bool Algorythm::solve(Graph &graph, int k) {

    if(k == 0){
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
            switch(exercise.board[i][j]) {
                case '+':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i-1, j)){
                        if(nodesTab[i-1][j] != nullptr && (exercise.board[i-1][j] == '+' ||  exercise.board[i-1][j] == '|' )){
                            nodesTab[i-1][j]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i-1][j]);
                        }
                    }
                    if(isOnBoard(exercise.H, exercise.W, i, j-1)){
                        if(nodesTab[i][j-1] != nullptr && (exercise.board[i][j-1] == '+' ||  exercise.board[i][j-1] == '-' )){
                            nodesTab[i][j-1]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i][j-1]);
                        }
                    }
                    break;
                case '-':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i, j-1)){
                        if(nodesTab[i][j-1] != nullptr && (exercise.board[i][j-1] == '+' ||  exercise.board[i][j-1] == '-' )){
                            nodesTab[i][j-1]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i][j-1]);
                        }
                    }
                    break;
                case '|':
                    nodesTab[i][j] = new Node(i,j);
                    if(isOnBoard(exercise.H, exercise.W, i-1, j)){
                        if(nodesTab[i-1][j] != nullptr && (exercise.board[i-1][j] == '+' ||  exercise.board[i-1][j] == '|' )){
                            nodesTab[i-1][j]->addNeighbour(nodesTab[i][j]);
                            nodesTab[i][j]->addNeighbour(nodesTab[i-1][j]);

                        }
                    }
                    break;
                case '.':
                    break;
            }
            if(nodesTab[i][j] != nullptr) this->nodes.push_back(nodesTab[i][j]);
        }
    }

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
    this->connectedComponents.clear();

    for(Node* node : this->nodes){
        if(node -> marker == 0){
            int count = countVertexInConnectedComponent(node);
            this->connectedComponents.emplace_back(std::pair<int, Node*>(count, node));
        }
    }
    for(Node* node : this->nodes)
        if(node -> marker == 1) node -> marker = 0;

    //std::cout<< "Connected components counts: ";
    this->connectedComponents.sort();
}

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

    if(this->marker == marker) this->marker = 0;

    if(radius == 1){
        for(auto neighbor: this->neighbors) {
            if(neighbor->marker == marker){
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

int readInput(std::string filename){
    std::cout << filename << std::endl;
    return 0;
}

int main() {

    Exercise exercise = InputReader::read();

    Graph graph = Graph(exercise);
    Algorythm::findSolution(graph, exercise.L, exercise.K);

    return 0;
}

