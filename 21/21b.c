#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int ensure_fifo(const char *path)
{
    struct stat info;
    if (mkfifo(path, 0660) == 0 || errno == EEXIST) {
        if (lstat(path, &info) == 0 && S_ISFIFO(info.st_mode))
            return 0;
    }
    perror("mkfifo");
    return -1;
}

int main()
{
    if (ensure_fifo("fifo21_ab") == -1 || ensure_fifo("fifo21_ba") == -1)
        return 1;

    int incoming = open("fifo21_ab", O_RDONLY);
    int outgoing = open("fifo21_ba", O_WRONLY);

    while (1) {

        char choice[32];
        printf("\nRead: 1, Write: 2, Exit: 3\n");
        printf("Process B: Enter your preference: ");
        fflush(stdout);

        if (fgets(choice, sizeof(choice), stdin) == NULL)
            break;

        if (strcmp(choice, "1\n") == 0) {

            char reply[128];
            ssize_t count = read(incoming, reply, sizeof(reply) - 1);

            if (count == 0) {
                puts("Process A closed its writing end");
                break;
            }
            reply[count] = '\0';
            printf("B received: %s", reply);

        } 
        else if (strcmp(choice, "2\n") == 0) {

            char buffer[100];
            printf("Process B: Enter message: ");
            fflush(stdout);

            fgets(buffer, sizeof(buffer), stdin);
            write(outgoing, buffer, strlen(buffer));
            puts("Sent");

        } 
        else if (strcmp(choice, "3\n") == 0) {
            break;

        } 
        else {
            puts("Choose 1, 2, or 3.");
        }
    }

    close(incoming);
    close(outgoing);

    return 0;
}

/*
nilkanth@zuxxy: gcc 21b.c && ./a.out 

Read: 1, Write: 2, Exit: 3
Process B: Enter your preference: 2
Process B: Enter message: Hello
Sent

Read: 1, Write: 2, Exit: 3
Process B: Enter your preference: 2
Process B: Enter message: i am here     
Sent

*/