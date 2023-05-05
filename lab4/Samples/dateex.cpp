#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
  int status;

  pid_t fork_return;

  // char *myargv[] = {(char *)"/bin/date", (char *)"date", NULL};
  char *myargv[] = {(char *)"ls", (char *)"-l", NULL};

  fork_return = fork();

  if (fork_return == 0) {
    // execl("/bin/date","date",NULL);//works
    // execl("date","date",NULL);//doesn't work
    // execlp("ls,"ls","-l",NULL); //works
    // execv(myargv[0], &myargv[1]);
    execvp(myargv[0], myargv);
    printf("You should not see me. ");
    perror("Fork...");
  }

  else if (fork_return > 0)
  {
    wait(&status);
    printf("In the PARENT process\n");
  }
  else
  {
    printf("Error\n");
  }
  return 0;
}
