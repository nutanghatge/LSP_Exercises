/* Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
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
  int fd,fd1,fd2,count,i;
  size_t size;
  struct details *record;
  char buffer[179];
  char buff[] = "Contents of the record file before it is modified\n";
  char buff1[] = "Contents of the record file after it is modified\n";
  
  size = sizeof (struct details) * RECORDS;  

  /* Writing Records */
  if ((fd = open(RECORD_FILE, O_RDWR)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  
  /* mmap system call */
  if((record = (struct details *) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED,fd, 0)) == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  for (i=0; i<RECORDS; i++) {
    record[i].id = FIRST_RECORD_NO + i;
    sprintf(record[i].name, "\tNoName\n");
  }

  write(fd, record, size);
   
  /*Contents of the record file before it is modified*/
  write(1,buff,sizeof (buff));

  if ((fd1 = open(RECORD_FILE, O_RDONLY)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  while ((count = read(fd1,buffer,30)) > 0) {
    write(1,buffer,count);
  }

  /* Set the file offset to 0 */
  lseek(fd, 0, SEEK_SET);
 
  /* Update second record */
  record[1].id = 53;
  sprintf(record[1].name,"\tSUNeeta\n");
  write(fd, record, size);
  
  /*Contents of the record file after it is modified*/
  write(1,buff1,sizeof(buff1));
  if ((fd2 = open(RECORD_FILE, O_RDONLY)) < 0) {
    perror(RECORD_FILE);
    exit(1);
  }
  while ((count = read(fd2,buffer,179)) > 0) {
    write(1,buffer,count);
  }
  close(fd);
  close(fd1);
  close(fd2);
}
