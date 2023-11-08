#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {

pid_t tempPid = getpid();

printf("This is the parent process (PID=%d) \n", tempPid);

for (int i = 0; i < 4; i++) {

tempPid = getpid();

fork();

printf("This is the child process no.%d  process (PID=%d) \n", i+1, tempPid);
}
exit(EXIT_SUCCESS);
}
