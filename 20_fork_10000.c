/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      20_fork_10000.c
 * @brief     Exercise on fork()
 * @details   This program creates a child process,the parent process prints 
 *            PARENT + pid 10000 times, and the child process prints CHILD + pid 10000 
 *            times and both processes exit.
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

/*************************************************************************************
 *                          INCLUDES                                                 *
 *************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*************************************************************************************
 *                          MACROS                                                   *
 *************************************************************************************/
#define ITERN 10000

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main() {
  /* Local Variables*/
  pid_t pid;
  int n,check;
  char *identity;
  /* fork */
  pid = fork();
  switch (pid) {
    case -1:
      if ((check = printf("fork failed\n")) < 0) {
        perror("printf error");
        return 1;
      }
    break;

    case 0:
      identity = "CHILD";
      break;

    default:
      identity = "PARENT";
      break;
  }
  for(n = ITERN; n > 0; n--) {
    if ((check = printf("%s + %d\n",identity,pid)) < 0) {
        perror("printf error");
        return 1;
      }
  }
  return 0;
}
