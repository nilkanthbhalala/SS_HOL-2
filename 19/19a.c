#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    const char *path = "fifo_mknod";

    mknod(path, S_IFIFO | 0660, 0);
    printf("FIFO named pipe created using mknod: %s\n", path);
    return 0;
}

/*

nilkanth@zuxxy: gcc 19a.c && ./a.out 
FIFO named pipe created using mknod: fifo_mknod
*/
