#include <stdio.h>
#include <stdlib.h>

#include "../mt/matsumoto.h"
#include "../display/display_utility.h"

/**
 * @brief This function return a pseudo-random number between a and b : [a, b]
 * 
 * @param a lower bound (minimum value that the random number can take)
 * @param b upper bound (maximum value that the random number can take)
 * 
 * @return r : a pseudo-random number 
*/

double uniform(double a, double b)
{
    double r = genrand_real1();
    
    return a + (b - a) * r;
}


/**
 * @brief This function implements the Poisson's Law based on the mathematical definition.
 * 
 * @param m values average of points
 * 
 * @return r : a pseudo-random number
*/

double negExp(double mean)
{
    double r = (double) rand() / ((double) RAND_MAX + 1); // Utilisation de RAND_MAX + 1 pour exclure 1
    return -mean * log(1.0 - r);
}

double randomIndividual()
{
    return genrand_real1();
}


void simulateClasses_1()
{
    double classA   = 0;
    double classB   = 0;
    double classC   = 0;

    int    drawings = 1000;
    int    i;
    double individual;

    double array[3] = {0};

    for (i = 0; i <= drawings; i++)
    {
        individual = randomIndividual();

        if (individual < 0.5)
        {
            classA++;
        }
        else if (individual >= 0.5 && individual < 0.65)
        {
            classB++;
        }
        else
        {
            classC++;
        }    
    }

    // 
    array[0]    = classA / drawings;
    array[1]    = array[0] + (classB / drawings);
    array[2]    = array[1] + (classC / drawings);

    displayArray(array, 3);
}

void simulateClassesBound(double a, double b, int sizeSample, int drawings, int numberClasses)
{
    int    i;
    double individual;

    double * array = (double *) calloc(numberClasses, sizeof(double));

    if (array)
    {
        for (i = 0; i <= drawings; i++)
        {
            individual = uniform(a, b);
            array[(int) (individual - a) / sizeSample]++;
            //printf("%f : %d \n", individual, (int) (individual - a) / sizeSample);
        }  
    }
    displayArray(array, sizeSample);
}

int simulateHDLClass(const double * cumulativeArray, double individualPSR)
{
    int    i;
    i   = 0;
    while (individualPSR > cumulativeArray[i])
    {
        i++;
    }
    return i; 
   //printf("\n HDL Results : individual is class %d with a psr at %f. \n", i+1, individualPSR);
}