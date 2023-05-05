#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFLEN 10

int main(void)
{
  int i;
  char buffer[BUFLEN + 1];
  pid_t fork_return;

  fork_return = fork();

  if (fork_return == 0)
  {
    strncpy(buffer, "CHILD\n", BUFLEN); /*in the child process*/
    buffer[BUFLEN] = '\0';
  }
  else if (fork_return > 0)
  {
    strncpy(buffer, "PARENT\n", BUFLEN); /*in the parent process*/
    buffer[BUFLEN] = '\0';
  }
  else if (fork_return == -1)
  {
    printf("ERROR:\n");
    switch (errno)
    {
    case EAGAIN:
      printf("Cannot fork process: System Process Limit Reached\n");
    case ENOMEM:
      printf("Cannot fork process: Out of memory\n");
    }
    return 1;
  }

  for (i = 0; i < 5; ++i) /*both processes do this*/
  {
    sleep(1); /*5 times each*/
    printf("%s", buffer);
    fflush(stdout);
  }

  if (fork_return > 0)
  {
    int status;
    wait(&status);
    if (WIFEXITED(status))
      printf("\n Child returned: %d\n", WEXITSTATUS(status));
  }

  return 10;
}
