#include "Utils.h"

string Utils::GENES = "012345678"; //9abcdefghijklmno";    // Valid Genes

void Utils::seed()
{
  srand(time(nullptr));
}
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
int Utils::fitness(Sudoku s)
{
  int size = s.size;
  int count = 0,cost;
  bool flag;
  int i,j;
  for(int k=0;k<size;k++)
  {
    for (i=0;i<size;i++)
    {
      flag = false;
      cost =0;
      for (j = 0; j < size; j++)
      {
        if (s.board[i][j] == k)
        {
          flag = true;
          cost++;
        }
      }

      if(flag == false)
      {
        cost++;
      }
      else
      {
        cost--;
      }
      count = cost + count;
    }
  }

  cost = 0;
  for(int k=0;k<size;k++) 
  {
    for (i=0;i<size;i++) 
    {
      flag = false;
      cost=0;
      for (j = 0; j < size; j++) 
      {
        if (s.board[j][i] == k) 
        {
          flag = true;
          cost++;
        }
      }
      if(flag == false)
      {
        cost++;
      }
      else
      {
        cost--;
      }
      count = cost + count;
    }
  }
  return count;
}