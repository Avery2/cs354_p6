////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c division.c
// Semester:         CS 354 Fall 2020
// Instructor:       deppeler
//
// Discussion Group: 631
// Author:           Justin Chan
// Email:            jachan@wisc.edu
// CS Login:         justinc
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020, Jim Skrentny, (skrentny@cs.wisc.edu)
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS354-Fall 2020, Deb Deppeler (deppeler@cs.wisc.edu)
//
////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define SIGALRM 14
#define DELAY 3
#define SIGUSR1 10
#define SIGUSR2 12
#define SIGINT 2

int user_signal_count = 0;

/*
 * Handler for SIGINT signal
 * Prints out number of times SIGUSR1 signal was handled and exits.
 */
static void ctrl_c_handler()
{
	printf("SIGUSR1 was handled %d times. Exiting now.\n", user_signal_count);
	exit(0);
}

/*
 * Handler for SIGALRM signal
 * Prints out message then resets alarm.
 */
static void alarm_handler()
{
	time_t now;
	if (time(&now) == (time_t)-1)
	{
		printf("Error with errno %d was caught. Exiting now.\n", errno);
		exit(0);
	}
	char *time_val = ctime(&now);
	if (time_val == NULL)
	{
		printf("Error with errno %d was caught. Exiting now.\n", errno);
		exit(0);
	}
	// print the pid (process id) and current time (format linux date command)
	printf("PID: %d CURRENT TIME: %s", getpid(), time_val);
	// reset alarm
	alarm(DELAY);
	return;
}

/*
 * Handler for SIGUSER1 signal.
 * Prints message and updates counter.
 */
static void usr_handler()
{
	printf("SIGUSR1 handled and counted!\n");
	user_signal_count++;
	return;
}

/*
 * Main function that sets up handlers then enters infinite loop.
 */
int main(int argc, char *argv[])
{
	printf("Pid and time print every 3 seconds.\nEnter Ctrl-C to end the program.\n");

	alarm(DELAY); // setup alarm to go off 3 seconds later, sending SIGALRM signal to the program
	// register signal handler to handle the SIGALRM (14)
	struct sigaction alarm_action;
	memset(&alarm_action, 0, sizeof(alarm_action));
	alarm_action.sa_flags = SA_SIGINFO;
	alarm_action.sa_sigaction = alarm_handler;
	if (sigaction(SIGALRM, &alarm_action, NULL) != 0)
	{
		printf("Error with errno %d was caught. Exiting now.\n", errno);
		exit(0);
	}

	struct sigaction usr_action;
	memset(&usr_action, 0, sizeof(usr_action));
	usr_action.sa_flags = SA_SIGINFO;
	usr_action.sa_sigaction = usr_handler;
	if (sigaction(SIGUSR1, &usr_action, NULL) != 0)
	{
		printf("Error with errno %d was caught. Exiting now.\n", errno);
		exit(0);
	}

	struct sigaction exit_action;
	memset(&exit_action, 0, sizeof(exit_action));
	exit_action.sa_flags = SA_SIGINFO;
	exit_action.sa_sigaction = ctrl_c_handler;
	if (sigaction(SIGINT, &exit_action, NULL) != 0)
	{
		printf("Error with errno %d was caught. Exiting now.\n", errno);
		exit(0);
	}

	while (1)
	{
	}
}
