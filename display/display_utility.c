/**
 * @file display_utility.c
 * 
 * @brief This files implements display's methods.
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function display the values of a array
*/

void displayArray(const double  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Array[%d] \t : %.2f \n", i, array[i]);
    }
}

/**
 * @brief This function display the number of individuals 
 * per class
*/

void displayClass(const int  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Class %d \t : %d \n", i + 1, array[i]);
    }
}
