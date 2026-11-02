#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main()
{
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0)
    {
        printf("Max open files (soft limit): %ld\n", limit.rlim_cur);
        printf("Max open files (hard limit): %ld\n", limit.rlim_max);
    }

    int channel[2];
    pipe(channel);

    int size = fcntl(channel[0], F_GETPIPE_SZ);
    if (size == -1)
        perror("F_GETPIPE_SZ");
    else
        printf("Pipe capacity: %d bytes\n", size);

    close(channel[0]);
    close(channel[1]);
    return 0;
}

/*

nilkanth@zuxxy: gcc 23.c && ./a.out 
Max open files (soft limit): 524288
Max open files (hard limit): 524288
Pipe capacity: 65536 bytes
*/
