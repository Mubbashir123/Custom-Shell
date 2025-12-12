#include <iostream>
#include <string>
using namespace std;
int main() {
  cout<<"$ ";
  while(true)
 { string command;
  getline(cin,command);
  if(command=="exit") return;
  if(!command.empty())
  cout<<command<<": command not found"<<endl;
  cout<<"$ ";
}


}
