#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include "node.h"
#include "Astar.h"
#include <chrono>
#include <stack>
#include "ucNode.h"
#include "UCS.hpp"
#include "Problem.h"

using namespace std;

auto start_time = chrono::high_resolution_clock::now();

vector<vector<int>> defaultPuzzle = {{8, 7, 1},
                                     {6, 0, 2},
                                     {5, 4, 3}};

vector<vector<int>> goalPuzzle =    {{1, 2, 3},
                                     {4, 5, 6},
                                     {7, 8, 0}};

void printPuzzle(const vector<vector<int>> &puzzle) {
    for (const auto &row : puzzle) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

bool isPuzzleValid(const vector<vector<int>> &puzzle) {
    unordered_set<int> numbers;
    for (const auto &row : puzzle) {
        for (const auto &val : row) {
            if (val >= 0 && val <= 8) {
                if (numbers.find(val) == numbers.end()) {
                    numbers.insert(val);
                } else {
                    return false; // Duplicate found
                }
            } else {
                return false; // Invalid number
            }
        }
    }
    return true;
}

vector<vector<int>> getPuzzleFromInput() {
    vector<vector<int>> puzzle(3, vector<int>(3));
    bool zeroEntered = false;
    cout << "Enter your puzzle, use a zero to represent the blank." << endl;
    while (true) {
        for (int i = 0; i < 3; ++i) {
            cout << "Enter the " << (i + 1) << " row, use space or tabs between numbers." << endl;
            string input;
            getline(cin, input);
            stringstream ss(input);
            for (int j = 0; j < 3; ++j) {
                int value;
                ss >> value;
                if (value == 0) {
                    if (!zeroEntered) {
                        zeroEntered = true;
                    } else {
                        cout << "Only 1 blank (zero) is allowed. Please try again." << endl;
                        --i; // Repeat the current row input
                        break;
                    }
                }
                puzzle[i][j] = value;
            }
        }
        if (isPuzzleValid(puzzle)) {
            break;
        } else {
            cout << "Invalid puzzle, please make sure numbers 0 to 8 are entered with no duplicates. Try again." << endl;
        }
    }
    return puzzle;
}

int main() {
    int choice;
    cout << "Welcome to XXX (change this to your student ID) 8 puzzle solver. Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> choice;
    cin.ignore();
    vector<vector<int>> puzzle;
    if (choice == 1) {
        puzzle = defaultPuzzle;
    } else if (choice == 2) {
        puzzle = getPuzzleFromInput();
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    printPuzzle(puzzle);

    cout << "Enter your choice of algorithm:" << endl;
    cout << "1- Uniform Cost Search" << endl;
    cout << "2- A* with the Misplaced Tile heuristic." << endl;
    cout << "3- A* with the Euclidean distance heuristic." << endl;
    int algorithmChoice;
    cin >> algorithmChoice;

    switch(algorithmChoice) {
        case 1:
            {
                cout << "Uniform Cost Search" << endl;
                int x, y;
                for (int i = 0; i < puzzle.size(); ++i) {
                        for (int j = 0; j < puzzle[i].size(); ++j) {
                            if (puzzle[i][j] == 0) { 
                                x = j;
                                y = i;
                            }
                        }
                }
                //create start state ucNode(parent, vector<state>, yB, xB, g_n, depth)
                ucNode* startState = new ucNode(nullptr, puzzle, y, x, 0, 0);
                //Problem(startNode, goalvector<state>)
                Problem* p = new Problem(startState, goalPuzzle);
                ucNode* solution = ucs(p);

                if(solution != nullptr){
                    cout << "Found goal state!\n";
                    printPuzzle(solution->state);
                    stack <ucNode*> full_sol;
                    ucNode* cur = solution;
                    while (cur->parent != nullptr){
                        full_sol.push(cur);
                        cur = cur->parent;
                    }
                    cout << "Here is the sequence of actions: \n";
                    printPuzzle(puzzle);
                    cout <<  "\n";
                    while(!full_sol.empty()){
                        cur = full_sol.top();
                        printPuzzle(cur->state);
                        cout << "\n";
                        full_sol.pop();                        
                    }
                    cout << "To solve this problem the search algorithm expanded a total of " << p->expandedNodes << " nodes.\n";
                    cout << "The maximum number of nodes in the queue at any one time: " << p->maxQueueSize << ".\n";
                    cout << "The depth of the goal node was " << solution->depth << ".\n";
                }
                else{
                    cout << "No solution found.\n";
                    cout << "Number of nodes expanded: " << p->expandedNodes << "\n";
                }
                               
            }
            break;
        case 2:
            cout << "A* with the Misplaced Tile heuristic." << endl;
            
            AStarMisplaced(puzzle, goalpuzzle);
            break;
        case 3:
            cout << "A* with the Euclidean distance heuristic." << endl;
            break;
        default:
            cout << "Whats up with you? " << endl;
            break;
    }
    cout << "HELLLO WORLD" << endl;
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "Runtime: " << duration << " ms" << endl;
    return 0;
}