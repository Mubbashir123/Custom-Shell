#include <bits/stdc++.h>
#include <sys/stat.h>
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
        char *pathenv = getenv("PATH");
        if (pathenv == NULL)
        {
          cout << cmd << ": not found " << endl;
          continue;
        }
        string path(pathenv);
        bool f = false;

        char sep = ';'; // seperator for windows
        int st = 0;
        for (int i = 0; i <= path.size(); i++)
        {
          if (i == path.size() || path[i] == sep)
          {
            string dir = path.substr(st, i - st);
            st = i + 1;

            if (dir.empty())
              continue;

            string fullPath = dir + "/" + cmd;

            struct stat sb;
            if(stat(fullPath.c_str(), &sb) == 0 && (sb.st_mode & S_IXUSR))
            {
              cout << cmd << " is " << fullPath << endl;
              f = true;
              break;
            }
          }
        }

        if (!f)
        {
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
