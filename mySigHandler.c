#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define SIGALRM 14

void alarm_handler()
{
	printf("%d %ld", getpid(), time(NULL));
	alarm(3);
	return;
}

int main()
{
	printf("START");
	alarm(3); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	// handler function
	// print the pid (process id) and current time (format linux date command)

	signal(SIGALRM, alarm_handler);
	// while (1)
	// {
	// }
}
