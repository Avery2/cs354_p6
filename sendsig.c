#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SIGUSR1 10
#define SIGINT 2

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    if (!(strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-i") == 0))
    {
        printf("Usage: <signal type> <pid>\n");
    }

    pid_t pid = atoi(argv[2]);

    if (strcmp(argv[1], "-u") == 0)
    {
        if (kill(pid, SIGUSR1) != 0)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
    }
    if (strcmp(argv[1], "-i") == 0)
    {
        if (kill(pid, SIGINT) != 0)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
    }
}