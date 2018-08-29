#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n, max;
    int* ptr;

    printf("Enter total number of elements: ");
    scanf("%d", &n);
    printf("\n");

    ptr = (int*) malloc(n * sizeof(int));
    if(ptr == NULL)
    {
     	printf("Error! memory not allocated.");
        return -1;
    }


    // Stores number entered by the user
    for(i = 0; i < n; ++i)
    {
       printf("Enter Number %d: ", i+1);
       scanf("%d", ptr + i);
    }

    // Loop to store largest number to max
    // INVAR: Largest element in first i elements stored in max
    for(i = 1; i < n; ++i)
    {
       // Change < to > if you want to find the smallest element
       if(max < *(ptr + i))
           max = *(ptr + i);
    }
    printf("Largest element = %d\n", max);

    free(ptr);

    return 0;
}