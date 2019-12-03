#include<iostream>
#include "src/SudokuManager.h"
#include "src/SimulatedAnnealing.h"
#include "src/GeneticAlgorithm.h"
#include "src/Backtrack.h"

#include <map>

using namespace std;

void testSudokuManager()
{
  SudokuManager::seed();
  SudokuManager a = SudokuManager::generateBoard(3, 50); // 9x9 board with 50 squares filled in
  a.print();
  a.save("output.txt");
  a.save("shiity.txt");

  SudokuManager b = SudokuManager::benchmarkBoard(1); // get the first benchmark board
  b.print();
  a.save("fuck.txt");
}

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

void testSimulatedAnnealing(int mat[9][9])
{
  Sudoku Board(mat);

  int T=20;
  double Tmin = 0.001;
  double alpha = 0.9;
  int numIterations = 500;
  double fstop = 0;
  double p = 0.6;
  SimulatedAnnealing SA(T,Tmin,alpha,numIterations, fstop, p);
  State sol = SA.run(&Board);
  sol.printState();
  std::cout<<sol.fitness();
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
  //testSudokuManager();
  testGeneticAlgorithm(mat);
  //testSimulatedAnnealing(mat);
  //testBacktrack();
  return 0;
}