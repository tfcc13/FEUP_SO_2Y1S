#include <stdio.h>

void f() {
int x;
g(&x);
}

int main() {
printf("value: %d\n", g(f,2));
return 0;
}
