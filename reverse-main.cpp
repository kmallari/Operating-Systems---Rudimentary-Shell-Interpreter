// reverse-main.cpp
// Lui Agustin
// 20220308

#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s;
  int len;
  while ( getline(cin,s) )
  {
    len = s.length();
    while (len>0)
      cout <<s[--len];
    cout <<endl;
  }
}