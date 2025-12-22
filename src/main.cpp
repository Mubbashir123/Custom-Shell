#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cwctype>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main()
{
  while (true)
  {
    cout << "$ ";
    string command;
    getline(cin, command);
    if (command == "exit")
      break;
    else if (command.find("type") != string::npos)
    {
      if (command.substr(5) == "echo" || command.substr(5) == "exit" || command.substr(5) == "type")
      {
        cout << command.substr(5) << " is a shell builtin" << endl;
      }
      else 
{
    string cmd = command.substr(5);

    const char* pathEnv = getenv("PATH");
    if (!pathEnv) {
        cout << cmd << ": not found" << endl;
        continue;
    }

    string path(pathEnv);
    path.push_back(':');   

    bool found = false;
    int prev = 0;

    for (int i = 0; i < path.size(); i++) {
        if (path[i] == ':') {
            string dir = path.substr(prev, i - prev);
            prev = i + 1;

            if (dir.empty()) continue;

            if (exists(dir)) {
                string fullPath = dir + "/" + cmd;

                if (exists(fullPath)) {
                    auto perms = status(fullPath).permissions();

                    if ((perms & filesystem::perms::owner_exec) != filesystem::perms::none) {
                        cout << cmd << " is " << fullPath << endl;
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << cmd << ": not found" << endl;
    }
}

    }
    else if (command.find("echo") != string::npos)
    {
      cout << command.substr(5) << endl;
    }
    else
      cout << command << ": command not found" << endl;
  }
}
