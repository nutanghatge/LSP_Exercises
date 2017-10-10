/*===================================================================================*/
/*************************************************************************************/
/**
 * @file      12_monitor.c
 * @brief     Exercise on inotify
 * @details   This program  monitors first 100 files mentioned in a monitor.conf
              file for modification and deletion and report all changes to amonitor.log 
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
#include <errno.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

/*************************************************************************************
 *                          LOCAL MACROS                                             *
 *************************************************************************************/
#define FILEPATH "monitor.conf"
#define LOGFILE "monitor.log"
#define BUFSIZE (100 * (sizeof(struct inotify_event) + NAME_MAX + 1))

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
  FILE *fconfig, *fout;
  struct inotify_event *event;
  struct stat statBuf;
  char watchName[PATH_MAX];
  int notifyFd, watchFd, n;
  char eventBuf[BUFSIZE];
  char watchedNames[100][NAME_MAX + 1];
  char *p;

  if ((notifyFd = inotify_init()) < 0) {
    printf("Error no >> %d\n", errno);
    perror("inotify_init");
    return EXIT_FAILURE;
  }

  if ((fconfig = fopen(FILEPATH,"r")) == NULL) {
    printf("Error no >> %d\n", errno);
    perror("fopen");
    return EXIT_FAILURE;
  }

  while ((fgets(watchName, PATH_MAX, fconfig)) != NULL) {
    watchName[strlen(watchName) - 1] = '\0';
    if (stat(watchName, &statBuf) < 0) {
      if ((printf("Cannot stat %s, ignored\n", watchName)) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
      continue;
    }

    if (S_ISREG(statBuf.st_mode)) {
      if ((watchFd = inotify_add_watch(notifyFd, watchName, IN_MODIFY | IN_DELETE_SELF)) < 0) {
        if ((printf("Error adding watch\n")) < 0) {
          perror("printf error");
          return EXIT_FAILURE;
        }
      } else {
        if ((printf("Added %s to watch list on descriptor %d\n", watchName, watchFd)) < 0) {
          perror("printf error");
          return EXIT_FAILURE;
        }
        strncpy(watchedNames[watchFd], watchName, strlen(watchName));
      }
    } else {
      if ((printf("%s is not a regular file, ignored\n", watchName)) < 0) {
        perror("printf error");
        return EXIT_FAILURE;
      }
    }
  }
 
  if ((fout = fopen(LOGFILE, "a")) == NULL) {
     perror("fopen");
     return EXIT_FAILURE;
   }

   while (1) {
     if ((n = read(notifyFd, eventBuf, BUFSIZE)) < 0) {
       perror("read system call");
       return EXIT_FAILURE;
     }
     
     for (p = eventBuf; p < eventBuf + n;) {
       event = (struct inotify_event *) p;
       p += sizeof(struct inotify_event) + event->len;
       
       if (event->mask & IN_MODIFY) {
         if ((fprintf(fout,"%s was modified\n", watchedNames[event->wd])) < 0) {
           perror("fprintf error");
           return EXIT_FAILURE;
         }
       }

       if (event->mask & IN_DELETE_SELF) {
         if ((fprintf(fout,"%s was deleted\n", watchedNames[event->wd])) < 0) {
           perror("fprintf error");
           return EXIT_FAILURE;
         }
       }
      
       if((fflush(fout)) < 0) {
         perror("fflush error");
         return EXIT_FAILURE;
       }
     }
  }
}
  

