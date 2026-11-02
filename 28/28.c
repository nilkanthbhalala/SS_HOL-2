#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main()
{
    key_t key;
    int msgid;
    struct msqid_ds buf;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgctl(msgid, IPC_STAT, &buf);
    printf("Current permissions: %o\n", buf.msg_perm.mode);

    buf.msg_perm.mode = 0644;
    msgctl(msgid, IPC_SET, &buf);

    msgctl(msgid, IPC_STAT, &buf);
    printf("Permissions successfully changed to: %o\n", buf.msg_perm.mode);

    return 0;
}

/*

nilkanth@zuxxy: gcc 28.c && ./a.out
Current permissions: 666
Permissions successfully changed to: 644
*/
