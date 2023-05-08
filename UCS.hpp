#ifndef UCS_HPP
#define UCS_HPP

#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;
struct ucNode{
    ucNode* parent = nullptr;
    vector<vector<int>> state;
    int xB = 0;
    int yB = 0;
    int g_n = 0;
    int depth = 0;
    vector<ucNode*> children;
    ucNode(ucNode* p, vector<vector<int>> s, int y, int x, int g, int d){
        this->parent = p;
        this->state = s;
        this->yB = y;
        this->xB = x;
        this->g_n = g;
        this->depth = d;
    }
};

struct Problem{
    ucNode* initialState = nullptr;
    vector<vector<int>> goalState;
    int expandedNodes = 0;
    int maxQueueSize = 0;
    Problem(ucNode* is, vector<vector<int>> gs){
        this->initialState = is;
        this->goalState = gs;
        this->expandedNodes = 0;
        this->maxQueueSize = 0;
    }
};

ucNode* ucs(Problem* p);
void print(const vector<vector<int>> &state);
vector<ucNode*> expandNodes(ucNode*, vector<vector<vector<vector<int>>>> &, int , int);

ucNode* ucs(Problem* p){
    ucNode* start = p->initialState;
    int row = start->yB;
    int col = start->xB;
    int width = p->goalState.size();
    int height = p->goalState[0].size();

    //queue to iterate through
    queue<ucNode*> queue;
    //a vector (for hash) of vectors(for multiple values) or vector<vector<int>> for puzzles
    vector<vector<vector<vector<int>>>> previousStates(width*height);

    //initialize queue with the start state and add to previous states
    queue.push(start);
    previousStates[row*width + col].push_back(start->state);
    ucNode* current;

    //while the queue of untested states is not empty keep going
    while(!queue.empty()){
        //find the size of queue to get Max Queue Size
        if(queue.size() > p->maxQueueSize){p->maxQueueSize = queue.size();} 

        //pop the top state to check node
        current = queue.front();
        queue.pop();

        //if the state is the goal state then return the state
        if(current->state == p->goalState){
            return current;
        }
        //if the state is not the goal state
        else{
            cout << "The best state to expand with g(n) = " << current->g_n << " and h(n) = 0 is:\n";
            print(current->state);

            //find new states
            vector<ucNode*> expansion = expandNodes(current, previousStates, width, height);
            //if any states are found add them to the queue.
            if(!expansion.empty()){
                for(int i = 0; i < expansion.size(); i++){
                    queue.push(expansion[i]);
                }
            }
        }
        p->expandedNodes++;
    }
    return nullptr;
}

void print(const vector<vector<int>> &state){
    for (const auto &row : state) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector <ucNode*> expandNodes(ucNode* curr, vector<vector<vector<vector<int>>>>& previousStates, int width, int height){
    vector <ucNode*> newStates;
    //expand the node using the operators
    int x = curr->xB;
    int y = curr->yB;
    vector<vector<int>> operators = {{0,1},{0,-1},{1,0},{-1,0}};
    for(int i = 0; i < operators.size(); i++){
        int newY = y + operators[i][0];
        int newX = x + operators[i][1];

        //only use the new operator if it is valid
        if((newY < height) && (newX < width) && (newX >= 0) && (newY >= 0)){
            //get new state of vector with swapped values
            vector<vector<int>> newState = curr->state;
            swap(newState[y][x], newState[newY][newX]);   

            //check if this new state has already been pushed into the queue before
            if(!(find(previousStates[newY*width + newX].begin(), 
                        previousStates[newY*width + newX].end(), newState) != previousStates[newY*width+ newX].end())){

                //if the new state has not been pushed in create a new node state for it 
                ucNode* node = new ucNode(curr, 
                                    newState,
                                    newY,
                                    newX,
                                    curr->g_n + 1,
                                    curr->depth + 1);

                //add node to current' children.
                curr->children.push_back(node);
                //add to newStates to send back
                newStates.push_back(node);
            }
        }
    }
    return newStates;
}

#endif