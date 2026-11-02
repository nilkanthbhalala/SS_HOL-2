#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void handle_stop(int signo)
{
    (void)signo;
    puts("SIGSTOP caught form Program 13b.c");
    _exit(1);
}

int main()
{
    struct sigaction action = {0};
    action.sa_handler = handle_stop;
    sigemptyset(&action.sa_mask);

    printf("Process ID: %ld\n", (long)getpid());
    sigaction(SIGSTOP, &action, NULL);
    
    for (;;) ;
    fflush(stdout);
}

/*

nilkanth@zuxxy: gcc 13a.c && ./a.out 
Process ID: 169157
SIGSTOP cannot be caught (sigaction: Invalid argument)
*/
