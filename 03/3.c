#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("Open-file limit before: soft=%llu hard=%llu\n", (unsigned long long)limit.rlim_cur, (unsigned long long)limit.rlim_max);
    limit.rlim_cur = 512;
    limit.rlim_max = 513;
    
    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("setrlimit");
        return 1;
    }
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }
    printf("Open-file limit after:  soft=%llu hard=%llu\n", (unsigned long long)limit.rlim_cur, (unsigned long long)limit.rlim_max);
    return 0;
}

/*

nilkanth@zuxxy: gcc 3.c && ./a.out
Open-file limit before: soft=524288 hard=524288
Open-file limit after:  soft=512 hard=513
*/
