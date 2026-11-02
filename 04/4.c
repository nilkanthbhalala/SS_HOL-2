#define _POSIX_C_SOURCE 200809L
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

static uint64_t timestamp(void)
{
    unsigned long long low, high;
    __asm__ volatile("lfence; rdtsc" : "=a"(low), "=d"(high) :: "memory");
    return ((uint64_t)high << 32) | low;
}

int main()
{
    uint64_t start = timestamp();

    for (int i = 0; i < 100; ++i)
        (void)getppid();

    uint64_t elapsed = timestamp() - start;

    puts("Timestamp counter cycles for 100 getppid calls:");
    printf("Total: %"PRIu64" \nAverage: %"PRIu64" \n", elapsed, elapsed / 100);
    return 0;
}

/*
nilkanth@zuxxy: gcc 4.c && ./a.out
Timestamp counter cycles for 100 getppid calls:
Total: 151225 
Average: 1512 
*/
