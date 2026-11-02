#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("fifo22", O_WRONLY);
    char *message = "Hello from writer process!";
    write(fd, message, strlen(message));
    close(fd);
    return 0;
}