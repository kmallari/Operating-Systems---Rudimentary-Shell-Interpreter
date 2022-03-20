//Project 1 Rudimentary Shell Interpreter
//ENGG 126 A
//Coded by:
//Felipe Gan
//Kevin Mallari
//Luke Lao

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

// ADDITIONAL LIBRARIES NEEDED
#include <fcntl.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <vector>
using namespace std;

string charToString(char *chars)
{
  string s(chars);
  return s;
}

char *trimWhiteSpace(char *chars)
{
  string temp = charToString(chars);
  while (temp.find(' ') == 0) // trim at start
  {
    temp.erase(0, 1);
  }

  while (temp.find(' ') == temp.length() - 1) // trim at end
  {
    temp.erase(temp.length() - 1, 1);
  }

  char *c = new char[temp.length()];
  strcpy(c, temp.c_str());

  return c;
}

// split character array using delimiter
vector<char *> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while (getline(ss, tok, delimiter))
  {
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

void execCommand(string command, int type)
{
  pid_t pid = fork();
  pid_t pidPipe;

  vector<char *> redirectCommand, regularCommand;

  if (pid == 0)
  {
    if (type == 1 || type == 2) // redirection
    {
      if (type == 1) // output redirection
      {
        redirectCommand = split(
            command, '>'); // split command with output delimiter
        redirectCommand[0] =
            trimWhiteSpace(redirectCommand[0]); // trim whitespace
        redirectCommand[1] =
            trimWhiteSpace(redirectCommand[1]); // trim whitespace

        // https://man7.org/linux/man-pages/man2/open.2.html
        int fileDesc = open(redirectCommand.data()[1],
                            O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fileDesc,
             STDOUT_FILENO); // dup2 file descriptor for output
        close(fileDesc);
      }
      else if (type == 2) // input redirection
      {
        redirectCommand =
            split(command, '<'); // split command with input delimiter
        redirectCommand[0] =
            trimWhiteSpace(redirectCommand[0]); // trim whitespace
        redirectCommand[1] =
            trimWhiteSpace(redirectCommand[1]); // trim whitespace

        // https://man7.org/linux/man-pages/man2/open.2.html
        int fileDesc = open(redirectCommand.data()[1],
                            O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fileDesc, STDIN_FILENO); // dup2 file descriptor for
                                      // input
        close(fileDesc);
      }

      redirectCommand[1] =
          NULL; // removes filename from array and replaces with null
                // for command execution

      size_t spc = charToString(redirectCommand[0])
                       .find(' '); // check if additional arguments
                                   // within first command
      if (spc != string::npos)     // execute if space is detected in
                                   // first argument
      {
        vector<char *> commandInput = split(
            charToString(redirectCommand[0]),
            ' '); // split first argument based on space delimiter
        if (execvp(commandInput.data()[0], commandInput.data()) ==
            -1) // execute command
        {
          cout << "SOMETHING WENT WRONG "; // error display
          cout << "REDIRECT ERROR"
               << endl; // additional information for debugging
          exit(10);
        }
      }
      else // no space in first argument, execute as is
      {
        if (execvp(redirectCommand.data()[0],
                   redirectCommand.data()) == -1) // execute command
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR" << endl;
          exit(10);
        }
      }
    }
    else if (type == 3)
    {
      int fd[2];
      char *secondCommand[2];

      regularCommand =
          split(command, '|'); // split command with pipe delimiter
      secondCommand[0] = trimWhiteSpace(
          regularCommand[1]); // extracts second command

      size_t spc1 = charToString(regularCommand[0])
                        .find(' '); // check if additional arguments
                                    // within first command
      size_t spc2 = charToString(secondCommand[0])
                        .find(' '); // check if additional arguments
                                    // within second command

      if (pipe(fd) == -1) // creates pipe
      {
        cout << "SOMETHING WENT WRONG "; // error display
        cout << "PIPE ERROR"
             << endl; // additional information for debugging
        exit(10);
      }

      pidPipe = fork(); // forks to execute input pipe within child

      if (pidPipe > 0) // output pipe or parent pipe
      {
        wait(NULL); // wait for input pipe/child
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO); // communicate through pipe, READ
        close(fd[0]);
        if (spc2 != string::npos)
        {
          vector<char *> commandInput =
              split(charToString(secondCommand[0]), ' ');
          if (execvp(commandInput.data()[0], commandInput.data()) ==
              -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" << endl;
            exit(10);
          }
        }
        else
        {
          secondCommand[1] = NULL;
          if (execvp(secondCommand[0], secondCommand) == -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" << endl;
            exit(10);
          }
        }
      }
      else if (pidPipe == 0)
      {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); // communicate through pipe, WRITE
        close(fd[1]);
        if (spc1 != string::npos)
        {
          vector<char *> commandInput =
              split(charToString(regularCommand[0]), ' ');
          if (execvp(commandInput.data()[0], commandInput.data()) ==
              -1)
          {
            cout << "SOMETHING WENT WRONG INPUT PIPE" << endl;
            exit(10);
          }
        }
        else
        {
          if (execvp(regularCommand.data()[0],
                     regularCommand.data()) == -1)
          {
            cout << "SOMETHING WENT WRONG INPUT PIPE" << endl;
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
      regularCommand =
          split(command, ' '); // split command with space delimiter

      if (execvp(regularCommand.data()[0], regularCommand.data()) ==
          -1) // execute command
      {
        cout << "SOMETHING WENT WRONG " << endl;
        exit(10);
      }
    }

    // kill(pid, SIGKILL);
  }
  else if (pid < 0)
  {
    cout << "Fork failed. Exiting Program...";
    exit(-1);
  }
  else
  {
    wait(NULL);
  }
}

void checkInput(string command)
{
  size_t redirin = command.find('<');
  size_t redirout = command.find('>');
  size_t pipe = command.find('|');

  //redirection in
  if (redirin != string::npos)
  {
    execCommand(command, 2);
  }
  //redirection out
  else if (redirout != string::npos)
  {
    execCommand(command, 1);
  }
  //pipe
  if (pipe != string::npos)
  {
    execCommand(command, 3);
  }
  //regular command
  else if (redirin == string::npos && redirout == string::npos)
  {
    execCommand(command, 0);
  }
}

int main()
{
  string input;
  vector<char *> prevArgs, prevFNMs;
  bool should_run = 1; // determine when to exit program

  while (should_run)
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