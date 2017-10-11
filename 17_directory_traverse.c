/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      17_dir_traverse.c
 * @brief     Exercise on time
 * @details   This program recursively traverses a directory and build an hour by 
 *            hour historogram that tracks the last modification time of regular
 *            files and prints out the histogram 
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
#include <limits.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

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
static int modtimeHist[24];
static int rflag, aflag;

/*************************************************************************************
 *                          PRIVATE FUNCTIONS                                        *
 *************************************************************************************/
/**************************************************************************************************
Name        : processfile
Input(s)    : name: filename
Output(s)   : processes a fle to check modification time
Description : This function processes a file, check modification time and update the same in array
***************************************************************************************************/
static int processfile(char *name) { 
  struct stat sb;
  struct tm* bdtime;
  
  if ((printf("Processing file %s\n", name)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  if ((stat(name, &sb)) < 0) {
    perror("stat error");
  }
  if ((bdtime = localtime(&(sb.st_mtime))) < 0) {
    perror("localtime error");
    return EXIT_FAILURE;
  }
  modtimeHist[bdtime->tm_hour]++;
  return EXIT_SUCCESS;
}  

/**************************************************************************************************
Name        : processdir
Input(s)    : name: dirname
Output(s)   : processes a directory to check modification time
Description : This function processes a directory and files present inside a directory.
***************************************************************************************************/
static int processdir(char *dirname) {
  DIR *d;
  struct dirent *info;
  char fullFileName[PATH_MAX];
  struct stat statbuf;

  if ((printf("Processing a directory %s\n", dirname)) < 0) {
    perror("printf error");
    return EXIT_FAILURE;
  }
  
  if ((d = opendir(dirname)) < 0) {
    perror("opendir error");
    return EXIT_FAILURE;
  } 

  while ((info = readdir(d)) != NULL) {
    if (info->d_name[0] == '.' && !aflag) continue;
    
    strncpy(fullFileName, dirname, strlen(dirname));
    strncat(fullFileName, "/", 1);
    strncat(fullFileName, info->d_name, strlen(info->d_name));
    
    printf("full file name %s\n", fullFileName);
    if ((stat(fullFileName, &statbuf)) < 0) {
      perror("stat error");
    }
    if (strncmp(info->d_name, ".", 1) && strncmp(info->d_name, "..", 2) && rflag && S_ISDIR(statbuf.st_mode)) {
      if ((processdir(fullFileName)) < 0) {
        printf("failed to process directory %s\n", fullFileName);
        return EXIT_FAILURE;
      } 
    } else {
      if ((processfile(fullFileName)) < 0) {
        printf("failed to process directory %s\n", fullFileName);
        return EXIT_FAILURE;
      }
    }
  }
  if (closedir(d) < 0) {
    perror("closedir error");
    return EXIT_FAILURE;
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
int main(int argc, char *argv[]) {
  char dirname[PATH_MAX];
  int i,c;
  
  for (i = 0; i < 24; i++) modtimeHist[i] = 0;
  opterr = 0;

  while ((c = getopt(argc, argv, "ar")) != EOF) {
    switch (c) {
      case 'a':
        aflag = 1;
        break;

      case 'r':
        rflag = 1;
        break;
   
      case '?':
        fprintf(stderr,"Invalid option - %c\n", optopt);
        break;
    }
  }

  argv += optind;
  argc -= optind;

  if (argv[0][0] == '/') {
    strncpy(dirname, argv[0], PATH_MAX);
  } else {
    getcwd(dirname, PATH_MAX);
    strncat(dirname, "/", 1);
    strncat(dirname, argv[0], sizeof(argv[0]));
  }
  if ((processdir(dirname)) < 0) {
    return EXIT_FAILURE;
  }
   
  for (i = 0; i < 24; i++) {
    if ((printf("hour %2d: count %6d\n", i, modtimeHist[i])) < 0) {
      perror("printf error");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
