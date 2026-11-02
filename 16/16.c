#include <stdio.h>
#include <sys/wait.h>
#include<string.h>
#include <unistd.h>

int main()
{
    int fd1[2];
    int fd2[2];
    char parent_msg[] = "Hello Child, how are you?";
    char child_msg[] = "I am fine, Parent!";
    char buffer[100];

    pipe(fd1);
    pipe(fd2);

    if (fork())
    {
        close(fd1[0]); //closed read point
        close(fd2[1]); //closed write point

        write(fd1[1], parent_msg, strlen(parent_msg) + 1);
        close(fd1[1]);

        read(fd2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd2[0]);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd1[0]);

        write(fd2[1], child_msg, strlen(child_msg) + 1);
        close(fd2[1]);
    }

    return 0;
}

/*

nilkanth@zuxxy: gcc 16.c && ./a.out 
Child received: Hello Child, how are you?
Parent received: I am fine, Parent!
*/
