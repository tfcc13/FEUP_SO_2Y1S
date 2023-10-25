#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
struct stat info;
if (argc < 2) {
fprintf(stderr, "usage: %s file\n", argv[0]);
exit(EXIT_FAILURE);
}

int counter_size = 0;
int counter_blocks = 0 ;

for (int i = 1; i < argc; i++) {
int retv = stat(argv[i], &info);
if (retv == -1) {
fprintf(stderr, "fsize: Can’t stat %s\n", argv[i]);
exit(EXIT_FAILURE);
}
printf("%s size: %d bytes, disk_blocks: %d\n",
argv[i], (int)info.st_size, (int)info.st_blocks);
counter_size += (int)info.st_size;
counter_blocks += (int)info.st_blocks;
}
printf("total size: %d bytes,  counter_size, total disc blocks: %d\n", counter_size, counter_blocks);
exit(EXIT_SUCCESS);
} 
