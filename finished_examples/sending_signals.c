#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_tstp(int signum) {
    printf("Sigtstp recieved, and my process number is: %d\n", getpid());
    return;
}
// example of sending signals using kill
int main () {
    signal(SIGTSTP, sig_tstp);
    pid_t pid;
    pid = fork();
    // really should handle negative pid errors here.

    if (pid == 0) {
        printf("\nI'm the child! And my pid is: %d\n", getpid());
        while(1) {
            sleep(1);
        }
        return 0;
    }
    else {
        printf("\nI'm the parent! And my pid is: %d\n", pid);
        sleep(1);
        // using kill function to send signal. See https://man7.org/linux/man-pages/man2/kill.2.html
        kill(pid, SIGTSTP);
        return 0;
    }
}