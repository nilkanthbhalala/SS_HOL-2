#include <signal.h>
#include <unistd.h>

static void handle_signal(int signo)
{
    const char message[] = "Caught SIGINT with sigaction\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    _exit(0);
}

int main()
{
    struct sigaction action = {0};
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    
    raise(SIGINT);
    return 0;
}

/*

nilkanth@zuxxy: gcc 10b.c -o a.out
nilkanth@zuxxy: ./a.out
Caught SIGINT with sigaction
*/
