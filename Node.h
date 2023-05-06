#ifndef NODE_H
#define NODE_H
#include <vector>

struct Node{
    Node* parent = nullptr;
    std::vector<std::vector<int>> state;
    int xB;
    int yB;
    int g_n = 0;
    std::vector<Node*> children;
};


#endif