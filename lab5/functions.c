#include "functions.h"
/* FUNCTION: initialize
 * This function should initialize the array
 * to random values between 1 and 500
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */
int initialize(int *array, int length)
{
  srand(getpid());
  int i;

  for (i = 0; i < length; i++)
  {
    array[i] = rand() % 500 + 1;
  }

  return 0;
}
/* FUNCTION: findMin
 * This function should find the smallest element in the array and
 * return it through the argument min.
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *     min: set to the smallest value in array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */
/*
int findMin(int *array, int length, int *min)
{
  int i;

  *min = array[0];
  for (i = 1; i < length; i++)
  {
    if (*min > array[i])
    {
      *min = array[i];
    }
  }

  return 0;
}
*/

void* findMin (void* package)
{
  int i;
  struct ArrayPackage *p = (struct ArrayPackage*)package;
  int start = p->start, end = p->end, *array = p->array;
  int min = array[start];

  printf("\nStart:%d, End:%d", start, end);

  for (i = start; i < end; i++)
    if (min > array[i])
      min = array[i];

  if (MIN > min)
  {
    if (pthread_mutex_lock(&min_lock) != 0)
    {
      perror("Could not lock output: ");
      exit(4); //something horrible happened - exit whole program with error
    }

    MIN = min;

    if (pthread_mutex_unlock(&min_lock) != 0)
    {
      perror("Could not unlock output: ");
      exit(5); //something horrible happened - exit whole program with error
    }
  }

  free (package);
  return NULL;
}

/* FUNCTION: printArray
 * This function should print all the elements of the array
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */
int printArray(int *array, int length)
{
  int i;

  for (i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
    // add a newline character for readability
    if ((i + 1) % 15 == 0)
    {
      printf("\n");
    }
  }
  printf("\n");
  return 0;
}
