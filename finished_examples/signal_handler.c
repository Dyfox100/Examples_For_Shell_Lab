// header file for i/o functions like printf or sprintf. stdio stands for standard input output.
#include <stdio.h>

// this header declares functionality for registering / using signal handlers.
#include <signal.h>

// header file for unix standard functions, macros, and constants.
// things like sleep, fork, execve, getpid, getpgid, etc...
// environ is also declared in this. environ is a pointer to an array of strings that secify your environment. 
// envrion has things like username, current directory, etc... See https://man7.org/linux/man-pages/man7/environ.7.html
#include <unistd.h>

// run is a flag telling the program to continue running.
// We need it to be able to stop the progam from the sigtstp handler.
// since we are overwriting the behaviour of sigtstp, it won't stop the 
// program unless we tell it to. It has to be global so it can be accessed in the 
// hanlder and the main function.
// The sig_atomic_t datatype is atomic with respect to signals, meaning that
// another signal couldn't interupt setting run to 0 in the handler.
// Volatile tells us that this variable may change in another function / file / whatever. 
// This prevents the compiler from optimizing run to just always be a constant 1 in the main function.
volatile sig_atomic_t run;

void sigtstp_handler(int signum) {
    // You really shouldn't use printf inside signal hanlders.
    // It is not a safe asynchronous function. 
    // See the section on "Signal Handling and Nonreentrant Functions"
    // at ftp://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_24.html
    // non-reentrant means that the function can't safely 
    // restart where it stopped if it is interrrupted during execution.
    // This is just for teaching purposes. 
    printf("\nI was stopped by SIGTSTP aka crtl-z!\n");
    run = 0;
    return;
}

int main (int argc, char** argv) {
    run = 1;
    // signal registers a function to the signla specified in the first arg.
    // the SIGCHILD constant is defined in the signal header 
    // and is the signal number of the sig child signal.
    // sigchild is sent when a child process completes.
    signal(SIGTSTP, sigtstp_handler);
    while(run) {
        printf("I'm not stopped\n");
        sleep(1);
    }
    return 0;
}
