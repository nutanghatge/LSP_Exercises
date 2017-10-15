/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      27_global_counter.c
 * @brief     Exercise on signals
 * @details   This program is a global counter and the counter resets every time there	
 *            is a SIGINT signal.SIGQUIT and SIGTERM should be ignored.	
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
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

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
static int n;

/*************************************************************************************
 *                          PRIVATE FUNCTIONS                                        *
 *************************************************************************************/
/**************************************************************************************************
Name        : handler
Input(s)    : signum: signal number
Output(s)   : prints message and signal ID in case the signal is received.
Description : This function is a signal handler.
***************************************************************************************************/
static void handler(int signum)
{
  printf("signal %d received - counter reset\n", signum);
  n = 0;
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
  if (signal(SIGINT, handler) == SIG_ERR) {
    printf("error no >> %d\n", errno);
    perror("signal");
    return EXIT_FAILURE;
  }

  if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
    printf("error no >> %d\n", errno);
    perror("signal");
    return EXIT_FAILURE;
  }

  if (signal(SIGTERM, SIG_IGN) == SIG_ERR) {
    printf("error no >> %d\n", errno);
    perror("signal");
    return EXIT_FAILURE;
  }

  while(1) {
    if (printf("Working %d\n", n++) < 0) {
      perror("printf  error");
      return EXIT_FAILURE;
    }
    sleep(1);
  }
  return EXIT_SUCCESS;
}
