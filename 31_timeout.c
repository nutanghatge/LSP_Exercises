/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      31_timeout.c
 * @brief     Exercise on signals
 * @details   System calls such as read() are blocking and do not timeout (they can 
 *            block forever waiting for data) – SIGALRM	signal that gets raised by
 *            the alarm() system call  prints a message to the screen when the user 
 *            doesn’t enter any input for longer than 5 second. 
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
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>

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
Name        : timeout_handler
Input(s)    : unused: signal number
Output(s)   : does nothing
Description : This function is a signal handler.
***************************************************************************************************/
static void timeout_handler(int unused)
{
  /* Nothing to do */
}

/**************************************************************************************************
Name        : t_getnum
Input(s)    : timeout to be set: timeout seconds
Output(s)   : set alarm for timeout
Description : This function is an alarm
***************************************************************************************************/
static int t_getnum(int timeout)
{
  int n;
  char line[100];
  struct sigaction action;

  action.sa_handler = timeout_handler;
  if (sigemptyset(&action.sa_mask) < 0) {
    printf("error no >> %d\n", errno);
    perror("sigemptyset");
    return -1;
  }
  action.sa_flags = 0;
  if (sigaction(SIGALRM, &action, NULL) < 0) {
    printf("error no >> %d\n", errno);
    perror("sigaction");
    return -1;
  }

  alarm(timeout);
  if ((n = read(0, line, 100)) < 0) {
    return -1;
  }

  alarm(0);
  if (n == -1 && errno == EINTR) { 
    return -1;
  }
  n = atoi(line);
  return n;
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
  int num;

  while(1) {
    if (printf("enter a number: ") < 0) { 
      perror("printf error");
      return EXIT_FAILURE;
    }
    if (fflush(stdout) == EOF) {
      printf("error no >> %d\n", errno);
      perror("fflush");
      return EXIT_FAILURE;
    }
    if ((num = t_getnum(5)) == -1) {
      if (printf("timed out!\n") < 0) { 
        perror("printf error");
        return EXIT_FAILURE;
      }
    } else {
      if (printf("You entered %d\n", num) < 0) { 
        perror("printf error");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
