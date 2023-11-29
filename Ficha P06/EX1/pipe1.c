#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define LINESIZE 256


int main(int argc, char* argv[]) {



    //See if it has an argument with the right name and writes a message if it doesnt
    if(argc != 2) {
        fprintf(stderr, "Missing: %s text.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //cria um array tamanho 2
    int fd[2];
    //cria um processo pid
    pid_t pid;

    //se nao criar pid da erro
    if (pipe(fd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }

    //Se processo filho nao for criado da erro
    if ((pid = fork()) == -1) { perror("fork"); exit(EXIT_FAILURE); }


    //Processo pai
    if (pid > 0) { /* parent */
        
        //char line[LINESIZE] = "Lorem ipsum dolor sit amet ...";
        
        //fecha o processo pai, se existir anteriormente
        close(fd[0]);

        //abre um ficheito de texto em modo de leitura
        FILE* file = fopen(argv[1],"r");

        //se retornar null houve erro na abertura e faz print de uma mensagem
        if(file == NULL) {
            printf("error: could not open file");
            exit(EXIT_FAILURE);
        }


        //cria uma array com otamanho do buffer de leitura pre definido
        char buffer[LINESIZE];

        //inicia os dados de leitura
        //le o buffer(onde é guardado os dados de leitura), sizeof(char) indica o tamanho de cada elemento a ser lido (1 byte de cada vez)
        //O linesize indica o numero de elementos a ler de cada vez, e o file é o pointer para o ficheiro que esta a ser lido
        int nchars = fread(buffer,sizeof(char),LINESIZE,file);

    // enquanto nao terminar de ler o ficheiro, escreve oara o pipe os dados e leitura
        while(nchars>0) {
            write(fd[1],buffer,nchars);
            nchars = fread(buffer,sizeof(char),LINESIZE,file); //atualiza os dados de leitura
        }



        //write(fd[1], line, strlen(line));

        fclose(file);
        close(fd[1]);

        //espero pelo processo filho terminar, se terminar antes do child da erro
        if ( wait(NULL) == -1) { perror("wait"); exit(EXIT_FAILURE); }

        exit(EXIT_SUCCESS);

    } else { /* child */

        //array de armazenamento de dados passados pelo pipe    
        char line[LINESIZE];
        
        //numero de caracteres lido pelo pipe
        int nchars;
        close(fd[1]);

        //int nbytes = read(fd[0], line, LINESIZE);
        
        //write(STDOUT_FILENO, line, nbytes);

        //le os caracteres do pipe fd[0] e guarda no buffer line, com tamanho LINESIZE de cada vez 
        nchars = read(fd[0],line,LINESIZE);

        //repete o processo até terminar de ler todos os dados do pipe
       while(nchars>0) {
           write(STDOUT_FILENO,line,nchars);
           nchars = read(fd[0],line,LINESIZE);
        }

        close(fd[0]);
        exit(EXIT_SUCCESS);
}
    return 0;
}