#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Sudoku inputSudoku)
{
  double inputT = 20;
  double inputTmin = 0.001;
  double inputAlpha = 0.9;
  int inputNum = 500;
  int inputFstop = 0;
  double inputP = 0.6;
  *this = SimulatedAnnealing(inputT, inputTmin, inputAlpha, inputNum, inputFstop, inputP, inputSudoku);
}
SimulatedAnnealing::SimulatedAnnealing(double inputT, double inputTmin, double inputAlpha, int inputNum, int inputFstop, double inputP, Sudoku inputSudoku)
{
  T = inputT;
  Tmin = inputTmin;
  alpha = inputAlpha;
  numIterations = inputNum;
  fStop = inputFstop;
  p = inputP;
  current = inputSudoku.copy();
  
  int size = current.size;
  int sqrtSize = (int)sqrt(size);
  fixed = new bool *[size];
  // Init canChagne matrix and fill the board
  for (int i = 0; i < size; i++)
  {
    fixed[i] = new bool[size];
    for (int j = 0; j < size; j++)
    {
      if (current.board[i][j] == -1)
      {
        fixed[i][j] = false;
        // Assign a random value
        int num = -1; //temporary
        do
        {
          num = Utils::randomGenerator(size);
        } while (!current.validInBlock(i, j, num));
        current.board[i][j] = num;
      }
      else
      {
        fixed[i][j] = true;
      }
    }
  }
}
Sudoku SimulatedAnnealing::getNeighbor()
{
  int i, j, k1, k2, k3, k4;
  Sudoku neighbor = current.copy();
  int size = current.size;
  int sqrtSize = (int)sqrt(size);

  i = Utils::randomGenerator(size);
  j = Utils::randomGenerator(size);
  do
  {
    k1 = i - i % sqrtSize + Utils::randomGenerator(sqrtSize);
    k2 = j - j % sqrtSize + Utils::randomGenerator(sqrtSize);

    k3 = i - i % sqrtSize + Utils::randomGenerator(sqrtSize);
    k4 = j - j % sqrtSize + Utils::randomGenerator(sqrtSize);
  } while (fixed[k1][k2] || fixed[k3][k4]);

  neighbor.board[k1][k2] = current.board[k3][k4];
  neighbor.board[k3][k4] = current.board[k1][k2];
  return neighbor;
}
void SimulatedAnnealing::printCurrentBoard()
{
  current.print();
}
bool SimulatedAnnealing::run()
{
  int currentFitnessScore = Utils::fitness(current);
  double currTemperature = T;

  while (currTemperature > Tmin)
  {
    for (int i = 0; i < numIterations; i++)
    {
      Sudoku neighbor = getNeighbor();
      int neighborsFitnessScore = Utils::fitness(neighbor);
      double threshold = neighborsFitnessScore < currentFitnessScore ? 1.0 : exp(-1.0 * (neighborsFitnessScore - currentFitnessScore) / currTemperature);

      if (threshold > p)
      {
        current = neighbor;
        currentFitnessScore = neighborsFitnessScore;
        cout<<"currT: "<<currTemperature<<"/"<<T<<"\tI: "<<i<<"/"<<numIterations<<"\tNew Fit: "<<currentFitnessScore<<"\tThresh: "<<threshold<<endl;
      }
      if (currentFitnessScore <= fStop)
      {
        cout<<"Stopped because currentFitnessScore <= fstop : fstop = "<<fStop<<endl;
        return true;
      }
    }
    currTemperature = currTemperature * alpha; // Decreases T, cooling phase
  }
  cout<<"Stopped because Temperature"<<endl;
  return false;
}