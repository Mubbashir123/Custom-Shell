#include <iostream>
#include <string>
using namespace std;
int main() {
  while(true)
  { 
    cout<<"$ ";
    string command;
  getline(cin,command);
  if(command=="exit") break;
  else if (command.find("type")!=string::npos)
  {
    if(command.substr(5)=="echo"|| command.substr(5)=="exit"|| command.substr(5)=="type")
    {
      cout<<command.substr(5)<<" is a shell builtin"<<endl;
    }
    else cout<<command.substr(5)<<": not found"<<endl;
  }
  else if(command.find("echo")!=string::npos)
  {
    cout<<command.substr(5)<<endl;
  }
  else
  cout<<command<<": command not found"<<endl;
}


}
