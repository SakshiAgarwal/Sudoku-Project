#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <random>
#include <string>
#include "Sudoku.h"
using namespace std;

class Utils
{
  public:
    static string GENES;
    const static int SRN = 3;
    const static int N = 9;
    static void seed();
    static int randomGenerator(int num);
    static int random_num(int start, int end);
    static char mutated_genes();
    static int fitness(Sudoku s);
};
#endif