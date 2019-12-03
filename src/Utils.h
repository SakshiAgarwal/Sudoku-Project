#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <random>
#include <string>
using namespace std;

class Utils
{
  public:
    static string GENES;
    const static int SRN = 3;
    const static int N = 9;
    static int randomGenerator(int num);
    static int random_num(int start, int end);
    static char mutated_genes();
};
#endif