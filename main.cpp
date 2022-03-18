#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

// ADDITIONAL LIBRARIES NEEDED
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <fcntl.h>
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

void execCommand(vector<char *> command, char ** data, vector<char *> fileNMs, int redirect)
{
  pid_t pid = fork();

/*   char *c = new char[command.length() + 1];
  strcat(c, " /bin/");
  strcat(c, command.c_str());
  command.data()[0] = c.data(); */

  if(pid == 0)
  {
    if (redirect == 1) //currently only for output redirection
    {
      int fileDesc = open(fileNMs.data()[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
      dup2(fileDesc,STDOUT_FILENO);
      close(fileDesc);
      data[1] = NULL;
      if(execvp(command[0], data) == -1)
      {
        cout << "SOMETHING WENT WRONG";
        cout << "REDIRECT ERROR";
        exit(10);
      }
    }
    else if (redirect == 2)
    {
      
    }
    else 
    {
      if(execvp(command[0], data) == -1)
      {
        cout << "SOMETHING WENT WRONG";
        exit(10);
      }
    }
  }
  else
  {
    wait(NULL);
  }
}

// void checkInput(string currentCommand, vector<char *> &previousCommand, vector<char *> &previousFNMs)
void checkInput(string currentCommand)
{
  size_t redirin = currentCommand.find('<');
  size_t redirout = currentCommand.find('>');
  vector<char *> nullVec, redirectInCommand, redirectOutCommand;
  
  if(redirin!=string::npos)
  {
    vector<char *> redirectInCommand = split(currentCommand, '<');
    cout << redirectInCommand.data()[1] <<endl;
    execCommand(redirectInCommand, redirectInCommand.data(), redirectInCommand, 2);
    redirectInCommand.clear();
  }
  else if (redirout!=string::npos)
  {
    vector<char *> redirectOutCommand = split(currentCommand, '>');
    cout << redirectOutCommand.data()[1] <<endl;
    execCommand(redirectOutCommand, redirectOutCommand.data(), redirectOutCommand, 1);
    redirectOutCommand.clear();
  }
  else
  {
    vector<char *> command = split(currentCommand, ' ');
    execCommand(command, command.data(), nullVec, false);
    command.clear();
  }
} 

/*   if (redirectInCommand[1] != NULL)
  {
    //vector<char *> fileNMs = split(redirectInCommand.data()[1], ) possible check for multiple input files
    cout << "REDIRECT IN";
    cout << redirectInCommand.data()[1] <<endl;
    // execCommand(redirectInCommand, redirectInCommand.data(), redirectInCommand, true);
    // previousFNMs[0] = redirectInCommand.data()[1];
    // previousCommand[0] = redirectInCommand.data()[0];
  }
  else if (redirectOutCommand[1] != NULL)
  {
    //vector<char *> fileNMs = split(redirectInCommand.data()[1], ) possible check for multiple input files
    cout << "REDIRECT OUT";
    cout << redirectOutCommand.data()[1] <<endl;
    // execCommand(redirectOutCommand, redirectOutCommand.data(), redirectOutCommand, true);
    // previousFNMs[0] = redirectOutCommand.data()[1];
    // previousCommand[0] = redirectOutCommand.data()[0];
  }
  else
  {
    cout << "WENT TO ELSE";
    vector<char *> command = split(currentCommand, ' ');
    // execCommand(command, command.data(), nullVec, false);
    // previousCommand = command;
    // previousFNMs[0] = NULL;
  }
  // redirectInCommand.clear();
  // redirectOutCommand.clear(); */

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

    // checkInput(input, prevArgs, prevFNMs);
    checkInput(input);
    input.clear();
  }
}