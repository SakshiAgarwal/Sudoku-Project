//
// Created by Sakshi Agarwal on 11/7/19.
//

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
using namespace std;

class SimulatedAnnealing
{
  private: 
    Sudoku current;
    vector<pair<int, int>> freePoints;

  public:
    // Thresholding parameters -
    // initial Temperature T
    // numIterations - number of Iterations for a particular temp T
    // change the threshold probability
    double T;
    double Tmin;
    double alpha;
    int numIterations;
    double fStop;
    double p;

    SimulatedAnnealing(Sudoku inputSudoku);
    SimulatedAnnealing(double inputT, double inputTmin, double inputAlpha, int inputNum,int inputFstop, double inputP, Sudoku inputBoard);
    
    Sudoku getNeighbor();
    void printCurrentBoard();

    bool run();
};
#endif