#include <unistd.h>

#define SIGALRM 14

main()
{
	alarm(3); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	// handler function
	// print the pid (process id) and current time (format linux date command)

	signal(SIGALRM, alarm_handler);

	while (1)
	{
	}
}

alarm_handler()
{
	print(sys_getpid() + sys_time());
	alarm(3);
}
