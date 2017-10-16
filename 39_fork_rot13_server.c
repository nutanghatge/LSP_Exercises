/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      39_fork_rot13_server.c
 * @brief     Exercise on fork
 * @details   This program is TCP server which returns every character rotated by
 *            13 (plus 13, modulo 26) and uses fork
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
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/
#define SERVER_PORT 8000

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
Name        : rot13
Input(s)    : *s: string 
               n: length 
Output(s)   : character rotated by 13
Description : This function rotates each character by 13 
***************************************************************************************************/
static int rot13(unsigned char *s, int n) {
  unsigned char *p;
  for (p = s; p < s + n; p++) {
    if (islower(*p)) {
      *p += 13;
      if (*p > 'z') *p -= 26;
    }
   }
  return EXIT_SUCCESS;
}

/**************************************************************************************************
Name        : rot13_service
Input(s)    : in: file descriptor from where to read from
              out: file descriptor to where to write to
Output(s)   : each character from a message rotated by 13
Description : This function provides a service to rotate each character from a string to rotate by 13 
***************************************************************************************************/
static int rot13_service(int in, int out) {
  unsigned char buf[1024];
  int count;
  while ((count = read(in, buf, 1024)) > 0) {
    if ((rot13(buf, count)) < 0) {
      if ((printf("Rotation failed\n")) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
      return EXIT_FAILURE;
    }
    if ((write(out, buf, count)) < 0) {
      perror("write");
      return EXIT_FAILURE;
    }
  }
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
  int server_sockfd, client_sockfd;
  int server_len, client_len, count;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char message[1000];

  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
   printf("error no >> %d\n", errno);
    perror("signal");
    return EXIT_FAILURE;
  }

  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("error no >> %d\n", errno);
    perror("socket");
    return EXIT_FAILURE;
  }
 
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_len = sizeof(server_address);
  server_address.sin_port = htons(SERVER_PORT);

  if ((bind(server_sockfd, (struct sockaddr *)&server_address, server_len)) < 0) {
    printf("error no >> %d\n", errno);
    perror("bind");
    return EXIT_FAILURE;
  }

  if ((listen(server_sockfd, 5)) < 0) {
    printf("error no >> %d\n", errno);
    perror("listen");
    return EXIT_FAILURE;
  }
  
  while (1) {
    if ((printf("server waiting\n")) < 0) {
      printf("error no >> %d\n", errno);
      perror("printf error");
      return EXIT_FAILURE;
    }

    client_len = sizeof(client_address);
    if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len)) < 0) {
      printf("error no >> %d\n", errno);
      perror("accept");
      return EXIT_FAILURE;
    }
    if (fork() == 0) {
      if ((close(server_sockfd)) < 0) {
        printf("error no >> %d\n", errno);
        perror("close");
        return EXIT_FAILURE;
      }
      if (printf("new child (pid %d) using descriptor %d\n", getpid(), client_sockfd) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
      if ((rot13_service(client_sockfd, client_sockfd)) < 0) {
        return EXIT_FAILURE;
      }

      if ((close(client_sockfd)) < 0) {
        printf("error no >> %d\n", errno);
        perror("close");
        return EXIT_FAILURE;
      }
    } else {
      if ((close(client_sockfd)) < 0) {
        printf("error no >> %d\n", errno);
        perror("close");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
