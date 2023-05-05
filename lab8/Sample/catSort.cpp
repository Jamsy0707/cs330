#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  int f_des[2];

  if (pipe(f_des) == -1)
  {
    perror("Pipe");
    exit(1);
  }
  switch (fork())
  {
  case -1:
    perror("Fork");
    exit(2);
  case 0: /*In the child*/
    dup2(f_des[1], 1);
    close(f_des[0]);
    close(f_des[1]);
    write(1, "In the child\n", strlen("In the child\n"));
    execl("/bin/cat", "cat", "colorFile.txt", NULL);
    exit(3);
  default: /*In the parent*/
    dup2(f_des[0], 0);
    
		close(f_des[0]);
    close(f_des[1]);  //Try commenting this line out and see what happens
    write(1, "In parent\n", strlen("In parent\n"));
    execl("/usr/bin/sort", "sort", NULL);
    exit(4);
  }
}
