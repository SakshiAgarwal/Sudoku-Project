#include "Utils.h"

string Utils::GENES = "012345678"; //9abcdefghijklmno";    // Valid Genes

int Utils::randomGenerator(int num)
{
    return (int) floor((rand()%(num)));
}
int Utils::random_num(int start, int end)
{
  int range = (end-start)+1;
  int random_int = start+(rand()%range);
  return random_int;
}
char Utils::mutated_genes()
{
  int len = GENES.size();
  int r = random_num(0, len-1);
  return GENES[r];
}