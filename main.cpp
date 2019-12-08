#include<iostream>
#include <ctime>
#include "src/Utils.h"
#include "src/Logger.h"
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
  int population_size=10; //size of Gene pool
  int stop=0; //number of generations to run until forced to stop; to go until completion set to 0
  //!!!PLEASE use steps of 10% when adjusting the parameters below to avoid segmentation faults!!!
  int elitism=10; //best percentage of candidates go to new gen unchanged; elitism=10 -> best 10%
  int eligible=50; //best percentage of candidates get to mate for new gen; eligible=50 -> best 50%
  float mutation=0.4; //chance of random gene for offspring instead of parents'; mutation=0.1 -> 10% chance

  Board.compute(population_size, elitism, eligible, mutation, stop);
}

void testSimulatedAnnealing()
{
  for(int num_empty = 120; num_empty < 140; num_empty += 10)
  {
    Logger bullshit;
    bullshit.open("./logs/"+to_string(num_empty)+".txt");
    for(int j = 0; j < 100; j++)
    {
      Sudoku a = SudokuGenerator::generateGuarantee(16, 1, num_empty);
      SimulatedAnnealing b = SimulatedAnnealing(a);
      b.alpha = 0.9995;
      b.T = 4;
      b.num_neighbors = 1000;
      b.Tmin = 2;
      bool result = b.run();
      cout << j << " : " << result << " , " << b.total_iteration<< endl;
      vector<double> shit;
      shit.push_back(j);
      shit.push_back(result);
      shit.push_back(b.total_iteration);
      bullshit.log(shit);
      a.destroy();
    }
    bullshit.close();
  }
}
void testBacktrack()
{
  Sudoku a = Sudoku("./boards/report_example.txt");
  a.print();
  int result = Backtrack::run(a.size, a.board);
  cout << "RESULT: " << result << endl;
  a.destroy();
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
  //Sudoku::test();
  //testGeneticAlgorithm(mat);
  testSimulatedAnnealing();
  //testBacktrack();
  return 0;
}