#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H
#include<iostream>
#include<math.h>
#include<stack>
#include "Sudoku.h"
#include "Utils.h"
using namespace std;

class SudokuGenerator
{
  private:
    static bool** empty2DBool(int inputSize);
    static int** empty2DInt(int inputSize);

  public:
    static Sudoku generateNoGuarantee(int inputSize, int numberOfSquaresFilled);
    static Sudoku generateGuarantee(int inputSize, int numberOfSquaresFilled);
};
#endif
