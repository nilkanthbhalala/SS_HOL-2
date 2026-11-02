#include <signal.h>
#include <stdio.h>
#include<unistd.h>

int main(void)
{
    struct sigaction action = {0};
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    
    puts("SIGINT is ignored");
    // raise(SIGINT);
    while(1){
        sleep(3);
        break;
    }

    action.sa_handler = SIG_DFL;
    sigaction(SIGINT, &action, NULL);
    puts("Default SIGINT action restored; raising SIGINT now");
    sleep(10);

    return 0;
}

/*
nilkanth@zuxxy: gcc 11.c && ./a.out 
SIGINT is ignored
^C^C^C^C^C^C^C
Default SIGINT action restored; raising SIGINT now
^C
*/
