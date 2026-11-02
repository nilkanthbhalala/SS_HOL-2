#include <signal.h>
#include <unistd.h>

static void handle_signal(int signo)
{
    const char message[] = "Caught SIGFPE: Divide by zero\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    _exit(0);
}

int main(void)
{
    signal(SIGFPE, handle_signal);
    // raise(SIGFPE);
    int x = 10;
    int y = 0;
    int result = x / y;
    (void)result;
    return 0;
}

/*

nilkanth@zuxxy: gcc 8c.c && ./a.out
Caught SIGFPE: Divide by zero
*/
