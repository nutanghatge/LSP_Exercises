/* A program that prints out all the arguments input to	it (similar to echo) */
/* Header Files */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int i, check;
  /* Validate arguments*/
  if (argc < 2) {
    printf("Usage %s <string1> <string2> ...\n", argv[0]);
    return 0;
  }
  
  /* print input arguments to screen */
  for(i = 1; i < argc; i++) {
    if ((check = write(1, argv[i], strlen(argv[i]))) < 0) {
      printf("Error No >> %d\n", errno);
      perror(argv[i]);
      return 1;
    }
    if ((check = write(1, " ", 1)) < 0) {
      printf("Error No >> %d\n", errno);
      perror(argv[i]);
      return 1;
    }
  } 
  if ((check = write(1, "\n", 1)) < 0) {
    printf("Error No >> %d\n", errno);
    perror(argv[i]);
    return 1;
  }
  return 0;
}
