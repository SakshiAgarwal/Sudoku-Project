//
// Created by Sakshi Agarwal on 11/7/19.
//

#include <memory>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include "Sudoku.h"
#include "SimulatedAnnealing.h"

/**  Thresholding parameters -
 * initial Temperature T
 * numIterations - number of Iterations for a particular temp T
 * change the threshold probability
**/

int main()
{
    int mat[9][9] =
            {
                {0, -1, -1, -1, -1, -1, -1, -1, 1},
                {-1, -1, 7, -1, -1, 8, -1, 2, 6},
                {6, -1, -1, 4, 2, -1, -1, 7, -1},
                {-1, 7, -1, -1, 6, 2, -1, 4, 3},
                {-1, -1, 5, 3, -1, 1, 6, -1, -1},
                {8, 6, -1, 7, 4, -1, -1, 0, -1},
                {-1, 0, -1, -1, 7, 6, -1, -1, 8},
                {2, 3, -1, 5, -1, -1, 7, -1, -1},
                {7, -1, -1, -1, -1, -1, -1, -1, 0}
            };

/**Create the sudoku board with matrix **/
    Sudoku Board(mat);

/**    Parameters for SA algorithm **/
    int T=20;
    double Tmin = 0.001;
    double alpha = 0.9;
    int numIterations = 500;
    double fstop = 0;
    double p = 0.6;
/**    Initialise SA with the parameters **/
    SimulatedAnnealingAlgorithm SA(T,Tmin,alpha,numIterations, fstop, p);

/**    Call the SA algorithm which returns the solution state of Sudoku **/
    state sol = SA.run(&Board);
/**    Print the solution & fitness value **/
    sol.printState();
    std::cout<<sol.fitness();

   return 0;
}
