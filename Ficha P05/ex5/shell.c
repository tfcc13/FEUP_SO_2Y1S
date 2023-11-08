#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
for( ; ; ) {
/* give prompt, read command and null terminate it */
fprintf(stdout, "$ ");
char buf[1024];
char* command = fgets(buf, sizeof(buf), stdin);
if(command == NULL)
break;
command[strlen(buf) - 1] = '\0';
/* call fork and check return value */
pid_t pid = fork();
if(pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if(pid == 0) {
/* child */
int retv = execlp(command, command, (char *)0);
if(retv == -1) {
perror("execlp");
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
