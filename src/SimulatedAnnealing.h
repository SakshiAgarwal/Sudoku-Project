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
#include "Sudoku.h"
#include "State.h"
#include "Utils.h"
using namespace std;

class SimulatedAnnealing
{
  public:
    /** Change here for a 25*25 input **/
    const static int SRN = 3;
    const static int N = 9;

    // Thresholding parameters -
    // initial Temperature T
    // numIterations - number of Iterations for a particular temp T
    // change the threshold probability
    double T;
    double Tmin;
    double alpha;
    int numIterations;
    double f;
    double p;

    SimulatedAnnealing(double T, double Tmin, double a, int num,int fstop, double p);
    int randomGenerator(int num);
    State run(Sudoku *Board);
};
#endif