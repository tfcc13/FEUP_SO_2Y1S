#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1



int main (int argc, char* argv[]) {

    if(argc != 2 ) {
        fprintf(stderr,"Usage;: %s \" command1 | command2 \"\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    char* command = argv [1];

    //Cria uma string   com o path desejado
    char* myfifo = "/tmp/myfifo";
    
    //apaga se existe o ficheiro
    unlink(myfifo);

    mkfifo(myfifo, 0666);


    pid_t pid = fork();

    if(pid == -1) {
        perror("error: fork failed");
        exit(EXIT_FAILURE);
    }

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