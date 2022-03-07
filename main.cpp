#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

// ADDITIONAL LIBRARIES NEEDED
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// split character array using delimiter
vector<char *> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str);  // Turn the string into a stream.
  string tok;

  while (getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  // translate vector of strings to vector of characters
  vector<char *> chars;

  for (int i = 0; i < internal.size(); i++)
  {
    char *c = new char[internal[i].length() + 1];
    strcpy(c, internal[i].c_str());
    chars.push_back(c);
  }

  return chars;
}

void execCommand(vector<char *> command, vector<char *> fileNMs, bool redirect)
{
  pid_t pid = fork();


  if(redirect)
  {
    
  }
  else
  {
    execvp(command.data()[0], command.data());
  }
}

void checkInput(string currentCommand, vector<char *> &previousCommand, vector<char *> &previousFNMs)
{
  vector<char *> redirectInCommand = split(currentCommand, '<');
  vector<char *> redirectOutCommand = split(currentCommand, '<');

  if (currentCommand.data()[0] == '!!')
  {
    if(previousCommand.data()[0] != NULL)
    {
      if(previousFNMs.data()[0] != NULL)
      {
        execCommand(previousCommand, previousFNMs, true);
      }
      else
      {
        execCommand(previousCommand, NULL, false);
      }
    }
    else
    {
      cout << "No commands in history." <<endl;
    }
  }
  else if (redirectInCommand.data()[1] != NULL)
  {
    //vector<char *> fileNMs = split(redirectInCommand.data()[1], ) possible check for multiple input files
    execCommand(redirectInCommand.data()[0],redirectInCommand.data()[1], true)
    previousFNMs[0] = redirectInCommand.data()[1];
    previousCommand[0] = redirectInCommand.data()[0];
  }
  else if (redirectOutCommand.data()[1] != NULL)
  {
    //vector<char *> fileNMs = split(redirectInCommand.data()[1], ) possible check for multiple input files
    execCommand(redirectOutCommand.data()[0],redirectOutCommand.data()[1], true)
    previousFNMs[0] = redirectOutCommand.data()[1];
    previousCommand[0] = redirectOutCommand.data()[0];
  }
  else
  {
    vector<char *> command = split(currentCommand, ' '); 
    execCommand(command, NULL, false);
    previousCommand = command;
    previousFNMs[0] = NULL;
  }
}

int main()
{
  string input;

  //vector<char *> args;
  vector<char *> prevArgs, prevFNMs;
  bool should_run = 1; //determine when to exit program

  while(should_run)
  {
    cout << "osh>";
    getline(cin, input);

    checkInput(input, prevArgs, prevFNMs);
  }
}