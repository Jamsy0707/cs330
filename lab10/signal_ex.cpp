/*
1. q Terminate: SIGALRM
    Core: SIGBUS
    Stop: SIGTSTP
    Ignore: SIGCHLD

2. SIGKILL and SIGSTOP
*/

// original code from http://jan.netcomp.monash.edu.au/OS/l8_1.html
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> //added this to the original
#include <time.h>

static void intHandler(int signalNo, siginfo_t *info, void *context)
{
  printf("Signal received %i\n", signalNo);
  if (signalNo == SIGURG)
    printf("Child received signal!\n");
  else if (signalNo == SIGCHLD)
    printf("Parent recieved signal!\n");

  exit(signalNo);
}

int main(int argc, char *argv[])
{
  pid_t pid;

  // Variables needed for signals
  sigset_t interruptMask;
  struct sigaction act;

  // set the stage (the bitmask)
  sigemptyset(&interruptMask);
  sigaddset(&interruptMask, SIGURG);
  sigaddset(&interruptMask, SIGCHLD);

  // Hook up the signalhandler to SIGINT and SIGURG
  act.sa_sigaction = &intHandler;
  act.sa_mask = interruptMask;
  act.sa_flags = SA_SIGINFO;

  if ((pid = fork()) < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (pid > 0)    // Parent
  {
    if (sigaction(SIGCHLD, &act, NULL) == -1)
    {
        perror("sigaction cannot set SIGCHLD");
        exit(SIGCHLD);
    } 

    nanosleep((const struct timespec[]){{0, 500000L}}, NULL);
    kill(pid, SIGURG);
    while (1)
    {
      printf("parent waiting\n");
      nanosleep((const struct timespec[]){{0, 5000L}}, NULL);
    }
  }
  else if (pid == 0)    // Child
  {
    if (sigaction(SIGURG, &act, NULL) == -1)
    {
      perror("sigaction cannot set SIGURG");
      exit(SIGURG);
    }
    while (1)
    {
      printf("child waiting\n");
      nanosleep((const struct timespec[]){{0, 5000L}}, NULL);
    }
  }

  exit(0);
}