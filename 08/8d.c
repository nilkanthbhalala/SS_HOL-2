#include <signal.h>
#include <unistd.h>

static void handle_alarm(int signo)
{
    const char message[] = "Caught SIGALRM from alarm()\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    _exit(0);
}

int main(void)
{
    signal(SIGALRM, handle_alarm);
    alarm(3);

    for (;;){
        write(1, "Waiting..\n", 10);
        sleep(1);
    }
    _exit(1);
}

/*

nilkanth@zuxxy:  gcc 8d.c && ./a.out
Waiting..
Waiting..
Waiting..
Caught SIGALRM from alarm()
*/
