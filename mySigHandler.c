#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define SIGALRM 14
#define DELAY 3

void alarm_handler()
{
	// handler function
	// print the pid (process id) and current time (format linux date command)
	printf("%d %ld", getpid(), time(NULL));
	alarm(DELAY);
	return;
}

int main()
{
	printf("Pid and time print every 3 seconds.\nEnter Ctrl-C to end the program.");
	alarm(DELAY); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	signal(SIGALRM, alarm_handler);
	while (1)
	{
	}
}
