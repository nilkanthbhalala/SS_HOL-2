#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    key_t key = ftok("smfile", 65);
    int id = semget(key, 1, IPC_CREAT | 0660);

    union semun 
    { 
        int val; 
        struct semid_ds *buf; 
        unsigned short *array; 
    } value;

    value.val = 1;
    semctl(id, 0, SETVAL, value);
    printf("Binary semaphore ID: %d, value: %d\n", id, value.val);
    return 0;
}

/*

nilkanth@zuxxy: gcc 31a.c && ./a.out
Binary semaphore ID: 0, value: 1

gcc 31a.c && ./a.out
Binary semaphore ID: 1, value: 1
*/
