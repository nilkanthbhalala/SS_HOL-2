#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SEM_NAME "/ticket_mutex"

int main()
{
    if (sem_unlink(SEM_NAME) == 0)
    {
        printf("Semaphore %s removed successfully.\n", SEM_NAME);
    }
    return 0;
}

/*
gcc 32d.c && ./a.out
Semaphore /ticket_mutex removed successfully.
*/