/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      19_fork_1.c
 * @brief     Exercise on fork()
 * @details   This program creates a child process, the parent process prints
 *            PARENT + pid, and the child process prints CHILD + pid and both
 *            processes	exit.
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
#include <sys/types.h>
#include <unistd.h>

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main() {
  pid_t pid;
  int check;
  /* fork  a process */
  pid = fork();
  switch (pid) {
    case -1: 
      if ((check = printf("fork failed\n")) < 0) {
        perror("printf error");
        return 1;
      }
    break;

    case 0:
      if ((check = printf("CHILD + %d\n",pid)) < 0) {
        perror("printf error");
        return 1;
      }
    break;

    default:
      if ((check = printf("PARENT + %d\n",pid)) < 0) {
        perror("printf error");
        return 1;
      }
    break;
  }
  return 0;
}
