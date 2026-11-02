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

    int outgoing = open("fifo21_ab", O_WRONLY);
    int incoming = open("fifo21_ba", O_RDONLY);

    while (1) {

        char choice[32];

        printf("\nRead: 1, Write: 2, Exit: 3\n");
        printf("Process A: Enter your preference: ");
        fflush(stdout);

        if (fgets(choice, sizeof(choice), stdin) == NULL)
            break;

        if (strcmp(choice, "1\n") == 0) {

            char reply[128];
            ssize_t count = read(incoming, reply, sizeof(reply) - 1);

            if (count == 0) {
                puts("Process B closed its writing end");
                break;
            }
            reply[count] = '\0';
            printf("A received: %s\n", reply);

        } 
        else if (strcmp(choice, "2\n") == 0) {

            char buffer[100];
            printf("Process A: Enter message: ");
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

nilkanth@zuxxy: gcc 21a.c && ./a.out

Read: 1, Write: 2, Exit: 3
Process A: Enter your preference: 1
A received: Hello

Read: 1, Write: 2, Exit: 3
Process A: Enter your preference: 1
A received: i am here

Read: 1, Write: 2, Exit: 3
Process A: Enter your preference: 
*/