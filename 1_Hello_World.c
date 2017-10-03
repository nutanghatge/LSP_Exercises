#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

int main() { 
  /*Local Variables*/
  int fd;

  /*Open a file named hello for write operation, create a new one if its not present*/
  if ((fd = open("hello", O_WRONLY | O_CREAT, 0644)) < 0) { 
    /*Error*/
    printf("The Error no. is: %d\n", errno);
    perror("hello");
    return EXIT_FAILURE; 
  } 

  /*Write a string in a file named hello*/
  write(fd, "Hello World", 11);
  close(fd);
  return EXIT_SUCCESS; 
} 
