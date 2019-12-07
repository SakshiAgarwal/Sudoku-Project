#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <ctime>
#include "Utils.h"
#include "Individual.h"

using namespace std;

class GeneticAlgorithm
{
  public:
    int fixed_val[Utils::N][Utils::N];
    int mat[Utils::N][Utils::N];

    int **create_gnome(int mat[Utils::N][Utils::N]);
    GeneticAlgorithm(int mat[Utils::N][Utils::N]);
    void compute(int population_size, int elitism, int eligible, float mutation, int stop);
};

#endif