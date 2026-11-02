#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        printf("Child %ld is sending SIGKILL to parent %ld\n", (long)getpid(), (long)getppid());
        fflush(stdout);

        kill(getppid(), SIGKILL);
        sleep(1);
        printf("Child is now orphaned; new parent is %ld\n", (long)getppid());
        return 0;
    }
    for (;;)
        pause();
}

/*

nilkanth@zuxxy: gcc 12.c && ./a.out 
Child 173881 is sending SIGKILL to parent 173880
Killed                     ./a.out
Child is now orphaned; new parent is 4405
*/