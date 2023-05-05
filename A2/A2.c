// James Sieben 200455325


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct Parameters
{
    int *arr;
    int size;
    int depth;
};

void mergeSortMain(int *arr, int size, int depth);
void merge(int *s, int *m, int *e);
void *mergeSortThread(void *pv);

int main()
{
    // Declare an array of size 100
    int size = 100;
    int arr[size];
    
    // Populate the array with random integers and print the unsorted array
    srand((unsigned)time(0));
    printf("\nUnsorted:\n");
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 1000;
        printf("%4d ", arr[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");

    // Call the merge sort algo with a depth of 4
    mergeSortMain(arr, size, 4);

    // Print the sorted array
    printf("\nSorted:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%4d ", arr[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");

    return 0;
}

// merge function to integrate the thread's results into the array
void merge(int *s, int *m, int *e)
{
    int *res = malloc((e - s)*sizeof(*res)); // Dynamically allocate enough memory for the array to be sorted
    int *dst = res;
    int *lhs = s; // Left side begins at the start (s)
    int *rhs = m; // Right side begins at the middle (m)

    while (lhs != m && rhs != e)
        *dst++ = (*lhs < *rhs) ? *lhs++ : *rhs++;

    while (lhs != m)
        *dst++ = *lhs++;

    // copy results
    memcpy(s, res, (rhs - s) * sizeof *res);
    free(res);
}

// Passes the thread's info to the main merge sort function
void *mergeSortThread(void *pv)
{
    struct Parameters *p = pv;
    mergeSortMain(p->arr, p->size, p->depth);
    return pv;
}

// The main function for sorting recursively calls itself
void mergeSortMain(int *arr, int size, int depth)
{
    // Base case where only one element is left
    if (size < 2)
    {
        return;
    }
    // If there's 2 or 3 ints left, split and call mergeSortMain with depth of 0
    else if (depth <= 0 || size < 4)
    {
        mergeSortMain(arr, size/2, 0);
        mergeSortMain(arr + size/2, size - size/2, 0);
    }
    // If there's more than 3 ints left, perform the main task
    else
    {
        // Declare a struct in prep of splitting
        struct Parameters p = {arr, size/2, depth/2};
        pthread_t t;

        // Create a new thread
        pthread_create(&t, NULL, mergeSortThread, &p);

        // Call the main merge sort function on the first part of the new array
        mergeSortMain(arr + size/2, size - size/2, depth/2);

        // Join the thread
        pthread_join(t, NULL);
    }

    // Finally, merge partitions together
    merge(arr, arr+size/2, arr+size);
}