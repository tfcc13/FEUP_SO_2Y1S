#include <stdio.h>

int* f() {
int x;
return &x;
}

int main() {
printf("value: %d\n", g(f,2));
return 0;
}
