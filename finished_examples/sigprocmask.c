#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// signal handler for demonstrating that only one signal is queued.
// again, don't use printf in signal handlers in real life. Just for demonstrations.
void sig_handler(int signum) {
    printf("Signal number %d executed!", signum);
    return;
}

int main () {
    // initilize empty signal set. Think of it as a bit mask for every signal. 
    sigset_t sig_set;
    sigemptyset(&sig_set);
    signal(SIGTSTP, sig_handler);
    // Add the signal(s) we'd like to not recieve to the set. SIGTSTP is a macro defined in signal.h.
    // It is the signal number of the sigtstp signal.
    sigaddset(&sig_set, SIGTSTP);
    // sigprocmask applies the action designated by the first parameter to the signals designated by the 
    // second argument. The third argument is a place to store the prior signal set and masks in. 
    // We don't really care about what signals were blocked before, so we just pass in NULL.
    // SIG_BLOCK is another macro defined in signal.h. The SIG_BLOCK constant tells sigprocmask to 
    // block signals.
    sigprocmask(SIG_BLOCK, &sig_set, NULL);

    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Forking Error, Process Termianted!\n\n");
        exit(-1);
    }
    else if (pid == 0) {
        // in child process
        for(int i = 0; i < 5; i++) {
            sleep(1);
            printf("Still In Child Process. Not Killed Or Stopped!\n\n");
        }
        return 0;
    }
    else {
        // in parent process
        // Wait for child to complete, then unblock signal.
        // Important to remember especially if blocking a signal you'll need to exit the program etc...
        // SIG_UNBLOCK is antoher macro defined in signal.h
        int child_status;
        wait(&child_status);
        printf("Child returned with status: %d\n\n", child_status);
        sigprocmask(SIG_UNBLOCK, &sig_set, 0);
        return 0;
    }
}