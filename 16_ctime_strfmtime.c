/* A program to use ctime() and strfmtime() */
/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Macros */
#define FORMAT "%a %b %d %H:%M:%S %Y"
#define TEST_FILE "test"

int main() {
  /* Local Variables and declarations */
  char date[70];
  struct stat statbuf;
  int fd, check;

  if ((fd = open(TEST_FILE, O_RDWR | O_CREAT)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("open system call error");
    return 1;
  }
  if ((check = fstat(fd, &statbuf)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("Stat"); 
    return 1;
  }
  /* extract modified time and set it as per required format */
  strftime(date, sizeof(date), FORMAT, localtime(&(statbuf.st_atime)));
  printf("%s\n%s\n", date, ctime(&(statbuf.st_ctime)));
  return 0;
}
