#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    const char *path = "fifo_mkfifo";
    mkfifo(path, 0660);
    printf("Created FIFO: %s\n", path);
    return 0;
}

/*

nilkanth@zuxxy: gcc 19b.c && ./a.out 
Created FIFO: fifo_mkfifo
*/

/*
nilkanth@zuxxy: strace -e trace=mknod,mknodat mknod fifo_mknod_strace p
mknodat(AT_FDCWD, "fifo_mknod_strace", S_IFIFO|0666) = 0
+++ exited with 0 +++

nilkanth@zuxxy: strace -e trace=mknod,mknodat mkfifo fifo_mkfifo_strace
mknodat(AT_FDCWD, "fifo_mkfifo_strace", S_IFIFO|0664) = 0
+++ exited with 0 +++

mkfifo is preferable for FIFO creation because it directly expresses the intended operation. Both approaches may ultimately use the same kernel node-creation mechanism, so this trace alone does not establish that one is faster
*/