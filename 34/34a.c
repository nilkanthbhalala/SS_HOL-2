#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

void handle_client(int client_sock)
{
    char buffer[1024];
    int n;
    while ((n = read(client_sock, buffer, 1024)) > 0)
    {
        write(client_sock, buffer, n);
    }
    close(client_sock);
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

    while (1)
    {
        int client_sock = accept(server_sock, NULL, NULL);
        if (fork() == 0)
        {
            close(server_sock);
            handle_client(client_sock);
            return 0;
        }
        close(client_sock);
    }
}

/*
server is running:
gcc 34a.c -o server && ./server 

client side 1:
nc 127.0.0.1 8080
hellow
hellow
hi
hi

*/