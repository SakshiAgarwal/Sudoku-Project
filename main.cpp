#include<iostream>
#include "src/Sudoku.h"
#include "src/SudokuGenerator.h"
#include "src/SimulatedAnnealing.h"
#include "src/GeneticAlgorithm.h"
#include "src/Backtrack.h"
using namespace std;

void testGeneticAlgorithm(int mat[9][9])
{
  GeneticAlgorithm Board(mat);

  // Parameters for Genetic algorithm
  int population_size=100; //size of Gene pool
  int stop=0; //number of generations to run until forced to stop; to go until completion set to 0
  //!!!PLEASE use steps of 10% when adjusting the parameters below to avoid segmentation faults!!!
  int elitism=10; //best percentage of candidates go to new gen unchanged; elitism=10 -> best 10%
  int eligible=50; //best percentage of candidates get to mate for new gen; eligible=50 -> best 50%
  float mutation=0.1; //chance of random gene for offspring instead of parents'; mutation=0.1 -> 10% chance

  Board.compute(population_size, elitism, eligible, mutation, stop);
}

void testSudoku()
{
  // Test all constructors
  Sudoku a = Sudoku();
  a.print();
  Sudoku b = Sudoku(9);
  b.print();
  Sudoku c = Sudoku("./boards/guaranteed_solution.txt");
  c.print();
  Sudoku d = Sudoku::benchmarkBoard(1);
  d.print();
  Sudoku e = Sudoku(16, d.board);
  e.print();

  // Checking copy
  Sudoku f = e.copy();
  f.print();
  e.board[0][0] = 10000;
  e.print();
  f.print();
  
  // Checking bool functions
  Sudoku g = Sudoku("./boards/test.txt");
  g.print();
  int val = 4;
  for(int i = 0; i < g.size; i++)
  {
    for(int j = 0; j < g.size; j++)
    {
      bool h = g.validInRow(i, val);
      bool k = g.validInCol(j, val);
      bool l = g.validInBlock(i, j, val);
      bool m = g.valid(i, j, val);
      cout<<"("<<m<<"="<<h<<k<<l<<") ";
    } 
    cout << endl;
  }
}
void testSimulatedAnnealing()
{
  //Sudoku a = Sudoku("./boards/test.txt");
  Sudoku a = Sudoku::benchmarkBoard(1); 
  SimulatedAnnealing b = SimulatedAnnealing(a);
  b.alpha = 0.9995;
  b.T = 4;
  b.Tmin = 2.0;
  b.printCurrentBoard();
  bool result = b.run();
  cout << "Simulated Annealing Result: "<< result << endl;
  b.printCurrentBoard();
}
void testBacktrack(int mat[9][9])
{
  //SudokuManager::seed();
  //SudokuManager b = SudokuManager::benchmarkBoard(6); // get the first benchmark board
  //SudokuManager b = SudokuManager("boards/guaranteed_solution2.txt");
  //Backtrack solver = Backtrack(16, b.getBoard());
  int result = Backtrack::run(mat);
  cout << "RESULT: " << result << endl;
}

int main()
{
  /*
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
    */
  //testSudoku();
  //testGeneticAlgorithm(mat);
  testSimulatedAnnealing();
  //testBacktrack();
  return 0;
}