/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      global.h
 * @brief     Implements a singly linked list data structure with void * payload
 * @details   A collection of utility functions to implement a singly linked list
 *            data structure of void pointer payload.
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
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/*************************************************************************************
 *                          INCLUDES                                                 *
 *************************************************************************************/
#include <stdbool.h>

/*************************************************************************************
 *                          GLOBAL MACROS                                            *
 *************************************************************************************/

/*************************************************************************************
 *                          GLOBAL TYPEDEFS                                          *
 *************************************************************************************/

/*************************************************************************************
 *                          GLOBAL VARIABLES                                         *
 *************************************************************************************/

/*************************************************************************************
 *                          PUBLIC FUNCTIONS                                         *
 *************************************************************************************/
/********************************************//**
 * @brief   Service to the rot13 server
 * @details This function provides a service to rotate each character from a string to rotate by 13
 * @param   in: file descriptor from where to read from
 * @param   out: file descriptor to where to write to
 * @return
 ***********************************************/
int rot13_service(int in, int out);

/********************************************//**
 * @brief   rotate each character by 13
 * @details This function rotates each character by 13 
 * @param   *s: input string
 * @param   n: length
 * @return
 ***********************************************/
int rot13(unsigned char *s, int n); 

#endif
