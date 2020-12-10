#include <stdio.h>
#include <stdlib.h>

#define SIGFPE 8

int div_count = 0;

static void interrupt_handler()
{
    printf("Total number of operations completed successfully: %d\nThe program will be terminated.\n", div_count);
}

static void div_zero_hanlder()
{
    printf("Error: a division by 0 operation was attempted.\nTotal number of operations completed successfully: %d\nThe program will be terminated.\n", div_count);
}

int main(int argc, char *argv[])
{
    struct sigaction div_zero_action;
    memset(&div_zero_action, 0, sizeof(div_zero_action));
    div_zero_action.sa_flags = SA_SIGINFO;
    div_zero_action.sa_sigaction = div_zero_hanlder;
    sigaction(SIGALRM, &div_zero_action, NULL);

    struct sigaction interrupt_action;
    memset(&interrupt_action, 0, sizeof(interrupt_action));
    interrupt_action.sa_flags = SA_SIGINFO;
    interrupt_action.sa_sigaction = interrupt_handler;
    sigaction(SIGALRM, &interrupt_action, NULL);

    while (1)
    {
        // non-numeric input defaults to 0
        char input1[100];
        char input2[100];
        printf("Enter first integer: ");
        fgets(input1, 100, stdin);
        printf("Enter second integer: ");
        fgets(input2, 100, stdin);
        int n1 = atoi(input1);
        int n2 = atoi(input2);
        printf("%d / %d is %d with a remainder of %d\n", n1, n2, n1 / n2, n1 % n2);
        div_count++;
    }
}