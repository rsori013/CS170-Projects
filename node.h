#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;

struct Node {
    vector<vector<int>> puzzle;
    int g;
    int h;
    int f;
    Node* parent;
};
#endif // NODE_H