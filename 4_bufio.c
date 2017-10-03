/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char *argv[]) {
  /* Local Variables */
  int size, count, i;
  char *buffer;
  FILE *fd;
  
  /*Verify User Input*/
  if (3 != argc) {
    printf("Usage %s <blocksize> <blockcount>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fd = fopen("test" , "w")) == 0) {
    printf("Error no >> %d\n", errno);
    perror("test");
    exit(EXIT_FAILURE);
  }
 
  size = atoi(argv[1]);
  count = atoi(argv[2]);

  buffer = malloc(size);

  for (i=0; i<count; i++) {
    fwrite(buffer, 1, size, fd);
  }

  fclose(fd);
}
