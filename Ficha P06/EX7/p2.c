
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
    
    //abre o pipe com permissão para ler apenas
    int fd = open(myfifo,O_RDONLY);
    
    //Se falha a abertura notifica de erro de abertura
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }
    
    //executa a leitura enquanto o terminal estiver a executar
    while (1) {
        char text[BUF_SIZE];
        read(fd, text, BUF_SIZE);
        printf("%s", text);
    }
    
    //fecha o pipe
    close(fd);
    
    exit(EXIT_SUCCESS);

    return 0;

}