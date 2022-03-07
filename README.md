
# Operating Systems Project - Rudimentary Shell Interpreter
## General Specifications
Design a C/C++ program to serve as a shell interface that accepts user commands and then executes each command in a separate  process. Your implementation will  support  input and output redirection, as well as pipes as a form of interprocess communication (IPC) between a pair of commands.  Implement  this  project   using  system   calls   such   as  the   UNIX  `fork()`,  `exec()`, `wait()`,  `dup2()`, and  `pipe()`  on Linux, UNIX, or macOS  systems or equivalent system calls on other operating systems. 

## Detailed Specifications
Design a C/C++ program to serve as a shell interface that accepts user commands and then executes each command in a separate process. Your implementation will support input and output redirection, as well as pipes as a form of IPC between a pair of commands. Implement this project using system calls such as the UNIX fork(), exec(), wait(), dup2(), and pipe() on Linux, UNIX, or macOS systems or equivalent system calls on other operating systems. 
 
The program parses each line from the user for the pipe ( '|' ) and input ( '<' ) and output ( '>' ) redirection symbols and acts accordingly. The program does not pass entire command lines from a user to the operating system if they contain the pipe ( '|' ) or input ( '<' ) or output ( '>' ) redirection symbols.  

The output redirection operator `‘>’` redirects the output of a command to a file. In the command line  
`ls > out.txt` the output from the ls command would be redirected to the file out.txt. 

The input redirection operator ‘<’ redirects the contents of a file to the input of a command. In the command line  
`sort < in.txt` the file `in.txt` would serve as input to the sort command.  

The pipe operator '|' allows the output of one command to serve as input to another. In the command line `ls -l | less` the output of the command `ls -l` serves as the input to the less command.  

For this rudimentary shell interpreter, it may be assumed that at most one of the pipe  
and redirection operators occurs on a command line and at most once in the case of the pipe.
