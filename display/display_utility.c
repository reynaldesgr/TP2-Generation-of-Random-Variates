#include <stdio.h>
#include <stdlib.h>

void displayArray(const double  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Array[%d] \t : %.2f \n", i, array[i]);
    }
}


void displayClass(const int  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Class %d \t : %d \n", i + 1, array[i]);
    }
}
