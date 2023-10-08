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
 * @brief Generate a pseudo-random number between a and b: [a, b].
 * 
 * @param a Lower bound (minimum value that the random number can take).
 * @param b Upper bound (maximum value that the random number can take).
 * 
 * @return A pseudo-random number in the specified range [a, b].
 */

double uniform(double a, double b)
{
    double r = genrand_real1();
    
    return a + (b - a) * r;
}


/**
 * @brief Generate a random number following the exponential negative distribution.
 * 
 * @param mean Mean of the distribution.
 * 
 * @return A random number following the exponential negative distribution.
 */

double negExp(double mean)
{
    double r = genrand_real2(); // genrand_real2 to avoid 1
    return -mean * log(1.0 - r);
}

/**
 * @brief Generate two random numbers following the standard normal distribution (N(0,1))
 *        using the Box-Muller method.
 * 
 * @param x1 Pointer to store the first Gaussian variable.
 * @param x2 Pointer to store the second Gaussian variable.
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
 * @brief Generate a random number between [0, 1].
 * 
 * @return A random number between [0, 1].
 */

double randomIndividual()
{
    return genrand_real1();
}


/**
 * @brief Simulate classes and calculate their probabilities.
 * 
 * This function simulates classes based on randomIndividual() values and calculates
 * the probabilities of three classes (classA, classB, and classC) within a given
 * number of drawings. The probabilities are then displayed using displayArray().
 */

void simulateClasses1()
{
    double classA   = 0;
    double classB   = 0;
    double classC   = 0;

    int    drawings = 1000;
    int    i;
    double individual;

    // Array to store class probabilities
    double array[3] = {0};

    for (i = 0; i <= drawings; i++)
    {
        // Generate a random individual
        individual = randomIndividual();

        if (individual < 0.5)
        {
            classA++; // Count class A
        }
        else if (individual >= 0.5 && individual < 0.65)
        {
            classB++; // Count class B
        }
        else
        {
            classC++; // Count class C
        }    
    }

    // Calculate class A, B, C probabilities
    array[0]    = classA / drawings;
    array[1]    = array[0] + (classB / drawings);
    array[2]    = array[1] + (classC / drawings);

    // Display class probabilities
    displayArray(array, 3);
}


/**
 * @brief Simulate an HDL cholesterol class based on individual PSR.
 * 
 * This function simulates an individual's class for HDL 'good' cholesterol study
 * based on their individual PSR (Percentile Score Rank) and the cumulative array
 * of probabilities for each class.
 * 
 * @param cumulativeArray An array of cumulative probabilities for each class.
 * @param individualPSR The individual's PSR (Percentile Score Rank).
 * 
 * @return The individual's class.
 */

int simulateHDLClass(const double * cumulativeArray, double individualPSR)
{
    int    i;

    i       = 0;

    // Find the class based on individual PSR using CDF
    while (individualPSR > cumulativeArray[i])
    {
        i++;
    }

    return i; 
}

/**
 * @brief Simulate rolling a six-sided dice 20 times and summing the results.
 * 
 * This function simulates rolling a six-sided dice 20 times and summing the results.
 * It also displays a histogram of the results, as well as the mean and standard deviation
 * of the simulation.
 */

void simulateRoll20DiceSum()
{
    int roll;
    int face;

    int sum                             = 0;
    double sum_of_squares               = 0.0;

    int    histogram [101]              = {0};
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
 * @brief Simulate the Box-Muller distribution.
 * 
 * This function simulates the Box-Muller distribution and displays a histogram of the results.
 */

void simulateBMDistribution()
{
    int     index1;
    int     index2;
    int     binx1;
    int     binx2;
    double  x1;
    double  x2;

    double          meanBM                  = 0.;
    int             histogram[NUM_BINS];
    double      *   valuesBM                = malloc(2*NUM_SIMULATIONS_BM*sizeof(double));
    
    int i;

    for (i = 0; i < 2 * NUM_SIMULATIONS_BM; i++) 
    {
        // Generate pairs of Gaussian random numbers
        boxMuller(&x1, &x2);
        valuesBM[i] = x1;
        i++;
        valuesBM[i] = x2;  
    }

    // Create a histogram of the generated values
    createHistogram(MIN_X, MAX_X, NUM_BINS, histogram, valuesBM, 2 * NUM_SIMULATIONS_BM);
    // Free memory allocated for values
    free(valuesBM);
}


/**
 * @brief Simulate a random variable using rejection/acceptance method.
 * 
 * This function uses the density function of a Gaussian law while performing a rejection step based on the desired
 * mean and standard deviation.
 * 
 * @param numSimulation Number of simulations to perform.
 * @param mean Mean of the distribution.
 * @param stdDeviation Standard deviation of the distribution.
 * @param minX Lower-bound for the first Gaussian variable.
 * @param maxX Upper-bound for the first Gaussian variable.
 * @param minY Lower-bound for the second Gaussian variable.
 * @param maxY Upper-bound for the second Gaussian variable.
 * 
 */

void genericRejection(double numSimulation, double mean, double stdDeviation, double minX, double maxX, double minY, double maxY)
{
    for (int i = 0; i < numSimulation; i++) 
    {
        double x, y, f;
        double na1, na2;
        do
        {
            // Generate two random number between [0, 1]
            na1 = genrand_real1();
            na2 = genrand_real1();

            // Scale the random numbers to the desired range
            x   = minX + na1 * (maxX - minX);
            y   = maxY * na2;

            // Call to the density function f of a continious law
            f   = gaussianDensityFunction(x, mean, stdDeviation);

            if (y <= f)
            {
                printf("(%f, %f) \t==>\t Accepted\n", x, y);
            }
            else
            {
                printf("(%f, %f) \t==>\t Rejected\n", x, y);
            }

        } while (y > f); // Continue until a valid value is accepted
    }
}


