/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      10_dir_atri_approach2.c
 * @brief     Exercise on stat,dirent
 * @details   A program to print output file attributes similar to ls –l on a directory
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
#include <errno.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
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

/*************************************************************************************
 *                          PRIVATE FUNCTIONS                                        *
 *************************************************************************************/
/**************************************************************************************************
Name        : my_ls
Input(s)    : *name: char pointer to the file name 
Output(s)   : displays <filetype> <permission> <num of links> <username> <groupname> <file size> <last modified time> <file name> of a file
Description : This function lists the atrributes of a given file same as linux comand "ls -l" 
***************************************************************************************************/
static void my_ls(char *name) {
  struct stat statbuf;
  struct group *grp;
  struct passwd *pwd;
  char date[20];

  char *filetype[] = {"?","p","c","?","d","?","b","?","-","?","l","?","s"};
  char *modtime;

  if ((stat(name,&statbuf)) < 0) {
    perror("stat");
    return;
  }

  if ((grp = getgrgid(statbuf.st_gid)) == NULL) {
    printf("Error no >> %d\n", errno);
    perror("Groupname");
    return;
  }

  if ((pwd = getpwuid(statbuf.st_uid)) == NULL) {
    printf("Error no >> %d\n", errno);
    perror("Groupname");
    return;
  }

  if ((printf("%s", filetype[(statbuf.st_mode >> 12) & 017])) < 0) {
    perror("printf error");
    return;
  }

  if ((printf("%c%c%c%c%c%c%c%c%c",
             (statbuf.st_mode & S_IRUSR) ? 'r' : '-',
             (statbuf.st_mode & S_IWUSR) ? 'w' : '-',
             (statbuf.st_mode & S_IXUSR) ? 'x' : '-',
             (statbuf.st_mode & S_IRGRP) ? 'r' : '-',
             (statbuf.st_mode & S_IWGRP) ? 'w' : '-',
             (statbuf.st_mode & S_IXGRP) ? 'x' : '-',
             (statbuf.st_mode & S_IROTH) ? 'r' : '-',
             (statbuf.st_mode & S_IWOTH) ? 'w' : '-',
             (statbuf.st_mode & S_IXOTH) ? 'x' : '-')) < 0) {
    perror("printf error");
    return;
  }

  if ((strftime(date, 20, "%b %d %R", localtime(&(statbuf.st_mtime)))) == 0) {
    perror("strftime");
    return;
  }

  if ((printf(" %ld %s %s %ld %s %s\n", statbuf.st_nlink, pwd->pw_name, grp->gr_name, statbuf.st_size, date, name)) < 0) {
    perror("printf error");
    return;
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
  DIR *dp;
  struct dirent *entry;

  if (2 != argc) {
    printf("Usage %s <directory name>\n", argv[0]);
    return EXIT_FAILURE;;
  }
  
  if ((chdir(argv[1])) < 0) {
    perror(argv[1]);
    return EXIT_FAILURE;
  }

  if ((dp = opendir(".")) == NULL) {
    printf("Error No >> %d\n", errno);
    perror(argv[1]);
    return EXIT_FAILURE;
  } 
  
  while ((entry = readdir(dp)) != NULL) {
    my_ls(entry->d_name);
 }
 return EXIT_SUCCESS;
}      
