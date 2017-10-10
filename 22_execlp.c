/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      22_execlp.c
 * @brief     Exercise on execlp()
 * @details   This program gives a choice to the user to either run ps,ls,date 
 *            and goof and run the command using execlp.
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
#include <string.h>

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
  char *command;
  int input;
  if ((printf("Please enter a number to get that command to be executed\n1.ps\n2.ls\n3.date\n4.goof\n")) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  if ((scanf("%d",&input)) == EOF) {
    perror("scanf");
    return EXIT_FAILURE;
  }
    
  switch (input) {
   case 1:
     if ((execlp("ps", "ps", NULL ,NULL)) == -1) {
       perror("execlp");
       return EXIT_FAILURE;
     }
     break;

   case 2:
     if ((execlp("ls", "ls", NULL ,NULL)) == -1) {
       perror("execlp");
       return EXIT_FAILURE;
     }
     break;

   case 3:
     if ((execlp("date", "date", NULL ,NULL)) == -1) {
       perror("execlp");
       return EXIT_FAILURE;
     }
     break;

   case 4:
     if ((execlp("goof", "goof", NULL ,NULL)) == -1) {
       perror("execlp");
       return EXIT_FAILURE;
     }
     break;

   default:
     printf("Invalid option\n");
     return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
