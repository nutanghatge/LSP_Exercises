/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      35_getaddinfo_client.c
 * @brief     Exercise on getaddinfo()
 * @details   Usage of getaddinfo() system call
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
  int sockfd, s, j;
  char message[BSIZE];
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  size_t len;
  ssize_t nread;

  if (argc < 3) {
    printf("Usage: %s host port msg...\n", argv[0]);
    return EXIT_FAILURE;
  }

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  if ((s = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0) {
    printf("Error no >> %d\n", errno);
    perror("getaddrinfo");
    return EXIT_FAILURE;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    if ((sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
      continue;
    }

    if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == -1) {
      perror("oops: client1");
      return EXIT_FAILURE;
    } else { 
      break;
    }
    
    if((close(sockfd)) < 0) {
      printf("error no >> %d\n", errno);
      perror("close");
      return EXIT_FAILURE;
    }
  }

  if (NULL == rp) {
    printf("Could not connect\n");
    return EXIT_FAILURE;
  }
 
  freeaddrinfo(result);

  for (j = 3; j < argc; j++) {
    len = strlen(argv[j]);
    if (len + 1 > BSIZE) {
      printf("Ignoring long message in argument %d\n", j);
      continue;
    }
  
    if (write(sockfd, argv[j], len) != len) {
      printf("partial/failed write\n");
      return EXIT_FAILURE;
    }

    if ((nread = read(sockfd, message, BSIZE)) == -1) {
      perror("read");
      return EXIT_FAILURE;
    }
    printf("Received %ld bytes: %s\n", (long) nread, message);
  }
  return EXIT_SUCCESS;
}
