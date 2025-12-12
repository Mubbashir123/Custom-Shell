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
   
  else if(command.find("echo")!=string::npos)
  {
    cout<<command.substr(5)<<endl;
  }
  
  else
  cout<<command<<": command not found"<<endl;
}


}
