#include "SudokuManager.h"

string SudokuManager::output_folder = "boards/";

char SudokuManager::file_names[8][27] = {"benchmarks/hexa-20.txt", "benchmarks/hexa-21.txt", 
  "benchmarks/hexa-50.txt", "benchmarks/hexa-80.txt", "benchmarks/hexa-21.txt", 
  "benchmarks/hexa-82.txt", "benchmarks/hexa-100.txt", "benchmarks/hexa-101.txt"};

SudokuManager::SudokuManager()
{
  *this = SudokuManager(3);
}

SudokuManager::SudokuManager(int inputSize)
{
  if(inputSize < 2)
  {
    throw invalid_argument("Sudoku size must be greater than 1.");
  } 
  size = inputSize * inputSize;
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

SudokuManager::SudokuManager(std::string file_name)
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
            int temp = ( (int) w.at(0) - 'A') + 10;
            row.push_back(temp);
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
        board[i][j] = v;
        j += 1;
      }
      i += 1;
    }
  }
  myfile.close();
}
SudokuManager::SudokuManager(int input_size, int** input_board)
{
  size = input_size;
  board = new int*[size];
  for(int i = 0; i < size; i++)
  {
    board[i] = new int[size];
    for(int j = 0; j < size; j++)
    {
      board[i][j] = input_board[i][j];
    }
  }
}

int** SudokuManager::getBoard()
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

void SudokuManager::print()
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
void SudokuManager::save(string output_name)
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
SudokuManager SudokuManager::benchmarkBoard(int index)
{
  if(index < 0 || index > 7)
  {
    throw invalid_argument("Index should be between 0 and 8.");
  } 
  char* name = file_names[index];
  SudokuManager temp(name);
  return temp;
}

bool SudokuManager::isValidCol(int j, int val)
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
bool SudokuManager::isValidRow(int i, int val)
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
bool SudokuManager::isValidBlock(int i, int j, int val)
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

bool SudokuManager::isValidAssignment(int i, int j, int val)
{
  bool a = isValidCol(j, val);
  bool b = isValidRow(i, val);
  bool c = isValidBlock(i,j,val);
  return a && b && c;
}
int SudokuManager::getRand(int max)
{
  return rand() % max; 
}
SudokuManager SudokuManager::generateBoard(int inputSize, int difficulty)
{  
  SudokuManager a = SudokuManager(inputSize);
  int count = difficulty;
  int iteration = 0;
  while(count > 0)
  {
    int randRow = getRand(a.size);
    int randColumn = getRand(a.size);
    int randAssignment = getRand(a.size);
    
    if( a.board[randRow][randColumn] == -1 && a.isValidAssignment( randRow, randColumn, randAssignment))
    {
      // Debugging only
      //int valueID = difficulty - count + 1;
      //cout<<valueID<<" : ("<<randRow<<","<<randColumn<<") = "<< randAssignment<<endl;
      a.board[randRow][randColumn] = randAssignment;
      count -= 1;
    }
    iteration += 1;
  }
  return a;
}
void SudokuManager::seed()
{
  srand(time(nullptr));
}