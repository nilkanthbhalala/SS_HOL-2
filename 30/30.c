#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    char *str = (char *)shmat(shmid, (void *)0, 0);
    strcpy(str, "Hello Shared Memory");

    printf("Data written: %s\n", str);
    shmdt(str);

    str = (char *)shmat(shmid, (void *)0, SHM_RDONLY);

    printf("Data read (read-only): %s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

/*

nilkanth@zuxxy: gcc 30.c && ./a.out
Data written: Hello Shared Memory
Data read (read-only): Hello Shared Memory
*/
