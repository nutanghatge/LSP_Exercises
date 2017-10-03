/* Header files */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* Macros */
#define SIZE 50

int main() {
  /* local variables */
  int fd1,fd2,count;
  char buff[SIZE];

  /* open file1 in readonly mode */
  if ((fd1 = open("file1", O_RDONLY, 0644)) < 0) { 
    printf("Error no >> %d\n", errno);
    perror("File1");
    return EXIT_FAILURE;
  } 

  /* open file2 or create if it doesnt exist */
  if ((fd2 = open("file2", O_WRONLY | O_CREAT, 0644)) < 0) { 
    printf("Error no >> %d\n", errno);
    perror("File2");
    return EXIT_FAILURE;
  }
  
  /* read contents of file1 and write it in file2 */
  while ((count = read(fd1, buff, sizeof (buff))) > 0) { 
    write(fd2, buff, count);
  } 	
  close(fd1);
  close(fd2);
  return EXIT_SUCCESS;
}
