#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define SIGALRM 14
#define DELAY 3

static void alarm_handler()
{
	// handler function
	// print the pid (process id) and current time (format linux date command)
	printf("%d %s", getpid(), ctime(NULL));
	alarm(DELAY);
	return;
}

int main(int argc, char *argv[])
{
	printf("Pid and time print every 3 seconds.\nEnter Ctrl-C to end the program.\n");

	alarm(DELAY); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	// sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = alarm_handler;
	sigaction(SIGALRM, &sa, NULL);
	while (1)
	{
	}
}
