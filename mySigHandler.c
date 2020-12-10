#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define SIGALRM 14
#define DELAY 3
#define SIGUSR1 10
#define SIGUSR2 12
#define SIGINT 2

int user_signal_count = 0;

// TODO fix error handling according to scheme.xw

static void ctrl_c_handler()
{
	printf("SIGUSR1 was handled %d times. Exiting now.\n", user_signal_count);
	exit(0);
}

static void alarm_handler()
{
	// printf("handler called\n");
	// handler function
	// print the pid (process id) and current time (format linux date command)
	time_t now;
	time(&now);
	printf("PID: %d CURRENT TIME: %s\n", getpid(), ctime(&now));
	// printf("reset alarm\n");
	alarm(DELAY);
	return;
}

static void usr_handler()
{
	printf("SIGUSR1 handled and counted!\n");
	user_signal_count++;
	return;
}

int main(int argc, char *argv[])
{
	printf("Pid and time print every 3 seconds.\nEnter Ctrl-C to end the program.\n");

	alarm(DELAY); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	struct sigaction alarm_action;
	memset(&alarm_action, 0, sizeof(alarm_action));
	alarm_action.sa_flags = SA_SIGINFO;
	alarm_action.sa_sigaction = alarm_handler;
	sigaction(SIGALRM, &alarm_action, NULL);

	struct sigaction usr_action;
	memset(&usr_action, 0, sizeof(usr_action));
	usr_action.sa_flags = SA_SIGINFO;
	usr_action.sa_sigaction = usr_handler;
	sigaction(SIGUSR1, &usr_action, NULL);

	struct sigaction exit_action;
	memset(&exit_action, 0, sizeof(exit_action));
	exit_action.sa_flags = SA_SIGINFO;
	exit_action.sa_sigaction = ctrl_c_handler;
	sigaction(SIGINT, &exit_action, NULL);

	while (1)
	{
	}
}
