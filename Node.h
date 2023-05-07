#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

struct Node{
    Node* parent = nullptr;
    vector<vector<int>> state;
    int xB = 0;
    int yB = 0;
    int g_n = 0;
    int depth = 0;
    vector<Node*> children;
    Node(Node* p, vector<vector<int>> s, int y, int x, int g, int d){
        this->parent = p;
        this->state = s;
        this->yB = y;
        this->xB = x;
        this->g_n = g;
        this->depth = d;
    }
};


#endif