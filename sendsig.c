#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        // TODO do I keep this? Or remove extra testing
        printf("Usage: <signal type> <pid>\n");
    }
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // check error atoi
    pid_t pid = atoi(argv[2]);

    if (strcmp(argv[1], "-u") == 0)
    {
        kill(pid, SIGUSR1);
    }
    if (strcmp(argv[1], "-i") == 0)
    {
        kill(pid, SIGINT);
    }
}