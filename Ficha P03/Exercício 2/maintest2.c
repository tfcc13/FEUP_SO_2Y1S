#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
char* p1 = (char*)malloc(strlen(argv[1]));

strcpy(p1, argv[1]);


for (unsigned x = 0; p1[x] != '\0'; x++) {

	p1[x] = tolower(p1[x]);

}

printf("p1 holds:%s\n", p1);

exit(EXIT_SUCCESS);
}
