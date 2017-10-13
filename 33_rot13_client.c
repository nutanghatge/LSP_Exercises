/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      32_local_client.c
 * @brief     Exercise on socket
 * @details   This program is TCP echo server listening to port 8000, i.e. it
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
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/
#define SERVER_PORT 8000
#define BSIZE 1024
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
int main(int argc, char *argv[]) {
  int sockfd;
  int len, count;
  struct sockaddr_in address;
  struct hostent *hostinfo;
  char message[BSIZE];
  char *server_name;

  server_name = (argc > 1) ? argv[1] : "localhost" ;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("error no >> %d\n", errno);
    perror("socket");
    return EXIT_FAILURE;
  }

  if ((hostinfo = gethostbyname(server_name)) == NULL) {
    printf("error no >> %d\n", h_errno);
    return EXIT_FAILURE;
  }
  
  address.sin_family = AF_INET;
  memcpy((char *)&address.sin_addr, hostinfo->h_addr, hostinfo->h_length);
  len = sizeof(address);
  address.sin_port = htons(SERVER_PORT);
  
  if ((connect(sockfd, (struct sockaddr *)&address, len)) < 0) {
    perror("oops: client1");
    return EXIT_FAILURE;
  }

  while ((count = read(sockfd, message, BSIZE)) > 0) {
      if ((write(sockfd, message, count)) < 0) {
        printf("error no >> %d\n", errno);
        perror("write");
        return EXIT_FAILURE;
      }
      if ((read(sockfd, message, count)) < 0) {
        printf("error no >> %d\n", errno);
        perror("write");
        return EXIT_FAILURE;
      }
      if ((write(1, message, count)) < 0) {
        printf("error no >> %d\n", errno);
        perror("write");
        return EXIT_FAILURE;
      }
    if ((printf("message from server = %s\n", message)) < 0) {
      printf("error no >> %d\n", errno);
      perror("printf");
      return EXIT_FAILURE;
    }
  }
  
  if((close(sockfd)) < 0) {
    printf("error no >> %d\n", errno);
    perror("close");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
