/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      15_getopt_options.c
 * @brief     Exercise on getopt
 * @details   This program takes ‘c’, ‘v’,as Boolean options, ‘b’ as a numeric option,
 *            ‘f’ as a text option and remaining non-option arguments and prints out
 *            all the options that were set along with non-option arguments.
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
#include <unistd.h>

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main(int argc, char *argv[]) {
  /* Local Variables*/
  int opt;
  int check;
  if (argc < 3) {
    if ((check = printf("Usage %s <option> <argument>\n",argv[0])) < 0) {
      perror("printf error");
      return 1;
    }
  }
  /* Parse command options */
  while((opt = getopt(argc,argv, "cv:bf")) != -1) {
    switch(opt) {
      case 'c':
      case 'v':
        if ((check = printf("boolean option: %c\n", opt)) < 0) {
          perror("printf error");
          return 1;
        }
        break;

      case 'b':
        if ((check = printf("numeric option: %c\n", opt)) < 0) {
          perror("printf error");
          return 1;
        }
        break;
      
      case 'f':
        if ((check = printf("text option: %c\n", opt)) < 0) {
          perror("printf error");
          return 1;
        }
        break;

      default:
        if ((check = printf("unknown option: %c\n", opt)) < 0) {
          perror("printf error");
          return 1;
        }
        break;
    }
  }
  for(; optind < argc; optind++) {
    printf("argument: %s\n", argv[optind]);
  }
  return 0;
}

