#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
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

      params = split(args, ' ');
      command = params[0];

      char command_char[command.size() + 1];
      strcpy(command_char, command.c_str());
      
      char* argument_list[params.size()+1];
      for (int i = 0; i<params.size(); i++)
      {
        strcpy(params[i], argument_list[i]);
      }

      argument_list[params.size()] = NULL;

      execvp(command_char, argument_list);

    /**
    * After reading user input, the steps are:
    * (1) fork a child process using fork()
    * (2) the child process will invoke execvp()
    * (3) parent will invoke wait() unless command included &
    */
    }
  return 0;
}