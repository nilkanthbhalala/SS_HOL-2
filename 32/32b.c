#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SHM_NAME "/ticket_shm"
#define SEM_NAME "/ticket_mutex"

typedef struct
{
    int ticket_no;
} database_t;

int main()
{
    int shm_fd;
    database_t *db;
    sem_t *mutex;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(database_t));

    db = mmap(0, sizeof(database_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);

    printf("Process %d: waiting to enter critical section...\n", getpid());
    sem_wait(mutex);

    printf("Process %d: inside critical section (holding lock)\n", getpid());
    printf("Process %d: Current ticket number = %d\n", getpid(), db->ticket_no);

    sleep(10);

    db->ticket_no++;
    printf("Process %d: New ticket number written = %d\n", getpid(), db->ticket_no);

    printf("Process %d: leaving critical section...\n", getpid());
    sem_post(mutex);

    munmap(db, sizeof(database_t));
    close(shm_fd);
    sem_close(mutex);

    return 0;
}

/*
nilkanth@zuxxy:$ gcc 32b.c && ./a.out
Process 200624: waiting to enter critical section...
Process 200624: inside critical section (holding lock)
Process 200624: Current ticket number = 1
Process 200624: New ticket number written = 2
Process 200624: leaving critical section...
*/