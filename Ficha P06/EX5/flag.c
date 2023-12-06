#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int flag = 1;

static void handler1() { 
    printf("caught SIGINT\n");
    flag = 0;
 }

int main(int argc, char* argv[]) {

printf("my PID is %d\n", getpid());
/* enter potentially infinite loop ... */

if(signal (SIGINT, handler1) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

while(flag)

pause();

exit(EXIT_SUCCESS);

}