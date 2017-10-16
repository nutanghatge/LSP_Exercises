/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      36_ipv6_server.c
 * @brief     Exercise on ipv6
 * @details   This program is TCP ipv6 server which returns every character rotated by
 *            13 (plus 13, modulo 26)
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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "global.h"

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
/*************************************************************************************
 *                          PUBLIC FUNCTIONS                                         *
 *************************************************************************************/
/*************************************************************************************
 * Refer to the header file for a detailed description                               *
 *************************************************************************************/
int rot13(unsigned char *s, int n) {
  unsigned char *p;
  for (p = s; p < s + n; p++) {
    if (islower(*p)) {
      *p += 13;
      if (*p > 'z') *p -= 26;
    }
   }
  return EXIT_SUCCESS;
}

/*************************************************************************************
 * Refer to the header file for a detailed description                               *
 *************************************************************************************/
int rot13_service(int in, int out) {
  unsigned char buf[1024];
  int count;
  while ((count = read(in, buf, 1024)) > 0) {
    if (rot13(buf, count) < 0) {
      if ((printf("Rotation failed\n")) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
      return EXIT_FAILURE;
    }
    if (write(out, buf, count) < 0) {
      perror("write");
      return EXIT_FAILURE;
    }
  }
}

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main() {
  int server_sockfd, client_sockfd;
  int server_len, client_len, count;
  struct sockaddr_in6 server_address;
  struct sockaddr_in6 client_address;
  char message[1000];

  if ((server_sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
    printf("error no >> %d\n", errno);
    perror("socket");
    return EXIT_FAILURE;
  }

  server_address.sin6_family = AF_INET6;
  server_address.sin6_addr = in6addr_any;
  server_len = sizeof(server_address);
  server_address.sin6_port = htons(SERVER_PORT);

  if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
    printf("error no >> %d\n", errno);
    perror("bind");
    return EXIT_FAILURE;
  }

  if (listen(server_sockfd, 5) < 0) {
    printf("error no >> %d\n", errno);
    perror("listen");
    return EXIT_FAILURE;
  }
  while (1) {
    if (printf("server waiting\n") < 0) {
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

    if (rot13_service(client_sockfd, client_sockfd) < 0) {
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
