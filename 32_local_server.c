/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      32_local_server.c
 * @brief     Exercise on socket
 * @details   This program is TCP echo server listening	to port 8000, i.e. it
 *            replies back with the same text that the client sends to it. 
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
 
    while ((count = read(client_sockfd, message, sizeof(message))) > 0) {
      if ((write(client_sockfd, message, count)) < 0) {
        printf("error no >> %d\n", errno);
        perror("write");
        return EXIT_FAILURE;
      }
    }
    if ((close(client_sockfd)) < 0) {
      printf("error no >> %d\n", errno);
      perror("close");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
