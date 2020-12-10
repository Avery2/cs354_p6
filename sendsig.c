#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: <signal type> <pid>");
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%d", *argv[i]);
        }
    }
}