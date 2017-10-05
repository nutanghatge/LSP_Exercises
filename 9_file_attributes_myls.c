/* A program to print output file attributes similar to ls –l on a single file */
/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

  /* Local Variables and declarations */
  struct stat statbuf;
  struct group *grp;
  struct passwd *pwd;
  char date[20];
  int check;

  /*Verify User Input*/
  if (2 != argc) {
    printf("Usage %s <file name>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((check = stat(argv[1], &statbuf)) < 0) {
    printf("Error no >> %d\n", errno);
    perror(argv[1]);
    return 1;
  }
  /* get username and groupname */
  if ((grp = getgrgid(statbuf.st_gid)) == NULL) {
    printf("Error no >> %d\n", errno);
    perror("Groupname");
    return 1;
  } 

  if ((pwd = getpwuid(statbuf.st_uid)) == NULL) {
    printf("Error no >> %d\n", errno);
    perror("Username");
    return 1;
  }

  /* extract modified time and set it as per required format */
  strftime(date, 20, "%b %d %R", localtime(&(statbuf.st_mtime)));

  /* display permission attributes*/
  if (S_ISREG(statbuf.st_mode)) {
    printf("-%c%c%c%c%c%c%c%c%c",
          (statbuf.st_mode & S_IRUSR) ? 'r' : '-',
          (statbuf.st_mode & S_IWUSR) ? 'w' : '-',
          (statbuf.st_mode & S_IXUSR) ? 'x' : '-',
          (statbuf.st_mode & S_IRGRP) ? 'r' : '-',
          (statbuf.st_mode & S_IWGRP) ? 'w' : '-',
          (statbuf.st_mode & S_IXGRP) ? 'x' : '-',
          (statbuf.st_mode & S_IROTH) ? 'r' : '-',
          (statbuf.st_mode & S_IWOTH) ? 'w' : '-',
          (statbuf.st_mode & S_IXOTH) ? 'x' : '-');
  
  /* display <num of links> <username> <groupname> <file size> <last modified time> <file name>*/
    printf(" %ld %s %s %ld %s %s\n", statbuf.st_nlink, pwd->pw_name, grp->gr_name, statbuf.st_size, date, argv[1]);
  } 
  return 0;
}
