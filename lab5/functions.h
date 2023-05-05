#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ArrayPackage
{
  int *array;
  int start;
  int end;
};

extern int MIN;
pthread_mutex_t min_lock;

int initialize(int *array, int length);
void* findMin(void *package);
int printArray(int *array, int length);

#endif
