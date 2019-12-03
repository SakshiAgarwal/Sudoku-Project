#include "Individual.h"

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
  return ind1.fitness < ind2.fitness;
}

Individual::Individual(int** chromosome)
{
  for(int i=0; i<Utils::N; i++)
    for(int j=0; j<Utils::N; j++)
      this->chromosome[i][j] = chromosome[i][j];
  fitness = cal_fitness();
};

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2, int fixed_val[Utils::N][Utils::N], float mutation)
{
  // chromosome for offspring
  int** child_chromosome=0;
  child_chromosome = new int*[Utils::N];
  for(int i=0; i<Utils::N; i++)
  {
    child_chromosome[i] = new int[Utils::N];
  }
  //int len = chromosome.size();
  for(int i=0; i<Utils::N; i++)
  {
    for(int j=0; j<Utils::N; j++)
    {
      // random probability
      float p = Utils::random_num(0, 100)/100;

      // if prob is less than 0.45, insert gene
      // from parent 1
      if(p < (1-mutation)/2){
        //std::cout<<"Taking first parent's gene:"<<i<<" "<<j<<"\n";
        child_chromosome[i][j] = chromosome[i][j];
      }
      // if prob is between 0.45 and 0.90, insert
      // gene from parent 2
      else if(p < (1-mutation)){
        //std::cout<<"Taking second parent's gene:"<<i<<" "<<j<<"\n";
        child_chromosome[i][j] = par2.chromosome[i][j];
      }
      // otherwise insert random gene(mutate),
      // for maintaining diversity
      else if(fixed_val[i][j] == 1){
        //std::cout<<"Fixed gene:"<<i<<" "<<j<<"\n";
        child_chromosome[i][j] = chromosome[i][j];
      }
      else
        child_chromosome[i][j] = Utils::mutated_genes()-'0';
    }
  }
  // create new Individual(offspring) using
  // generated chromosome for offspring
  return Individual(child_chromosome);
};


// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness()
{
  //int len = TARGET.size();
  int fitness = 0;
  for(int i=0; i<Utils::N; i++)
    for(int j=0; j<Utils::N; j++)
    {
      // if(i == 0 && j == 6)
      // {
      //   std::cout<<"chromosome["<<i<<"]["<<j<<"]: "<<chromosome[i][j]<<" is safe?: "<<CheckIfSafe(i, j, chromosome[i][j])<<"\n";
      //   std::cout<<"unUsedInRow: "<<unUsedInRow(i, chromosome[i][j], j)<<"\n";
      //   std::cout<<"unUsedInCol: "<<unUsedInCol(j, chromosome[i][j], i)<<"\n";
      //   std::cout<<"unUsedInBox: "<<unUsedInBox(i-i%SRN, j-j%SRN, chromosome[i][j], i, j)<<"\n";
      // }
      if(!CheckIfSafe(i, j, chromosome[i][j]))
          fitness++;
    }
  return fitness;
};

// check in the box for existence
bool Individual::unUsedInBox(int rowStart, int colStart, int num, int x, int y)
{
  for (int i = 0; i<Utils::SRN; i++)
    for (int j = 0; j<Utils::SRN; j++)
      if(i != x%Utils::SRN || j != y%Utils::SRN)
      {
        //std::cout<<"unUsedInBox value: "<<this->chromosome[rowStart+i][colStart+j]<<" ("<<i<<","<<j<<")"<<"\n";
        if (this->chromosome[rowStart+i][colStart+j]==num)
          return false;
      }

  return true;
}

// check in the row for existence
bool Individual::unUsedInRow(int i,int num, int y)
{
  for (int j = 0; j<Utils::N; j++)
    if(j != y)
      if (this->chromosome[i][j] == num)
        return false;
  return true;
}

// check in the column for existence
bool Individual::unUsedInCol(int j,int num, int x)
{
  for (int i = 0; i<Utils::N; i++)
    if(i != x)
      if (this->chromosome[i][j] == num)
        return false;
  return true;
}

// check if num is safe to put at (i,j)
bool Individual::CheckIfSafe(int i,int j,int num)
{
  //std::cout<<"CheckIfSafe num value: "<<num<<"\n";
  return (unUsedInRow(i, num, j) &&
          unUsedInCol(j, num, i) &&
          unUsedInBox(i-i%Utils::SRN, j-j%Utils::SRN, num, i, j));
}

void Individual::printSudoku()
{
  cout<<"Printing sudoku matrix ------- \n";
  for (int i = 0; i<Utils::N; i++)
  {
    for (int j = 0; j<Utils::N; j++)
      cout<<this->chromosome[i][j]<<" ";
    cout<<"\n";
  }
  cout<<"\n";
}
