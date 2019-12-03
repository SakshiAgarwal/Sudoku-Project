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
    //std::cout<<"Creating initial population:"<<i<<"\n";
    int **gnome = create_gnome(mat);
    population.push_back(Individual(gnome));
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
    if(new_generation[0].fitness!=f){
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
      int r = Utils::random_num(0, eligible*population_size/100), s=r;
      //cout<< "parent "<< r<<" with ";
      Individual parent1 = population[r];
      while(s == r)
      {
        s = Utils::random_num(0, eligible*population_size/100);
      }
      //cout<< "parent "<< s<<"\n";
      Individual parent2 = population[s];
      Individual offspring = parent1.mate(parent2, fixed_val, mutation);
      new_generation.push_back(offspring);
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
  cout<< "Fitness: "<< population[0].fitness << "\n";
}