#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

static void handle_timer(int signo)
{
    const char message[] = "ITIMER_VIRTUAL expired\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
}

int main(void)
{
    struct sigaction action = {0};
    struct itimerval timer = {{10, 10}, {10, 0}};
    action.sa_handler = handle_timer;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGVTALRM, &action, NULL) == -1 || setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
        return 1;
    while(true){}
}

/*

nilkanth@zuxxy: gcc 1b.c -o timer && ./timer
ITIMER_VIRTUAL expired
ITIMER_VIRTUAL expired
*/
