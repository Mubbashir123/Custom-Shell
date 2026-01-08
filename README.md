# Custom Linux Shell 

A POSIX-compliant command-line shell built from scratch in C++. 

This project was developed to understand the fundamental concepts of Operating Systems, focusing on process management, inter-process communication (IPC), and file descriptor manipulation without relying on high-level abstractions.

## 🚀 Features

* **Command Execution:** Runs standard Linux commands (e.g., `ls`, `grep`, `sleep`) using the `fork()` and `execvp()` mechanism.
* **Pipelines (`|`):** Supports chaining commands (e.g., `ls -l | grep main`) using kernel-level pipes.
* **I/O Redirection (`>`):** Redirects standard output to files (e.g., `echo "Hello" > out.txt`).
* **Built-in Commands:** Implementation of `cd` (Change Directory) and `exit`.
* **Signal Handling:** Proper process termination and zombie process prevention.

## 🛠️ Installation & Usage

### Prerequisites
You need a C++ compiler (`g++`) and the Readline library installed.

**On Ubuntu/Debian/WSL:**
```bash
sudo apt update
sudo apt install g++ libreadline-dev
