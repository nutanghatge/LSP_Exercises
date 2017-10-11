/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      18_process_time.c
 * @brief     Exercise on sysconf,clock,times
 * @details   This program measures time taken by a process. 
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
#include <sys/fcntl.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/times.h>

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
  struct tms tmsbuf;
  long i, retVal;

  if ((retVal = sysconf(_SC_CLK_TCK)) < 0) {
    printf("Error no >> %d\n", errno);
    perror("sysconf");
    return EXIT_FAILURE;
  }

  if ((printf("clock ticks %ld\n", retVal)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  
  if ((printf("CLOCKS PER SEC %ld\n", CLOCKS_PER_SEC)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
   
  for (i = 0; i < 100000; i++);
  
  times(&tmsbuf);
  if ((printf("utime = %ld\n", tmsbuf.tms_utime)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
   
  if ((printf("stime = %ld\n", tmsbuf.tms_stime)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }

  if ((printf("cutime = %ld\n", tmsbuf.tms_cutime)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }

  if ((printf("cstime = %ld\n", tmsbuf.tms_cstime)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  
  if ((printf("clock = %ld\n", clock())) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
