#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message 
{ 
    long type; 
    char text[128]; 
};

int main()
{
    key_t key = ftok("p_file", 65);
    int id = msgget(key, IPC_CREAT | 0660);
    
    struct message message;
    message.type = 1;
    strcpy(message.text, "Hi, How are you? I am Nilkanth Bhalala.");

    msgsnd(id, &message, strlen(message.text) + 1, 0); //IPC_NOWAIT
    printf("Message sent to queue with ID: %d\n", id);
    return 0;
}

/*

nilkanth@zuxxy: gcc 26.c && ./a.out 
Message sent to queue with ID: 3
nilkanth@zuxxy:/mnt/367FB805056220E7/IIITB/SS/HandsOn_2/26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          nilkanth   666        0            0           
0x410201ba 1          nilkanth   666        0            0           
0x410201ca 2          nilkanth   666        0            0           
0x410201e8 3          nilkanth   660        40           1     
*/
