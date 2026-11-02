#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int ensure_fifo(void)
{
    struct stat info;
    if (mkfifo("fifo20", 0660) == 0 || errno == EEXIST) {
        if (lstat("fifo20", &info) == 0 && S_ISFIFO(info.st_mode))
            return 0;
    }
    perror("mkfifo");
    return -1;
}

int main(int argc, char *argv[])
{
    char *message;
    if(argc != 2)
        return 1;
    else
        message = argv[1];   


    if (ensure_fifo() == -1)
        return 1;

    int fd = open("fifo20", O_WRONLY);
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    printf("Sent\n");
    close(fd);
    return 0;
}

/*

nilkanth@zuxxy: gcc 20_writer.c && ./a.out "This is first msg from writer side"
Sent
*/
