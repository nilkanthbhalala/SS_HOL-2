#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int channel[2];
    pipe(channel);
    pid_t child = fork();

    if (child == 0) {

        char message[128];
        close(channel[1]);
        ssize_t count = read(channel[0], message, sizeof(message)-1);
        message[count] = '\0';
        printf("Child received: %s\n", message);
        close(channel[0]);
    
    }else{

        close(channel[0]);
        const char message[] = "Hello from the parent";
        write(channel[1], message, sizeof(message));
        close(channel[1]);
        waitpid(child, NULL, 0);
        return 0;
    }
}

/*
nilkanth@zuxxy: gcc 15.c && ./a.out 
Child received: Hello from the parent
*/
