/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      21_fork_wait.c
 * @brief     Exercise on fork
 * @details   A	program	where a parent forks a child process and then blocks itself 
 *            till the child terminates,after which it prints out if the child exited
 *            normally OR if the child was terminated.The child	thread simply
 *	      print its	own process ID and sleep for 500 seconds to allow for signals
 *	      to be sent to it from the terminal to test the various status messages
 * @see
 * @author    Nutan Ghatge, nutanghatge@elear.solutions
 * @copyright Copyright (c) 2017 Elear Solutions Tech Private Limited. All rights
 *            reserved.
 * @license   To any person (the "Recipient") obtaining a copy of this software and
 *            associated documentation files (the "Software"):\n
 *            All information contained in or disclosed by this software is
 *            confidential and proprietary information of Elear Solutions Tech
 *            Private Limited and all rights therein are expressly reserved.
 *            By accepting this material the recipient agrees that this material and
 *            the information contained therein is held in confidence and in trust
 *            and will NOT be used, copied, modified, merged, published, distributed,
 *            sublicensed, reproduced in whole or in part, nor its contents revealed
 *            in any manner to others without the express written permission of
 *            Elear Solutions Tech Private Limited.
 */
/*************************************************************************************/
/*===================================================================================*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/

/*************************************************************************************
 *                          LOCAL TYPEDEFS                                           *
 *************************************************************************************/

/*************************************************************************************
 *                          LOCAL PROTOTYPES                                         *
 *************************************************************************************/

/*************************************************************************************
 *                          GLOBAL VARIABLES                                         *
 *************************************************************************************/

/*************************************************************************************
 *                          LOCAL VARIABLES                                          *
 *************************************************************************************/

/*************************************************************************************
 *                          PRIVATE FUNCTIONS                                        *
 *************************************************************************************/
/**************************************************************************************************
Name        : signal handler
Input(s)    : sig: signal number
Output(s)   : prints message and signal ID in case the signal is received.
Description : This function is a signal handler.
***************************************************************************************************/
static void ouch (int sig) {
  printf("OUCH! - I got signal %d\n", sig);
  return;
}

/*************************************************************************************
 *                          PUBLIC FUNCTIONS                                         *
 *************************************************************************************/
/*************************************************************************************
 * Refer to the header file for a detailed description                               *
 *************************************************************************************/

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main() {
  pid_t pid;
  int n, exit_code, check;
  char *identity;
  struct sigaction act;
  
  act.sa_handler = ouch;
  if ((check = sigemptyset(&act.sa_mask)) < 0) {
    printf("Error no >> %d\n", errno);
    perror("sigemptyset");
    return EXIT_FAILURE;
  }

  act.sa_flags = 0;

  if ((check = sigaction(SIGINT, &act, 0)) < 0) { 
    printf("Error no >> %d\n", errno);
    perror("sigaction");
    return EXIT_FAILURE;
  }

  if ((pid = fork()) < 0) { 
    printf("Error no >> %d\n", errno);
    perror("fork failed\n");
    return EXIT_FAILURE;
  } else if (pid == 0) {
    identity = "CHILD";
    n = 10;
    exit_code = 37;
  } else {
    identity = "PARENT";
    n = 8;
    exit_code = 0;
  }

  for (; n > 0; n--) {
    if ((check = printf("%s + %d\n", identity, pid)) < 0) {
      perror("printf error");
      return EXIT_FAILURE;
    }
    sleep(1);
  }
  
  if (pid != 0) {
    int stat_val;
    pid_t child_pid;

    if ((child_pid = wait(&stat_val)) < 0) {
      printf("Error no >> %d\n", errno);
      perror("wait");
      return EXIT_FAILURE;
    }
    sleep(500);
    if ((check = printf("Child has finished : PID = %d\n", child_pid)) < 0) {
      perror("printf error");
      return EXIT_FAILURE;
    }
    if (WIFEXITED(stat_val)) {
      if ((check = printf("child exited with code %d\n", WEXITSTATUS(stat_val))) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
    } else {
      if ((check = printf("child terminated abnormally\n")) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
    }
  }
  exit(exit_code);
}
