#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);

    puts("SIGINT is ignored");
    // raise(SIGINT);
    while(1){
        sleep(3);
        break;
    }

    signal(SIGINT, SIG_DFL);
    puts("Default SIGINT action restored; raising SIGINT now");
    sleep(10);

    return 0;
}

/*
nilkanth@zuxxy:gcc 9.c && ./a.out 
SIGINT is ignored
^C^C^C^C   -->Nothing happened 
Default SIGINT action restored; raising SIGINT now
^C
*/
