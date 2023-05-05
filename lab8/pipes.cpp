// grep -i -n sed colorFile.txt > sed.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
  int f_des[2];

  if (pipe(f_des) == -1)
  {
    perror("Pipe");
    exit(1);
  }
  char *grepArguments[] = {(char*)"grep", (char*)"-o", (char*)"-i", (char*)"pipe", (char*)"colorFile.txt", NULL};
  char *wcArguments[] = {(char*)"wc", (char*)"-w", NULL};

  switch (fork())
  {
  case -1:
    perror("Fork");
    exit(2);
  case 0: /*In the child*/
    dup2(f_des[1], 1);
    close(f_des[0]);
    close(f_des[1]);
    execvp("grep", grepArguments);
    exit(3);
  default: /*In the parent*/
    dup2(f_des[0], 0);
    int newFile = open("newFile.txt", O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
    dup2(newFile, 1);
	  close(f_des[0]);
    close(f_des[1]); 
    execvp("wc", wcArguments);
    exit(4);
  }
}
