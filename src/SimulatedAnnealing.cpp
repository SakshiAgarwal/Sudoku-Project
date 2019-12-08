#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Sudoku inputSudoku)
{
  // default
  double inputT = 20;
  double inputTmin = 0.001;
  double inputAlpha = 0.9;
  int inputNum = 500;
  double inputP = 0.6;
  *this = SimulatedAnnealing(inputT, inputTmin, inputAlpha, inputNum, inputP, inputSudoku);
}
SimulatedAnnealing::SimulatedAnnealing(double inputT, double inputTmin, double inputAlpha, int inputNeighbors, double inputP, Sudoku inputSudoku)
{
  T = inputT;
  Tmin = inputTmin;
  alpha = inputAlpha;
  num_neighbors = inputNeighbors;
  p = inputP;
  solution = inputSudoku.copy();
  total_iteration = 0;
  
  int size = solution.size;
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
      int val = solution.board[i][j];
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
        solution.board[i][j] = val;
      }
      val += 1;
    }
  }
  delete countMissing;
}
Sudoku SimulatedAnnealing::getNeighbor()
{
  Sudoku neighbor = solution.copy();
  int size = solution.size;
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

  neighbor.board[i1][j1] = solution.board[i2][j2];
  neighbor.board[i2][j2] = solution.board[i1][j1];
  return neighbor;
}
void SimulatedAnnealing::printCurrentBoard()
{
  solution.print();
}
bool SimulatedAnnealing::run()
{
  Logger iteration_logger;
  Logger temp_logger;
  if(LOG_SIMULATED_ANNEALING)
  {
    iteration_logger.open("./logs/iteration.txt");
    temp_logger.open("./logs/temperature.txt");
  }
  

  total_iteration = 0;
  if(Utils::fitness(solution) == 0)
  {
    return true;
  }
  double currTemperature = T;
  while (currTemperature > Tmin)
  {
    int best_neighbor_score = Utils::fitness(solution);
    Sudoku best_neighbor = solution.copy();
    for (int i = 0; i < num_neighbors; i++)
    {
      Sudoku neighbor = getNeighbor();
      int neighborsFitnessScore = Utils::fitness(neighbor);
      double threshold = neighborsFitnessScore < best_neighbor_score ? 1.0 : exp(-1.0 * (neighborsFitnessScore - best_neighbor_score) / currTemperature);
       
      if (threshold > p)
      {
        best_neighbor.destroy();
        best_neighbor = neighbor.copy();
        best_neighbor_score = neighborsFitnessScore;
        //cout<<"currT: "<<currTemperature<<"/"<<T<<"\tI: "<<i<<"/"<<num_neighbors<<"\tNew Fit: "<<best_neighbor_score<<"\tThresh: "<<threshold<<endl;
        if (best_neighbor_score == 0)
        {
          total_iteration += 1;
          
          if(LOG_SIMULATED_ANNEALING)
          {
            vector<double> shit;
            shit.push_back(total_iteration);
            shit.push_back(best_neighbor_score);
            vector<double> holy;
            holy.push_back(currTemperature);
            holy.push_back(best_neighbor_score);
            
            iteration_logger.log(shit);
            temp_logger.log(holy);
          }
          
          //cout<<"Solution Found "<<endl; 
          solution.destroy();
          solution = best_neighbor.copy();
          best_neighbor.destroy();
          return true;
        }
      } 
      neighbor.destroy();
    }
    
    if(LOG_SIMULATED_ANNEALING)
    {
      vector<double> shit;
      shit.push_back(total_iteration);
      shit.push_back(best_neighbor_score);
      vector<double> holy;
      holy.push_back(currTemperature);
      holy.push_back(best_neighbor_score);
      
      iteration_logger.log(shit);
      temp_logger.log(holy);
    }
    total_iteration += 1;
    solution.destroy();
    solution = best_neighbor.copy();
    best_neighbor.destroy();
    currTemperature = currTemperature * alpha; // Decreases T, cooling phase
  }
  //cout<<"Stopped because Temperature"<<endl;
  return false;
}
void SimulatedAnnealing::printMasked(int val)
{
  int size = solution.size;
  int divider = sqrt(size);
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      string temp = to_string(solution.board[i][j]);
      // Empty spaces are *
      if(solution.board[i][j] == -1 || solution.board[i][j] != val)
      {
        cout << " * ";
      } else if(temp.length() == 1)
      {
        cout << " " << solution.board[i][j] << " ";
      } else 
      {
        cout << solution.board[i][j] << " ";
      }
      // Column divider
      if(j % divider == divider - 1)
      {
        cout << "  ";
      }
    }
    cout << endl;
    // Row divider
    if(i % divider == divider - 1)
    {
      cout << endl;
    }
  }

}