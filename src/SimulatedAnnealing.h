#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include <memory>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <vector>
#include "Sudoku.h"
#include "Utils.h"
#include "Logger.h"
using namespace std;

class SimulatedAnnealing
{
  private: 
    static const int LOG_SIMULATED_ANNEALING = false;
    vector<pair<int, int>> freePoints;
    Sudoku solution;

  public:
    // Thresholding parameters -
    // initial Temperature T
    // numIterations - number of Iterations for a particular temp T
    // change the threshold probability
    double T;
    double Tmin;
    double alpha;
    int num_neighbors;
    double p;
    int total_iteration;

    SimulatedAnnealing(Sudoku inputSudoku);
    SimulatedAnnealing(double inputT, double inputTmin, double inputAlpha, int inputNeighbors, double inputP, Sudoku inputBoard);
    
    Sudoku getNeighbor();
    void printCurrentBoard();
    void printMasked(int val);
    bool log(vector<double> row);

    bool run();
};
#endif