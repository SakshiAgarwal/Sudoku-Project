#include "Sudoku.h"

string Sudoku::output_folder = "boards/";

char Sudoku::file_names[8][27] = {"benchmarks/hexa-20.txt", "benchmarks/hexa-21.txt", 
  "benchmarks/hexa-50.txt", "benchmarks/hexa-80.txt", "benchmarks/hexa-21.txt", 
  "benchmarks/hexa-82.txt", "benchmarks/hexa-100.txt", "benchmarks/hexa-101.txt"};

/***************************
 *
 * constructors
 *
 ***************************/
Sudoku::Sudoku()
{
  *this = Sudoku(9);
}
Sudoku::Sudoku(int inputSize)
{
  if(inputSize < 0)
  {
    throw invalid_argument("Sudoku size must be positive.");
  } 
  int sqrtSize = (int)sqrt(inputSize);
  if( sqrtSize * sqrtSize != inputSize)
  {
    throw invalid_argument("Sudoku size must be a square.");
  } 
  size = inputSize;
  board = new int*[size];
  for(int i = 0; i < size; i++)
  {
    board[i] = new int[size];
    for(int j = 0; j < size; j++)
    {
      board[i][j] = -1;
    }
  }
}
Sudoku::Sudoku(std::string file_name)
{
  ifstream myfile;
  myfile.open (file_name);
  string line;

  // if file exists
  if (myfile.is_open())
  {
    vector<vector<int>> vectorBoard = {};
    while ( getline (myfile, line) )
    {     
      if(line.length() != 1)
      { 
        vector<int> row = {};
        vector<string> result;
        istringstream iss(line);
        // Iterate every word in the line
        for (string w; iss >> w; )
        {
          // convert HEX to number
          if( regex_match(w, std::regex("[+-]?[0-9]+")))
          {
            row.push_back(stoi(w));
          } else 
          {
            int pre = ((int)w.at(0));
            if(pre >= (int)'a')
            {
              pre -= 'a';
            }
            else if(pre >= (int)'A')
            {
              pre -= 'A';
            }
            row.push_back(pre + 10);
          }
        } 
        vectorBoard.push_back(row);
      }
    }

    // Convert the vector into 2D array
    size = vectorBoard.size();
    board = new int*[size];
    int i = 0;
    for (auto row: vectorBoard)
    {
      int j = 0;
      board[i] = new int[size];
      for (auto v: row) 
      {
        board[i][j] = v  % size; // mod so we get the values in [0,size)
        j += 1;
      }
      i += 1;
    }
  }
  myfile.close();
}
Sudoku::Sudoku(int input_size, int** input_board)
{
  size = input_size;
  board = new int*[size];
  for(int i = 0; i < size; i++)
  {
    board[i] = new int[size];
    for(int j = 0; j < size; j++)
    {
      board[i][j] = input_board[i][j] % input_size;
    }
  }
}
Sudoku Sudoku::copy()
{
  return Sudoku(size, board);
}


/***************************
 *
 * bool functions
 *
 ***************************/
bool Sudoku::validInCol(int j, int val)
{
  for(int x = 0; x < size; x++)
  {
    if(board[x][j] == val)
    {
      return false;
    }
  }
  return true;
}
bool Sudoku::validInRow(int i, int val)
{
  for(int x = 0; x < size; x++)
  {
    if(board[i][x] == val)
    {
      return false;
    }
  }
  return true;
}
bool Sudoku::validInBlock(int i, int j, int val)
{
  int sqrtSize = sqrt(size);
  int rowDiv = (int) i/sqrtSize;
  int colDiv = (int) j/sqrtSize;
  for(int x = rowDiv * sqrtSize; x < (rowDiv + 1) * sqrtSize; x++)
  {
    for(int y = colDiv * sqrtSize; y < (colDiv + 1) * sqrtSize; y++)
    {
      if(board[x][y] == val)
      { 
        return false;
      }
    }
  }
  return true;
}
bool Sudoku::valid(int i, int j, int val)
{
  bool a = validInCol(j, val);
  bool b = validInRow(i, val);
  bool c = validInBlock(i,j,val);
  return a && b && c;
}

/***************************
 *
 * IO Functions
 *
 ***************************/
int** Sudoku::getBoardCopy()
{
  int** boardCopy = new int*[size];
  for(int i = 0; i < size; i++)
  {
    boardCopy[i] = new int[size];
    for(int j = 0; j < size; j++)
    {
      boardCopy[i][j] = board[i][j];
    }
  }
  return boardCopy;
}
void Sudoku::print()
{
  int divider = sqrt(size);
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      string temp = to_string(board[i][j]);
      if(temp.length() == 1)
      {
        cout << " " << board[i][j] << " ";
      } else 
      {
        // Empty spaces are *
        if(board[i][j] == -1)
        {
          cout << " * ";
        } else 
        {
          cout << board[i][j] << " ";
        }
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
void Sudoku::save(string output_name)
{
  ofstream myfile;
  string final_file(output_folder + output_name);
  myfile.open(final_file);
  
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      string temp = to_string(board[i][j]);
      if(temp.length() == 1)
      {
        myfile << " " << board[i][j] << " ";
      } else 
      {
        myfile << board[i][j] << " ";
      }
    }
    myfile << endl;
  }
  myfile.close();
}
Sudoku Sudoku::benchmarkBoard(int index)
{
  if(index < 0 || index > 7)
  {
    throw invalid_argument("Index should be between 0 and 8.");
  } 
  char* name = file_names[index];
  Sudoku temp(name);
  return temp;
}

void Sudoku::test()
{
  
  // create using all constructors
  Sudoku a = Sudoku();
  Sudoku b = Sudoku(9);
  Sudoku c = Sudoku("./boards/guaranteed_solution.txt");
  Sudoku d = Sudoku::benchmarkBoard(0);
  Sudoku e = Sudoku(16, d.board);
  bool correct = true;
  for(int i = 0; i < e.size; i++)
  {
    for(int j = 0; j < e.size; j++)
    {
      if(d.board[i][j] != e.board[i][j])
      {
        correct = false;
      }
    }
  }
  // Checking copy
  Sudoku f = e.copy();
  e.board[0][0] = 10000;
  
  // print results
  cout << "Constructor Sudoku()\t\t\t: "<< (a.size == 9) << endl;
  cout << "Constructor Sudoku(9)\t\t\t: "<< (b.size == 9) << endl;
  cout << "Constructor Sudoku(string)\t\t: "<< (c.size == 9 && c.board[0][0] == 8) << endl;
  cout << "Constructor benchmarkBoard(int)\t\t: "<< (d.size == 16 && d.board[14][15] == 10) << endl;
  cout << "Constructor Sudoku(int, int**)\t\t: "<< (correct && &e != &d) << endl;
  cout << "Constructor copy()\t\t\t: "<< (f.board[0][0] != 10000) << endl;

  // Checking bool functions
  cout << "The diagonal_test.txt board:"<<endl;
  Sudoku g = Sudoku("./boards/diagonal_test.txt");
  g.print();
  cout << "should see all the squares that aren't valid marked with 0:"<<endl;
  int val = 4;
  for(int i = 0; i < g.size; i++)
  {
    for(int j = 0; j < g.size; j++)
    {
      bool h = g.validInRow(i, val);//
      bool k = g.validInCol(j, val);
      bool l = g.validInBlock(i, j, val);
      bool m = g.valid(i, j, val);//
      cout<<"("<<m<<"="<<h<<k<<l<<") ";
    } 
    cout << endl;
  }
}