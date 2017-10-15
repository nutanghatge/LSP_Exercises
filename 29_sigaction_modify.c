/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      29_sigaction_modify.c
 * @brief     Exercise on signals
 * @details   This program registers a signal handler using the signalaction() with
 *            sa_flags=SA_RESTART and perform a read operation on a pipe 
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
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
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
Name        : myhandler
Input(s)    : sigtype: signal number
Output(s)   : prints message and signal ID in case the signal is received.
Description : This function is a signal handler.
***************************************************************************************************/
static void myhandler(int sigtype)
{
  printf("got signal %d\n", sigtype);
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
  struct sigaction action;
  int  n, p[2];
  char buf[1000];

  if (pipe(p) < 0) {
    printf("Error no %d\n", errno);
    perror("pipe");
    return EXIT_FAILURE;
  }

  action.sa_handler = myhandler;
  if (sigemptyset(&action.sa_mask) < 0) {
    printf("Error no %d\n", errno);
    perror("sigemptyset");
    return EXIT_FAILURE;
  }
  
  action.sa_flags = SA_RESTART;

  if (sigaction(SIGINT, &action, NULL) < 0) {
    printf("Error no %d\n", errno);
    perror("pipe");
    return EXIT_FAILURE;
  }

  while(1) {
    if ((n = read(p[0], buf, 1000)) < 0) {
      printf("Error no %d\n", errno);
      perror("read");
      return EXIT_FAILURE;
    } 
  }
}
