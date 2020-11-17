// header file for i/o functions like printf or sprintf. stdio stands for standard input output.
#include <stdio.h>

// these two header files declare the pid type, and the wait functions (among other things).
#include <sys/types.h>
#include <sys/wait.h>

// this header declares functionality for registering / using signal handlers.
#include <signal.h>

// header file for unix standard functions, macros, and constants.
// things like sleep, fork, execve, getpid, getpgid, etc...
// environ is also declared in this. environ is a pointer to an array of strings that secify your environment. 
// envrion has things like username, current directory, etc... See https://man7.org/linux/man-pages/man7/environ.7.html
#include <unistd.h>

// environ mut be declared locally too.
extern char** environ;

void sigchild_handler(int signum) {
    int status;
    pid_t pid;
    // reaps child. -1 as pid tells waitpid to wait untill a child is ready to be reaped.
    // WUNTRACED tells waitpid to also return if a child is stopped, 
    // not just terminated or exited.
    // Putting this together, waitpid(-1, &status, WUNTRACED) will
    // return the pid (and set the status) of a stopped, exited, or
    // terminated child process (as long as it is already done). 
    pid = waitpid(-1, &status, WUNTRACED);
    printf("\nChild process exited with error number %d\n\n", status);
    return;
}

// main function has the number of command line args passed to it in argc
// and the string form of the command line args in argv.
int main (int argc, char** argv) {
    pid_t pid;
    int status;
    // signal registers a function to the signla specified in the first arg.
    // the SIGCHILD constant is defined in the signal header 
    // and is the signal number of the sig child signal.
    // sigchild is sent when a child process completes.
    signal(SIGCHLD, sigchild_handler);
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
        // don't wait for child to complete, it's running in the background.
        for (int i = 0; i < 10; i++) {
            printf("I'm doing something else. Iteration: %d\n", i);
            //fflush(stdout);
            sleep(1);
        }
    }
}

