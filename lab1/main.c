#include <stdio.h>
void swap(int *x, int *y)
{
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
  return;
} /* end swap */

/* In main, the call will look something like this */
int main()
{
  int a;
  int b;
  printf("Please enter an integer: ");
  scanf("%i", &a);
  printf("Please enter a second integer: ");
  scanf("%i", &b);

  swap(&a, &b);
  printf("The number swapped is: %i %i\n", a, b);

  return 0;
}