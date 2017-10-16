/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      41_thread.c
 * @brief     Exercise on threads
 * @details   This program spawns a thread, prints that it is in the thread, sleeps 
 *            for 1000seconds and returns exit code 99. The parent waits for the thread	
 *            to complete, and prints out the child’s exit code 
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
#include <pthread.h>
#include <sys/types.h>
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
Name        : func
Input(s)    : arg: string 
Output(s)   : prints a string passed as input and exit with code 99
Description : This is a simple thread handler
***************************************************************************************************/
static void *func(void *arg) {
    if (printf("child thread says %s\n", (char *)arg) < 0) {
      perror("printf error");
    }
    sleep(1000);
    pthread_exit((void *)99);
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
    pthread_t handle;
    int exitcode;
    int error;
    
    if ((error = pthread_create(&handle, NULL, func, "hi!")) != 0) {
      printf("Error no >> %d\n", error);
      perror("pthread_create");
      return EXIT_FAILURE;
    }
    if (printf("primary thread says hello\n") < 0) {
      perror("printf error");
      return EXIT_FAILURE;
    }
    if ((error = pthread_join(handle, (void **)&exitcode)) != 0) {
      printf("Error no >> %d\n", error);
      perror("pthread_join");
      return EXIT_FAILURE;
    }
    if (printf("exit code %d\n", exitcode) < 0) {
      perror("printf error");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
