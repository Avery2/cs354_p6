#include <stdio.h>
#include <stdlib.h>

#define SIGFPE 8

int main(int argc, char *argv[])
{
    printf(atoi("f"));
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
    }
}