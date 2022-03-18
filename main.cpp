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

string charToString(char *chars)
{
  string s(chars);
  return s;
}

void execCommand(vector<char *> command, char **data,
                 vector<char *> fileNMs, bool redirect)
{
  pid_t pid = fork();

  /*   char *c = new char[command.length() + 1];
    strcat(c, " /bin/");
    strcat(c, command.c_str());
    command.data()[0] = c.data(); */

  vector<char *> commandInput = split(charToString(command[0]), ' ');

  if (pid == 0)
  {
    if (redirect) // currently only for output redirection
    {
      int fileDesc = open(
          fileNMs.data()[1], O_RDWR | O_CREAT,
          S_IRUSR |
              S_IWUSR); // https://man7.org/linux/man-pages/man2/open.2.html
      dup2(fileDesc, STDOUT_FILENO);
      close(fileDesc);
      data[1] = NULL;
      if (execvp(commandInput.data()[0], commandInput.data()) == -1)
      {
        cout << data;
        cout << "SOMETHING WENT WRONG" << endl;
        cout << "REDIRECT ERROR" << endl;
        // kill(pid, SIGKILL);
        exit(10);
      }
    }
    else
    {
      if (execvp(commandInput.data()[0], data) == -1)
      {
        cout << "SOMETHING WENT WRONG" << endl;
        exit(10);
      }
    }
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
  vector<char *> nullVec, redirectInCommand, redirectOutCommand;

  if (redirin != string::npos)
  {
    vector<char *> redirectInCommand = split(currentCommand, '<');
    cout << redirectInCommand.data()[1] << endl;
    execCommand(redirectInCommand, redirectInCommand.data(),
                redirectInCommand, true);
    redirectInCommand.clear();
  }
  else if (redirout != string::npos)
  {
    vector<char *> redirectOutCommand = split(currentCommand, '>');
    cout << redirectOutCommand.data()[1] << endl;
    execCommand(redirectOutCommand, redirectOutCommand.data(),
                redirectOutCommand, true);
    redirectOutCommand.clear();
  }
  else
  {
    vector<char *> command = split(currentCommand, ' ');
    execCommand(command, command.data(), nullVec, false);
    command.clear();
  }
}

int main()
{
  string input;
  // vector<char *> args;
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

    cout << "input: " << input << endl;
    // checkInput(input, prevArgs, prevFNMs);
    checkInput(input);
  }
}