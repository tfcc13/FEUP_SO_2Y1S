#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void handler1() { printf("caught SIGUSR1\n"); }

static void handler2() { printf("caught SIGUSR2\n"); }

static void handler3() { printf("Program running in the background \n");}

static void handler4() {printf("Program stopped \n");}

static void handler5() {printf("User logged out \n");}

//static void handler6() {printf("Terminated the process \n");}

int main(int argc, char* argv[]) {

    printf("my PID is %d\n", getpid());

    if (signal(SIGUSR1, handler1) == SIG_ERR) {
        fprintf(stderr, "Can’t catch SIGUSR1: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, handler2) == SIG_ERR) {
        fprintf(stderr, "Can’t catch SIGUSR2: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(signal (SIGTSTP, handler3) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGTSTOP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }


    if(signal (SIGINT, handler4) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(signal (SIGHUP, handler5) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGHUP: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    /*
    if(signal (SIGKILL, handler6) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGKILL: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    */

    /* stick around ... */
    for ( ; ; )
        pause();        
    return 0;
}