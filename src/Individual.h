#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <memory>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include "Utils.h"
using namespace std;

class Individual
{
  public:
    int chromosome[Utils::N][Utils::N];
    int fitness;
    Individual(int** chromosome);
    Individual mate(Individual parent2, int fixed_val[Utils::N][Utils::N], float mutation);
    int cal_fitness();
    bool unUsedInBox(int rowStart, int colStart, int num, int i, int j);
    bool unUsedInRow(int i,int num, int j);
    bool unUsedInCol(int j,int num, int i);
    bool CheckIfSafe(int i,int j,int num);
    void printSudoku();
    friend bool operator< (const Individual &ind1, const Individual &ind2);
};
#endif