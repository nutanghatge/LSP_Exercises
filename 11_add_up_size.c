/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      11_add_up_size.c
 * @brief     Exercise on dirent,stat
 * @details   A program to add up the total size of files in a given directory.
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
#include <dirent.h> 
#include <stdio.h> 
#include <sys/stat.h> 
#include <errno.h>
#include <unistd.h>

/*************************************************************************************
 *                          MACROS                                                   *
 *************************************************************************************/
#define FOLDERPATH "/home/nutanghatge/LSP/bin"

/*************************************************************************************
 *                          MAIN                                                     *
 *************************************************************************************/
int main(void)
{
  /* Local Variables */
  DIR *d;
  struct dirent *dir;
  struct stat statbuf;
  size_t size;
  int check;
  size = 0;

  /* change current directory to the given directory */
  if ((check = chdir(FOLDERPATH)) < 0) {
    if ((check = printf("Error no >> %d\n", errno)) < 0) {
      perror("printf error");
      return 1;
    }
    perror("chdir");
    return 1;
  }

  /* open current directory */
  d = opendir(".");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if ((check = stat(dir->d_name,&statbuf)) < 0) {
        if ((check = printf("Error no >> %d\n", errno)) < 0) {
          perror("printf error");
          return 1;
        }
        perror("stat");
        return 1;
      }
      size = size + (statbuf.st_size);
    }
    if ((check = printf("total size of all files %ld\n", size)) < 0) {
      perror("printf error");
      return 1;
    }
    closedir(d);
    return 0;
  }
  if ((check = printf("Error no >> %d\n", errno)) < 0) {
    perror("printf error");
    return 1;
  }
  perror("opendir");
  return 1;
}
