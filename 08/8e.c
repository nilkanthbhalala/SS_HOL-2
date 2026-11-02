#define _DEFAULT_SOURCE
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include<stdio.h>
#include<time.h>

static volatile sig_atomic_t count;
time_t start_time;

static void handle_alarm(int signo)
{
   
    (void)signo;
    time_t now = time(NULL);
    printf("Caught SIGALRM: Timer expired! Elapsed: %ld seconds\n",
           now - start_time);

    if (++count == 4)
        _exit(0);
}

int main(void)
{
    struct itimerval timer = {{2, 0}, {1, 0}};
    start_time = time(NULL);

    signal(SIGALRM, handle_alarm);
    setitimer(ITIMER_REAL, &timer, NULL);
    
    for (;;)
        pause();
}

/*

nilkanth@zuxxy: gcc 8e.c && ./a.out
Caught SIGALRM: Timer expired! Elapsed: 1 seconds
Caught SIGALRM: Timer expired! Elapsed: 3 seconds
Caught SIGALRM: Timer expired! Elapsed: 5 seconds
Caught SIGALRM: Timer expired! Elapsed: 7 seconds
*/
