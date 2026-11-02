#include <signal.h>
#include <unistd.h>

static void handle_signal(int signo)
{
    const char message[] = "Caught SIGSEGV with sigaction\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    _exit(0);
}

int main(void)
{
    struct sigaction action = {0};
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    sigaction(SIGSEGV, &action, NULL);
    
    // raise(SIGSEGV);
    int *p = NULL;
    *p = 42;
    return 0;
}

/*

nilkanth@zuxxy: gcc 10a.c && ./a.out 
Caught SIGSEGV with sigaction
*/
