//#include <bits/stdc++.h>
//#include "Sudoku.h"
using namespace std;

const static int SRN = 4;
const static int N = 16;
// Valid Genes
//const string GENES = "012345678";//9abcdefghijklmno";

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes(int* GENES)
{
    //int len = GENES.size();
    int r = random_num(0, N-1);
    //std::cout<<"Mutating gene:"<<r<<"\n";
    return GENES[r];
}

// //check box when generating values
bool inBox(int** gnome, int rowStart, int colStart, int num, int x, int y)
{
  //std::cout<<"colStart: "<<colStart<<"\n";
  //std::cout<<"rowStart: "<<rowStart<<"\n";
  for (int i = 0; i<SRN; i++)
    for (int j = 0; j<SRN; j++){
      // std::cout<<"Here?";
      if(i != x%SRN || j != y%SRN){
        //std::cout<< "Before if("<<i<<")("<<j<<"):\n";
        //std::cout<< "gnome[i][j]: "<<gnome[rowStart+i][colStart+j]<<"\n";
        if (gnome[rowStart+i][colStart+j]==num){
          //std::cout<< "If:\n";
          return false;
        }
      }
    }
  return true;
}

// create chromosome or string of genes
int **create_gnome(int mat[N][N], int* GENES)
{
    //int len = TARGET.size();
    int** gnome=0;
    gnome = new int*[N];
    for(int i=0; i<N; i++)
    {
      gnome[i] = new int[N];
      for(int j=0; j<N; j++)
      {
        if(mat[i][j] != -1)
            gnome[i][j] = mat[i][j];
        else
            gnome[i][j]=-1;
      }
    }
    for(int i=0; i<N; i++)
    {
      for(int j=0; j<N; j++)
      {
        if(mat[i][j] == -1)
          do{
             gnome[i][j] = mutated_genes(GENES);
             //std::cout<< "In box: ("<<i<<")("<<j<<")"<<gnome[i][j]<<"\n";
          }while (!inBox(gnome, i-i%SRN, j - j%SRN, gnome[i][j], i, j));
      }
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
    int** mate(Individual parent2, int fixed_val[N][N], float mutation, int* GENES);
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
int** Individual::mate(Individual par2, int fixed_val[N][N], float mutation, int* GENES)
{
    // chromosome for offspring
    int** child_chromosome=0;
    child_chromosome = new int*[N];
    for(int i=0; i<N; i++)
    {
      child_chromosome[i] = new int[N];
    }
    //int len = chromosome.size();

    // random probability
    int p = random_num(0, N); 	  //crossover point
    //float mg = random_num(0, N*N);	  //chosen gene for mutation
    float mc = random_num(0, 100)/100;    //mutation chance

    int x=(p/SRN)*SRN, y=(p%SRN)*SRN;

    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
      {
        if(i<x){
          child_chromosome[i][j] = chromosome[i][j];
        }else if(i<x+SRN && j<y){
          child_chromosome[i][j] = chromosome[i][j];
        }else{
          child_chromosome[i][j] = par2.chromosome[i][j];
        }
      }

  if(mc >= (1-mutation))
  {
    int p = random_num(0, N-1);
    bool done=false;
    int x=(p/SRN)*SRN, y=(p%SRN)*SRN, count=0;

    while(!done && count<100)
    {
      int mg1 = random_num(0, N-1);
      int mg2 = random_num(0, N-1);
      if(mg1 != mg2)
      {
        if(fixed_val[x+(mg1/SRN)][y+(mg1%SRN)]!=1 && fixed_val[x+(mg2/SRN)][y+(mg2%SRN)]!=1)
        {
          int aux = child_chromosome[x+(mg1/SRN)][y+(mg1%SRN)];
          child_chromosome[x+(mg1/SRN)][y+(mg1%SRN)] = child_chromosome[x+(mg2/SRN)][y+(mg2%SRN)];
          child_chromosome[x+(mg2/SRN)][y+(mg2%SRN)] = aux;
          done = true;
        }
        count++;
      }
    }

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

  void compute(int population_size, int elitism, int eligible, float mutation, int stop, int restarts, int restart_threshold)
  {
        srand((unsigned)(time(0)));
        //Fill in obvious values
        //init crossoff array
        bool crossoff[N][N][N];
        for(int k=0; k<N; k++)
          for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
            {
              crossoff[k][i][j] = true;
              if(mat[i][j]!=-1){
                crossoff[k][i][j]=false;
              }else{
                for(int l=0; l<N; l++)
                  if(mat[i][l]==k) crossoff[k][i][j]=false;
                for(int l=0; l<N; l++)
                  if(mat[l][j]==k) crossoff[k][i][j]=false;
                for(int l=0; l<SRN; l++)
                  for(int m=0; m<SRN; m++)
                    if(mat[i-i%SRN+l][j-j%SRN+m]==k) crossoff[k][i][j]=false;
              }
            }
       //check each cell
       for(int k=0; k<N; k++)
         for(int i=0; i<N; i++)
         {
           int count=0, d=-1;
           for(int j=0; j<N; j++)
              if(crossoff[j][k][i]==true)
              {
                count++;
                d=j;
              }
          if(count==1){
              mat[k][i]=d;
              fixed_val[k][i]=1;
              crossoff[d][k][i]=false;
              for(int l=0; l<N; l++)
                crossoff[d][k][l]=false;
              for(int l=0; l<N; l++)
                crossoff[d][l][i]=false;
              for(int l=0; l<SRN; l++)
                for(int m=0; m<SRN; m++)
                  crossoff[d][k-k%SRN+l][i-i%SRN+m]=false;
          }
       }
       //check for singular value/cell
       for(int k=0; k<N; k++)
         for(int i=0; i<N; i++)
           for(int j=0; j<N; j++)
           {
             if(crossoff[k][i][j]==true){
               int count=-3;
               for(int l=0; l<N; l++)
                 if(crossoff[k][i][l]) count++;
               for(int l=0; l<N; l++)
                 if(crossoff[k][l][j]) count++;
               for(int l=0; l<SRN; l++)
                 for(int m=0; m<SRN; m++)
                   if(crossoff[k][i-i%SRN+l][j-j%SRN+m]) count++;
               if(count==0)
               {
                 mat[i][j]=k;
                 fixed_val[i][j]=1;
                 for(int l=0; l<SRN; l++)
                   crossoff[l][i][j]=false;
               }
             }
          }
       std::cout<<"Print mat:\n";
       for (int i = 0; i<N; i++)
       {
           for (int j = 0; j<N; j++)
               std::cout<<mat[i][j]<<" ";
           std::cout<<"\n";
       }
       std::cout<<"\n";
       //Phase2: GA
       bool found = false, restart = false;
       vector<Individual> persistent_population;

       int restart_count=0, total_generation=0;
       while((!found))
       {
           restart = false;
           // current generation
           int generation = 0;
           int f=0;
           int *GENES= new int[N];
           for(int i = 0; i < N; i++)
              GENES[i] = i;

           vector<Individual> population;

           // create initial population
           if(persistent_population.size() == population_size)
           {
             population = persistent_population;
             for(int i = 0;i<population_size;i++)
                  persistent_population.pop_back();
           }else{
             for(int i = 0;i<population_size;i++)
             {
                 //std::cout<<"Creating initial population:"<<i<<"\n";
                 int **gnome = create_gnome(mat, GENES);
                 population.push_back(Individual(gnome));

        	       for(int j=0; j<N; j++)
        	       {
          	         delete[] gnome[j];
        	       }
                 delete[] gnome;
                 //population[i].printSudoku();
                 cout<< "Fitness: "<< population[i].fitness << "\n";
             }
           }
           //std::cout<<"Population 0:\n";
           //population[0].printSudoku();
           //found = true;
           while((!found) && (!restart))
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
               if(new_generation[0].fitness!=f){
                   restart_count = 0;
                   f=new_generation[0].fitness;
                   cout<< "Generation: " << generation << "\t\t";
                   cout<< "Fitness: "<< new_generation[0].fitness << "\n";
               }
               restart_count++;
               if(restart_count >= restart_threshold){
                   //f=new_generation[0].fitness;
                   cout<< "RESTARTING: \n";
                   restart=true;
                   int selection = population_size/10;
                   if(persistent_population.size()<population_size){
                     for(int i=0; i<selection; i++)
                        persistent_population.push_back(new_generation[i]);
                        sort(persistent_population.begin(), persistent_population.end());
                   }
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
    	             int **mate = parent1.mate(parent2, fixed_val, mutation, GENES);
                   Individual offspring = Individual(mate);

      		         for(int j = 0; j < N; j++) {
          	          delete[] mate[j];
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
               total_generation++;
               if(stop != 0)
                if(total_generation > stop)
                  break;
          }
          cout<< "Generation: " << generation-1 << "\n";
          //cout<< "String: "<< population[0].chromosome <<"\t";
          population[0].printSudoku();
          cout<< "Fitness: "<< population[0].fitness << "\n\n";
          if(persistent_population.size()<=0){
            if(population[0].fitness<=persistent_population[0].fitness){
              Individual best=population[0];
            }else{
              Individual best=persistent_population[0];
            }
          }else{
            Individual best=population[0];
          }
         for(int i = 0;i<population_size;i++)
         {
  	        population.pop_back();
  	     }
         if(stop != 0)
          if(total_generation > stop){
            best.printSudoku();
            cout<< "Fitness: "<< best.fitness << "\n\n";
          }
            break;
      }
      cout<< "Total Generations: " << total_generation-1 << "\n";
}
};
