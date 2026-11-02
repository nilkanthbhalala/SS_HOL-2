#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int channel[2];
    pipe(channel);

    pid_t left = fork();
    if (left == 0) {

        close(channel[0]);
        close(STDOUT_FILENO);
        fcntl(channel[1], F_DUPFD, STDOUT_FILENO);
        close(channel[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        _exit(127);
    }

    pid_t right = fork();
    if (right == 0) {

        close(channel[1]);
        close(STDIN_FILENO);
        fcntl(channel[0], F_DUPFD, STDIN_FILENO);
        close(channel[0]);

        execlp("wc", "wc", (char *)NULL);
        _exit(127);
    }

    close(channel[0]);
    close(channel[1]);
    waitpid(left, NULL, 0);
    waitpid(right, NULL, 0);
    return 0;
}

/*
nilkanth@zuxxy: gcc 17c.c -o a.out
nilkanth@zuxxy: ./a.out
      5      38     201
*/
