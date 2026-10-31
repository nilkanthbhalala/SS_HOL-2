#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include<time.h>

void handle_timer(int signo)
{
    char message[] = "ITIMER_REAL expired\n";
    write(1, message, sizeof(message) - 1);
}

int main()
{
    struct sigaction action = {0};
    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    action.sa_handler = handle_timer;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGALRM, &action, NULL) == -1 || setitimer(ITIMER_REAL, &timer, NULL) == -1)
        return 1;
    while(1){
        pause();
    }
    // struct timespec delay = {
    //     .tv_sec = 1,
    //     .tv_nsec = 0
    // };
    // while(true){
    //     write(1, ".", 1);
    //     nanosleep(&delay, NULL);
    // }
}

/*
nilkanth@zuxxy: gcc 1a.c -o timer && ./timer
ITIMER_REAL expired
ITIMER_REAL expired
ITIMER_REAL expired
*/
