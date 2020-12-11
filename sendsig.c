////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      mySigHandler.c division.c
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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SIGUSR1 10
#define SIGINT 2

/*
 * Main function.
 * Reads arguments and then sends a SIGINT or SIGUSR1 signal to a given process if possible.
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    if (!(strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-i") == 0))
    {
        printf("Usage: <signal type> <pid>\n");
    }

    pid_t pid = atoi(argv[2]);

    if (strcmp(argv[1], "-u") == 0)
    {
        if (kill(pid, SIGUSR1) != 0)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
    }
    if (strcmp(argv[1], "-i") == 0)
    {
        if (kill(pid, SIGINT) != 0)
        {
            printf("Error with errno %d was caught. Exiting now.\n", errno);
            exit(0);
        }
    }
}