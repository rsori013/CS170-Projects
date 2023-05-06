#ifndef PROBLEM_H
#define PROBLEM_H
#include <vector>
#include "Node.h"

struct Problem{
    Node* initialState = nullptr;
    std::vector<std::vector<int>> goalState;
    int expandedNodes = 0;
    int dimensions = 3;
    int maxQueueSize = 0;
};

#endif