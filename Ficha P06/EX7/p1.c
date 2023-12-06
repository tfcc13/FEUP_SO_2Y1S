#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 128

int main(int argc, char* argv[]) {

    //Cria uma string   com o path desejado
    char* myfifo = "/tmp/myfifo";
    
    //apaga se existe o ficheiro
    unlink(myfifo);

    //Cria um pipe com o nome no path especificado anteriormente 
    int rv = mkfifo(myfifo, 0666);
    
    //se não cria, avisa de erro
    if (rv == -1) { perror("mkfifo"); exit(EXIT_FAILURE); }
    
    // abre o pipe criado, com permissao para escrever apenas
    int fd = open(myfifo, O_WRONLY);
    
    //Se falha a abertura notifica de erro de abertura
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }
    
    //executa a escrita enquanto o terminal estiver a executar
    while (1) {
        char text[BUF_SIZE];
        fgets(text, BUF_SIZE, stdin);
        write(fd, text, strlen(text)+1);
    }

    //fecha o pipe
    close(fd);

    exit(EXIT_SUCCESS);

    return 0;
}