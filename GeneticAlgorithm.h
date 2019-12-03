//#include <bits/stdc++.h>
//#include "Sudoku.h"
using namespace std;

const static int SRN = 3;
const static int N = 9;
// Valid Genes
const string GENES = "012345678";//9abcdefghijklmno";

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = GENES.size();
    int r = random_num(0, len-1);
    //std::cout<<"Mutating gene:"<<r<<"\n";
    return GENES[r];
}

// create chromosome or string of genes
int **create_gnome(int mat[N][N])
{
    //int len = TARGET.size();
    int** gnome=0;
    gnome = new int*[N];
    for(int i=0; i<N; i++)
    {
      gnome[i] = new int[N];
      for(int j=0; j<N; j++)
        if(mat[i][j] != -1)
            gnome[i][j] = mat[i][j];
        else
            gnome[i][j] = mutated_genes()-'0';
    }
    return gnome;
}

class GeneticAlgorithm;
// Class representing individual in population
class Individual
{
    // const static int N = 9;
    // const static int SRN = 3;
public:
    int chromosome[N][N];
    int fitness;
    Individual(int** chromosome);
    int** mate(Individual parent2, int fixed_val[N][N], float mutation);
    int cal_fitness();
    bool unUsedInBox(int rowStart, int colStart, int num, int i, int j);
    bool unUsedInRow(int i,int num, int j);
    bool unUsedInCol(int j,int num, int i);
    bool CheckIfSafe(int i,int j,int num);
    void printSudoku();
};

Individual::Individual(int** chromosome)
{
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        this->chromosome[i][j] = chromosome[i][j];
    fitness = cal_fitness();
};

// Perform mating and produce new offspring
int** Individual::mate(Individual par2, int fixed_val[N][N], float mutation)
{
    // chromosome for offspring
    int** child_chromosome=0;
    child_chromosome = new int*[N];
    for(int i=0; i<N; i++)
    {
      child_chromosome[i] = new int[N];
    }
    //int len = chromosome.size();
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
      {
          // random probability
          float p = random_num(0, 100)/100;

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
              child_chromosome[i][j] = mutated_genes()-'0';

      }

    // create new Individual(offspring) using
    // generated chromosome for offspring
    return child_chromosome;
}


// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness()
{
    //int len = TARGET.size();
    int fitness = 0;
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
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
}

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

// check in the box for existence
bool Individual::unUsedInBox(int rowStart, int colStart, int num, int x, int y)
{
    for (int i = 0; i<SRN; i++)
      for (int j = 0; j<SRN; j++)
        if(i != x%SRN || j != y%SRN)
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
    for (int j = 0; j<N; j++)
      if(j != y)
        if (this->chromosome[i][j] == num)
            return false;
    return true;
}

// check in the column for existence
bool Individual::unUsedInCol(int j,int num, int x)
{
    for (int i = 0; i<N; i++)
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
            unUsedInBox(i-i%SRN, j-j%SRN, num, i, j));
}

void Individual::printSudoku()
{
    std::cout<<"Printing sudoku matrix ------- \n";
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
            std::cout<<this->chromosome[i][j]<<" ";
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

class GeneticAlgorithm
{
  // const static int N = 9;
  // const static int SRN = 3;
public:
  int fixed_val[N][N];
  int mat[N][N];

  GeneticAlgorithm(int mat[N][N])
  {
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
      {
        if(mat[i][j]!=-1)
          this->fixed_val[i][j] = 1;

        this->mat[i][j] = mat[i][j];
      }
  }

  void compute(int population_size, int elitism, int eligible, float mutation, int stop)
  {
        srand((unsigned)(time(0)));

         // current generation
         int generation = 0;
         int f=0;

         vector<Individual> population;
         bool found = false;

         // create initial population
         for(int i = 0;i<population_size;i++)
         {
             //std::cout<<"Creating initial population:"<<i<<"\n";
             int **gnome = create_gnome(mat);
             population.push_back(Individual(gnome));
	     
    	     for(int i=0; i<N; i++)
    	     {
      	         delete[] gnome[i];
    	     }
	     delete[] gnome;
             population[i].printSudoku();
             cout<< "Fitness: "<< population[i].fitness << "\n";
         }
         //std::cout<<"Population 0:\n";
         //population[0].printSudoku();
         //found = true;
         while(! found)
         {
             // sort the population in increasing order of fitness score
             sort(population.begin(), population.end());
             //std::cout<<"Population 0 after sort:\n";
             //population[0].printSudoku();
             // if the individual having lowest fitness score ie.
             // 0 then we know that we have reached to the target
             // and break the loop
             if(population[0].fitness <= 0)
             {
                 found = true;
                 break;
             }

             // Otherwise generate new offsprings for new generation
             vector<Individual> new_generation;

             // Perform Elitism, that mean 10% of fittest population
             // goes to the next generation
             int s = (elitism*population_size)/100;
	     //cout<<s<<"\n";
             for(int i = 0;i<s;i++){
                 //std::cout<<"New gen elite:\n";
                 new_generation.push_back(population[i]);
             }
             //std::cout<<"New gen population 0 before cross:\n";
             //new_generation[0].printSudoku();
             if(new_generation[0].fitness!=f || generation%250000 == 0){
                 f=new_generation[0].fitness;
                 cout<< "Generation: " << generation << "\t\t";
                 cout<< "Fitness: "<< new_generation[0].fitness << "\n";
             }
             //cout<< "Fitness: "<< new_generation[0].fitness << "\n";

             // From 50% of fittest population, Individuals
             // will mate to produce offspring
             //s = ((100-elitism)*population_size)/100;
	           s = population_size - s;
	           //cout<<s<<"\n";
             for(int i = 0;i<s;i++)
             {
                 //cout<< "Crossing: ";
                 int len = population.size();
                 int r = random_num(0, eligible*population_size/100), s=r;
                 //cout<< "parent "<< r<<" with ";
                 Individual parent1 = population[r];
                 while(s == r) s = random_num(0, eligible*population_size/100);
                 //cout<< "parent "<< s<<"\n";
                 Individual parent2 = population[s];
		 int **mate = parent1.mate(parent2, fixed_val, mutation);
                 Individual offspring = Individual(mate);

    		 for(int i = 0; i < N; i++) {
        	     delete[] mate[i];   
    		 }
    		 delete[] mate; 
                 new_generation.push_back(offspring);
             }

             for(int i = 0;i<population_size;i++)
             {
                population.pop_back();
             }
             population = new_generation;
             // cout<< "Generation: " << generation << "\n";
             // //cout<< "String: "<< population[0].chromosome <<"\t";
             // population[0].printSudoku();
             // population[1].printSudoku();
             // population[2].printSudoku();
             // population[3].printSudoku();
             // population[4].printSudoku();
             // population[5].printSudoku();
             // population[6].printSudoku();
             // population[7].printSudoku();
             // population[8].printSudoku();
             // population[9].printSudoku();
             // cout<< "Fitness: "<< population[0].fitness << "\n";
             // cout<< "Fitness: "<< population[1].fitness << "\n";
             // cout<< "Fitness: "<< population[2].fitness << "\n";
             // cout<< "Fitness: "<< population[3].fitness << "\n";
             // cout<< "Fitness: "<< population[4].fitness << "\n";
             // cout<< "Fitness: "<< population[5].fitness << "\n";
             // cout<< "Fitness: "<< population[6].fitness << "\n";
             // cout<< "Fitness: "<< population[7].fitness << "\n";
             // cout<< "Fitness: "<< population[8].fitness << "\n";
             // cout<< "Fitness: "<< population[9].fitness << "\n";

             generation++;
             if(stop != 0)
              if(generation > stop)
                break;
          }
          cout<< "Generation: " << generation-1 << "\t";
          //cout<< "String: "<< population[0].chromosome <<"\t";
          population[0].printSudoku();
          cout<< "Fitness: "<< population[0].fitness << "\n";

         for(int i = 0;i<population_size;i++)
         {
	     population.pop_back();
	 }
  }
};
