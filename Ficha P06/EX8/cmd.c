#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1


char* cmd1[] = {"ls", "-l", NULL};
char* cmd2[] = {"wc", "-l", NULL};
int main (int argc, char* argv[]) {
int fd[2];
pid_t pid;
if (pipe(fd) < 0) {
    perror("error: failed to make pipe ");
    exit(EXIT_FAILURE);
}
if ((pid = fork()) < 0) {
/* fork error */
    
    perror("error: failed to make fork ");
    exit(EXIT_FAILURE);
}
if (pid > 0) {

close(fd[READ_END]);
dup2(fd[WRITE_END], STDOUT_FILENO);
close(fd[WRITE_END]);

// parent writes to the pipe
if (execvp(cmd1[0], cmd1) < 0) {
/* exec error */
    perror("execvp cmd1 error");
    exit(EXIT_FAILURE);

}
} else {
// stdout to pipeclose(fd[WRITE_END]);

dup2(fd[READ_END], STDIN_FILENO);

close(fd[READ_END]);

if (execvp(cmd2[0], cmd2) < 0) {
/* exec error */
    perror("error: failed execvp cmd2");
    exit(EXIT_FAILURE);
}

// stdin from pipe
}
}