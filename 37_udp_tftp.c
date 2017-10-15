/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      37_udp_tftp.c
 * @brief     Exercise on udp
 * @details   A UDP client to stream a file from the TFTP server and display it on stdout
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

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/
#define TFTP_PORT	69	
#define BSIZE		600	
#define MODE		"octet"
#define OP_RRQ		1	
#define OP_DATA		3
#define OP_ACK		4
#define	OP_ERROR	5

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
  struct sockaddr_in server;		
  struct hostent *host;		
  char   buffer[BSIZE], *p;
  int    count, server_len;

  if (argc != 3) {
    printf("usage: %s hostname filename\n", argv[0]);
    return EXIT_FAILURE;
  }

  sock = socket(AF_INET, SOCK_DGRAM, 0);

  if ((host = gethostbyname(argv[1])) == NULL) {
    printf("unknown host: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  server.sin_family = AF_INET;
  memcpy(&server.sin_addr.s_addr, host->h_addr, host->h_length);
  server.sin_port = htons(TFTP_PORT);
                                                            
  *(short *)buffer = htons(OP_RRQ);
  p = buffer + 2;
  strncpy(p, argv[2], sizeof(argv[2]));	
  p += strlen(argv[2]) + 1;
  strncpy(p, MODE, sizeof(MODE));
  p += strlen(MODE) + 1;

  count = sendto(sock, buffer, p-buffer, 0, (struct sockaddr *)&server, sizeof server);

  do {
    server_len = sizeof server;
    count = recvfrom(sock, buffer, BSIZE, 0, (struct sockaddr *)&server, &server_len);
    if (ntohs(*(short *)buffer) == OP_ERROR) {
      printf("stream: %s\n", buffer+4);
    } else {
      if (write(1, buffer+4, count-4) < 0) {
        perror("write");
        return EXIT_FAILURE;
      }
      *(short *)buffer = htons(OP_ACK);
      sendto(sock, buffer, 4, 0, (struct sockaddr *)&server, sizeof server);
    }
  } while (count == 516);
  return 0;
}
