#define _DEFAULT_SOURCE
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include<time.h>

static void handle_timer(int signo)
{
    const char message[] = "ITIMER_PROF expired\n";
    write(STDOUT_FILENO, message, sizeof(message)-1);
}

int main(void)
{
    struct sigaction action = {0};
    struct itimerval timer = {{10, 10}, {10, 0}};
    action.sa_handler = handle_timer;
    // sigemptyset(&action.sa_mask);
    if (sigaction(SIGPROF, &action, NULL) == -1 || setitimer(ITIMER_PROF, &timer, NULL) == -1)
        return 1;
    while(1){}

    // unsigned long count = 0;
    // while (1) {
    //     count++; //Here i am on user mode
    //     if (count == 100000000UL) {
    //         write(STDOUT_FILENO, ".", 1); //Here i am using CPU
    //         count = 0;
    //     }
    // }
}

/*

nilkanth@zuxxy: gcc 1c.c -o timer && ./timer
ITIMER_PROF expired //After 10s
ITIMER_PROF expired //After 10s 10us
ITIMER_PROF expired //After 10s 10us
*/
