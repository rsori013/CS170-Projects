#include <queue>
#include <algorithm>
#include <iostream>
#include "node.h"

using namespace std;
void AStarMisplaced(vector<vector<int>>& initial_state);
int MisplacedTilesCounter(const vector<vector<int>>& current, const vector<vector<int>>& goal);
vector<Node*> ExpandNode(Node* current_node, const vector<vector<int>>& goal);
bool IsGoal(const vector<vector<int>>& current, const vector<vector<int>>& goal);
void printSolution(Node* goal_node);
pair<int, int> FindEmptyTile(const vector<vector<int>>& puzzle);
vector<vector<int>> SwapTiles(const vector<vector<int>>& puzzle, int row1, int col1, int row2, int col2);

void AStar(vector<vector<int>>& initial_state) {
    vector<vector<int>> goal = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 0}};

    queue<Node*> open;
    Node* root = new Node{initial_state, 0, MisplacedTilesCounter(initial_state, goal), 0, nullptr};
    root->f = root->g + root->h;
    open.push(root);

    int nodesExpanded = 0;
    int maxNodesInQueue = 1;
    int goalDepth = 0;

    while (!open.empty()) {
        Node* current = open.front();
        open.pop();

        if (IsGoal(current->puzzle, goal)) {
            goalDepth = current->g;
            printSolution(current);
            break;
        }

        vector<Node*> children = ExpandNode(current, goal);
        nodesExpanded++;

        for (int i = 0; i < children.size(); i++) {
            Node* child = children[i];
            open.push(child);
        }

        maxNodesInQueue= max(maxNodesInQueue, static_cast<int>(open.size()));
    }

    cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes.\n";
    cout << "The maximum number of nodes in the queue at any one time: " <<maxNodesInQueue << ".\n";
    cout << "The depth of the goal node was " << goalDepth << ".\n";
}





int MisplacedTilesCounter(const vector<vector<int>>& current, const vector<vector<int>>& goal) {
    int misplacedTiles = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (current[i][j] != goal[i][j] && current[i][j] != 0) {
                misplacedTiles++;
            }
        }
    }
    return misplacedTiles; // returning how many misplaced tiles there are currently
}

vector<Node*> ExpandNode(Node* current_node, const vector<vector<int>>& goal) {
    vector<Node*> children;
    pair<int, int> empty_tile = FindEmptyTile(current_node->puzzle);
    int row = empty_tile.first;
    int col = empty_tile.second;
    //possible directions a puzzle can move to 
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < directions.size(); ++i) {
        int new_row = row + directions[i].first;
        int new_col = col + directions[i].second;

        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            vector<vector<int>> new_puzzle = SwapTiles(current_node->puzzle, row, col, new_row, new_col);
            Node* child = new Node{new_puzzle, current_node->g + 1, MisplacedTilesCounter(new_puzzle, goal), 0, current_node};
            child->f = child->g + child->h;
            children.push_back(child);
        }
    }

    return children;
}

bool IsGoal(const vector<vector<int>>& current, const vector<vector<int>>& goal) { // Afunction to check if the current puzzle we have right now is the goal
    return current == goal;
}

void printSolution(Node* goal_node) {
    //it not the root node then there are other nodes to be printed. 
    if (goal_node->parent != nullptr) {
        printSolution(goal_node->parent);
    }

    cout << "The best state to expand with g(n) = " << goal_node->g << " and h(n) = " << goal_node->h << " is:\n";
    for (int i = 0; i < goal_node->puzzle.size(); ++i) {
        for (int j = 0; j < goal_node->puzzle[i].size(); ++j) {
            cout << goal_node->puzzle[i][j] << " ";
        }
    cout << "\n";
}
cout << "\n";

}


pair<int, int> FindEmptyTile(const vector<vector<int>>& puzzle) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (puzzle[i][j] == 0) { // meaning we find the empty tile lets gooo and returing its location
                return {i, j};
            }
        }
    }
    cout << "ERROR: Something went wrong" << endl;
    return {-4, -20}; 
}

vector<vector<int>> SwapTiles(const vector<vector<int>>& puzzle, int row1, int col1, int row2, int col2) {
    vector<vector<int>> new_puzzle = puzzle;
    swap(new_puzzle[row1][col1], new_puzzle[row2][col2]);
    return new_puzzle;
}

