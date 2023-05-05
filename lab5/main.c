#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int MIN = 9999; /*Used when you implement the thread function */

int main(int argc, char *argv[])
{
  int *array;
  struct ArrayPackage onePackage;
  int size = 0;
  int num_threads;
  int increments;
  int min = 9999;
  pthread_t *thread_ids;
  void *p_status;

  if (pthread_mutex_init(&min_lock, NULL) != 0)
  {
    perror("Could not create mutex for MIN: ");
    return 1;
  }
  printf("How many threads? ");
  scanf("%d", &num_threads);
  thread_ids = (pthread_t *)malloc(sizeof(pthread_t *) * num_threads);

  do
  {
    printf("How big is the array (100 elements or more)? ");
    scanf("%i", &size);
  } while (size < 100);
  array = (int *)malloc(sizeof(int) * size);

  increments = size / num_threads;

  if (initialize(array, size) != 0)
  {
    printf("initialization error\n");
    exit(1);
  }

  printArray(array, size);

  for (int i = 0; i < num_threads; i++)
  {
    struct ArrayPackage *onePack =
        (struct ArrayPackage *)malloc(sizeof(struct ArrayPackage));
    /*-------------------------------------------------------------------*/
    /* Store the array, the start, and the end into the onePack instance */
    onePack->start = i*increments;
    onePack->end = i*increments + increments;
    if (i == num_threads-1)
    {
      onePack->end == size;
    }
    onePack->array = array;
    /*---------------------------------------------------------------------*/
    /* Call the pthread_create */
    if (pthread_create(&thread_ids[i], NULL, findMin, onePack) > 0)
    {
      perror("error creating thread: ");
      return 2;
    }
  }
  
  for (int i = 0; i < num_threads; i++)
  {
    /*---------------------------------------------------------------------*/
    /*Call the join                                                        */
    if (pthread_join(thread_ids[i], &p_status) != 0)
    {
      perror("trouble joining thread: ");
      return 3;
    }
  }

  /*-----------------------------------------------------------------------*/
  if (pthread_mutex_lock(&min_lock) != 0)
  {
    perror("Could not lock output: ");
    exit(4); //something horrible happened - exit whole program with error
  }

  printf("\nMin value in array is: %d\n\n", MIN);

  if (pthread_mutex_unlock(&min_lock) != 0)
  {
    perror("Could not unlock output: ");
    exit(5); //something horrible happened - exit whole program with error
  }

  free(array);
  free(thread_ids);
  return 0;
}