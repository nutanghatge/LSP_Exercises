/* Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/uio.h>

/* macros */
#define RECORDS 3
#define RECORD_FILE "records.dat"
#define FIRST_RECORD_NO 55

/* structure definition */
struct details {
  int id;
  char name[80];
};

/* Main function */
int main() {
  /* local variables */
  int fd, fd1, fd2, count, i, check;
  size_t size;
  struct details *record;
  char buffer[179];
  size = sizeof(struct details) * RECORDS;  

  /* Writing Records */
  if ((fd = open(RECORD_FILE, O_RDWR)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  
  /* mmap system call */
  if ((record = (struct details *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  for (i = 0; i < RECORDS; i++) {
    record[i].id = FIRST_RECORD_NO + i;
    if ((check = sprintf(record[1].name, "\tNoName\n")) < 0) {
      printf("Error No >> %d\n", errno);
      perror("Record Update");
      return 1;
    }
  }

  if ((check = write(fd, record, size)) < 0) {
    printf("Error No >> %d\n", errno); 
    perror(RECORD_FILE);
    return 1;
  }
   
  /*Contents of the record file before it is modified*/
  printf("Content of the record file before modification\n");
  
  if ((fd1 = open(RECORD_FILE, O_RDONLY)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  while ((count = read(fd1, buffer, 30)) > 0) {
    if ((check = write(1, buffer, count)) < 0) {
      printf("Error No >> %d\n", errno);
      perror(RECORD_FILE);
      return 1;
    }
  }

  /* Set the file offset to 0 */
  if ((check = lseek(fd, 0, SEEK_SET)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("lseek failed");
    return 1;
  } 

  /* Update second record */
  record[1].id = 53;
  if ((check = sprintf(record[1].name, "\tSUNeeta\n")) < 0) {
    printf("Error No >> %d\n", errno);
    perror("Record Update");
    return 1;
  }

  if ((check = write(fd, record, size)) < 0) {
    printf("Error No >> %d\n", errno);
    perror(RECORD_FILE);
    return 1;
  }
  
  /*Contents of the record file after it is modified*/
  printf("\nContent of the file after modification\n");

  if ((fd2 = open(RECORD_FILE, O_RDONLY)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  while ((count = read(fd2, buffer, 179)) > 0) {
    if ((check = write(1, buffer, count)) < 0) {
      printf("Error No >> %d\n", errno);
      perror(RECORD_FILE);
      return 1;
    }
  }
  if ((check = close(fd)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("error closing fd");
    return 1;
  }
  if ((check = close(fd1)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("error closing fd");
    return 1;
  }
  if ((check = close(fd2)) < 0) {
    printf("Error No >> %d\n", errno);
    perror("error closing fd");
    return 1;
  }
  return 0;
}
