// Lui Agustin
// 20220302
// initial code from
// (book ) Abraham Silberschatz, Peter Galvin and Greg Gagne:
//    Operating System Concepts, 10th ed, Wiley, 2018.
#include <sys/types.h>
#include <sys/wait.h> //https://www.geeksforgeeks.org/wait-system-call-c/
//#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;
int main()
{
  string s;
  pid_t pid;
  /* fork a child process */
  cout << "~\033[1;31mFelipe\033[0m\033[1;32mLuke\033[0m\033[1;33mKevin\033[0m\n$ ";
  getline (cin, s);
  pid = fork();
  cout << "Press Enter:";
  getline (cin, s);
  cout << s << endl;
  if (pid < 0)
  { /* error occurred */
    cerr << "Fork Failed";
    return 1;
  }
   else if (pid == 0)
  { /* child process */
    execlp("/bin/ls","ls",NULL);
    cout << "child s: " << s << endl;
  }
  else
  { /* parent process */
    /* parent will wait for the child to complete */
    cout << "parent pid: " << pid << endl;
    cout << "parent s: " << s << endl;
    wait(NULL);
    cout << "Child Complete\n";
  }
  return 0;
}