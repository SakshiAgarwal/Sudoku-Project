#include "GeneticAlgorithm.h"

// Create random genes for mutation
// create chromosome or string of genes
int** GeneticAlgorithm::create_gnome(int mat[Utils::N][Utils::N])
{
  int** gnome=0;
  gnome = new int*[Utils::N];
  for(int i=0; i<Utils::N; i++)
  {
    gnome[i] = new int[Utils::N];
    for(int j=0; j<Utils::N; j++)
      if(mat[i][j] != -1)
        gnome[i][j] = mat[i][j];
      else
        gnome[i][j] = Utils::mutated_genes()-'0';
  }
  return gnome;
}

GeneticAlgorithm::GeneticAlgorithm(int mat[Utils::N][Utils::N])
{
  for(int i=0; i<Utils::N; i++)
    for(int j=0; j<Utils::N; j++)
    {
      if(mat[i][j]!=-1)
        this->fixed_val[i][j] = 1;

      this->mat[i][j] = mat[i][j];
    }
}

void GeneticAlgorithm::compute(int population_size, int elitism, int eligible, float mutation, int stop)
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
    int **gnome = create_gnome(mat);
    population.push_back(Individual(gnome));
    population[i].printSudoku();
    cout<< "Fitness: "<< population[i].fitness << "\n";
  }
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
    for(int i = 0;i<s;i++){
      new_generation.push_back(population[i]);
    }
    if(new_generation[0].fitness!=f){
        f=new_generation[0].fitness;
        cout<< "Generation: " << generation << "\t\t";
        cout<< "Fitness: "<< new_generation[0].fitness << "\n";
    }
    // From 50% of fittest population, Individuals
    // will mate to produce offspring
    //s = ((100-elitism)*population_size)/100;
    s = population_size - s;
    for(int i = 0;i<s;i++)
    {
      int len = population.size();
      int r = Utils::random_num(0, eligible*population_size/100), s=r;
      Individual parent1 = population[r];
      while(s == r)
      {
        s = Utils::random_num(0, eligible*population_size/100);
      }
      Individual parent2 = population[s];
      Individual offspring = parent1.mate(parent2, fixed_val, mutation);
      new_generation.push_back(offspring);
    }
    population = new_generation;
    generation++;
    if(stop != 0)
    if(generation > stop)
      break;
  }
  cout<< "Generation: " << generation-1 << "\t";
  //cout<< "String: "<< population[0].chromosome <<"\t";
  cout<< "Fitness: "<< population[0].fitness << "\n";
}