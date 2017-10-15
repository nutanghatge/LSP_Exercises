/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      25_shell_pipe.c
 * @brief     Exercise on pipes
 * @details   This program is the shell program that support a shell that can handle 
 *            inputs any commands input	with a max of one pipe. 
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
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
Name        : prompt_and_parse
Input(s)    : **u : upstream array **d: downstream array.
Output(s)   : This function prints a prompt, reads in a command line, and parses it, placing  pointers
              to the individual  tokens prior to a "|"  token into the upstream  array  (u),  and 
              tokens following a "|" token (if any) into the downstream array (d).Both arrays are 
              terminated by a NULL pointer
***************************************************************************************************/
static int prompt_and_parse(char **u, char **d) {
  static char line[100];
  d[0] = NULL;
  if (printf("ashish> ") < 0) {
    perror("printf error");
    return -1;
  }
  if (gets(line) == NULL) {
    return -1;
  }
  *u++ = strtok(line, " \t");
  while (*u = strtok(NULL, " \t")) {
    if (strncmp(*u, "|", 1) == 0) {
      *u = NULL;
      while (*d++ = strtok(NULL, " \t")) {
        return 1;
      }
      u++;
    }
  }
  return 1;
}

/*************************************************************************************
 *                          PUBLIC FUNCTIONS                                         *
 *************************************************************************************/
/*************************************************************************************
 * Refer to the header file for a detailed description                               *
 *************************************************************************************/
int main() {
  int p[2], ret;
  char *upstream[20], *downstream[20];

  while (prompt_and_parse(upstream, downstream) > 0) {
    if (downstream[0] == NULL) {
      if (fork() == 0) {
        if (execvp(upstream[0], upstream) < 0) {
          printf("error no >> %d\n", errno);
          perror("execvp");
          return EXIT_FAILURE;
        }
	if (printf("%s: not found\n", upstream[0]) < 0) {
          perror("printf");
          return EXIT_FAILURE;
        }
	return EXIT_FAILURE;
	} else {
	wait(0);
	}
    } else {
      if (pipe(p) < 0) {
        printf("error no >> %d\n", errno);
        perror("pipe");
        return EXIT_FAILURE;
      }
      if ((ret = fork()) < 0) {
        printf("error no >> %d\n", errno);
        perror("fork");
        return EXIT_FAILURE;
      }
      if (ret == 0) {
        if (dup2(p[1], 1) < 0) {
          printf("error no >> %d\n", errno);
          perror("dup2");
          return EXIT_FAILURE;
        }
   
        if (close(p[0]) < 0) {
          printf("error no >> %d\n", errno);
          perror("close");
          return EXIT_FAILURE;
        }
        if (execvp(upstream[0], upstream) < 0) {
          printf("error no >> %d\n", errno);
          perror("execvp");
          return EXIT_FAILURE;
        }
        printf("%s: not found\n", upstream[0]);
        return EXIT_FAILURE;
      }

      if ((ret = fork()) < 0) {
        printf("error no >> %d\n", errno);
        perror("fork");
        return EXIT_FAILURE;
      }
      if (ret == 0) {
        if (dup2(p[0], 0) < 0) {
          printf("error no >> %d\n", errno);
          perror("dup2");
          return EXIT_FAILURE;
        }
   
        if (close(p[1]) < 0) {
          printf("error no >> %d\n", errno);
          perror("close");
          return EXIT_FAILURE;
        }
        if (execvp(downstream[0], downstream) < 0) {
          printf("error no >> %d\n", errno);
          perror("execvp");
          return EXIT_FAILURE;
        }
        printf("%s: not found\n", downstream[0]);
        return EXIT_FAILURE;
      } else {
        if (close(p[0]) < 0) {
          printf("error no >> %d\n", errno);
          perror("close");
          return EXIT_FAILURE;
        }
        if (close(p[1]) < 0) {
          printf("error no >> %d\n", errno);
          perror("close");
          return EXIT_FAILURE;
        }
        wait(0);
        wait(0);
      }
    }
  }
}
