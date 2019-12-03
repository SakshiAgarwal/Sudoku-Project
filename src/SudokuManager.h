#ifndef SUDOKUMANAGER_H
#define SUDOKUMANAGER_H
#include<iostream>
#include <fstream>
#include <string>

#include <vector>
#include <sstream>
#include <regex>

#include <cmath>
#include <ctime>
using namespace std;

class SudokuManager 
{
  private: 
    int** board;
    int size;
    bool isValidAssignment(int i, int j, int val);
    bool isValidCol(int j, int val);
    bool isValidRow(int i, int val);
    bool isValidBlock(int i, int j, int val);
    static int getRand(int max);
    static char file_names[8][27];
    static string output_folder;
    
  public:
    SudokuManager();
    SudokuManager(int size);
    SudokuManager(string file_name);
    SudokuManager(int input_size, int** input_board);
    int** getBoard();
    void print();
    void save(string output_name);
    static SudokuManager benchmarkBoard(int index);
    static SudokuManager generateBoard(int size, int difficulty);
    static void seed();
};
#endif