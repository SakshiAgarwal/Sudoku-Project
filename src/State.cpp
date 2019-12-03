#include "State.h"

State::State(int a[Utils::N][Utils::N],int fix[Utils::N][Utils::N])
{
  for(int i=0;i<Utils::N;i++)
  {
    for(int j=0;j<Utils::N;j++) {
      curr[i][j] = a[i][j];
      f[i][j] = fix[i][j];
    }
  }
}
State State::neighbour()
{
  int i,j,k1,k2,k3,k4;
  int array2[Utils::N][Utils::N];
  for(i=0;i<Utils::N;i++)
  {
    for(j=0;j<Utils::N;j++)
    {
      array2[i][j] = curr[i][j];
    }
    //std::cout <<"in neighbour"<< std::endl;
  }
    
  i = Utils::randomGenerator(Utils::N);
  j = Utils::randomGenerator(Utils::N);

  //std::cout<<i<< " "<<j<<std::endl;
  do
  {
    k1 = Utils::randomGenerator(Utils::SRN);
    k2 = Utils::randomGenerator(Utils::SRN);

    k3 = Utils::randomGenerator(Utils::SRN);
    k4 = Utils::randomGenerator(Utils::SRN);
    //std::cout<<k1<< " "<<k2<<" "<<k3<<" "<<k4<<std::endl;

    //std::cout <<"searching for values to be switched No!  "<<i-(i%SRN)+k1<<" "<<j - (j%SRN) + k2<<" "<<i-(i%SRN)+k3<<" "<<j - (j%SRN) + k4<<std::endl;
  } while (f[i-i%Utils::SRN+k1][j - j%Utils::SRN + k2]||f[i-i%Utils::SRN+k3][j - j%Utils::SRN + k4]);

  //std::cout<<"switched indices - ("<<i-i%SRN+k1<<","<<j - j%SRN + k2<<") ("<<i-i%SRN+k3<<","<<j - j%SRN + k4<<"\n";

  array2[i-i%Utils::SRN+k1][j - j%Utils::SRN + k2] = curr[i-i%Utils::SRN+k3][j - j%Utils::SRN + k4];
  array2[i-i%Utils::SRN+k3][j - j%Utils::SRN + k4] = curr[i-i%Utils::SRN+k1][j - j%Utils::SRN + k2];
  //std::cout <<"values swapped"<< std::endl;
  //std::cout <<"out of neighbour"<< std::endl;

  //for(i=0;i<N;i++) {
    //for (j = 0; j < N; j++)
      //std::cout << array2[i][j] << " ";
    //std::cout<<"\n";
  //}
  State s2(array2,f);
  return s2;
}

int State::fitness()
{
  int count = 0,cost;
  bool flag;
  int i,j;
  for(int k=0;k<Utils::N;k++)
  {
    for (i=0;i<Utils::N;i++)
    {
      flag = false;
      cost =0;
      for (j = 0; j < Utils::N; j++)
      {
        if (curr[i][j] == k)
        {
          flag = true;
          cost++;
        }
      }

      if(flag == false)
      {
        cost++;
      }
      else
      {
        cost--;
      }
      count = cost + count;
    }
  }

  cost = 0;
  for(int k=0;k<Utils::N;k++) 
  {
    for (i=0;i<Utils::N;i++) 
    {
      flag = false;
      cost=0;
      for (j = 0; j < Utils::N; j++) 
      {
        if (curr[j][i] == k) 
        {
          flag = true;
          cost++;
        }
      }
      if(flag == false)
      {
        cost++;
      }
      else
      {
        cost--;
      }
      count = cost + count;
    }
  }
  return count;
}
void State::printState()
{
  cout << "Printing state matrix now ------- \n";
  for (int i = 0; i<Utils::N; i++)
  {
    for (int j = 0; j<Utils::N; j++)
      cout<<curr[i][j]<<" ";
    cout<<"\n";
  }
  cout<<"\n";
}
