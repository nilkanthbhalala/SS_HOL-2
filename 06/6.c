#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

static void *worker(void *argument)
{
    intptr_t number = (intptr_t)argument;
    printf("Thread %ld is running\n", number);

    sleep(3);
    struct timespec delay = {
        .tv_sec = 1,
        .tv_nsec = 0
    };
    int i = 3;
    while(i){
        printf("%ld", number);
        nanosleep(&delay, NULL);
        --i;
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    
    for (intptr_t i = 0; i < 3; ++i) 
        pthread_create(&threads[i], NULL, worker, (void *)i);
    
    sleep(10);
    
    for (int i = 0; i < 3; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            return 1;
        }
    }
    return 0;
}

/*

nilkanth@zuxxy: gcc -pthread 6.c -o a.out
nilkanth@zuxxy: ./a.out
Thread 0 is running
Thread 1 is running
Thread 2 is running
012021021  <-- This is how thread runs
*/
