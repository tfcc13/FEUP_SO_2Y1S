#include <stdio.h>
#include <stdlib.h>

int* f() {
int* x = (int*)malloc(sizeof(int));
return x;
}

int main() {
printf("value: %d\n", g(f,2));
return 0;
}
