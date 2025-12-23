#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
vector<string> parseArgs(const string &line) {
    vector<string> args;
    string cur;
    bool inQuotes = false;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '\'') {
            inQuotes = !inQuotes;
        }
        else if (isspace(c) && !inQuotes) {
            if (!cur.empty()) {
                args.push_back(cur);
                cur.clear();
            }
        }
        else {
            cur.push_back(c);
        }
    }

    if (!cur.empty())
        args.push_back(cur);

    return args;
}

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

        else if (command.rfind("echo", 0) == 0) {
            auto args = parseArgs(command);

            for (int i = 1; i < args.size(); i++) {
                cout << args[i];
                if (i + 1 < args.size()) cout << " ";
            }
                cout << endl;
}


        else {
            
            auto args=parseArgs(command);
            string cmd=args[0];

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
