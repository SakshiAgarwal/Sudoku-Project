#ifndef LOGGER_H
#define LOGGER_H
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Logger
{
  private:
    ofstream current_file;

  public:
    Logger();
    bool open(string file_name, vector<int> baggage);
    bool open(string file_name);
    bool open_append(string file_name);
    void close();
    bool log(vector<double> dataRow);

};
#endif