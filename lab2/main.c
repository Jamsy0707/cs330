//James Sieben 200455325

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(int argc, char *argv[])
{
  int min = 9999;
  int size = 0;

  printf("How big is the array? ");
  scanf("%d", &size);
  int *array = (int*)malloc(size*sizeof(int));
  if (initialize(array, size) != 0)
  {
    printf("initialization error\n");
    exit(1);
  }

  if (returnMin(array, size, &min) != 0)
  {
    printf("someFunction error\n");
    exit(1);
  }
  printf("min value in array is: %d\n", min);

  free(array);

  exit(0);
}
