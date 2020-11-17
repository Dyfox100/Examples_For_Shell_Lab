// header file for i/o functions like printf or sprintf. stdio stands for standard input output.
#include <stdio.h>

// these two header files declare the pid type, and the wait functions (among other things).
#include <sys/types.h>
#include <sys/wait.h>

// header file for unix standard functions, macros, and constants.
// things like sleep, fork, execve, getpid, getpgid, etc...
// environ is also declared in this. environ is a pointer to an array of strings that secify your environment. 
// envrion has things like username, current directory, etc... See https://man7.org/linux/man-pages/man7/environ.7.html
#include <unistd.h>

// environ mut be declared locally too.
extern char** environ;

// main function has the number of command line args passed to it in argc
// and the string form of the command line args in argv.
int main (int argc, char** argv) {
    pid_t pid;
    int status;
    // fork creates child process. Called once and returns twice.
    // returns 0 if this is the child process, reutrns child's pid to parent, and
    // returns negative value if error occured.
    if ((pid = fork()) < 0) {
        // negative return code from fork means error occured and child not created.
        printf("Error forking process");
        return -1;
    }
    else if (pid == 0) {
        // we're in the child process
        execve("./sleep_5.o", argv + 1, environ);
        // see https://linux.die.net/man/2/execve for info on execve
    }
    else {
        // we're in the parent
        // wait for child to complete
        // we've got the child's pid in pid, so wait for that pid to complete.
        // child is reapead by waiting for it to complete.
         waitpid(pid, &status, 0);
         // see https://linux.die.net/man/2/waitpid
         printf("parent complete\n");
    }
}