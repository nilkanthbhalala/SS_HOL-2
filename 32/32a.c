#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>

#define SEM_NAME "/ticket_mutex"
#define DB_FILE "database"

int main()
{
    sem_t *mutex;
    int fd;

    struct
    {   
        int ticket_no;
    }database;

    mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);

    printf("Process %d: waiting to enter critical section...\n", getpid());
    sem_wait(mutex);

    printf("Process %d: inside critical section (holding lock)\n", getpid());
    fd = open(DB_FILE, O_RDWR);
    read(fd, &database, sizeof(database));
    printf("Process %d: Current ticket number = %d\n", getpid(), database.ticket_no);

    sleep(10);
    database.ticket_no++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &database, sizeof(database));
    fsync(fd);

    printf("Process %d: New ticket number written = %d\n", getpid(), database.ticket_no);

    close(fd);

    printf("Process %d: leaving critical section...\n", getpid());
    sem_post(mutex);

    sem_close(mutex);
    return 0;
}

/*
Terminal:1 
gcc 32a.c && ./a.out
Process 200313: waiting to enter critical section...
Process 200313: inside critical section (holding lock)
Process 200313: Current ticket number = 3
Process 200313: New ticket number written = 4
Process 200313: leaving critical section...


Terminal:2 
gcc 32a.c && ./a.out
Process 200349: waiting to enter critical section...
Process 200349: inside critical section (holding lock)
Process 200349: Current ticket number = 4
Process 200349: New ticket number written = 5
Process 200349: leaving critical section...

*/