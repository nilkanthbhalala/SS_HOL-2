#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void handle_signal(int signo)
{
    const char message[] = "\nCaught SIGINT (Ctrl+C pressed)\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    _exit(0);
}

int main(void)
{
    signal(SIGINT, handle_signal);
    // raise(SIGINT);
    while (1)
    {
        printf("Working...\n");
        sleep(2);
    }
    return 0;
}

/*

nilkanth@zuxxy: gcc 8b.c && ./a.out
Working...
Working...
^C
Caught SIGINT (Ctrl+C pressed)
*/
