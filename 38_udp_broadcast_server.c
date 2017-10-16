/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      38_udp_broadcast_server.c
 * @brief     Exercise on udp
 * @details   This is a distributed update service,i.e. a service that uses UDP 
 *            broadcast to broadcast an update. The service also have a	client end
 *	      that listens for broadcasts and prints them.
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/
#define SERVER_PORT 2066
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
int main(int argc, char *argv[])
{
  int    sock;			
  struct sockaddr_in server, clientAddr;				
  char   buffer[BSIZE] = "This is a broadcast message\n";
  socklen_t addr_size;
  int broadcast = 1;

  if (argc != 2) {
    printf("usage: %s hostname\n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("socket error\n");
  }
  
  if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof broadcast) == -1) {
    perror("setsockopt (SO_BROADCAST)");
    return EXIT_FAILURE;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);
  
  if (bind(sock, (struct sockaddr *)&server, sizeof server) < 0) {
    printf("Error no >> %d\n", errno); 
    perror("bind");
    return EXIT_FAILURE;
  }
  server.sin_addr.s_addr = 0xffffffff;
  if (fork()) {
    while (1) {
      sendto(sock, buffer, BSIZE, 0, (struct sockaddr *)&server, sizeof server);
    }
  } else {
    while(1) {
      addr_size = sizeof(clientAddr);
      recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&clientAddr, &addr_size); 
      if (printf("Received from server: %s\n", buffer) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
    }
  } 
}
