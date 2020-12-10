#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: <signal type> <pid>\n");
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%s\n", *argv[i]);
        }
    }
}