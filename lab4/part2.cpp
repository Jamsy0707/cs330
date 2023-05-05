#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char mynum = '0';
int main(void)
{
  int i;
  pid_t fork_return;
  char buffer[10];
  fork_return = fork();
  if (fork_return == 0)
  {
    strcpy(buffer, "CHILD"); /*in the child process*/
    for (i = 0; i < 5; ++i)  /*both processes do this*/
    {
      mynum = i + '0';
      sleep(1); /*5 times each*/
      printf("%s%c\n", buffer, mynum);
      fflush(stdout);
    }
    return 0;
  }
  else if (fork_return > 0)
  {
    strcpy(buffer, "PARENT"); /*in the parent process*/
    for (i = 0; i < 5; ++i)   /*both processes do this*/
    {
      sleep(1); /*5 times each*/
      printf("%s%c\n", buffer, mynum);
      fflush(stdout);
    }
    return 0;
  }
  else
  {
    printf("error\n");
    fflush(stdout);
  }
}
