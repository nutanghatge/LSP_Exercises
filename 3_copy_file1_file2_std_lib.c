/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Macros */
#define SIZE 50

int main() {
  /* local variables */
  FILE *fd1,*fd2;
  int count;
  char buff[SIZE];

  /* open file1 in readonly mode */
  if ((fd1 = fopen("file1", "r")) == 0) {
    printf("error no >> %d\n", errno);
    perror("file1");
    return EXIT_FAILURE;
  }

  /* open file2 or create if it doesnt exist */
  if ((fd2 = fopen("file2", "w")) == 0) {
    printf("error no >> %d\n", errno);
    perror("file2");
    return EXIT_FAILURE;
  }
  
  /* read contents of file1 and write it in file2 */
  while ((count = fread(buff, 1, sizeof (buff), fd1)) > 0) { 
    fwrite(buff, 1, count, fd2);
  } 	
  fclose(fd1);
  fclose(fd2);
  return EXIT_SUCCESS;
}
