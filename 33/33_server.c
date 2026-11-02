#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Server waiting for connection...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected!\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));
        printf("Client: %s", buffer);

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Client exited the chat.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(new_socket, buffer, strlen(buffer), 0);

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server exited the chat.\n");
            break;
        }
    }

    close(new_socket);
    close(server_fd);

    return 0;
}

/*
gcc 33_server.c -o server
nilkanth@zuxxy: ./server
Server waiting for connection...
Client connected!
hello
Client: hello
Server: Client: i am fine
Server: ok
Client: ok
*/
