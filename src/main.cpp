#include <iostream>
#include <string>
using namespace std;
int main() {
  cout<<"$ ";
  string command;
  getline(cin,command);
  if(!command.empty())
  cout<<command<<": command not found"<<endl;
}
