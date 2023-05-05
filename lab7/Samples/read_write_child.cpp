// Modified from page 7 of Interprocess Communication in Unix by John
// Shapely Gray

// checking errno and using perror

#include <cstdio>
#include <cstdlib>
#include <errno.h>     //needed for perror
#include <fcntl.h>     //needed for open
#include <sys/stat.h>  //needed for open
#include <sys/types.h> //needed for open
#include <unistd.h>

using namespace std;

extern int errno;
// extern char *sys_errlist[];

int main(int argc, char *argv[])
{
  int inFile;
  int n_char = 0, buffer[10];

  // Initially n_char is set to 0 -- errno is 0 by default
  printf("n_char = %d \t errno = %d\n", n_char, errno);

  inFile = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  printf("\ninFile = %d \t errno = %d\n", inFile, errno);
  if (inFile == -1)
  {
    perror("Trying to open file: ");
    exit(1);
  }

  // Use the read system call to obtain 10 characters from inFile
  while ((n_char = read(0, buffer, 10)) != 0)
  {
    // Display the characters read
    n_char = write(inFile, buffer, n_char);
  }

  struct stat statBuf;
  int err;

  close(inFile);

  return 0;
}
