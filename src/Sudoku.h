#ifndef SUDOKU_H
#define SUDOKU_H
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include<math.h>
using namespace std;

class Sudoku
{
  private:
    static string output_folder;
    static char file_names[8][27];

  public:
    int** board;
    int size;

    // constructors
    Sudoku();
    Sudoku(int size);
    Sudoku(string file_name);
    Sudoku(int input_size, int** input_board);
    Sudoku copy();
    void destroy();

    // bool functions
    bool validInCol(int j, int val);
    bool validInRow(int i, int val);
    bool validInBlock(int i, int j, int val);
    bool valid(int i, int j, int val);

    // IO Functions
    int** getBoardCopy();
    void print();
    void save(string output_name);
    static Sudoku benchmarkBoard(int index);

    static void test();
};
#endif
