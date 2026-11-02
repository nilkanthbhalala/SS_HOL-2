#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

#define SEM_NAME "/printer_sem"

int main()
{
    sem_t *sem;

    //2 printers
    sem = sem_open(SEM_NAME, O_CREAT, 0644, 2);

    printf("Process %d: waiting for a printer...\n", getpid());
    sem_wait(sem);

    printf("Process %d: got a printer! Printing...\n", getpid());
    sleep(10);

    printf("Process %d: done printing, releasing printer.\n", getpid());
    sem_post(sem);

    sem_close(sem);
    return 0;
}
/*
gcc 32c.c && ./a.out
Process 200993: waiting for a printer...
Process 200993: got a printer! Printing...
Process 200993: done printing, releasing printer.
*/