#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(void)
{
  printf("Hello \n");
  pid_t ret = fork();
  if (ret > 0)
    cout << "Parent\n";
  else if (ret == 0)
    cout << "Child\n";
  return 0;
}
