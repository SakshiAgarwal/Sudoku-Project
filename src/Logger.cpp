#include "Logger.h"

Logger::Logger()
{
  // does nothing
}
bool Logger::open(string file_name, vector<int> baggage)
{
  string f_name = file_name;
  for(int i = 0; i < baggage.size(); i++)
  {
    f_name += "_" + to_string(baggage[i]);
  }
  return open(f_name);
}
bool Logger::open(string file_name)
{
  current_file = ofstream(file_name);
  if(current_file.is_open())
  {
    return true;
  }
  else {
    cout << "Unable to Open file: "<<file_name<<endl;
  }
}
bool Logger::open_append(string file_name)
{
  current_file = ofstream(file_name, ios_base::app);
  if(current_file.is_open())
  {
    return true;
  }
  else {
    cout << "Unable to Open file: "<<file_name<<endl;
  }
}
void Logger::close()
{
  current_file.close();
}
bool Logger::log(vector<double> dataRow)
{
  if(current_file.is_open())
  {
    current_file << dataRow[0];
    for(int i = 1; i < dataRow.size(); i++)
    {
      current_file<<","<<dataRow[i];
    }
    current_file<<endl;
    return true; // successful
  }
  return false; // file not open
}