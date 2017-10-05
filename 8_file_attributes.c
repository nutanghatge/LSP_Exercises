/* A program to	print the last modified, last accessed and last	changed	attributes of an input file */
/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
  /* Local Variables and declarations */
  struct stat statBuf;
  char date[10];
  int check;  

  /*Verify User Input*/
  if (2 != argc) {
    printf("Usage %s <file name>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /* Check if the file is a regular file and print required details */
  if ((check = stat(argv[1], &statBuf)) < 0) {
    printf("Error No >> %d\n", errno);
    perror(argv[1]);
    return 1;
  }
  if (S_ISREG(statBuf.st_mode)) {
    printf("Last modified time: %s", ctime(&(statBuf.st_mtime)));
    printf("Last accessed time: %s", ctime(&(statBuf.st_atime)));
    printf("Last time attributes changed: %s\n", ctime(&(statBuf.st_ctime)));
    return 0;
  }
  return 1;
}
