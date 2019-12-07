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
/*
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
*/

int Utils::fitness(Sudoku s)
{
  int errors = 0;
  int boardSize = s.size;
  int sqrtSize = sqrt(boardSize);
  // check columns and rows
  for(int fixed_index = 0; fixed_index < boardSize; fixed_index++)
  {
    // helper vals for boxCount
    int base_i = (fixed_index * sqrtSize) % boardSize;
    int base_j = ((int)(fixed_index * sqrtSize) / boardSize) * sqrtSize;

    int* colCount = new int[boardSize];
    int* rowCount = new int[boardSize];
    int* boxCount = new int[boardSize];
    // initialize
    for(int k = 0; k < boardSize; k++)
    {
      colCount[k] = 0;
      rowCount[k] = 0;
      boxCount[k] = 0;
    }
    // count
    for(int moving_index = 0; moving_index < boardSize; moving_index++)
    {
      int colVal = s.board[moving_index][fixed_index];
      int rowVal = s.board[fixed_index][moving_index];
      int boxVal = s.board[base_i + (moving_index % sqrtSize)][base_j + (int)(moving_index / sqrtSize)];
      if(colVal == -1)
        errors += 1;
      else 
        colCount[colVal] += 1;
      if(rowVal == -1) 
        errors += 1;
      else 
        rowCount[rowVal] += 1;
      if(boxVal == -1) 
        errors += 1;
      else 
        boxCount[boxVal] += 1;
    }
    // evaluate counts
    for(int val = 0; val < boardSize; val++)
    {
      errors += 4 * max(0, colCount[val] - 1);
      errors += 4 * max(0, rowCount[val] - 1);
      errors += 4 * max(0, boxCount[val] - 1);
    }
  } 
  return errors;
}
