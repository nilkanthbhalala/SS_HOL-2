#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{

    key_t key = ftok("key_progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*

nilkanth@zuxxy: gcc 24.c && ./a.out 
Message Queue Key: 1090650554
Message Queue ID: 1
*/
