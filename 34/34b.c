#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handle_client(void *arg)
{
    int client_sock = *((int *)arg);
    free(arg);
    printf("Thread %ld: started for client socket %d\n", pthread_self(), client_sock);

    char buffer[BUFFER_SIZE];
    int n;

    while ((n = read(client_sock, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[n] = '\0';
        printf("Thread %ld: received '%s'\n", pthread_self(), buffer);
        write(client_sock, buffer, n);
    }

    printf("Thread %ld: client disconnected, closing socket %d\n", pthread_self(), client_sock);
    close(client_sock);
    return NULL;
}

int main()
{
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        int client_sock = accept(server_sock, NULL, NULL);
        printf("Main thread: client connected, socket=%d\n", client_sock);

        int *pclient = malloc(sizeof(int));
        *pclient = client_sock;

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, pclient);
        pthread_detach(tid);
    }

    close(server_sock);
    return 0;
}

/*
Thread Server:
gcc 34b.c -pthread -o pthread_server && ./pthread_server 
Server listening on port 8080...
Thread 123950891792064: started for client socket 4
Thread 123950891792064: received 'hi
'
Thread 123950891792064: received 'Hellow
'


Client 1:
nc 127.0.0.1 8080
hi
hi
Hellow
Hellow
*/