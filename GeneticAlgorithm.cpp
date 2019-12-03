#include <memory>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include "GeneticAlgorithm.h"

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
    // int mat[9][9] =
    //         {
    //             {0, 2, 7, 8, 2, 6, 5, 4, 1},
    //             {2, 0, 7, 7, 3, 8, 7, 2, 6},
    //             {6, 3, 1, 4, 2, 7, 6, 7, 3},
    //             {4, 7, 7, 8, 6, 2, 1, 4, 3},
    //             {5, 7, 5, 3, 8, 1, 6, 1, 4},
    //             {8, 6, 3, 7, 4, 8, 3, 0, 8},
    //             {7, 0, 6, 6, 7, 6, 0, 3, 8},
    //             {2, 3, 6, 5, 6, 7, 7, 6, 3},
    //             {7, 1, 5, 0, 2, 6, 3, 4, 0}
    //         };

/**Create the sudoku board with matrix **/
    GeneticAlgorithm Board(mat);

/**    Parameters for Genetic algorithm **/
    int population_size=10; //size of Gene pool
    int stop=0; //number of generations to run until forced to stop; to go until completion set to 0
    //!!!PLEASE use steps of 10% when adjusting the parameters below to avoid segmentation faults!!!
    int elitism=10; //best percentage of candidates go to new gen unchanged; elitism=10 -> best 10%
    int eligible=50; //best percentage of candidates get to mate for new gen; eligible=50 -> best 50%
    float mutation=0.04; //chance of random gene for offspring instead of parents'; mutation=0.1 -> 10% chance

    Board.compute(population_size, elitism, eligible, mutation, stop);


   return 0;
}
