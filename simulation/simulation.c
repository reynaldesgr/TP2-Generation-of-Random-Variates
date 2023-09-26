#include <stdio.h>
#include <stdlib.h>

#include "simulation.h"
#include "../imath/math_utility.h"
#include "../display/display_utility.h"
#include "../mt/matsumoto.h"

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
    double r = genrand_real2(); // genrand_real2 to avoid 1
    return -mean * log(1.0 - r);
}


void boxMuller(double * x1, double * x2)
{
    // Calculation of rn1 and rn2 : random numbers
    double rn1 = genrand_real1();
    double rn2 = genrand_real1();

    *x1       = cos(2 * M_PI * rn2) * (sqrt(-2 *log(rn1)));
    *x2       = sin(2 * M_PI * rn2) * (sqrt(-2 *log(rn1)));
}

double f(double x)
{
    return exp(-x);
}

double genericRejectionBM(double * x1, double * x2, double minX, double maxX, double minY, double maxY)
{
    do{
        boxMuller(x1, x2);
    }while (*x1 < minX | *x1 > maxX | *x2 > maxY | *x2 < minY);
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

void simulateRoll20DiceSum()
{
    int sum                     = 0;
    double sum_of_squares       = 0.0;

    int histogram[NUM_BINS]  = {0};

    // Simulate the experiment 'NUM_SIMULATIONS' times
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        int experiment_sum = 0;

        // Roll the dice 'NUM_ROLLS' times and calculate the sum
        for (int j = 0; j < NUM_ROLLS; j++) {
            int roll = uniform(1,6); // Generate a random number between 1 and 6
            experiment_sum += roll;
        }

        // Update the running total and sum of squares
        sum += experiment_sum;
        sum_of_squares += experiment_sum * experiment_sum;

        // Update the histogram based on the experiment sum
        histogram[experiment_sum]++;
    }

    // Calculate the average and standard deviation
    double average = (double)sum / NUM_SIMULATIONS;
    double variance = (sum_of_squares / NUM_SIMULATIONS) - (average * average);
    double std_deviation = sqrt(variance);

    printf("Average: %.2lf\n", average);
    printf("Standard Deviation: %.2lf\n", std_deviation);

    /*for (int i = 20; i < 120; i++) {
        printf("%d-%d: %d\n", i, i+1, histogram[i]);
    }*/
}
