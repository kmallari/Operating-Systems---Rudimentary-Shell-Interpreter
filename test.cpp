#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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

void execute(vector<char *> b)
{
  char *c = new char[b.size() + 1];
  strcpy(c, "/usr/bin/");
  strcat(c, b[0]);
  b.data()[0] = c;
  
  cout << c <<endl;
  cout << b.data()[0] <<endl;
  cout << b.data()[1] <<endl;

  if(execvp(b.data()[0], b.data())==-1)
  {
    cout << "ERROR" <<endl;
  }
}

int main()
{
  string a = "ls>testingnotepad.txt";
  // vector<char *> b = split(a, ' ');
  vector<char *> c = split(a, '>');
  // for (int i = 0; i < b.size(); i++)
  // {
  //   cout << b[i] << endl;
  // }
  // cout << b.data()[0] <<endl;
  // execute(b);
  // execvp(b.data()[0], b.data());
  int fileDesc = open(c.data()[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); //https://man7.org/linux/man-pages/man2/open.2.html
  dup2(fileDesc,1);
  dup2(fileDesc,2);
  close(fileDesc);
  c[1] = NULL;
  // cout << c.data()[0] <<endl;
  // cout << c.data()[1] <<endl;
  // cout << c.data()[2] <<endl;
  // c[1] = NULL;
  // cout << c.data()[0] <<endl;
  // cout << c.data()[1] <<endl;

  execvp(c.data()[0], c.data());
}
