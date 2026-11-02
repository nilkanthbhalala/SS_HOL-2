#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    msgctl(msgid, IPC_RMID, NULL);
    printf("Message queue removed successfully.\n");

    return 0;
}

/*

nilkanth@zuxxy: gcc 29.c && ./a.out
Message queue removed successfully.
*/
