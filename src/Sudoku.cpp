#include "Sudoku.h"

Sudoku::Sudoku(int a[N][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      mat[i][j] = a[i][j];
      if (mat[i][j] == -1)
        fix[i][j] = 0;
      else
        fix[i][j] = 1;
    }
  }
}
// check in the box for existence
bool Sudoku::unUsedInBox(int rowStart, int colStart, int num)
{
  for (int i = 0; i < SRN; i++)
    for (int j = 0; j < SRN; j++)
      if (mat[rowStart + i][colStart + j] == num)
        return false;
  return true;
}

// check in the row for existence
bool Sudoku::unUsedInRow(int i, int num)
{
  for (int j = 0; j < N; j++)
    if (mat[i][j] == num)
      return false;
  return true;
}

// check in the column for existence
bool Sudoku::unUsedInCol(int j, int num)
{
  for (int i = 0; i < N; i++)
    if (mat[i][j] == num)
      return false;
  return true;
}

// check if num is safe to put at (i,j)
bool Sudoku::CheckIfSafe(int i, int j, int num)
{
  return (unUsedInRow(i, num) &&
          unUsedInCol(j, num) &&
          unUsedInBox(i - i % SRN, j - j % SRN, num));
}

void Sudoku::printSudoku()
{
  cout << "Printing sudoku matrix ------- \n";
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << mat[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}
int Sudoku::randomGenerator(int num)
{
  return (int)floor((rand() % (num)));
}

void Sudoku::init_solution()
{
  //        """Generate a random solution from a Sudoku problem
  //        """
  int num;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (mat[i][j] == -1)
      {
        do
        {
          num = randomGenerator(N);
        } while (!unUsedInBox(i - i % SRN, j - j % SRN, num));

        mat[i][j] = num;
      }
    }
  }
}
