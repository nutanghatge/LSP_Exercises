/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
  /* Local Variables */
  int fd, size, count, i;
  char *buffer;
  
  /* Verify User Input*/
  if (3 != argc) {
    printf("Usage %s <blocksize> <blockcount>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fd = open("test" , O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
    printf("Error no >> %d\n", errno);
    perror("test");
    exit(EXIT_FAILURE);
  }
  size = atoi(argv[1]);
  count = atoi(argv[2]);

  /*Memory allocation*/
  buffer = malloc(size);

  for (i=0; i<count; i++) {
    write(fd, buffer, size);
  }

  close(fd);
}
