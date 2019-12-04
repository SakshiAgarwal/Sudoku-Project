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

  // init an array of numbers missing
  int* countMissing = new int[size];
  for (int i = 0; i < size; i++)
  {
    countMissing[i] = size;
  }
  
  // Init canChagne matrix and gather countMissing data
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int val = current.board[i][j];
      if(val == -1)
      {
        freePoints.push_back(pair<int, int>(i,j));
      } else {
        countMissing[val] -= 1;
      }
    }
  }

  // fill the board
  for(int k = 0; k < freePoints.size(); k++)
  {
    pair<int, int> p = freePoints[k];
    int i = p.first;
    int j = p.second;

    // find a value we can fill the space with
    bool notFilled = true;
    int val = 0;
    while(notFilled)
    {
      if(countMissing[val] > 0)
      {
        notFilled = false;
        countMissing[val] -= 1;
        current.board[i][j] = val;
      }
      val += 1;
    }
  }
}
Sudoku SimulatedAnnealing::getNeighbor()
{
  Sudoku neighbor = current.copy();
  int size = current.size;
  int sqrtSize = (int)sqrt(size);

  int index_1 = Utils::randomGenerator(freePoints.size());
  int index_2 = Utils::randomGenerator(freePoints.size());
  while(index_1 == index_2)
  {
    index_2 = Utils::randomGenerator(freePoints.size());
  }
  pair<int, int> p1 = freePoints[index_1];
  pair<int, int> p2 = freePoints[index_2];
  int i1 = p1.first;
  int j1 = p1.second;
  int i2 = p2.first;
  int j2 = p2.second;

  neighbor.board[i1][j1] = current.board[i2][j2];
  neighbor.board[i2][j2] = current.board[i1][j1];
  return neighbor;
}
void SimulatedAnnealing::printCurrentBoard()
{
  current.print();
}
bool SimulatedAnnealing::run()
{
  int currentFitnessScore = Utils::fitness(current);
  if(currentFitnessScore == 0)
  {
    return true;
  }
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