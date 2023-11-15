#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


#define MAX_COMMAND_SIZE 1024

void myhistory(int n) {
	FILE *file  = fopen("history.txt", "r");
	if(file != NULL) {
		char buffer[MAX_COMMAND_SIZE];
		int count = 0;

		//conta número de comandos logados
		while (fgets(buffer, sizeof(buffer),file) != NULL) {
			count++;
		}
		
		//Coloca o pointer para o inicio do ficheiro  
		rewind(file);

		//ignora as primeiras linhas de comando
		for (int i = 0; i < count -n; i++) {
			fgets(buffer,sizeof(buffer),file);
		}

		while(fgets(buffer,sizeof(buffer),file) != NULL) {
			printf("%s", buffer);
		}

		fclose(file);
	}

	else {
		printf("It was not possible to read from history file");		
		}

}

void add_to_history(const char *command) {
    FILE *file = fopen("history.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", command);
        fclose(file);
    } else {
        perror("Error writing to history.txt");
    }
}



int main(int argc, char* argv[]) {

	for( ; ; ) {
	/* give prompt, read command and null terminate it */
		fprintf(stdout, "$ ");
		char buf[1024];
		char* command = fgets(buf, sizeof(buf), stdin);
		if(command == NULL)
		break;
		command[strlen(buf) - 1] = '\0';
		if (strcmp(command, "exit") == 0) {
			exit(EXIT_SUCCESS);
	}
		 if (strncmp(command, "myhistory", 9) == 0) {
            char *token = strtok(command, " ");
            token = strtok(NULL, " ");
            if (token != NULL) {
                int n = atoi(token);
                myhistory(n);
            } else {
                printf("Invalid usage of myhistory. Usage: myhistory <n>\n");
            }
            continue;
        }

		add_to_history(command);
	/* call fork and check return value */
	pid_t pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}


	if(pid == 0) {

		/* child */

		char *token = strtok(command, " ");
		char *args[1024];
		int i = 0;

		while(token != NULL) {
			args[i++] = token;
			token  = strtok(NULL, " ");
		}
		args[i] = NULL;

		int retv = execvp(args[0], args);
		if(retv == -1) {
		perror("execvp");
		exit(EXIT_FAILURE);
	}

	}
	/* shell waits for command to finish before giving prompt again */
	int retv = waitpid(pid, NULL, 0);
	if (retv == -1) {
		perror("waitpid");
		exit(EXIT_FAILURE);	
	}

}
exit(EXIT_SUCCESS);
}
