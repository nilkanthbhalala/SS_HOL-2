#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_signal(int signo)
{
    const char message[] = "Caught SIGSEGV: Invalid memory access\n";
    (void)signo;
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    exit(0);
}

int main()
{
    signal(SIGSEGV, handle_signal); 
    raise(SIGSEGV);
    return 0;
}

/*
nilkanth@zuxxy: gcc 8a.c && ./a.out
Caught SIGSEGV: Invalid memory access
*/
