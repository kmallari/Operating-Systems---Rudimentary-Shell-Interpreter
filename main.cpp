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

string charToString(char *chars)
{
  string s(chars);
  return s;
}

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
  pid_t pidPipe;

  size_t spc = charToString(command[0]).find(' ');
  size_t dash = charToString(command[1]).find('-');
  size_t period = charToString(command[1]).find('.');

  if(pid == 0)
  {
    if (redirect == 1) //currently only for output redirection
    {
      int fileDesc = open(fileNMs.data()[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
      dup2(fileDesc,STDOUT_FILENO);
      close(fileDesc);
      data[1] = NULL;
      
      if (spc!=string::npos)
      {
        vector<char *> commandInput = split(charToString(command[0]), ' ');
        if(execvp(commandInput.data()[0], commandInput.data()) == -1)
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
          exit(10);
        }
      }
      else 
      {
        if(execvp(command[0], data) == -1)
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
          exit(10);
        }
      }
    }
    else if (redirect == 2)
    {
      int fileDesc = open(fileNMs.data()[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
      dup2(fileDesc,STDIN_FILENO);
      close(fileDesc);
      data[1] = NULL;
      if (spc!=string::npos)
      {
        vector<char *> commandInput = split(charToString(command[0]), ' ');
        if(execvp(commandInput.data()[0], commandInput.data()) == -1)
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
          exit(10);
        }
      }
      else 
      {
        if(execvp(command[0], data) == -1)
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
          exit(10);
        }
      }
    }
    else if (redirect == 3)
    {
      int fd[2];
      char *secondCommand[2];
      secondCommand[0] = command[1];
      data[1] = NULL;
      
      if(pipe(fd) == -1)
      {
        cout << "SOMETHING WENT WRONG ";
        cout << "PIPE ERROR"<<endl;
        exit(10);
      }

      pidPipe = fork();
      if (pidPipe > 0) {
        wait(NULL);
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        if (dash!=string::npos)
        {
          vector<char *> commandInput = split(charToString(secondCommand[0]), ' ');
          if(execvp(commandInput.data()[0], commandInput.data()) == -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" <<endl;
            exit(10);
          }
        }
        else
        {
          secondCommand[1] = NULL;
          if (execvp(secondCommand[0], secondCommand) == -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" <<endl;
            exit(10);
          }
        }
      } 
      else if (pidPipe == 0) 
      {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        if (spc!=string::npos)
        {
          vector<char *> commandInput = split(charToString(command[0]), ' ');
          if(execvp(commandInput.data()[0], commandInput.data()) == -1)
          {
            cout << "SOMETHING WENT WRONG INPUT PIPE" <<endl;
            exit(10);
          }
        }
        else 
        {
          if(execvp(command[0], data) == -1)
          {
            cout << "SOMETHING WENT WRONG INPUT PIPE" <<endl;
            exit(10);
          }
        }
        exit(10);
      }
      close(fd[0]);
      close(fd[1]);
    }
    else
    {
      if (dash==string::npos && period==string::npos)
      {
        data[1] = NULL;
      }

      if(execvp(command[0], data) == -1)
      {
        cout << "SOMETHING WENT WRONG " <<endl;
        exit(10);
      }
    }

    //kill(pid, SIGKILL);
  }
  else
  {
    wait(NULL);
  }
}

void checkInput(string currentCommand)
{
  size_t redirin = currentCommand.find('<');
  size_t redirout = currentCommand.find('>');
  size_t pipe = currentCommand.find('|');
  vector<char *> nullVec, redirectInCommand, redirectOutCommand, command, pipeCommand;

  if(redirin!=string::npos)
  {
    redirectInCommand = split(currentCommand, '<');
    execCommand(redirectInCommand, redirectInCommand.data(), redirectInCommand, 2);
  }
  else if (redirout!=string::npos)
  {
    redirectOutCommand = split(currentCommand, '>');
    execCommand(redirectOutCommand, redirectOutCommand.data(), redirectOutCommand, 1);
  }

  if(pipe!=string::npos)
  {
    pipeCommand = split(currentCommand, '|');
    execCommand(pipeCommand, pipeCommand.data(), nullVec, 3);
  }
  else if (redirin==string::npos && redirout==string::npos)
  {
    command = split(currentCommand, ' ');
    execCommand(command, command.data(), nullVec, false);
  }
} 

int main()
{
  string input;
  vector<char *> prevArgs, prevFNMs;
  bool should_run = 1; //determine when to exit program

  while(should_run)
  {
    cout << "~\033[1;31mFelipe\033[0m\033[1;32mLuke\033[0m\033[1;"
            "33mKevin\033[0m\n$ ";
    getline(cin, input);

    if (input == "exit")
    {
      return 0;
    }

    checkInput(input);
  }
}