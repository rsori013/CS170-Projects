#include <map>
#include <queue>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <utility>
#include "Node.h"
#include "Problem.h"

struct compare{bool operator()(const Node* &ln, const Node* &rn) const{return ln->g_n < rn->g_n;}};


Node* ucs(Problem* p){
    std::priority_queue<Node*, std::vector<Node*>, compare> queue;

    //initialize queue with the start state
    Node* start = p->initialState;
    queue.push(start);
    Node* current;

    //while the queue of untested states is not empty keep going
    while(!queue.empty()){
        //pop the top state to check node
        current = queue.top();
        queue.pop();  

        //if the state is the goal state then return the state
        if(current->state == p->goalState){
            return current;
        }
        //if the state is not the goal state
        else{
            //expand the node using the operators
            std::vector<std::vector<int>> operators = {{0,1},{0,-1},{1,0},{-1,0}};
            for(int i = 0; i < operators.size(); i++){
                //check if using the operator is valid
                if((current->xB+operators[i][1] < current->state.size()) && (current->yB+operators[i][0] < current->state[0].size())){
                    //check if state has been visited or state is in queue
                    //if both are false add it to queue
                    if(true){
                        Node* node = new Node;
                        node->parent = current;
                        node->state = current->state;
                        std::swap(node->state[node->yB][node->xB],node->state[node->yB][node->xB+1]);
                        node->xB+=operators[i][1];
                        node->yB+=operators[i][0];
                        node->g_n++;
                        queue.push(node);
                        current->children.push_back(node);
                    }
                }   
            }

        }
    }
    return nullptr;
}