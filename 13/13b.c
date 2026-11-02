#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PID\n", argv[0]);
        return 2;
    }

    char *end;
    long value = strtol(argv[1], &end, 10);

    kill( (pid_t)value, SIGSTOP);
    printf("Sent SIGSTOP to process %ld\n", value);
    return 0;
}

/*

nilkanth@zuxxy: gcc 13b.c && ./a.out 174643
Sent SIGSTOP to process 174643
*/
