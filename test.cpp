#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// split string using delimiter
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
}

int main () {
  string a = "mkdir folder_name";
  vector<string> b = split(a, ' ');
  for (int i = 0; i < b.size(); i++) {
    cout << b[i] << endl;
  }
}