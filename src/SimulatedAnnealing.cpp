#include "SimulatedAnnealing.h"
SimulatedAnnealing::SimulatedAnnealing(double T, double Tmin, double a, int num,int fstop, double p) {
  this->T = T;
  this->Tmin = Tmin;
  this->alpha = a;
  this->numIterations = num;
  this->f = fstop;
  this->p = p;
}

State SimulatedAnnealing::run(Sudoku *Board) {

  Board->init_solution();
  Board->printSudoku();

  State currState(Board->mat,Board->fix);
  currState.printState();

  State best = currState;
  while (T > Tmin) 
  {
    for (int i = 0; i < numIterations; i++) 
    {
      cout <<"Iteration for T = "<<T<<"-----"<<i<< endl;

      State next = currState.neighbour();
      //std::cout <<"Printing next state "<< std::endl;
      //next.printState();

      int e = currState.fitness() ;
      //std::cout <<"current fitness value received  "<< std::endl;

      int ep = next.fitness();
      cout <<"fitness current ---- "<<e << endl;
      cout <<"fitness next  ---- "<<ep << endl;

      double threshold = ep < e ? 1.0 : exp(-1.0 * (ep-e) / T);

      cout <<"threshold value ---- "<<threshold << endl;

      if (threshold > p)
          currState = next;

      cout <<"Fitness value ------"<<currState.fitness() << endl;

      if (currState.fitness() <= f)
          return currState;

      // Check if we are the best seen so far, and if so, copy.
      if (best.fitness() < currState.fitness()) {
          best = currState;
          cout << "Best: " << best.fitness() << '\n';
      }
    }
    T *= alpha; // Decreases T, cooling phase
  }
  return best;
}