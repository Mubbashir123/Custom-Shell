#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;
void runCommand(vector<string>args)
{
    auto it=find(args.begin(),args.end(),">");
    if(it!=args.end())
    {
        int index=distance(args.begin(),it);
        if(index+1<args.size())
        {
            string filename=args[index+1];
            int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            
            if(fd<0)
            {
                perror("Failed to open file");
                exit(1);
            }
            dup2(fd,STDOUT_FILENO);
            close(fd);

            args.erase(it,it+2);

        }
        
    }
    vector<char *> c_args;
    for (auto &a : args)
        c_args.push_back(&a[0]);
    c_args.push_back(NULL);
    execvp(c_args[0], c_args.data());

    perror("Exec failed");
    exit(1);
}
vector<string> parseArgs(const string &line)
{
    vector<string> args;
    string cur;
    bool inQuotes = false;

    for (int i = 0; i < line.size(); i++)
    {
        char c = line[i];

        if (c == '\'')
        {
            inQuotes = !inQuotes;
        }
        else if (isspace(c) && !inQuotes)
        {
            if (!cur.empty())
            {
                args.push_back(cur);
                cur.clear();
            }
        }
        else
        {
            cur.push_back(c);
        }
    }

    if (!cur.empty())
        args.push_back(cur);

    return args;
}

int main()
{
    while (true)
    {
        cout << "$ ";
        string command;
        // getline(cin, command);

        if (!getline(cin, command))
            break;

        if (command.empty())
            continue;

        auto args = parseArgs(command);
        if (args.empty())
            continue;

        if (args[0] == "exit")
            break;

        else if (args[0] == "cd")
        {
            if (args.size() < 2)
            {
                chdir(getenv("HOME"));
            }
            else
            {
                if (chdir(args[1].c_str()) != 0)
                {
                    perror("cd failed");
                }
            }
            continue;
        }

        else
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Fork failed");
            }
            else if (pid == 0)
            {

                runCommand(args);
            }
            else
            {
                wait(NULL);
            }
        }
    }
}
