/**
 * @file simulation.c
 * 
 * @brief This file contains functions/procedures implementing randomess
 * and differents simulation techniques based on Lab #2 - Generation of Random Variates
 * 
*/

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

/**
 * @brief This function generates numbers following the standard normal distribution
 * N(0,1) using Box-Muller method
 * 
 * @param x1 First gaussian variable
 * @param x2 Second gaussian variable
 *
*/

void boxMuller(double * x1, double * x2)
{
    // Calculation of rn1 and rn2 : random numbers
    double rn1 = genrand_real1();
    double rn2 = genrand_real1();

    *x1       = cos(2 * M_PI * rn2) * (sqrt(-2 *log(rn1)));
    *x2       = sin(2 * M_PI * rn2) * (sqrt(-2 *log(rn1)));
}

/**
 * @brief This function use the Box-Muller method to generate pairs
 * of Gaussian random numbers (standard normal distribution) while 
 * performing a rejection step
 * 
 * @param x1 First gaussian variables generated by BM algorithm
 * @param x2 Second gaussian variables generated by BM algorithm
 *
 * @param minX Lower-bound for x1
 * @param maxX Upper-bound for x1
 * 
 * @param minY Lower-bound for x2
 * @param maxY Upper-bound for x2
 * 
*/

double genericRejection(double mean, double stdDeviation, double minX, double maxX, double minY, double maxY)
{
    double x, y;
    double na1, na2;
    do
    {
        boxMuller(&na1, &na2);
        x   = minX + na1 * (maxX - minX);
        y   = maxY * na2;
        printf("x = %f \t|\t \n | y = %f \t|\t f(x) = %f\t=>\t ", x, y, gaussianDensityFunction(x, mean, stdDeviation));

        if (y > gaussianDensityFunction(x, mean, stdDeviation ))
        {
            printf("Accepted \n");
        }
        else
        {
            printf("Rejected\n");
        }

    } while (y > gaussianDensityFunction(x, mean, stdDeviation ));

}

/**
 * @brief This function return a random number between [0, 1]
 * 
 * @return a random number between [0, 1]
*/

double randomIndividual()
{
    return genrand_real1();
}

/**
 * @brief This function is used to answer part 3
 * 3 - Reproduction of discrete empirical distributions
*/

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


/**
 * @brief This function simulate a PSR result of a individual 
 * for the HDL 'good' cholesterol study.
 * 
 * @return The individual's class
*/

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

/**
 * @brief This function performs a roll dice and sum the
 * result 20 times and display a histogram of the results.
 * It also display the mean and standard deviation of a simulation.
*/

void simulateRoll20DiceSum()
{
    int roll;
    int face;

    int sum                             = 0;
    double sum_of_squares               = 0.0;

    int    histogram [NUM_BINS]         = {0};
    double valuesDice[NUM_SIMULATIONS];

    // Simulate the experiment 'NUM_SIMULATIONS' times
    for (int i = 0; i < NUM_SIMULATIONS; i++) 
    {
        // Sum 'NUM_ROLLS' times the faces obtained
        for (int i = 0; i < NUM_ROLLS; i++)
        {
            face = uniform(1, 6);
            sum+=face;
        }
        valuesDice[i] = sum;
        sum           = 0;
    }

    createHistogram(20, 120, 100, histogram, valuesDice, NUM_SIMULATIONS);
}

/**
 * @brief This function test NUM_SIMULATION times the Box Muller function 
 * to generate numbers around 0 following N(0,1). 
*/

void simulateBMDistribution()
{
    int     index1;
    int     index2;
    int     binx1;
    int     binx2;
    double  x1;
    double  x2;

    double meanBM = 0.;
    int         histogram     [NUM_BINS];
    double      valuesBM      [NUM_SIMULATIONS];
    
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        boxMuller(&x1, &x2);
        valuesBM[i] = x1;
    }

    createHistogram(MIN_X, MAX_X, NUM_BINS, histogram, valuesBM, NUM_SIMULATIONS);
}


/**
 * @brief This function test the acceptance/rejection algorithm for a gaussian law
 * 
 * @param mean Mean of the gaussian law
 * @param stdDeviation Standard deviation of the gaussian law
 * 
*/

void testingRejection(double mean, double stdDeviation)
{
    double x1, x2;
    double      valuesBM      [10];
    
    for (int i = 0; i < 10; i++) {
        genericRejection(mean, stdDeviation, -1, 1, -1, 1);
    }
}


