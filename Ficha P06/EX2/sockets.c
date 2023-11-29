#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {


    //See if it has an argument with the right name and writes a message if it doesnt
    if(argc != 2) {
        fprintf(stderr, "Missing: %s text.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }


//buffer size of 1024 chars
char buf[1024];

//array of sockets 
int sockets[2], retv;

//creation of pair of sockets
//AFUNIX local socket connection
// STOCK_STREAM passes the message as it is
retv = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);


//error if socket is not created
if (retv == -1) { perror("socketpair"); exit(EXIT_FAILURE); }
retv = fork();

//Error if fork didnt work
if (retv == -1) { perror("fork"); exit(EXIT_FAILURE); }

// if socket works
if (retv > 0) { /* parent */

    //message to pass
    //char string1[] = "In every walk with nature...";


    close(sockets[1]);


    //abre um ficheito de texto em modo de leitura
    FILE* file = fopen(argv[1],"r");

    //se retornar null houve erro na abertura e faz print de uma mensagem
        if(file == NULL) {            printf("error: could not open file");
        exit(EXIT_FAILURE);
    }

    int nchars = fread(buf,sizeof(char),1024,file);


    //as a socket is bidirectional you can read or write
    
    //write(sockets[0], string1, sizeof(string1));
    //read(sockets[0], buf, sizeof(buf));

    while( nchars > 0) {
        write(sockets[0], buf, nchars);
        read(sockets[0], buf, nchars);
        printf("message from %d-->%s\n", getpid(), buf);
        nchars = fread(buf,sizeof(char),1024,file);

    }
    //write(sockets[0], string1, sizeof(string1));
    //read(sockets[0], buf, sizeof(buf));



    //printf("message from %d-->%s\n", getpid(), buf);
    close(sockets[0]);

    //Wait for the child process to terminate
    retv = wait(NULL);
    //if parent process ends before child it gives an error
    if (retv == -1) { perror("wait"); exit(EXIT_FAILURE); }
}
else { /* child */


//another message to pass
char string2[] = "...one receives far more than he seeks.";

close(sockets[0]);

read(sockets[1], buf, sizeof(buf));

printf("message from %d-->%s\n", getppid(), buf);

write(sockets[1], string2, sizeof(string2));

close(sockets[1]);
exit(EXIT_SUCCESS);

}
}