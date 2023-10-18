#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

char* p1 = (char*)malloc(strlen(argv[1]));

char* p2 = (char*)malloc(strlen(argv[2]));


strcpy(p1, argv[1]);
strcpy(p2, argv[2]);

char* ptr = strstr(argv[2],argv[1]);


if (ptr != NULL) {

printf("%s ocorreu em  %s \n", p1,p2); 

}

else {
	printf("%s nao ocorreu em  %s \n", p1,p2); 

}

return 0;

}
