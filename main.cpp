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

<<<<<<< HEAD
char * trimWhiteSpace(char *chars)
{
  string temp = charToString(chars);
  while (temp.find(' ') == 0)
  {
    temp.erase(0,1);
  }

  while (temp.find(' ') == temp.length()-1) //trim at end
  {
    temp.erase(temp.length()-1,1);
=======
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
>>>>>>> kevs
  }

  char *c = new char[temp.length()];
  strcpy(c, temp.c_str());

  return c;
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

<<<<<<< HEAD
void execCommand(vector<char *> command, char ** data, int type)
=======
void execCommand(string command, int type)
>>>>>>> kevs
{
  pid_t pid = fork();
  pid_t pidPipe;

<<<<<<< HEAD
  size_t spc = charToString(command[0]).find(' ');
  size_t dash = charToString(command[1]).find('-');
  size_t period = charToString(command[1]).find('.');

  if(pid == 0)
  {
    if (type == 1) //output redirection
    {
      command[1] = trimWhiteSpace(command[1]);

      int fileDesc = open(command.data()[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
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
=======
  vector<char *> redirectCommand, regularCommand;

  if(pid == 0)
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
>>>>>>> kevs
      }
      else if (type == 2) // input redirection
      {
<<<<<<< HEAD
        if(execvp(command[0], data) == -1)
        {
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
          exit(10);
        }
      }
    }
    else if (type == 2)
    {
      command[1] = trimWhiteSpace(command[1]);

      int fileDesc = open(command.data()[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
      dup2(fileDesc,STDIN_FILENO);
      close(fileDesc);
      data[1] = NULL;
      if (spc!=string::npos)
=======
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
>>>>>>> kevs
      {
        vector<char *> commandInput = split(
            charToString(redirectCommand[0]),
            ' '); // split first argument based on space delimiter
        if (execvp(commandInput.data()[0], commandInput.data()) ==
            -1) // execute command
        {
<<<<<<< HEAD
          cout << "SOMETHING WENT WRONG ";
          cout << "REDIRECT ERROR"<<endl;
=======
          cout << "SOMETHING WENT WRONG "; // error display
          cout << "REDIRECT ERROR"
               << endl; // additional information for debugging
>>>>>>> kevs
          exit(10);
        }
      }
      else // no space in first argument, execute as is
      {
        if (execvp(redirectCommand.data()[0],
                   redirectCommand.data()) == -1) // execute command
        {
          cout << "SOMETHING WENT WRONG ";
<<<<<<< HEAD
          cout << "REDIRECT ERROR"<<endl;
=======
          cout << "REDIRECT ERROR" << endl;
>>>>>>> kevs
          exit(10);
        }
      }
    }
<<<<<<< HEAD
=======

>>>>>>> kevs
    else if (type == 3)
    {
      int fd[2];
      char *secondCommand[2];
<<<<<<< HEAD
      secondCommand[0] = trimWhiteSpace(command[1]);
      data[1] = NULL;
      
      if(pipe(fd) == -1)
      {
        cout << "SOMETHING WENT WRONG ";
        cout << "PIPE ERROR"<<endl;
=======

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
>>>>>>> kevs
        exit(10);
      }

      pidPipe = fork(); // forks to execute input pipe within child

      if (pidPipe > 0) // output pipe or parent pipe
      {
        wait(NULL); // wait for input pipe/child
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO); // communicate through pipe, READ
        close(fd[0]);
<<<<<<< HEAD
        if (dash!=string::npos)
        {
          vector<char *> commandInput = split(charToString(secondCommand[0]), ' ');
          if(execvp(commandInput.data()[0], commandInput.data()) == -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" <<endl;
=======
        if (spc2 != string::npos)
        {
          vector<char *> commandInput =
              split(charToString(secondCommand[0]), ' ');
          if (execvp(commandInput.data()[0], commandInput.data()) ==
              -1)
          {
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" << endl;
>>>>>>> kevs
            exit(10);
          }
        }
        else
        {
          secondCommand[1] = NULL;
          if (execvp(secondCommand[0], secondCommand) == -1)
          {
<<<<<<< HEAD
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" <<endl;
=======
            cout << "SOMETHING WENT WRONG OUTPUT PIPE" << endl;
>>>>>>> kevs
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
<<<<<<< HEAD
            cout << "SOMETHING WENT WRONG INPUT PIPE" <<endl;
=======
            cout << "SOMETHING WENT WRONG INPUT PIPE" << endl;
>>>>>>> kevs
            exit(10);
          }
        }
        else
        {
          if (execvp(regularCommand.data()[0],
                     regularCommand.data()) == -1)
          {
<<<<<<< HEAD
            cout << "SOMETHING WENT WRONG INPUT PIPE" <<endl;
=======
            cout << "SOMETHING WENT WRONG INPUT PIPE" << endl;
>>>>>>> kevs
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
<<<<<<< HEAD
      if (dash==string::npos && period==string::npos)
      {
        data[1] = NULL;
      }

      if(execvp(command[0], data) == -1)
      {
        cout << "SOMETHING WENT WRONG " <<endl;
=======
      regularCommand =
          split(command, ' '); // split command with space delimiter

      if (execvp(regularCommand.data()[0], regularCommand.data()) ==
          -1) // execute command
      {
        cout << "SOMETHING WENT WRONG " << endl;
>>>>>>> kevs
        exit(10);
      }
    }
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

<<<<<<< HEAD
void checkInput(string currentCommand)
{
  size_t redirin = currentCommand.find('<');
  size_t redirout = currentCommand.find('>');
  size_t pipe = currentCommand.find('|');
  vector<char *> nullVec, redirectInCommand, redirectOutCommand, command, pipeCommand;

  if(redirin!=string::npos)
  {
    redirectInCommand = split(currentCommand, '<');
    execCommand(redirectInCommand, redirectInCommand.data(), 2);
  }
  else if (redirout!=string::npos)
  {
    redirectOutCommand = split(currentCommand, '>');
    execCommand(redirectOutCommand, redirectOutCommand.data(), 1);
  }

  if(pipe!=string::npos)
  {
    pipeCommand = split(currentCommand, '|');
    execCommand(pipeCommand, pipeCommand.data(), 3);
  }
  else if (redirin==string::npos && redirout==string::npos)
  {
    command = split(currentCommand, ' ');
    execCommand(command, command.data(), false);
=======
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
>>>>>>> kevs
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
<<<<<<< HEAD

=======
    
>>>>>>> kevs
    checkInput(input);
  }
}