#ifndef PROBLEM_H
#define PROBLEM_H
#include <vector>
#include "Node.h"

using namespace std;

struct Problem{
    Node* initialState = nullptr;
    vector<vector<int>> goalState;
    int expandedNodes = 0;
    int maxQueueSize = 0;
    Problem(Node* is, vector<vector<int>> gs){
        this->initialState = is;
        this->goalState = gs;
        this->expandedNodes = 0;
        this->maxQueueSize = 0;
    }
};

#endif