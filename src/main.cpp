#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    while (true) {
        cout << "$ ";
        string command;
        getline(cin, command);

        if (command == "exit")
            break;

        else if (command.rfind("type ", 0) == 0) { 
            string cmd = command.substr(5);

            if (cmd == "echo" || cmd == "exit" || cmd == "type") {
                cout << cmd << " is a shell builtin" << endl;
                continue;
            }

            const char *pathEnv = getenv("PATH");
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

                    string fullPath = dir + "/" + cmd;
                    if (filesystem::exists(fullPath)) {
                        auto perms = filesystem::status(fullPath).permissions();
                        if ((perms & filesystem::perms::owner_exec) != filesystem::perms::none) {
                            cout << cmd << " is " << fullPath << endl;
                            found = true;
                            break;
                        }
                    }
                }
            }

            if (!found)
                cout << cmd << ": not found" << endl;
        }

        else if (command.rfind("echo ", 0) == 0) {
            cout << command.substr(5) << endl;
        }

        else {
            
            string cmd;
            stringstream ss(command);
            ss >> cmd;

            const char *pathEnv = getenv("PATH");
            bool found = false;

            if (pathEnv) {
                string path(pathEnv);
                path.push_back(':');
                int prev = 0;

                for (int i = 0; i < path.size(); i++) {
                    if (path[i] == ':') {
                        string dir = path.substr(prev, i - prev);
                        prev = i + 1;

                        if (dir.empty()) continue;

                        string fullPath = dir + "/" + cmd;
                        if (filesystem::exists(fullPath)) {
                            auto perms = filesystem::status(fullPath).permissions();
                            if ((perms & filesystem::perms::owner_exec) != filesystem::perms::none) {
                                found = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (found) {
                system(command.c_str());
            } else {
                cout << cmd << ": command not found" << endl;
            }
        }
    }
}
