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
  string a = "ls -l";
  vector<char *> b = split(a, ' ');
  // for (int i = 0; i < b.size(); i++)
  // {
  //   cout << b[i] << endl;
  // }
  cout << b.data()[0] <<endl;
  execute(b);
  execvp(b.data()[0], b.data());
}
