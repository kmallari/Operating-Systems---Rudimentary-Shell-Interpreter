#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> //https://www.geeksforgeeks.org/wait-system-

#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

#define MAX LINE 80 /* The maximum length command */
int main(void)
{
char *args[MAX LINE/2 + 1]; /* command line arguments */
int should run = 1; /* flag to determine when to exit program */
while (should run) {
cout << "osh>";
/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) parent will invoke wait() unless command included &
*/
}
return 0;
}