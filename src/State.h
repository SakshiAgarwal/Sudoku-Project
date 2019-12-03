#ifndef STATE_H
#define STATE_H
#include <iostream>
#include "Utils.h"

using namespace std;

class State{
  public:
    /** state description
     * A curr matrix which represents a state of the Sudoku matrix
     * f matrix : remembers the fixed elements in the initial Sudoku matrix
     * State constructor : initilializes both the matrices
     * neighbour() : find a neighbour of the curr matrix and returns the state for it
     * fitness() : evaluates the fitness of the curr state of Sudoku and return an int value
     * printState() : prints the current state matrix **/
    int curr[Utils::N][Utils::N];
    int f[Utils::N][Utils::N];
    
    State(int a[Utils::N][Utils::N],int fix[Utils::N][Utils::N]);
    State neighbour();
    int fitness();
    void printState();
};
#endif