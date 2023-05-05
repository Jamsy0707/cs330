#include <stdio.h>
#include <stdlib.h>

int DivideInt(int, int, int *);

int main()
{
	int x, y, z;
    scanf("%i", &x);
    scanf("%i", &y);

    DivideInt(x,y,&z);

    printf("x / y = %i\n", z);

    int *a;
    a = (int*)malloc(10*sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        a[i] = rand();
    }
    free(a);

	return 0;
}


int DivideInt(int a, int b, int *c)
{

	*c = a / b;

}