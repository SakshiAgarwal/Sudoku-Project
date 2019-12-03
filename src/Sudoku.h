#include<iostream>
#include<math.h>
using namespace std;

class Sudoku
{
  private:
    /** Change here for a 25*25 input **/
    const static int N = 9;
    const static int SRN = 3;
  public:
    int mat[N][N];
    int fix[N][N];

    Sudoku(int a[N][N]);
    bool unUsedInBox(int rowStart, int colStart, int num);
    bool unUsedInRow(int i,int num);
    bool unUsedInCol(int j,int num);
    bool CheckIfSafe(int i,int j,int num);
    void printSudoku();
    int randomGenerator(int num);
    void init_solution(); 
};
