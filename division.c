#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define SIGFPE 8
#define SIGINT 2
#define BUFFER 100

int div_count = 0;

static void interrupt_handler()
{
    printf("\nTotal number of operations completed successfully: %d\nThe program will be terminated.\n", div_count);
    exit(0);
}

static void div_zero_hanlder()
{
    printf("Error: a division by 0 operation was attempted.\nTotal number of operations completed successfully: %d\nThe program will be terminated.\n", div_count);
    exit(0);
}

int main(int argc, char *argv[])
{
    struct sigaction div_zero_action;
    memset(&div_zero_action, 0, sizeof(div_zero_action));
    div_zero_action.sa_flags = SA_SIGINFO;
    div_zero_action.sa_sigaction = div_zero_hanlder;
    if (sigaction(SIGFPE, &div_zero_action, NULL) != 0)
    {
        printf("Error with errno %d was caught. Exiting now.\n", errno);
        exit(0);
    }

    struct sigaction interrupt_action;
    memset(&interrupt_action, 0, sizeof(interrupt_action));
    interrupt_action.sa_flags = SA_SIGINFO;
    interrupt_action.sa_sigaction = interrupt_handler;
    if (sigaction(SIGINT, &interrupt_action, NULL) != 0)
    {
        printf("Error with errno %d was caught. Exiting now.\n", errno);
        exit(0);
    }

    while (1)
    {
        // non-numeric input defaults to 0
        char input1[BUFFER];
        char input2[BUFFER];
        printf("Enter first integer: ");
        if (fgets(input1, BUFFER, stdin) == NULL)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
        printf("Enter second integer: ");
        if (fgets(input2, BUFFER, stdin) == NULL)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
        int n1 = atoi(input1);
        int n2 = atoi(input2);
        printf("%d / %d is %d with a remainder of %d\n", n1, n2, n1 / n2, n1 % n2);
        div_count++;
    }
}