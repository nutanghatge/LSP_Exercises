#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define SOURCE_FILE "sam"
#define DEST_FILE "tst"

int main() {
  int fdSrc, fdDst;
  char *srcAddr, *dstAddr;
  size_t size;

  if ((fdSrc = (SOURCE_FILE, O_RDONLY)) < 0) {
    printf("Error Num >> %d\n", errno);
    perror(SOURCE_FILE);
  }

  if ((fdDst = (DEST_FILE, O_WRONLY | O_CREAT)) < 0) {
    printf("Error Num >> %d\n", errno);
    perror(DEST_FILE);
  }

  size = lseek(fdSrc, 0, SEEK_END);
  if ((srcAddr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fdSrc,0)) == MAP_FAILED) {
    perror("source map error");
    exit(1);
  }

  if ((dstAddr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fdDst,0)) == MAP_FAILED) {
    perror("mmap error");
    exit(2);
  }

  memcpy(dstAddr, srcAddr, size);
  msync(dstAddr, size, MS_SYNC);
}  
  
  
  
 
