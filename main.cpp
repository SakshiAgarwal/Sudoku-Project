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

#define MAX_EMPTY_CELLS 160
#define ITERATION_PER_DIFFICULTY 100

void testGeneticAlgorithm()
{
  // Parameters for Genetic algorithm
  int population_size=10; //size of Gene pool
  int stop=0; //number of generations to run until forced to stop; to go until completion set to 0
  //!!!PLEASE use steps of 10% when adjusting the parameters below to avoid segmentation faults!!!
  int elitism=10; //best percentage of candidates go to new gen unchanged; elitism=10 -> best 10%
  int eligible=50; //best percentage of candidates get to mate for new gen; eligible=50 -> best 50%
  float mutation=0.4; //chance of random gene for offspring instead of parents'; mutation=0.1 -> 10% chance
  
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


  for(int num_empty = 0; num_empty < MAX_EMPTY_CELLS; num_empty += 10)
  {
    Logger bullshit;
    bullshit.open("./logs/genetic_algorithm_"+to_string(num_empty)+".txt");
    for(int j = 0; j < ITERATION_PER_DIFFICULTY; j++)
    {
      Sudoku a = SudokuGenerator::generateGuarantee(16, 1, num_empty);
      // MUST FIX THIS MAT THING
      GeneticAlgorithm b(mat);
      
      bool result = b.compute(population_size, elitism, eligible, mutation, stop);
      cout << j << " : " << result << " , " << b.generation<< endl;
      vector<double> shit;
      shit.push_back(j);
      shit.push_back(result);
      shit.push_back(b.generation);
      bullshit.log(shit);
      a.destroy();
    }
    bullshit.close();
  }
}

void testSimulatedAnnealing()
{
  for(int num_empty = 0; num_empty < MAX_EMPTY_CELLS; num_empty += 10)
  {
    Logger bullshit;
    bullshit.open("./logs/local_search_"+to_string(num_empty)+".txt");
    for(int j = 0; j < ITERATION_PER_DIFFICULTY; j++)
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
  clock_t omg;
  for(int num_empty = 160; num_empty < MAX_EMPTY_CELLS; num_empty += 10)
  {
    Logger bullshit;
    bullshit.open_append("./logs/backtrack_"+to_string(num_empty)+".txt");
    for(int j = 0; j < ITERATION_PER_DIFFICULTY; j++)
    {
      Sudoku a = SudokuGenerator::generateGuarantee(16, 1, num_empty);
      omg = clock();
      int result = Backtrack::run(a.size, a.board);
      float goddamn = (float)(clock() - omg) / CLOCKS_PER_SEC;
      cout << j << " : " << result << " , " << Backtrack::backtracks<< " , " << goddamn<< endl;
      vector<double> shit;
      shit.push_back(j);
      shit.push_back(result);
      shit.push_back(Backtrack::backtracks);
      shit.push_back(goddamn);
      bullshit.log(shit);
      a.destroy();
    }
    bullshit.close();
  }
}

int main()
{
  //Sudoku::test();
  //testGeneticAlgorithm();
  testSimulatedAnnealing();
  //testBacktrack();
  return 0;
}







