/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      30_reconfigure.c
 * @brief     Exercise on signals
 * @details   This program re-reads a reconfigure.conf file everytime a SIGHUP signal
 *            is received. Using the values in the reconfigure.conf file the program
 *            is able to change its behavior without actually requiring	a termination 
 *            and restart 
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
#include <stdlib.h>
#include <signal.h>

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
static int count = 0;
static char c;

/*************************************************************************************
 *                          PRIVATE FUNCTIONS                                        *
 *************************************************************************************/
/**************************************************************************************************
Name        : read_config_file
Input(s)    : signum: signal number
Output(s)   : prints character and count
Description : This function is a signal handler
***************************************************************************************************/
static void read_config_file(int signum)
{
  FILE *fd;
  char *line;
  size_t len = 0;
  if ((fd = fopen("/tmp/reconfigure.conf", "r")) == NULL) {
    printf("Error No >> %d\n", errno);
    perror("fopen");
    return;
  }

  if (getline(&line, &len, fd) < 0) {
    printf("Error No >> %d\n", errno);
    perror("getline");
    return;
  }

  c = line[0];
  if (getline(&line, &len, fd) < 0) {
    printf("Error No >> %d\n", errno);
    perror("getline");
    return;
  }
  count = atoi(line);
  printf("read char = %c and count = %d\n", c, count);
  if (fclose(fd) == EOF) {
    printf("Error No >> %d\n", errno);
    perror("fclose");
    return;
  }
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
  int i;
  if (signal(SIGHUP, read_config_file) == SIG_ERR) {
    printf("Error No >> %d\n", errno);
    perror("signal");
    return EXIT_FAILURE;
  }
  
  if (raise(SIGHUP) != 0) {
    printf("raise error\n");
    return EXIT_FAILURE;
  }

  while (1) {
    for (i = 0; i < count; i++) {
      if (putchar(c) == EOF) {
        printf("putchar error\n");
        return EXIT_FAILURE;
      }
    }
    if (putchar('\n') == EOF) {
      printf("putchar error\n");
      return EXIT_FAILURE;
    }
    sleep(3);
  }
  return EXIT_SUCCESS;
}
