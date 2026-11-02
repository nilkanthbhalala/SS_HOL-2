#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to server!\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(sock, buffer, strlen(buffer), 0);

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Client exited the chat.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, sizeof(buffer));
        printf("Server: %s", buffer);

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server exited the chat.\n");
            break;
        }
    }
    close(sock);
    return 0;
}

/*
gcc 33_client.c -o client
nilkanth@zuxxy: ./client 
Connected to server!
Client: hello
Server: hello
Client: i am fine
Server: ok
Client: ok

*/