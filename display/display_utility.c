/**
 * @file display_utility.c
 * 
 * @brief This files implements display's methods.
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function displays the values of an array.
 * 
 * This function prints the values of a given array.
 * 
 * @param array The array of values to be displayed.
 * @param size The size of the array.
 */

void displayArray(const double  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Array[%d] \t : %.2f \n", i, array[i]);
    }
}

/**
 * @brief This function displays the number of individuals per class.
 * 
 * This function prints the count of individuals in each class along with their class numbers.
 * 
 * @param array The array of counts representing the number of individuals in each class.
 * @param size The number of classes.
 */

void displayClass(const int  * array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Class %d \t : %d \n", i + 1, array[i]);
    }
}
