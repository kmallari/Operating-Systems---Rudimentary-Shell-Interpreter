#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void command_parse(string args, string &parseCommand, vector<string> &parseParam)
{
  stringstream sstream(args);
  string temp;

  vector<string> out;
  
  while (getline(sstream, temp, ' ')) 
  {
    parseParam.push_back(temp);
  }

  parseCommand = parseParam[0];
  parseParam.erase(parseParam.begin());
}


int main()
{
  string args; /* command line arguments */
  string command; //command
  vector<string> params;
  int should_run = 1; /* flag to determine when to exit program */
  while (should_run) {
      cout << "osh>";

      getline(cin, args);

      command_parse(args, command, params);

      cout << "INPUT: " << command << "   ";
      
      for (int i = 0; i<params.size(); i++)
      {
          cout << params[i];
      }

      cout <<endl;


    /**
    * After reading user input, the steps are:
    * (1) fork a child process using fork()
    * (2) the child process will invoke execvp()
    * (3) parent will invoke wait() unless command included &
    */
    }
  return 0;
}