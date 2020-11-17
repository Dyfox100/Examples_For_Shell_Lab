// header file for i/o functions like printf or sprintf. stdio stands for standard input output.
#include <stdio.h>

// this header declares functionality for registering / using signal handlers.
#include <signal.h>

// header file for unix standard functions, macros, and constants.
// things like sleep, fork, execve, getpid, getpgid, etc...
// environ is also declared in this. environ is a pointer to an array of strings that secify your environment. 
// envrion has things like username, current directory, etc... See https://man7.org/linux/man-pages/man7/environ.7.html
#include <unistd.h>

int main (int argc, char** argv) {
    return 0;
}