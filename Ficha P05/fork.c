#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
pid_t parent_pid = getpid();

printf("Processo Pai (PID = %d) \n", parent_pid);



fork();

pid_t child_pid = getpid();
printf("Processo filho 1 (PID = %d) \n", child_pid);

fork();

child_pid = getpid();
printf("Processo filho 2 (PID = %d) \n", child_pid);
fork();
child_pid = getpid();

printf("Processo filho 3 (PID = %d) \n", child_pid);

exit(EXIT_SUCCESS);
}
